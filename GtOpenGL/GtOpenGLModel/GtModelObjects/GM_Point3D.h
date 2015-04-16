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
#ifndef GM_POINT3D_H
#define GM_POINT3D_H

#include "..\GtCadObject.h"

namespace GT
{	
	namespace GtOpenGL
	{

		class HTL_DLLAPI GM_Point3D : public GtCadObject
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			//TPoint3D(void);
			GM_Point3D(double dblX = 0.0f, double dblY = 0.0f,double dblZ = 0.0f);
			GM_Point3D(const GM_Point3D & rhs);
			virtual ~GM_Point3D(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GM_Point3D & operator = (const GM_Point3D & rhs);
			//!EQUAL TO Operator
			bool operator == (const GM_Point3D & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (const GM_Point3D & rhs);
			//!LESS THAN Operator
			bool operator < (const GM_Point3D & rhs);
			//!GREATER THAN Operator
			bool operator > (const GM_Point3D & rhs);

			//!Zeroes point coordinates
			void Zero(void);
			//!Rounds the point coordinates to the specified number of decimals
			void Round(int intNumDecimals);
			//!Set the point coordinates
			void Set(double dblX = 0.0f, double dblY = 0.0f,double dblZ = 0.0f);
			//!Normalize the point coordinates
			void Normalize(void);
			//!Access the point coordinate [0,1,2] is [x,y,z]
			double operator[]( int i ) const;

		public:		
			//!Return the bounding box of the item 
			virtual GtAABox GetBoundingBox(void);
			//!Return the selection box of the item 
			virtual GtAABox GetSelectionBox(void);

		public:
			double x;
			double y;
			double z;

		private:
			virtual void DrawSurfaces(void);

		};//end class defintion
	};//end namespace GtOpenGL
};//end namepace GT
#endif //GM_POINT3D_H