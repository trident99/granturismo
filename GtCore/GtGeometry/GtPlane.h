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
#ifndef GT_PLANE_H
#define GT_PLANE_H

#include ".\GtPoint3DF.h"


#include "modHtlBase.h"
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		class HTL_DLLAPI GtPlane : public HtlBase
		{
		public:
			GtPlane();
			GtPlane(const GtPlane & rhs);
			virtual ~GtPlane(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtPlane & operator = (const GtPlane & rhs);

			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//!Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//!Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);
		public:
			//!Plane Origin
			GtPoint3DF m_objOrigin;
			//!Plane Normal
			GtPoint3DF m_objNormal;
		};
	};//end namespace GtCore
};//end namespace GT
#endif