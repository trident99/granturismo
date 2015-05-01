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

#include ".\GtEventManager.h"
#include ".\GtEventCreator.h"
#include "..\modGtGraphic.h"
#include "..\GtMath\GtBasicMath.h"

namespace GT{

	namespace GtCore{

		//!Default Constructor
		GtEventManager::GtEventManager()
			: HtlHasSlots()
		{
			this->m_ptrFocusWidget = NULL;
			this->m_winID = NULL;
			this->m_ptrMainProc = NULL;
			this->m_ptrPainter = NULL;
			this->m_ptrRootWidget = NULL;
		};

		//!Destructor
		GtEventManager::~GtEventManager()
		{
			if(m_blnRunning)
			{
				this->Set_blnRunning(false);
			}
		};
		//PUBLIC MEMBER FUNCTIONS
		//!Get the pointer to the connected widget
		GtObject* GtEventManager::AtObject(size_t index)
		{
			if((index >= 0) && (index < m_arrObjects.size()))
			{
				return m_arrObjects.at(index);
			}else{
				return NULL;
			}
		};
		//!Register an object with the event manager
		void GtEventManager::RegisterObject(GtObject * ptrObj)
		{
			if(ptrObj)
			{
				this->m_arrObjects.insert(ptrObj,ptrObj);
			}
		};
		//!UN-Register an object with the event manager
		void GtEventManager::UnRegisterObject(GtObject * ptrObj)
		{
			if(ptrObj)
			{
				this->m_arrObjects.erase(ptrObj);
			}
		};

		//!Run the Event Loop
		void GtEventManager::StartMainEventLoop(void)
		{
			this->m_blnRunning = true;

			if(m_ptrMainProc)
			{
				//run the user defined main loop before processing events
				this->m_ptrMainProc();
				return;
			}
			//paint the gui to start
			this->PostPaint();

			while(m_blnRunning)
			{
				MSG currMsg;

				if(!m_blnRunning){return;};
				//while(GetMessage(&winMessage,this->Get_winHandle(),0,0))
				while(PeekMessage(&currMsg,m_winID,0,0,PM_REMOVE))
				{

					if(!m_blnRunning){return;};
					//Queue the message for Gt Processing
					//then there are events to be processed

					GtEvent currEvent;
					currEvent = CreateGtEvent(currMsg);
					this->SetFocusWidget(currEvent);
					GtWidget* ptrFocus = this->GetFocusWidget();
					if(ptrFocus)
					{
						ptrFocus->HandleEvent(&currEvent);
					}
	
					//standard windows processing
					TranslateMessage(&currMsg);
					DispatchMessage(&currMsg);

					//check for quit
					if(currMsg.message == WM_QUIT)
					{
						m_blnRunning = false;
						this->StopMainEventLoop();
						return;
					}

					//process posted events second
					if(!m_blnRunning){return;};
					int numProcessed = 0;
					while((this->CountPostedEvents() > 0)&&(numProcessed < 10))
					{
						Htl1DList<GtEvent,HtlUnknownType>* ptrPostedEvents = this->GetPostedEvents();
						//then there are events to be processed
						GtEvent currEvent;
						currEvent = ptrPostedEvents->front();
						ptrPostedEvents->pop_front();
						this->SetFocusWidget(currEvent);
						GtWidget* ptrFocus = this->GetFocusWidget();
						if(ptrFocus)
						{
							ptrFocus->HandleEvent(&currEvent);
						}else{
							//send event to all registered widgets
							for(size_t i = 0; i < this->CountObjects(); i++)
							{
								GtObject* ptrObj =	this->AtObject(i);
								if(ptrObj)
								{
									ptrObj->HandleEvent(&currEvent);
								}
							}
						}
						//process a max of 10 posted events
						//before going back to system events
						numProcessed++;
					}//end posted event loop

				};//end while loop for peek message
				
			};//end main for loop

		};
		//!Stop the Event Loop
		void GtEventManager::StopMainEventLoop(void)
		{
			this->m_blnRunning = false;
			this->m_winID = NULL;//reset the winID
		};

		//!Post and event for processing
		void GtEventManager::PostEvent(GtEvent evnt)
		{
			m_arrPostedEvents.push_back(evnt);
		};

		//!Force a paint event
		void GtEventManager::PostPaint(void)
		{
			size_t i, numObjs;
			if(!m_ptrPainter){return;};//safety check
			if(!m_ptrRootWidget){return;};//safety check
			if(!m_blnRunning){return;};//shutdown safety check
			
			GtCanvas topCanvas;
			m_rootCanvas.m_frame = m_ptrRootWidget->Get_objFrame();
			m_rootCanvas.m_view = m_rootCanvas.m_frame;
			m_ptrPainter->Set_objViewport(topCanvas.m_frame);
			m_ptrPainter->GtStartCanvas(&m_rootCanvas);
			//invalidate the canvas region
			RECT inval;
			inval.left = topCanvas.m_frame.xMin;
			inval.right = topCanvas.m_frame.xMax;
			inval.top = topCanvas.m_frame.yMin;
			inval.bottom = topCanvas.m_frame.yMax;
			::InvalidateRect(m_winID,&inval,FALSE);
			//paint the object
			m_ptrRootWidget->OnPaint(m_ptrPainter);

			//end the canvas and painting session
			m_ptrPainter->GtEndCanvas();
			
		};
			
		//!Clears the Event Queues
		void GtEventManager::ClearEvents(void)
		{
			m_arrPostedEvents.clear();
		};

		//!Cycles through the widgets
		void GtEventManager::SetFocusWidget(GtEvent evnt)
		{

			if(evnt.m_objType != MouseLeftPress)
			{
				//then not a focus event, no change in focus
				return;
			}
			GtPoint3DI pos;
			pos.x = gRound(evnt.m_objPos.x);
			pos.y = gRound(evnt.m_objPos.y);

			size_t i, numObjs;
			numObjs = m_arrObjects.size();
			for(i = 0; i < numObjs;i++)
			{
				GtWidget* ptrCurr = NULL;
				GtWidget* ptrTest = NULL;
				ptrCurr = dynamic_cast<GtWidget*>(m_arrObjects.at(i));
				if(ptrCurr)
				{
					ptrTest = ptrCurr->SetFocusWidget(pos);
				}
				if(ptrTest)
				{	
					if(m_ptrFocusWidget)
					{//already have a focus, check if change
						if(m_ptrFocusWidget != ptrTest)
						{
							//then changing focus, close the previous
							m_ptrFocusWidget->ClearFocus(ptrTest);
						}
					}
					//set the new focus
					m_ptrFocusWidget = ptrTest;
				}
			}

		};

	};//end namespace GtCore

};//end namespace GT