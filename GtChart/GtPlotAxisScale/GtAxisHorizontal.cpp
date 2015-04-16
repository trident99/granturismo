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

#include ".\GtAxisHorizontal.h"
#include "..\GtPlotAxisScale\GtScaleBase.h"
#include <modHtlMath.h>

namespace GT
{
	namespace GtChart
	{
		//!Parent set constructor
		GtAxisHorizontal::GtAxisHorizontal(GtObject* ptrParent)
			:GtPlotItem(ptrParent)
		{
			m_sngUB = 10.0f;
			m_sngLB = 0.0f;
			m_sngMajor = 1.0f;
			m_sngMinor = 0.50f;
			m_ptrScale = new GtScaleBase(this);
			m_strFormat = "%3.1f";
			m_strLabel = "XAxis";

		};

		//!Virtual destructor
		GtAxisHorizontal::~GtAxisHorizontal(void)
		{

		};

		//Transform Model to Viewport 
		void GtAxisHorizontal::ModelToViewPt(float & ptModel, float & ptView)
		{
			if(m_ptrScale)
			{
				m_ptrScale->ModelToViewPt(ptModel,ptView);
			}
		};
		//Transform Model to Viewport 
		void GtAxisHorizontal::ModelToViewPt(long & ptModel, long & ptView)
		{
			if(m_ptrScale)
			{
				float sngMod, sngView;
				sngMod = (float)ptModel;
				m_ptrScale->ModelToViewPt(sngMod,sngView);
				ptView = (long)sngView;
			}
		};

		//Viewport to Model Transformation
		void GtAxisHorizontal::ViewToModelPt(float & ptView, float & ptModel)
		{
			if(m_ptrScale)
			{
				m_ptrScale->ViewToModelPt(ptView,ptModel);
			}
		};
		//Viewport to Model Transformation
		void GtAxisHorizontal::ViewToModelPt(long & ptView, long & ptModel)
		{
			if(m_ptrScale)
			{
				float sngMod, sngView;
				sngView = (float) ptView;
				m_ptrScale->ViewToModelPt(sngView,sngMod);
				ptModel = (long)sngMod;
			}
		};
		//!Get the bounding rectangle of the item
		GtRectI GtAxisHorizontal::BoundingRect(void)
		{
			return m_objFrame;	
		};
		//!Updates the scale settings
		void GtAxisHorizontal::Update(void)
		{
			//y = M * x + B
			float sngM, sngB;
			GtPoint3DI ptCursor, pt0, pt1;
			//draw the main line
			sngM = (m_objFrame.xMax - m_objFrame.xMin) / (m_sngUB - m_sngLB);
			m_ptrScale->Set_sngScale(sngM);
			sngB = (float)m_objFrame.xMin - (sngM * m_sngLB);
			m_ptrScale->Set_sngOrigin(sngB);

		};

		//!Required Draw function for the plot item, must be implemented
		int GtAxisHorizontal::Draw( GtPainter *painter)
		{
			//draw the scale,
			//draw the ticks,
			//draw the text
			if(!painter){return NULL;};//safety check
			if(!m_ptrScale){return NULL;};//safety check
			painter->Set_objBrush(GtBrush(GtColor(255,255,255)));
			painter->Set_objPen(GtPen(GtColor(0,0,0)));


			float sngScaleX;
			GtPoint3DI ptCursor, pt0, pt1, textPt;
			char chrVal[32];
			//draw the main line
			if(m_ptrScale->Get_objScaleType() == ScaleLinear)
			{
				pt0.x = m_objFrame.xMin; pt0.y = m_objFrame.yMin;
				pt1.x = m_objFrame.xMax; pt1.y = m_objFrame.yMin;
				painter->GtDrawLine(pt0,pt1);
				//draw minor ticks
				float ptX = 0.0f;
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptX);
					pt0.x = (long)ptX; pt0.y = m_objFrame.yMin;
					pt1.x = (long)ptX; pt1.y = m_objFrame.yMin+5;
					painter->GtDrawLine(pt0,pt1);
					i = i + (m_sngMinor);
				}
				//draw major ticks
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptX);
					pt0.x = (long)ptX; pt0.y = m_objFrame.yMin;
					pt1.x = (long)ptX; pt1.y = m_objFrame.yMin+10;
					painter->GtDrawLine(pt0,pt1);

					textPt.x = (long)ptX; textPt.y = m_objFrame.yMin+15;
					sprintf(chrVal,(m_strFormat.c_str()),i);
					std::string strTemp = chrVal;
					//GtStringToWString(strTemp,chrVal);
					painter->GtDrawText(strTemp,textPt);

					i = i + (m_sngMajor);
				}
				//draw the label
				float halfX = float(m_objFrame.xMin + m_objFrame.xMax) / (2.0f);
				textPt.x = (long)halfX; textPt.y = m_objFrame.yMin + 35;
				painter->GtDrawText(m_strLabel,textPt);
				return 1;
			};//end ScaleLinear

			if(m_ptrScale->Get_objScaleType() == ScaleLogarithm)
			{
				pt0.x = m_objFrame.xMin; pt0.y = m_objFrame.yMin;
				pt1.x = m_objFrame.xMax; pt1.y = m_objFrame.yMin;
				painter->GtDrawLine(pt0,pt1);
				float ptX = 0.0f;
				float logShift = m_sngLB;
				float nextShift = 10.0 * logShift;
				//draw major ticks
				bool blnFirst = true;
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					
					this->ModelToViewPt(i,ptX);
					pt0.x = (long)ptX; pt0.y = m_objFrame.yMin;
					pt1.x = (long)ptX; pt1.y = m_objFrame.yMin+10;
					painter->GtDrawLine(pt0,pt1);

					textPt.x = (long)ptX; textPt.y = m_objFrame.yMin+15;
					sprintf(chrVal,(m_strFormat.c_str()),i);
					std::string strIn = chrVal;
					//GtStringToWString(strTemp,strIn);
					if(blnFirst)
					{
						blnFirst = false;
						painter->GtDrawText(strIn,textPt);
					}
					if(i >= nextShift) 
					{
						painter->GtDrawText(strIn,textPt);
						logShift = nextShift;
						nextShift = 10.0f * nextShift;
					};
					i = i + (logShift);
				}
				//draw the label
				float halfX = float(m_objFrame.xMin + m_objFrame.xMax) / (2.0f);
				textPt.x = (long)halfX; textPt.y = m_objFrame.yMin + 35;
				painter->GtDrawText(m_strLabel,textPt);
				return 1;
			};//end ScaleLogarithm

			return 1;
		};

	
		int GtAxisHorizontal::DrawMajorGrid(GtRectI & frame, GtPainter * painter)
		{
			//draw the scale,
			//draw the ticks,
			//draw the text
			if(!painter){return NULL;};//safety check
			if(!m_ptrScale){return NULL;};//safety check
			float ptX;
			GtPoint3DI ptCursor, pt0, pt1;
			//draw the main line

			painter->Set_objPen(GtPen(GtColor(0,0,0)));

			//draw the main line
			if(m_ptrScale->Get_objScaleType() == ScaleLinear)
			{
				//draw major ticks
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptX);
					pt0.x = (long)ptX; pt0.y = frame.yMin;
					pt1.x = (long)ptX; pt1.y = frame.yMax;
					painter->GtDrawLine(pt0,pt1);
					i = i + (m_sngMajor);
				}
				return 1;
			};

			if(m_ptrScale->Get_objScaleType() == ScaleLogarithm)
			{
				pt0.x = m_objFrame.xMin; pt0.y = m_objFrame.yMin;
				pt1.x = m_objFrame.xMax; pt1.y = m_objFrame.yMin;
				painter->GtDrawLine(pt0,pt1);
				float ptX = 0.0f;
				float logShift = m_sngLB;
				float nextShift = 10.0 * logShift;
				//draw major ticks
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptX);
					pt0.x = (long)ptX; pt0.y = frame.yMin;
					pt1.x = (long)ptX; pt1.y = frame.yMax;
					painter->GtDrawLine(pt0,pt1);

					if(i >= nextShift) 
					{
						logShift = nextShift;
						nextShift = 10.0f * nextShift;
					};
					i = i + (logShift);
				}
				return 1;
			};//end ScaleLogarithm

			return 0;
		};
		int GtAxisHorizontal::DrawMinorGrid(GtRectI & frame, GtPainter * painter)
		{
			//draw the scale,
			//draw the ticks,
			//draw the text
			if(!painter){return NULL;};//safety check
			if(!m_ptrScale){return NULL;};//safety check
			float ptX;
			GtPoint3DI ptCursor, pt0, pt1;

			//draw the main line
			if(m_ptrScale->Get_objScaleType() == ScaleLinear)
			{
				//draw the main line
				painter->Set_objPen(GtPen(GtColor(0,0,0),DashLine));
				//draw major ticks
				for(float i = m_sngLB; i < (m_sngUB + .001); )
				{
					this->ModelToViewPt(i,ptX);
					pt0.x = (long)ptX; pt0.y = frame.yMin;
					pt1.x = (long)ptX; pt1.y = frame.yMax;
					painter->GtDrawLine(pt0,pt1);
					i = i + (m_sngMinor);
				}
				return 1;	
			};

			return 0;
		};
	};//end namespace GtChart

};//end namespace GT