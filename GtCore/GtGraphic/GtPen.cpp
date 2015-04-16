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

#include ".\GtPen.h"
#include "..\GtMath\GtBasicMath.h"
#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		//!Default Constructor
		GtPen::GtPen()
			: HtlBase()
		{
			this->m_sngWidth = 1.0f;
			this->m_objStyle = SolidLine;
			this->m_objJoinStyle = MiterJoin;
			this->m_objColor.SetRGB(0,0,0);		
		};

		GtPen::GtPen(GtColor color, GtPenStyle style, float width)
		{
			this->m_sngWidth = width;
			this->m_objStyle = style;
			this->m_objJoinStyle = MiterJoin;
			this->m_objColor = color;	
		};

		GtPen::GtPen(const GtPen & rhs)
		{
			this->m_sngWidth = rhs.Get_sngWidth();
			this->m_objStyle = rhs.Get_objStyle();
			this->m_objJoinStyle = rhs.Get_objJoinStyle();
			this->m_objColor = rhs.Get_objColor();	
		};

		//!Destructor
		GtPen::~GtPen()
		{
			//do nothing
		};

		//operator overloads
		GtPen & GtPen::operator= (const GtPen & rhs)
		{
			if(&rhs != this)
			{
				m_sngWidth = rhs.Get_sngWidth();
				m_objStyle = rhs.Get_objStyle();
				m_objJoinStyle = rhs.Get_objJoinStyle();
				m_objColor = rhs.Get_objColor();
			}
			return (*this);
		};

		bool GtPen::operator == (GtPen & rhs )
		{
			if(	m_sngWidth != rhs.Get_sngWidth()){return false;};
			if(	m_objStyle != rhs.Get_objStyle()){return false;};
			if(	m_objJoinStyle != rhs.Get_objJoinStyle()){return false;};
			if(	m_objColor != rhs.Get_objColor()){return false;};
			//else made it through, equal
			return true;
		};
		bool GtPen::operator != (GtPen & rhs )
		{
			if(	m_sngWidth != rhs.Get_sngWidth()){return true;};
			if(	m_objStyle != rhs.Get_objStyle()){return true;};
			if(	m_objJoinStyle != rhs.Get_objJoinStyle()){return true;};
			if(	m_objColor != rhs.Get_objColor()){return true;};
			//else made it through, equal
			return false;		
		};

	//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtPen::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<float,CPP_FLOAT>(ptrCurrNode,"m_sngWidth",m_sngWidth,false);
			intReturn &= SetHtlMemVar<GtPenStyle,HTL_ENUM>(ptrCurrNode,"m_objStyle",m_objStyle,false);
			intReturn &= SetHtlMemVar<GtPenJoinStyle,HTL_ENUM>(ptrCurrNode,"m_objJoinStyle",m_objJoinStyle,false);

			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				intReturn &= SetHtlMemVar<GtColor,HTL_BASE>(ptrCurrNode,"m_objColor",m_objColor,false);
			};

			return intReturn;
		};

		int GtPen::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<float,CPP_FLOAT>(ptrCurrNode,"m_sngWidth",m_sngWidth);
			intReturn &= GetHtlMemVar<GtPenStyle,HTL_ENUM>(ptrCurrNode,"m_objStyle",m_objStyle);
			intReturn &= GetHtlMemVar<GtPenJoinStyle,HTL_ENUM>(ptrCurrNode,"m_objJoinStyle",m_objJoinStyle);

			intReturn &= GetHtlMemVar<GtColor,HTL_BASE>(ptrCurrNode,"m_objColor",m_objColor);

			return intReturn;

		};



	};//end namespace GtCore

};//end namespace GT







