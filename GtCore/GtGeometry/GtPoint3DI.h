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
#ifndef GT_POINT3DI_H
#define GT_POINT3DI_H

#include "..\GtCoreLibRefs.h"

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{
		class HTL_DLLAPI GtPoint3DI : public HtlBase
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			//GtPoint3DI(void);
			GtPoint3DI(long lngX = 0, long lngY = 0,long lngZ = 0);
			GtPoint3DI(const GtPoint3DI& rhs);
			virtual ~GtPoint3DI(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtPoint3DI & operator = (const GtPoint3DI & rhs);
			//!EQUAL TO Operator
			bool operator == (const GtPoint3DI & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (const GtPoint3DI & rhs);
			//!LESS THAN Operator
			bool operator < (const GtPoint3DI & rhs);
			//!GREATER THAN Operator
			bool operator > (const GtPoint3DI & rhs);

			//!Is valid point check
			bool IsPointValid(void);
			//!Resets point to invalid location
			void Reset(void);
			//!Zeroes point coordinates
			void Zero(void);
			//!Set the point coordinates
			void Set(long dblX = 0, long dblY = 0,long dblZ = 0);

			//!Access the point coordinate [0,1,2] is [x,y,z]
			long operator[]( int i ) const;
			//!Point3D Addition
			GtPoint3DI operator + ( const GtPoint3DI& w ) const;
			//!Point3D Subraction
			GtPoint3DI operator - ( const GtPoint3DI& w ) const;
			//!Point3D scalar multiplication
			GtPoint3DI operator * ( long const t ) const;
			//!Point3D scalar division
			GtPoint3DI operator / ( long const t ) const;
			//!Point3D DOT PRODUCT
			double operator * ( const GtPoint3DI& w ) const;
			//!Point3D CROSS PRODUCT
			GtPoint3DI operator ^ ( const GtPoint3DI& w ) const;
			//!Point3D Magnitude
			double Mag() const;

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			long x;
			long y;
			long z;
		};

		bool SortPoint3DI_Ascending(GtPoint3DI & a, GtPoint3DI & b);
		bool SortPoint3DI_Descending(GtPoint3DI & a, GtPoint3DI & b);

	};//end namespace GtCore
};//end namepace GT
#endif //GT_POINT3DI_H