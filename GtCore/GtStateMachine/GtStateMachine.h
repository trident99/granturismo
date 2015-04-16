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

#ifndef GT_STATE_MACHINE_H
#define GT_STATE_MACHINE_H

#include "..\modGtBase.h"
#include ".\GtStateHistory.h"
#include ".\GtStateTransition.h"

using namespace HTL;

namespace GT
{

	namespace GtCore
	{

		//!This is the base object that provides signals slots capability as well as a global unique identifier for the object.
		/*!
		This is the base object that provides signals slots capability as well as a
		global unique identifier for the object. It inherits the HtlBase serialization engine
		*/
		class HTL_DLLAPI GtStateMachine : public GtObject
		{
		public:
			//!Parent set constructor
			GtStateMachine(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtStateMachine(void);

			//MEMBER VARIABLES////////////////////////

			//!Pointer to the ending target state
			GTOBJECT_MEMVAR_BYVAL(public, GtState*,  ptrCurrent);
			//!Pointer to the ending target state
			GTOBJECT_MEMVAR_BYVAL(public, GtState*,  ptrPrevious);

			//SIGNALS/////////////////////////////////
		public:
			//!Signal for when the state is entered
			HtlSignal00  StateChanged; 
			//!Signal for when the state is entered
			HtlSignal00  Finished; 
			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Add a State to the state machine
			int AddState(GtState* ptrState);
			//!Delete a State from the state machine
			int DeleteState( GtState * ptrState);
			//!Delete a State from the state machine by index
			int DeleteState( size_t index);
			//!Delete ALL States
			void DeleteAllStates(void);
			//!GOTO the pointer to the first state
			GtState * FirstState(void);
			//!GOTO the pointer to the last state
			GtState * LastState(void);
			//!Get the number of states
			size_t CountStates(void);
			//!GOTO the next state
			GtState * NextState(void);
			//!GOTO the previous state
			GtState * PreviousState(void);
			//!Get the state history pointer
			GtStateHistory * GetHistoryPtr(void);

		protected:
			//!The collection of States in the state machine
			Htl1DVector<GtState*, HTL_BASE_PTR> m_arrStates;
			//!The state history
			GtStateHistory m_objHistory;
		};//end HtlBase class definition

}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H