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

#include ".\GtDateEdit.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtDateEdit::GtDateEdit(GtObject* ptrParent)
			: GtFrame(ptrParent)
		{
			m_strType = "GtDateEdit";
			m_intMonth = 0;
			m_intDay = 0;
			m_intYear = 0;
		};
		//virtual destructor
		GtDateEdit::~GtDateEdit(void)
		{
			m_intMonth = 0;
			m_intDay = 0;
			m_intYear = 0;
		};
		//!Month Accessors

		void GtDateEdit::Set_intMonth(int month)
		{
			if((month > 0) && (month <= 12))
			{
				m_intMonth = month;
				Changed.Emit();
			}
		};
		void GtDateEdit::IncrementMonth(void)
		{
			int temp = m_intMonth;
			if(temp++ < 12)
			{
				m_intMonth++;
				Changed.Emit();
			}
		};
		void GtDateEdit::DecrementMonth(void)
		{
			int temp = m_intMonth;
			if(temp-- > 0)
			{
				m_intMonth--;
				Changed.Emit();
			}
		};
		//!Day Accessors

		void GtDateEdit::Set_intDay(int day)
		{
			if((day > 0) && (day <= 31))
			{
				m_intDay = day;
				Changed.Emit();
			}
		};
		void GtDateEdit::IncrementDay(void)
		{
			int temp = m_intDay;
			if(temp++ < 31)
			{
				m_intDay++;
				Changed.Emit();
			}
		};
		void GtDateEdit::DecrementDay(void)
		{
			int temp = m_intDay;
			if(temp-- > 0)
			{
				m_intDay--;
				Changed.Emit();
			}
		};
		//!Year Accessors
		void GtDateEdit::Set_intYear(int year)
		{
			m_intYear = year;
			Changed.Emit();
		};
		void GtDateEdit::IncrementYear(void)
		{
			m_intYear++;
			Changed.Emit();
		};
		void GtDateEdit::DecrementYear(void)
		{
			m_intYear--;
			Changed.Emit();
		};
		//Pretty Print Day / Month / Year
		std::string GtDateEdit::ToStringDMY(void)
		{
			std::string strDate;
			char chrBuf[64];
			sprintf(chrBuf, "%d / %d / %d",m_intDay,m_intMonth,m_intYear);
			strDate = chrBuf;
			return strDate;
		};
		//Pretty Print Month / Day / Year
		std::string GtDateEdit::ToStringMDY(void)
		{
			std::string strDate;
			char chrBuf[64];
			sprintf(chrBuf, "%d / %d / %d",m_intMonth,m_intDay,m_intYear);
			strDate = chrBuf;
			return strDate;
		};

		//!Custom Event Processing
		int GtDateEdit::HandleEvent(GtEvent * ptrEvent)
		{

			//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				GtPoint3DI pos;
				pos.x = gRound(ptrEvent->m_objPos.x);
				pos.y = gRound(ptrEvent->m_objPos.y);
				//drawing rectangles
				//GtRectI m_rectDay;
				if( m_rectDayIncr.Contains(pos)){this->IncrementDay();this->PostPaint(); return 1;};
				if( m_rectDayDecr.Contains(pos)){this->DecrementDay();this->PostPaint(); return 1;};
				//drawing rectangles
				//GtRectI m_rectMonth;
				if( m_rectMonthIncr.Contains(pos)){this->IncrementMonth();this->PostPaint(); return 1;};
				if( m_rectMonthDecr.Contains(pos)){this->DecrementMonth();this->PostPaint(); return 1;};
				//drawing rectangles
				//GtRectI m_rectYear;
				if( m_rectYearIncr.Contains(pos)){this->IncrementYear();this->PostPaint(); return 1;};
				if( m_rectYearDecr.Contains(pos)){this->DecrementYear();this->PostPaint(); return 1;};
			}
			return 0;
		};

		//!Custom Widget Painting
		int GtDateEdit::OnPaint(GtPainter * painter)
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

			//Month Rectangles
			m_rectMonth = m_objFrame;
			m_rectMonth.xMax = m_rectMonth.xMin + 50;
			m_rectMonth.yMax = m_rectMonth.yMin + 25;

			m_rectMonthIncr.xMin = m_rectMonth.xMax;
			m_rectMonthIncr.xMax = m_rectMonthIncr.xMin + 25;
			m_rectMonthIncr.yMin = m_rectMonth.yMin;
			m_rectMonthIncr.yMax = m_rectMonthIncr.yMin + 15;

			m_rectMonthDecr.xMin = m_rectMonth.xMax;
			m_rectMonthDecr.xMax = m_rectMonthIncr.xMin + 25;
			m_rectMonthDecr.yMin = m_rectMonthIncr.yMax;
			m_rectMonthDecr.yMax = m_rectMonthDecr.yMin + 15;

			//Day Rectangles
			m_rectDay = m_objFrame;
			m_rectDay.xMin = m_rectMonthIncr.xMax;
			m_rectDay.xMax = m_rectDay.xMin + 50;
			m_rectDay.yMax = m_rectDay.yMin + 25;		
			
			m_rectDayIncr.xMin = m_rectDay.xMax;
			m_rectDayIncr.xMax = m_rectDayIncr.xMin + 25;
			m_rectDayIncr.yMin = m_rectDay.yMin;
			m_rectDayIncr.yMax = m_rectDayIncr.yMin + 15;

			m_rectDayDecr.xMin = m_rectDay.xMax;
			m_rectDayDecr.xMax = m_rectDayIncr.xMin + 25;
			m_rectDayDecr.yMin = m_rectDayIncr.yMax;
			m_rectDayDecr.yMax = m_rectDayDecr.yMin + 15;
			
			//Year Rectangles
			m_rectYear = m_objFrame;
			m_rectYear.xMin = m_rectDayIncr.xMax;
			m_rectYear.xMax = m_rectYear.xMin + 100;
			m_rectYear.yMax = m_rectYear.yMin + 25;		
			
			m_rectYearIncr.xMin = m_rectYear.xMax;
			m_rectYearIncr.xMax = m_rectYearIncr.xMin + 25;
			m_rectYearIncr.yMin = m_rectYear.yMin;
			m_rectYearIncr.yMax = m_rectYearIncr.yMin + 15;

			m_rectYearDecr.xMin = m_rectYear.xMax;
			m_rectYearDecr.xMax = m_rectYearIncr.xMin + 25;
			m_rectYearDecr.yMin = m_rectYearIncr.yMax;
			m_rectYearDecr.yMax = m_rectYearDecr.yMin + 15;
			m_objFrame.xMax = m_rectYearDecr.xMax;

			painter->GtDrawRect(m_rectDay);
			painter->GtDrawRect(m_rectMonth);
			painter->GtDrawRect(m_rectYear);

			painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
			painter->GtDrawRect(m_rectDayIncr);
			painter->GtDrawRect(m_rectDayDecr);
			painter->GtDrawRect(m_rectMonthIncr);
			painter->GtDrawRect(m_rectMonthDecr);
			painter->GtDrawRect(m_rectYearIncr);
			painter->GtDrawRect(m_rectYearDecr);

			painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
			painter->GtDrawTriangleUp(m_rectDayIncr,5);
			painter->GtDrawTriangleDown(m_rectDayDecr,5);
			painter->GtDrawTriangleUp(m_rectMonthIncr,5);
			painter->GtDrawTriangleDown(m_rectMonthDecr,5);
			painter->GtDrawTriangleUp(m_rectYearIncr,5);
			painter->GtDrawTriangleDown(m_rectYearDecr,5);

			GtPoint3DI textPos;
			char buf[8];
			std::string strTemp;
			sprintf(buf, "%02d", m_intDay);
			strTemp = buf;
			textPos.x = m_rectDay.xMin + 5;
			textPos.y = m_rectDay.yMin + 2;
			painter->GtDrawStaticText(strTemp,textPos);

			sprintf(buf, "%02d", m_intMonth);
			strTemp = buf;
			textPos.x = m_rectMonth.xMin + 5;
			textPos.y = m_rectMonth.yMin + 2;
			painter->GtDrawStaticText(strTemp,textPos);

			sprintf(buf, "%04d", m_intYear);
			strTemp = buf;
			textPos.x = m_rectYear.xMin + 5;
			textPos.y = m_rectYear.yMin + 2;
			painter->GtDrawStaticText(strTemp,textPos);
			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);

			return 1;
		};		

	};//end namespace GtCore

};//end namespace GT