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

#include ".\GtWidget.h"
#include "..\modGtProcess.h"
#include "..\modGtMath.h"

namespace GT
{
	namespace GtCore
	{
		GtWidget* GtWidget::m_ptrTopWidget = NULL;

		//default constructor
		GtWidget::GtWidget(GtObject* ptrParent)
			: GtObject(ptrParent)
			,m_objFont()
		{
			m_strType = "GtWidget";
			//!Boolean flag for has focus
			m_blnFocus = false;
			//!Boolean flag for is modal(true), or modeless(false)
			m_blnModal = true;
			//!Boolean flag for full screen
			m_blnFullScreen = false;
			//!Boolean flag for is active window
			m_blnIsActiveWin = false;
			//!Boolean flag for is minimized
			m_blnMinimized = false;
			//!Boolean flag for is maximized
			m_blnMaximized = false;
			//!Boolean flag for accepts drops from drag operations
			m_blnAcceptsDrops = false;
			//!Boolean flag for autofill background
			m_blnAutoFillBackground = false;

			//!Window ID
			m_winID = NULL;
			//!GtWindowsFlags
			m_intWinFlags = NULL;
			//!Context Menu Policy
			m_objContextPolicy = NoContextMenu;
			//!Focus Policy
			m_objFocusPolicy = NoFocus;

			//STYLESHEET
			//!Integer Paint Order
			m_intPaintOrder = -1;
			//!Integer Tab Order
			m_intTabOrder = -1;

			//GEOMETRY
			//!The minimum height of the widget
			m_intMinHeight = -1;
			//!The maximum height of the widget
			m_intMaxHeight = -1;
			//!The minimum width of the widget
			m_intMinWidth = -1;
			//!The maximum width of the widget
			m_intMaxWidth = -1;
			//!The pointer to the root widget
			m_ptrRoot = NULL;
			//!pointer to the event manager
			m_ptrEvMan = NULL;

			m_ptrTopWidget = NULL;

			m_blnVisible = true;
		};
		//virtual destructor
		GtWidget::~GtWidget(void)
		{
			m_strType.clear();
			m_strText.clear();

			return;
		};
			
		//!Gets the root widget for this structure
		GtWidget* GtWidget::GetRootWidget(void)
		{
			//already set, return it
			if(m_ptrRoot){return m_ptrRoot;};
			//need to retrieve the root widget, call the parent
			GtWidget* ptrCast = dynamic_cast<GtWidget*>(m_ptrParent);
			if(ptrCast)	
			{ 
				m_ptrRoot = ptrCast->GetRootWidget();
				return m_ptrRoot;
			}else{
				return NULL;
			}
			
		};

		//!Gets the event manager pointer
		GtEventManager* GtWidget::GetEventManager(void)
		{
			if(m_ptrEvMan){return m_ptrEvMan;};
			if(!m_ptrRoot)
			{
				this->GetRootWidget();
			}
			//now get the event manager from the root widget
			if(m_ptrRoot)
			{
				m_ptrEvMan = m_ptrRoot->GetEventManager();
				return m_ptrEvMan;
			}else{
				return NULL;
			}
		};

		//!Gets the event manager pointer
		GtPoint3DI GtWidget::RequestOffset(void)
		{
			m_objOffset.Zero();
			if(!m_ptrParent){return m_objOffset;};
			//need to retrieve the root widget, call the parent
			GtWidget* ptrCast = dynamic_cast<GtWidget*>(m_ptrParent);
			if(ptrCast)	
			{ 
				GtPoint3DI pos = ptrCast->RequestOffset();
				GtRectI frameParent = ptrCast->Get_objFrame();
				
				m_objOffset.x = pos.x + frameParent.xMin;
				m_objOffset.y = pos.y + frameParent.yMin;
			}
			return m_objOffset;

		};

		//Post a paint event
		void GtWidget::PostPaint(void)
		{
			if(m_ptrEvMan)
			{
				m_ptrEvMan->PostPaint();
			}else{
				m_ptrEvMan = GetEventManager();
				if(m_ptrEvMan)
				{
					m_ptrEvMan->PostPaint();
				}
			}

		};
		
		//Post a paint event
		void GtWidget::PostEvent(GtEvent evnt)
		{
			if(m_ptrRoot)
			{
				return m_ptrRoot->PostEvent(evnt);
			}else{
				GetRootWidget();
				if(m_ptrRoot)
				{
					m_ptrRoot->PostEvent(evnt);
				}
			}		
		};
		//!Custom Widget Painting
		int GtWidget::OnPaint(GtPainter * ptrPainter)
		{
			if(!m_blnVisible){return 0;};//on off check
			if(!ptrPainter){return 0;};//safety check

			//set local coordinates
			GtPoint3DI origin;
			origin.x = gRound(m_objFrame.xMin);
			origin.y = gRound(m_objFrame.yMin);
			//translate to frame location
			ptrPainter->GtTranslate(origin.x,origin.y);

			bool blnIsTopChild = false;
			size_t i, numSubs;
			numSubs = this->m_arrSubWidgets.size();
			for(i = 0; i < numSubs; i++)
			{
				GtWidget* ptrCurr = m_arrSubWidgets.at(i);
				if(ptrCurr)
				{
					ptrCurr->OnPaint(ptrPainter);
				}
				if(ptrCurr == m_ptrTopWidget)
				{
					blnIsTopChild = true;
				}
			}
			if( (m_ptrTopWidget)&& (blnIsTopChild) )
			{
				m_ptrTopWidget->OnPaint(ptrPainter);
			}
			//translate back
			ptrPainter->GtTranslate(-origin.x,-origin.y);
			return 1;
		};

		//!Activate the window
		void GtWidget::ActivateWindow()
		{	
			SetActiveWindow(m_winID);
		};

		//!Set the visibility of the widget
		void GtWidget::SetVisible( bool blnIsVisible)
		{	
			this->m_blnVisible = blnIsVisible;
			//now set sub widgets
			size_t i, numSubs;
			numSubs = this->m_arrSubWidgets.size();
			for(i = 0; i < numSubs; i++)
			{
				GtWidget* ptrCurr = m_arrSubWidgets.at(i);
				if(ptrCurr)
				{
					ptrCurr->SetVisible(blnIsVisible);
				}
			}
			return;
		};

		//!Set the enabled of the widget
		void GtWidget::SetEnabled( bool blnIsEnabled)
		{	
			this->m_blnEnabled = blnIsEnabled;
			//now set sub widgets
			size_t i, numSubs;
			numSubs = this->m_arrSubWidgets.size();
			for(i = 0; i < numSubs; i++)
			{
				GtWidget* ptrCurr = m_arrSubWidgets.at(i);
				if(ptrCurr)
				{
					ptrCurr->SetEnabled(blnIsEnabled);
				}
			}
			return;
		};

		//!Get the pointer to the parent widget
		GtWidget * GtWidget::GetParentWidget()
		{
			return dynamic_cast<GtWidget*>(m_ptrParent);
		};
		//!Get the sub widget at the x,y position
		GtWidget * GtWidget::SubWidgetAtPos(int x, int y)
		{	
			GtPoint3DI pt(x,y,0);
			size_t i, numSubs;
			bool blnInside = false;
			numSubs = m_arrSubWidgets.size();
			if(numSubs <= 0){return NULL;};
			for(i = 0; i < numSubs; i++)
			{
				GtWidget* ptrCurr = m_arrSubWidgets.at(i);
				if(ptrCurr)
				{
					blnInside = ptrCurr->Get_objFrame().Contains(pt);
				}
				if(blnInside)
				{
					return ptrCurr;
				}
			}
			//otherwise none found
			return NULL;
		};
		//!Get the sub widget at the position
		GtWidget * GtWidget::SubWidgetAtPos(GtPoint3DI & p)
		{	
			size_t i, numSubs;
			bool blnInside = false;
			numSubs = m_arrSubWidgets.size();
			if(numSubs <= 0){return NULL;};
			for(i = 0; i < numSubs; i++)
			{
				GtWidget* ptrCurr = m_arrSubWidgets.at(i);
				if(ptrCurr)
				{
					blnInside = ptrCurr->Get_objFrame().Contains(p);
				}
				if(blnInside)
				{
					return ptrCurr;
				}
			}
			//otherwise none found
			return NULL;
		};
		//!Get the sub widget at the index
		GtWidget * GtWidget::AtSubWidget(size_t index)
		{	
			if((index >= 0)&&(index < m_arrSubWidgets.size()))
			{
				return m_arrSubWidgets.at(index);
			};
			return NULL;
		};

		//!Get the sub widget at the index
		GtWidget * GtWidget::AtSubWidget(std::string strName)
		{
			size_t i, numWidgets;
			if(strName.empty()){return NULL;};//safety check
			numWidgets = m_arrSubWidgets.size();
			for(i = 0; i < numWidgets; i++)
			{
				GtWidget* ptrCurr = m_arrSubWidgets.at(i);
				if(ptrCurr)
				{
					if(strName == ptrCurr->Get_strName())
					{
						return ptrCurr;
					}
				}
			}
			//didnt find name match
			return NULL;

		};



		//!Add a subwidget to the collection
		int GtWidget::AddSubWidget(GtWidget* ptrAdd)
		{	
			if(ptrAdd)
			{
				ptrAdd->Set_ptrParent(this);
				m_arrSubWidgets.push_back(ptrAdd);
				return 1;
			}
			return NULL;
		};
		//!Delete the subwidget with the pointer
		int GtWidget::DeleteSubWidget(GtWidget* ptrDel)
		{	
			if(!ptrDel){return 0;};//safety check
			size_t i, numSubs;
			numSubs = this->m_arrSubWidgets.size();
			if(numSubs <= 0){return 0;};//safety check size
			for(i = 0; i < numSubs; i++)
			{
				if(m_arrSubWidgets.at(i) == ptrDel)
				{
					delete m_arrSubWidgets.at(i);
					m_arrSubWidgets.erase(i);
					return 1;
				}
			}
			return 0;
		};
		//!Delete the sub widget at the index
		int GtWidget::DeleteSubWidget(size_t index)
		{	
			size_t numSubs;
			numSubs = this->m_arrSubWidgets.size();
			if(numSubs <= 0){return 0;};//safety check size
			if((index >= 0) && (index < numSubs))
			{
				delete m_arrSubWidgets.at(index);
				m_arrSubWidgets.erase(index);
				return 1;
			}
			
			return 0;
		};
		//!Delete ALL sub widgets
		int GtWidget::DeleteAllSubWidgets(void)
		{	
			size_t i, numSubs;
			numSubs = this->m_arrSubWidgets.size();
			if(numSubs <= 0){return 0;};//safety check size

			for(i = 0; i < numSubs; i++)
			{
				delete m_arrSubWidgets.at(i);
			}
			m_arrSubWidgets.clear();
			return 0;
		};



		//vector partitioning algorithm
		int WidgetPartition(GtWidgetList * ptrCollection, int iLeft, int iRight)
		{
			if(!ptrCollection){return 0;};
			GtWidget* ptrPivot = ptrCollection->at(iRight);
			if(!ptrPivot){return 0;};
			try{
				while(iLeft < iRight)
				{
					GtWidget * ptrLeft = ptrCollection->at(iLeft);
					GtWidget * ptrRight = ptrCollection->at(iRight);
					if(ptrLeft && ptrRight)
					{
						while(ptrLeft->Get_intPaintOrder() < ptrPivot->Get_intPaintOrder())
						{
							iLeft++;
						}
						while(ptrRight->Get_intPaintOrder() > ptrPivot->Get_intPaintOrder())
						{
							iRight--;
						}
						if(ptrLeft->Get_intPaintOrder()	== ptrRight->Get_intPaintOrder())
						{
							iLeft++;
						}else if (iLeft < iRight){
							//swap objects
							GtWidget* temp = ptrCollection->at(iLeft);
							ptrCollection->at(iLeft) = ptrCollection->at(iRight);
							ptrCollection->at(iRight) = temp;
						}
					}
				}

				return iRight;
			}catch(...){
				return -1;
			}

		};
		//vector quicksort algorithm
		int WidgetQuickSort(GtWidgetList * ptrCollection, int iStartIndex, int iEndIndex)
		{
			try{
				if(!ptrCollection){return 0;};
				//pivot element
				int intSplitPoint;

				if(iStartIndex < iEndIndex)
				{
					//return the position where the pivot belongs
					intSplitPoint = WidgetPartition(ptrCollection,iStartIndex,iEndIndex);
					WidgetQuickSort(ptrCollection,iStartIndex, intSplitPoint - 1);
					WidgetQuickSort(ptrCollection,intSplitPoint + 1, iEndIndex);
				}
				return 1;
			}catch(...){return -1;};
		}

		//!Sort the Composite Collection  - Ascending

		int WidgetSortAscending(GtWidgetList * ptrCollection)
		{
			if(!ptrCollection){return 0;};
			int intRet;
			int intNum = ptrCollection->size();
			intRet = WidgetQuickSort(ptrCollection,0,(intNum - 1));
			return intRet;
		};


		//!Sort the sub widgets by their intPaintOrder
		void GtWidget::SortByOrder(void)
		{	
			WidgetSortAscending(&m_arrSubWidgets);
			return;
		};
		//Get the child widgets bounding rectangle
		GtRectI	GtWidget::SubWidgetsRect()
		{				
			GtWidget* ptrCurr = NULL;
			GtRectI objBounding, objCurrFrame;
			size_t i, numSubs;
			numSubs = m_arrSubWidgets.size();
			if(numSubs <= 0){return GtRectI();};//safety check

			//initialize to first then find bounding box
			ptrCurr = m_arrSubWidgets.at(0);
			if(ptrCurr){objBounding = ptrCurr->Get_objFrame();};
			for(i = 0; i < numSubs; i++)
			{
				ptrCurr = m_arrSubWidgets.at(i);
				if(ptrCurr)
				{
					objCurrFrame = ptrCurr->Get_objFrame();
					if(objCurrFrame.xMin < objBounding.xMin){objBounding.xMin = objCurrFrame.xMin;};
					if(objCurrFrame.xMax > objBounding.xMax){objBounding.xMax = objCurrFrame.xMax;};
					if(objCurrFrame.yMin < objBounding.yMin){objBounding.yMin = objCurrFrame.yMin;};
					if(objCurrFrame.yMax > objBounding.yMax){objBounding.yMax = objCurrFrame.yMax;};
				}
			}
			return objBounding;
		};

		//!Get the height of the widget
		int	GtWidget::GetHeight() const
		{	
			return abs(m_objFrame.yMax - m_objFrame.yMin);
		};
		//!Get the width of the widget
		int	GtWidget::GetWidth() const
		{	
			return abs(m_objFrame.xMax - m_objFrame.xMin);
		};

		void GtWidget::Set_strText(std::string & str)
		{
			m_strText = str;
		};

		void GtWidget::Set_objFrame(GtRectI & frame)
		{
			m_objFrame = frame;
			m_objPos.x = m_objFrame.xMin;
			m_objPos.y = m_objFrame.yMin;
		};

		//!Get the position of the top left corner
		GtPoint3DI	GtWidget::GetPosition()
		{	
			return GtPoint3DI(m_objFrame.xMin,m_objFrame.yMin,0);
		};
		//!Mapping coordinate points///////////////
		GtPoint3DI	GtWidget::mapFromGlobal(const GtPoint3DI & pos)
		{	
			return GtPoint3DI((pos.x - m_objFrame.xMin),(pos.y - m_objFrame.yMin),0);
		};
		GtPoint3DI	GtWidget::mapFromParent(const GtPoint3DI & pos)
		{	
			GtWidget * ptrCast = dynamic_cast<GtWidget*>(m_ptrParent);
			if(ptrCast)
			{
				GtRectI objParentRect = ptrCast->Get_objFrame();
				return GtPoint3DI((pos.x - objParentRect.xMin),(pos.y - objParentRect.yMin),0);
			}
			return GtPoint3DI();
		};
		GtPoint3DI	GtWidget::mapToGlobal(const GtPoint3DI & pos)
		{	
			return GtPoint3DI((m_objFrame.xMin + pos.x),(m_objFrame.yMin + pos.y),0);
		};
		GtPoint3DI	GtWidget::mapToParent(const GtPoint3DI & pos)
		{	
			GtWidget * ptrCast = dynamic_cast<GtWidget*>(m_ptrParent);
			if(ptrCast)
			{
				GtRectI objParentRect = ptrCast->Get_objFrame();
				return GtPoint3DI((objParentRect.xMin + pos.x),(objParentRect.yMin + pos.y),0);
			}
			return GtPoint3DI();
		};
		//!check to see if widget is under current mouse location
		bool GtWidget::IsUnderMouse()
		{		
			POINT p;
			if (GetCursorPos(&p))
			{
				//cursor position now in p.x and p.y
				//This returns the cursor position relative to screen coordinates. Call ScreenToClient to map to window coordinates.
				if (ScreenToClient(m_winID, &p))
				{
					//p.x and p.y are now relative to hwnd's client area
					if((p.x >= m_objFrame.xMin) && (p.x <= m_objFrame.xMax) &&
						(p.y >= m_objFrame.yMin) && (p.y <= m_objFrame.yMax) )
					{
						return true;
					}
				}
			}		
			return false;
		};

		bool  GtWidget::Contains(GtPoint3DI & pos)
		{
			return 	m_objFrame.Contains(pos);
		};

		//!Close the widget
		void GtWidget::Close()
		{
			this->SetVisible(false);
			this->Closed.Emit();
			return;
		};
		//!Hide the widget
		void GtWidget::Hide()
		{	
			this->SetVisible(false);
			return;
		};
		//!Show the widget
		void GtWidget::Show()
		{	
			this->SetVisible(true);
			return;
		};


		//!Focus Policy
		void GtWidget::SetTopWidget(GtWidget* ptrObj)
		{
			if(ptrObj)
			{
				m_ptrTopWidget = ptrObj;
			}
		};
		GtWidget* GtWidget::GetTopWidget(void)
		{
			return m_ptrTopWidget;
		};


		//!Tests and sets the focus widget based on the cursor location provided
		 GtWidget* GtWidget::SetFocusWidget(GtPoint3DI & pos)
		 {
			 GtPoint3DI transPos, offPos;

			 //need to retrieve the root widget, call the parent
			 offPos = this->RequestOffset();
			 transPos.x = pos.x - offPos.x;
			 transPos.y = pos.y - offPos.y;

			 //quick exclusion check
			 if(!m_objFrame.Contains(transPos))
			 {
				 //if top widget active check that 
				 if((m_ptrTopWidget)&& (this != m_ptrTopWidget))
				 {
					return m_ptrTopWidget->SetFocusWidget(pos);
				 }
				 m_blnFocus = false;
				 return NULL;
			 };//point not in frame
			 //Otherwise point inside frame, 
			 //first see if it is a sub widget
			 size_t i, numSubs;
			 numSubs = m_arrSubWidgets.size();
			 if(numSubs <= 0)
			 {//then no sub widgets, this is the focus widget
				 m_blnFocus = true;
				 return this;
			 }
			 //otherwise cycle through sub widgets
			 for(i = 0; i < numSubs; i++)
			 {
				GtWidget* ptrCurr = m_arrSubWidgets.at(i);
				GtWidget* ptrSub = NULL;
				if(ptrCurr)
				{
					ptrSub = ptrCurr->SetFocusWidget(pos);
					if(ptrSub)
					{//then focus found in a sub widget
						m_blnFocus = false;//focus is sub widget not this
						return ptrSub;
					}
				}
			 }
			 //made it through sub widgets without finding focus
			 //so this object is the focus if it is visible
			 if(this->m_blnVisible)
			 {
				 m_blnFocus = true;
				 return this; 
			 }else{
				 return NULL;
			 }
		 };

	};//end namespace GtCore

};//end namespace GT