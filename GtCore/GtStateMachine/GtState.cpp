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

#include ".\GtState.h"
#include ".\GtStateTransition.h"
namespace GT
{
	namespace GtCore
	{

		//default constructor
		GtState::GtState(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtState";
			m_ptrTransition = NULL;
		};
		//virtual destructor
		GtState::~GtState(void)
		{
			Finished.Emit();
			return;
		};
		//the function that is executed when entering a state
		int GtState::OnEnterState( GtEvent * evnt){Entered.Emit(); return 0;}; 

		GtState* GtState::OnExitState( GtEvent * evnt)
		{
			if(m_ptrTransition)
			{
				GtState* ptrNext = m_ptrTransition->Get_ptrTarget();
				if(ptrNext)
				{
					ptrNext->OnEnterState();
					//no transition connecting to another state
					Exited.Emit(); 
					return ptrNext;
				}else{
					return NULL;
				}

			}else{
				//no transition connecting to another state
				return NULL;
			}
		}; 

	};//end namespace GtCore

};//end namespace GT