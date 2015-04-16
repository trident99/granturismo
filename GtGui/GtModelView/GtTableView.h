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

#ifndef GT_TABLE_VIEW_H
#define GT_TABLE_VIEW_H

#include <modGtItemModel.h>

#include "..\GtBasicControls\GtScrollArea.h"
#include "..\GtBasicControls\GtHorizScrollBar.h"
#include "..\GtBasicControls\GtVertScrollBar.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{
		class GtTableRow;
		class GtTableColumn;

		typedef HtlTreeNode<GtTableModelIndex,void*>* CellNodeIter;
		typedef HtlTreeNode<Htl1DIndex,GtTableRow*>* CellRowIter;
		typedef HtlTreeNode<Htl1DIndex,GtTableColumn*>* CellColIter;

		class HTL_DLLAPI GtTableView : public GtFrame
		{
		public:
			//!Parent set constructor
			GtTableView(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtTableView(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The rectangle geometry for the widget
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objSelColor);
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, GtScrollBarPolicy, horizScrollPolicy);
			//!The vertical scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, GtScrollBarPolicy, vertScrollPolicy);
			//!The maximum size of the viewport
			GTOBJECT_MEMVAR_BYREF(public, GtSizeI, viewMaxSize);
			//SIGNALS/////////////////////////////////
		public:
			HtlSignal00 SelectionChanged;
			//!Signal for Action object changed
			HtlSignal00 HorizChanged;//value
			//!Signal for Action object changed
			HtlSignal00 VertChanged;//value
			//!Signal for indicating a scroll change
			HtlSignal02<int,int>  ScrollChanged;//dx, dy
			//!Signal for indicating a range change
			HtlSignal02<int,int>  RangeVertChanged;//min, max
			//!Signal for indicating a range change
			HtlSignal02<int,int>  RangeHorizChanged;//min, max
			//MEMBER FUNCTIONS////////////////////////
		public:

			//Set the Table model being viewed
			void SetTableModel(GtTableItemModel * ptrModel);
			//Get the pointer to the Table model being viewed
			GtTableItemModel * GetTableModelPtr(void);
			//!Force a model reset
			void Reset(void);
			//!Get the pointer to the selection model
			GtTableSelection* GetSelection(void);

			//ROWS AND COLUMNS METHODS//////////////////////////
			long CountCells(void){return 0;};
			long CountRows(void){ return m_lngRowCount;};
			long CountColumns(void){return m_lngColCount;};

			//!Get the pointer to the row at the index
			GtTableRow* GetRowPtr(long row);
			//!Get the pointer to the column at the index
			GtTableColumn* GetColumnPtr(long col);
			//!Get Set the row height
			int GetRowHeight(long row);
			int SetRowHeight(long row, int height);
			//!Get Set the column width
			int GetColumnWidth(long col);
			int SetColumnWidth(long col, int width);

			//CELL MEMBER FUNCTIONS////////////////////////////
			//!Get the pointer to the cell at location
			GtTableModelIndex* GetCellPtr(size_t index);
			//!Get the pointer to the cell at location
			GtTableModelIndex* GetCellPtr(long row, long col);
			//!Get the cell origin top left point. non-visible cells will have a zeroed point
			GtPoint3DI GetCellOrigin(long row, long col);
			//!Get the cell rect. non-visible cells will have zeroed rect
			GtRectI GetCellRect(int row, int col);
			//!Get the cell from the mouse point
			GtTableModelIndex* GetCellFromPt(GtPoint3DI pos);

			//SCROLLING MEMBER FUNCTIONS/////////////////////////
			//Get the pointer to the Horizontal scroll bar
			GtHorizScrollBar * GetHorizScrollBar(void);
			//Get the pointer to the Vertical scroll bar
			GtVertScrollBar * GetVertScrollBar(void);
			//!Scroll Horizontal only
			void ScrollHorizontal(int dx);
			//!Scroll Vertical only
			void ScrollVertical(int dy);
			//!Scroll vertical and horizontal;
			void Scroll(int dx, int dy);
			//!GetRanges
			int GetScrollHorizMin(void){return m_objHorizScroll.Get_intMin();};
			int GetScrollHorizMax(void){return m_objHorizScroll.Get_intMax();};
			int GetScrollVertMin(void){return m_objVertScroll.Get_intMin();};
			int GetScrollVertMax(void){return m_objVertScroll.Get_intMax();};

		public:
			
			//!Tests and sets the focus widget based on the cursor location provided
			virtual GtWidget* SetFocusWidget(GtPoint3DI & pos);
			//!Set the object frame and update all control geometries
			virtual void Set_objFrame(GtRectI & frame);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:

			//!boolean flag for mouse down
			bool m_blnMouseDown;
			//!boolean flage for shift key pressed
			bool m_blnShiftDown;
			//pointer to the Table model being viewed
			GtTableItemModel * m_ptrModel;
			//The built in selection model
			GtTableSelection m_objSelection;

			//!The Row Colection
			HtlListMap<Htl1DIndex,HTL_BASE,GtTableRow*,HTL_BASE_PTR> m_mapRows;
			//!The Column Colection
			HtlListMap<Htl1DIndex,HTL_BASE,GtTableColumn*,HTL_BASE_PTR> m_mapColumns;

			//!The Horizontal Scroll Bar
			GtHorizScrollBar m_objHorizScroll;
			//!The Vertical Scroll Bar
			GtVertScrollBar m_objVertScroll;
			//!Number of Rows and Columns
			long m_lngRowCount;
			long m_lngColCount;

			//!The current starting index for visible cells
			long m_lngVisibleRowStart;
			long m_lngVisibleRowEnd;
			long m_lngVisibleColStart;
			long m_lngVisibleColEnd;

			//!Update the row and column counts based on the cell Table
			void UpdateRowColCount(void);
			//update the scroll window geometry
			void UpdateScrollGeometry(void);
			//update the current Table cell locations
			void UpdateTableGeometry(void);

		};//end GtTableView class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_SCROLL_AREA_H
