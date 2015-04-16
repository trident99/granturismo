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

#ifndef GT_TAB_BAR_H
#define GT_TAB_BAR_H

#include ".\GtFrame.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{
		//forward declaration of tab page
		class GtTabPage;

		class HTL_DLLAPI GtTabBar : public GtFrame
		{
		public:
			//!Parent set constructor
			GtTabBar(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtTabBar(void);

			//MEMBER VARIABLES////////////////////////
			//!The frame style for the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intTabWidth);

			int GetSelTab(void){return m_intSelTab;};
			void SetSelTab(int index);

			//SIGNALS/////////////////////////////////
			HtlSignal00 TabChanged;
		public:
			//MEMBER FUNCTIONS////////////////////////
			//!Get the pointer to the tab page
			GtTabPage* AtTabPage(int index);
			//!Get the pointer to the tab page
			GtTabPage* AtTabPage(std::string strName);

			//!Get the pointer to the tab page
			GtTabPage* GetSelTabPage(void);
			//!Add a tab page
			void AddTabPage(GtTabPage* ptrPage);
			//!Remove a tab page
			void RemoveTabPage(int index);
			//!Remove All tab pages
			void RemoveAllTabPages(void);
			//!Get the rect of the actual tab at page
			GtRectI AtTabPageRect(int index);

			void IncrementTabVisible(void);
			void DecrementTabVisible(void);

		public:
			//!Tests and sets the focus widget based on the cursor location provided
			virtual GtWidget* SetFocusWidget(GtPoint3DI & pos);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:
			//!The integer selected tab
			int m_intSelTab;
			//!The integer selected tab
			int m_intFirstVisible;
			//!rect for the increment tab button
			GtRectI m_rectTabIncr;
			//!rect for the decrement tab button
			GtRectI m_rectTabDecr;
			//!rect for the tabs rect bar
			GtRectI m_rectTabBar;
			//!The collection of tab pages
			Htl1DList<GtTabPage*, HTL_BASE_PTR> m_arrPages;
			//!The collection of tab pages
			Htl1DList<GtRectI, HTL_BASE> m_arrTabRects;
			//!Update the tab geometry based on which index is visible first
			void UpdateGeometry(void);


		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H