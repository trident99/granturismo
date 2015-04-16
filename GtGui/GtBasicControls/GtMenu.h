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

#ifndef GT_MENU_H
#define GT_MENU_H

#include ".\GtAction.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtMenu : public GtAction
		{
		public:
			//!Parent set constructor
			GtMenu(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtMenu(void);

			//MEMBER VARIABLES////////////////////////
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intWidth);
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowMenu);

			//SIGNALS/////////////////////////////////
		public:
			//No additional signals 
			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Add an action to the menu
			void AddAction(GtAction* ptrNewAction);
			//!Add an action to the menu with the string name
			void AddAction(std::string strName);
			//!Add a sub menu 
			void AddMenu(GtMenu* ptrNewMenu);
			//!Add the sub menu with the string name
			void AddMenu(std::string strName);
			//!Add a Separator
			void AddSeparator(void);
			//!Clear the menu sub items
			void Clear(void);
			//!Checks to see if the supplied action is a child of this menu
			bool IsChildAction(GtAction* ptrTest);

			GtMenu* GetRootMenu(void);

		public:
			//!Clear the focus
			virtual void ClearFocus(GtWidget* ptrNewFocus);
			//!Close the widget
			virtual void Close();
			//!Tests and sets the focus widget based on the cursor location provided
			virtual GtWidget* SetFocusWidget(GtPoint3DI & pos);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);

		protected:

			GtAction* m_ptrSelAction;

			//!The menu sub actions and sub menus
			Htl1DList<GtAction*,HTL_BASE_PTR> m_arrSubItems;

			void UpdateMenuVisible(bool blnVisible);

			bool IsRootMenu(void);

			GtRectI m_rectShadow;

		};//end GtAction class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_MENU_H