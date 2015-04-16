/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
**  Qwt Widget Library
**
**  GT is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to GT.
**
**  GT is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with GT.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtPlotBar.h"
#include "..\GtPlotAxisScale\GtAxisHorizontal.h"
#include "..\GtPlotAxisScale\GtAxisVertical.h"
#include <modHtlMath.h>

namespace GT
{
	namespace GtChart
	{

		//GTBARITEM MEMBER FUNCTIONS///////////////////////
		GtBarItem::GtBarItem()	
		{
			m_sngPos = 0.0f;
			m_dblVal = 0.0f;
			m_objColor.SetRGB(255,0,0);
			m_objRect.Zero();
		}
		GtBarItem::~GtBarItem(){};
		//!Assignment Operator
		GtBarItem & GtBarItem::operator = (const GtBarItem & rhs)
		{
			m_sngPos = rhs.m_sngPos;
			m_dblVal = rhs.m_dblVal;
			m_objColor = rhs.m_objColor;
			m_strName = rhs.m_strName;
			m_objRect = rhs.m_objRect;
			return *this;
		};



		//GTPLOTBAR MEMBER FUNCTIONS///////////////////////
		//!Parent set constructor
		GtPlotBar::GtPlotBar(GtObject* ptrParent)
			:GtPlotItem(ptrParent)
		{

		};
		//!Virtual destructor
		GtPlotBar::~GtPlotBar(void)
		{

		};

		GtPlotBar & GtPlotBar::operator = (GtPlotBar & rhs)
		{
			if(this == &rhs)
				return *this;

			HtlBase::operator=(rhs);

			//ORSSerializable Initialization
			m_strType = "GtPlotBar";
			//GtPlotBar Initialization////////////////////
			size_t i, intNumPts;
			m_arrObjPoints.clear();
			intNumPts = rhs.Size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.push_back(rhs.m_arrObjPoints.at(i));
			};
			return *this;	
		};

		void GtPlotBar::Clear(void)
		{
			m_arrObjPoints.clear();
		};
		size_t GtPlotBar::Size(void)
		{
			return m_arrObjPoints.size();
		};

		GtBarItem & GtPlotBar::At(size_t intIndex)
		{
			size_t intNumPoints;
			intNumPoints = m_arrObjPoints.size();
			if((intIndex >= 0) && (intIndex < intNumPoints))
			{
				return m_arrObjPoints.at(intIndex);
			}else{
				return m_objNullPoint;
			};
		};
		void GtPlotBar::PushBack(GtBarItem & objNewPoint)
		{
			m_arrObjPoints.push_back(objNewPoint);
			return;
		};
		void GtPlotBar::Round(int intNumDecimals)
		{
			size_t i, intNumPoints;
			intNumPoints = m_arrObjPoints.size();
			if(intNumPoints <= 0){return;};
			for(i = 0; i < intNumPoints; i++)
			{
				Math::hround(m_arrObjPoints.at(i).m_dblVal,intNumDecimals);
			};
		};

		//!Required Draw function for the plot item, must be implemented
		int GtPlotBar::Draw( GtPainter *painter)
		{
			if(!painter){return 0;};//safety check

			GtPen oldPen;
			GtBrush oldBrush;
			
			GtPoint3DI textPos;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			size_t j, numPts;
			GtRectI rectH, rectV;
			GtAxisHorizontal* ptrHoriz = this->Get_ptrXAxis();
			GtAxisVertical* ptrVert = this->Get_ptrYAxis();

			if(!ptrHoriz){return 0;}//safety check
			if(!ptrVert){return 0;}//safety check
			numPts = this->m_arrObjPoints.size();


			
			if(numPts > 0)
			{			

				rectH = ptrHoriz->Get_objFrame();
				rectV = ptrVert->Get_objFrame();
				float sngBinWidth = (float)(rectV.yMax - rectV.yMin) / (float)numPts;
				float rectHalfWidth = (float)((0.80) * sngBinWidth * (0.50)); //80% width then half that
				long lngCursorY = (long)(sngBinWidth / 2.0f) + rectV.yMin;

				painter->Set_objBrush(GtBrush(m_objBackColor));
				painter->Set_objPen(GtPen(m_objForeColor));
				//calculate the rects
				for(j = 0; j < numPts; j++)
				{
					m_arrObjPoints.at(j).m_sngPos = (float)lngCursorY;
					m_arrObjPoints.at(j).m_objRect.xMin = rectH.xMin;
					float xmodel,xval;
					xmodel = (float)m_arrObjPoints.at(j).m_dblVal;
					ptrHoriz->ModelToViewPt(xmodel,xval);
					m_arrObjPoints.at(j).m_objRect.xMax = (long) xval;

					m_arrObjPoints.at(j).m_objRect.yMin = lngCursorY - (long)rectHalfWidth;
					m_arrObjPoints.at(j).m_objRect.yMax = lngCursorY + (long)rectHalfWidth;
					//go to next bin
					lngCursorY += (long)sngBinWidth;
				}
				//draw the rects
				//calculate the rects
				for(j = 0; j < numPts; j++)
				{
					painter->Set_objBrush(GtBrush(m_arrObjPoints.at(j).m_objColor));
					painter->GtFillRect(m_arrObjPoints.at(j).m_objRect);
				}
							
				//finished, reset old brushes and pens
				painter->Set_objPen(oldPen);
				painter->Set_objBrush(oldBrush);

			}//end point check
			return 1;
		};


		//!Get the bounding rectangle of the item
		GtRectI & GtPlotBar::BoundingModelRect(void)
		{

			m_modelRect.Zero();

			size_t i, numPts;
			numPts = m_arrObjPoints.size();

			if (numPts <= 0){ return m_modelRect; }//safety check

			m_modelRect.xMin = (long)m_arrObjPoints.at(0).m_dblVal;
			m_modelRect.yMin = (long)m_arrObjPoints.at(0).m_sngPos;
			m_modelRect.xMax = (long)m_arrObjPoints.at(0).m_dblVal;
			m_modelRect.yMax = (long)m_arrObjPoints.at(0).m_sngPos;
			for(i = 0; i < numPts; i++)
			{
				if (m_arrObjPoints.at(i).m_dblVal < m_modelRect.xMin){ m_modelRect.xMin = (long)m_arrObjPoints.at(i).m_dblVal; };
				if (m_arrObjPoints.at(i).m_sngPos < m_modelRect.yMin){ m_modelRect.yMin = (long)m_arrObjPoints.at(i).m_sngPos; };
				if (m_arrObjPoints.at(i).m_dblVal > m_modelRect.xMax){ m_modelRect.xMax = (long)m_arrObjPoints.at(i).m_dblVal; };
				if (m_arrObjPoints.at(i).m_sngPos > m_modelRect.yMax){ m_modelRect.yMax = (long)m_arrObjPoints.at(i).m_sngPos; };
			}

			return m_modelRect;
			
		};

		//!Get the bounding rectangle of the item
		GtRectI & GtPlotBar::BoundingCanvasRect(void)
		{

			m_canvasRect.Zero();
			if (!m_ptrXAxis){ return m_canvasRect; };
			if (!m_ptrYAxis){ return m_canvasRect; };
			
			m_modelRect = this->BoundingModelRect();
			//convert the rect to canvas
			m_ptrXAxis->ModelToViewPt(m_modelRect.xMin, m_canvasRect.xMin);
			if (m_canvasRect.xMin < 0){ m_canvasRect.xMin = 0; };
			m_ptrXAxis->ModelToViewPt(m_modelRect.xMax, m_canvasRect.xMax);
			if (m_canvasRect.xMax < 0){ m_canvasRect.xMax = 0; };
			m_ptrYAxis->ModelToViewPt(m_modelRect.yMin, m_canvasRect.yMin);
			if (m_canvasRect.yMin < 0){ m_canvasRect.yMin = 0; };
			m_ptrYAxis->ModelToViewPt(m_modelRect.yMax, m_canvasRect.yMax);
			if (m_canvasRect.yMax < 0){ m_canvasRect.yMax = 0; };

			return m_canvasRect;
		};



	};//end namespace GtChart

};//end namespace GT