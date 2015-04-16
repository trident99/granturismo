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

#include ".\GtListView.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtListView::GtListView(GtObject* ptrParent)
			: GtFrame(ptrParent)
		{
			m_strType = "GtListView";

			//!Number of Rows
			m_lngRowCount = 0;

			//!The current starting index for visible cells
			m_lngVisibleRowStart = 0;
			m_lngVisibleRowEnd = 0;

			//!boolean flag for mouse down
			m_blnMouseDown = false;
			//!boolean flage for shift key pressed
			m_blnShiftDown = false;
			//pointer to the list model being viewed
			m_ptrModel = NULL;

			//connect the slots
			m_objVertScroll.ValueChanged.SlotConnect(this, &GtListView::ScrollVertical);
		};
		//virtual destructor
		GtListView::~GtListView(void)
		{
			this->UpdateRowCount();
			this->UpdateListGeometry();
			m_ptrModel = NULL;
			m_objVertScroll.ValueChanged.SlotDisconnect(this);
		};

		//Set the list model being viewed
		void GtListView::SetListModel(GtListItemModel * ptrModel)
		{
			if(ptrModel)
			{
				m_lngVisibleRowStart = 0;
				m_lngVisibleRowEnd = 0;
				m_ptrModel = ptrModel;
				m_objSelection.ClearSelection();
				m_objSelection.Set_ptrModel(m_ptrModel);
				this->UpdateRowCount();
				this->UpdateScrollGeometry();
				this->UpdateListGeometry();
				this->PostPaint();
			}
			return;
		};
		//Get the pointer to the list model being viewed
		GtListItemModel * GtListView::GetListModelPtr(void)
		{
			if(m_ptrModel)
			{
				return m_ptrModel;
			}
			return NULL;
		}
		//!Force a model reset
		void GtListView::Reset(void)
		{
			if(m_ptrModel)
			{
				m_ptrModel->UpdateSyncModel();
				m_objSelection.Set_ptrModel(m_ptrModel);
				m_objSelection.ClearSelection();
				this->UpdateRowCount();
				this->UpdateScrollGeometry();
				this->UpdateListGeometry();
				this->PostPaint();
			}
			return;
		};
		//!Get the pointer to the selection model
		GtListSelection* GtListView::GetSelection(void)
		{
			return &m_objSelection;	
		};
		//!Get the model index at point
		GtListModelIndex* GtListView::GetIndexAtPt ( GtPoint3DI & pt )
		{
			//cycle through the indexes and get the points
			if(!m_ptrModel){return NULL;}//safety check
			size_t i, num;
			num = m_ptrModel->CountRows();
			for(i = 0; i < num;i++)
			{
				GtListModelIndex* ptrCurr = m_ptrModel->GetIndex(i);
				if(ptrCurr)
				{
					if(ptrCurr->m_objFrame.Contains(pt))
					{//match
						return ptrCurr;
					}
				}
			}
			//couldn't find match
			return NULL;
		};
		//!Scroll to the desired model index
		void  GtListView::ScrollTo( GtListModelIndex & index )
		{
			//cycle through the indexes and get the points
			if(!m_ptrModel){return;}//safety check
			size_t i, num;
			num = m_ptrModel->CountRows();
			for(i = 0; i < num;i++)
			{
				GtListModelIndex* ptrCurr = m_ptrModel->GetIndex(i);
				if(ptrCurr)
				{
					if(ptrCurr->m_lngRow == index.m_lngRow)
					{
						m_lngVisibleRowStart = i;
						this->UpdateListGeometry();
						this->PostPaint();
					}
				}
			}
			//couldn't find match
			return;
		};
		//!Get the rect of the item at index
		GtRectI  GtListView::GetItemRect( GtListModelIndex & index )
		{
			GtRectI rectNull;
			//cycle through the indexes and get the points
			if(!m_ptrModel){return rectNull;}//safety check
			size_t i, num;
			num = m_ptrModel->CountRows();
			for(i = 0; i < num;i++)
			{
				GtListModelIndex* ptrCurr = m_ptrModel->GetIndex(i);
				if(ptrCurr)
				{
					if(ptrCurr->m_lngRow == index.m_lngRow)
					{
						//note this rect changes when you scroll!!!
						//it is not to be treated as constant
						return ptrCurr->m_objFrame;
					}
				}
			}
			//couldn't find match
			return rectNull;
		};

		//SCROLLING MEMBER FUNCTIONS/////////////////////////
		//Get the pointer to the Vertical scroll bar
		GtVertScrollBar * GtListView::GetVertScrollBar(void)
		{
			return &m_objVertScroll;
		};
		//!Scroll Vertical only
		void GtListView::ScrollVertical(int dy)
		{
			if(!m_ptrModel){return;};//safety check
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
			this->UpdateListGeometry();
			this->PostPaint();	
		};

		//EVENT HANDLING MEMBER FUNCTIONS///////////////////
		//!Custom Event Processing
		int GtListView::HandleEvent(GtEvent * ptrEvent)
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
					GtListModelIndex* ptrCell = this->GetIndexAtPt(pos);
					if(ptrCell)
					{
						m_objSelection.Set_ptrTopLeft(ptrCell);
						m_objSelection.AddSelIndex(ptrCell);
						this->SelectionChanged.Emit();
					};

				}else{
					//range selection
					GtListModelIndex* ptrCell = this->GetIndexAtPt(pos);
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
		int GtListView::OnPaint(GtPainter * painter)
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
			size_t i, numCells;
			numCells = m_ptrModel->CountRows();
			for(i = m_lngVisibleRowStart; i < m_lngVisibleRowEnd; i++)
			{
				GtListModelIndex* ptrCell = m_ptrModel->GetIndex(i);
				if(ptrCell)
				{
					if(m_objSelection.IsSelected(ptrCell))
					{
						painter->Set_objBrush(GtBrush(m_objSelColor));
						painter->GtFillRect(ptrCell->m_objFrame);
					}
					painter->Set_objBrush(m_objBackBrush);
					painter->GtDrawFrame(ptrCell->m_objFrame);
					painter->GtDrawText(ptrCell->m_strText, ptrCell->m_objFrame,0);
				}
			}

			//draw the scroll bar
			this->m_objVertScroll.OnPaint(painter);
			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};		
		//update the row count
		void GtListView::UpdateRowCount()
		{
			
			//MAP GRID IS 0 BASED ARRAY
			size_t i,j, numcells;
			m_lngRowCount = 0;
			if(!m_ptrModel){return;}

			numcells = m_ptrModel->CountRows();
			if(numcells <= 0){return;};//nothing to do

			//get the first cell
			GtListModelIndex* ptrCurr = m_ptrModel->GetIndex(0);
			if(!ptrCurr){return;};//safey check
			m_lngRowCount = ptrCurr->m_lngRow;

			//now cycle through the cells
			for(i = 0; i < numcells; i++)
			{
				ptrCurr = m_ptrModel->GetIndex(i);
				if(ptrCurr)
				{
					if(ptrCurr->m_lngRow > m_lngRowCount){m_lngRowCount = ptrCurr->m_lngRow;};
				}
			}
			//increment because 0 based array
			m_lngRowCount++;
			return;
		};
		//update the list geometries
		void GtListView::UpdateListGeometry()
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

			//CALCULATE CELL RECTS/////////////////////////////////////

			rect.xMin = m_objFrame.xMin;
			rect.xMax = m_objFrame.xMin + defWidth;
			rect.yMin = m_objFrame.yMin;
			rect.yMax = m_objFrame.yMin + defHeight;
			XLast = m_objFrame.xMin;
			YLast = m_objFrame.yMin;
			for(i = 0; i < m_lngRowCount; i++)
			{
				if(currHeight < 25){currHeight = 25;};//min row height
				if(i == 0)
				{  //restart row
					rect.yMin = m_objViewFrame.yMin;
					rect.yMax = m_objViewFrame.yMin + currHeight;
				}else if((i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd))
				{
					//set for next row
					rect.yMin = YLast;
					rect.yMax = rect.yMin + currHeight;
				}

				rect.xMin = m_objViewFrame.xMin;
				rect.xMax = m_objViewFrame.xMax;

				if( (i >= m_lngVisibleRowStart)&&(i <= m_lngVisibleRowEnd) )
				{//then visible cell
					GtListModelIndex* ptrCell = m_ptrModel->GetIndex(i);
					if(ptrCell)
					{
						ptrCell->m_objFrame = (rect);
						ptrCell->m_blnVisible = (true);
					}
				}else{
					//not visible cell
					GtListModelIndex* ptrCell = m_ptrModel->GetIndex(i);
					if(ptrCell)
					{
						ptrCell->m_objFrame = (rectNull);
						ptrCell->m_blnVisible = (false);
					}
				}//end cell type check

				YLast = rect.yMax;
			}//end loop through rows

		};
		//update the scroll geometries
		void GtListView::UpdateScrollGeometry()
		{
			//set up the scroll bars
			GtRectI rectVert, rectHoriz, rectTarget;

			rectVert = m_objFrame;
			rectVert.xMin = rectVert.xMax - 25;
			m_objVertScroll.Set_objFrame(rectVert);

			//set up the viewport
			m_objViewFrame = m_objFrame;
			m_objViewFrame.xMax = rectVert.xMin;

			//set the ranges for the scroll bars

			m_objVertScroll.Set_intMin(0);
			int intVertMax = m_lngRowCount;
			if(intVertMax <= 0){intVertMax = 0;};
			m_objVertScroll.Set_intMax(intVertMax);

			m_objVertScroll.Set_intValue(0);
			this->PostPaint();
			return;
		};

		void GtListView::Set_objFrame(GtRectI & frame)
		{
			GtWidget::Set_objFrame(frame);
			this->UpdateScrollGeometry();	
		};

	//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtListView::SetFocusWidget(GtPoint3DI & pos)
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
			//otherwise grid widget
			return this;
		};
	};//end namespace GtCore

};//end namespace GT