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

#ifndef GT_DIALOG_H
#define GT_DIALOG_H

#include "..\GtBasicControls\GtFrame.h"
#include <modGtEvent.h>
using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtDialog : public GtFrame
		{
		public:
			//!Parent set constructor
			GtDialog(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtDialog(void);

			//MEMBER VARIABLES////////////////////////
			//!Boolean flag for dialog is running
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnRunning);
			//!Boolean flag for dialog is accepted
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnAccepted);
			//!Sets the object frame
			virtual void Set_objFrame(GtRectI & frame);
			//SIGNALS/////////////////////////////////
		public:
			//!Signal for accepting dialog
			HtlSignal00 Accepted;
			//!Signal for rejecting dialog
			HtlSignal00 Rejected;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Dialog Initialization
			//!This function runs the initialization methods for a dialog
			void InitializeDialog(void);
			//!Initialize the Controls
			virtual void InitializeControls(void);
			//!Initialize the Abstract Item Model Controls
			virtual void InitializeModels(void);
			//!Initialize the Actions
			virtual void InitializeActions(void);
			//!Initialize the Menus
			virtual void InitializeMenus(void);
			//!Initialize the Popup Context Menus
			virtual void InitializeContextMenus(void);


			//!run the dialog GUI and Event Loops
			void StartDialog(void);
			//!Shut down the dialog GUI and Event Loops
			void StopDialog(void);

			//!Slot for handling Minimize event of the title bar
			void OnMinimize(void);
			//!Slot for handling Maximize event of the title bar
			void OnMaximize(void);

			//INHERITED FUNCTIONS FOR
			virtual void Accept(void);
			virtual void Reject(void);
			virtual int Exec(void);

			//Post a paint event
			virtual void PostPaint(void);
			//!Gets the root widget for this structure
			virtual GtWidget* GetRootWidget(void);
			//!Gets the event manager pointer
			virtual GtEventManager* GetEventManager(void);
			//!Hide the widget
			virtual void Hide();
			//!Show the widget
			virtual void Show();
			//!Close the widget
			virtual void Close();
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:
			//This is the painter for the Dialog
			GtPainter* m_ptrPainter;
			//!The event manager for this root widget
			GtEventManager m_objEventManager;
			//!Thread for running the main event loop for the dialog
			HtlThread m_objMainThread;
			//!thread function entry point
			static DWORD RunDialogThread(void* ptrThis);

		};//end GtDialog class definition
		
		//WndProc function
		LRESULT CALLBACK WndDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	}//end namespace GtCore
}//end namespace GT
#endif //GT_MAIN_WINDOW_H