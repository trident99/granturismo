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
#ifndef GT_POINT3DF_H
#define GT_POINT3DF_H

#include "..\GtCoreLibRefs.h"

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{
		class HTL_DLLAPI GtPoint3DF : public HtlBase
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			//GtPoint3DF(void);
			GtPoint3DF(double dblX = 0.0f, double dblY = 0.0f,double dblZ = 0.0f);
			GtPoint3DF(const GtPoint3DF& rhs);
			virtual ~GtPoint3DF(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtPoint3DF & operator = (const GtPoint3DF & rhs);
			//!EQUAL TO Operator
			bool operator == (const GtPoint3DF & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (const GtPoint3DF & rhs);
			//!LESS THAN Operator
			bool operator < (const GtPoint3DF & rhs);
			//!GREATER THAN Operator
			bool operator > (const GtPoint3DF & rhs);

			//!Is valid point check
			bool IsPointValid(void);
			//!Resets point to invalid location
			void Reset(void);
			//!Zeroes point coordinates
			void Zero(void);
			//!Rounds the point coordinates to the specified number of decimals
			void Round(int intNumDecimals);
			//!Set the point coordinates
			void Set(double dblX = 0.0f, double dblY = 0.0f,double dblZ = 0.0f);
			//!Normalize the point coordinates
			void Normalize(void);
			//!Return a Normalized Point
			GtPoint3DF Normalize() const;
			//!Access the point coordinate [0,1,2] is [x,y,z]
			double operator[]( int i ) const;
			//!Point3D Addition
			GtPoint3DF operator + ( const GtPoint3DF& w ) const;
			//!Point3D Subraction
			GtPoint3DF operator - ( const GtPoint3DF& w ) const;
			//!Point3D scalar multiplication
			GtPoint3DF operator * ( double const t ) const;
			//!Point3D scalar division
			GtPoint3DF operator / ( double const t ) const;
			//!Point3D DOT PRODUCT
			double operator * ( const GtPoint3DF& w ) const;
			//!Point3D CROSS PRODUCT
			GtPoint3DF operator ^ ( const GtPoint3DF& w ) const;
			//!Point3D Magnitude
			double Mag() const;

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			double x;
			double y;
			double z;
		};

		bool SortPoint3DF_Ascending(GtPoint3DF & a, GtPoint3DF & b);
		bool SortPoint3DF_Descending(GtPoint3DF & a, GtPoint3DF & b);

	};//end namespace GtCore
};//end namepace GT
#endif //GT_POINT3DF_H