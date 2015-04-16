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


#ifndef GT_EVENT_ENUMS_H
#define GT_EVENT_ENUMS_H

#include "..\GtCoreLibRefs.h"
#include "..\GtCoreEnums.h"


namespace GT
{
	namespace GtCore
	{

		//!Gt Variant Types (Alphabetical
		enum GtEventType
		{
			EventUnknown = -1,
			EventBase = 0,
			//Keyboard Events
			KeyPress = 1,
			KeyRelease = 2,
			//Mouse Left Click Events
			MouseLeftPress,
			MouseLeftRelease,
			MouseLeftDoubleClick,
			//Mouse Right Click Events
			MouseRightPress,
			MouseRightRelease,
			MouseRightDoubleClick,
			//Mouse Middle Click Events
			MouseMiddlePress,
			MouseMiddleRelease,
			MouseMiddleDoubleClick,
			//Mouse Wheel Event
			MouseWheel,
			MouseWheelPress,
			MouseWheelRelease,
			//Mouse Move Event
			MouseMove,
			MouseHover,
		
			//DragEvents
			DragEnter,
			DragLeave,
			DragMove,
			DragDrop,

			//Action Events
			ActionAdd,
			ActionChanged,
			ActionRemove,

			//Menu Events
			MenuAdd,
			MenuChanged,
			MenuRemove,
			ContextMenu,

			//System Events
			SystemClipboard,
			SystemCursorChange,
			SystemClose,
			SystemOpen,
			SystemHelp,
			SystemScroll,
			SystemTimer,

			//Focus Events
			FocusEnter,
			FocusLeave,

			//Paint Events
			PaintEvent,

			//Touch Events
			TouchMove,
			TouchPress,
			TouchRelease,
			TouchEnter,
			TouchLeave,
			//Tablet Events
			TabletMove,
			TabletPress,
			TabletRelease,
			TabletOrientation,

			//Window Events
			WindowActivate,
			WindowBlocked,
			WindowDeactivate,
			WindowStateChange,
			WindowTitleChange,
			WindowUnblocked,
			WindowIdChange,

		};

	};//end namespace GtCore

};//end namespace GT

namespace HTL
{
		using namespace GT::GtCore;
		//to and from string functions
		template <>
		HTL_EXPORT void enumToString<GtEventType>(GtEventType enumVal, std::string & strReturn);

		template <>
		HTL_EXPORT void stringToEnum<GtEventType>(std::string & strVal, GtEventType & enumValReturn);

		//to and from string functions
		template <>
		HTL_EXPORT void enumToString<GtKeyboardModifier>(GtKeyboardModifier enumVal, std::string & strReturn);

		template <>
		HTL_EXPORT void stringToEnum<GtKeyboardModifier>(std::string & strVal, GtKeyboardModifier & enumValReturn);

};


#endif//GT_EVENT_H