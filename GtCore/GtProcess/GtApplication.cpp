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

#include ".\GtApplication.h"

namespace GT
{
	namespace GtCore
	{
		//!GLOBAL POINTER TO APPLICATION SINGLETON
		GtApplication* g_ptrApplication = NULL;
		GtEventManager* g_ptrEventManager = NULL;

		//!Parent set constructor
		GtApplication::GtApplication(int argc, char *argv)
		{
			this->m_intArgC = argc;
			this->m_chrArgV = argv;

			this->m_ptrMainProc = NULL;
			this->m_ptrWindow = NULL;
			this->m_winID = NULL;

			//get the processID
			this->m_intAppPID = GetCurrentProcessId();
			//NEED CODE FOR APPLICATION FILE NAME AND PATH
			//QFileInfo(qAppFileName()).filePath()
		};
		//!Virtual destructor
		GtApplication::~GtApplication(void)
		{
			this->ClearEvents();
			g_ptrApplication = NULL;
			g_ptrEventManager = NULL;
		};

		//!Get the Arg C
		int GtApplication::Get_intArgC(void)
		{
			return m_intArgC;
		};
		//!Get the Arg V character string
		char* GtApplication::Get_chrArgV(void)
		{
			return m_chrArgV;
		};
		//!Get the string Application Directory Path
		std::string GtApplication::Get_strAppDirPath(void)
		{
			return m_strAppDirPath;
		};
		//!Get the Application current PID
		ulong GtApplication::Get_intAppPID(void)
		{
			return m_intAppPID;
		};

		void GtApplication::Set_winID(HWND handle)
		{
			this->m_winID = handle;
			this->m_objEventManager.Set_winID(handle);
		};

		//!Core Application Singleton Creation
		void GtApplication::GtApplicationInit(int argc, char *argv)
		{
			if(g_ptrApplication){return;};//only call once
			//haven't made application singleton yet
			g_ptrApplication = GetAppInstancePtr();
			g_ptrEventManager = g_ptrApplication->GetEventManagerPtr();
			
		};
		//!Static member function to get the Application Instance Pointer
		GtApplication * GtApplication::GetAppInstancePtr()
		{
			static GtApplication mySingletonApp(0, 0);
			g_ptrApplication = &mySingletonApp;
			return g_ptrApplication;
		};
		//!Get the pointer to the singleton event manager
		GtEventManager * GtApplication::GetEventManagerPtr()
		{
			return &m_objEventManager;
		};

		//!Execute the application main loop
		int	GtApplication::Execute(void)
		{
			this->m_objEventManager.Set_blnRunning(true);
			this->m_objEventManager.Set_ptrMainProc(this->m_ptrMainProc);
			this->m_objEventManager.Set_winID(NULL);
			this->m_objEventManager.StartMainEventLoop();//start listening in on windows
			return 1;
		};
		//!Quit the Application
		void GtApplication::Quit(void)
		{

			GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
			if(ptrApp)
			{
				GtEventManager* ptrEvMan = ptrApp->GetEventManagerPtr();
				if(ptrEvMan)
				{	
					ptrEvMan->Set_blnRunning(false);
					ptrEvMan->StopMainEventLoop();
					Sleep(2000);//wait for event thread to be terminated naturally
					ptrEvMan->ClearEvents();
				};
				//delete ptrApp;
				g_ptrApplication = NULL;
				g_ptrEventManager = NULL;
			}
			return;

		};

		//!Forceably clear the event buffers
		void GtApplication::ClearEvents()
		{
			this->m_objEventManager.ClearEvents();
		};
		//!Does the application have events pending
		bool GtApplication::HasPendingEvents()
		{
			int intTotal= m_objEventManager.CountPostedEvents();
			return (intTotal > 0);
		};
		//!Post an event
		void GtApplication::PostEvent( GtEvent & evnt)
		{
			m_objEventManager.PostEvent(evnt);
			return;
		};
		//!Send an event to a specific object
		bool GtApplication::SendEvent(GtObject * receiver, GtEvent * evnt)
		{
			if((receiver)&&(evnt))
			{
				receiver->HandleEvent(evnt);
				return true;
			}
			return false;
		};

		void GtApplication::RegisterHandle(HWND handle, GtObject* ptrObj)
		{
			if(handle && ptrObj)
			{
				m_arrHandleObjects.insert(handle,ptrObj);
			};
		};

		GtObject* GtApplication::GetHandleObject(HWND handle)
		{
			size_t num = m_arrHandleObjects.size();
			if(handle && (num > 0))
			{
				HtlTreeNode<HWND,GtObject*> * iter;
				iter = m_arrHandleObjects.find(handle);
				if(iter)
				{
					return iter->value();
				}else{
					return NULL;
				}
			}
			return NULL;
		};

		void GtApplication::ClearHandleMap(void)
		{
			m_arrHandleObjects.clear();
		};



	};//end namespace GtCore

};//end namespace GT