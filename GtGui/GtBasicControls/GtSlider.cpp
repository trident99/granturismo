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

#include ".\GtSlider.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtSlider::GtSlider(GtObject* ptrParent)
			:GtWidget(ptrParent)
		{
			m_intMin = 0;
			m_intMax = 100;
			m_intValue = 0;
			m_blnSliderGrab = false;
		};

		//!Virtual destructor
		GtSlider::~GtSlider(void)
		{
			m_intValue = 0;
		};
		
		//!Set the minimum range value
		void GtSlider::Set_intMin(int min)
		{
			m_intMin = min;
			this->RangeChanged.Emit(m_intMin,m_intMax);
		};
		
		//!Set the maximum range value
		void GtSlider::Set_intMax(int max)
		{
			m_intMax = max;
			this->RangeChanged.Emit(m_intMin,m_intMax);			
		};
		
		//!Set the slider position value
		void GtSlider::Set_intValue(int val)
		{
			m_intValue = val;
			this->ValueChanged.Emit(val);			
		};

		//!Boolean check to see if slider at maximum
		bool GtSlider::IsAtMinimum(void)
		{
			return (m_intValue <= m_intMin);
		};
		//!Boolean check to see if slider at minimum
		bool GtSlider::IsAtMaximum(void)
		{
			return (m_intValue >= m_intMax);
		};
		//!Set the minimum and maximum range settings
		void GtSlider::SetRange(int min, int max)
		{
			m_intMin = min;
			m_intMax = max;
			this->RangeChanged.Emit(m_intMin,m_intMax);
		};
		//!Increment the position by delta
		void GtSlider::Increment(int idelta)
		{
			m_intValue += idelta;
			if(m_intValue > m_intMax){m_intValue = m_intMax;};//safety bound check
			this->ValueChanged.Emit(m_intValue);	
		};
		//!Decrement the position by delta
		void GtSlider::Decrement(int idelta)
		{
			m_intValue -= idelta;
			if(m_intValue < m_intMin){m_intValue = m_intMin;};//safety bound check
			this->ValueChanged.Emit(m_intValue);	
		};


		//!Custom Event Processing
		int GtSlider::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};
				GtPoint3DI pos, hoverPos, delta;
				pos.x = gRound(ptrEvent->m_objPos.x);
				pos.y = gRound(ptrEvent->m_objPos.y);

				delta = this->RequestOffset();

				hoverPos.x = pos.x - delta.x;
				hoverPos.y = pos.y - delta.y;

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				if(m_rectSlider.Contains(hoverPos))
				{
					m_blnSliderGrab = true;
				}
				return 1;
			}
			if(ptrEvent->m_objType == MouseLeftRelease)
			{

				m_blnSliderGrab = false;
				return 1;
			}
			if(ptrEvent->m_objType == MouseMove)
			{
				if(m_blnSliderGrab)
				{
					//calculate new slider position
					float percent = (float(hoverPos.x - m_objFrame.xMin)) / (float(m_objFrame.xMax - m_objFrame.xMin));
					int newVal = m_intMin + gRound(percent * float(m_intMax - m_intMin));
					//check bounds
					if(newVal < m_intMin){newVal = m_intMin;};
					if(newVal > m_intMax){newVal = m_intMax;};
					//set the new value
					this->Set_intValue(newVal);

					this->PostPaint();
					return 1;
				}
				return 1;
			}
			return 0;

		};
		//!Custom Widget Painting
		int GtSlider::OnPaint(GtPainter * painter)
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

			//render normal
			//render compact mode
			//draw buttons
			painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
			m_objFrame = m_objFrame;
			m_objFrame.yMax = m_objFrame.yMin + 25;			
			painter->GtDrawRect(m_objFrame);
			
			GtLineI bar;
			float percent = ((float)m_intValue) / ((float)(m_intMax - m_intMin));
			m_sliderPos.x = m_objFrame.xMin + gRound(percent * (m_objFrame.xMax - m_objFrame.xMin));
			m_sliderPos.y = m_objFrame.yMin;

			m_rectSlider = m_objFrame;
			m_rectSlider.xMin = m_sliderPos.x - 5; 
			m_rectSlider.xMax = m_sliderPos.x + 5; 
			m_rectSlider.yMax = m_rectSlider.yMin + 25;
			painter->Set_objBrush(GtBrush(GtColor(0,0,255)));
			painter->GtDrawRect(m_rectSlider);
			//Draw Marker

			bar.m_P0.x = m_sliderPos.x ;
			bar.m_P0.y = m_objFrame.yMin;
			bar.m_P1.x = m_sliderPos.x;
			bar.m_P1.y = m_objFrame.yMin + 25;

			painter->Set_objPen(GtPen(GtColor(0,0,0),SolidLine,4.0));
			painter->GtDrawLine(bar);


			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);

			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT