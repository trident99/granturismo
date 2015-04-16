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


#ifndef GT_ITEM_ENUMS_H
#define GT_ITEM_ENUMS_H

#include "..\GtCoreLibRefs.h"

namespace GT
{
	namespace GtCore
	{

		enum GtItemFlag
		{
			NoItemFlags = 0, //It does not have any properties set. 
			ItemIsSelectable = 1, //It can be selected. 
			ItemIsEditable = 2, //It can be edited. 
			ItemIsDragEnabled = 4, //It can be dragged. 
			ItemIsDropEnabled = 8, //It can be used as a drop target. 
			ItemIsUserCheckable = 16, //It can be checked or unchecked by the user. 
			ItemIsEnabled = 32, //The user can interact with the item. 
			ItemIsTristate = 64 //The item is checkable with three separate states. 
		};


	};//end namespace GtCore

};//end namespace GT

namespace HTL
{
	using namespace GT::GtCore;

	//to and from string functions
	template <>
	HTL_EXPORT void enumToString<GtItemFlag>(GtItemFlag enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtItemFlag>(std::string & strVal, GtItemFlag & enumValReturn);

}

#endif//GT_ITEM_ENUMS_H