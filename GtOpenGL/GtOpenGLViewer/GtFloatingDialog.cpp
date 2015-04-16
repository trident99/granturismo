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

#include ".\GtFloatingDialog.h"
#include ".\GtViewport.h"


namespace GT
{
	namespace GtOpenGL
	{

		GtFloatingDialog::GtFloatingDialog(GtObject* ptrParent)
			: GtDialog(ptrParent)
		{
			m_ptrGtView = NULL;

			//Qt::WindowFlags flags = 0;
			//flags |= Qt::CustomizeWindowHint;//custom window title bar
			//flags |= Qt::WindowTitleHint;//add the window title bar
			//flags |= Qt::WindowMinimizeButtonHint;//add the minimize button
			//flags |= Qt::WindowMaximizeButtonHint;//add the maximize button
			//NO window close button, keep that disabled
			//this->setWindowFlags(flags);


		}

		GtFloatingDialog::~GtFloatingDialog()
		{
			try{
									
				if(m_ptrGtView)
				{
					m_ptrGtView->ViewportClosing.SlotDisconnect(this);
					m_ptrGtView = NULL;
				};
			}catch(...){
				return;
			};
		}
		void  GtFloatingDialog::OnResizeEvent ( GtEvent * ptrEvent )
		{
			if(!ptrEvent){return;};
			try{
				if(m_ptrGtView)
				{
					//QSize objCurrSize = this->size();
					//ui.frmTGLView->resize(objCurrSize);
					//this->m_ptrTGLView->resize(objCurrSize);
				};
			}catch(...){
				return;
			};

		};

		//!Custom Event Processing
		int GtFloatingDialog::HandleEvent(GtEvent * ptrEvent)
		{

			return 0;
		};

		void GtFloatingDialog::OnKeyPressEvent ( GtEvent * ptrEvent )
		{
			//filter out escape and enter
			if(ptrEvent->m_objKey == Key_Escape){return;};
			if(ptrEvent->m_objKey == Key_Return){return;};
			//otherwise pass it to GtDialog
		};

		void GtFloatingDialog::Set_ptrViewport(GtViewport* ptrViewport)
		{
			try{
				if(ptrViewport)
				{
					this->m_ptrGtView = ptrViewport;
					m_ptrGtView->Set_ptrParent(this);
					this->Set_strText(m_ptrGtView->Get_strText());
					//connect the closing signal incase viewport closed out of scope
					m_ptrGtView->ViewportClosing.SlotConnect<GtDialog>(this,&GtDialog::Reject);
				};
			}catch(...){
				return;
			};
		};

		GtViewport* GtFloatingDialog::Get_ptrViewport(void)
		{
			if(m_ptrGtView)
			{
				return m_ptrGtView;
			}else{
				return NULL;
			};
		};

	};//end namespace GtOpenGL
};//end namespace GT