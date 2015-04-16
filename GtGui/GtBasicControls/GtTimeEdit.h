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

#ifndef GT_TIME_EDIT_H
#define GT_TIME_EDIT_H

#include ".\GtFrame.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtTimeEdit : public GtFrame
		{
		public:
			//!Parent set constructor
			GtTimeEdit(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtTimeEdit(void);
			//!Month Accessors
			int Get_intHour(void){return m_intHour;};
			void Set_intHour(int hour);
			void IncrementHour(void);
			void DecrementHour(void);
			//!Day Accessors
			int Get_intMinute(void){return m_intMinute;};
			void Set_intMinute(int day);
			void IncrementMinute(void);
			void DecrementMinute(void);
			//!Year Accessors
			int Get_intSecond(void){return m_intSecond;};
			void Set_intSecond(int second);
			void IncrementSecond(void);
			void DecrementSecond(void);
			//Pretty Print total decimal hours
			double ToHours(void);
			//Pretty Print total decimal minutes
			double ToMinutes(void);
			//Pretty Print total seconds
			double ToSeconds(void);

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
			int m_intHour;
			//!Integer Day
			int m_intMinute;
			//!Integer Year
			int m_intSecond;

		private:
			//drawing rectangles
			GtRectI m_rectHour;
			GtRectI m_rectHourIncr;
			GtRectI m_rectHourDecr;
			//drawing rectangles
			GtRectI m_rectMinute;
			GtRectI m_rectMinuteIncr;
			GtRectI m_rectMinuteDecr;
			//drawing rectangles
			GtRectI m_rectSecond;
			GtRectI m_rectSecondIncr;
			GtRectI m_rectSecondDecr;

		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_DATE_EDIT_H