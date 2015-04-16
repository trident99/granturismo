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


#include  ".\GtPlane.h"
using namespace GT;
using namespace GT::GtCore;

#include "modHtlArchive.h"
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		//TGLPPLANE///////////////////////////////////////////////////////
		GtPlane::GtPlane()
		{
			m_objOrigin.Zero();
			m_objNormal.Zero();
		};

		GtPlane::GtPlane(const GtPlane & rhs)
		{
			m_objOrigin = rhs.m_objOrigin;
			m_objNormal = rhs.m_objNormal;
		};
		GtPlane::~GtPlane()
		{
			return;
		};
		GtPlane & GtPlane::operator = (const GtPlane & rhs)
		{
			if(this == &rhs)
				return *this;

			m_objOrigin = rhs.m_objOrigin;
			m_objNormal = rhs.m_objNormal;
			return *this;
		};
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtPlane::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<GtPoint3DF,HTL_BASE>(ptrCurrNode,"m_objOrigin",m_objOrigin,false);
			intReturn &= SetHtlMemVar<GtPoint3DF,HTL_BASE>(ptrCurrNode,"m_objNormal",m_objNormal,false);
			return intReturn;
		};

		int GtPlane::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<GtPoint3DF,HTL_BASE>(ptrCurrNode,"m_objOrigin",m_objOrigin);
			intReturn &= GetHtlMemVar<GtPoint3DF,HTL_BASE>(ptrCurrNode,"m_objNormal",m_objNormal);
			return intReturn;

		};
	};//end namespace GtCore
};//end namespace GT