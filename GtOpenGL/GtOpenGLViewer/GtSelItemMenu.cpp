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

#include ".\GtSelItemMenu.h"
#include ".\GtViewport.h"

#include "..\GtOpenGLModel\GtCadObject.h"
#include "..\GtOpenGLModel\GtCadLayer.h"
#include "..\GtOpenGLModel\GtPartModel.h"

#include <modGtEvent.h>

namespace GT
{

	namespace GtOpenGL
	{

		GtSelItemMenu::GtSelItemMenu(GtObject* ptrParent)
			: GtMenu(ptrParent)
		{
			//clear the object listing
			m_ptrPartModel = NULL;

			this->InitializeMenu();
		};

		GtSelItemMenu::~GtSelItemMenu()
		{
			//clear the menu
			this->Clear();
			//clear the object listing
			m_ptrPartModel = NULL;
		};


		void GtSelItemMenu::Set_ptrPartModel(GtPartModel * ptrPartModel)
		{
			if(ptrPartModel)
			{
				m_ptrPartModel = ptrPartModel;
			}else{
				m_ptrPartModel = NULL;
			};
			return;
		};

		void GtSelItemMenu::ClearPartModelPtr(void)
		{
			m_ptrPartModel = NULL;
		};

		void GtSelItemMenu::AddItems(std::vector<GtCadObject*> & arrItems)
		{
			int i, intNumItems;
			if(arrItems.size() > 0)
			{
				intNumItems = arrItems.size();
				for(i = 0; i < intNumItems;i++)
				{
					GtCadObject* ptrCurrItem = arrItems.at(i);
					if(ptrCurrItem)
					{
						GtAction* ptrNewItemAction = new GtAction(this);
						std::string str = ptrCurrItem->Get_strName();
						//GtStringToWString(strWName, ptrCurrItem->Get_strName());
						ptrNewItemAction->Set_strText(str);
						ptrNewItemAction->Set_objGUID(ptrCurrItem->Get_objGUID());
						ptrNewItemAction->Set_ptrData((void*)ptrCurrItem);
						this->AddAction(ptrNewItemAction);
					};//end item safety check
				};//end for loop through items
			};//end item container size
			return;
		};

		void GtSelItemMenu::AddItem(GtCadObject* ptrItem)
		{
			if(ptrItem)
			{
				GtAction* ptrNewItemAction = new GtAction(this);
				std::string str = ptrItem->Get_strName();
				//GtStringToWString(strWName, ptrItem->Get_strName());
				ptrNewItemAction->Set_strText(str);
				ptrNewItemAction->Set_objGUID(ptrItem->Get_objGUID());
				ptrNewItemAction->Set_ptrData((void*)ptrItem);
				this->AddAction(ptrNewItemAction);
			};//end item safety check
			return;
		};

		void GtSelItemMenu::InitializeMenu(void)
		{
			//connect(this,SIGNAL(hovered( QAction *)),this,SLOT(HighlightSelectedItem ( QAction * ) ) );
			//connect(this,SIGNAL(triggered( QAction *)),this,SLOT(HighlightSelectedItem ( QAction * ) ) );

		};

		void GtSelItemMenu::HighlightSelectedItem (  HtlGUID128 & objSelGUID )
		{
			//safety checks
			if(!m_ptrPartModel){return;};

			//otherwise get action GUID and find match in item list.
			m_ptrPartModel->ClearSelection();

			GtCadObject* ptrSelItem = (GtCadObject*)(m_ptrSelAction->Get_ptrData());
			if(ptrSelItem)
			{
				ptrSelItem->Set_blnSelected(true);
			}
			return;
		};

		int GtSelItemMenu::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};
			GtMenu::HandleEvent(ptrEvent);

			if(m_blnShowMenu)
			{
				if( (ptrEvent->m_objType == MouseMove)||
					(ptrEvent->m_objType == MouseHover) )
				{
					this->HighlightSelectedItem(m_ptrSelAction->Get_objGUID());
					this->PostPaint();
					return 1;
				}//end mouse
			}//end if show menu

			return 0;
		};

	};//end namespace GtOpenGL
};//end namespace GT