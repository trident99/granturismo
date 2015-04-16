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

#include ".\GtFont.h"
#include "..\GtMath\GtBasicMath.h"
#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		//!Default Constructor
		GtFont::GtFont()
			: HtlBase()
		{
			m_strFontFamily = L"Arial";
			m_intPoint = 20;

		};

		//!Font Family Constructor
		GtFont::GtFont(std::wstring strFontName, GtColor& val, int intFlags)
		{
			m_strFontFamily = strFontName;
			m_intPoint = 20;
			m_objColor = val;
			m_intFontStyle = intFlags;
		};

		//!Destructor
		GtFont::~GtFont()
		{
			//do nothing
		};

		//operator overloads
		GtFont & GtFont::operator= ( GtFont & rhs)
		{
			if(&rhs != this)
			{
				m_strFontFamily = rhs.Get_strFontFamily();
				m_intPoint = rhs.Get_intPoint();
				m_objColor = rhs.Get_objColor();
				m_intFontStyle = rhs.Get_intFontStyle();
			}
			return (*this);
		};

		bool GtFont::operator == (GtFont & rhs )
		{
			if(	m_strFontFamily != rhs.Get_strFontFamily()){return false;};
			if(	m_intPoint != rhs.Get_intPoint()){return false;};
			if(	m_objColor != rhs.Get_objColor()){return false;};
			if(	m_intFontStyle != rhs.Get_intFontStyle()){return false;};
			//else made it through, equal
			return true;
		};

		bool GtFont::operator != (GtFont & rhs )
		{
			if(	m_strFontFamily != rhs.Get_strFontFamily()){return true;};
			if(	m_intPoint != rhs.Get_intPoint()){return true;};
			if(	m_objColor != rhs.Get_objColor()){return true;};
			if(	m_intFontStyle != rhs.Get_intFontStyle()){return true;};
			//else made it through, equal
			return false;		
		};


	//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtFont::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			//intReturn &= SetHtlMemVar<std::wstring,STL_STRING>(ptrCurrNode,"m_strFontFamily",m_strFontFamily,false);
			intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intPoint",m_intPoint,false);
			intReturn &= SetHtlMemVar<GtColor,HTL_BASE>(ptrCurrNode,"m_objColor",m_objColor,false);
			intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intFontStyle",m_intFontStyle,false);
			return intReturn;
		};

		int GtFont::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			//intReturn &= GetHtlMemVar<std::wstring,STL_STRING>(ptrCurrNode,"m_strFontFamily",m_strFontFamily);
			intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intPoint",m_intPoint);
			intReturn &= GetHtlMemVar<GtColor,HTL_BASE>(ptrCurrNode,"m_objColor",m_objColor);
			intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intFontStyle",m_intFontStyle);

			return intReturn;

		};



	};//end namespace GtCore

};//end namespace GT

