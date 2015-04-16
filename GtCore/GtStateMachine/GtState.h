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

#ifndef GT_STATE_H
#define GT_STATE_H

#include "..\modGtBase.h"

using namespace HTL;

namespace GT
{

	namespace GtCore
	{

		class GtStateTransition;
		//!This is the base object that provides signals slots capability as well as a global unique identifier for the object.
		/*!
		This is the base object that provides signals slots capability as well as a
		global unique identifier for the object. It inherits the HtlBase serialization engine
		*/
		class HTL_DLLAPI GtState : public GtObject
		{
		public:
			//!Parent set constructor
			GtState(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtState(void);

			//MEMBER VARIABLES////////////////////////
			//!Pointer to the beginning source state
			GTOBJECT_MEMVAR_BYVAL(public, GtStateTransition*,  ptrTransition);
			//!Pointer to the ending target state
			GTOBJECT_MEMVAR_BYVAL(public, GtState*,  ptrTarget);


			//SIGNALS/////////////////////////////////
		public:
			//!Signal for when the state is entered
			HtlSignal00  Entered; 
			//!Signal for when the state is exited
			HtlSignal00  Exited; 
			//!Signal for when the state is destroyed
			HtlSignal00  Finished; 

			//MEMBER FUNCTIONS////////////////////////
		public:
			//the function that is executed when entering a state
			virtual int OnEnterState( GtEvent * evnt = 0 );
			//!The function exits the state and provides the pointer to the next state
			virtual GtState* OnExitState( GtEvent * evnt = 0 ); 

		protected:



		};//end HtlBase class definition

}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H