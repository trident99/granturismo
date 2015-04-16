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


#ifndef GT_EVENT_MANAGER_H
#define GT_EVENT_MANAGER_H

#include "..\GtBase\GtObject.h"
#include "..\GtGraphic\GtWidget.h"
#include ".\GtEvent.h"
#include <modHtlContainer.h>
#include <modHtlThread.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{
		//forward declaration
		class GtPainter;

		//Application function pointer for console applications
		typedef int(*AppFunctionPtr)(void);

		class HTL_DLLAPI GtEventManager : public HtlHasSlots 
		{
		public:
			//!Default Constructor
			GtEventManager();

			//!Destructor
			~GtEventManager();

			//PUBLIC MEMBER FUNCTIONS
		public:
			//!boolean flag to control running of event loop
			HTLMEMVAR_BYVAL_STYLE1(public, AppFunctionPtr, ptrMainProc);
			//!boolean flag to control running of event loop
			HTLMEMVAR_BYVAL_STYLE1(public, bool, blnRunning);
			//!enum representation of the event class type
			HTLMEMVAR_BYVAL_STYLE1(public, HWND, winID);
			//!enum representation of the event class type
			HTLMEMVAR_BYVAL_STYLE1(public, GtPainter*, ptrPainter);
			//!Check to see if it is running still
			bool IsRunning(void){return m_blnRunning;};

			//!Count the number of connected widgets
			size_t CountObjects(void){return m_arrObjects.size();};
			//!Get the pointer to the connected widget
			GtObject* AtObject(size_t index);
			//!Register an object with the event manager
			void RegisterObject(GtObject * ptrObj);
			//!UN-Register an object with the event manager
			void UnRegisterObject(GtObject * ptrObj);

			//!Run the System Event Listener Loop
			void StartMainEventLoop(void);
			//!Stop the System Event Listener Loop
			void StopMainEventLoop(void);

			//!MAIN EVENT PROCESSING LOOP
			//!Post and event for processing
			void PostEvent(GtEvent evnt);
			//!Force a paint event
			void PostPaint(void);
			//!Clears the Event Queues
			void ClearEvents(void);

			Htl1DList<GtEvent,HtlUnknownType>* GetPostedEvents(void){return &m_arrPostedEvents;};

			int CountPostedEvents(void){return m_arrPostedEvents.size();};

			//Focus related 
			GtWidget* GetFocusWidget(void){return m_ptrFocusWidget;};
			//!Cycles through the widgets
			void SetFocusWidget(GtEvent evnt);


			//PRIVATE MEMBER VARIABLES
		protected:
			//!The list of the objects to be notified of events
			HtlListMap<GtObject*,HTL_BASE_PTR,GtObject*,HTL_BASE_PTR> m_arrObjects;

			//!The list of events to be processed
			Htl1DList<GtEvent,HtlUnknownType> m_arrPostedEvents;
			//!The FOCUS widget
			GtWidget* m_ptrFocusWidget;

			
		};//end GtEventManager

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_MANAGER_H