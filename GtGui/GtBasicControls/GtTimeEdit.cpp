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

#include ".\GtTimeEdit.h"
#include <modGtEvent.h>
#include <modGtMath.h>
namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtTimeEdit::GtTimeEdit(GtObject* ptrParent)
			: GtFrame(ptrParent)
		{
			m_strType = "GtTimeEdit";
			m_intHour = 0;
			m_intMinute = 0;
			m_intSecond = 0;
		};
		//virtual destructor
		GtTimeEdit::~GtTimeEdit(void)
		{
			m_intHour = 0;
			m_intMinute = 0;
			m_intSecond = 0;
		};
		//!Hour Accessors

		void GtTimeEdit::Set_intHour(int hour)
		{
			if((hour >= 0) && (hour < 24))
			{
				m_intHour = hour;
				Changed.Emit();
			}
		};
		void GtTimeEdit::IncrementHour(void)
		{
			int temp = m_intHour;
			if(temp < 23)
			{
				m_intHour++;
				Changed.Emit();
			}else if(temp >= 23){
				//rollover the number to 0
				m_intHour = 0;
				Changed.Emit();
			}

		};
		void GtTimeEdit::DecrementHour(void)
		{
			int temp = m_intHour;
			if(temp > 0)
			{
				m_intHour--;
				Changed.Emit();
			}else if(temp <= 0){
				//roll back to 23
				m_intHour = 23;
				Changed.Emit();
			}
		};
		//!Minute Accessors

		void GtTimeEdit::Set_intMinute(int Minute)
		{
			if((Minute >= 0) && (Minute < 60))
			{
				m_intMinute = Minute;
				Changed.Emit();
			}
		};
		void GtTimeEdit::IncrementMinute(void)
		{
			int temp = m_intMinute;
			if(temp < 59)
			{
				m_intMinute++;
				Changed.Emit();
			}else if(temp >= 59){
				//roll over
				m_intMinute = 0;
				Changed.Emit();
			}
		};
		void GtTimeEdit::DecrementMinute(void)
		{
			int temp = m_intMinute;
			if(temp > 0)
			{
				m_intMinute--;
				Changed.Emit();
			}else if(temp <= 0){
				//roll back
				m_intMinute = 59;
				Changed.Emit();
			}
		};
		//!Second Accessors
		void GtTimeEdit::Set_intSecond(int second)
		{
			if((second >= 0) && (second < 60))
			{
				m_intSecond = second;
				Changed.Emit();
			}
		};
		void GtTimeEdit::IncrementSecond(void)
		{
			int temp = m_intSecond;
			if(temp < 59)
			{
				m_intSecond++;
				Changed.Emit();
			}else if(temp >= 59){
				//roll over
				m_intSecond = 0;
				Changed.Emit();
			}
		};
		void GtTimeEdit::DecrementSecond(void)
		{
			int temp = m_intSecond;
			if(temp > 0)
			{
				m_intSecond--;
				Changed.Emit();
			}else if(temp <= 0){
				//roll back
				m_intSecond = 59;
				Changed.Emit();
			}
		};

		//Pretty Print total decimal hours
		double GtTimeEdit::ToHours(void)
		{
			return 0;
		};

		//Pretty Print total decimal minutes
		double GtTimeEdit::ToMinutes(void)
		{
			return 0;
		};

		//Pretty Print total seconds
		double GtTimeEdit::ToSeconds(void)
		{
			return 0;
		};


		//!Custom Event Processing
		int GtTimeEdit::HandleEvent(GtEvent * ptrEvent)
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
				if( m_rectHourIncr.Contains(pos)){this->IncrementHour();this->PostPaint(); return 1;};
				if( m_rectHourDecr.Contains(pos)){this->DecrementHour();this->PostPaint(); return 1;};
				//drawing rectangles
				//GtRectI m_rectMinute;
				if( m_rectMinuteIncr.Contains(pos)){this->IncrementMinute();this->PostPaint(); return 1;};
				if( m_rectMinuteDecr.Contains(pos)){this->DecrementMinute();this->PostPaint(); return 1;};
				//drawing rectangles
				//GtRectI m_rectSecond;
				if( m_rectSecondIncr.Contains(pos)){this->IncrementSecond();this->PostPaint(); return 1;};
				if( m_rectSecondDecr.Contains(pos)){this->DecrementSecond();this->PostPaint(); return 1;};
			}
			return 0;
		};

		//!Custom Widget Painting
		int GtTimeEdit::OnPaint(GtPainter * painter)
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

			//Hour Rectangles
			m_rectHour = m_objFrame;
			m_rectHour.xMax = m_rectHour.xMin + 50;
			m_rectHour.yMax = m_rectHour.yMin + 25;

			m_rectHourIncr.xMin = m_rectHour.xMax;
			m_rectHourIncr.xMax = m_rectHourIncr.xMin + 25;
			m_rectHourIncr.yMin = m_rectHour.yMin;
			m_rectHourIncr.yMax = m_rectHourIncr.yMin + 15;

			m_rectHourDecr.xMin = m_rectHour.xMax;
			m_rectHourDecr.xMax = m_rectHourIncr.xMin + 25;
			m_rectHourDecr.yMin = m_rectHourIncr.yMax;
			m_rectHourDecr.yMax = m_rectHourDecr.yMin + 15;

			//Minute Rectangles
			m_rectMinute = m_objFrame;
			m_rectMinute.xMin = m_rectHourIncr.xMax;
			m_rectMinute.xMax = m_rectMinute.xMin + 50;
			m_rectMinute.yMax = m_rectMinute.yMin + 25;		
			
			m_rectMinuteIncr.xMin = m_rectMinute.xMax;
			m_rectMinuteIncr.xMax = m_rectMinuteIncr.xMin + 25;
			m_rectMinuteIncr.yMin = m_rectMinute.yMin;
			m_rectMinuteIncr.yMax = m_rectMinuteIncr.yMin + 15;

			m_rectMinuteDecr.xMin = m_rectMinute.xMax;
			m_rectMinuteDecr.xMax = m_rectMinuteIncr.xMin + 25;
			m_rectMinuteDecr.yMin = m_rectMinuteIncr.yMax;
			m_rectMinuteDecr.yMax = m_rectMinuteDecr.yMin + 15;
			
			//Second Rectangles
			m_rectSecond = m_objFrame;
			m_rectSecond.xMin = m_rectMinuteIncr.xMax;
			m_rectSecond.xMax = m_rectSecond.xMin + 50;
			m_rectSecond.yMax = m_rectSecond.yMin + 25;		
			
			m_rectSecondIncr.xMin = m_rectSecond.xMax;
			m_rectSecondIncr.xMax = m_rectSecondIncr.xMin + 25;
			m_rectSecondIncr.yMin = m_rectSecond.yMin;
			m_rectSecondIncr.yMax = m_rectSecondIncr.yMin + 15;

			m_rectSecondDecr.xMin = m_rectSecond.xMax;
			m_rectSecondDecr.xMax = m_rectSecondIncr.xMin + 25;
			m_rectSecondDecr.yMin = m_rectSecondIncr.yMax;
			m_rectSecondDecr.yMax = m_rectSecondDecr.yMin + 15;
			m_objFrame.xMax = m_rectSecondIncr.xMax;

			painter->GtDrawRect(m_rectHour);
			painter->GtDrawRect(m_rectMinute);
			painter->GtDrawRect(m_rectSecond);

			painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
			painter->GtDrawRect(m_rectHourIncr);
			painter->GtDrawRect(m_rectHourDecr);
			painter->GtDrawRect(m_rectMinuteIncr);
			painter->GtDrawRect(m_rectMinuteDecr);
			painter->GtDrawRect(m_rectSecondIncr);
			painter->GtDrawRect(m_rectSecondDecr);

			painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
			painter->GtDrawTriangleUp(m_rectHourIncr,5);
			painter->GtDrawTriangleDown(m_rectHourDecr,5);
			painter->GtDrawTriangleUp(m_rectMinuteIncr,5);
			painter->GtDrawTriangleDown(m_rectMinuteDecr,5);
			painter->GtDrawTriangleUp(m_rectSecondIncr,5);
			painter->GtDrawTriangleDown(m_rectSecondDecr,5);

			GtPoint3DI textPos;
			char buf[8];
			std::string strTemp;
			sprintf(buf, "%02d", m_intHour);
			strTemp = buf;
			textPos.x = m_rectHour.xMin + 5;
			textPos.y = m_rectHour.yMin + 2;
			painter->GtDrawStaticText(strTemp,textPos);

			sprintf(buf, "%02d", m_intMinute);
			strTemp = buf;
			textPos.x = m_rectMinute.xMin + 5;
			textPos.y = m_rectMinute.yMin + 2;
			painter->GtDrawStaticText(strTemp,textPos);

			sprintf(buf, "%02d", m_intSecond);
			strTemp = buf;
			textPos.x = m_rectSecond.xMin + 5;
			textPos.y = m_rectSecond.yMin + 2;
			painter->GtDrawStaticText(strTemp,textPos);
			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);

			return 1;
		};		

	};//end namespace GtCore

};//end namespace GT