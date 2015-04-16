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

#include ".\GtMainWindow.h"
#include <modGtProcess.h>

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtMainWindow::GtMainWindow(GtObject* ptrParent)
			: GtDialog(ptrParent)
		{
			m_strType = "GtMainWindow";
			m_ptrCentral = NULL;
			//!Pointer to the Main Menu
			m_ptrMainMenu = NULL;
			//!Pointer to the status bar
			m_ptrStatus = NULL;
			//!Pointer to the main progress bar
			m_ptrProgress = NULL;
		};
		//virtual destructor
		GtMainWindow::~GtMainWindow(void)
		{
			//UnregisterClass(L"GtMainWindow",GetModuleHandle(NULL));
			if(m_winID)
			{
				DestroyWindow(m_winID);
				m_winID = NULL;
			}
			//register with event 
			
		};

		//!Add a Tool Bar
		void  GtMainWindow::AddToolBar ( GtToolBar * toolbar )
		{
			if(toolbar)
			{
				m_arrToolBars.push_back(toolbar);
			};
		};
		//!Insert a Tool Bar 
		void  GtMainWindow::InsertToolBar ( GtToolBar * before, GtToolBar * toolbar )
		{
			return;
		};
		//!Remove a Tool Bar
		void  GtMainWindow::RemoveToolBar ( GtToolBar * toolbar )
		{
			size_t i, numBars;
			numBars = m_arrToolBars.size();
			if(numBars <= 0){return;}//safety check
			
			for(i = 0; i < numBars;i++)
			{
				GtToolBar* ptrCurr = m_arrToolBars.at(i);
				if(ptrCurr == toolbar)
				{
					delete toolbar;
					m_arrToolBars.erase(i);
					return;
				}
			}
			return;
		};
		//!Remove ALL Tool Bars
		void GtMainWindow::ClearToolBars(void)
		{
			size_t i, numBars;
			numBars = m_arrToolBars.size();
			if(numBars <= 0){return;}//safety check

			for(i = 0; i < numBars;i++)
			{
				GtToolBar* ptrCurr = m_arrToolBars.at(i);
				delete ptrCurr;
			}
			m_arrToolBars.clear();
			return;
		};

		//!Get the pointer to the central widget
		GtWidget * GtMainWindow::GetCentralWidget(void)
		{
			if(m_ptrCentral)
			{
				return this->m_ptrCentral;
			}else{
				return NULL;
			};
		};
		//!Set the central widget
		void  GtMainWindow::SetCentralWidget ( GtWidget * widget )
		{
			if(!widget){return;}//saftey check
			if(m_ptrCentral)
			{	//delete the existing
				delete m_ptrCentral;
				m_ptrCentral = NULL;
			}
			m_ptrCentral = widget;
			return;
		};
		//!ClearCentral Widget
		void GtMainWindow::ClearCentralWidget(void)
		{
			if(m_ptrCentral)
			{	//delete the existing
				delete m_ptrCentral;
				m_ptrCentral = NULL;
			}
		};


		//!Get the main menu pointer
		GtMenu *  GtMainWindow::GetMainMenu(void)
		{
			if(m_ptrMainMenu)
			{
				return m_ptrMainMenu;
			}else{
				return NULL;
			}
		};
		//!Set the main menu pointer
		void  GtMainWindow::SetMainMenu( GtMenu * menu )
		{
			if(!menu){return;}//saftey check
			if(m_ptrMainMenu)
			{	//delete the existing
				delete m_ptrMainMenu;
				m_ptrMainMenu = NULL;
			}
			m_ptrMainMenu = menu;
			return;
		};
		//!Clear the main menu
		void GtMainWindow::ClearMainMenu(void)
		{
			if(m_ptrMainMenu)
			{	//delete the existing
				delete m_ptrMainMenu;
				m_ptrMainMenu = NULL;
			}
		};

		//!Get the pointer to the status bar
		GtStatusBar* GtMainWindow::GetStatusBar(void)
		{
			if(m_ptrStatus)
			{
				return m_ptrStatus;
			}else{
				return NULL;
			}
		};
		//!Set the status bar
		void  GtMainWindow::SetStatusBar ( GtStatusBar * statusbar )
		{
			if(!statusbar){return;}//saftey check
			if(m_ptrStatus)
			{	//delete the existing
				delete m_ptrStatus;
				m_ptrStatus = NULL;
			}
			m_ptrStatus = statusbar;
			return;
		};
		//!Clear the status bar
		void GtMainWindow::ClearStatusBar(void)
		{
			if(m_ptrStatus)
			{	//delete the existing
				delete m_ptrStatus;
				m_ptrStatus = NULL;
			}
		};
		//!Set the Status bar message to display for msecs
		void GtMainWindow::SetMessage(std::string strText,int msecs)
		{
			m_ptrStatus->SetMessage(strText, msecs);
		};

		//!Get the pointer to the progress bar
		GtProgressBar* GtMainWindow::GetProgressBar(void)
		{
			if(m_ptrProgress)
			{
				return m_ptrProgress;
			}else{
				return NULL;
			}
		};
		//!Set the progress bar
		void GtMainWindow::SetProgressBar(GtProgressBar* progress)
		{
			if(!progress){return;}//saftey check
			if(m_ptrProgress)
			{	//delete the existing
				delete m_ptrProgress;
				m_ptrProgress = NULL;
			}
			m_ptrProgress = progress;
			return;
		};
		//!Clear the progress bar
		void GtMainWindow::ClearProgressBar(void)
		{
			if(m_ptrProgress)
			{	//delete the existing
				delete m_ptrProgress;
				m_ptrProgress = NULL;
			}
		};
		//!Set the progress value
		void GtMainWindow::SetProgress(int value)
		{
			m_ptrProgress->Set_intValue(value);
		};

		//INHERITED FUNCTIONS FOR EVENT HANDLING AND PAINTING
		//!Custom Event Processing
		int GtMainWindow::HandleEvent(GtEvent * ptrEvent)
		{
			return 1;	
		};

		//!Custom Widget Painting
		int GtMainWindow::OnPaint(GtPainter * ptrPainter)
		{
			if(!m_blnVisible){return 0;};
			//safety check
			if(!ptrPainter){return 0;};
			//paint the main frame first
			GtFrame::OnPaint(ptrPainter);
			//set the frame for the title bar then render it
			GtRectI menuRect, statusRect, progressRect,centralRect;
			menuRect.xMin = m_objFrame.xMin;
			menuRect.xMax = m_objFrame.xMax;
			menuRect.yMin = m_objFrame.yMin;
			menuRect.yMax = m_objFrame.yMin + 25;//pixels
			if(m_ptrMainMenu)
			{
				m_ptrMainMenu->Set_objFrame(menuRect);
				m_ptrMainMenu->OnPaint(ptrPainter);
			}

			centralRect.xMin = m_objFrame.xMin;
			centralRect.xMax = m_objFrame.xMax;
			centralRect.yMin = menuRect.yMax;
			centralRect.yMax = m_objFrame.yMax - 25;
			if(m_ptrCentral)
			{
				m_ptrCentral->Set_objFrame(centralRect);
				m_ptrCentral->OnPaint(ptrPainter);
			}

			statusRect.xMin = m_objFrame.xMin;
			statusRect.xMax = m_objFrame.xMin + (long)((double)m_objFrame.Width() / 2.0f) ;
			statusRect.yMin = centralRect.yMax;
			statusRect.yMax = m_objFrame.yMax;
			if(m_ptrStatus)
			{
				m_ptrStatus->Set_objFrame(statusRect);
				m_ptrStatus->OnPaint(ptrPainter);
			}

			progressRect.xMin = statusRect.xMax;
			progressRect.xMax = m_objFrame.xMax;
			progressRect.yMin = centralRect.yMax;
			progressRect.yMax = m_objFrame.yMax;
			if(m_ptrProgress)
			{
				m_ptrProgress->Set_objFrame(progressRect);
				m_ptrProgress->OnPaint(ptrPainter);
			}

			return 1;
		};		


//WndProc function
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
	//case WM_MOVE:
    case WM_PAINT:
        {
			GtWidget objTemp;
			objTemp.PostPaint();
			//local paint to diffuse infinite paint calls
			HDC ptrHDC;
			PAINTSTRUCT ptrPaint;						
			ptrHDC = ::BeginPaint(hWnd, &ptrPaint);
			::EndPaint(hWnd, &ptrPaint);
            return 0;
		}
	case WM_CLOSE:
		{			
			GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
			if(ptrApp)
			{
				GtEventManager* ptrEvMan = ptrApp->GetEventManagerPtr();
				if(ptrEvMan)
				{	
					ptrEvMan->Set_blnRunning(false);
				};
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