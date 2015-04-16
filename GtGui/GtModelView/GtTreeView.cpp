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

#include ".\GtTreeView.h"
#include ".\GtTableRow.h"
#include ".\GtTableColumn.h"

#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtTreeView::GtTreeView(GtObject* ptrParent)
			: GtFrame(ptrParent)
		{
			m_strType = "GtTreeView";

			//!Number of Rows
			m_lngRowCount = 0;
			m_lngColCount = 0;
			m_intTab = 10;
			//!The current starting index for visible cells
			m_lngVisibleRowStart = 0;
			m_lngVisibleRowEnd = 0;
			m_lngVisibleColStart = 0;
			m_lngVisibleColEnd = 0;

			m_blnDrawGrid = false;
			//!boolean flag for mouse down
			m_blnMouseDown = false;
			//!boolean flage for shift key pressed
			m_blnShiftDown = false;
			//pointer to the Table model being viewed
			m_ptrModel = NULL;

			m_objSelColor = GtColor(255,255,0);
			//connect the slots
			m_objHorizScroll.Set_intDelta(2);
			m_objVertScroll.Set_intDelta(2);

			m_objHorizScroll.ValueChanged.SlotConnect(this, &GtTreeView::ScrollHorizontal);
			m_objVertScroll.ValueChanged.SlotConnect(this, &GtTreeView::ScrollVertical);


			Htl1DIndex colKey; colKey.m_lngX = 0;
			CellColIter iterCol = m_mapColumns.find(colKey);
			if(!iterCol)
			{ 
				//then doesnt already exist, create it
				GtTableColumn* ptrNewCol = new GtTableColumn(this);
				if(ptrNewCol)
				{
					ptrNewCol->Set_lngColumn(0);
					ptrNewCol->Set_intWidth(300);
					m_mapColumns.insert(colKey,ptrNewCol);
				}
			};

		};
		//virtual destructor
		GtTreeView::~GtTreeView(void)
		{
			this->UpdateRowColCount();
			this->UpdateTreeGeometry();
			m_ptrModel = NULL;
			m_objHorizScroll.ValueChanged.SlotDisconnect(this);
			m_objVertScroll.ValueChanged.SlotDisconnect(this);
		};

		//Set the Table model being viewed
		void GtTreeView::SetTreeModel(GtTreeItemModel * ptrModel)
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
				this->UpdateTreeGeometry();
				this->PostPaint();
			}
			return;
		};
		//Get the pointer to the Table model being viewed
		GtTreeItemModel * GtTreeView::GetTreeModelPtr(void)
		{
			if(m_ptrModel)
			{
				return m_ptrModel;
			}
			return NULL;
		}
		//!Force a model reset
		void GtTreeView::Reset(void)
		{
			if(m_ptrModel)
			{
				m_objSelection.Set_ptrModel(m_ptrModel);
				m_objSelection.ClearSelection();
				this->UpdateRowColCount();
				this->UpdateScrollGeometry();
				this->UpdateTreeGeometry();
				this->PostPaint();
			}
			return;
		};
		//!Get the pointer to the selection model
		GtTreeSelection* GtTreeView::GetSelection(void)
		{
			return &m_objSelection;	
		};
	
		//SCROLLING MEMBER FUNCTIONS/////////////////////////
		//Get the pointer to the Horizontal scroll bar
		GtHorizScrollBar * GtTreeView::GetHorizScrollBar(void)
		{
			return &m_objHorizScroll;
		};
		//Get the pointer to the Vertical scroll bar
		GtVertScrollBar * GtTreeView::GetVertScrollBar(void)
		{
			return &m_objVertScroll;
		};

		//!Scroll Horizontal only
		void GtTreeView::ScrollHorizontal(int dx)
		{
			if(!m_ptrModel){return;}//safety check
			int intNewPos, intSMin,intSMax;
			if(m_ptrModel->CountRows() <= 0){return;};//safety check
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
			this->UpdateTreeGeometry();
			this->PostPaint();

		};
		//!Scroll Vertical only
		void GtTreeView::ScrollVertical(int dy)
		{
			if(!m_ptrModel){return;}//safety check
			int intNewPos, intSMin,intSMax;
			if(m_ptrModel->CountRows() <= 0){return;};//safety check
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
			this->UpdateTreeGeometry();
			this->PostPaint();
		};
		//!Scroll vertical and horizontal;
		void GtTreeView::Scroll(int dx, int dy)
		{
			if(!m_ptrModel){return;}//safety check
			bool blnXChanged, blnYChanged;
			int intNewXPos, intNewYPos, intSMin, intSMax;
			if(m_ptrModel->CountRows() <= 0){return;};//safety check

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
				this->UpdateTreeGeometry();
				this->PostPaint();
			}
		};
		//ROW AND COLUMN METHODS//////////////////
		//!Get the pointer to the row at the index
		GtTableRow* GtTreeView::GetRowPtr(long row)
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
		GtTableColumn* GtTreeView::GetColumnPtr(long col)
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
		int  GtTreeView::GetRowHeight(long row)
		{
			GtTableRow* ptrSel = this->GetRowPtr(row);
			if(ptrSel)
			{
				return ptrSel->Get_intHeight();
			}
			return 0;
		};
		int GtTreeView::SetRowHeight(long row, int height)
		{
			if(height < 0){return 0;}//safety check
			GtTableRow* ptrSel = this->GetRowPtr(row);
			if(ptrSel)
			{
				ptrSel->Set_intHeight(height);
				this->UpdateTreeGeometry();
				this->PostPaint();
				return 1;
			}
			return 0;
		};
		//!Get Set the column width
		int  GtTreeView::GetColumnWidth(long col)
		{
			GtTableColumn* ptrSel = this->GetColumnPtr(col);
			if(ptrSel)
			{
				return ptrSel->Get_intWidth();
			}
			return 0;
		};
		int GtTreeView::SetColumnWidth(long col, int width)
		{
			if(width < 0){return 0;};//safety check
			GtTableColumn* ptrSel = this->GetColumnPtr(col);
			if(ptrSel)
			{
				ptrSel->Set_intWidth(width);
				this->UpdateTreeGeometry();
				this->PostPaint();
				return 1;
			}
			return 0;
		};
		//CELL MEMBER FUNCTIONS////////////////////////////
		//!Get the pointer to the cell at index in the map
		GtTreeModelIndex* GtTreeView::GetCellPtr(size_t index)
		{
			if(!m_ptrModel){return NULL;};//safety check
			size_t num = m_ptrModel->CountRows();
			if((index >= 0)&&(index < num))
			{
				return m_ptrModel->GetIndex(index,0);
			}else{
				return NULL;
			}
		};

		//!Get the pointer to the cell at location
		GtTreeModelIndex* GtTreeView::GetCellPtr(long row, long col)
		{
			if(!m_ptrModel){return NULL;};//safety check
			size_t num = m_ptrModel->CountRows();
			GtTreeModelIndex* cell = m_ptrModel->GetIndex(row,col);
			if(cell){return cell;};
			//otherwise didn't find anything
			return NULL;
		};
		//!Get the cell origin top left point. non-visible cells will have a zeroed point
		GtPoint3DI GtTreeView::GetCellOrigin(long row, long col)
		{
			GtPoint3DI topLeft;
			topLeft.Zero();
			if(!m_ptrModel){return topLeft;};//safety check
			size_t num = m_ptrModel->CountRows();
			GtTreeModelIndex* cell = m_ptrModel->GetIndex(row,col);
			if(cell)
			{
				topLeft.x = cell->m_objFrame.xMin;
				topLeft.y = cell->m_objFrame.yMin;
			};
			//otherwise didn't find anything
			return topLeft;
		};
		//!Get the cell rect. non-visible cells will have zeroed rect
		GtRectI GtTreeView::GetCellRect(int row, int col)
		{
			GtRectI rectNull;
			rectNull.Zero();
			if(!m_ptrModel){return rectNull;};//safety check
			size_t num = m_ptrModel->CountRows();
			GtTreeModelIndex* cell = m_ptrModel->GetIndex(row,col);
			if(cell)
			{
				return cell->m_objFrame;
			};
			//otherwise didn't find anything
			return rectNull;
		};
		//!Get the cell from the mouse point
		GtTreeModelIndex* GtTreeView::GetCellFromPt(GtPoint3DI pos)
		{
			//cycle through the indexes and get the points
			if(!m_ptrModel){return NULL;}//safety check
			size_t i, num;
			num = m_ptrModel->CountRows();
			for(i = 0; i < num;i++)
			{
				GtTreeModelIndex* ptrCurr = m_ptrModel->AtIndex(i);
				if(ptrCurr)
				{
					if(ptrCurr->m_objFrame.Contains(pos))
					{//match
						return ptrCurr;
					}
					if(ptrCurr->m_objCtrl.Contains(pos))
					{
						return ptrCurr;
					}
				}
			}
			//couldn't find match
			return NULL;
		};
		//EVENT HANDLING MEMBER FUNCTIONS///////////////////
		//!Custom Event Processing
		int GtTreeView::HandleEvent(GtEvent * ptrEvent)
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
					GtTreeModelIndex* ptrCell = this->GetCellFromPt(pos);
					if(ptrCell)
					{
						if(ptrCell->m_objCtrl.Contains(pos))
						{
							//toggle expanded
							ptrCell->m_blnExpanded = !ptrCell->m_blnExpanded;
							this->UpdateTreeGeometry();
							this->PostPaint();
							return 1;
						}
						//otherwise add / change selection
						m_objSelection.Set_ptrTopLeft(ptrCell);
						m_objSelection.AddSelIndex(ptrCell);
						this->SelectionChanged.Emit();
					};

				}else{
					//range selection
					GtTreeModelIndex* ptrCell = this->GetCellFromPt(pos);
					if(ptrCell)
					{
						//m_objSelection.Set_ptrBottomRight(ptrCell);
						//m_objSelection.GetSelectedRange();
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
		int GtTreeView::OnPaint(GtPainter * painter)
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

			size_t lngDrawRow = 0;
			GtTreeModelIndex* ptrRoot = m_ptrModel->GetRootNodePtr();
			if(ptrRoot)
			{
				this->OnPaintNode(painter, ptrRoot,lngDrawRow);
			}

			//draw the scroll bar
			this->m_objVertScroll.OnPaint(painter);
			this->m_objHorizScroll.OnPaint(painter);
			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};		

		void GtTreeView::OnPaintNode(GtPainter * painter, GtTreeModelIndex* ptrNode, size_t & lngCurrRow )
		{
			int defWidth,defHeight;
			defWidth = 200;
			defHeight = 25;

			if(!ptrNode){return;};
			if(!m_ptrModel){return;};
			if((m_lngVisibleRowStart == 0)&&
				(m_lngVisibleRowEnd == 0))
			{
				return;//nothing to draw
			}

			lngCurrRow += 1;
			if( (lngCurrRow >= m_lngVisibleRowStart) && 
				(lngCurrRow <= m_lngVisibleRowEnd) )
			{
				if(ptrNode->m_blnVisible)
				{
					if((ptrNode->HasChildren())&&(ptrNode->m_blnExpanded))
					{
						painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
						painter->GtDrawTriangleDown(ptrNode->m_objCtrl,0);
					}
					if((ptrNode->HasChildren())&&(!ptrNode->m_blnExpanded))
					{
						painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
						painter->GtDrawTriangleRight(ptrNode->m_objCtrl,0);
					}

					if(m_objSelection.IsSelected(ptrNode))
					{
						painter->Set_objBrush(GtBrush(m_objSelColor));
						painter->GtFillRect(ptrNode->m_objFrame);
					}
					painter->Set_objBrush(m_objBackBrush);
					if(m_blnDrawGrid)
					{
						painter->GtDrawFrame(ptrNode->m_objFrame);
					}
					painter->GtDrawText(ptrNode->m_strText,ptrNode->m_objFrame,0);
				}
			}//end visible row check

			if(ptrNode->m_blnExpanded)
			{//expanded draw children
				size_t i, numSub;
				numSub = ptrNode->m_arrSubNodes.size();
				for(i = 0; i < numSub; i++)
				{
					GtTreeModelIndex* ptrSub = ptrNode->m_arrSubNodes.at(i);
					if(ptrSub)
					{
						this->OnPaintNode(painter,ptrSub,lngCurrRow);
					}
				}//end loop
			}//end node expanded
		};


		//update the row count
		void GtTreeView::UpdateRowColCount()
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
			//numcells = m_ptrModel->CountRows();

			//if(numcells <= 0){return;};//nothing to do
			////get the first cell
			////now cycle through the cells
			//GtTreeModelIndex* ptrCurr = NULL;
			//for(i = 0; i < numcells; i++)
			//{
			//	ptrCurr = m_ptrModel->AtIndex(i);
			//	if(ptrCurr)
			//	{
			//		if(ptrCurr->m_lngRow > m_lngRowCount){m_lngRowCount = ptrCurr->m_lngRow;};

			//		if(ptrCurr->m_lngCol > ptrCurr->m_arrData.size()){m_lngColCount = ptrCurr->m_arrData.size();};
			//	}
			//}
			//increment because 0 based array
			m_lngRowCount = m_ptrModel->CountRows();
			m_lngColCount = m_ptrModel->CountColumns();


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

			return;
		};
		//update the Table geometries
		void GtTreeView::UpdateTreeGeometry()
		{
			if(!m_ptrModel){return;}//safey check

			this->ClearGeometry();
			//right now using default cell heights
			//will include real cell heights and widths when columns and rows are implemented
			size_t i,j;
			GtRectI rect, rectNull;
			int defWidth,defHeight,currWidth,currHeight, XLast,YLast;
			defWidth = 300;
			defHeight = 25;
			currWidth = defWidth;
			currHeight = defHeight;
			rectNull.Zero();

			//CALCULATE VISIBLE CELL RANGES///////////////////////////
			int sum = 0;
			m_lngVisibleRowEnd = m_lngVisibleRowStart;
			for(i = m_lngVisibleRowStart; i < m_lngRowCount; i++)
			{
				sum += defHeight;
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

			GtTreeModelIndex* ptrRoot = m_ptrModel->GetRootNodePtr();
			size_t intCurrRow = 0;
			this->UpdateNodeGeometry(ptrRoot,intCurrRow,rect);
			return;
		};


		//update the current Table cell locations
		void GtTreeView::UpdateNodeGeometry(GtTreeModelIndex* ptrNode, size_t & lngCurrRow, GtRectI & rectLast)
		{
			int defWidth,defHeight;
			defWidth = 200;
			defHeight = 25;

			if(!ptrNode){return;};
			if(!m_ptrModel){return;};
			
			lngCurrRow += 1;
			if( (lngCurrRow >= m_lngVisibleRowStart) && 
				(lngCurrRow <= m_lngVisibleRowEnd) )
			{
				//specialcase root
				if(ptrNode == m_ptrModel->GetRootNodePtr())
				{
					ptrNode->m_objFrame = rectLast;
				}else{
					rectLast.xMin = m_objFrame.xMin;
					//rect.xMax = m_objFrame.xMin + GetColumnWidth(0);
					long lngHalfWidth = rectLast.xMax - rectLast.xMin;
					//now indent the left side by level
					long level = ptrNode->m_lngLevel * m_intTab;
					if(level < lngHalfWidth)//max indent is half width
					{
						rectLast.xMin += level + 10;//constant 10 for controls
					}

					//set for next row
					rectLast.yMin = rectLast.yMax;
					rectLast.yMax = rectLast.yMin + defHeight;
					//assign
					ptrNode->m_objFrame = rectLast;

					if(ptrNode->HasChildren())
					{
						//the control node
						ptrNode->m_objCtrl.xMin = rectLast.xMin - 10;
						ptrNode->m_objCtrl.xMax = rectLast.xMin;
						ptrNode->m_objCtrl.yMin = rectLast.yMin;
						ptrNode->m_objCtrl.yMax = rectLast.yMin + 10;
					}else{
						ptrNode->m_objCtrl.Zero();
					}

				}//end Xcoord modifications

				//end visible row check
			}else{
				ptrNode->m_objFrame.Zero();
				ptrNode->m_objCtrl.Zero();
			}

			if(ptrNode->m_blnExpanded)
			{//expanded draw children
				size_t i, numSub;
				numSub = ptrNode->m_arrSubNodes.size();
				for(i = 0; i < numSub; i++)
				{
					GtTreeModelIndex* ptrSub = ptrNode->m_arrSubNodes.at(i);
					if(ptrSub)
					{
						this->UpdateNodeGeometry(ptrSub,lngCurrRow,rectLast);
					}
				}
			}
		};

		//clean slates the tree geometry (zeros the rects)
		void GtTreeView::ClearGeometry(void)
		{
			if(!m_ptrModel){return;};//safety check
			size_t i, numNodes;
			numNodes = this->m_ptrModel->CountRows();
			for(i = 0; i < numNodes; i++)
			{
				GtTreeModelIndex * ptrCurr = m_ptrModel->AtIndex(i);
				if(ptrCurr)
				{
					ptrCurr->m_objFrame.Zero();
					ptrCurr->m_objCtrl.Zero();
				}
			}

		};

		//update the scroll geometries
		void GtTreeView::UpdateScrollGeometry()
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

		void GtTreeView::Set_objFrame(GtRectI & frame)
		{
			GtWidget::Set_objFrame(frame);
			this->UpdateScrollGeometry();	
		};

	//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtTreeView::SetFocusWidget(GtPoint3DI & pos)
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



			//for(i = 0; i < m_lngRowCount; i++)
			//{
			//	currHeight = this->GetRowHeight(i);
			//	GtTreeModelIndex* ptrCellNode = this->GetCellPtr(i,0);
			//	if(currHeight < 25){currHeight = 25;};//min row height

			//	if(ptrCellNode)
			//	{
			//		if(ptrCellNode->m_blnVisible)
			//		{
			//			if(i == 0)
			//			{  //restart row
			//				rect.yMin = m_objFrame.yMin;
			//				rect.yMax = m_objFrame.yMin + currHeight;
			//			}else if((i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd))
			//			{
			//				//set for next row
			//				rect.yMin = YLast;
			//				rect.yMax = rect.yMin + currHeight;
			//			}
			//		}
			//	}
			//	for(j = 0; j < m_lngColCount; j++)
			//	{
			//		currWidth = this->GetColumnWidth(j);
			//		if(currWidth < 25){currWidth = 25;};//min col width
			//		if(j == 0)
			//		{  //restart row
			//			rect.xMin = m_objFrame.xMin;
			//			rect.xMax = m_objFrame.xMin + currWidth;
			//			long lngHalfWidth = rect.xMax - rect.xMin;
			//			//now indent the left side by level
			//			if(ptrCellNode)
			//			{
			//				long level = ptrCellNode->m_lngLevel * m_intTab;
			//				if(level < lngHalfWidth)//max indent is half width
			//				{
			//					rect.xMin += level + 10;//constant 10 for controls
			//				}
			//			}

			//			if(ptrCellNode->HasChildren())
			//			{
			//			//the control node
			//				ptrCellNode->m_objCtrl.xMin = rect.xMin - 10;
			//				ptrCellNode->m_objCtrl.xMax = rect.xMin;
			//				ptrCellNode->m_objCtrl.yMin = rect.yMin;
			//				ptrCellNode->m_objCtrl.yMax = rect.yMin + 10;
			//			}else{
			//				ptrCellNode->m_objCtrl.Zero();
			//			}
			//		}else if((j >= m_lngVisibleColStart)&&(j <= m_lngVisibleColEnd))
			//		{
			//			rect.xMin = XLast;
			//			rect.xMax = rect.xMin + currWidth;
			//		}

			//		if( (i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd)
			//			&& (j >= m_lngVisibleColStart)&&(j <= m_lngVisibleColEnd) )
			//		{//then visible cell
			//			GtTreeModelIndex* ptrCell = this->GetCellPtr(i,j);
			//			if(ptrCell)
			//			{
			//				ptrCell->m_objFrame = rect;
			//				ptrCell->m_blnVisible = true;
			//			}
			//		}else{
			//			//not visible cell
			//			GtTreeModelIndex* ptrCell = this->GetCellPtr(i,j);
			//			if(ptrCell)
			//			{
			//				ptrCell->m_objFrame = rectNull;
			//				ptrCell->m_blnVisible = false;
			//			}
			//		}//end cell type check
			//		XLast = rect.xMax;
			//	}//end loop through columns

			//	YLast = rect.yMax;
			//}//end loop through rows