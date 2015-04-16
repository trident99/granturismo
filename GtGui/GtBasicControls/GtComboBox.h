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

#ifndef GT_COMBOBOX_H
#define GT_COMBOBOX_H

#include ".\GtFrame.h"
#include ".\GtMenu.h"
#include "modHtlContainer.h"
using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		struct HTL_DLLAPI GtComboBoxItem
		{
			GtComboBoxItem()
			{
				m_ptrData = NULL;
			}
		public:
			std::string m_strText;
			//!Variant Data
			GtVariant m_varData;
			//!Pointer to data object
			void* m_ptrData;
		};

		//forward declaration of action
		class GtAction;


		class HTL_DLLAPI GtComboBox : public GtFrame
		{
		public:
			//!Parent set constructor
			GtComboBox(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtComboBox(void);

			//MEMBER VARIABLES////////////////////////
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intWidth);
			//!The maximum number of items in the combobox
			GTOBJECT_MEMVAR_BYVAL(public, int, intMaxCount);
			//!The maximum number of items visible in the combobox
			GTOBJECT_MEMVAR_BYVAL(public, int, intMaxVisible);
			
			//!Accessors for m_intCurrIndex
			int Get_intCurrIndex(void){return m_intCurrIndex;};
			void Set_intCurrIndex(int index);
			
			//SIGNALS/////////////////////////////////
		public:
			//!Signal for Action object changed
			HtlSignal00 Clicked;
			//!Signal for mouse hovering over action
			HtlSignal00	Pressed;
			//!Signal for mouse hovering over action
			HtlSignal00	Released;
			//!Signal for action being toggled between checked and unchecked state
			HtlSignal01<int> SelectionChanged;//index
			//!Signal for indicating an item is selected
			HtlSignal01<int> Highlighted;//index

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Add an item to the combo box
			void AddItem(GtComboBoxItem & item);
			//!Remove an item from the item list
			void DeleteItem(int index);
			//!Clears all items in the list
			void DeleteAllItems(void);
			//!Returns the number of items in the list
			size_t CountItems(void);
			//!Item accessor
			GtComboBoxItem AtItem(int index);
			//!Item accessor get text
			std::string AtText(int index);
			//!Item accessor get data
			GtVariant AtData(int index);
			//!Item accessor get pointer
			void* AtPtrObj(int index);

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
			//!The currently selected index
			int m_intCurrIndex;
			//!The menu sub actions and sub menus
			Htl1DList<GtAction*,HTL_BASE_PTR> m_arrItems;
			//!Syncronizes the popup menu with the item list
			void UpdateMenuVisible(bool blnVisible);
			//!Commits the temporary index to the current index
			void CommitSelection(void);

		private:
			//!Boolean flag for showing menu
			bool m_blnShowMenu;
			//!Rect for combo box
			GtRectI m_rectCombo;
			//!Rect for the text
			GtRectI m_rectText;
			//!shadow rect for pull down menu
			GtRectI m_rectShadow;
			//!the temporary hovered index
			int m_intTempIndex;
		};//end GtButton class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_ACTION_H