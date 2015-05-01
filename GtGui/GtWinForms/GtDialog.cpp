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

#include ".\GtDialog.h"
#include ".\GtMainWindow.h"
#include <modGtProcess.h>
#include <modGtGraphic.h>
namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtDialog::GtDialog(GtObject* ptrParent)
			: GtFrame(ptrParent)
		{
			m_strType = "GtDialog";
			m_strText = "GtDialog";
			m_blnVisible = true;
			//register the dialog for painting and 
			this->m_objEventManager.RegisterObject(this);
			m_ptrRoot = this;

			this->m_objMainThread.Set_ptrThreadFunc(GtDialog::RunDialogThread);
			this->m_objMainThread.Set_ptrParam(this);
			this->m_objMainThread.init();
			this->m_objMainThread.start();
			//wait for the thread to get caught up
			Sleep(500);

			//register with Application HWND server 
			GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
			if(ptrApp)
			{
				ptrApp->RegisterHandle(m_winID,this);
			}

		};
		//virtual destructor
		GtDialog::~GtDialog(void)
		{

			UnregisterClass((LPCSTR)"GtDialog",GetModuleHandle(NULL));
			if(m_winID)
			{
				DestroyWindow(m_winID);
				m_winID = NULL;
			}
			//register with event 
			
		};
		void GtDialog::Set_objFrame(GtRectI & frame)
		{
			GtWidget::Set_objFrame(frame);
			//now sync the window
			RECT rect;
			GetWindowRect(m_winID, &rect);
			SetWindowPos(m_winID,HWND_TOP,rect.left,rect.top,
				frame.Width(),frame.Height(),SWP_SHOWWINDOW);
			this->PostPaint();
		};

		//!Gets the root widget for this structure
		GtWidget* GtDialog::GetRootWidget(void)
		{
			return this;
		};
		//!Gets the event manager pointer
		GtEventManager* GtDialog::GetEventManager(void)
		{
			return &m_objEventManager;
		};



		//!This function runs the initialization methods for a dialog
		void GtDialog::InitializeDialog(void)
		{
			//!Initialize the Controls
			this->InitializeControls();
			//!Initialize the Abstract Item Model Controls
			this->InitializeModels();
			//!Initialize the Actions
			this->InitializeActions();
			//!Initialize the Menus
			this->InitializeMenus();
			//!Initialize the Popup Context Menus
			this->InitializeContextMenus();

		};
		//!Initialize the Controls
		void GtDialog::InitializeControls(void){};
		//!Initialize the Abstract Item Model Controls
		void GtDialog::InitializeModels(void){};
		//!Initialize the Actions
		void GtDialog::InitializeActions(void){};
		//!Initialize the Menus
		void GtDialog::InitializeMenus(void){};
		//!Initialize the Popup Context Menus
		void GtDialog::InitializeContextMenus(void){};

		//Post a paint event
		void GtDialog::PostPaint(void)
		{
			m_objEventManager.PostPaint();
		};

			//!Accepting Dialog
		void GtDialog::Accept(void )
		{
			m_blnAccepted = true;
			this->Accepted.Emit();
			this->Close();
			return;
		};
		//!Rejecting Dialog
		void GtDialog::Reject(void)
		{
			m_blnAccepted = false;
			this->Rejected.Emit();
			this->Close();
			return;
		}; 
		//!Execute the Dialog
		int GtDialog::Exec(void)
		{
			m_blnRunning = true;
			if(m_blnModal)
			{
				//run MODAL
				//disable parent 
				this->Show();

				while(m_blnRunning){};//spin until close

				if(m_blnAccepted)
				{
					//EnableWindow(m_winParentID, TRUE);
					this->Close();
					return 1;//Accepted
				}else{
					//EnableWindow(m_winParentID, TRUE);
					this->Close();
					return 0;//Rejected
				}

			}else{
				this->Show();
				return 1;
			}
			return 0;
		}; 


		//!Slot for handling Minimize event of the title bar
		void GtDialog::OnMinimize(void)
		{
			m_blnMinimized = true;
			m_blnMaximized = false;
		};
		//!Slot for handling Maximize event of the title bar
		void GtDialog::OnMaximize(void)
		{
			m_blnMinimized = false;
			m_blnMaximized = true;
		};

		//!thread function entry point
		DWORD GtDialog::RunDialogThread(void* ptrThis)
		{
			GtDialog* ptrCast = static_cast<GtDialog*>(ptrThis);
			if(ptrCast)
			{
				ptrCast->StartDialog();
			}	
			return 1;
		};

		//!run the dialog GUI and Event Loops
		void GtDialog::StartDialog(void)
		{
			//Set up window class
			WNDCLASS wnd;
			wnd.cbClsExtra = 0;
			wnd.cbWndExtra = 0;
			wnd.hCursor = LoadCursor(0, IDC_ARROW);
			wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
			wnd.lpszMenuName = 0;
			wnd.style = CS_OWNDC;
			wnd.hbrBackground = 0;
			wnd.lpfnWndProc = WndDialogProc;
			wnd.hInstance = GetModuleHandle(NULL);
			wnd.lpszClassName = (LPCSTR)"GtDialog";

			//Register window class
			RegisterClass(&wnd);

			
			this->m_winID = CreateWindow(
				"GtDialog",      /* Classname */
				"Windows App",       /* Title Text */
				(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS),  /* default window */
				CW_USEDEFAULT,        /* Windows decides the position */
				CW_USEDEFAULT,        /* where the window ends up on the screen */
				100,                  /* The programs width */
				100,                  /* and height in pixels */
				HWND_DESKTOP,         /* The window is a child-window to desktop */
				NULL,                 /* No menu */
				GetModuleHandle(NULL), /* Program Instance handler */
				NULL                  /* No Window Creation data */
				);

			ShowWindow(m_winID,SW_HIDE);
			UpdateWindow(m_winID);

			//create the painter for this dialog
			m_ptrPainter = new GtPainterGDI();
			m_ptrPainter->Set_winID(this->m_winID);
			m_ptrPainter->GtBeginPainting();
			//set the event managers painter
			this->m_objEventManager.Set_ptrRootWidget(this);
			this->m_objEventManager.Set_ptrPainter(m_ptrPainter);

			//start listening in on windows
			this->m_objEventManager.Set_blnRunning(true);
			this->m_objEventManager.Set_winID(this->m_winID);
			this->m_objEventManager.StartMainEventLoop();
			
			//exited main event loop
			//shut down the painter
			if(m_ptrPainter)
			{
				m_ptrPainter->GtEndPainting();
				delete m_ptrPainter;
				m_ptrPainter = NULL;
			}

			return;

		};
		//!Shut down the dialog GUI and Event Loops
		void GtDialog::StopDialog(void)
		{
			this->m_blnRunning = false;
			this->m_objEventManager.StopMainEventLoop();
		};

		//!Hide the widget
		void GtDialog::Hide()
		{
			ShowWindow(m_winID,SW_HIDE);
			UpdateWindow(m_winID);
		};
		//!Show the widget
		void GtDialog::Show()
		{
			ShowWindow(m_winID,SW_SHOW);
			UpdateWindow(m_winID);
			this->PostPaint();
		};
		//!Close the widget
		void GtDialog::Close()
		{
			this->Hide();
			this->StopDialog();
			Sleep(100);//wait for thread to finish
			int z = 10;
		};

		//INHERITED FUNCTIONS FOR EVENT HANDLING AND PAINTING
		//!Custom Event Processing
		int GtDialog::HandleEvent(GtEvent * ptrEvent)
		{
			return 1;	
		};

		//!Custom Widget Painting
		int GtDialog::OnPaint(GtPainter * ptrPainter)
		{
			if(!m_blnVisible){return 0;};
			//safety check
			if(!ptrPainter){return 0;};
			//paint the main frame first
			GtFrame::OnPaint(ptrPainter);

			return 1;
		};		



//WndProc function
LRESULT CALLBACK WndDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
	//case WM_MOVE:
    case WM_PAINT:
        {			
			//local paint to diffuse infinite paint calls
			HDC ptrHDC;
			PAINTSTRUCT ptrPaint;						
			ptrHDC = ::BeginPaint(hWnd, &ptrPaint);
			::EndPaint(hWnd, &ptrPaint);

			GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
			if(ptrApp)
			{
				GtDialog* ptrDiag = dynamic_cast<GtDialog*>(ptrApp->GetHandleObject(hWnd));
				if(ptrDiag)
				{
					ptrDiag->PostPaint();
				}
			}

            return 0;
		}
	case WM_CLOSE:
		{			
		GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
			if(ptrApp)
			{
				GtDialog* ptrDiag = dynamic_cast<GtDialog*>(ptrApp->GetHandleObject(hWnd));
				if(ptrDiag)
				{
					//check to see if main window
					GtMainWindow* ptrCast = dynamic_cast<GtMainWindow*>(ptrDiag);
					if(ptrCast)
					{
						ptrCast->Close();
						GtEventManager* ptrAppEvMan = ptrApp->GetEventManagerPtr();
						if(ptrAppEvMan)
						{	
							ptrAppEvMan->Set_blnRunning(false);
							ptrAppEvMan->StopMainEventLoop();
							Sleep(1000);//wait for event thread to be terminated naturally
							ptrAppEvMan->ClearEvents();
							return 0;
						};
					}

					//if normal dialog then check if modal
					if(ptrDiag->Get_blnModal())
					{
						ptrDiag->Close();
					}else{
						ptrDiag->Hide();
					}
				}
			}
			return 0;
			break;
		}
	case WM_DESTROY:
		{			
			//PostQuitMessage(0);
			return 0;
			break;
		}

    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}


	};//end namespace GtCore

};//end namespace GT