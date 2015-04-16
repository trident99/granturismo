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

#include ".\GtTabBar.h"
#include ".\GtTabPage.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtTabBar::GtTabBar(GtObject* ptrParent)
			:GtFrame(ptrParent)
		{
			m_strType = "GtTabBar";
			m_intTabWidth = 50;
			m_intFirstVisible = 0;
			m_intSelTab = 0;
		};

		//!Virtual destructor
		GtTabBar::~GtTabBar(void)
		{

		};

		//MEMBER VARIABLES////////////////////////

		void GtTabBar::SetSelTab(int index)
		{
			size_t i, numPages;
			GtTabPage* ptrCurr = NULL;
			numPages = m_arrPages.size();
			if((index >= 0)&&(index < numPages))
			{
				this->m_intSelTab = index;

				for(i = 0; i < numPages;i++)
				{//clear the board
					ptrCurr = m_arrPages.at(i);
					if(ptrCurr)
					{
						ptrCurr->SetVisible(false);
					}
				}
				//activate the selected tab
				ptrCurr = m_arrPages.at(index);
				ptrCurr->SetVisible(true);
				//emit changed signal and trigger a redraw
				this->TabChanged.Emit();
				this->PostPaint();
			}
			return;
		};

		//MEMBER FUNCTIONS////////////////////////
		//!Get the pointer to the tab page
		GtTabPage* GtTabBar::AtTabPage(int index)
		{
			size_t i, numPages;
			numPages = m_arrPages.size();
			if((index >= 0)&&(index < numPages))
			{
				return m_arrPages.at(index);
			}
			//illegal index
			return NULL;
		};

		//!Get the pointer to the tab page
		GtTabPage* GtTabBar::AtTabPage(std::string strName)
		{
			size_t i, numPages;
			if(strName.empty()){return NULL;};//safety check
			numPages = m_arrPages.size();
			for(i = 0; i < numPages; i++)
			{
				GtTabPage* ptrCurr = m_arrPages.at(i);
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
		//!Get the pointer to the tab page
		GtTabPage* GtTabBar::GetSelTabPage(void)
		{
			return AtTabPage(m_intSelTab);
		};

		//!Add a tab page
		void GtTabBar::AddTabPage(GtTabPage* ptrPage)
		{
			if(ptrPage)
			{
				m_arrPages.push_back(ptrPage);
				this->UpdateGeometry();
			}
		};

		//!Remove a tab page
		void GtTabBar::RemoveTabPage(int index)
		{
			size_t i, numPages;
			numPages = m_arrPages.size();
			if((index >= 0)&&(index < numPages))
			{
				GtTabPage* ptrRem = m_arrPages.at(index);
				if(ptrRem)
				{
					delete ptrRem;
					m_arrPages.erase(index);
				}
			}
			this->UpdateGeometry();
			return;
		};

		//!Remove All tab pages
		void GtTabBar::RemoveAllTabPages(void)
		{
			size_t i, numPages;
			if(m_arrPages.size() <= 0){return;};//safety check
			numPages = m_arrPages.size();
			for(i = 0; i < numPages; i++)
			{
				GtTabPage* ptrCurr = m_arrPages.at(i);
				if(ptrCurr)
				{
					delete ptrCurr;
				}
			}
			m_arrPages.clear();
			this->UpdateGeometry();
			//didnt find name match
			return;
		};

		//!Get the rect of the actual tab at page
		GtRectI GtTabBar::AtTabPageRect(int index)
		{
			GtRectI rectNull;
			size_t i, numPages;
			numPages = m_arrTabRects.size();
			if((index >= 0)&&(index < numPages))
			{
				return m_arrTabRects.at(index);
			}
			//illegal index
			return rectNull;
		}

		void GtTabBar::IncrementTabVisible(void)
		{
			if(m_arrPages.size() <= 0)
			{
				m_intFirstVisible = 0;
				this->UpdateGeometry();
				this->PostPaint();
				return;
			}
			m_intFirstVisible++;
			if(m_intFirstVisible >= m_arrPages.size())
			{
				m_intFirstVisible = m_arrPages.size() - 1;
			}
			this->UpdateGeometry();
			this->PostPaint();
			return;
		};
		void GtTabBar::DecrementTabVisible(void)
		{
			if(m_arrPages.size() <= 0)
			{
				m_intFirstVisible = 0;
				this->UpdateGeometry();
				this->PostPaint();
				return;
			}
			m_intFirstVisible--;
			if(m_intFirstVisible <= 0)
			{
				m_intFirstVisible = 0;
			}
			this->UpdateGeometry();
			this->PostPaint();
			return;
		};


		//!Update the tab geometry based on which index is visible first
		void GtTabBar::UpdateGeometry(void)
		{
			size_t i, numTabs;
			//calculate the main rects
			m_rectTabIncr = m_objFrame;
			m_rectTabDecr = m_objFrame;
			m_rectTabBar = m_objFrame;
			m_objViewFrame = m_objFrame;

			//decrement button
			m_rectTabDecr.xMax = m_rectTabDecr.xMin + 25;
			m_rectTabDecr.yMax = m_rectTabDecr.yMin + 25;
			//increment button
			m_rectTabIncr.xMin = m_rectTabIncr.xMax - 25;
			m_rectTabIncr.yMax = m_rectTabIncr.yMin + 25;
			//
			m_rectTabBar.xMin = m_rectTabDecr.xMax;
			m_rectTabBar.xMax = m_rectTabIncr.xMin;
			m_rectTabBar.yMax = m_rectTabBar.yMin + 25;
			//tab page view frame
			m_objViewFrame.yMin = m_rectTabBar.yMax;

			//reset the tab boxes
			int intTabCursor = 0;
			numTabs = m_arrPages.size();
			m_arrTabRects.clear();
			for(i = 0; i < numTabs; i++)
			{
				GtRectI rectTab;
				if (i >= m_intFirstVisible)
				{
					rectTab.xMin = m_rectTabBar.xMin + (intTabCursor * m_intTabWidth);
					rectTab.xMax = m_rectTabBar.xMin + ((intTabCursor + 1) * m_intTabWidth);
					rectTab.yMin = m_rectTabBar.yMin;
					rectTab.yMax = m_rectTabBar.yMax;
					intTabCursor++;
				}
				m_arrTabRects.push_back(rectTab);
				GtTabPage* ptrPage = this->AtTabPage(i);
				if(ptrPage)
				{
					GtRectI rect;
					rect.xMin = 0;
					rect.xMax = m_objViewFrame.Width();
					rect.yMin = 25;
					rect.yMax = m_objViewFrame.Height();
					ptrPage->Set_objFrame(rect);
					//ptrPage->Set_objFrame(m_objViewFrame);
				}
			}

		};
		//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtTabBar::SetFocusWidget(GtPoint3DI & pos)
		{

			if(m_objViewFrame.Contains(pos))
			{
				GtTabPage* ptrCurrPage = this->AtTabPage(m_intSelTab);
				if(ptrCurrPage)
				{
					return ptrCurrPage->SetFocusWidget(pos);
				}
			}
			//otherwise try sub widgets
			return GtWidget::SetFocusWidget(pos);
		}
		//!Custom Event Processing
		int GtTabBar::HandleEvent(GtEvent * ptrEvent)
		{
			size_t i, numTabs;
			//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				int intCurrSel = m_intSelTab;

				GtPoint3DI pos;
				pos.x = gRound(ptrEvent->m_objPos.x);
				pos.y = gRound(ptrEvent->m_objPos.y);

				if(m_rectTabDecr.Contains(pos))
				{
					this->DecrementTabVisible();
					return 1;
				}
				if(m_rectTabIncr.Contains(pos))
				{
					this->IncrementTabVisible();
					return 1;
				}

				numTabs = m_arrPages.size();
				for(i = 0; i < numTabs; i++)
				{
					GtRectI rectTab;
					rectTab = m_arrTabRects.at(i);
					if((rectTab.Contains(pos))&&(i != m_intSelTab))
					{//then change in tab selection
						this->SetSelTab(i);
						return 1;
					}
				}//end loop through tabs
				
			}//end left mouse press
			return 0;
		};
		//!Custom Widget Painting
		int GtTabBar::OnPaint(GtPainter * painter)
		{
			//HRGN clip = ::CreateRectRgn(50, 50, 100, 100);
			//::SelectClipRgn(context, clip);
			//::Rectangle(context, 0, 0, 50, 50);
			size_t i, numTabs;
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen oldPen;
			GtBrush oldBrush;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);
			painter->GtDrawRect(m_rectTabBar);
						//draw normal
			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);
			painter->GtDrawRect(m_rectTabDecr);
			painter->GtDrawRect(m_rectTabIncr);

			painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
			painter->GtDrawTriangleLeft(m_rectTabDecr,5);
			painter->GtDrawTriangleRight(m_rectTabIncr,5);

			numTabs = m_arrPages.size();
			for(i = 0; i < numTabs; i++)
			{
				GtRectI rectTab;
				GtPoint3DI textPos;
				if (i >= m_intFirstVisible)
				{
					if(i == m_intSelTab)
					{
						//draw pressed mode
						painter->Set_objPen(GtPen(GtColor(0,0,255),SolidLine,2));
						painter->Set_objBrush(GtBrush(GtColor(250,250,120)));
					}else{
						//draw normal
						painter->Set_objPen(m_objPen);
						painter->Set_objBrush(m_objBackBrush);
					}
					rectTab = m_arrTabRects.at(i);
					if(rectTab.xMax < m_rectTabIncr.xMin)
					{	
						//then it fits, draw it
						painter->GtDrawRoundedRect(rectTab,10);
						textPos.x = rectTab.xMin + 5;
						textPos.y = rectTab.yMin;
						GtTabPage* ptrSelTab = this->AtTabPage(i);
						if(ptrSelTab)
						{
							std::string strTab = ptrSelTab->Get_strText();
							painter->GtDrawStaticText(strTab,textPos);
						}
					}


				}//end first visible

				if(i == m_intSelTab)
				{

					GtPoint3DI origin;
					origin.x = gRound(m_objFrame.xMin);
					origin.y = gRound(m_objFrame.yMin);
					//translate to frame location
					painter->GtTranslate(origin.x,origin.y);

					//painter->Set_objPen(GtPen(SolidLine,GtColor(0,0,255),2));
					//painter->Set_objBrush(m_objBackBrush);
					//painter->GtDrawRect(m_objViewFrame);

					GtTabPage* ptrSelTab = AtTabPage(m_intSelTab);
					if(ptrSelTab)
					{
						ptrSelTab->OnPaint(painter);
					}
					painter->GtTranslate(-origin.x,-origin.y);

				}//end is selected tab


			}//end for loop through tabs

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT