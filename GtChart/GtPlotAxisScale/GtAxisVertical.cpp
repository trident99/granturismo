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

#include ".\GtAxisVertical.h"
#include "..\GtPlotAxisScale\GtScaleBase.h"
#include <modHtlMath.h>

namespace GT
{
	namespace GtChart
	{
		//!Parent set constructor
		GtAxisVertical::GtAxisVertical(GtObject* ptrParent)
			:GtPlotItem(ptrParent)
		{
			m_sngUB = 10.0f;
			m_sngLB = 0.0f;
			m_sngMajor = 1.0f;
			m_sngMinor = 0.50f;
			m_ptrScale = new GtScaleBase(this);
			m_strFormat = "%3.1f";
			m_strLabel = L"YAxis";
		};

		//!Virtual destructor
		GtAxisVertical::~GtAxisVertical(void)
		{

		};

		//Transform Model to Viewport 
		void GtAxisVertical::ModelToViewPt(float & ptModel, float & ptView)
		{
			if(m_ptrScale)
			{

				m_ptrScale->ModelToViewPt(ptModel,ptView);
				//switch orientation for y
				ptView = (m_objFrame.yMax - ptView) + m_objFrame.yMin;
			}
		};
		void GtAxisVertical::ModelToViewPt(long & ptModel, long & ptView)
		{
			if(m_ptrScale)
			{
				float sngMod, sngView;
				sngMod = (float)ptModel;
				m_ptrScale->ModelToViewPt(sngMod,sngView);
				ptView = (long)sngView;
				//switch orientation for y
				ptView = (m_objFrame.yMax - ptView) + m_objFrame.yMin;
			}
		};
		//Viewport to Model Transformation
		void GtAxisVertical::ViewToModelPt(float & ptView, float & ptModel)
		{
			if(m_ptrScale)
			{
				//switch orientation for y
				ptView = (m_objFrame.yMax - ptView) + m_objFrame.yMin;
				m_ptrScale->ViewToModelPt(ptView,ptModel);

			}
		};
		//Viewport to Model Transformation
		void GtAxisVertical::ViewToModelPt(long & ptView, long & ptModel)
		{
			if(m_ptrScale)
			{
				float sngMod, sngView;
				//switch orientation for y
				ptView = (m_objFrame.yMax - ptView) + m_objFrame.yMin;

				sngView = (float) ptView;
				m_ptrScale->ViewToModelPt(sngView,sngMod);
				ptModel = (long)sngMod;
			}
		};
		//!Get the bounding rectangle of the item
		GtRectI GtAxisVertical::BoundingRect(void)
		{
			return m_objFrame;	
		};
		//!Updates the scale settings
		void GtAxisVertical::Update(void)
		{
			//y = M * x + B
			float sngM, sngB;
			GtPoint3DI ptCursor, pt0, pt1;
			//draw the main line
			sngM = (m_objFrame.yMax - m_objFrame.yMin) / (m_sngUB - m_sngLB);
			m_ptrScale->Set_sngScale(sngM);
			sngB = (float)m_objFrame.yMin - (sngM * m_sngLB);
			m_ptrScale->Set_sngOrigin(sngB);
		};

		//!Required Draw function for the plot item, must be implemented
		int GtAxisVertical::Draw( GtPainter *painter)
		{
			//draw the scale,
			//draw the ticks,
			//draw the text
			if(!painter){return NULL;};//safety check
			if(!m_ptrScale){return NULL;};//safety check
			painter->Set_objBrush(GtBrush(GtColor(255,255,255)));
			painter->Set_objPen(GtPen(GtColor(0,0,0)));

			float sngScaleY;
			GtPoint3DI ptCursor, pt0, pt1,textPt;
			char chrVal[32];

			if(m_ptrScale->Get_objScaleType() == ScaleLinear)
			{

				pt0.x = m_objFrame.xMax; pt0.y = m_objFrame.yMin;
				pt1.x = m_objFrame.xMax; pt1.y = m_objFrame.yMax;
				painter->GtDrawLine(pt0,pt1);
				//draw minor ticks
				float ptY = 0.0f;
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptY);
					pt0.x = m_objFrame.xMax; pt0.y = (long)ptY;
					pt1.x = m_objFrame.xMax-5; pt1.y = (long)ptY;
					painter->GtDrawLine(pt0,pt1);
					i = i + (m_sngMinor);
				}
				//draw major ticks
				ptY = 0.0f;
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptY);
					pt0.x = m_objFrame.xMax; pt0.y = (long)ptY;
					pt1.x = m_objFrame.xMax-10; pt1.y = (long)ptY;
					painter->GtDrawLine(pt0,pt1);

					textPt.x = m_objFrame.xMax-40; textPt.y = (long)ptY;
					sprintf(chrVal,(m_strFormat.c_str()),i);
					std::string strTemp = chrVal;
					//GtStringToWString(strTemp,chrVal);
					painter->GtDrawText(strTemp,textPt);
					i = i + (m_sngMajor);
				}
			};

			if(m_ptrScale->Get_objScaleType() == ScaleLogarithm)
			{
				pt0.x = m_objFrame.xMax; pt0.y = m_objFrame.yMin;
				pt1.x = m_objFrame.xMax; pt1.y = m_objFrame.yMax;
				painter->GtDrawLine(pt0,pt1);
				float ptY = 0.0f;
				float logShift = m_sngLB;
				float nextShift = 10.0 * logShift;
				//draw major ticks
				bool blnFirst = true;
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{

					this->ModelToViewPt(i,ptY);
					pt0.x = m_objFrame.xMax; pt0.y = (long)ptY;
					pt1.x = m_objFrame.xMax-10; pt1.y = (long)ptY;
					painter->GtDrawLine(pt0,pt1);

					textPt.x = m_objFrame.xMin - 50; textPt.y = (long)ptY;
					sprintf(chrVal,(m_strFormat.c_str()),i);
					std::string strIn = chrVal;
					//GtStringToWString(strTemp,strIn);
					if(blnFirst)
					{
						blnFirst = false;
						painter->GtDrawText(strIn, textPt);
					}
					if(i >= nextShift) 
					{
						painter->GtDrawText(strIn, textPt);
						logShift = nextShift;
						nextShift = 10.0f * nextShift;
					};
					i = i + (logShift);
				}
				return 1;
			};

			return 0;
		};

		int GtAxisVertical::DrawMajorGrid(GtRectI & frame, GtPainter * painter)
		{
			//draw the scale,
			//draw the ticks,
			//draw the text
			if(!painter){return NULL;};//safety check
			if(!m_ptrScale){return NULL;};//safety check
			float ptY;
			GtPoint3DI ptCursor, pt0, pt1;
			//draw the main line

			painter->Set_objPen(GtPen(GtColor(0,0,0)));
			//draw the main line
			if(m_ptrScale->Get_objScaleType() == ScaleLinear)
			{
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptY);
					pt0.x = frame.xMin; pt0.y = (long)ptY;
					pt1.x = frame.xMax; pt1.y = (long)ptY;
					painter->GtDrawLine(pt0,pt1);
					i = i + (m_sngMajor);
				}
				return 1;	
			};


			if(m_ptrScale->Get_objScaleType() == ScaleLogarithm)
			{
				float ptY = 0.0f;
				float logShift = m_sngLB;
				float nextShift = 10.0 * logShift;
				//draw major ticks
				bool blnFirst = true;
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{

					this->ModelToViewPt(i,ptY);
					pt0.x = frame.xMin; pt0.y = (long)ptY;
					pt1.x = frame.xMax; pt1.y = (long)ptY;
					painter->GtDrawLine(pt0,pt1);

					if(blnFirst)
					{
						blnFirst = false;
					}
					if(i >= nextShift) 
					{
						logShift = nextShift;
						nextShift = 10.0f * nextShift;
					};
					i = i + (logShift);
				}
				return 1;
			};

			//shouldn't get here
			return 0;

		};
		int GtAxisVertical::DrawMinorGrid(GtRectI & frame, GtPainter * painter)
		{
			//draw the scale,
			//draw the ticks,
			//draw the text
			if(!painter){return NULL;};//safety check
			if(!m_ptrScale){return NULL;};//safety check
			float ptY;
			GtPoint3DI ptCursor, pt0, pt1;
			//draw the main line
			painter->Set_objPen(GtPen(GtColor(0,0,0),DashLine));
			//draw major ticks
			if(m_ptrScale->Get_objScaleType() == ScaleLinear)
			{
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptY);
					pt0.x = frame.xMin; pt0.y = (long)ptY;
					pt1.x = frame.xMax; pt1.y = (long)ptY;
					painter->GtDrawLine(pt0,pt1);
					i = i + (m_sngMinor);
				}
			};
			return 1;				
		};

	};//end namespace GtChart

};//end namespace GT