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

#include ".\GtStateMachine.h"

namespace GT
{
	namespace GtCore
	{

		//default constructor
		GtStateMachine::GtStateMachine(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtStateMachine";
			this->m_ptrCurrent = NULL;
			this->m_ptrPrevious = NULL;
		};
		//virtual destructor
		GtStateMachine::~GtStateMachine(void)
		{
			Finished.Emit();
			return;
		};
		//!Add a State to the state machine
		int GtStateMachine::AddState(GtState* ptrState)
		{
			if(ptrState)
			{
				m_arrStates.push_back(ptrState);
				return 1;
			};
			return 0;
		};
		//!Delete a State from the state machine
		int GtStateMachine::DeleteState( GtState * ptrState)
		{
			Htl1DVector<GtState*, HTL_BASE_PTR>::Iterator iter;
			if(ptrState)
			{
				for(iter = m_arrStates.begin(); iter != m_arrStates.end(); ++iter)
				{
					if(ptrState == *iter)
					{
						m_arrStates.erase(iter);
						return 1;
					}
				}
			}
			return 0;
		};
		//!Delete a State from the state machine by index
		int GtStateMachine::DeleteState( size_t index)
		{
			int i = 0;
			Htl1DVector<GtState*, HTL_BASE_PTR>::Iterator iter;

			for(iter = m_arrStates.begin(); iter != m_arrStates.end(); ++iter)
			{
				if(i = index)
				{
					m_arrStates.erase(iter);
					return 1;
				}
				i++;
			}
			return 0;
		};
		//!Delete ALL States
		void GtStateMachine::DeleteAllStates(void)
		{
			m_arrStates.clear();
		};
		//!GOTO the pointer to the first state
		GtState * GtStateMachine::FirstState(void)
		{
			m_ptrPrevious = m_ptrCurrent;
			if(m_arrStates.size() > 0)
			{
				m_ptrCurrent = m_arrStates.front();
				m_objHistory.AddState(m_ptrCurrent);
				return m_ptrCurrent;
			}
			//otherwise return NULL
			return NULL;
		};
		//!GOTO the pointer to the last state
		GtState * GtStateMachine::LastState(void)
		{
			m_ptrPrevious = m_ptrCurrent;
			if(m_arrStates.size() > 0)
			{
				m_ptrCurrent = m_arrStates.back();
				m_objHistory.AddState(m_ptrCurrent);
				return m_ptrCurrent;
			}
			//otherwise return NULL
			return NULL;
		};
		//!Get the number of states
		size_t GtStateMachine::CountStates(void)
		{
			return m_arrStates.size();
		};
		//!GOTO the next state
		GtState * GtStateMachine::NextState(void)
		{
			m_ptrPrevious = m_ptrCurrent;
			if(m_arrStates.size() > 0)
			{
				m_ptrCurrent = m_ptrCurrent->OnExitState();
				if(m_ptrCurrent)
				{
					m_ptrCurrent->OnEnterState();
					m_objHistory.AddState(m_ptrCurrent);
					return m_ptrCurrent;
				}else{
					return NULL;
				}
			}
			//otherwise return NULL
			return NULL;
		};
		//!GOTO the previous state
		GtState * GtStateMachine::PreviousState(void)
		{
			m_ptrPrevious = m_ptrCurrent;
			if(m_arrStates.size() > 0)
			{
				m_ptrCurrent = m_objHistory.LastState();
				m_ptrCurrent->OnEnterState();
				m_objHistory.AddState(m_ptrCurrent);
				return m_ptrCurrent;
			}
			//otherwise return NULL
			return NULL;
		};
		//!Get the state history pointer
		GtStateHistory * GtStateMachine::GetHistoryPtr(void)
		{
			return &m_objHistory;
		};

	};//end namespace GtCore

};//end namespace GT