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

#ifndef GT_ACTION_H
#define GT_ACTION_H

#include "..\GtGuiLibRefs.h"
#include ".\GtControlEnums.h"
#include <modGtGraphic.h>
#include <modGtGeometry.h>

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{
		//Forward declaration of GtMenu
		class GtMenu;

		class HTL_DLLAPI GtAction : public GtWidget
		{
		public:
			//!Parent set constructor
			GtAction(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtAction(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnHovered);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnCheckable);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnChecked);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnSeparator);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnIcon);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, GtPixmap, objIcon);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, GtKey, objKey);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intModifiers);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, std::string, strTipText);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnEnabled);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, GtVariant, varData);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, void*, ptrData);
			//SIGNALS/////////////////////////////////
		public:			
			//!Signal for action being selected and triggered
			HtlSignal00 Triggered;
			//!Signal for Action object changed
			HtlSignal00 Changed;
			//!Signal for mouse hovering over action
			HtlSignal00	Hovered;
			//!Signal for action being toggled between checked and unchecked state
			HtlSignal01<bool> Toggled;


			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Menu Parent Object using a dynamic cast
			GtMenu * MenuParent(void);
			//!Conveinience slot for causing a Hovered signal emit
			void Hover(void);
			//!Conveinience slot for causing a Toggled signal emit
			void Toggle(void);
			//!Conveinience slot for causing a Triggered signal emit
			void Trigger(void);

			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:
			GtRectI m_rectCheck;

		};//end GtAction class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_ACTION_H