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

#ifndef GT_GRID_VIEW_H
#define GT_GRID_VIEW_H

#include "..\GtBasicControls\GtScrollArea.h"
#include "..\GtBasicControls\GtHorizScrollBar.h"
#include "..\GtBasicControls\GtVertScrollBar.h"

#include ".\GtGridSelection.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{
		class GtGridRow;
		class GtGridColumn;
		class GtGridCell;

		typedef HtlTreeNode<Htl2DIndex,GtGridCell*>* CellNodeIter;
		typedef HtlTreeNode<Htl1DIndex,GtGridRow*>* CellRowIter;
		typedef HtlTreeNode<Htl1DIndex,GtGridColumn*>* CellColIter;

		class HTL_DLLAPI GtGridView : public GtFrame
		{
		public:
			//!Parent set constructor
			GtGridView(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtGridView(void);

			//MEMBER VARIABLES////////////////////////
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, int, intNumFixedRows);
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, int, intNumFixedCols);
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, int, intDefCellWidth);
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, int, intDefCellHeight);
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnEditable);
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnFixedRowSel);
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnFixedColSel);

			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, GtScrollBarPolicy, horizScrollPolicy);
			//!The vertical scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, GtScrollBarPolicy, vertScrollPolicy);
			//!The maximum size of the viewport
			GTOBJECT_MEMVAR_BYREF(public, GtSizeI, viewMaxSize);
			//SIGNALS/////////////////////////////////
		public:
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


			//ROWS AND COLUMNS METHODS//////////////////////////
			long CountCells(void){return m_mapCells.size();};
			long CountRows(void){ return m_lngRowCount;};
			long CountColumns(void){return m_lngColCount;};
			//!Resize the grid
			int  Resize(long rows, long cols);
			//!Insert a Column before index nColBefore
			int  InsertColumn(std::wstring & strHeading,
				UINT nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE,
				long nColBefore = -1);
			//!Insert Row before index nRowBefore
			int  InsertRow(std::wstring &  strHeading, long nRowBefore = -1);
			//!Delete column at index
			int DeleteColumn(long nColumn);
			//!Delete row at index
			int DeleteRow(long nRow);
			//!Delete ALL grid cells
			int DeleteAllItems();
			//!Get the pointer to the row at the index
			GtGridRow* GetRowPtr(long row);
			//!Get the pointer to the column at the index
			GtGridColumn* GetColumnPtr(long col);
			//!Get Set the row height
			int GetRowHeight(long row);
			int SetRowHeight(long row, int height);
			//!Get Set the column width
			int GetColumnWidth(long col);
			int SetColumnWidth(long col, int width);

			//CELL MEMBER FUNCTIONS////////////////////////////
			//!Get the pointer to the cell at index in the map
			GtGridCell* AtCellPtr(long index);
			//!Get the pointer to the cell at location
			GtGridCell* GetCellPtr(long row, long col);
			//!Get the cell origin top left point. non-visible cells will have a zeroed point
			GtPoint3DI GetCellOrigin(long row, long col);
			//!Get the cell rect. non-visible cells will have zeroed rect
			GtRectI GetCellRect(int row, int col);
			//!Get the cell from the mouse point
			GtGridCell* GetCellFromPt(GtPoint3DI pos);
			//!Set the Cells in the selection to default width
			int SetCellsToDefWidth(GtGridSelection & arrSel);
			//!Set the Cells in the selection to default height
			int SetCellsToDefHeight(GtGridSelection & arrSel);

			//CELL VALUE MEMBER FUNCTIONS///////////////////////
			//!Get and Set Cell Text
			std::string GetText(long row,long col);
			void SetText(long row,long col, std::string strVal);
			//!Get and Set Cell double value
			double GetDblValue(long row, long col);
			void SetDblValue(long row, long col, double dblVal);
			//!Get and Set Cell integer value
			long GetIntValue(long row, long col);
			void SetIntValue(long row, long col, long intVal);

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
			//!The Cell Colection
			HtlListMap<Htl2DIndex,HTL_BASE,GtGridCell*,HTL_BASE_PTR> m_mapCells;
			//!The Row Colection
			HtlListMap<Htl1DIndex,HTL_BASE,GtGridRow*,HTL_BASE_PTR> m_mapRows;
			//!The Column Colection
			HtlListMap<Htl1DIndex,HTL_BASE,GtGridColumn*,HTL_BASE_PTR> m_mapColumns;

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
			//!The position of the target top left point that is visible
			GtPoint3DI m_objTargetPos;
			//!Update the row and column counts based on the cell grid
			void UpdateRowColCount(void);
			//update the scroll window geometry
			void UpdateScrollGeometry(void);
			//update the current grid cell locations
			void UpdateGridCellGeometry(void);

		};//end GtGridView class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_SCROLL_AREA_H
