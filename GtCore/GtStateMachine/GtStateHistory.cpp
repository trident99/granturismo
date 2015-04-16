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

#include ".\GtStateHistory.h"
#include ".\GtStateTransition.h"
namespace GT
{
	namespace GtCore
	{

		//default constructor
		GtStateHistory::GtStateHistory(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtStateHistory";
		};
		//virtual destructor
		GtStateHistory::~GtStateHistory(void)
		{
			this->ClearHistory();
			return;
		};
		//! Gets the First GtState pointer in the collection
		GtState* GtStateHistory::FirstState(void)
		{
			if(m_arrStates.size() > 0)
			{
				return m_arrStates.front();
			}else{
				return NULL;
			}
		};
		//! Gets the Last GtState pointer in the collection
		GtState* GtStateHistory::LastState(void)
		{
			if(m_arrStates.size() > 0)
			{
				return m_arrStates.back();
			}else{
				return NULL;
			}
		};
		//! Gets the GtState pointer at the specified index
		GtState* GtStateHistory::AtState(size_t index)
		{
			if((index >= 0)&&(index < m_arrStates.size()))
			{
				return m_arrStates.at(index);
			}else{
				return NULL;
			};
		};
		//!Add a GtState to the history
		size_t GtStateHistory::CountStates(void)
		{
			return m_arrStates.size();
		};
		//!Add a state to the history
		int GtStateHistory::AddState(GtState * ptrCurrent)
		{
			if(ptrCurrent)
			{
				m_arrStates.push_back(ptrCurrent);
				this->AddedState.Emit();
				return 1;
			}else{
				return 0;
			}
		};
		//!Clears the state history
		int GtStateHistory::ClearHistory(void)
		{
			m_arrStates.clear();
			this->Cleared.Emit();
			return 1;
		};

	};//end namespace GtCore

};//end namespace GT