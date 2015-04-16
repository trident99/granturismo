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

#include ".\GtTableView.h"
#include ".\GtTableRow.h"
#include ".\GtTableColumn.h"

#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtTableView::GtTableView(GtObject* ptrParent)
			: GtFrame(ptrParent)
		{
			m_strType = "GtTableView";

			//!Number of Rows
			m_lngRowCount = 0;
			m_lngColCount = 0;

			//!The current starting index for visible cells
			m_lngVisibleRowStart = 0;
			m_lngVisibleRowEnd = 0;
			m_lngVisibleColStart = 0;
			m_lngVisibleColEnd = 0;

			//!boolean flag for mouse down
			m_blnMouseDown = false;
			//!boolean flage for shift key pressed
			m_blnShiftDown = false;
			//pointer to the Table model being viewed
			m_ptrModel = NULL;

			m_objSelColor = GtColor(255,255,0);
			//connect the slots
			m_objHorizScroll.ValueChanged.SlotConnect(this, &GtTableView::ScrollHorizontal);
			m_objVertScroll.ValueChanged.SlotConnect(this, &GtTableView::ScrollVertical);
		};
		//virtual destructor
		GtTableView::~GtTableView(void)
		{
			this->UpdateRowColCount();
			this->UpdateTableGeometry();
			m_ptrModel = NULL;
			m_objHorizScroll.ValueChanged.SlotDisconnect(this);
			m_objVertScroll.ValueChanged.SlotDisconnect(this);
		};

		//Set the Table model being viewed
		void GtTableView::SetTableModel(GtTableItemModel * ptrModel)
		{
			if(ptrModel)
			{
				m_lngVisibleRowStart = 0;
				m_lngVisibleRowEnd = 0;
				m_lngVisibleColStart = 0;
				m_lngVisibleColEnd = 0;

				m_ptrModel = ptrModel;
				m_objSelection.ClearSelection();
				m_objSelection.Set_ptrModel(m_ptrModel);

				this->UpdateRowColCount();
				this->UpdateScrollGeometry();
				this->UpdateTableGeometry();
				this->PostPaint();
			}
			return;
		};
		//Get the pointer to the Table model being viewed
		GtTableItemModel * GtTableView::GetTableModelPtr(void)
		{
			if(m_ptrModel)
			{
				return m_ptrModel;
			}
			return NULL;
		}
		//!Force a model reset
		void GtTableView::Reset(void)
		{
			if(m_ptrModel)
			{
				m_ptrModel->UpdateSyncModel();
				m_objSelection.Set_ptrModel(m_ptrModel);
				m_objSelection.ClearSelection();
				this->UpdateRowColCount();
				this->UpdateScrollGeometry();
				this->UpdateTableGeometry();
				this->PostPaint();
			}
			return;
		};
		//!Get the pointer to the selection model
		GtTableSelection* GtTableView::GetSelection(void)
		{
			return &m_objSelection;	
		};
	
		//SCROLLING MEMBER FUNCTIONS/////////////////////////
		//Get the pointer to the Horizontal scroll bar
		GtHorizScrollBar * GtTableView::GetHorizScrollBar(void)
		{
			return &m_objHorizScroll;
		};
		//Get the pointer to the Vertical scroll bar
		GtVertScrollBar * GtTableView::GetVertScrollBar(void)
		{
			return &m_objVertScroll;
		};

		//!Scroll Horizontal only
		void GtTableView::ScrollHorizontal(int dx)
		{
			if(!m_ptrModel){return;}//safety check
			int intNewPos, intSMin,intSMax;
			if(m_ptrModel->CountCells() <= 0){return;};//safety check
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
			m_lngVisibleColStart = intNewPos;

			this->HorizChanged.Emit();
			this->ScrollChanged.Emit(dx,0);
			this->UpdateTableGeometry();
			this->PostPaint();

		};
		//!Scroll Vertical only
		void GtTableView::ScrollVertical(int dy)
		{
			if(!m_ptrModel){return;}//safety check
			int intNewPos, intSMin,intSMax;
			if(m_ptrModel->CountCells() <= 0){return;};//safety check
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
			m_lngVisibleRowStart = intNewPos;

			this->VertChanged.Emit();
			this->ScrollChanged.Emit(0,dy);
			this->UpdateTableGeometry();
			this->PostPaint();
		};
		//!Scroll vertical and horizontal;
		void GtTableView::Scroll(int dx, int dy)
		{
			if(!m_ptrModel){return;}//safety check
			bool blnXChanged, blnYChanged;
			int intNewXPos, intNewYPos, intSMin, intSMax;
			if(m_ptrModel->CountCells() <= 0){return;};//safety check

			blnXChanged = true;
			intNewXPos = dx;
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
				m_lngVisibleColStart = intNewXPos;
				this->HorizChanged.Emit();
			}

			blnYChanged = true;
			intNewYPos = dy;
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
				m_lngVisibleRowStart = intNewYPos;
				this->HorizChanged.Emit();
			}
			if(blnXChanged || blnYChanged)
			{
				this->ScrollChanged.Emit(dx,dy);
				this->UpdateTableGeometry();
				this->PostPaint();
			}
		};
		//ROW AND COLUMN METHODS//////////////////
		//!Get the pointer to the row at the index
		GtTableRow* GtTableView::GetRowPtr(long row)
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
		GtTableColumn* GtTableView::GetColumnPtr(long col)
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
		int  GtTableView::GetRowHeight(long row)
		{
			GtTableRow* ptrSel = this->GetRowPtr(row);
			if(ptrSel)
			{
				return ptrSel->Get_intHeight();
			}
			return 0;
		};
		int GtTableView::SetRowHeight(long row, int height)
		{
			if(height < 0){return 0;}//safety check
			GtTableRow* ptrSel = this->GetRowPtr(row);
			if(ptrSel)
			{
				ptrSel->Set_intHeight(height);
				this->UpdateTableGeometry();
				this->PostPaint();
				return 1;
			}
			return 0;
		};
		//!Get Set the column width
		int  GtTableView::GetColumnWidth(long col)
		{
			GtTableColumn* ptrSel = this->GetColumnPtr(col);
			if(ptrSel)
			{
				return ptrSel->Get_intWidth();
			}
			return 0;
		};
		int GtTableView::SetColumnWidth(long col, int width)
		{
			if(width < 0){return 0;};//safety check
			GtTableColumn* ptrSel = this->GetColumnPtr(col);
			if(ptrSel)
			{
				ptrSel->Set_intWidth(width);
				this->UpdateTableGeometry();
				this->PostPaint();
				return 1;
			}
			return 0;
		};
		//CELL MEMBER FUNCTIONS////////////////////////////
		//!Get the pointer to the cell at index in the map
		GtTableModelIndex* GtTableView::GetCellPtr(size_t index)
		{
			if(!m_ptrModel){return NULL;};//safety check
			size_t num = m_ptrModel->CountCells();
			if((index >= 0)&&(index < num))
			{
				return m_ptrModel->GetIndex(index);
			}else{
				return NULL;
			}
		};

		//!Get the pointer to the cell at location
		GtTableModelIndex* GtTableView::GetCellPtr(long row, long col)
		{
			if(!m_ptrModel){return NULL;};//safety check
			size_t num = m_ptrModel->CountCells();
			GtTableModelIndex* cell = m_ptrModel->GetIndex(row,col);
			if(cell){return cell;};
			//otherwise didn't find anything
			return NULL;
		};
		//!Get the cell origin top left point. non-visible cells will have a zeroed point
		GtPoint3DI GtTableView::GetCellOrigin(long row, long col)
		{
			GtPoint3DI topLeft;
			topLeft.Zero();
			if(!m_ptrModel){return topLeft;};//safety check
			size_t num = m_ptrModel->CountCells();
			GtTableModelIndex* cell = m_ptrModel->GetIndex(row,col);
			if(cell)
			{
				topLeft.x = cell->m_objFrame.xMin;
				topLeft.y = cell->m_objFrame.yMin;
			};
			//otherwise didn't find anything
			return topLeft;
		};
		//!Get the cell rect. non-visible cells will have zeroed rect
		GtRectI GtTableView::GetCellRect(int row, int col)
		{
			GtRectI rectNull;
			rectNull.Zero();
			if(!m_ptrModel){return rectNull;};//safety check
			size_t num = m_ptrModel->CountCells();
			GtTableModelIndex* cell = m_ptrModel->GetIndex(row,col);
			if(cell)
			{
				return cell->m_objFrame;
			};
			//otherwise didn't find anything
			return rectNull;
		};
		//!Get the cell from the mouse point
		GtTableModelIndex* GtTableView::GetCellFromPt(GtPoint3DI pos)
		{
			//cycle through the indexes and get the points
			if(!m_ptrModel){return NULL;}//safety check
			size_t i, num;
			num = m_ptrModel->CountCells();
			for(i = 0; i < num;i++)
			{
				GtTableModelIndex* ptrCurr = m_ptrModel->GetIndex(i);
				if(ptrCurr)
				{
					if(ptrCurr->m_objFrame.Contains(pos))
					{//match
						return ptrCurr;
					}
				}
			}
			//couldn't find match
			return NULL;
		};
		//EVENT HANDLING MEMBER FUNCTIONS///////////////////
		//!Custom Event Processing
		int GtTableView::HandleEvent(GtEvent * ptrEvent)
		{
						
			if(GtIsKeyDown(VK_SHIFT)){m_blnShiftDown = true;}else{m_blnShiftDown = false;};

			//safety check
			if(!ptrEvent){return 0;};
			GtPoint3DI pos;
			pos.x = gRound(ptrEvent->m_objPos.x);
			pos.y = gRound(ptrEvent->m_objPos.y);

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				m_blnMouseDown = true;
				if(!m_blnShiftDown)
				{
					//new selection started
					m_objSelection.ClearSelection();
					GtTableModelIndex* ptrCell = this->GetCellFromPt(pos);
					if(ptrCell)
					{
						m_objSelection.Set_ptrTopLeft(ptrCell);
						m_objSelection.AddSelIndex(ptrCell);
						this->SelectionChanged.Emit();
					};

				}else{
					//range selection
					GtTableModelIndex* ptrCell = this->GetCellFromPt(pos);
					if(ptrCell)
					{
						m_objSelection.Set_ptrBottomRight(ptrCell);
						m_objSelection.GetSelectedRange();
						this->SelectionChanged.Emit();
					};		
				}

				this->PostPaint();
				return 1;
			}
			if(ptrEvent->m_objType == MouseLeftRelease)
			{
				m_blnMouseDown = false;

				this->PostPaint();
				return 1;
			}
			if((ptrEvent->m_objType == KeyPress)&&
				(ptrEvent->m_objKey == Key_Escape))
			{
				m_objSelection.ClearSelection();
				this->SelectionChanged.Emit();
				this->PostPaint();
				return 1;
			}

			return 0;
		};

		//!Custom Widget Painting
		int GtTableView::OnPaint(GtPainter * painter)
		{
			//safety check
			if(!painter){return 0;};
			GtPen oldPen;
			GtBrush oldBrush;

			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			//paint the base frame
			painter->Set_objBrush(m_objBackBrush);
			GtFrame::OnPaint(painter);
	
			if(!m_ptrModel)
			{
				painter->Set_objPen(oldPen);
				painter->Set_objBrush(oldBrush);
				return 0;
			}

			//otherwise draw the cells
			size_t i,j, numCells;
			numCells = m_ptrModel->CountCells();
			for(i = m_lngVisibleRowStart; i < m_lngVisibleRowEnd; i++)
			{
				for(j = m_lngVisibleColStart; j < m_lngVisibleColEnd; j++)
				{
					GtTableModelIndex* ptrCell = m_ptrModel->GetIndex(i,j);
					if(ptrCell)
					{
						if(ptrCell->m_blnVisible)
						{
							if(m_objSelection.IsSelected(ptrCell))
							{
								painter->Set_objBrush(GtBrush(m_objSelColor));
								painter->GtFillRect(ptrCell->m_objFrame);
							}
							painter->Set_objBrush(m_objBackBrush);
							painter->GtDrawFrame(ptrCell->m_objFrame);
							painter->GtDrawText(ptrCell->m_strText,ptrCell->m_objFrame,0);
						}
					}
				}//end j loop
			}//end i loop

			//draw the scroll bar
			this->m_objVertScroll.OnPaint(painter);
			this->m_objHorizScroll.OnPaint(painter);
			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};		
		//update the row count
		void GtTableView::UpdateRowColCount()
		{
			if(!m_ptrModel){return;};
			//MAP Table IS 0 BASED ARRAY
			size_t i,j, numcells;
			//record old values
			size_t rowsOld = m_lngRowCount;
			size_t colsOld = m_lngColCount;

			//reset values
			m_lngRowCount = 0;
			m_lngColCount = 0;
			numcells = m_ptrModel->CountCells();

			if(numcells <= 0){return;};//nothing to do
			//get the first cell
			GtTableModelIndex* ptrCurr = m_ptrModel->GetIndex(0);
			if(!ptrCurr){return;};//safey check
			m_lngRowCount = ptrCurr->m_lngRow;
			m_lngColCount = ptrCurr->m_lngCol;
			//now cycle through the cells
			for(i = 0; i < numcells; i++)
			{
				ptrCurr = m_ptrModel->GetIndex(i);
				if(ptrCurr)
				{
					if(ptrCurr->m_lngRow > m_lngRowCount){m_lngRowCount = ptrCurr->m_lngRow;};
					if(ptrCurr->m_lngCol > m_lngColCount){m_lngColCount = ptrCurr->m_lngCol;};
				}
			}
			//increment because 0 based array
			m_lngRowCount++;
			m_lngColCount++;


			//ROWS FIRST////////////////
			if(rowsOld < m_lngRowCount)
			{
				// then adding rows
				for(i = rowsOld; i < m_lngRowCount; i++)
				{
					Htl1DIndex rowKey; rowKey.m_lngX = i;
					CellRowIter iterRow = m_mapRows.find(rowKey);
					if(!iterRow)
					{ 
						//then doesnt already exist, create it
						GtTableRow* ptrNewRow = new GtTableRow(this);
						if(ptrNewRow)
						{
							ptrNewRow->Set_lngRow(i);
							m_mapRows.insert(rowKey,ptrNewRow);
						}
					};
				}//end i loop
			}else if(m_lngRowCount < rowsOld){
				// then deleting rows
				// then adding rows
				for(i = m_lngRowCount; i < rowsOld; i++)
				{
					Htl1DIndex rowKey; rowKey.m_lngX = i;
					CellRowIter iterRow = m_mapRows.find(rowKey);
					if(iterRow)
					{ 
						m_mapRows.erase(rowKey);
					};
				}//end i loop
			}
			//COLUMNS SECOND////////////////
			if(colsOld < m_lngColCount)
			{
				// then adding rows
				for(j = colsOld; j < m_lngColCount; j++)
				{
					Htl1DIndex colKey; colKey.m_lngX = j;
					CellColIter iterCol = m_mapColumns.find(colKey);
					if(!iterCol)
					{ 
						//then doesnt already exist, create it
						GtTableColumn* ptrNewCol = new GtTableColumn(this);
						if(ptrNewCol)
						{
							ptrNewCol->Set_lngColumn(j);
							m_mapColumns.insert(colKey,ptrNewCol);
						}
					};

				}//end j loop

				// then adding cols
			}else if(m_lngColCount < colsOld){
				// then deleting cols
				// then adding rows
				for(j = m_lngColCount; j < colsOld; j++)
				{

					Htl1DIndex colKey; colKey.m_lngX = j;
					CellColIter iterCol = m_mapColumns.find(colKey);
					if(iterCol)
					{ 
						m_mapColumns.erase(colKey);
					};

				}//end j loop
			}
			
			//Repopulate the rows and column collections
			if(m_mapRows.size() > 0)
			{
				for(i = 0; i < m_lngRowCount; i++)
				{
					GtTableRow* ptrCurr = m_mapRows.at(i);
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
					GtTableColumn* ptrCurr = m_mapColumns.at(j);
					if(ptrCurr)
					{
						ptrCurr->ResetCellMembers();
					}
				}
			}

			return;
		};
		//update the Table geometries
		void GtTableView::UpdateTableGeometry()
		{
			if(!m_ptrModel){return;}//safey check
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
			if(sum > m_objViewFrame.Height())
			{
				m_lngVisibleRowEnd--;
			}
			if(m_lngVisibleRowEnd < 0){m_lngVisibleRowEnd = 0;}//min value


			sum = 0;
			m_lngVisibleColEnd = m_lngVisibleColStart;
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
			if(sum > m_objViewFrame.Width())
			{
				m_lngVisibleColEnd--;
			}
			if(m_lngVisibleColEnd < 0){m_lngVisibleColEnd = 0;}//min value



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
				}else if((i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd))
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
					}else if((j >= m_lngVisibleColStart)&&(j <= m_lngVisibleColEnd))
					{
						rect.xMin = XLast;
						rect.xMax = rect.xMin + currWidth;
					}

					if( (i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd)
						&& (j >= m_lngVisibleColStart)&&(j <= m_lngVisibleColEnd) )
					{//then visible cell
						GtTableModelIndex* ptrCell = this->GetCellPtr(i,j);
						if(ptrCell)
						{
							ptrCell->m_objFrame = rect;
							ptrCell->m_blnVisible = true;
						}
					}else{
						//not visible cell
						GtTableModelIndex* ptrCell = this->GetCellPtr(i,j);
						if(ptrCell)
						{
							ptrCell->m_objFrame = rectNull;
							ptrCell->m_blnVisible = false;
						}
					}//end cell type check
					XLast = rect.xMax;
				}//end loop through columns

				YLast = rect.yMax;
			}//end loop through rows

		};
		//update the scroll geometries
		void GtTableView::UpdateScrollGeometry()
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
			int intVertMax = m_lngRowCount;
			if(intVertMax <= 0){intVertMax = 0;};
			m_objVertScroll.Set_intMax(intVertMax);

			m_objHorizScroll.Set_intMin(0);
			int intHorizMax = m_lngColCount;
			if(intHorizMax <= 0){intHorizMax = 0;};
			m_objHorizScroll.Set_intMax(intHorizMax);

			m_objVertScroll.Set_intValue(0);
			m_objHorizScroll.Set_intValue(0);
			this->PostPaint();
			return;
		};

		void GtTableView::Set_objFrame(GtRectI & frame)
		{
			GtWidget::Set_objFrame(frame);
			this->UpdateScrollGeometry();	
		};

	//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtTableView::SetFocusWidget(GtPoint3DI & pos)
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

			if(rectVert.Contains(pos))
			{
				m_objVertScroll.Set_blnFocus(true);
				return &m_objVertScroll;
			}else{
				m_objVertScroll.Set_blnFocus(false);
			}

			rectHoriz = m_objHorizScroll.Get_objFrame();

			if(rectHoriz.Contains(pos))
			{
				m_objHorizScroll.Set_blnFocus(true);
				return &m_objHorizScroll;
			}else{
				m_objHorizScroll.Set_blnFocus(false);
			}

			//otherwise Table widget
			return this;
		};
	};//end namespace GtCore

};//end namespace GT