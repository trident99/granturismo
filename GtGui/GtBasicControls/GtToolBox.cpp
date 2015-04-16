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

#include ".\GtToolBox.h"
#include ".\GtTabPage.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtToolBox::GtToolBox(GtObject* ptrParent)
			:GtFrame(ptrParent)
		{
			m_strType = "GtToolBox";
			m_intSelTab = 0;
		};

		//!Virtual destructor
		GtToolBox::~GtToolBox(void)
		{

		};

		//MEMBER VARIABLES////////////////////////

		void GtToolBox::SetSelTab(int index)
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
				this->UpdateGeometry();
			}
			return;
		};

		//MEMBER FUNCTIONS////////////////////////
		//!Get the pointer to the tab page
		GtTabPage* GtToolBox::AtTabPage(int index)
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
		GtTabPage* GtToolBox::AtTabPage(std::string strName)
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

		//!Add a tab page
		void GtToolBox::AddTabPage(GtTabPage* ptrPage)
		{
			if(ptrPage)
			{
				m_arrPages.push_back(ptrPage);
				this->UpdateGeometry();
			}
		};

		//!Remove a tab page
		void GtToolBox::RemoveTabPage(int index)
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
		void GtToolBox::RemoveAllTabPages(void)
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
			m_arrPageRects.clear();
			m_intSelTab = 0;
			//didnt find name match

			return;
		};
		//!Get the rect of the tab page that the 
		GtRectI GtToolBox::AtTabPageRect(int index)
		{
			size_t i, numPages;
			numPages = m_arrPageRects.size();
			if((index >= 0)&&(index < numPages))
			{
				return m_arrPageRects.at(index);
			}
			//illegal index
			return NULL;


		};
		//!Update the rectangle geometries based on what tab is selected
		void GtToolBox::UpdateGeometry(void)
		{
			size_t i, numTabs;
			if(m_arrPages.size() <= 0){return;};
			numTabs = m_arrPages.size();
			m_arrPageRects.clear();

			int intYPos = m_objFrame.yMin;
			for(i = 0; i < numTabs; i++)
			{
				if(m_intSelTab != i)
				{
					//the normal tab
					GtRectI rectTab;
					rectTab = m_objFrame;
					rectTab.yMin = intYPos;
					intYPos += 25;
					rectTab.yMax = intYPos ;
					m_arrPageRects.push_back(rectTab);
				}else{
					//the normal tab
					GtRectI rectTab;
					rectTab = m_objFrame;
					rectTab.yMin = intYPos;
					intYPos += 25;
					rectTab.yMax = intYPos ;
					m_arrPageRects.push_back(rectTab);

					//frame for the controls
					m_objViewFrame = m_objFrame;
					m_objViewFrame.yMin = intYPos;
					int delta = (numTabs - i) * 25;
					m_objViewFrame.yMax -= delta;

					GtTabPage* ptrSelTab = AtTabPage(i);
					if(ptrSelTab)
					{
						GtRectI rect;
						rect.xMin = m_objViewFrame.xMin- m_objFrame.xMin;
						rect.xMax = m_objViewFrame.Width();
						rect.yMin = m_objViewFrame.yMin- m_objFrame.yMin;
						rect.yMax = rect.yMin + (m_objFrame.Height() - (numTabs * 25) );
						ptrSelTab->Set_objFrame(rect);
					}
					intYPos = m_objViewFrame.yMax;

				}//end selection check
			}//end for loop
			return;
		};

		//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtToolBox::SetFocusWidget(GtPoint3DI & pos)
		{
			size_t i, numTabs;
			if(m_arrPages.size() <= 0){return 0;};
			numTabs = m_arrPages.size();
			//check the viewframe
			if(m_objViewFrame.Contains(pos))
			{
				GtTabPage* ptrCurr = m_arrPages.at(m_intSelTab);
				if(ptrCurr)
				{
					return ptrCurr->SetFocusWidget(pos);	
				}else{
					return NULL;
				}
			}
			if(m_objFrame.Contains(pos))
			{
				return this;
			}
			//not in focus
			return NULL;
		};

		//!Custom Event Processing
		int GtToolBox::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				size_t i, numTabs;
				if(m_arrPages.size() <= 0){return 0;};
				numTabs = m_arrPages.size();

				GtPoint3DI pos;
				pos.x = gRound(ptrEvent->m_objPos.x);
				pos.y = gRound(ptrEvent->m_objPos.y);
				for(i = 0; i < numTabs; i++)
				{
					GtRectI rectTab = m_arrPageRects.at(i);
					if(rectTab.Contains(pos))
					{
						this->SetSelTab(i);
						this->PostPaint();
					}
				}
				return 1;
			}
			return 0;
		};
		//!Custom Widget Painting
		int GtToolBox::OnPaint(GtPainter * painter)
		{
			size_t i, numTabs;
			if(m_arrPages.size() <= 0){return 0;};
			numTabs = m_arrPages.size();

			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen oldPen;
			GtBrush oldBrush;
			//INITIALIZE PENS AND BRUSHES

			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			GtTabPage* ptrCurrTab = NULL;
			for(i = 0; i < numTabs; i++)
			{
				if(m_intSelTab != i)
				{
					ptrCurrTab = AtTabPage(i);
					//draw released mode
					painter->Set_objPen(m_objPen);
					painter->Set_objBrush(m_objBackBrush);
					GtRectI tabRect = m_arrPageRects.at(i);
					painter->GtDrawRoundedRect(tabRect,10);

					GtPoint3DI pos;
					pos.x = tabRect.xMin + 5;
					pos.y = tabRect.yMin;
					if(ptrCurrTab)
					{
						ptrCurrTab->SetVisible(false);
						std::string strTab = ptrCurrTab->Get_strText();
						painter->GtDrawStaticText(strTab,pos);
					}
				}else{
					ptrCurrTab = AtTabPage(i);
					//draw released mode
					//draw pressed mode
					painter->Set_objPen(GtPen(GtColor(0,0,255),SolidLine,2));
					painter->Set_objBrush(GtBrush(GtColor(250,250,120)));	
					GtRectI tabRect = m_arrPageRects.at(i);
					painter->GtDrawRoundedRect(tabRect,10);

					GtPoint3DI pos;
					pos.x = tabRect.xMin + 5;
					pos.y = tabRect.yMin;
					if(ptrCurrTab)
					{
						ptrCurrTab->SetVisible(true);
						std::string strTab = ptrCurrTab->Get_strText();
						painter->GtDrawStaticText(strTab,pos);
						//draw the tab page
						GtPoint3DI origin;
						origin.x = gRound(m_objFrame.xMin);
						origin.y = gRound(m_objFrame.yMin);
						//translate to frame location
						painter->GtTranslate(origin.x,origin.y);

						ptrCurrTab->OnPaint(painter);

						painter->GtTranslate(-origin.x,-origin.y);
					}

				}//end selection check
			}//end for loop

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};

	};//end namespace GtCore

};//end namespace GT