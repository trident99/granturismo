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

#include ".\GtSpinBox.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtSpinBox::GtSpinBox(GtObject* ptrParent)
			:GtFrame(ptrParent)
		{
			m_intMin = 0;
			m_intMax = 100;
			m_intValue = 0;
			m_intDelta = 1;
		};

		//!Virtual destructor
		GtSpinBox::~GtSpinBox(void)
		{
			m_intValue = 0;
		};
		
		//!Set the minimum range value
		void GtSpinBox::Set_intMin(int min)
		{
			m_intMin = min;
			this->RangeChanged.Emit(m_intMin,m_intMax);
		};
		
		//!Set the maximum range value
		void GtSpinBox::Set_intMax(int max)
		{
			m_intMax = max;
			this->RangeChanged.Emit(m_intMin,m_intMax);			
		};
		
		//!Set the slider position value
		void GtSpinBox::Set_intValue(int val)
		{
			m_intValue = val;
			this->ValueChanged.Emit(val);			
		};

		//!Boolean check to see if slider at maximum
		bool GtSpinBox::IsAtMinimum(void)
		{
			return (m_intValue <= m_intMin);
		};
		//!Boolean check to see if slider at minimum
		bool GtSpinBox::IsAtMaximum(void)
		{
			return (m_intValue >= m_intMax);
		};
		//!Set the minimum and maximum range settings
		void GtSpinBox::SetRange(int min, int max)
		{
			m_intMin = min;
			m_intMax = max;
			this->RangeChanged.Emit(m_intMin,m_intMax);
		};
		//!Increment the position by delta
		void GtSpinBox::Increment(int idelta)
		{
			m_intValue += idelta;
			if(m_intValue > m_intMax){m_intValue = m_intMax;};//safety bound check
			this->ValueChanged.Emit(m_intValue);	
		};
		//!Decrement the position by delta
		void GtSpinBox::Decrement(int idelta)
		{
			m_intValue -= idelta;
			if(m_intValue < m_intMin){m_intValue = m_intMin;};//safety bound check
			this->ValueChanged.Emit(m_intValue);	
		};


		//!Custom Event Processing
		int GtSpinBox::HandleEvent(GtEvent * ptrEvent)
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
				if( m_rectValueIncr.Contains(pos))
				{
					this->Increment(1);
					ValueChanged.Emit(m_intValue);
					this->PostPaint();
					return 1;
				};
				if( m_rectValueDecr.Contains(pos))
				{
					this->Decrement(1);
					ValueChanged.Emit(m_intValue);
					this->PostPaint(); 
					return 1;
				};
				
			}
			return 0;
		};
		//!Custom Widget Painting
		int GtSpinBox::OnPaint(GtPainter * painter)
		{
			//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen oldPen;
			GtBrush oldBrush;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);

			//Value Rectangles
			m_rectValue = m_objFrame;
			m_rectValue.xMax = m_rectValue.xMin + 150;
			m_rectValue.yMax = m_rectValue.yMin + 25;

			m_rectValueIncr.xMin = m_rectValue.xMax;
			m_rectValueIncr.xMax = m_rectValueIncr.xMin + 25;
			m_rectValueIncr.yMin = m_rectValue.yMin;
			m_rectValueIncr.yMax = m_rectValueIncr.yMin + 15;

			m_rectValueDecr.xMin = m_rectValue.xMax;
			m_rectValueDecr.xMax = m_rectValueIncr.xMin + 25;
			m_rectValueDecr.yMin = m_rectValueIncr.yMax;
			m_rectValueDecr.yMax = m_rectValueDecr.yMin + 15;
			m_objFrame.xMax = m_rectValueIncr.yMax;

			painter->GtDrawRect(m_rectValue);

			painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
			painter->GtDrawRect(m_rectValueIncr);
			painter->GtDrawRect(m_rectValueDecr);

			painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
			painter->GtDrawTriangleUp(m_rectValueIncr,5);
			painter->GtDrawTriangleDown(m_rectValueDecr,5);

			GtPoint3DI textPos;
			char buf[16];
			std::string strTemp;
			sprintf(buf, "%d", m_intValue);
			strTemp = buf;
			textPos.x = m_rectValue.xMin + 5;
			textPos.y = m_rectValue.yMin + 2;
			painter->GtDrawStaticText(strTemp,textPos);

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT