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

#include ".\GtCoreEnums.h"


namespace GT{

	namespace GtCore{

		int GtStringToWString(std::wstring &ws, const std::string &s)
		{
			std::wstring wsTmp(s.begin(), s.end());

			ws = wsTmp;

			return 0;
		}

		template <>
		void enumToString<GtVarType>(GtVarType enumVal, std::string & strReturn)
		{
			try{
				switch(enumVal)
				{
					//HTL CPLUSPLUS NATIVE TYPES
				case VarUnknown: {strReturn = "VarUnknown";  return; break;};
				case CppChar: {strReturn = "CppChar";  return; break;};
				case CppUChar: {strReturn = "CppUChar";  return; break;};
				case CppShort: {strReturn = "CppShort";  return; break;};
				case CppUShort: {strReturn = "CppUShort";  return; break;};
				case CppInt: {strReturn = "CppInt";  return; break;};
				case CppUInt: {strReturn = "CppUInt";  return; break;};
				case CppLong: {strReturn = "CppLong";  return; break;};
				case CppULong: {strReturn = "CppULong";  return; break;};
				case CppLongLong: {strReturn = "CppLongLong";  return; break;};
				case CppULongLong: {strReturn = "CppULongLong";  return; break;};
				case CppFloat: {strReturn = "CppFloat";  return; break;};
				case CppDouble: {strReturn = "CppDouble";  return; break;};
				case GtObjPtr: {strReturn = "GtObjPtr";  return; break;};
				case VoidObjPtr: {strReturn = "VoidObjPtr";  return; break;};
					//DEFUALT UNKNOWN
				default: {strReturn = "VarUnknown";  return; break;};

				};
			}catch(...){
				strReturn = "";
			};
			return;
		};

		template <>
		void stringToEnum<GtVarType>(std::string & strVal, GtVarType & enumValReturn)
		{
			try{
				if(strVal.empty()){enumValReturn = VarUnknown; return;};
				//check by comparison
				//HTL CPLUSPLUS NATIVE TYPES
				if(strVal == "VarUnknown"){enumValReturn = VarUnknown; return;};
				if(strVal == "CppChar"){enumValReturn = CppChar; return;};
				if(strVal == "CppUChar"){enumValReturn = CppUChar; return;};
				if(strVal == "CppShort"){enumValReturn = CppShort; return;};
				if(strVal == "CppUShort"){enumValReturn = CppUShort; return;};
				if(strVal == "CppInt"){enumValReturn = CppInt; return;};
				if(strVal == "CppUInt"){enumValReturn = CppUInt; return;};
				if(strVal == "CppLong"){enumValReturn = CppLong; return;};
				if(strVal == "CppULong"){enumValReturn = CppULong; return;};
				if(strVal == "CppLongLong"){enumValReturn = CppLongLong; return;};
				if(strVal == "CppULongLong"){enumValReturn = CppULongLong; return;};
				if(strVal == "CppFloat"){enumValReturn = CppFloat; return;};
				if(strVal == "CppDouble"){enumValReturn = CppDouble; return;};
				if(strVal == "GtObjPtr"){enumValReturn = GtObjPtr; return;};
				if(strVal == "VoidObjPtr"){enumValReturn = VoidObjPtr; return;};

				//DEFUALT UNKNOWN
				enumValReturn = VarUnknown;
				return;
			}catch(...){
				enumValReturn = VarUnknown;
				return;
			};
		};


		char GtKeyToChar(GtKey key,int modifiers)
		{
			//LOWER CASE FIRST///////////////////////////////////////////////
			if((key == Key_A)&& (!(modifiers & ShiftModifier))){return 'a';};
			if((key == Key_B)&& (!(modifiers & ShiftModifier))){return 'b';};
			if((key == Key_C)&& (!(modifiers & ShiftModifier))){return 'c';};
			if((key == Key_D)&& (!(modifiers & ShiftModifier))){return 'd';};
			if((key == Key_E)&& (!(modifiers & ShiftModifier))){return 'e';};
			if((key == Key_F)&& (!(modifiers & ShiftModifier))){return 'f';};
			if((key == Key_G)&& (!(modifiers & ShiftModifier))){return 'g';};
			if((key == Key_H)&& (!(modifiers & ShiftModifier))){return 'h';};
			if((key == Key_I)&& (!(modifiers & ShiftModifier))){return 'i';};
			if((key == Key_J)&& (!(modifiers & ShiftModifier))){return 'j';};
			if((key == Key_K)&& (!(modifiers & ShiftModifier))){return 'k';};
			if((key == Key_L)&& (!(modifiers & ShiftModifier))){return 'l';};
			if((key == Key_M)&& (!(modifiers & ShiftModifier))){return 'm';};
			if((key == Key_N)&& (!(modifiers & ShiftModifier))){return 'n';};
			if((key == Key_O)&& (!(modifiers & ShiftModifier))){return 'o';};
			if((key == Key_P)&& (!(modifiers & ShiftModifier))){return 'p';};
			if((key == Key_Q)&& (!(modifiers & ShiftModifier))){return 'q';};
			if((key == Key_R)&& (!(modifiers & ShiftModifier))){return 'r';};
			if((key == Key_S)&& (!(modifiers & ShiftModifier))){return 's';};
			if((key == Key_T)&& (!(modifiers & ShiftModifier))){return 't';};
			if((key == Key_U)&& (!(modifiers & ShiftModifier))){return 'u';};
			if((key == Key_V)&& (!(modifiers & ShiftModifier))){return 'v';};
			if((key == Key_W)&& (!(modifiers & ShiftModifier))){return 'w';};
			if((key == Key_X)&& (!(modifiers & ShiftModifier))){return 'x';};
			if((key == Key_Y)&& (!(modifiers & ShiftModifier))){return 'y';};
			if((key == Key_Z)&& (!(modifiers & ShiftModifier))){return 'z';};
			if((key == Key_1)&& (!(modifiers & ShiftModifier))){return '1';};
			if((key == Key_2)&& (!(modifiers & ShiftModifier))){return '2';};
			if((key == Key_3)&& (!(modifiers & ShiftModifier))){return '3';};
			if((key == Key_4)&& (!(modifiers & ShiftModifier))){return '4';};
			if((key == Key_5)&& (!(modifiers & ShiftModifier))){return '5';};
			if((key == Key_6)&& (!(modifiers & ShiftModifier))){return '6';};
			if((key == Key_7)&& (!(modifiers & ShiftModifier))){return '7';};
			if((key == Key_8)&& (!(modifiers & ShiftModifier))){return '8';};
			if((key == Key_9)&& (!(modifiers & ShiftModifier))){return '9';};
			if((key == Key_0)&& (!(modifiers & ShiftModifier))){return '0';};

			if((key == Key_Numpad0)&& (!(modifiers & ShiftModifier))){return '0';};
			if((key == Key_Numpad1)&& (!(modifiers & ShiftModifier))){return '1';};
			if((key == Key_Numpad2)&& (!(modifiers & ShiftModifier))){return '2';};
			if((key == Key_Numpad3)&& (!(modifiers & ShiftModifier))){return '3';};
			if((key == Key_Numpad4)&& (!(modifiers & ShiftModifier))){return '4';};
			if((key == Key_Numpad5)&& (!(modifiers & ShiftModifier))){return '5';};
			if((key == Key_Numpad6)&& (!(modifiers & ShiftModifier))){return '6';};
			if((key == Key_Numpad7)&& (!(modifiers & ShiftModifier))){return '7';};
			if((key == Key_Numpad8)&& (!(modifiers & ShiftModifier))){return '8';};
			if((key == Key_Numpad9)&& (!(modifiers & ShiftModifier))){return '9';};
			if((key == Key_Multiply)&& (!(modifiers & ShiftModifier))){return '*';};
			if((key == Key_Add)&& (!(modifiers & ShiftModifier))){return '+';};
			if((key == Key_Separator)&& (!(modifiers & ShiftModifier))){return ',';};
			if((key == Key_Subtract)&& (!(modifiers & ShiftModifier))){return '-';};
			if((key == Key_Decimal)&& (!(modifiers & ShiftModifier))){return '.';};
			if((key == Key_Divide)&& (!(modifiers & ShiftModifier))){return '/';};

			if((key == Key_OEM_SemiColon)&& (!(modifiers & ShiftModifier))){return ';';};
			if((key == Key_OEM_Plus)&& (!(modifiers & ShiftModifier))){return '=';};
			if((key == Key_OEM_Comma)&& (!(modifiers & ShiftModifier))){return ',';};
			if((key == Key_OEM_Minus)&& (!(modifiers & ShiftModifier))){return '-';};
			if((key == Key_OEM_Period)&& (!(modifiers & ShiftModifier))){return '.';};
			if((key == Key_OEM_Backslash)&& (!(modifiers & ShiftModifier))){return '/';};
			if((key == Key_OEM_Tilda)&& (!(modifiers & ShiftModifier))){return '`';};
			if((key == Key_OEM_OpenBracket)&& (!(modifiers & ShiftModifier))){return '[';};
			if((key == Key_OEM_Foreslash)&& (!(modifiers & ShiftModifier))){return '\\';};
			if((key == Key_OEM_CloseBracket)&& (!(modifiers & ShiftModifier))){return ']';};
			if((key == Key_OEM_Quote)&& (!(modifiers & ShiftModifier))){return '\'';};

			//UPPER CASE SECOND///////////////////////////////////////////////
			if((key == Key_A)&& ((modifiers & ShiftModifier))){return 'A';};
			if((key == Key_B)&& ((modifiers & ShiftModifier))){return 'B';};
			if((key == Key_C)&& ((modifiers & ShiftModifier))){return 'C';};
			if((key == Key_D)&& ((modifiers & ShiftModifier))){return 'D';};
			if((key == Key_E)&& ((modifiers & ShiftModifier))){return 'E';};
			if((key == Key_F)&& ((modifiers & ShiftModifier))){return 'F';};
			if((key == Key_G)&& ((modifiers & ShiftModifier))){return 'G';};
			if((key == Key_H)&& ((modifiers & ShiftModifier))){return 'H';};
			if((key == Key_I)&& ((modifiers & ShiftModifier))){return 'I';};
			if((key == Key_J)&& ((modifiers & ShiftModifier))){return 'J';};
			if((key == Key_K)&& ((modifiers & ShiftModifier))){return 'K';};
			if((key == Key_L)&& ((modifiers & ShiftModifier))){return 'L';};
			if((key == Key_M)&& ((modifiers & ShiftModifier))){return 'M';};
			if((key == Key_N)&& ((modifiers & ShiftModifier))){return 'N';};
			if((key == Key_O)&& ((modifiers & ShiftModifier))){return 'O';};
			if((key == Key_P)&& ((modifiers & ShiftModifier))){return 'P';};
			if((key == Key_Q)&& ((modifiers & ShiftModifier))){return 'Q';};
			if((key == Key_R)&& ((modifiers & ShiftModifier))){return 'R';};
			if((key == Key_S)&& ((modifiers & ShiftModifier))){return 'S';};
			if((key == Key_T)&& ((modifiers & ShiftModifier))){return 'T';};
			if((key == Key_U)&& ((modifiers & ShiftModifier))){return 'U';};
			if((key == Key_V)&& ((modifiers & ShiftModifier))){return 'V';};
			if((key == Key_W)&& ((modifiers & ShiftModifier))){return 'W';};
			if((key == Key_X)&& ((modifiers & ShiftModifier))){return 'X';};
			if((key == Key_Y)&& ((modifiers & ShiftModifier))){return 'Y';};
			if((key == Key_Z)&& ((modifiers & ShiftModifier))){return 'Z';};
			if((key == Key_1)&& ((modifiers & ShiftModifier))){return '!';};
			if((key == Key_2)&& ((modifiers & ShiftModifier))){return '@';};
			if((key == Key_3)&& ((modifiers & ShiftModifier))){return '#';};
			if((key == Key_4)&& ((modifiers & ShiftModifier))){return '$';};
			if((key == Key_5)&& ((modifiers & ShiftModifier))){return '%';};
			if((key == Key_6)&& ((modifiers & ShiftModifier))){return '^';};
			if((key == Key_7)&& ((modifiers & ShiftModifier))){return '&';};
			if((key == Key_8)&& ((modifiers & ShiftModifier))){return '*';};
			if((key == Key_9)&& ((modifiers & ShiftModifier))){return '(';};
			if((key == Key_0)&& ((modifiers & ShiftModifier))){return ')';};

			if((key == Key_Numpad0)&& ((modifiers & ShiftModifier))){return '0';};
			if((key == Key_Numpad1)&& ((modifiers & ShiftModifier))){return '1';};
			if((key == Key_Numpad2)&& ((modifiers & ShiftModifier))){return '2';};
			if((key == Key_Numpad3)&& ((modifiers & ShiftModifier))){return '3';};
			if((key == Key_Numpad4)&& ((modifiers & ShiftModifier))){return '4';};
			if((key == Key_Numpad5)&& ((modifiers & ShiftModifier))){return '5';};
			if((key == Key_Numpad6)&& ((modifiers & ShiftModifier))){return '6';};
			if((key == Key_Numpad7)&& ((modifiers & ShiftModifier))){return '7';};
			if((key == Key_Numpad8)&& ((modifiers & ShiftModifier))){return '8';};
			if((key == Key_Numpad9)&& ((modifiers & ShiftModifier))){return '9';};
			if((key == Key_Multiply)&& ((modifiers & ShiftModifier))){return '*';};
			if((key == Key_Add)&& ((modifiers & ShiftModifier))){return '+';};
			if((key == Key_Separator)&& ((modifiers & ShiftModifier))){return ',';};
			if((key == Key_Subtract)&& ((modifiers & ShiftModifier))){return '-';};
			if((key == Key_Decimal)&& ((modifiers & ShiftModifier))){return '.';};
			if((key == Key_Divide)&& ((modifiers & ShiftModifier))){return '/';};

			if((key == Key_OEM_SemiColon)&& ((modifiers & ShiftModifier))){return ':';};
			if((key == Key_OEM_Plus)&& ((modifiers & ShiftModifier))){return '+';};
			if((key == Key_OEM_Comma)&& ((modifiers & ShiftModifier))){return '<';};
			if((key == Key_OEM_Minus)&& ((modifiers & ShiftModifier))){return '_';};
			if((key == Key_OEM_Period)&& ((modifiers & ShiftModifier))){return '>';};
			if((key == Key_OEM_Backslash)&& ((modifiers & ShiftModifier))){return '?';};
			if((key == Key_OEM_Tilda)&& ((modifiers & ShiftModifier))){return '~';};
			if((key == Key_OEM_OpenBracket)&& ((modifiers & ShiftModifier))){return '{';};
			if((key == Key_OEM_Foreslash)&& ((modifiers & ShiftModifier))){return '|';};
			if((key == Key_OEM_CloseBracket)&& ((modifiers & ShiftModifier))){return '}';};
			if((key == Key_OEM_Quote)&& ((modifiers & ShiftModifier))){return '\"';};

			//shift independent keys
			if(key == Key_Space){return ' ';};
			return NULL;
		};

		wchar_t GtKeyToWChar(GtKey key,int modifiers)
		{
					//LOWER CASE FIRST///////////////////////////////////////////////
			if((key == Key_A)&& (!(modifiers & ShiftModifier))){return L'a';};
			if((key == Key_B)&& (!(modifiers & ShiftModifier))){return L'b';};
			if((key == Key_C)&& (!(modifiers & ShiftModifier))){return L'c';};
			if((key == Key_D)&& (!(modifiers & ShiftModifier))){return L'd';};
			if((key == Key_E)&& (!(modifiers & ShiftModifier))){return L'e';};
			if((key == Key_F)&& (!(modifiers & ShiftModifier))){return L'f';};
			if((key == Key_G)&& (!(modifiers & ShiftModifier))){return L'g';};
			if((key == Key_H)&& (!(modifiers & ShiftModifier))){return L'h';};
			if((key == Key_I)&& (!(modifiers & ShiftModifier))){return L'i';};
			if((key == Key_J)&& (!(modifiers & ShiftModifier))){return L'j';};
			if((key == Key_K)&& (!(modifiers & ShiftModifier))){return L'k';};
			if((key == Key_L)&& (!(modifiers & ShiftModifier))){return L'l';};
			if((key == Key_M)&& (!(modifiers & ShiftModifier))){return L'm';};
			if((key == Key_N)&& (!(modifiers & ShiftModifier))){return L'n';};
			if((key == Key_O)&& (!(modifiers & ShiftModifier))){return L'o';};
			if((key == Key_P)&& (!(modifiers & ShiftModifier))){return L'p';};
			if((key == Key_Q)&& (!(modifiers & ShiftModifier))){return L'q';};
			if((key == Key_R)&& (!(modifiers & ShiftModifier))){return L'r';};
			if((key == Key_S)&& (!(modifiers & ShiftModifier))){return L's';};
			if((key == Key_T)&& (!(modifiers & ShiftModifier))){return L't';};
			if((key == Key_U)&& (!(modifiers & ShiftModifier))){return L'u';};
			if((key == Key_V)&& (!(modifiers & ShiftModifier))){return L'v';};
			if((key == Key_W)&& (!(modifiers & ShiftModifier))){return L'w';};
			if((key == Key_X)&& (!(modifiers & ShiftModifier))){return L'x';};
			if((key == Key_Y)&& (!(modifiers & ShiftModifier))){return L'y';};
			if((key == Key_Z)&& (!(modifiers & ShiftModifier))){return L'z';};
			if((key == Key_1)&& (!(modifiers & ShiftModifier))){return L'1';};
			if((key == Key_2)&& (!(modifiers & ShiftModifier))){return L'2';};
			if((key == Key_3)&& (!(modifiers & ShiftModifier))){return L'3';};
			if((key == Key_4)&& (!(modifiers & ShiftModifier))){return L'4';};
			if((key == Key_5)&& (!(modifiers & ShiftModifier))){return L'5';};
			if((key == Key_6)&& (!(modifiers & ShiftModifier))){return L'6';};
			if((key == Key_7)&& (!(modifiers & ShiftModifier))){return L'7';};
			if((key == Key_8)&& (!(modifiers & ShiftModifier))){return L'8';};
			if((key == Key_9)&& (!(modifiers & ShiftModifier))){return L'9';};
			if((key == Key_0)&& (!(modifiers & ShiftModifier))){return L'0';};

			if((key == Key_Numpad0)&& (!(modifiers & ShiftModifier))){return L'0';};
			if((key == Key_Numpad1)&& (!(modifiers & ShiftModifier))){return L'1';};
			if((key == Key_Numpad2)&& (!(modifiers & ShiftModifier))){return L'2';};
			if((key == Key_Numpad3)&& (!(modifiers & ShiftModifier))){return L'3';};
			if((key == Key_Numpad4)&& (!(modifiers & ShiftModifier))){return L'4';};
			if((key == Key_Numpad5)&& (!(modifiers & ShiftModifier))){return L'5';};
			if((key == Key_Numpad6)&& (!(modifiers & ShiftModifier))){return L'6';};
			if((key == Key_Numpad7)&& (!(modifiers & ShiftModifier))){return L'7';};
			if((key == Key_Numpad8)&& (!(modifiers & ShiftModifier))){return L'8';};
			if((key == Key_Numpad9)&& (!(modifiers & ShiftModifier))){return L'9';};
			if((key == Key_Multiply)&& (!(modifiers & ShiftModifier))){return L'*';};
			if((key == Key_Add)&& (!(modifiers & ShiftModifier))){return L'+';};
			if((key == Key_Separator)&& (!(modifiers & ShiftModifier))){return L',';};
			if((key == Key_Subtract)&& (!(modifiers & ShiftModifier))){return L'-';};
			if((key == Key_Decimal)&& (!(modifiers & ShiftModifier))){return L'.';};
			if((key == Key_Divide)&& (!(modifiers & ShiftModifier))){return L'/';};

			if((key == Key_OEM_SemiColon)&& (!(modifiers & ShiftModifier))){return L';';};
			if((key == Key_OEM_Plus)&& (!(modifiers & ShiftModifier))){return L'=';};
			if((key == Key_OEM_Comma)&& (!(modifiers & ShiftModifier))){return L',';};
			if((key == Key_OEM_Minus)&& (!(modifiers & ShiftModifier))){return L'-';};
			if((key == Key_OEM_Period)&& (!(modifiers & ShiftModifier))){return L'.';};
			if((key == Key_OEM_Backslash)&& (!(modifiers & ShiftModifier))){return L'/';};
			if((key == Key_OEM_Tilda)&& (!(modifiers & ShiftModifier))){return L'`';};
			if((key == Key_OEM_OpenBracket)&& (!(modifiers & ShiftModifier))){return L'[';};
			if((key == Key_OEM_Foreslash)&& (!(modifiers & ShiftModifier))){return L'\\';};
			if((key == Key_OEM_CloseBracket)&& (!(modifiers & ShiftModifier))){return L']';};
			if((key == Key_OEM_Quote)&& (!(modifiers & ShiftModifier))){return L'\'';};


			//LOWER CASE FIRST///////////////////////////////////////////////
			if((key == Key_A)&& ((modifiers & ShiftModifier))){return L'A';};
			if((key == Key_B)&& ((modifiers & ShiftModifier))){return L'B';};
			if((key == Key_C)&& ((modifiers & ShiftModifier))){return L'C';};
			if((key == Key_D)&& ((modifiers & ShiftModifier))){return L'D';};
			if((key == Key_E)&& ((modifiers & ShiftModifier))){return L'E';};
			if((key == Key_F)&& ((modifiers & ShiftModifier))){return L'F';};
			if((key == Key_G)&& ((modifiers & ShiftModifier))){return L'G';};
			if((key == Key_H)&& ((modifiers & ShiftModifier))){return L'H';};
			if((key == Key_I)&& ((modifiers & ShiftModifier))){return L'I';};
			if((key == Key_J)&& ((modifiers & ShiftModifier))){return L'J';};
			if((key == Key_K)&& ((modifiers & ShiftModifier))){return L'K';};
			if((key == Key_L)&& ((modifiers & ShiftModifier))){return L'L';};
			if((key == Key_M)&& ((modifiers & ShiftModifier))){return L'M';};
			if((key == Key_N)&& ((modifiers & ShiftModifier))){return L'N';};
			if((key == Key_O)&& ((modifiers & ShiftModifier))){return L'O';};
			if((key == Key_P)&& ((modifiers & ShiftModifier))){return L'P';};
			if((key == Key_Q)&& ((modifiers & ShiftModifier))){return L'Q';};
			if((key == Key_R)&& ((modifiers & ShiftModifier))){return L'R';};
			if((key == Key_S)&& ((modifiers & ShiftModifier))){return L'S';};
			if((key == Key_T)&& ((modifiers & ShiftModifier))){return L'T';};
			if((key == Key_U)&& ((modifiers & ShiftModifier))){return L'U';};
			if((key == Key_V)&& ((modifiers & ShiftModifier))){return L'V';};
			if((key == Key_W)&& ((modifiers & ShiftModifier))){return L'W';};
			if((key == Key_X)&& ((modifiers & ShiftModifier))){return L'X';};
			if((key == Key_Y)&& ((modifiers & ShiftModifier))){return L'Y';};
			if((key == Key_Z)&& ((modifiers & ShiftModifier))){return L'Z';};
			if((key == Key_1)&& ((modifiers & ShiftModifier))){return L'!';};
			if((key == Key_2)&& ((modifiers & ShiftModifier))){return L'@';};
			if((key == Key_3)&& ((modifiers & ShiftModifier))){return L'#';};
			if((key == Key_4)&& ((modifiers & ShiftModifier))){return L'$';};
			if((key == Key_5)&& ((modifiers & ShiftModifier))){return L'%';};
			if((key == Key_6)&& ((modifiers & ShiftModifier))){return L'^';};
			if((key == Key_7)&& ((modifiers & ShiftModifier))){return L'&';};
			if((key == Key_8)&& ((modifiers & ShiftModifier))){return L'*';};
			if((key == Key_9)&& ((modifiers & ShiftModifier))){return L'(';};
			if((key == Key_0)&& ((modifiers & ShiftModifier))){return L')';};

			if((key == Key_Numpad0)&& ((modifiers & ShiftModifier))){return L'0';};
			if((key == Key_Numpad1)&& ((modifiers & ShiftModifier))){return L'1';};
			if((key == Key_Numpad2)&& ((modifiers & ShiftModifier))){return L'2';};
			if((key == Key_Numpad3)&& ((modifiers & ShiftModifier))){return L'3';};
			if((key == Key_Numpad4)&& ((modifiers & ShiftModifier))){return L'4';};
			if((key == Key_Numpad5)&& ((modifiers & ShiftModifier))){return L'5';};
			if((key == Key_Numpad6)&& ((modifiers & ShiftModifier))){return L'6';};
			if((key == Key_Numpad7)&& ((modifiers & ShiftModifier))){return L'7';};
			if((key == Key_Numpad8)&& ((modifiers & ShiftModifier))){return L'8';};
			if((key == Key_Numpad9)&& ((modifiers & ShiftModifier))){return L'9';};
			if((key == Key_Multiply)&& ((modifiers & ShiftModifier))){return L'*';};
			if((key == Key_Add)&& ((modifiers & ShiftModifier))){return L'+';};
			if((key == Key_Separator)&& ((modifiers & ShiftModifier))){return L',';};
			if((key == Key_Subtract)&& ((modifiers & ShiftModifier))){return L'-';};
			if((key == Key_Decimal)&& ((modifiers & ShiftModifier))){return L'.';};
			if((key == Key_Divide)&& ((modifiers & ShiftModifier))){return L'/';};

			if((key == Key_OEM_SemiColon)&& ((modifiers & ShiftModifier))){return L':';};
			if((key == Key_OEM_Plus)&& ((modifiers & ShiftModifier))){return L'+';};
			if((key == Key_OEM_Comma)&& ((modifiers & ShiftModifier))){return L'<';};
			if((key == Key_OEM_Minus)&& ((modifiers & ShiftModifier))){return L'_';};
			if((key == Key_OEM_Period)&& ((modifiers & ShiftModifier))){return L'>';};
			if((key == Key_OEM_Backslash)&& ((modifiers & ShiftModifier))){return L'?';};
			if((key == Key_OEM_Tilda)&& ((modifiers & ShiftModifier))){return L'~';};
			if((key == Key_OEM_OpenBracket)&& ((modifiers & ShiftModifier))){return L'{';};
			if((key == Key_OEM_Foreslash)&& ((modifiers & ShiftModifier))){return L'|';};
			if((key == Key_OEM_CloseBracket)&& ((modifiers & ShiftModifier))){return L'}';};
			if((key == Key_OEM_Quote)&& ((modifiers & ShiftModifier))){return L'\"';};


			//shift independent keys
			if(key == Key_Space){return L' ';};
			return NULL;
			
		};




	};//end namespace GtCore

};//end namespace GT