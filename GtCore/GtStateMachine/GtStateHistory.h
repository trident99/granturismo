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

#ifndef GT_STATE_HISTORY_H
#define GT_STATE_HISTORY_H

#include ".\GtState.h"
#include <modHtlContainer.h>

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
		class HTL_DLLAPI GtStateHistory : public GtObject
		{
		public:
			//!Parent set constructor
			GtStateHistory(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtStateHistory(void);

			//SIGNALS/////////////////////////////////
		public:
			//!Signal for when the state is added to the history
			HtlSignal00  AddedState; 
			//!Signal for when the history is cleared
			HtlSignal00  Cleared; 

			//MEMBER FUNCTIONS////////////////////////
		public:
			//! Gets the First GtState pointer in the collection
			GtState* FirstState(void);
			//! Gets the Last GtState pointer in the collection
			GtState* LastState(void);
			//! Gets the GtState pointer at the specified index
			GtState* AtState(size_t index);
			//!Add a GtState to the history
			size_t CountStates(void);
			//!Add a state to the history
			int AddState(GtState * ptrCurrent);
			//!Clears the state history
			int ClearHistory(void);

		protected:

			Htl1DList<GtState*,HTL_BASE_PTR> m_arrStates;

		};//end HtlBase class definition

}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H