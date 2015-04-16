/*
**	This file is part of the TridentCAD
**	This software was merged and developed by:
**	
**  Anthony Daniels
**
**  TridentCAD is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to TridentCAD.
**
**  TridentCAD is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with TridentCAD.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#ifndef GT_POLYLINEI_H
#define GT_POLYLINEI_H

#include ".\GtPoint3DI.h"
#include <modHtlContainer.h>

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{	
		class HTL_DLLAPI GtPolylineI : public HtlBase
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			GtPolylineI(void);
			GtPolylineI(GtPolylineI& rhs);
			virtual ~GtPolylineI(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtPolylineI & operator = (GtPolylineI & rhs);
			//!EQUAL TO Operator
			bool operator == (GtPolylineI & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (GtPolylineI & rhs);
			//!Clears the polyline of all points
			inline void Clear(void);
			//!Gets the number of points
			inline size_t Size(void);
			//!Returns the point at index
			inline GtPoint3DI & At(size_t index);
			//!Adds the point3d the the back of the coordinates
			inline void PushBack(GtPoint3DI & objNewPoint);

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			StlVector<GtPoint3DI, HTL_BASE> m_arrObjPoints;
			std::string m_strObjectName;
		private:
			GtPoint3DI m_objNullPoint;
		};

	};//end namespace GtCore

};//end namepace GT
#endif //GT_POLYLINE_H