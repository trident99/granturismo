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

#include ".\GtEventCreator.h"
#include "..\GtGeometry\GtPoint3DI.h"
#include "..\GtGeometry\GtPoint3DF.h"
#include "Windowsx.h"


namespace GT{

	namespace GtCore{
		//global mouse last move position
		GtPoint3DI g_objMouseLastPos;

		//!Post and event for processing
		GtEvent CreateGtEvent(MSG winMsg)
		{
			//This function is essentially a massive switch case statement.
			//unfortunately there the message is an int so using template functors is out.
			//The purpose of this function is to translate the system events to the GtEvent class
			GtEvent newEvent;
			newEvent.m_strType = "EventUnknown";
			newEvent.m_objType = EventUnknown;
			switch(winMsg.message)
			{
				//WINDOWS KEYBOARD EVENTS/////////////////////////////////
			case WM_KEYDOWN : 
				{
					newEvent.m_strType = "KeyPress";
					newEvent.m_objType = KeyPress;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;
					//map the virtual key to an actual char
					//char c = MapVirtualKey (param, MAPVK_VK_TO_CHAR);
					newEvent.m_objKey = WinVKey_To_GtKey(param);
					//get the modifiers, clear first
					newEvent.m_objModifiers = NoModifier;
					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};
					//return the event
					return newEvent;
					break;
				}
			case WM_KEYUP : 
				{
					newEvent.m_strType = "KeyRelease";
					newEvent.m_objType = KeyRelease;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;
					//map the virtual key to an actual char
					//char c = MapVirtualKey (param, MAPVK_VK_TO_CHAR);
					newEvent.m_objKey = WinVKey_To_GtKey(param);
					//get the modifiers, clear first
					newEvent.m_objModifiers = NoModifier;
					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};
					//return the event
					return newEvent;
					break;
				}
				//WINDOWS MOUSE EVENTS/////////////////////////////////////////////////

			case WM_LBUTTONDOWN: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseLeftPress";
					newEvent.m_objType = MouseLeftPress;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};

					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;
				
					return newEvent;
					break;
				}

			case WM_LBUTTONUP: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseLeftRelease";
					newEvent.m_objType = MouseLeftRelease;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};

					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;

					return newEvent;
					break;
				}
			case WM_RBUTTONDOWN: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseRightPress";
					newEvent.m_objType = MouseRightPress;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};

					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;
				
					return newEvent;
					break;
				}

			case WM_RBUTTONUP: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseRightRelease";
					newEvent.m_objType = MouseRightRelease;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};

					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;

					return newEvent;
					break;
				}
			case WM_MBUTTONDOWN: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseMiddlePress";
					newEvent.m_objType = MouseMiddlePress;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};

					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;
				
					return newEvent;
					break;
				}

			case WM_MBUTTONUP: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseMiddleRelease";
					newEvent.m_objType = MouseMiddleRelease;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};

					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;

					return newEvent;
					break;
				}
			case WM_MOUSEMOVE: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseMove";
					newEvent.m_objType = MouseMove;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};
					//VK_LBUTTON			0x12 ALT key
					if(GtIsKeyDown(VK_LBUTTON)){newEvent.m_objModifiers = newEvent.m_objModifiers | LeftMouseModifier;};
					//VK_RBUTTON			0x12 ALT key
					if(GtIsKeyDown(VK_RBUTTON)){newEvent.m_objModifiers = newEvent.m_objModifiers | RightMouseModifier;};
					//VK_MBUTTON			0x12 ALT key
					if(GtIsKeyDown(VK_MBUTTON)){newEvent.m_objModifiers = newEvent.m_objModifiers | CenterMouseModifier;};
	
					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;
					//calculate position delta
					newEvent.m_objDelta.x = xPos - g_objMouseLastPos.x;
					newEvent.m_objDelta.y = yPos - g_objMouseLastPos.y;

					//set new last position
					g_objMouseLastPos.x = xPos;
					g_objMouseLastPos.y = yPos;

					return newEvent;
					break;
				}

			case WM_MOUSEWHEEL: //WM_LBUTTONUP, WM_LBUTTONDBLCLK same as WM_LBUTTONDOWN
				{
					newEvent.m_strType = "MouseWheel";
					newEvent.m_objType = MouseWheel;
					//winMsg.wParam is the windows virtual key code
					WPARAM param = winMsg.wParam;

					//VK_SHIFT		0x10 SHIFT key
					if(GtIsKeyDown(VK_SHIFT)){newEvent.m_objModifiers = newEvent.m_objModifiers | ShiftModifier;};
					//VK_CONTROL		0x11 CTRL key
					if(GtIsKeyDown(VK_CONTROL)){newEvent.m_objModifiers = newEvent.m_objModifiers | ControlModifier;};
					//VK_MENU			0x12 ALT key
					if(GtIsKeyDown(VK_MENU)){newEvent.m_objModifiers = newEvent.m_objModifiers | AltModifier;};
					//VK_LBUTTON			0x12 ALT key
					if(GtIsKeyDown(VK_LBUTTON)){newEvent.m_objModifiers = newEvent.m_objModifiers | LeftMouseModifier;};
					//VK_RBUTTON			0x12 ALT key
					if(GtIsKeyDown(VK_RBUTTON)){newEvent.m_objModifiers = newEvent.m_objModifiers | RightMouseModifier;};
					//VK_MBUTTON			0x12 ALT key
					if(GtIsKeyDown(VK_MBUTTON)){newEvent.m_objModifiers = newEvent.m_objModifiers | CenterMouseModifier;};
	
					int xPos = GET_X_LPARAM(winMsg.lParam); 
					int yPos = GET_Y_LPARAM(winMsg.lParam); 
					newEvent.m_objPos.x = xPos;
					newEvent.m_objPos.y = yPos;
					//calculate position delta
					newEvent.m_objDelta.x = xPos - g_objMouseLastPos.x;
					newEvent.m_objDelta.y = yPos - g_objMouseLastPos.y;
					//set new last position
					g_objMouseLastPos.x = xPos;
					g_objMouseLastPos.y = yPos;

					//get mouse wheel parameters
					int fwKeys = GET_KEYSTATE_WPARAM(winMsg.wParam);
					int zDelta = GET_WHEEL_DELTA_WPARAM(winMsg.wParam);

					newEvent.m_intVal = zDelta / WHEEL_DELTA;

					return newEvent;
					break;
				}


			};//end message switch case statement
			return newEvent;

		};//end CreateGtEvent

		//!Convert Windows Virtual Key to GtKey
		GtKey WinVKey_To_GtKey(WPARAM vkey)
		{
			switch(vkey)
			{
			case 0x01: {/*VK_LBUTTON*/ return GtCore::Key_LeftButton; break;};
			case 0x02: {/*VK_RBUTTON*/ return GtCore::Key_RightButton; break;};
			case 0x03: {/*VK_CANCEL*/ return GtCore::Key_Cancel; break;};
			case 0x04: {/*VK_MBUTTON*/ return GtCore::Key_MiddleButton; break;};
			case 0x05: {/*VK_XBUTTON1*/ return GtCore::Key_XButton01; break;};
			case 0x06: {/*VK_XBUTTON2*/ return GtCore::Key_XButton02; break;};
			case 0x07: {/*Undefined*/ return GtCore::Key_Undefined01; break;};
			case 0x08: {/*VK_BACK*/ return GtCore::Key_Backspace; break;};
			case 0x09: {/* VK_TAB*/ return GtCore::Key_Tab; break;};

			case 0x0C: {/* VK_CLEAR*/ return GtCore::Key_Clear; break;};
			case 0x0D: {/*  VK_RETURN*/ return GtCore::Key_Return; break;};

			case 0x10: {/* VK_SHIFT*/ return GtCore::Key_Shift; break;};
			case 0x11: {/* VK_CONTROL*/ return GtCore::Key_Control; break;};
			case 0x12: {/* VK_MENU*/ return GtCore::Key_Alt; break;};
			case 0x13: {/* VK_PAUSE*/ return GtCore::Key_Pause; break;};
			case 0x14: {/* VK_CAPITAL*/ return GtCore::Key_CapsLock; break;};
			case 0x15: {/* VK_HANGUL*/ return GtCore::Key_Hangul; break;};
			case 0x16: {/**/ return GtCore::Key_Undefined02; break;};
			case 0x17: {/* VK_JUNJA*/ return GtCore::Key_Junja; break;};
			case 0x18: {/* VK_FINAL*/ return GtCore::Key_Final; break;};
			case 0x19: {/* VK_KANJI*/ return GtCore::Key_Kanji; break;};
			case 0x1A: {/* */ return GtCore::Key_Undefined03; break;};
			case 0x1B: {/* VK_ESCAPE*/ return GtCore::Key_Escape; break;};
			case 0x1C: {/* VK_CONVERT*/ return GtCore::Key_Convert; break;};
			case 0x1D: {/* VK_NONCONVERT*/ return GtCore::Key_NonConvert; break;};
			case 0x1E: {/* VK_ACCEPT*/ return GtCore::Key_Accept; break;};
			case 0x1F: {/* VK_MODECHANGE*/ return GtCore::Key_ModeChange; break;};
			case 0x20: {/* VK_SPACE*/ return GtCore::Key_Space; break;};
			case 0x21: {/* VK_PRIOR*/ return GtCore::Key_PageUp; break;};
			case 0x22: {/* VK_NEXT*/ return GtCore::Key_PageDown; break;};
			case 0x23: {/* VK_END*/ return GtCore::Key_End; break;};
			case 0x24: {/* VK_HOME*/ return GtCore::Key_Home; break;};
			case 0x25: {/* VK_LEFT*/ return GtCore::Key_Left; break;};
			case 0x26: {/* VK_UP*/ return GtCore::Key_Up; break;};
			case 0x27: {/* VK_RIGHT*/ return GtCore::Key_Right; break;};
			case 0x28: {/* VK_DOWN*/ return GtCore::Key_Down; break;};
			case 0x29: {/* VK_SELECT*/ return GtCore::Key_Select; break;};
			case 0x2A: {/* VK_PRINT*/ return GtCore::Key_Print; break;};
			case 0x2B: {/* VK_EXECUTE*/ return GtCore::Key_Execute; break;};
			case 0x2C: {/* VK_SNAPSHOT*/ return GtCore::Key_PrintScreen; break;};
			case 0x2D: {/* VK_INSERT*/ return GtCore::Key_Insert; break;};
			case 0x2E: {/* VK_DELETE*/ return GtCore::Key_Delete; break;};
			case 0x2F: {/* VK_HELP*/ return GtCore::Key_Help; break;};

			case 0x30: {/* 0 key*/ return GtCore::Key_0; break;};
			case 0x31: {/* 1 key*/ return GtCore::Key_1; break;};
			case 0x32: {/* 2 key*/ return GtCore::Key_2; break;};
			case 0x33: {/* 3 key*/ return GtCore::Key_3; break;};
			case 0x34: {/* 4 key*/ return GtCore::Key_4; break;};
			case 0x35: {/* 5 key*/ return GtCore::Key_5; break;};
			case 0x36: {/* 6 key*/ return GtCore::Key_6; break;};
			case 0x37: {/* 7 key*/ return GtCore::Key_7; break;};
			case 0x38: {/* 8 key*/ return GtCore::Key_8; break;};
			case 0x39: {/* 9 key*/ return GtCore::Key_9; break;};

			case 0x41: {/* A key*/ return GtCore::Key_A; break;};
			case 0x42: {/* B key*/ return GtCore::Key_B; break;};
			case 0x43: {/* C key*/ return GtCore::Key_C; break;};
			case 0x44: {/* D key*/ return GtCore::Key_D; break;};
			case 0x45: {/* E key*/ return GtCore::Key_E; break;};
			case 0x46: {/* F key*/ return GtCore::Key_F; break;};
			case 0x47: {/* G key*/ return GtCore::Key_G; break;};
			case 0x48: {/* H key*/ return GtCore::Key_H; break;};
			case 0x49: {/* I key*/ return GtCore::Key_I; break;};
			case 0x4A: {/* J key*/ return GtCore::Key_J; break;};
			case 0x4B: {/* K key*/ return GtCore::Key_K; break;};
			case 0x4C: {/* L key*/ return GtCore::Key_L; break;};
			case 0x4D: {/* M key*/ return GtCore::Key_M; break;};
			case 0x4E: {/* N key*/ return GtCore::Key_N; break;};
			case 0x4F: {/* O key*/ return GtCore::Key_O; break;};
			case 0x50: {/* P key*/ return GtCore::Key_P; break;};
			case 0x51: {/* Q key*/ return GtCore::Key_Q; break;};
			case 0x52: {/* R key*/ return GtCore::Key_R; break;};
			case 0x53: {/* S key*/ return GtCore::Key_S; break;};
			case 0x54: {/* T key*/ return GtCore::Key_T; break;};
			case 0x55: {/* U key*/ return GtCore::Key_U; break;};
			case 0x56: {/* V key*/ return GtCore::Key_V; break;};
			case 0x57: {/* W key*/ return GtCore::Key_W; break;};
			case 0x58: {/* X key*/ return GtCore::Key_X; break;};
			case 0x59: {/* Y key*/ return GtCore::Key_Y; break;};
			case 0x5A: {/* Z key*/ return GtCore::Key_Z; break;};

			case 0x5B: {/* VK_LWIN*/ return GtCore::Key_LeftWin; break;};
			case 0x5C: {/* VK_RWIN*/ return GtCore::Key_RightWin; break;};
			case 0x5D: {/* VK_APPS*/ return GtCore::Key_Applications; break;};
			case 0x5E: {/* */ return GtCore::Key_Null; break;};
			case 0x5F: {/* VK_SLEEP*/ return GtCore::Key_Sleep; break;};

			case 0x60: {/* VK_NUMPAD0*/ return GtCore::Key_Numpad0; break;};
			case 0x61: {/* VK_NUMPAD1*/ return GtCore::Key_Numpad1; break;};
			case 0x62: {/* VK_NUMPAD2*/ return GtCore::Key_Numpad2; break;};
			case 0x63: {/* VK_NUMPAD3*/ return GtCore::Key_Numpad3; break;};
			case 0x64: {/* VK_NUMPAD4*/ return GtCore::Key_Numpad4; break;};
			case 0x65: {/* VK_NUMPAD5*/ return GtCore::Key_Numpad5; break;};
			case 0x66: {/* VK_NUMPAD6*/ return GtCore::Key_Numpad6; break;};
			case 0x67: {/* VK_NUMPAD7*/ return GtCore::Key_Numpad7; break;};
			case 0x68: {/* VK_NUMPAD8*/ return GtCore::Key_Numpad8; break;};
			case 0x69: {/* VK_NUMPAD9*/ return GtCore::Key_Numpad9; break;};
			case 0x6A: {/* VK_MULTIPLY*/ return GtCore::Key_Multiply; break;};
			case 0x6B: {/* VK_ADD*/ return GtCore::Key_Add; break;};
			case 0x6C: {/* VK_SEPARATOR*/ return GtCore::Key_Separator; break;};
			case 0x6D: {/* VK_SUBTRACT*/ return GtCore::Key_Subtract; break;};
			case 0x6E: {/* VK_DECIMAL*/ return GtCore::Key_Decimal; break;};
			case 0x6F: {/* VK_DIVIDE*/ return GtCore::Key_Divide; break;};

			case 0xBA: {/* VK_OEM_PLUS*/ return GtCore::Key_OEM_SemiColon; break;};
			case 0xBB: {/* VK_OEM_PLUS*/ return GtCore::Key_OEM_Plus; break;};
			case 0xBC: {/* VK_OEM_COMMA*/ return GtCore::Key_OEM_Comma; break;};
			case 0xBD: {/* VK_OEM_MINUS*/ return GtCore::Key_OEM_Minus; break;};
			case 0xBE: {/* VK_OEM_PERIOD*/ return GtCore::Key_OEM_Period; break;};
			case 0xBF: {/* VK_OEM_2*/ return GtCore::Key_OEM_Backslash; break;};
			case 0xC0: {/* VK_OEM_3*/ return GtCore::Key_OEM_Tilda; break;};
			case 0xDB: {/* VK_OEM_4*/ return GtCore::Key_OEM_OpenBracket; break;};
			case 0xDC: {/* VK_OEM_5*/ return GtCore::Key_OEM_Foreslash; break;};
			case 0xDD: {/* VK_OEM_6*/ return GtCore::Key_OEM_CloseBracket; break;};
			case 0xDE: {/* VK_OEM_7*/ return GtCore::Key_OEM_Quote; break;};

			default: {return GtCore::Key_Null; break;};

			}

		};

	};//end namespace GtCore

};//end namespace GT