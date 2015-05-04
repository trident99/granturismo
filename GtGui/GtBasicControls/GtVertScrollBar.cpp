/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
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

#include ".\GtVertScrollBar.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtVertScrollBar::GtVertScrollBar(GtObject* ptrParent)
			:GtSlider(ptrParent)
		{
			m_intMin = 0;
			m_intMax = 100;
			m_intValue = 0;
			m_intDelta = -1;
		};

		//!Virtual destructor
		GtVertScrollBar::~GtVertScrollBar(void)
		{
			m_intValue = 0;
		};


		//!Custom Event Processing
		int GtVertScrollBar::HandleEvent(GtEvent * ptrEvent)
		{

			//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				GtPoint3DI pos;
				pos.x = gRound(ptrEvent->m_objPos.x);
				pos.y = gRound(ptrEvent->m_objPos.y);
				//drawing rectangles
				//GtRectI m_rectHour;
				if( m_rectTop.Contains(pos))
				{
					if(m_intDelta > 0)
					{
						this->Decrement(m_intDelta);
					}else{
						int delta = gRound(0.05 * float(m_intMax - m_intMin));
						if(delta <= 0){delta = 1;};//min delta
						this->Decrement(delta);
					}
					ValueChanged.Emit(m_intValue);
					this->PostPaint();
					return 1;
				};
				if( m_rectBottom.Contains(pos))
				{
					if(m_intDelta > 0)
					{
						this->Increment(m_intDelta);
					}else{
						int delta = gRound(0.05 * float(m_intMax - m_intMin));
						if(delta <= 0){delta = 1;};//min delta
						this->Increment(delta);
					}
					ValueChanged.Emit(m_intValue);
					this->PostPaint(); 
					return 1;
				};

				if( m_rectBar.Contains(pos))
				{
					int delta = gRound(0.1 * float(m_intMax - m_intMin));
					if(delta <= 0){delta = 1;};//min delta
					if(pos.y > m_currPos.y)
					{
						this->Increment(delta);
					}else{
						this->Decrement(delta);
					}
					ValueChanged.Emit(m_intValue);
					this->PostPaint(); 
					return 1;
				};


			};
			return 0;
		};
		//!Custom Widget Painting
		int GtVertScrollBar::OnPaint(GtPainter * painter)
		{
			//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen valPen, oldPen;
			GtBrush oldBrush;
			
			GtPoint3DI checkPos, textPos;
			int width = 4;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			
			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);

			//initialize rects
			if(m_objFrame.Height() < 50)
			{
				//render compact mode
				//draw buttons
				painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
				m_rectTop = m_objFrame;
				m_rectTop.xMax = m_rectTop.xMin + 25; 
				m_rectTop.yMax = m_rectTop.yMin + (long)((double)m_objFrame.Height() / 2.0f);			
				painter->GtDrawRect(m_rectTop);
				painter->GtDrawBevelFrameRaised(m_rectTop,2);

				m_rectBottom = m_objFrame;
				m_rectBottom.xMax = m_rectBottom.xMin + 25; 
				m_rectBottom.yMin = m_rectBottom.yMin + (long)((double)m_objFrame.Height() / 2.0f);
				painter->GtDrawRect(m_rectBottom);
				painter->GtDrawBevelFrameRaised(m_rectBottom,2);

				painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
				painter->GtDrawTriangleUp(m_rectTop,5);
				painter->GtDrawTriangleDown(m_rectBottom,5);
				

			}else{
				//render normal
				//render compact mode
				//draw buttons
				painter->Set_objBrush(GtBrush(GtColor(200,200,200)));
				m_rectBar = m_objFrame;
				m_rectBar.xMax = m_rectBar.xMin + 25; 
				m_rectBar.yMin = m_rectTop.yMax;
				m_rectBar.yMax = m_rectBottom.yMin;
				painter->GtDrawRect(m_rectBar);
								
				painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
				m_rectTop = m_objFrame;
				m_rectTop.xMax = m_rectTop.xMin + 25; 
				m_rectTop.yMax = m_rectTop.yMin + 25;			
				painter->GtDrawRect(m_rectTop);
				painter->GtDrawBevelFrameRaised(m_rectTop,2);

				m_rectBottom = m_objFrame;
				m_rectBottom.xMax = m_rectBottom.xMin + 25; 
				m_rectBottom.yMin = m_rectBottom.yMax - 25;
				painter->GtDrawRect(m_rectBottom);
				painter->GtDrawBevelFrameRaised(m_rectBottom,2);

				painter->Set_objPen(GtPen(GtColor(50,50,50)));
				painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
				painter->GtDrawTriangleUp(m_rectTop,5);
				painter->GtDrawTriangleDown(m_rectBottom,5);

				//Draw Marker
				
				GtLineI bar;
				float percent = ((float)m_intValue) / ((float)(m_intMax - m_intMin));
				m_currPos.x = m_rectBar.xMin;
				m_currPos.y = m_rectBar.yMin + gRound(percent * (m_rectBar.yMax - m_rectBar.yMin));
				bar.m_P0.x = m_rectBar.xMin;
				bar.m_P0.y = m_currPos.y;
				bar.m_P1.x = m_rectBar.xMin + 25;
				bar.m_P1.y = m_currPos.y;

				painter->Set_objPen(GtPen(GtColor(0,0,0),SolidLine,4.0));
				painter->GtDrawLine(bar);

			}//end if render compact

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);

			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT