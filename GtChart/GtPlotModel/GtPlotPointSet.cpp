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

#include ".\GtPlotPointSet.h"
#include "..\GtPlotAxisScale\GtAxisHorizontal.h"
#include "..\GtPlotAxisScale\GtAxisVertical.h"

namespace GT
{
	namespace GtChart
	{
			//!Parent set constructor
		GtPlotPointSet::GtPlotPointSet(GtObject* ptrParent)
			:GtPlotItem(ptrParent)
		{

		};
			//!Virtual destructor
		GtPlotPointSet::~GtPlotPointSet(void)
		{

		};
	
		GtPlotPointSet & GtPlotPointSet::operator = (GtPlotPointSet & rhs)
		{
			if(this == &rhs)
				return *this;

			HtlBase::operator=(rhs);

			//ORSSerializable Initialization
			m_strType = "GtPlotPointSet";
			//GtPlotPointSet Initialization////////////////////
			size_t i, intNumPts;
			m_arrObjPoints.clear();
			intNumPts = rhs.Size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.push_back(rhs.m_arrObjPoints.at(i));
			};
			return *this;	
		};

		bool GtPlotPointSet::operator == (GtPlotPointSet & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrObjPoints.size();
			intRHSNumPoints = rhs.m_arrObjPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return false;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrObjPoints.at(i) != rhs.m_arrObjPoints.at(i)){return false;};
			}
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GtPlotPointSet::operator != (GtPlotPointSet & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrObjPoints.size();
			intRHSNumPoints = rhs.m_arrObjPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return true;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrObjPoints.at(i) != rhs.m_arrObjPoints.at(i)){return true;};
			}
			//made it this far without finding a difference, must be the same
			return false;
		};

		void GtPlotPointSet::Clear(void)
		{
			m_arrObjPoints.clear();
		};
		size_t GtPlotPointSet::Size(void)
		{
			return m_arrObjPoints.size();
		};

		GtPoint3DF & GtPlotPointSet::At(size_t intIndex)
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
		void GtPlotPointSet::PushBack(GtPoint3DF & objNewPoint)
		{
			m_arrObjPoints.push_back(objNewPoint);
			return;
		};
		void GtPlotPointSet::Round(int intNumDecimals)
		{
			size_t i, intNumPoints;
			intNumPoints = m_arrObjPoints.size();
			if(intNumPoints <= 0){return;};
			for(i = 0; i < intNumPoints; i++)
			{
				m_arrObjPoints.at(i).Round(intNumDecimals);
			};
		};

		//!Required Draw function for the plot item, must be implemented
		int GtPlotPointSet::Draw( GtPainter *painter)
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
			GtAxisHorizontal* ptrHoriz = this->Get_ptrXAxis();
			GtAxisVertical* ptrVert = this->Get_ptrYAxis();

			if(!ptrHoriz){return 0;}//safety check
			if(!ptrVert){return 0;}//safety check

			numPts = this->m_arrObjPoints.size();
			if(numPts > 0)
			{
				painter->Set_objBrush(GtBrush(m_objBackColor));
				painter->Set_objPen(GtPen(m_objForeColor));

				for(j = 0; j < (numPts);j++)
				{
					float modX0,modY0;
					float vwX0,vwY0;

					modX0 = (float)this->m_arrObjPoints.at(j).x;
					modY0 = (float)this->m_arrObjPoints.at(j).y;

					//point 0
					ptrHoriz->ModelToViewPt(modX0,vwX0);
					ptrVert->ModelToViewPt(modY0,vwY0);

					//draw the line segment
					m_objSymbol.Set_objModelPos(GtPoint3DF(modX0,modY0));
					m_objSymbol.Set_objCanvasPos(GtPoint3DI((long)vwX0,(long)vwY0));
					m_objSymbol.Draw(painter);

				}//end loop through points

				//draw the point symbols
				//finished, reset old brushes and pens
				painter->Set_objPen(oldPen);
				painter->Set_objBrush(oldBrush);

			}//end point check
			return 1;
		};


		//!Get the bounding rectangle of the item
		GtRectI & GtPlotPointSet::BoundingModelRect(void)
		{

			m_modelRect.Zero();

			size_t i, numPts;
			numPts = m_arrObjPoints.size();

			if (numPts <= 0){ return m_modelRect; }//safety check

			m_modelRect.xMin = (long)m_arrObjPoints.at(0).x;
			m_modelRect.yMin = (long)m_arrObjPoints.at(0).y;
			m_modelRect.xMax = (long)m_arrObjPoints.at(0).x;
			m_modelRect.yMax = (long)m_arrObjPoints.at(0).y;
			for (i = 0; i < numPts; i++)
			{
				if (m_arrObjPoints.at(i).x < m_modelRect.xMin){ m_modelRect.xMin = (long)m_arrObjPoints.at(i).x; };
				if (m_arrObjPoints.at(i).y < m_modelRect.yMin){ m_modelRect.yMin = (long)m_arrObjPoints.at(i).y; };
				if (m_arrObjPoints.at(i).x > m_modelRect.xMax){ m_modelRect.xMax = (long)m_arrObjPoints.at(i).x; };
				if (m_arrObjPoints.at(i).y > m_modelRect.yMax){ m_modelRect.yMax = (long)m_arrObjPoints.at(i).y; };
			}

			return m_modelRect;
		};

		//!Get the bounding rectangle of the item
		GtRectI & GtPlotPointSet::BoundingCanvasRect(void)
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