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

#ifndef GT_BUTTON_H
#define GT_BUTTON_H

#include ".\GtFrame.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtButton : public GtFrame
		{
		public:
			//!Parent set constructor
			GtButton(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtButton(void);

			//MEMBER VARIABLES////////////////////////
			//!The boolean flag that indicates if the button is a toggle button type
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnToggle);
			//!The current toggle button state
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnButtonUp);
			//!The button uses an Icon instead of text
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnIcon);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYREF(public, GtPixmap, objIcon);


			//SIGNALS/////////////////////////////////
		public:
			//!Signal for Action object changed
			HtlSignal00 Clicked;
			//!Signal for mouse hovering over action
			HtlSignal00	DoubleClicked;
			//!Signal for mouse hovering over action
			HtlSignal00	Pressed;
			//!Signal for mouse hovering over action
			HtlSignal00	Released;
			//!Signal for action being toggled between checked and unchecked state
			HtlSignal01<bool> Toggled;


			//MEMBER FUNCTIONS////////////////////////
		public:
		
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		};//end GtButton class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_ACTION_H