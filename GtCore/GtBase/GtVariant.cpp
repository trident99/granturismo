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


#include ".\GtVariant.h"
#include ".\GtObject.h"
#include <modHtlArchive.h>

namespace GT
{
	namespace GtCore
	{

		//!Constructors
		GtVariant::GtVariant()
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = VarUnknown;
			memset(&m_varData,0,sizeof(GtVarData));
		};
		GtVariant::GtVariant(char varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppChar;
			m_varData.c = varVal;
		};
		GtVariant::GtVariant(uchar varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppUChar;
			m_varData.uc = varVal;
		};
		GtVariant::GtVariant(short varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppShort;
			m_varData.s = varVal;
		};
		GtVariant::GtVariant(ushort varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppUShort;
			m_varData.us = varVal;
		};
		GtVariant::GtVariant(long varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppLong;
			m_varData.l = varVal;
		};
		GtVariant::GtVariant(ulong varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppULong;
			m_varData.ul = varVal;
		};
		GtVariant::GtVariant(longlong varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppLongLong;
			m_varData.ll = varVal;
		};
		GtVariant::GtVariant(ulonglong varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppULongLong;
			m_varData.ull = varVal;
		};
		GtVariant::GtVariant(float varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppFloat;
			m_varData.f = varVal;
		};
		GtVariant::GtVariant(double varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = CppDouble;
			m_varData.d = varVal;
		};
		GtVariant::GtVariant(GtObject* varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = GtObjPtr;
			m_varData.ptrObj = varVal;
		};
		GtVariant::GtVariant(void* varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = VoidObjPtr;
			m_varData.ptrVoid = varVal;
		};

		GtVariant::GtVariant(std::string & varVal)
		{
			this->m_strType = "GtVariant";
			this->m_objType = HTL_BASE;
			this->m_varType = StlString;
			m_strData = varVal;
		};
		;
		//!Virtual destructor
		GtVariant::~GtVariant(void)
		{
			this->m_strType.clear();
			this->m_objType = HTL_BASE;
			this->m_varType = VarUnknown;
			memset(&m_varData,0,sizeof(GtVarData));
		};

		//!Assignment operators/////////////////////////////////////////
		GtVariant & GtVariant::operator= (const GtVariant & rhs)
		{
			m_varType = rhs.GetVarType();
			m_varData = rhs.GetVarData();
			return *this;
		};

		GtVariant & GtVariant::operator= ( const char & rhs)
		{
			m_varType = CppChar;
			m_varData.c = rhs;
			return *this;
		};

		GtVariant & GtVariant::operator= ( const uchar & rhs)
		{
			m_varType = CppUChar;
			m_varData.uc = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const short & rhs)
		{
			m_varType = CppShort;
			m_varData.s = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const ushort & rhs)
		{
			m_varType = CppUShort;
			m_varData.us = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const int & rhs)
		{
			m_varType = CppInt;
			m_varData.i = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const uint & rhs)
		{
			m_varType = CppUInt;
			m_varData.ui = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const long & rhs)
		{
			m_varType = CppLong;
			m_varData.l = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const ulong & rhs)
		{
			m_varType = CppULong;
			m_varData.ul = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const longlong & rhs)
		{
			m_varType = CppLongLong;
			m_varData.ll = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const ulonglong & rhs)
		{
			m_varType = CppULongLong;
			m_varData.ull = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const float & rhs)
		{
			m_varType = CppFloat;
			m_varData.f = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= ( const double & rhs)
		{
			m_varType = CppDouble;
			m_varData.d = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= (GtObject* & rhs)
		{
			m_varType = GtObjPtr;
			m_varData.ptrObj = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= (void* & rhs)
		{
			m_varType = VoidObjPtr;
			m_varData.ptrVoid = rhs;
			return *this;
		};
		GtVariant & GtVariant::operator= (std::string & rhs)
		{
			m_varType = StlString;
			m_strData = rhs;
			return *this;
		};

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtVariant::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};

			std::string strTemp;
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			GtCore::enumToString<GtVarType>(m_varType,strTemp);
			intReturn &= SetHtlMemVar<std::string,STL_STRING>(ptrCurrNode,"m_varType",strTemp,false);

			switch(m_varType)
			{
			case CppChar:
				{
					intReturn &= SetHtlMemVar<char,CPP_CHAR>(ptrCurrNode,"m_varData",m_varData.c,false);
					break;
				}
			case CppUChar:
				{
					intReturn &= SetHtlMemVar<uchar,CPP_UCHAR>(ptrCurrNode,"m_varData",m_varData.uc,false);
					break;
				}
			case CppShort:
				{
					intReturn &= SetHtlMemVar<short,CPP_SHORT>(ptrCurrNode,"m_varData",m_varData.s,false);
					break;
				}
			case CppUShort:
				{
					intReturn &= SetHtlMemVar<ushort,CPP_USHORT>(ptrCurrNode,"m_varData",m_varData.us,false);
					break;
				}
			case CppInt:
				{
					intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_varData",m_varData.i,false);
					break;
				}
			case CppUInt:
				{
					intReturn &= SetHtlMemVar<uint,CPP_UINT>(ptrCurrNode,"m_varData",m_varData.ui,false);
					break;
				}
			case CppLong:
				{
					intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"m_varData",m_varData.l,false);
					break;
				}
			case CppULong:
				{
					intReturn &= SetHtlMemVar<ulong,CPP_ULONG>(ptrCurrNode,"m_varData",m_varData.ul,false);
					break;
				}
			case CppLongLong:
				{
					intReturn &= SetHtlMemVar<longlong,CPP_LONGLONG>(ptrCurrNode,"m_varData",m_varData.ll,false);
					break;
				}
			case CppULongLong:
				{
					intReturn &= SetHtlMemVar<ulonglong,CPP_ULONGLONG>(ptrCurrNode,"m_varData",m_varData.ull,false);
					break;
				}
			case CppFloat:
				{
					intReturn &= SetHtlMemVar<float,CPP_FLOAT>(ptrCurrNode,"m_varData",m_varData.f,false);
					break;
				}
			case CppDouble:
				{
					intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_varData",m_varData.d,false);
					break;
				}
			case GtObjPtr:
				{
					intReturn &= SetHtlMemVar<GtObject*,HTL_BASE_PTR>(ptrCurrNode,"m_varData",m_varData.ptrObj,false);
					break;
				}
			default:
				{
					//do nothing
					break;
				}
			}//end switch on var type
			return intReturn;
		};

		int GtVariant::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			std::string strTemp;
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			//Standard Member Variables
			intReturn &= GetHtlMemVar<std::string,STL_STRING>(ptrCurrNode,"m_varType",strTemp);
			GtCore::stringToEnum<GtVarType>(strTemp,m_varType);
			switch(m_varType)
			{
			case CppChar:
				{
					intReturn &= GetHtlMemVar<char,CPP_CHAR>(ptrCurrNode,"m_varData",m_varData.c);
					break;
				}
			case CppUChar:
				{
					intReturn &= GetHtlMemVar<uchar,CPP_UCHAR>(ptrCurrNode,"m_varData",m_varData.uc);
					break;
				}
			case CppShort:
				{
					intReturn &= GetHtlMemVar<short,CPP_SHORT>(ptrCurrNode,"m_varData",m_varData.s);
					break;
				}
			case CppUShort:
				{
					intReturn &= GetHtlMemVar<ushort,CPP_USHORT>(ptrCurrNode,"m_varData",m_varData.us);
					break;
				}
			case CppInt:
				{
					intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_varData",m_varData.i);
					break;
				}
			case CppUInt:
				{
					intReturn &= GetHtlMemVar<uint,CPP_UINT>(ptrCurrNode,"m_varData",m_varData.ui);
					break;
				}
			case CppLong:
				{
					intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"m_varData",m_varData.l);
					break;
				}
			case CppULong:
				{
					intReturn &= GetHtlMemVar<ulong,CPP_ULONG>(ptrCurrNode,"m_varData",m_varData.ul);
					break;
				}
			case CppLongLong:
				{
					intReturn &= GetHtlMemVar<longlong,CPP_LONGLONG>(ptrCurrNode,"m_varData",m_varData.ll);
					break;
				}
			case CppULongLong:
				{
					intReturn &= GetHtlMemVar<ulonglong,CPP_ULONGLONG>(ptrCurrNode,"m_varData",m_varData.ull);
					break;
				}
			case CppFloat:
				{
					intReturn &= GetHtlMemVar<float,CPP_FLOAT>(ptrCurrNode,"m_varData",m_varData.f);
					break;
				}
			case CppDouble:
				{
					intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_varData",m_varData.d);
					break;
				}
			case GtObjPtr:
				{
					intReturn &= GetHtlMemVar<GtObject*,HTL_BASE_PTR>(ptrCurrNode,"m_varData",m_varData.ptrObj);
					break;
				}
			default:
				{
					//do nothing
					break;
				}
			}//end switch on var type
			return intReturn;

		};





	};//end namspace GtCore

};//end namespace GT