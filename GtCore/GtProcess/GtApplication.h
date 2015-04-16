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

#ifndef GT_CORE_APPLICATION_H
#define GT_CORE_APPLICATION_H

#include "..\GtCoreLibRefs.h"
#include "..\modGtBase.h"
#include "..\modGtEvent.h"
using namespace HTL;

namespace GT
{

	namespace GtCore
	{


		//Application function pointer for console applications
		typedef int(*AppFunctionPtr)(void);

		class GtEvent;
		//!
		/*
		The GtApplication class is the class for running both console and gui GT Applications.
		*/
		class HTL_DLLAPI GtApplication : public GtObject
		{
		private:
			//The Constructor is private to force the user to use the singleton initialization function
			//!Parent set constructor
			GtApplication(int argc, char *argv);
			//!Virtual destructor
			virtual ~GtApplication(void);

			//operator overloads

		public:
			//MEMBER VARIABLES////////////////////////

			//!Pointer to the console main function loop
			GTOBJECT_MEMVAR_BYVAL(public, AppFunctionPtr, ptrMainProc);
			//!Pointer to the parent object
			GTOBJECT_MEMVAR_BYVAL(public, GtObject*, ptrWindow);
			//!String name for the object
			GTOBJECT_MEMVAR_BYREF(public, std::string, strName);
			//!String name for the object
			GTOBJECT_MEMVAR_BYREF(public, std::string, strAppVersion);
			//!String name for the object
			GTOBJECT_MEMVAR_BYREF(public, std::string, strOrganizationName);
			//!String name for the object
			GTOBJECT_MEMVAR_BYREF(public, std::string, strDomain);
			//SIGNALS/////////////////////////////////
		public:
			//!Signal for when the object is destroyed
			HtlSignal00 QuitApplication; 
			//!Signal that the applicaiton is entering the core loop function
			HtlSignal00 EnterCoreLoop;
			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Get the Arg C
			int Get_intArgC(void);
			//!Get the Arg V character string
			char* Get_chrArgV(void);
			//!Get the string Application Directory Path
			std::string Get_strAppDirPath(void);
			//!Get the Application current PID
			ulong Get_intAppPID(void);

			void Set_winID(HWND handle);
			//!Core Application Singleton Creation
			static void GtApplicationInit(int argc, char *argv);
			//!Static member function to get the Application Instance Pointer
			static GtApplication * GetAppInstancePtr();
			//!Get the pointer to the singleton event manager
			GtEventManager * GetEventManagerPtr();

			//!Execute the application main loop
			int Execute(void);
			//!Quit the Application
			static void Quit(void);
				
			//!Forceably clear the event buffers
			void ClearEvents();
			//!Does the application have events pending
			bool HasPendingEvents();
			//!Post an event
			void PostEvent( GtEvent & evnt);
			//!Send an event to a specific object
			bool SendEvent(GtObject * receiver, GtEvent * evnt);

			void RegisterHandle(HWND handle, GtObject* ptrObj);

			GtObject* GetHandleObject(HWND handle);

			void ClearHandleMap(void);

		protected:
			int m_intArgC;
			char* m_chrArgV;
			ulong m_intAppPID;
			std::string m_strAppDirPath;
			//!The one and only event manager
			GtEventManager m_objEventManager;
			HWND m_winID;
			//!A pointer map to this applications handle objects
			HtlListMap<HWND,HtlUnknownType,GtObject*,HTL_BASE_PTR> m_arrHandleObjects;
		};//end HtlBase class definition

}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H