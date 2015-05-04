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

#include ".\GtComboBox.h"
#include ".\GtAction.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtComboBox::GtComboBox(GtObject* ptrParent)
			:GtFrame(ptrParent)
		{
			m_blnShowMenu = false;
			m_intWidth = 100;
		};
			//!Virtual destructor
		GtComboBox::~GtComboBox(void)
		{
			
		};

		void GtComboBox::Set_intCurrIndex(int index)
		{
			if( (index >= 0) && (index < m_arrItems.size()) )
			{
				m_intCurrIndex = index;
				GtAction* ptrCurr = m_arrItems.at(index);
				if(ptrCurr)
				{
					m_strText = ptrCurr->Get_strText();
				}
			}
		};

		//!Add an item to the combo box
		void GtComboBox::AddItem(GtComboBoxItem & item)
		{
			GtAction* ptrNew = new GtAction(this);
			if(ptrNew)
			{
				ptrNew->Set_strText(item.m_strText);
				ptrNew->Set_varData(item.m_varData);
				ptrNew->Set_ptrData(item.m_ptrData);
				ptrNew->Set_objBackBrush(this->m_objBackBrush);
				ptrNew->Triggered.SlotConnect(this,&GtComboBox::CommitSelection);
				m_arrItems.push_back(ptrNew);
			};
		};

		//!Remove an item from the item list
		void GtComboBox::DeleteItem(int index)
		{
			if( (index > 0) && (index < m_arrItems.size()) )
			{
				GtAction * ptrAct = m_arrItems.at(index);
				if(ptrAct)
				{
					ptrAct->Triggered.SlotDisconnect(this);
					delete ptrAct;	
					m_arrItems.erase(index);
				}
			}
		};

		//!Clears all items in the list
		void GtComboBox::DeleteAllItems(void)
		{
			size_t i, numItems;
			numItems = m_arrItems.size();
			for(i = 0; i < numItems; i++)
			{
				GtAction * ptrAct = m_arrItems.at(i);
				if(ptrAct)
				{
					ptrAct->Triggered.SlotDisconnect(this);
					delete ptrAct;	
				}
			}
			m_arrItems.clear();
		};

		//!Returns the number of items in the list
		size_t GtComboBox::CountItems(void)
		{
			return m_arrItems.size();
		};

		//!Item accessor
		GtComboBoxItem GtComboBox::AtItem(int index)
		{
			GtComboBoxItem ret;
			GtAction* ptrSel = m_arrItems.at(index);
			if(ptrSel)
			{
				ret.m_strText = ptrSel->Get_strText();
				ret.m_varData = ptrSel->Get_varData();
				ret.m_ptrData = ptrSel->Get_ptrData();
			}
			return ret;
		};

		//!Item accessor get text
		std::string GtComboBox::AtText(int index)
		{
			GtComboBoxItem ret;
			GtAction* ptrSel = m_arrItems.at(index);
			if(ptrSel)
			{
				ret.m_strText = ptrSel->Get_strText();
				ret.m_varData = ptrSel->Get_varData();
				ret.m_ptrData = ptrSel->Get_ptrData();
			}
			return ret.m_strText;
		};

		//!Item accessor get data
		GtVariant GtComboBox::AtData(int index)
		{
			GtComboBoxItem ret;
			GtAction* ptrSel = m_arrItems.at(index);
			if(ptrSel)
			{
				ret.m_strText = ptrSel->Get_strText();
				ret.m_varData = ptrSel->Get_varData();
				ret.m_ptrData = ptrSel->Get_ptrData();
			}
			return ret.m_varData;
		};

		//!Item accessor get pointer
		void* GtComboBox::AtPtrObj(int index)
		{
			GtComboBoxItem ret;
			GtAction* ptrSel = m_arrItems.at(index);
			if(ptrSel)
			{
				ret.m_strText = ptrSel->Get_strText();
				ret.m_varData = ptrSel->Get_varData();
				ret.m_ptrData = ptrSel->Get_ptrData();
			}
			return ret.m_ptrData;
		};

		void GtComboBox::UpdateMenuVisible(bool blnVisible)
		{
			size_t i, numActs;
			numActs = m_arrItems.size();
			if(!blnVisible)
			{
				for(i = 0; i < numActs;i++)
				{
					GtAction* ptrCurr = m_arrItems.at(i);
					if(ptrCurr)
					{
						ptrCurr->SetVisible(false);
					}
				}
				return;
			}
			//otherwise visible.
			GtPoint3DI posCursor;
			GtRectI rectAct = m_objFrame;
	
			//draw the menu below
			posCursor.x = m_objFrame.xMin;
			posCursor.y = m_objFrame.yMax;

			m_rectShadow.xMin = posCursor.x + 4;
			m_rectShadow.yMin = posCursor.y + 4;

				for(i = 0; i < numActs;i++)
				{
					GtAction* ptrCurr = m_arrItems.at(i);
					if(ptrCurr)
					{
						rectAct.xMin = posCursor.x;
						rectAct.xMax = posCursor.x + m_intWidth;
						rectAct.yMin = posCursor.y;
						rectAct.yMax = posCursor.y + 25;

						m_rectShadow.xMax = rectAct.xMax + 4;
						m_rectShadow.yMax = rectAct.yMax + 4;

						ptrCurr->Set_objFrame(rectAct);
						ptrCurr->SetVisible(true);
						//advance cursor
						posCursor.y = posCursor.y + 25;
					}
				}
				return;	
		};
		//!Commits the temporary index to the current index
		void GtComboBox::CommitSelection(void)
		{
			this->Set_intCurrIndex(m_intTempIndex);
			size_t i, numActs;
			numActs = m_arrItems.size();
			for(i = 0; i < numActs;i++)
			{
				GtAction* ptrCurr = m_arrItems.at(i);
				if(ptrCurr)
				{
					ptrCurr->SetVisible(false);
				}
			}
			this->Close();
		};
		//!Close the widget
		void GtComboBox::Close()
		{
			//close this menu
			m_blnShowMenu = false;
			GtWidget * ptrCast = dynamic_cast<GtWidget*>(m_ptrParent);
			if(ptrCast)
			{
				//clear the top widget request
				ptrCast->SetTopWidget(NULL);
			}
			this->Closed.Emit();
			this->PostPaint();
			return;
		};

		//!Clear the focus
		void GtComboBox::ClearFocus(GtWidget* ptrNewFocus)
		{
			m_blnFocus = false;
			GtAction* ptrCast = dynamic_cast<GtAction*>(ptrNewFocus);

			if(!ptrCast)
			{
				//this->Close();
			}else{
				//remain open
			}
		}

	//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtComboBox::SetFocusWidget(GtPoint3DI & pos)
		{

			size_t i, numActs;
			numActs = m_arrItems.size();
			if(m_blnShowMenu)
			{
				GtPoint3DI hoverPos, delta;
				delta = this->RequestOffset();

				hoverPos.x = pos.x - delta.x;
				hoverPos.y = pos.y - delta.y;

				for(i = 0; i < numActs; i++)
				{
					GtWidget * ptrCurr = m_arrItems.at(i);
					GtWidget * ptrFocus = NULL;
					if(ptrCurr)
					{
						GtRectI actFrame = ptrCurr->Get_objFrame();
						if(actFrame.Contains(hoverPos))
						{
							return ptrCurr;
						}
					}
				}
			}
			//otherwise try sub widgets
			return GtWidget::SetFocusWidget(pos);
		}


		//!Custom Event Processing
		int GtComboBox::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{

				m_blnShowMenu = !m_blnShowMenu;
				this->UpdateMenuVisible(m_blnShowMenu);
				GtWidget * ptrCast = dynamic_cast<GtWidget*>(m_ptrParent);
				if(ptrCast)
				{
					if(m_blnShowMenu)
					{
						//set this as top widget
						ptrCast->SetTopWidget(this);
					}else{
						//clear the top widget request
						ptrCast->SetTopWidget(NULL);
					}
				}

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

					delta = this->RequestOffset();

					hoverPos.x = pos.x - delta.x;
					hoverPos.y = pos.y - delta.y;
					size_t i, numActs;
					numActs = m_arrItems.size();

					for(i = 0; i < numActs; i++)
					{
						GtAction * ptrCurr = m_arrItems.at(i);
						if(ptrCurr)
						{
							if(ptrCurr->Contains(hoverPos))
							{
								m_intTempIndex = i;
								ptrCurr->Set_blnHovered(true);
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
		int GtComboBox::OnPaint(GtPainter * painter)
		{
							//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen valPen, oldPen;
			GtBrush oldBrush;
			
			GtPoint3DI textPos;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			
			painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
			m_rectCombo = m_objFrame;
			m_rectCombo.xMax = m_objFrame.xMin + 25; 
			m_rectCombo.yMax = m_objFrame.yMin + 25;			
			painter->GtDrawRect(m_rectCombo);	

			painter->Set_objFont(m_objFont);
			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);

			m_rectText = m_objFrame;
			m_rectText.xMin = m_rectCombo.xMax; 
			m_rectText.yMax = m_rectCombo.yMax;			
			painter->GtDrawRect(m_rectText);
			painter->GtDrawBevelFrameSunken(m_rectText,2);

			if(!m_blnShowMenu)
			{
				//draw triangles SIDEWAYS
				GtPoint3DI pos;
				GtPolylineI tri;
				painter->GtDrawBevelFrameRaised(m_rectCombo,2);
				painter->Set_objPen(GtPen(GtColor(0,0,0)));
				painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
				painter->GtDrawTriangleRight(m_rectCombo,5);

			}else{
				painter->GtDrawBevelFrameSunken(m_rectCombo,2);
				painter->Set_objPen(GtPen(GtColor(0,0,0)));
				painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
				painter->GtDrawTriangleDown(m_rectCombo,5);
			}
			//Draw the text

			textPos.x = m_rectCombo.xMax + 5;
			textPos.y = m_rectCombo.yMin;
			painter->Set_objPen(m_objPen);
			painter->GtDrawStaticText(m_strText,textPos);


			//draw the menu if necessary
			GtPoint3DI posMenu;
			posMenu.x = m_rectText.xMin;
			posMenu.y = m_rectText.yMax;
			
			if(m_blnShowMenu)
			{

				painter->Set_objBrush(GtBrush(GtColor(50,50,50)));
				painter->GtDrawRect(m_rectShadow);

				painter->Set_objBrush(m_objBackBrush);
				//draw the sub menu items
				size_t i, numActs;
				numActs = m_arrItems.size();
				for(i = 0; i < numActs;i++)
				{
					GtAction* ptrCurr = m_arrItems.at(i);
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