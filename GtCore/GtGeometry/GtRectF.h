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
#ifndef GT_RECTF_H
#define GT_RECTF_H

#include "..\GtCoreLibRefs.h"

using namespace HTL;

namespace GT
{	
	namespace GtCore
	{

		class GtPoint3DF;
		class GtSizeF;
		/*
		This class is the windowing system rectangle.
		The coordinate system is (0,0) (top,left) with x+ right and y+ down.
		It should be noted that this is right hand rule only if z+ goes into the screen.
		*/
		class HTL_DLLAPI GtRectF : public HtlBase
		{
		public:
			//!Default constructor
			GtRectF(double dblXMin = 0.0f,double dblXMax = 0.0f,
				double dblYMin = 0.0f,double dblYMax = 0.0f);

			//!constructor with two corner points
			GtRectF(const GtPoint3DF &atopLeft, const GtPoint3DF &abottomRight);

			//!constructor with top left and height and width dimensions
			GtRectF(const GtPoint3DF &atopLeft, const double awidth, const double aheight);
			//!destructor
			~GtRectF();
			//!Zero the coordinates of the rect
			void Zero(void);
			//!Is the rectangle NULL?
			bool IsNull(void) const;
			//!Is the rectangle valid?
			bool IsValid(void) const;

			//!Set the Origin (top left) X Coordinate (XMIN)
			void SetOriginX(double ax);
			//!Set the Origin (top left) Y Coordinate (YMIN)
			void SetOriginY(double ay);	
			//!Get the Origin (top left) X Coordinate (XMIN)
			double GetOriginX(void) const;
			//!Get the Origin (top left) Y Coordinate (YMIN)
			double GetOriginY(void) const;
			
			//!Set the Left (XMIN) coordinate 
			void SetLeft(double pos);
			//!Set the Top (YMIN) cooordinate
			void SetTop(double pos);
			//!Set the Right (XMAX) coordinate
			void SetRight(double pos);
			//!Set the Bottom (YMAX) coordinate
			void SetBottom(double pos);
			//!Get the Left (XMIN) coordinate.
			double GetLeft(void) const;
			//!Get the Top (YMIN) coordinate.
			double GetTop(void) const;
			//!Get the Right (XMAX) coordinate.
			double GetRight(void) const;
			//!Get the Bottom (YMAX) coordinate.
			double GetBottom(void) const;

			//!Set the Top Left Point
			void SetTopLeft(const GtPoint3DF &p);
			//!Set the Top Right Point
			void SetTopRight(const GtPoint3DF &p);
			//!Set the Bottom Left Point
			void SetBottomLeft(const GtPoint3DF &p);
			//!Set the Bottom Right Point
			void SetBottomRight(const GtPoint3DF &p);
			//!Get the Top Left Point
			GtPoint3DF GetTopLeft(void) const;
			//!Get the Top Right Point
			GtPoint3DF GetTopRight(void) const;
			//!Get the Bottom Left Point
			GtPoint3DF GetBottomLeft(void) const;
			//!Get the Bottom Right Point
			GtPoint3DF GetBottomRight(void) const;
			
			//!Get the center of the rectangle
			GtPoint3DF Center(void) const;
			//!Get the width (deltaX) of the rectangle
			double Width(void) const;
			//!Get the height (deltaY) of the rectangle
			double Height(void) const;
			//!Get the width and height as a GtSizeF object
			GtSizeF Size(void) const;
			//!Contains the passed in point
			bool Contains(GtPoint3DF & pt);

			//!Translate the rectangle
			void Translate(float dx, float dy);
			//!Translate the rectangle
			void Translate(const GtPoint3DF &p);

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			double xMin;
			double xMax;
			double yMin;
			double yMax;

		};//end class GtRectF

	};//end namespace GtCore
};//end namepace GT
#endif //GT_RECTF_H