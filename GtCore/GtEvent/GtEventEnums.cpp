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

#include ".\GtEventEnums.h"

namespace HTL
{
	template <>
	void enumToString<GtEventType>(GtEventType enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
				//check by comparison
			case EventUnknown: {strReturn = "EventUnknown";  return; break;};
			case EventBase: {strReturn = "EventBase";  return; break;};
				//Keyboard Events
			case KeyPress: {strReturn = "KeyPress";  return; break;};
			case KeyRelease: {strReturn = "KeyRelease";  return; break;};
				//Mouse Left Click Events
			case MouseLeftPress: {strReturn = "MouseLeftPress";  return; break;};
			case MouseLeftRelease: {strReturn = "MouseLeftRelease";  return; break;};
			case MouseLeftDoubleClick: {strReturn = "MouseLeftDoubleClick";  return; break;};
				//Mouse Right Click Events
			case MouseRightPress: {strReturn = "MouseRightPress";  return; break;};
			case MouseRightRelease: {strReturn = "MouseRightRelease";  return; break;};
			case MouseRightDoubleClick: {strReturn = "MouseRightDoubleClick";  return; break;};
				//Mouse Wheel Event
			case MouseWheel: {strReturn = "MouseWheel";  return; break;};
			case MouseWheelPress: {strReturn = "MouseWheelPress";  return; break;};
			case MouseWheelRelease: {strReturn = "MouseWheelRelease";  return; break;};
				//Mouse Move Event
			case MouseMove: {strReturn = "MouseMove";  return; break;};
			case MouseHover: {strReturn = "MouseHover";  return; break;};

				//DragEvents
			case DragEnter: {strReturn = "DragEnter";  return; break;};
			case DragLeave: {strReturn = "DragLeave";  return; break;};
			case DragMove: {strReturn = "DragMove";  return; break;};
			case DragDrop: {strReturn = "DragDrop";  return; break;};

				//Action Events
			case ActionAdd: {strReturn = "ActionAdd";  return; break;};
			case ActionChanged: {strReturn = "ActionChanged";  return; break;};
			case ActionRemove: {strReturn = "ActionRemove";  return; break;};

				//Menu Events
			case MenuAdd: {strReturn = "MenuAdd";  return; break;};
			case MenuChanged: {strReturn = "MenuChanged";  return; break;};
			case MenuRemove: {strReturn = "MenuRemove";  return; break;};
			case ContextMenu: {strReturn = "ContextMenu";  return; break;};

				//System Events
			case SystemClipboard: {strReturn = "SystemClipboard";  return; break;};
			case SystemCursorChange: {strReturn = "SystemCursorChange";  return; break;};
			case SystemClose: {strReturn = "SystemClose";  return; break;};
			case SystemOpen: {strReturn = "SystemOpen";  return; break;};
			case SystemHelp: {strReturn = "SystemHelp";  return; break;};
			case SystemScroll: {strReturn = "SystemScroll";  return; break;};
			case SystemTimer: {strReturn = "SystemTimer";  return; break;};

				//Focus Events
			case FocusEnter: {strReturn = "FocusEnter";  return; break;};
			case FocusLeave: {strReturn = "FocusLeave";  return; break;};

				//Paint Events
			case PaintEvent: {strReturn = "PaintEvent";  return; break;};

				//Touch Events
			case TouchMove: {strReturn = "TouchMove";  return; break;};
			case TouchPress: {strReturn = "TouchPress";  return; break;};
			case TouchRelease: {strReturn = "TouchRelease";  return; break;};
			case TouchEnter: {strReturn = "TouchEnter";  return; break;};
			case TouchLeave: {strReturn = "TouchLeave";  return; break;};


				//Tablet Events
			case TabletMove: {strReturn = "TabletMove";  return; break;};
			case TabletPress: {strReturn = "TabletPress";  return; break;};
			case TabletRelease: {strReturn = "TabletRelease";  return; break;};
			case TabletOrientation: {strReturn = "TabletOrientation";  return; break;};

				//Window Events
			case WindowActivate: {strReturn = "WindowActivate";  return; break;};
			case WindowBlocked: {strReturn = "WindowBlocked";  return; break;};
			case WindowDeactivate: {strReturn = "WindowDeactivate";  return; break;};
			case WindowStateChange: {strReturn = "WindowStateChange";  return; break;};
			case WindowTitleChange: {strReturn = "WindowTitleChange";  return; break;};
			case WindowUnblocked: {strReturn = "WindowUnblocked";  return; break;};
			case WindowIdChange: {strReturn = "WindowIdChange";  return; break;};


				//DEFUALT UNKNOWN
			default: {strReturn = "EventUnknown";  return; break;};
			};
		}catch(...){
			strReturn = "";
		};
		return;
	};

	template <>
	void stringToEnum<GtEventType>(std::string & strVal, GtEventType & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = EventUnknown; return;};
			//check by comparison

			if(strVal == "EventUnknown"){enumValReturn = EventUnknown; return;};
			if(strVal == "EventBase"){enumValReturn = EventBase; return;};

			//Keyboard Events
			if(strVal == "KeyPress"){enumValReturn = KeyPress; return;};
			if(strVal == "KeyRelease"){enumValReturn = KeyRelease; return;};

			//Mouse Left Click Events
			if(strVal == "MouseLeftPress"){enumValReturn = MouseLeftPress; return;};
			if(strVal == "MouseLeftRelease"){enumValReturn = MouseLeftRelease; return;};
			if(strVal == "MouseLeftDoubleClick"){enumValReturn = MouseLeftDoubleClick; return;};

			//Mouse Right Click Events
			if(strVal == "MouseRightPress"){enumValReturn = MouseRightPress; return;};
			if(strVal == "MouseRightRelease"){enumValReturn = MouseRightRelease; return;};
			if(strVal == "MouseRightDoubleClick"){enumValReturn = MouseRightDoubleClick; return;};

			//Mouse Wheel Event
			if(strVal == "MouseWheel"){enumValReturn = MouseWheel; return;};
			if(strVal == "MouseWheelPress"){enumValReturn = MouseWheelPress; return;};
			if(strVal == "MouseWheelRelease"){enumValReturn = MouseWheelRelease; return;};

			//Mouse Move Event
			if(strVal == "MouseMove"){enumValReturn = MouseMove; return;};
			if(strVal == "MouseHover"){enumValReturn = MouseHover; return;};

			//DragEvents
			if(strVal == "DragEnter"){enumValReturn = DragEnter; return;};
			if(strVal == "DragLeave"){enumValReturn = DragLeave; return;};
			if(strVal == "DragMove"){enumValReturn = DragMove; return;};
			if(strVal == "DragDrop"){enumValReturn = DragDrop; return;};

			//Action Events
			if(strVal == "ActionAdd"){enumValReturn = ActionAdd; return;};
			if(strVal == "ActionChanged"){enumValReturn = ActionChanged; return;};
			if(strVal == "ActionRemove"){enumValReturn = ActionRemove; return;};

			//Menu Events
			if(strVal == "MenuAdd"){enumValReturn = MenuAdd; return;};
			if(strVal == "MenuChanged"){enumValReturn = MenuChanged; return;};
			if(strVal == "MenuRemove"){enumValReturn = MenuRemove; return;};
			if(strVal == "ContextMenu"){enumValReturn = ContextMenu; return;};

			//System Events
			if(strVal == "SystemClipboard"){enumValReturn = SystemClipboard; return;};
			if(strVal == "SystemCursorChange"){enumValReturn = SystemCursorChange; return;};
			if(strVal == "SystemClose"){enumValReturn = SystemClose; return;};
			if(strVal == "SystemOpen"){enumValReturn = SystemOpen; return;};
			if(strVal == "SystemHelp"){enumValReturn = SystemHelp; return;};
			if(strVal == "SystemScroll"){enumValReturn = SystemScroll; return;};
			if(strVal == "SystemTimer"){enumValReturn = SystemTimer; return;};

			//Focus Events
			if(strVal == "FocusEnter"){enumValReturn = FocusEnter; return;};
			if(strVal == "FocusLeave"){enumValReturn = FocusLeave; return;};

			//Paint Events
			if(strVal == "PaintEvent"){enumValReturn = PaintEvent; return;};

			//Touch Events
			if(strVal == "TouchMove"){enumValReturn = TouchMove; return;};
			if(strVal == "TouchPress"){enumValReturn = TouchPress; return;};
			if(strVal == "TouchRelease"){enumValReturn = TouchRelease; return;};
			if(strVal == "TouchEnter"){enumValReturn = TouchEnter; return;};
			if(strVal == "TouchLeave"){enumValReturn = TouchLeave; return;};

			//Tablet Events
			if(strVal == "TabletMove"){enumValReturn = TabletMove; return;};
			if(strVal == "TabletPress"){enumValReturn = TabletPress; return;};
			if(strVal == "TabletRelease"){enumValReturn = TabletRelease; return;};
			if(strVal == "TabletOrientation"){enumValReturn = TabletOrientation; return;};

			//Window Events
			if(strVal == "WindowActivate"){enumValReturn = WindowActivate; return;};
			if(strVal == "WindowBlocked"){enumValReturn = WindowBlocked; return;};
			if(strVal == "WindowDeactivate"){enumValReturn = WindowDeactivate; return;};
			if(strVal == "WindowStateChange"){enumValReturn = WindowStateChange; return;};
			if(strVal == "WindowTitleChange"){enumValReturn = WindowTitleChange; return;};
			if(strVal == "WindowUnblocked"){enumValReturn = WindowUnblocked; return;};
			if(strVal == "WindowIdChange"){enumValReturn = WindowIdChange; return;};

			//DEFUALT UNKNOWN
			enumValReturn = EventUnknown;
			return;
		}catch(...){
			enumValReturn = EventUnknown;
			return;
		};
	};
	template <>
	void enumToString<GtKeyboardModifier>(GtKeyboardModifier enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
				//check by comparison
			case NoModifier: {strReturn = "NoModifier";  return; break;};
			case ShiftModifier: {strReturn = "ShiftModifier";  return; break;};
			case ControlModifier: {strReturn = "ControlModifier";  return; break;};
			case AltModifier: {strReturn = "AltModifier";  return; break;};
			case MetaModifier: {strReturn = "MetaModifier";  return; break;};
			case KeypadModifier: {strReturn = "KeypadModifier";  return; break;};
			case FunctionModifier: {strReturn = "FunctionModifier";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "NoModifier";  return; break;};
			};
		}catch(...){
			strReturn = "";
		};
		return;
	};

	template <>
	void stringToEnum<GtKeyboardModifier>(std::string & strVal, GtKeyboardModifier & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = NoModifier; return;};
			//check by comparison

			if(strVal == "NoModifier"){enumValReturn = NoModifier; return;};
			if(strVal == "ShiftModifier"){enumValReturn = ShiftModifier; return;};
			if(strVal == "ControlModifier"){enumValReturn = ControlModifier; return;};
			if(strVal == "AltModifier"){enumValReturn = AltModifier; return;};
			if(strVal == "MetaModifier"){enumValReturn = MetaModifier; return;};
			if(strVal == "KeypadModifier"){enumValReturn = KeypadModifier; return;};
			if(strVal == "FunctionModifier"){enumValReturn = FunctionModifier; return;};

			//DEFUALT UNKNOWN
			enumValReturn = NoModifier;
			return;
		}catch(...){
			enumValReturn = NoModifier;
			return;
		};
	};

};//end namespace HTL