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

#include ".\GtPlotPie.h"
#include "..\GtPlotAxisScale\GtAxisHorizontal.h"
#include "..\GtPlotAxisScale\GtAxisVertical.h"
#include <modHtlMath.h>

namespace GT
{
	namespace GtChart
	{

		//GTPieITEM MEMBER FUNCTIONS///////////////////////
		GtPieItem::GtPieItem()	
		{
			m_dblVal = 0.0f;
			m_dblPercent = 0.0f;
			m_sngStartDeg = 0.0f;
			m_sngSpanDeg = 0.0f;
			m_sngInRad = 0.0f;
			m_sngOutRad = 0.0f;
			m_objColor.SetRGB(255,0,0);
			m_objRect.Zero();
		}

		GtPieItem::GtPieItem(const GtPieItem & rhs)
		{
			m_dblVal = rhs.m_dblVal;
			m_dblPercent = rhs.m_dblPercent;
			m_sngStartDeg = rhs.m_sngStartDeg;
			m_sngSpanDeg = rhs.m_sngSpanDeg;
			m_sngInRad = rhs.m_sngInRad;
			m_sngOutRad = rhs.m_sngOutRad;
			m_objColor = rhs.m_objColor;
			m_strName = rhs.m_strName;
			m_objRect = rhs.m_objRect;
		}

		GtPieItem::~GtPieItem(){};
		//!Assignment Operator
		GtPieItem & GtPieItem::operator = (const GtPieItem & rhs)
		{
			m_dblVal = rhs.m_dblVal;
			m_dblPercent = rhs.m_dblPercent;
			m_sngStartDeg = rhs.m_sngStartDeg;
			m_sngSpanDeg = rhs.m_sngSpanDeg;
			m_sngInRad = rhs.m_sngInRad;
			m_sngOutRad = rhs.m_sngOutRad;
			m_objColor = rhs.m_objColor;
			m_strName = rhs.m_strName;
			m_objRect = rhs.m_objRect;
			return *this;
		};



		//GTPLOTPie MEMBER FUNCTIONS///////////////////////
		//!Parent set constructor
		GtPlotPie::GtPlotPie(GtObject* ptrParent)
			:GtPlotItem(ptrParent)
		{

		};
		//!Virtual destructor
		GtPlotPie::~GtPlotPie(void)
		{

		};

		GtPlotPie & GtPlotPie::operator = (GtPlotPie & rhs)
		{
			if(this == &rhs)
				return *this;

			HtlBase::operator=(rhs);

			//ORSSerializable Initialization
			m_strType = "GtPlotPie";
			//GtPlotPie Initialization////////////////////
			size_t i, intNumPts;
			m_arrObjPoints.clear();
			intNumPts = rhs.Size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.push_back(rhs.m_arrObjPoints.at(i));
			};
			this->BoundingModelRect();
			this->BoundingCanvasRect();
			return *this;	
		};

		void GtPlotPie::SetInnerRadius(float innerRad)
		{
			size_t i, intNumPts;
			intNumPts = m_arrObjPoints.size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.at(i).m_sngInRad = innerRad;
			};
			this->BoundingModelRect();
			this->BoundingCanvasRect();
		};

		void GtPlotPie::SetOuterRadius(float outerRad)
		{
			size_t i, intNumPts;
			intNumPts = m_arrObjPoints.size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.at(i).m_sngOutRad = outerRad;
			}
			this->BoundingModelRect();
			this->BoundingCanvasRect();
		};

		void GtPlotPie::Clear(void)
		{
			m_arrObjPoints.clear();
		};
		size_t GtPlotPie::Size(void)
		{
			return m_arrObjPoints.size();
		};

		GtPieItem & GtPlotPie::At(size_t intIndex)
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
		void GtPlotPie::PushBack(GtPieItem & objNewPoint)
		{
			m_arrObjPoints.push_back(objNewPoint);
			this->BoundingModelRect();
			this->BoundingCanvasRect();
			return;
		};
		void GtPlotPie::Round(int intNumDecimals)
		{
			size_t i, intNumPoints;
			intNumPoints = m_arrObjPoints.size();
			if(intNumPoints <= 0){return;};
			for(i = 0; i < intNumPoints; i++)
			{
				m_arrObjPoints.at(i).m_dblVal = Math::hround(m_arrObjPoints.at(i).m_dblVal,intNumDecimals);
			};
		};

		//!Update the percents
		void GtPlotPie::UpdateData(void)
		{
			double dblSum = 0.0f;
			size_t i, intNumPts;
			intNumPts = m_arrObjPoints.size();
			if(intNumPts <= 0){return;};
			for(i = 0; i < intNumPts; i++)
			{
				dblSum += m_arrObjPoints.at(i).m_dblVal;
			};
			for(i = 0; i < intNumPts; i++)
			{
				m_arrObjPoints.at(i).m_dblPercent = m_arrObjPoints.at(i).m_dblVal / dblSum;
			};
			double dblCursor = 0.0f;
			double dblSpan = 0.0f;
			for(i = 0; i < intNumPts; i++)
			{
				m_arrObjPoints.at(i).m_sngStartDeg = (float)dblCursor;
				m_arrObjPoints.at(i).m_sngSpanDeg = (float)(m_arrObjPoints.at(i).m_dblPercent * 360.0f);
				dblCursor += m_arrObjPoints.at(i).m_sngSpanDeg;
			};

		};



		//!Required Draw function for the plot item, must be implemented
		int GtPlotPie::Draw( GtPainter *painter)
		{
			if(!painter){return 0;};//safety check
			size_t i, numPts;
			GtPen oldPen;
			GtBrush oldBrush;			
			GtPoint3DI textPos;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			numPts = this->m_arrObjPoints.size();
			if(numPts <= 0){return 0;}//safety check
			for(i = 0; i < numPts;i++)
			{			
				GtPieItem curr = m_arrObjPoints.at(i);
				painter->Set_objBrush(GtBrush(curr.m_objColor));

				if(curr.m_sngInRad <= 0.001)
				{
					painter->GtDrawPie(m_objCenterPos,(int)curr.m_sngOutRad,curr.m_sngStartDeg,curr.m_sngSpanDeg);
				}else{
					painter->GtDrawArcPie(m_objCenterPos,(int)curr.m_sngInRad,(int)curr.m_sngOutRad,curr.m_sngStartDeg,curr.m_sngSpanDeg);
				}
				//finished, reset old brushes and pens
				painter->Set_objPen(oldPen);
				painter->Set_objBrush(oldBrush);

			}//end point check
			return 1;
		};


		//!Get the bounding rectangle of the item
		GtRectI & GtPlotPie::BoundingModelRect(void)
		{

			m_modelRect.Zero();
			float sngMaxRad = 0.0f;
			size_t i, numPts;
			numPts = m_arrObjPoints.size();

			if (numPts <= 0){ return m_modelRect; }//safety check

			for(i = 0; i < numPts; i++)
			{
				if(m_arrObjPoints.at(i).m_sngOutRad > sngMaxRad)
				{
					sngMaxRad = m_arrObjPoints.at(i).m_sngOutRad;
				}
			}

			m_modelRect.xMin = (long)(m_objCenterPos.x - sngMaxRad);
			m_modelRect.xMax = (long)(m_objCenterPos.x + sngMaxRad);
			m_modelRect.yMin = (long)(m_objCenterPos.y - sngMaxRad);
			m_modelRect.yMax = (long)(m_objCenterPos.y + sngMaxRad);

			return m_modelRect;
			
		};

		//!Get the bounding rectangle of the item
		GtRectI & GtPlotPie::BoundingCanvasRect(void)
		{

			m_canvasRect.Zero();
			if (!m_ptrXAxis){ return m_canvasRect; };
			if (!m_ptrYAxis){ return m_canvasRect; };
			
			m_modelRect = this->BoundingModelRect();
			m_canvasRect = m_modelRect;
			//convert the rect to canvas
			if (m_canvasRect.xMin < 0){ m_canvasRect.xMin = 0; };
			if (m_canvasRect.xMax < 0){ m_canvasRect.xMax = 0; };
			if (m_canvasRect.yMin < 0){ m_canvasRect.yMin = 0; };
			if (m_canvasRect.yMax < 0){ m_canvasRect.yMax = 0; };

			return m_canvasRect;
		};



	};//end namespace GtChart

};//end namespace GT