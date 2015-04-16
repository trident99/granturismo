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

#ifndef GT_LIST_VIEW_H
#define GT_LIST_VIEW_H

#include <modGtItemModel.h>

#include "..\GtBasicControls\GtFrame.h"
#include "..\GtBasicControls\GtVertScrollBar.h"
using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtListView : public GtFrame
		{
		public:
			//!Parent set constructor
			GtListView(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtListView(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objSelColor);
			//!Override for setting frame
			virtual void Set_objFrame(GtRectI & frame);
			//SIGNALS/////////////////////////////////
		public:
			//vertical scroll changed
			HtlSignal00 VertChanged;
			//selection of items changed
			HtlSignal00 SelectionChanged;

			//MEMBER FUNCTIONS////////////////////////
		public:	
			//Set the list model being viewed
			void SetListModel(GtListItemModel * ptrModel);
			//Get the pointer to the list model being viewed
			GtListItemModel * GetListModelPtr(void);
			//!Force a model reset
			void Reset(void);
			//!Get the pointer to the selection model
			GtListSelection* GetSelection(void);
			//!Get the model index at point
			GtListModelIndex* GetIndexAtPt ( GtPoint3DI & pt );
			//!Scroll to the desired model index
			void  ScrollTo( GtListModelIndex & index );
			//!Get the rect of the item at index
			GtRectI  GetItemRect( GtListModelIndex & index );

			//SCROLLING MEMBER FUNCTIONS/////////////////////////
			//Get the pointer to the Vertical scroll bar
			GtVertScrollBar * GetVertScrollBar(void);
			//!Scroll Vertical only
			void ScrollVertical(int dy);
			//!GetRanges
			int GetScrollVertMin(void){return m_objVertScroll.Get_intMin();};
			int GetScrollVertMax(void){return m_objVertScroll.Get_intMax();};

			//!Tests and sets the focus widget based on the cursor location provided
			virtual GtWidget* SetFocusWidget(GtPoint3DI & pos);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);	

		protected:

			//!The Vertical Scroll Bar
			GtVertScrollBar m_objVertScroll;
			//!Number of Rows
			long m_lngRowCount;

			//!The current starting index for visible cells
			long m_lngVisibleRowStart;
			long m_lngVisibleRowEnd;

			//!boolean flag for mouse down
			bool m_blnMouseDown;
			//!boolean flage for shift key pressed
			bool m_blnShiftDown;
			//pointer to the list model being viewed
			GtListItemModel * m_ptrModel;
			//The built in selection model
			GtListSelection m_objSelection;

			//update the row count
			void UpdateRowCount(void);
			//update the list geometries
			void UpdateListGeometry(void);
			//update the scroll geometries
			void UpdateScrollGeometry(void);

		};//end GtListView class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H