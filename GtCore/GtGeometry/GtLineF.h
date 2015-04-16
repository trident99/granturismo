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
#ifndef GT_LINEF_H
#define GT_LINEF_H

#include "..\GtCoreLibRefs.h"
#include ".\GtPoint3DF.h"

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{
		class HTL_DLLAPI GtLineF : public HtlBase
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			GtLineF(void);
			GtLineF(GtPoint3DF & start, GtPoint3DF & end);
			GtLineF(const GtLineF& rhs);
			virtual ~GtLineF(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtLineF & operator = (const GtLineF & rhs);
			//!EQUAL TO Operator
			bool operator == (const GtLineF & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (const GtLineF & rhs);

			//!zero the line
			void Zero(void);
			//Is the size null
			bool IsNull(void);
			//Is the size valid
			bool IsValid(void);


		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			//!Point 0 (start)
			GtPoint3DF m_P0;
			//!Point 1 (end)
			GtPoint3DF m_P1;
		};



	};//end namespace GtCore
};//end namepace GT
#endif //GT_LINEF_H