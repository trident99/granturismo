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


#ifndef GT_EVENT_H
#define GT_EVENT_H

#include "..\GtCoreLibRefs.h"
#include ".\GtEventEnums.h"
#include "..\GtGeometry\GtPoint3DF.h"
#include "..\GtGeometry\GtRectF.h"

namespace GT
{
	namespace GtCore
	{
		class GtObject;

		class HTL_DLLAPI GtEvent
		{
		public:
			//!Default Constructor
			GtEvent();

			//!Destructor
			~GtEvent();

			//Assignment Operator Overload
			GtEvent & operator = (GtEvent & rhs);

		public:
			//!string representation of the event class type
			std::string m_strType;
			//!enum representation of the event class type
			GtEventType m_objType;
			//!enum representation of the keyboard modifiers
			int m_objModifiers;
			//!enum representation of the key
			GtKey m_objKey;
			//!floating point value
			int m_intVal;
			//!floating point value
			double m_dblVal;
			//!position of the event
			GtPoint3DF m_objPos;
			//!position delta of the event
			GtPoint3DF m_objDelta;
			//!bounding rect of the event
			GtRectF m_objRect;
			//!pointer to the attached GtObject
			GtObject* m_ptrObj;

		};//end GtEvent

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_H