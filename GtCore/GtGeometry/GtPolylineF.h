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
#ifndef GT_POLYLINE_H
#define GT_POLYLINE_H

#include ".\GtPoint3DF.h"
#include <modHtlContainer.h>

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{	
		class HTL_DLLAPI GtPolylineF : public HtlBase
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			GtPolylineF(void);
			GtPolylineF(GtPolylineF& rhs);
			virtual ~GtPolylineF(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtPolylineF & operator = (GtPolylineF & rhs);
			//!EQUAL TO Operator
			bool operator == (GtPolylineF & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (GtPolylineF & rhs);
			//!Clears the polyline of all points
			inline void Clear(void);
			//!Gets the number of points
			inline size_t Size(void);
			//!Returns the point at index
			inline GtPoint3DF & At(size_t index);
			//!Adds the point3d the the back of the coordinates
			inline void PushBack(GtPoint3DF & objNewPoint);
			//!Round the polyline coordinates to number of decimals
			inline void Round(int intNumDecimals);

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			StlVector<GtPoint3DF, HTL_BASE> m_arrObjPoints;
			std::string m_strObjectName;
		private:
			GtPoint3DF m_objNullPoint;
		};

	};//end namespace GtCore

};//end namepace GT
#endif //GT_POLYLINE_H