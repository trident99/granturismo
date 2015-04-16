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

#include "..\GtMath\GtBasicMath.h"
#include  ".\GtLineI.h"

#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		GtLineI::GtLineI(void)
		{
			m_strType = "GtLineI";
			m_P0.Zero();
			m_P1.Zero();
		};

		GtLineI::GtLineI(GtPoint3DI & start, GtPoint3DI & end)
		{
			m_strType = "GtLineI";
			m_P0 = start;
			m_P1 = end;
		};
		GtLineI::GtLineI(const GtLineI& rhs)
		{
			m_strType = "GtLineI";
			m_P0 = rhs.m_P0;
			m_P1 = rhs.m_P1;			
		};
		GtLineI::~GtLineI(void)
		{
			this->Zero();
		};
		//PUBLIC OPERATOR
		//!Assignment Operator
		GtLineI & GtLineI::operator = (const GtLineI & rhs)
		{
			m_strType = "GtLineI";
			if(&rhs != this)
			{
				m_P0 = rhs.m_P0;
				m_P1 = rhs.m_P1;
			}
			return *this;
		};
		//!EQUAL TO Operator
		bool GtLineI::operator == (const GtLineI & rhs)
		{
			if(m_P0 != rhs.m_P0){return false;};
			if(m_P1 != rhs.m_P1){return false;};
			return true;
		};
		//!NOT EQUAL TO Operator
		bool GtLineI::operator != (const GtLineI & rhs)
		{
			if(m_P0 != rhs.m_P0){return true;};
			if(m_P1 != rhs.m_P1){return true;};
			return false;
		};

		//!zero the size
		void GtLineI::Zero(void)
		{
			m_P0.Zero();
			m_P1.Zero();
		};
		//Is the size null
		bool GtLineI::IsNull(void)
		{
			GtPoint3DI ptNull;
			ptNull.Zero();

			return( (m_P0 == ptNull) && (m_P1 == ptNull) );
		};
		//Is the size valid
		bool GtLineI::IsValid(void)
		{
			return (m_P0 != m_P1);
		};


		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtLineI::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<GtPoint3DI,HTL_BASE>(ptrCurrNode,"m_P0",m_P0,false);
			intReturn &= SetHtlMemVar<GtPoint3DI,HTL_BASE>(ptrCurrNode,"m_P1",m_P1,false);

			return intReturn;


		};

		int GtLineI::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<GtPoint3DI,HTL_BASE>(ptrCurrNode,"m_P0",m_P0);
			intReturn &= GetHtlMemVar<GtPoint3DI,HTL_BASE>(ptrCurrNode,"m_P1",m_P1);
			return intReturn;

		};

	};//end namespace GtCore

};//end namespace GT