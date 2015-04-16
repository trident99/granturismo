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

#ifndef GT_MAIN_WINDOW_H
#define GT_MAIN_WINDOW_H

#include "..\GtBasicControls\GtMenu.h"
#include "..\GtBasicControls\GtProgressBar.h"
#include "..\GtBasicControls\GtStatusBar.h"
#include "..\GtBasicControls\GtToolBar.h"

#include ".\GtDialog.h"
using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtMainWindow : public GtDialog
		{
		public:
			//!Parent set constructor
			GtMainWindow(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtMainWindow(void);

			//MEMBER VARIABLES////////////////////////
			//SIGNALS/////////////////////////////////
		public:
			//MEMBER FUNCTIONS////////////////////////
		public:

			//!Add a Tool Bar
			void  AddToolBar ( GtToolBar * toolbar );
			//!Insert a Tool Bar 
			void  InsertToolBar ( GtToolBar * before, GtToolBar * toolbar );
			//!Remove a Tool Bar
			void  RemoveToolBar ( GtToolBar * toolbar );
			//!Remove ALL Tool Bars
			void ClearToolBars(void);

			//!Get the pointer to the central widget
			GtWidget * GetCentralWidget(void); 
			//!Set the central widget
			void  SetCentralWidget ( GtWidget * widget );
			//!ClearCentral Widget
			void ClearCentralWidget(void);


			//!Get the main menu pointer
			GtMenu *  GetMainMenu(void);
			//!Set the main menu pointer
			void  SetMainMenu( GtMenu * menu ); 
			//!Clear the main menu
			void ClearMainMenu(void);

			//!Get the pointer to the status bar
			GtStatusBar* GetStatusBar(void);
			//!Set the status bar
			void  SetStatusBar ( GtStatusBar * statusbar );
			//!Clear the status bar
			void ClearStatusBar(void);
			//!Set the Status bar message to display for msecs
			void SetMessage(std::string strText,int msecs);

			//!Get the pointer to the progress bar
			GtProgressBar* GetProgressBar(void);
			//!Set the progress bar
			void SetProgressBar(GtProgressBar* progress);
			//!Clear the progress bar
			void ClearProgressBar(void);
			//!Set the progress value
			void SetProgress(int value);

			//INHERITED FUNCTIONS FOR 
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:
			GtWidget* m_ptrCentral;
			//!Pointer to the Main Menu
			GtMenu* m_ptrMainMenu;
			//!Pointer to the toolbars
			Htl1DList<GtToolBar*, HTL_BASE_PTR> m_arrToolBars;
			//!Pointer to the status bar
			GtStatusBar * m_ptrStatus;
			//!Pointer to the main progress bar
			GtProgressBar * m_ptrProgress;

		private:


		};//end HtlBase class definition
		//WndProc function
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	}//end namespace GtCore
}//end namespace GT
#endif //GT_MAIN_WINDOW_H