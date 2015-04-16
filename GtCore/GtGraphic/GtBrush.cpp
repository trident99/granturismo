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

#include ".\GtBrush.h"
#include "..\GtMath\GtBasicMath.h"
#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		//!Default Constructor
		GtBrush::GtBrush()
			: HtlBase()
		{
			this->m_objStyle = SolidPattern;
			this->m_objColor.SetRGB(0,0,0);		
		};

		GtBrush::GtBrush( GtColor & color, GtBrushStyle style)
		{
			this->m_objStyle = style;
			this->m_objColor = color;	
		};
		
		GtBrush::GtBrush(const GtBrush & rhs)
		{
			if(&rhs != this)
			{
				this->m_objStyle = rhs.Get_objStyle();
				this->m_objColor = rhs.Get_objColor();	
				this->m_objTexture = rhs.Get_objTexture();
			};
		};
		//!Destructor
		GtBrush::~GtBrush()
		{
			//do nothing
		};

		//operator overloads
		GtBrush & GtBrush::operator= (const GtBrush & rhs)
		{
			if(&rhs != this)
			{
				this->m_objStyle = rhs.Get_objStyle();
				this->m_objColor = rhs.Get_objColor();	
				this->m_objTexture = rhs.Get_objTexture();
			}
			return (*this);
		};

		bool GtBrush::operator == (GtBrush & rhs )
		{
			if(	m_objStyle != rhs.Get_objStyle()){return false;};
			if(	m_objColor != rhs.Get_objColor()){return false;};
			//else made it through, equal
			return true;
		};
		bool GtBrush::operator != (GtBrush & rhs )
		{
			if(	m_objStyle != rhs.Get_objStyle()){return true;};
			if(	m_objColor != rhs.Get_objColor()){return true;};
			//else made it through, equal
			return false;		
		};

	//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtBrush::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<GtBrushStyle,HTL_ENUM>(ptrCurrNode,"m_objStyle",m_objStyle,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				intReturn &= SetHtlMemVar<GtColor,HTL_BASE>(ptrCurrNode,"m_objColor",m_objColor,false);
			};

			return intReturn;
		};

		int GtBrush::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<GtBrushStyle,HTL_ENUM>(ptrCurrNode,"m_objStyle",m_objStyle);
			intReturn &= GetHtlMemVar<GtColor,HTL_BASE>(ptrCurrNode,"m_objColor",m_objColor);

			return intReturn;

		};



	};//end namespace GtCore

};//end namespace GT







