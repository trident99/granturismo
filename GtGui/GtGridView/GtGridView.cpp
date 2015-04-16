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

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtGridView.h"
#include ".\GtGridCell.h"
#include ".\GtGridSelection.h"
#include ".\GtGridRow.h"
#include ".\GtGridColumn.h"

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtGridView::GtGridView(GtObject* ptrParent)
			:GtFrame(ptrParent)

		{
			m_strType = "GtGridView";
			//!The horizontal scroll bar policy
			m_intNumFixedRows = 0;
			//!The horizontal scroll bar policy
			m_intNumFixedCols = 0;
			//!The horizontal scroll bar policy
			m_intDefCellWidth = 50;
			//!The horizontal scroll bar policy
			m_intDefCellHeight = 25;
			//!The horizontal scroll bar policy
			m_blnEditable = true;
			//!The horizontal scroll bar policy
			m_blnFixedRowSel = false;
			//!The horizontal scroll bar policy
			m_blnFixedColSel = false;

			m_lngVisibleRowStart = 0;
			m_lngVisibleRowEnd = 0;
			m_lngVisibleColStart = 0;
			m_lngVisibleColEnd = 0;

			m_objBackBrush = GtBrush(GtColor(160,160,160));

			m_objHorizScroll.Set_ptrParent(this);
			m_objVertScroll.Set_ptrParent(this);

			//hook up the scroll bars to the scrolling slots
			m_objHorizScroll.ValueChanged.SlotConnect(this, &GtGridView::ScrollHorizontal);
			m_objVertScroll.ValueChanged.SlotConnect(this, &GtGridView::ScrollVertical);

		};
		//!Virtual destructor
		GtGridView::~GtGridView(void)
		{
			this->DeleteAllItems();
			m_objHorizScroll.ValueChanged.SlotDisconnect(this);
			m_objVertScroll.ValueChanged.SlotDisconnect(this);
		};


		//!Resize the grid
		int  GtGridView::Resize(long rows, long cols)
		{
			size_t i,j,difRow,difCol;
			this->UpdateRowColCount();
			//ROWS FIRST////////////////
			if(rows > m_lngRowCount)
			{
				// then adding rows
				for(i = m_lngRowCount; i < rows; i++)
				{
					Htl1DIndex rowKey; rowKey.m_lngX = i;
					CellRowIter iterRow = m_mapRows.find(rowKey);
					if(!iterRow)
					{ 
						//then doesnt already exist, create it
						GtGridRow* ptrNewRow = new GtGridRow(this);
						if(ptrNewRow)
						{
							ptrNewRow->Set_lngRow(i);
							m_mapRows.insert(rowKey,ptrNewRow);
						}
					};
					//for each new row
					for(j = 0; j < cols; j++)
					{
						Htl2DIndex key; key.m_lngX = i; key.m_lngY = j;
						
						CellNodeIter iter = m_mapCells.find(key);
						if(!iter)
						{ //then doesnt already exist, create it
							//for all columns
							//make new cell and insert it
							GtGridCell* ptrNew = new GtGridCell(this);
							if(ptrNew)
							{
								ptrNew->Set_lngRow(i);
								ptrNew->Set_lngColumn(j);
								m_mapCells.insert(key,ptrNew);
							}
						}
					}//end j loop
				}//end i loop
			}else if(rows < m_lngRowCount){
				// then deleting rows
				// then adding rows
				for(i = rows; i < m_lngRowCount; i++)
				{
					Htl1DIndex rowKey; rowKey.m_lngX = i;
					CellRowIter iterRow = m_mapRows.find(rowKey);
					if(iterRow)
					{ 
						m_mapRows.erase(rowKey);
					};
					//for each new row
					for(j = 0; j < m_lngColCount; j++)
					{
						Htl2DIndex key; key.m_lngX = i; key.m_lngY = j;
						CellNodeIter iter = m_mapCells.find(key);
						if(iter)
						{ //then doesnt already exist, create it
							m_mapCells.erase(key);
						}
					}//end j loop
				}//end i loop
			}
			//COLUMNS SECOND////////////////
			if(cols > m_lngColCount)
			{
				// then adding rows
				for(j = m_lngColCount; j < cols; j++)
				{
					Htl1DIndex colKey; colKey.m_lngX = j;
					CellColIter iterCol = m_mapColumns.find(colKey);
					if(!iterCol)
					{ 
						//then doesnt already exist, create it
						GtGridColumn* ptrNewCol = new GtGridColumn(this);
						if(ptrNewCol)
						{
							ptrNewCol->Set_lngColumn(j);
							m_mapColumns.insert(colKey,ptrNewCol);
						}
					};
					//for each new row
					for(i = 0; i < m_lngRowCount; i++)
					{
						Htl2DIndex key; key.m_lngX = i; key.m_lngY = j;
						
						CellNodeIter iter = m_mapCells.find(key);
						if(!iter)
						{ //then doesnt already exist, create it
							//for all columns
							//make new cell and insert it
							GtGridCell* ptrNew = new GtGridCell(this);
							if(ptrNew)
							{
								ptrNew->Set_lngRow(i);
								ptrNew->Set_lngColumn(j);
								m_mapCells.insert(key,ptrNew);
							}
						}
					}//end i loop
				}//end j loop

				// then adding cols
			}else if(cols < m_lngColCount){
				// then deleting cols
				// then adding rows
				for(j = cols; j < m_lngColCount; j++)
				{

					Htl1DIndex colKey; colKey.m_lngX = j;
					CellColIter iterCol = m_mapColumns.find(colKey);
					if(iterCol)
					{ 
						m_mapColumns.erase(colKey);
					};

					//for each new row
					for(i = 0; i < m_lngRowCount; i++)
					{
						Htl2DIndex key; key.m_lngX = i; key.m_lngY = j;
						
						CellNodeIter iter = m_mapCells.find(key);
						if(iter)
						{ //then doesnt already exist, create it
							m_mapCells.erase(key);
						}
					}//end i loop
				}//end j loop
			}
			this->UpdateRowColCount();
			this->UpdateScrollGeometry();
			
			//Repopulate the rows and column collections
			if(m_mapRows.size() > 0)
			{
				for(i = 0; i < m_lngRowCount; i++)
				{
					GtGridRow* ptrCurr = m_mapRows.at(i);
					if(ptrCurr)
					{
						ptrCurr->ResetCellMembers();
					}
				}
			}
			if(m_mapColumns.size() > 0)
			{
				for(j = 0; j < m_lngColCount; j++)
				{
					GtGridColumn* ptrCurr = m_mapColumns.at(j);
					if(ptrCurr)
					{
						ptrCurr->ResetCellMembers();
					}
				}
			}

			return 1;
		};
		//!Insert a Column before index nColBefore
		int  GtGridView::InsertColumn(std::wstring & strHeading, UINT nFormat,	long nColBefore)
		{
			return 0;
		};
		//!Insert Row before index nRowBefore
		int  GtGridView::InsertRow(std::wstring &  strHeading, long nRowBefore)
		{
			return 0;
		};
		//!Delete column at index
		int GtGridView::DeleteColumn(long nColumn)
		{
			return 0;
		};
		//!Delete row at index
		int GtGridView::DeleteRow(long nRow)
		{
			return 0;
		};

		//!Delete ALL grid cells
		int GtGridView::DeleteAllItems()
		{
			size_t i,numcells;
			numcells = m_mapCells.size();
			if(numcells <= 0){return 0;};//nothing to do

			for(i = 0; i < numcells; i++)
			{
				GtGridCell* ptrCurr = m_mapCells.at(i);
				if(ptrCurr)
				{ //then doesnt already exist, create it
					delete ptrCurr;
				}
			}
			//now all deleted clear the map
			m_mapCells.clear();
			//update the counts
			this->UpdateRowColCount();

			return 1;
		};
		//!Get the pointer to the row at the index
		GtGridRow* GtGridView::GetRowPtr(long row)
		{
			Htl1DIndex key; key.m_lngX = row;
			CellRowIter iter = m_mapRows.find(key);
			if(iter)
			{
				return iter->value();
			}
			return NULL;
		};
		//!Get the pointer to the column at the index
		GtGridColumn* GtGridView::GetColumnPtr(long col)
		{
			Htl1DIndex key; key.m_lngX = col;
			CellColIter iter = m_mapColumns.find(key);
			if(iter)
			{
				return iter->value();
			}
			return NULL;
		};
		//!Get Set the row height
		int  GtGridView::GetRowHeight(long row)
		{
			GtGridRow* ptrSel = this->GetRowPtr(row);
			if(ptrSel)
			{
				return ptrSel->Get_intHeight();
			}
			return 0;
		};
		int GtGridView::SetRowHeight(long row, int height)
		{
			if(height < 0){return 0;}//safety check
			GtGridRow* ptrSel = this->GetRowPtr(row);
			if(ptrSel)
			{
				ptrSel->Set_intHeight(height);
				this->UpdateGridCellGeometry();
				this->PostPaint();
				return 1;
			}
			return 0;
		};
		//!Get Set the column width
		int  GtGridView::GetColumnWidth(long col)
		{
			GtGridColumn* ptrSel = this->GetColumnPtr(col);
			if(ptrSel)
			{
				return ptrSel->Get_intWidth();
			}
			return 0;
		};
		int GtGridView::SetColumnWidth(long col, int width)
		{
			if(width < 0){return 0;};//safety check
			GtGridColumn* ptrSel = this->GetColumnPtr(col);
			if(ptrSel)
			{
				ptrSel->Set_intWidth(width);
				this->UpdateGridCellGeometry();
				this->PostPaint();
				return 1;
			}
			return 0;
		};

		//CELL MEMBER FUNCTIONS////////////////////////////
		//!Get the pointer to the cell at index in the map
		GtGridCell* GtGridView::AtCellPtr(long index)
		{
			if((index >= 0)&&(index < m_mapCells.size()))
			{
				return m_mapCells.at(index);
			}else{
				return NULL;
			}
		};

		//!Get the pointer to the cell at location
		GtGridCell* GtGridView::GetCellPtr(long row, long col)
		{
			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{ //then doesnt already exist, create it
				return iter->value();
			}

			return NULL;
		};
		//!Get the cell origin top left point. non-visible cells will have a zeroed point
		GtPoint3DI GtGridView::GetCellOrigin(long row, long col)
		{
			GtPoint3DI pos;
			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{ //then doesnt already exist, create it
				GtGridCell* ptrCurr = iter->value();

				pos = ptrCurr->Get_objPos();
				return pos;
			}
			return pos;
		};
		//!Get the cell rect. non-visible cells will have zeroed rect
		GtRectI GtGridView::GetCellRect(int row, int col)
		{
			GtRectI rect;

			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{ //then doesnt already exist, create it
				GtGridCell* ptrCurr = iter->value();

				rect = ptrCurr->Get_objFrame();
				return rect;
			}
			return rect;
		};
		//!Get the cell from the mouse point
		GtGridCell* GtGridView::GetCellFromPt(GtPoint3DI pos)
		{
			GtRectI rect;
			size_t i,numcells;
			numcells = m_mapCells.size();
			if(numcells <= 0){return NULL;};//safety check

			for(i = 0; i < numcells;i++)
			{
				GtGridCell* ptrCurr = m_mapCells.at(i);
				if(ptrCurr)
				{
					rect = ptrCurr->Get_objFrame();
					if(rect.Contains(pos))
					{
						return ptrCurr;
					}
				}
			}
			return NULL;
		};
		//!Set the Cells in the selection to default width
		int GtGridView::SetCellsToDefWidth(GtGridSelection & arrSel)
		{
			return 0;
		};
		//!Set the Cells in the selection to default height
		int GtGridView::SetCellsToDefHeight(GtGridSelection & arrSel)
		{
			return 0;
		};

		//CELL VALUE MEMBER FUNCTIONS///////////////////////
		//!Get and Set Cell Text
		std::string GtGridView::GetText(long row,long col)
		{
			std::string strRet;
			
			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{
				GtGridCell* ptrCell = iter->value();
				strRet = ptrCell->Get_strText();
				return strRet;
			}

			return strRet;
		};
		void GtGridView::SetText(long row,long col, std::string strVal)
		{

			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{
				GtGridCell* ptrCell = iter->value();
				ptrCell->Set_strText(strVal);
				return;
			}
			return;
		};
		//!Get and Set Cell double value
		double GtGridView::GetDblValue(long row, long col)
		{
			double dblRet = 0.0f;
			std::string strRet;
			
			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{
				GtGridCell* ptrCell = iter->value();
				strRet = ptrCell->Get_strText();
				sscanf(strRet.c_str(),"%6.6f",&dblRet);
				return dblRet;
			}
			return dblRet;
		};
		void GtGridView::SetDblValue(long row, long col, double dblVal)
		{
			std::string strSet;
			char buf[256];
			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{
				GtGridCell* ptrCell = iter->value();
				if(ptrCell)
				{
					sprintf(buf,"%6.6f",dblVal);
					strSet = buf;
					ptrCell->Set_strText(strSet);
				}
				return;
			}
			return;
		};
		//!Get and Set Cell integer value
		long GtGridView::GetIntValue(long row, long col)
		{
			long lngRet = 0;
			std::string strRet;
			
			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{
				GtGridCell* ptrCell = iter->value();
				strRet = ptrCell->Get_strText();
				sscanf(strRet.c_str(),"%ld",&lngRet);
				return lngRet;
			}
			return lngRet;
		};
		void GtGridView::SetIntValue(long row, long col, long intVal)
		{
			std::string strSet;
			char buf[256];
			Htl2DIndex key; key.m_lngX = row; key.m_lngY = col;

			CellNodeIter iter = m_mapCells.find(key);
			if(iter)
			{
				GtGridCell* ptrCell = iter->value();
				if(ptrCell)
				{
					sprintf(buf,"%ld",intVal);
					strSet = buf;
					ptrCell->Set_strText(strSet);
				}
				return;
			}
			return;
		};


		//Get the pointer to the Horizontal scroll bar
		GtHorizScrollBar * GtGridView::GetHorizScrollBar(void)
		{
			return &m_objHorizScroll;
		};
		//Get the pointer to the Vertical scroll bar
		GtVertScrollBar * GtGridView::GetVertScrollBar(void)
		{
			return &m_objVertScroll;
		};

		//!Scroll Horizontal only
		void GtGridView::ScrollHorizontal(int dx)
		{
			int intNewPos, intSMin,intSMax;
			if(m_mapCells.size() <= 0){return;};//safety check
			intNewPos = dx;
			intSMin = m_objHorizScroll.Get_intMin();
			intSMax = m_objHorizScroll.Get_intMax();
			//bounds check
			if(intNewPos < intSMin)
			{
				//outside lower bound
				return;
			}
			if(intNewPos > intSMax)
			{
				//outside upper bound
				return;
			}
			//otherwise safe to update
			m_objTargetPos.x = intNewPos;
			m_lngVisibleColStart = m_intNumFixedCols + intNewPos;

			this->HorizChanged.Emit();
			this->ScrollChanged.Emit(dx,0);
			this->UpdateGridCellGeometry();
			this->PostPaint();

		};
		//!Scroll Vertical only
		void GtGridView::ScrollVertical(int dy)
		{
			int intNewPos, intSMin,intSMax;
			if(m_mapCells.size() <= 0){return;};//safety check
			intNewPos = dy;
			intSMin = m_objVertScroll.Get_intMin();
			intSMax = m_objVertScroll.Get_intMax();
			//bounds check
			if(intNewPos < intSMin)
			{
				//outside lower bound
				return;
			}
			if(intNewPos > intSMax)
			{
				//outside upper bound
				return;
			}
			//otherwise safe to update
			m_objTargetPos.y = intNewPos;
			m_lngVisibleRowStart = m_intNumFixedRows + intNewPos;

			this->VertChanged.Emit();
			this->ScrollChanged.Emit(0,dy);
			this->UpdateGridCellGeometry();
			this->PostPaint();
		};
		//!Scroll vertical and horizontal;
		void GtGridView::Scroll(int dx, int dy)
		{
			bool blnXChanged, blnYChanged;
			int intNewXPos, intNewYPos, intSMin, intSMax;
			if(m_mapCells.size() <= 0){return;};//safety check

			blnXChanged = true;
			intNewXPos = m_objTargetPos.x + dx;
			intSMin = m_objHorizScroll.Get_intMin();
			intSMax = m_objHorizScroll.Get_intMax();
			//bounds check
			if(intNewXPos < intSMin)
			{
				//outside lower bound
				blnXChanged = false;
			}
			if(intNewXPos > intSMax)
			{
				//outside upper bound
				blnXChanged = false;
			}
			//otherwise safe to update
			if(blnXChanged)
			{
				m_objTargetPos.x = intNewXPos;
				m_lngVisibleColStart = m_intNumFixedCols + intNewXPos;
				this->HorizChanged.Emit();
			}

			blnYChanged = true;
			intNewYPos = m_objTargetPos.y + dy;
			intSMin = m_objVertScroll.Get_intMin();
			intSMax = m_objVertScroll.Get_intMax();
			//bounds check
			if(intNewYPos < intSMin)
			{
				//outside lower bound
				blnYChanged = false;
			}
			if(intNewYPos > intSMax)
			{
				//outside upper bound
				blnYChanged = false;
			}
			//otherwise safe to update
			if(blnYChanged)
			{
				m_objTargetPos.y = intNewYPos;
				m_lngVisibleRowStart = m_intNumFixedRows + intNewYPos;
				this->HorizChanged.Emit();
			}
			if(blnXChanged || blnYChanged)
			{
				this->ScrollChanged.Emit(dx,dy);
				this->UpdateGridCellGeometry();
				this->PostPaint();
			}
		};

		void GtGridView::Set_objFrame(GtRectI & frame)
		{
			GtWidget::Set_objFrame(frame);
			this->UpdateScrollGeometry();	
		};

		void GtGridView::UpdateRowColCount(void)
		{
			//MAP GRID IS 0 BASED ARRAY
			size_t i,j, numcells;
			m_lngRowCount = 0;
			m_lngColCount = 0;
			numcells = m_mapCells.size();

			if(numcells <= 0){return;};//nothing to do
			//get the first cell
			GtGridCell* ptrCurr = m_mapCells.at(0);
			if(!ptrCurr){return;};//safey check
			m_lngRowCount = ptrCurr->Get_lngRow();
			m_lngColCount = ptrCurr->Get_lngColumn();
			//now cycle through the cells
			for(i = 0; i < numcells; i++)
			{
				ptrCurr = m_mapCells.at(i);
				if(ptrCurr)
				{
					if(ptrCurr->Get_lngRow() > m_lngRowCount){m_lngRowCount = ptrCurr->Get_lngRow();};
					if(ptrCurr->Get_lngColumn() > m_lngColCount){m_lngColCount = ptrCurr->Get_lngColumn();};
				}
			}
			//increment because 0 based array
			m_lngRowCount++;
			m_lngColCount++;
			return;
		};

		void GtGridView::UpdateScrollGeometry(void)
		{

			//set up the scroll bars
			GtRectI rectVert, rectHoriz, rectTarget;

			rectVert = m_objFrame;
			rectVert.xMin = rectVert.xMax - 25;
			rectVert.yMax = rectVert.yMax - 25;
			m_objVertScroll.Set_objFrame(rectVert);

			rectHoriz = m_objFrame;
			rectHoriz.yMin = rectHoriz.yMax - 25;
			rectHoriz.xMax = rectHoriz.xMax - 25;
			m_objHorizScroll.Set_objFrame(rectHoriz);
			//set up the viewport
			m_objViewFrame = m_objFrame;
			m_objViewFrame.xMax = rectVert.xMin;
			m_objViewFrame.yMax = rectHoriz.yMin;

			//set the ranges for the scroll bars

			m_objVertScroll.Set_intMin(0);
			int intVertMax = m_lngRowCount - m_intNumFixedRows;
			if(intVertMax <= 0){intVertMax = 0;};
			m_objVertScroll.Set_intMax(intVertMax);

			m_objHorizScroll.Set_intMin(0);
			int intHorizMax = m_lngColCount - m_intNumFixedCols;
			if(intHorizMax <= 0){intHorizMax = 0;};
			m_objHorizScroll.Set_intMax(intHorizMax);

			m_objVertScroll.Set_intValue(0);
			m_objHorizScroll.Set_intValue(0);
			this->PostPaint();
			return;
		};

		//update the current grid cell locations
		void GtGridView::UpdateGridCellGeometry(void)
		{
			//right now using default cell heights
			//will include real cell heights and widths when columns and rows are implemented
			size_t i,j;
			GtRectI rect, rectNull;
			int defWidth,defHeight,currWidth,currHeight, XLast,YLast;
			defWidth = 50;
			defHeight = 25;
			currWidth = defWidth;
			currHeight = defHeight;
			rectNull.Zero();

			//CALCULATE VISIBLE CELL RANGES///////////////////////////
			int sum = 0;
			m_lngVisibleRowEnd = m_lngVisibleRowStart;
			for(i = 0; i < m_intNumFixedRows; i++)
			{
				sum += GetRowHeight(i);
			}
			for(i = m_lngVisibleRowStart; i < m_lngRowCount; i++)
			{
				sum += GetRowHeight(i);
				if(sum > m_objViewFrame.Height())
				{
					break;
				}else{
					m_lngVisibleRowEnd++;
				}
			}
			//back off one
			m_lngVisibleRowEnd--;

			sum = 0;
			m_lngVisibleColEnd = m_lngVisibleColStart;
			for(j = 0; j < m_intNumFixedCols; j++)
			{
				sum += GetColumnWidth(j);
			}
			for(j = m_lngVisibleColStart; j < m_lngColCount; j++)
			{
				sum += GetColumnWidth(j);
				if(sum > m_objViewFrame.Width())
				{
					break;
				}else{
					m_lngVisibleColEnd++;
				}
			}
			//back off one
			m_lngVisibleColEnd --;


			//CALCULATE CELL RECTS/////////////////////////////////////

			rect.xMin = m_objFrame.xMin;
			rect.xMax = m_objFrame.xMin + defWidth;
			rect.yMin = m_objFrame.yMin;
			rect.yMax = m_objFrame.yMin + defHeight;
			XLast = m_objFrame.xMin;
			YLast = m_objFrame.yMin;
			for(i = 0; i < m_lngRowCount; i++)
			{
				currHeight = this->GetRowHeight(i);
				if(currHeight < 25){currHeight = 25;};//min row height
				if(i == 0)
				{  //restart row
					rect.yMin = m_objFrame.yMin;
					rect.yMax = m_objFrame.yMin + currHeight;
				}else if((i < m_intNumFixedRows) ||
					((i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd)))
				{
					//set for next row
					rect.yMin = YLast;
					rect.yMax = rect.yMin + currHeight;
				}
				for(j = 0; j < m_lngColCount; j++)
				{
					currWidth = this->GetColumnWidth(j);
					if(currWidth < 25){currWidth = 25;};//min col width
					if(j == 0)
					{  //restart row
						rect.xMin = m_objFrame.xMin;
						rect.xMax = m_objFrame.xMin + currWidth;
					}else if(( j < m_intNumFixedCols) ||
						((j >= m_lngVisibleColStart)&&(j <= m_lngVisibleColEnd)) )
					{
						rect.xMin = XLast;
						rect.xMax = rect.xMin + currWidth;
					}
					if((i < m_intNumFixedRows)&&
						(j < m_intNumFixedCols))
					{
						GtGridCell* ptrCell = this->GetCellPtr(i,j);
						if(ptrCell)
						{
							ptrCell->Set_objFrame(rect);
							ptrCell->SetVisible(true);
							ptrCell->Set_blnEditable(false);
							ptrCell->Set_objBackBrush(GtBrush(GtColor(200,200,200)));
						}
					}else if((i < m_intNumFixedRows)&&
						(j >= m_lngVisibleColStart)&&(j <= m_lngVisibleColEnd))
					{//then a fixed cell
						GtGridCell* ptrCell = this->GetCellPtr(i,j);
						if(ptrCell)
						{
							ptrCell->Set_objFrame(rect);
							ptrCell->SetVisible(true);
							ptrCell->Set_blnEditable(false);
							ptrCell->Set_objBackBrush(GtBrush(GtColor(200,200,200)));
						}
					}else if((j < m_intNumFixedCols) && 
						(i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd))
					{//then a fixed cell
						GtGridCell* ptrCell = this->GetCellPtr(i,j);
						if(ptrCell)
						{
							ptrCell->Set_objFrame(rect);
							ptrCell->SetVisible(true);
							ptrCell->Set_blnEditable(false);
							ptrCell->Set_objBackBrush(GtBrush(GtColor(200,200,200)));
						}
					}else if( (i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd)
						&& (j >= m_lngVisibleColStart)&&(j <= m_lngVisibleColEnd) )
					{//then visible cell
						GtGridCell* ptrCell = this->GetCellPtr(i,j);
						if(ptrCell)
						{
							ptrCell->Set_objFrame(rect);
							ptrCell->SetVisible(true);
							ptrCell->Set_blnEditable(true);
						}
					}else{
						//not visible cell
						GtGridCell* ptrCell = this->GetCellPtr(i,j);
						if(ptrCell)
						{
							ptrCell->Set_objFrame(rectNull);
							ptrCell->SetVisible(false);
							ptrCell->Set_blnEditable(false);
						}
					}//end cell type check
					XLast = rect.xMax;
				}//end loop through columns

				YLast = rect.yMax;
			}//end loop through rows

		};

		//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtGridView::SetFocusWidget(GtPoint3DI & pos)
		{
			//quick exclusion check
			if(!m_objFrame.Contains(pos))
			{
				m_blnFocus = false;
				return NULL;
			};//point not in frame
			//Otherwise point inside frame,
			//check scroll bars
			GtRectI rectVert, rectHoriz;
			rectVert = m_objVertScroll.Get_objFrame();
			rectHoriz = m_objHorizScroll.Get_objFrame();

			if(rectVert.Contains(pos))
			{
				m_objVertScroll.Set_blnFocus(true);
				return &m_objVertScroll;
			}else{
				m_objVertScroll.Set_blnFocus(false);
			}
			if(rectHoriz.Contains(pos))
			{
				m_objHorizScroll.Set_blnFocus(true);
				return &m_objHorizScroll;
			}else{
				m_objHorizScroll.Set_blnFocus(false);
			}
			//check the cells
			GtRectI rect;
			size_t i,numcells;
			numcells = m_mapCells.size();
			if(numcells <= 0){return NULL;};//safety check

			for(i = 0; i < numcells;i++)
			{
				GtGridCell* ptrCurr = m_mapCells.at(i);
				if(ptrCurr)
				{
					rect = ptrCurr->Get_objFrame();
					if(rect.Contains(pos))
					{
						return ptrCurr;
					}
				}
			}
			//otherwise grid widget
			return this;
		};
		//!Custom Event Processing
		int GtGridView::HandleEvent(GtEvent * ptrEvent)
		{
			return 0;
		};
		//!Custom Widget Painting
		int GtGridView::OnPaint(GtPainter * painter)
		{

			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen oldPen;
			GtBrush oldBrush;
			HDC hdcOld;
			HWND winIDOld;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			hdcOld = painter->Get_ptrHDC();
			winIDOld = painter->Get_winID();

			GtFrame::OnPaint(painter);

			//DRAW THE FIXED CELLS
			size_t i,numcells;
			numcells = m_mapCells.size();
			if(numcells <= 0)
			{
				//finished, reset old brushes and pens
				painter->Set_objPen(oldPen);
				painter->Set_objBrush(oldBrush);
				return 0;
			};//safety check

			for(i = 0; i < numcells;i++)
			{
				GtGridCell* ptrCurr = m_mapCells.at(i);
				if(ptrCurr)
				{
					if(ptrCurr->GetVisible())
					{
						ptrCurr->OnPaint(painter);
					}
				}
			}
			//DRAW THE REGULAR CELLS THAT ARE VISIBLE

			//draw the scroll bars
			m_objVertScroll.OnPaint(painter);
			m_objHorizScroll.OnPaint(painter);

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtGui

};//end namespace GT