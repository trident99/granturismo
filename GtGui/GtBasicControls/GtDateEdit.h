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

#ifndef GT_DATE_EDIT_H
#define GT_DATE_EDIT_H

#include ".\GtFrame.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtDateEdit : public GtFrame
		{
		public:
			//!Parent set constructor
			GtDateEdit(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtDateEdit(void);
			//!Month Accessors
			int Get_intMonth(void){return m_intMonth;};
			void Set_intMonth(int month);
			void IncrementMonth(void);
			void DecrementMonth(void);
			//!Day Accessors
			int Get_intDay(void){return m_intDay;};
			void Set_intDay(int day);
			void IncrementDay(void);
			void DecrementDay(void);
			//!Year Accessors
			int Get_intYear(void){return m_intYear;};
			void Set_intYear(int year);
			void IncrementYear(void);
			void DecrementYear(void);
			//Pretty Print Day / Month / Year
			std::string ToStringDMY(void);
			//Pretty Print Month / Day / Year
			std::string ToStringMDY(void);

			//SIGNALS/////////////////////////////////
		public:
			//!Signal for Action object changed
			HtlSignal00 Changed;
			//MEMBER FUNCTIONS////////////////////////
		public:

			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:
			//!Integer Month
			int m_intMonth;
			//!Integer Day
			int m_intDay;
			//!Integer Year
			int m_intYear;
		private:
			//drawing rectangles
			GtRectI m_rectDay;
			GtRectI m_rectDayIncr;
			GtRectI m_rectDayDecr;
			//drawing rectangles
			GtRectI m_rectMonth;
			GtRectI m_rectMonthIncr;
			GtRectI m_rectMonthDecr;
			//drawing rectangles
			GtRectI m_rectYear;
			GtRectI m_rectYearIncr;
			GtRectI m_rectYearDecr;
		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_DATE_EDIT_H