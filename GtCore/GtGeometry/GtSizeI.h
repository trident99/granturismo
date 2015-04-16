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
#ifndef GT_SIZEI_H
#define GT_SIZEI_H

#include "..\GtCoreLibRefs.h"

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{
		class HTL_DLLAPI GtSizeI : public HtlBase
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			//GtSizeI(void);
			GtSizeI(long dX = 0, long dY = 0);
			GtSizeI(const GtSizeI& rhs);
			virtual ~GtSizeI(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtSizeI & operator = (const GtSizeI & rhs);
			//!EQUAL TO Operator
			bool operator == (const GtSizeI & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (const GtSizeI & rhs);
			//!LESS THAN Operator
			bool operator < (const GtSizeI & rhs);
			//!GREATER THAN Operator
			bool operator > (const GtSizeI & rhs);
			//!Multiplicative compound operator
			GtSizeI & operator*=(double factor);
			//!Additive compound operator
			GtSizeI & operator+=(const GtSizeI & rhs);
			//!Subtractive compound operator
			GtSizeI & operator-=(const GtSizeI & rhs);
			//!Divisive compound operator
			GtSizeI & operator/=(double divisor);
			//!zero the size
			void Zero(void);
			//Is the size null
			bool IsNull(void) const;
			//Is the size valid
			bool IsValid(void) const;
			//Transpose the size
			void Transpose(void);

			inline long Width(void){return deltaX;};
			inline long Height(void){return deltaY;};

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			//size in width X Direction
			long deltaX;
			//size in height Y Direction
			long deltaY;
		};



	};//end namespace GtCore
};//end namepace GT
#endif //GT_SIZEF_H