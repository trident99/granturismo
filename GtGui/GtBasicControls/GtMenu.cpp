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

#include ".\GtMenu.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtMenu::GtMenu(GtObject* ptrParent)
			:GtAction(ptrParent)
		{
			m_blnShowMenu = false;
			m_intWidth = 50;
			m_ptrSelAction = NULL;
		};

		//!Virtual destructor
		GtMenu::~GtMenu(void)
		{
			this->Clear();
		};

		//!Add an action to the menu
		void GtMenu::AddAction(GtAction* ptrNewAction)
		{
			if(ptrNewAction)
			{
				ptrNewAction->Set_ptrParent(this);
				ptrNewAction->Triggered.SlotConnect(this,&GtMenu::Close);
				this->m_arrSubItems.push_back(ptrNewAction);
			}
			return;
		};

		//!Add an action to the menu with the string name
		void GtMenu::AddAction(std::string strName)
		{
			GtAction* ptrNew = new GtAction(this);
			ptrNew->Set_strName(strName);
			ptrNew->Triggered.SlotConnect(this,&GtMenu::Close);
			this->m_arrSubItems.push_back(ptrNew);
		};

		//!Add a sub menu 
		void GtMenu::AddMenu(GtMenu* ptrNewMenu)
		{
			if(ptrNewMenu)
			{
				ptrNewMenu->Set_ptrParent(this);
				GtAction* ptrNew = dynamic_cast<GtAction*>(ptrNewMenu);
				this->m_arrSubItems.push_back(ptrNew);
			}
			return;
		};

		//!Add the sub menu with the string name
		void GtMenu::AddMenu(std::string strName)
		{
			GtMenu* ptrNewMenu = new GtMenu(this);
			GtAction* ptrNew = dynamic_cast<GtAction*>(ptrNewMenu);
			ptrNew->Set_strName(strName);
			this->m_arrSubItems.push_back(ptrNew);
		};

		//!Add a Separator
		void GtMenu::AddSeparator(void)
		{
			GtAction* ptrNew = new GtAction(this);
			ptrNew->Set_blnSeparator(true);
			this->m_arrSubItems.push_back(ptrNew);
		};

		//!Clear the menu sub items
		void GtMenu::Clear(void)
		{
			size_t i, intNumItems;
			intNumItems = m_arrSubItems.size();
			if(intNumItems <= 0){return;};
			//NOTE this is a Composite collection,
			//so it must delete then clear all subItems
			for(i = 0; i < intNumItems; i++)
			{
				GtAction* ptrCurr = m_arrSubItems.at(i);
				if(ptrCurr)
				{
					delete ptrCurr;
				}
			}
			m_arrSubItems.clear();

		};
		//!Checks to see if the supplied action is a child of this menu
		bool GtMenu::IsChildAction(GtAction* ptrTest)
		{
			size_t i, intNumItems;
			intNumItems = m_arrSubItems.size();
			if(intNumItems <= 0){false;};
			//NOTE this is a Composite collection,
			//so it must delete then clear all subItems
			for(i = 0; i < intNumItems; i++)
			{
				GtAction* ptrCurr = m_arrSubItems.at(i);
				if(ptrCurr == ptrTest)
				{//match
					return true;
				}
				//if sub menu call recursively
				GtMenu* ptrCast = dynamic_cast<GtMenu*>(ptrCurr);
				if(ptrCast)
				{
					bool blnSubCheck = ptrCast->IsChildAction(ptrTest);
					if(blnSubCheck)
					{//then match found
						return true;
					}
				}
			}
			//no matches found
			return false;
			
		};

		bool GtMenu::IsRootMenu(void)
		{
			if(dynamic_cast<GtMenu*>(m_ptrParent))
			{
				//sub menu
				return false;
			}else{
				//root menu, no menu parent
				return true;
			}

		};

		void GtMenu::UpdateMenuVisible(bool blnVisible)
		{
			size_t i, numActs;
			numActs = m_arrSubItems.size();
			if(!blnVisible)
			{
				for(i = 0; i < numActs;i++)
				{
					GtAction* ptrCurr = m_arrSubItems.at(i);
					if(ptrCurr)
					{
						ptrCurr->SetVisible(false);
						GtMenu* ptrCast = dynamic_cast<GtMenu*>(ptrCurr);
						if(ptrCast)
						{
							ptrCast->UpdateMenuVisible(false);
						};
					};
				};
				return;
			}
			//otherwise visible.
			GtPoint3DI posCursor;
			GtRectI rectAct = m_objFrame;
	
				if(IsRootMenu())
				{
					//draw the menu below
					posCursor.x = m_objFrame.xMin;
					posCursor.y = m_objFrame.yMax;
				}else{
					//draw the menu to the right
					posCursor.x = m_objFrame.xMax;
					posCursor.y = m_objFrame.yMin;
				}
				m_rectShadow.xMin = posCursor.x + 4;
				m_rectShadow.yMin = posCursor.y + 4;

				for(i = 0; i < numActs;i++)
				{
					GtAction* ptrCurr = m_arrSubItems.at(i);
					if(ptrCurr)
					{
						rectAct.xMin = posCursor.x;
						rectAct.xMax = posCursor.x + m_intWidth;
						rectAct.yMin = posCursor.y;
						if(ptrCurr->Get_blnSeparator())
						{
							rectAct.yMax = posCursor.y + 5;
						}else{
							rectAct.yMax = posCursor.y + 25;
						};
						m_rectShadow.xMax = rectAct.xMax + 4;
						m_rectShadow.yMax = rectAct.yMax + 4;

						ptrCurr->Set_objFrame(rectAct);
						ptrCurr->SetVisible(true);
						//advance cursor
						posCursor.y = rectAct.yMax;
					}
				}
				return;	
		};

		//!Clear the focus
		void GtMenu::ClearFocus(GtWidget* ptrNewFocus)
		{
			m_blnFocus = false;
			GtAction* ptrCast = dynamic_cast<GtAction*>(ptrNewFocus);

			if(!ptrCast)
			{
				this->Close();
			}else{
				//then action, check if child
				if(!IsChildAction(ptrCast))
				{
					//then not part of this menu tree
					//close the menu
					this->Close();
				}
			}
		}

		//!Close the widget
		void GtMenu::Close()
		{
			//close this menu
			m_blnShowMenu = false;
			//close the parent
			GtMenu * parent = dynamic_cast<GtMenu*>(m_ptrParent);
			if(parent)
			{
				parent->Close();
			}
			this->Closed.Emit();
			this->PostPaint();
			return;
		};
		GtMenu* GtMenu::GetRootMenu(void)
		{
			GtMenu* ptrCast = dynamic_cast<GtMenu*>(m_ptrParent);
			if(ptrCast)
			{
				return ptrCast->GetRootMenu();
			}else{
				return this;
			};

		};
		//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtMenu::SetFocusWidget(GtPoint3DI & pos)
		{
			size_t i, numActs;
			numActs = m_arrSubItems.size();

			if(!m_blnVisible){return NULL;}//safey check

			//need to retrieve the root widget, call the parent
			GtMenu* ptrRoot = this->GetRootMenu();

			GtPoint3DI hoverPos, delta;
			delta = ptrRoot->RequestOffset();

			hoverPos.x = pos.x - delta.x;
			hoverPos.y = pos.y - delta.y;

			GtRectI mnuFrame = this->Get_objFrame();
			if(mnuFrame.Contains(hoverPos))
			{
				return this;
			}
			//safety check on whole menu
			if(!ptrRoot->Get_blnShowMenu())
			{
				return NULL;
			}
			//otherwise check sub items
			for(i = 0; i < numActs; i++)
			{
				GtWidget * ptrCurr = m_arrSubItems.at(i);
				GtWidget * ptrFocus = NULL;
				if(ptrCurr)
				{
					GtRectI actFrame = ptrCurr->Get_objFrame();
					if(actFrame.Contains(hoverPos) && m_blnShowMenu)
					{
						return ptrCurr;
					}
					GtMenu* ptrCast = dynamic_cast<GtMenu*>(ptrCurr);
					if(ptrCast)
					{//the a sub menu, explore that 
						GtWidget* ptrHit = ptrCast->SetFocusWidget(pos);
						if(ptrHit)
						{
							return ptrHit;
						}//end hit check
					}//end menu cast
				}//end current check
			}//end for loop items

			//otherwise try sub widgets
			return GtWidget::SetFocusWidget(pos);
		}
		//!Custom Event Processing
		int GtMenu::HandleEvent(GtEvent * ptrEvent)
		{
	//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{

				m_blnShowMenu = !m_blnShowMenu;
				this->Toggled.Emit(m_blnShowMenu);
				this->UpdateMenuVisible(m_blnShowMenu);
				Triggered.Emit();
				this->PostPaint();
				return 1;
			}

			if(m_blnShowMenu)
			{
				if( (ptrEvent->m_objType == MouseMove)||
					(ptrEvent->m_objType == MouseHover) )
				{
					GtPoint3DI pos, hoverPos, delta;
					pos.x = gRound(ptrEvent->m_objPos.x);
					pos.y = gRound(ptrEvent->m_objPos.y);

					GtMenu* ptrRoot = this->GetRootMenu();
					if(ptrRoot)
					{
						delta = ptrRoot->RequestOffset();
					}

					hoverPos.x = pos.x - delta.x;
					hoverPos.y = pos.y - delta.y;

					size_t i, numActs;
					numActs = m_arrSubItems.size();

					for(i = 0; i < numActs; i++)
					{
						GtAction * ptrCurr = m_arrSubItems.at(i);
						if(ptrCurr)
						{
							if(ptrCurr->Contains(hoverPos))
							{
								ptrCurr->Set_blnHovered(true);
								m_ptrSelAction = ptrCurr;
							}else{
								ptrCurr->Set_blnHovered(false);
							}
						}//end ptrCurr
					}//end loop through actions
					this->PostPaint();
					return 1;
				}//end mouse
			}//end if show menu


			return 0;
		};
		//!Custom Widget Painting
		int GtMenu::OnPaint(GtPainter * painter)
		{
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen oldPen;
			GtBrush oldBrush;
	
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			//draw released mode
			painter->Set_objPen(GtPen(GtColor(160,160,160),SolidLine,1));
			painter->Set_objBrush(m_objBackBrush);
			painter->GtDrawRect(m_objFrame);

			GtPoint3DI pos;
			pos.x = m_objFrame.xMin + 5;
			pos.y = m_objFrame.yMin;
			painter->GtDrawStaticText(m_strText,pos);

			if(!IsRootMenu())
			{
				GtRectI rectTri;
				rectTri = m_objFrame;
				rectTri.xMin = rectTri.xMax - 25;
				painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
				painter->GtDrawTriangleRight(rectTri,5);
			}
			
			if(m_blnShowMenu)
			{

				painter->Set_objBrush(GtBrush(GtColor(50,50,50)));
				painter->GtDrawRect(m_rectShadow);

				painter->Set_objBrush(m_objBackBrush);
				//draw the sub menu items
				size_t i, numActs;
				numActs = m_arrSubItems.size();
				for(i = 0; i < numActs;i++)
				{
					GtAction* ptrCurr = m_arrSubItems.at(i);
					if(ptrCurr)
					{
						ptrCurr->OnPaint(painter);
					}
				}
			}
			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT