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

#include ".\GtEvent.h"


namespace GT{

	namespace GtCore{

		//!Default Constructor
		GtEvent::GtEvent()
		{
			this->m_strType = "EventBase";
			this->m_objType = EventBase;
			this->m_objKey = (GtKey)0;
			this->m_objModifiers = (GtKeyboardModifier)0;
			this->m_intVal = 0;
			this->m_dblVal = 0.0f;
			this->m_objPos.Zero();
			this->m_objDelta.Zero();
			this->m_objRect.Zero();
			this->m_ptrObj = NULL;
		};

		//!Destructor
		GtEvent::~GtEvent()
		{
			this->m_strType.clear();
			this->m_objPos.Zero();
			this->m_objDelta.Zero();
			this->m_objRect.Zero();
			this->m_ptrObj = NULL;
		};

		//Assignment Operator Overload
		GtEvent & GtEvent::operator = (GtEvent & rhs)
		{
			if(this != &rhs)
			{
				//then not self referenceing, make the assignment
				this->m_strType = rhs.m_strType;
				this->m_objType = rhs.m_objType;
				this->m_objKey = rhs.m_objKey;
				this->m_objModifiers = rhs.m_objModifiers;
				this->m_intVal = rhs.m_intVal;
				this->m_dblVal = rhs.m_dblVal;
				this->m_objPos = rhs.m_objPos;
				this->m_objDelta = rhs.m_objDelta;
				this->m_objRect = rhs.m_objRect;
				this->m_ptrObj = rhs.m_ptrObj;
			}
			return *this;	
		};



	};//end namespace GtCore

};//end namespace GT