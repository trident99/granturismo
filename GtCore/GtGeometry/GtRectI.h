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
#ifndef GT_RECTI_H
#define GT_RECTI_H

#include "..\GtCoreLibRefs.h"

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{

		class GtPoint3DI;
		class GtSizeI;
		/*
		This class is the windowing system rectangle.
		The coordinate system is (0,0) (top,left) with x+ right and y+ down.
		It should be noted that this is right hand rule only if z+ goes into the screen.
		*/
		class HTL_DLLAPI GtRectI : public HtlBase
		{
		public:
			//!Default constructor
			GtRectI(long lngXMin = 0,long lngXMax = 0,
				long lngYMin = 0,long lngYMax = 0);

			//!constructor with two corner points
			GtRectI(const GtPoint3DI &atopLeft, const GtPoint3DI &abottomRight);

			//!constructor with top left and height and width dimensions
			GtRectI(const GtPoint3DI &atopLeft, const long awidth, const long aheight);
			//!copy constructor
			GtRectI(const GtRectI& rhs);
			//!destructor
			virtual ~GtRectI(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtRectI & operator = (const GtRectI & rhs);

			//!Zero the coordinates of the rect
			void Zero(void);
			//!Is the rectangle NULL?
			bool IsNull(void) const;
			//!Is the rectangle valid?
			bool IsValid(void) const;

			//!Set the Origin (top left) X Coordinate (XMIN)
			void SetOriginX(long ax);
			//!Set the Origin (top left) Y Coordinate (YMIN)
			void SetOriginY(long ay);	
			//!Get the Origin (top left) X Coordinate (XMIN)
			long GetOriginX(void) const;
			//!Get the Origin (top left) Y Coordinate (YMIN)
			long GetOriginY(void) const;
			
			//!Set the Left (XMIN) coordinate 
			void SetLeft(long pos);
			//!Set the Top (YMIN) cooordinate
			void SetTop(long pos);
			//!Set the Right (XMAX) coordinate
			void SetRight(long pos);
			//!Set the Bottom (YMAX) coordinate
			void SetBottom(long pos);
			//!Get the Left (XMIN) coordinate.
			long GetLeft(void) const;
			//!Get the Top (YMIN) coordinate.
			long GetTop(void) const;
			//!Get the Right (XMAX) coordinate.
			long GetRight(void) const;
			//!Get the Bottom (YMAX) coordinate.
			long GetBottom(void) const;

			//!Set the Top Left Point
			void SetTopLeft(const GtPoint3DI &p);
			//!Set the Top Right Point
			void SetTopRight(const GtPoint3DI &p);
			//!Set the Bottom Left Point
			void SetBottomLeft(const GtPoint3DI &p);
			//!Set the Bottom Right Point
			void SetBottomRight(const GtPoint3DI &p);
			//!Get the Top Left Point
			GtPoint3DI GetTopLeft(void) const;
			//!Get the Top Right Point
			GtPoint3DI GetTopRight(void) const;
			//!Get the Bottom Left Point
			GtPoint3DI GetBottomLeft(void) const;
			//!Get the Bottom Right Point
			GtPoint3DI GetBottomRight(void) const;
			
			//!Get the center of the rectangle
			GtPoint3DI Center(void) const;
			//!Get the width (deltaX) of the rectangle
			long Width(void) const;
			//!Get the height (deltaY) of the rectangle
			long Height(void) const;
			//!Get the width and height as a GtSizeF object
			GtSizeI Size(void) const;
			//!Contains the passed in point
			bool Contains(GtPoint3DI & pt);


			//!Translate the rectangle
			void Translate(int dx, int dy);
			//!Translate the rectangle
			void Translate(const GtPoint3DI &p);

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			long xMin;
			long xMax;
			long yMin;
			long yMax;

		};//end class GtRectI

	};//end namespace GtCore
};//end namepace GT
#endif //GT_RECTF_H