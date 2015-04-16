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

#ifndef GT_CORE_ENUMS_H
#define GT_CORE_ENUMS_H

#include ".\GtCoreLibRefs.h"
#include <modHtlContainer.h>

using namespace HTL;

namespace GT
{
	namespace GtCore
	{
		//!Gt Common typedefs
		//typedef unsigned char uchar;
		//typedef unsigned short ushort;
		//typedef unsigned int uint;
		//typedef unsigned long ulong;
		//typedef long long longlong;
		typedef long long GtInt64;
		//typedef unsigned long long ulonglong;
		typedef unsigned long long GtUInt64;

		/*Operation	| Output Range | Output Type | Bytes per Element | Output Class

		int8 -128 to 127 Signed 8-bit integer 1 int8

		int16 -32,768 to 32,767 Signed 16-bit integer  2 int16

		int32 -2,147,483,648 to 2,147,483,647 Signed 32-bit integer  4 int32

		int64 -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 Signed 64-bit integer  8 int64 
		*/

		/*Operation Output | Range | Output Type | Bytes per Element | Output Class

		uint8 0 to 255 Unsigned 8-bit integer 1 uint8

		uint16 0 to 65,535 Unsigned 16-bit integer 2 uint16

		uint32 0 to 4,294,967,295 Unsigned 32-bit integer  4 uint32

		uint64 0 to 18,446,744,073,709,551,615 Unsigned 64-bit integer  8 uint64 
		*/

		HTL_EXPORT int GtStringToWString(std::wstring &ws, const std::string &s);

		//!These are the template functions for conversion of enumerated types
		//to and from string form.

		template <typename T>
		HTL_EXPORT void enumToString(T enumVal, std::string & strReturn){return;};

		template <typename T>
		HTL_EXPORT void stringToEnum(std::string & strVal, T & enumValReturn){return;};

		//!Gt Variant Types
		enum GtVarType
		{
			VarUnknown = -1,
			CppChar = 0,
			CppUChar = 1,
			CppShort,
			CppUShort,
			CppInt,
			CppUInt,
			CppLong,
			CppULong,
			CppLongLong,
			CppULongLong,
			CppFloat,
			CppDouble,
			GtObjPtr,
			VoidObjPtr,
			StlString
		};
		//to and from string functions
		template <>
		HTL_EXPORT void enumToString<GtVarType>(GtVarType enumVal, std::string & strReturn);

		template <>
		HTL_EXPORT void stringToEnum<GtVarType>(std::string & strVal, GtVarType & enumValReturn);

		//!The open model flag for what type of access for the file
		enum GtOpenModeFlag
		{
			NotOpen = 0x0000,
			ReadOnly = 0x0001,
			WriteOnly = 0x0002,
			ReadWrite = ReadOnly | WriteOnly,
			Append = 0x0004,
			Truncate = 0x0008,
		};

		//!The directory filter flag
		enum GtDirFilter 
		{ 
			Dirs        = 0x001,
			Files       = 0x002,
			Drives      = 0x004,
			NoSymLinks  = 0x008,
			AllEntries  = Dirs | Files | Drives,
			TypeMask    = 0x00f,

			Readable    = 0x010,
			Writable    = 0x020,
			Executable  = 0x040,
			PermissionMask    = 0x070,

			Modified    = 0x080,
			Hidden      = 0x100,
			System      = 0x200,

			AccessMask  = 0x3F0,

			AllDirs       = 0x400,
			CaseSensitive = 0x800,
			NoDot         = 0x2000,
			NoDotDot      = 0x4000,
			NoDotAndDotDot = NoDot | NoDotDot,

			NoFilter = -1
		};

		//!The file sorting flag
		enum GtFileSortFlag 
		{ 
			Name        = 0x0000,
			Time        = 0x0001,
			Size        = 0x0002,
			Unsorted    = 0x0004,
			SortByMask  = 0x0008,

			DirsFirst   = 0x0010,
			Reversed    = 0x0020,
			IgnoreCase  = 0x0040,
			DirsLast    = 0x0080,
			LocaleAware = 0x0100,
			Type        = 0x0200,
			NoSort = -1
		};

		//!This has all of the key codes and their hex values
		enum GtKey
		{
			//The key names used by Gt.
			//Constant	Value	Description
			Key_Null		=	0x00,
			Key_LeftButton	=	0x01, //Left mouse button
			Key_RightButton =	0x02, //Right mouse button
			Key_Cancel		=	0x03, //Control-break processing
			Key_MiddleButton=	0x04, //Middle mouse button (three-button mouse)
			Key_XButton01	=	0x05, //X1 mouse button
			Key_XButton02	=	0x06, //X2 mouse button
			Key_Undefined01 =	0x07, //Undefined
			Key_Backspace	=	0x08, //BACKSPACE key
			Key_Tab			=	0x09, //TAB key
			//0x0A-0B Reserved
			Key_Clear		=	0x0C, //CLEAR key
			Key_Return		=	0x0D, //ENTER key 
			//0x0E-0F Undefined
			Key_Shift		=	0x10, //SHIFT key
			Key_Control		=	0x11, //CTRL key
			Key_Alt			=	0x12, //ALT key
			Key_Pause		=	0x13, //PAUSE key
			Key_CapsLock	=	0x14, //CAPS LOCK key
			Key_Hangul		=	0x15, //IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
			Key_Undefined02 = 	0x16, //Undefined
			Key_Junja		=	0x17, //IME Junja mode
			Key_Final		=	0x18, //IME final mode
			Key_Hanja		=	0x19, //IME Hanja mode
			Key_Kanji		=	0x19, //IME Kanji mode
			Key_Undefined03 =	0x1A, // Undefined
			Key_Escape		=	0x1B, // ESC key
			Key_Convert		=	0x1C, // IME convert
			Key_NonConvert	=	0x1D, // IME nonconvert
			Key_Accept		=	0x1E, // IME accept
			Key_ModeChange	=	0x1F, // IME mode change request
			Key_Space		=	0x20, // SPACEBAR
			Key_PageUp		=	0x21, // PAGE UP key
			Key_PageDown	=	0x22, // PAGE DOWN key
			Key_End			=	0x23, // END key
			Key_Home		=	0x24, // HOME key
			Key_Left		=	0x25, // LEFT ARROW key
			Key_Up			=	0x26, // UP ARROW key
			Key_Right		=	0x27, // RIGHT ARROW key
			Key_Down		=	0x28, // DOWN ARROW key
			Key_Select		=	0x29, // SELECT key
			Key_Print		=	0x2A, // PRINT key
			Key_Execute		=	0x2B, // EXECUTE key
			Key_PrintScreen	=	0x2C, // PRINT SCREEN key
			Key_Insert		=	0x2D, // INS key
			Key_Delete		=	0x2E, // DEL key
			Key_Help		=	0x2F, // HELP key

			Key_0 = 0x30, // 0 key
			Key_1 = 0x31, // 1 key
			Key_2 = 0x32, // 2 key
			Key_3 = 0x33, // 3 key
			Key_4 = 0x34, // 4 key
			Key_5 = 0x35, // 5 key
			Key_6 = 0x36, // 6 key
			Key_7 = 0x37, // 7 key
			Key_8 = 0x38, // 8 key
			Key_9 = 0x39, // 9 key
			//0x3A-40 Undefined

			Key_A = 0x41, // A key
			Key_B = 0x42, // B key
			Key_C = 0x43, // C key
			Key_D = 0x44, // D key
			Key_E = 0x45, // E key
			Key_F = 0x46, // F key
			Key_G = 0x47, // G key
			Key_H = 0x48, // H key
			Key_I = 0x49, // I key
			Key_J = 0x4A, // J key
			Key_K = 0x4B, // K key
			Key_L = 0x4C, // L key
			Key_M = 0x4D, // M key
			Key_N = 0x4E, // N key
			Key_O = 0x4F, // O key
			Key_P = 0x50, // P key
			Key_Q = 0x51, // Q key
			Key_R = 0x52, // R key
			Key_S = 0x53, // S key
			Key_T = 0x54, // T key
			Key_U = 0x55, // U key
			Key_V = 0x56, // V key
			Key_W = 0x57, // W key
			Key_X = 0x58, // X key
			Key_Y = 0x59, // Y key
			Key_Z = 0x5A, // Z key

			Key_LeftWin		=	0x5B, // Left Windows key (Natural keyboard) 
			Key_RightWin	=		0x5C, // Right Windows key (Natural keyboard)
			Key_Applications=			0x5D, // Applications key (Natural keyboard)
			//0x5E, // Reserved
			Key_Sleep	=	0x5F, // Computer Sleep key

			Key_Numpad0	=	0x60, // Numeric keypad 0 key
			Key_Numpad1	=	0x61, // Numeric keypad 1 key
			Key_Numpad2	=	0x62, // Numeric keypad 2 key
			Key_Numpad3	=	0x63, // Numeric keypad 3 key
			Key_Numpad4	=	0x64, // Numeric keypad 4 key
			Key_Numpad5	=	0x65, // Numeric keypad 5 key
			Key_Numpad6	=	0x66, // Numeric keypad 6 key
			Key_Numpad7	=	0x67, // Numeric keypad 7 key
			Key_Numpad8	=	0x68, // Numeric keypad 8 key
			Key_Numpad9	=	0x69, // Numeric keypad 9 key
			Key_Multiply=		0x6A, // Multiply key
			Key_Add		=	0x6B, // Add key
			Key_Separator=	0x6C, // Separator key
			Key_Subtract=		0x6D, // Subtract key
			Key_Decimal	=	0x6E, // Decimal key
			Key_Divide	=	0x6F, // Divide key

			Key_F1	=		0x70, // F1 key
			Key_F2	=		0x71, // F2 key
			Key_F3	=		0x72, // F3 key
			Key_F4	=		0x73, // F4 key
			Key_F5	=		0x74, // F5 key
			Key_F6	=		0x75, // F6 key
			Key_F7	=		0x76, // F7 key
			Key_F8	=		0x77, // F8 key
			Key_F9	=		0x78, // F9 key
			Key_F10	=		0x79, // F10 key
			Key_F11	=		0x7A, // F11 key
			Key_F12	=		0x7B, // F12 key
			Key_F13	=		0x7C, // F13 key
			Key_F14	=		0x7D, // F14 key
			Key_F15	=		0x7E, // F15 key
			Key_F16	=		0x7F, // F16 key
			Key_F17	=		0x80, // F17 key
			Key_F18	=		0x81, // F18 key
			Key_F19	=		0x82, // F19 key
			Key_F20	=		0x83, // F20 key
			Key_F21	=		0x84, // F21 key
			Key_F22	=		0x85, // F22 key
			Key_F23	=		0x86, // F23 key
			Key_F24	=		0x87, // F24 key
			//0x88-8F Unassigned

			Key_NumLock	=	0x90, // NUM LOCK key
			Key_ScrollLock	=	0x91, // SCROLL LOCK key
			//0x92-96 OEM specific
			//0x97-9F Unassigned

			Key_LeftShift	=	0xA0, // Left SHIFT key
			Key_RightShift	=	0xA1, // Right SHIFT key
			Key_LeftControl	=	0xA2, // Left CONTROL key
			Key_RightControl	=	0xA3, // Right CONTROL key
			Key_LeftAlt	=	0xA4, // Left MENU key
			Key_RightAlt	=	0xA5, // Right MENU key
			Key_BrowserBack	= 0xA6, // Browser Back key
			Key_BrowserForward =	0xA7, // Browser Forward key
			Key_BrowserRefresh =	0xA8, // Browser Refresh key
			Key_BrowserStop	=	0xA9, // Browser Stop key
			Key_BrowserSearch =	0xAA, // Browser Search key 
			Key_BrowserFavorites =	0xAB, // Browser Favorites key
			Key_BrowserHome	=	0xAC, // Browser Start and Home key
			Key_VolumeMute	=	0xAD, // Volume Mute key
			Key_VolumeDown	=	0xAE, // Volume Down key
			Key_VolumeUp	=	0xAF, // Volume Up key
			Key_MediaNextTrack	= 0xB0, // Next Track key
			Key_MediaPreviousTrack	= 0xB1, // Previous Track key
			Key_MediaStop		= 0xB2, // Stop Media key
			Key_MediaPlay	= 0xB3, // Play/Pause Media key

			Key_OEM_SemiColon = 0xBA, // ; or :
			Key_OEM_Plus = 0xBB,  //+ or =
			Key_OEM_Comma = 0xBC, //, or <
			Key_OEM_Minus = 0xBD, // - or _
			Key_OEM_Period = 0xBE, // . or >
			Key_OEM_Backslash = 0xBF, // / or ?
			Key_OEM_Tilda = 0xC0, // ~ or `
			Key_OEM_OpenBracket = 0xDB, // [ or {
			Key_OEM_Foreslash = 0xDC, // \ or |
			Key_OEM_CloseBracket = 0xDD, // ] or }
			Key_OEM_Quote = 0xDE, // ' or "
		};



		enum GtKeyboardModifier
		{
			NoModifier			= 0x0000,	//No modifier key is pressed.
			ShiftModifier		= 0x0002,	//A Shift key on the keyboard is pressed.
			ControlModifier		= 0x0004,	//A Ctrl key on the keyboard is pressed.
			AltModifier			= 0x0008,	//An Alt key on the keyboard is pressed.
			MetaModifier		= 0x0010,	//A Meta key on the keyboard is pressed.
			KeypadModifier		= 0x0020,	//A keypad button is pressed.
			FunctionModifier	= 0x0040,	//A Function button is pressed.
			LeftMouseModifier	= 0x0100,   //The Left Mouse Button is pressed.
			RightMouseModifier  = 0x0200,   //The Left Mouse Button is pressed.
			CenterMouseModifier  = 0x0400  //The Center Mouse Button is pressed.
		};

		HTL_DLLAPI char GtKeyToChar(GtKey key,int modifiers);
		HTL_DLLAPI wchar_t GtKeyToWChar(GtKey key,int modifiers);

	};//end namespace GtCore
};//end namespace GT

#endif