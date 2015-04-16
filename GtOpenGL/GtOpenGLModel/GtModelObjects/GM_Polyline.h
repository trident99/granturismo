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
#ifndef GM_POLYLINE_H
#define GM_POLYLINE_H

#include "..\GtCadObject.h"

#include <modHtlContainer.h>
using namespace HTL;

namespace GT
{	
	namespace GtOpenGL
	{

		class HTL_DLLAPI GM_Polyline : public GtCadObject
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			GM_Polyline(GtObject* ptrParent = NULL );
			GM_Polyline(GM_Polyline& rhs);
			virtual ~GM_Polyline(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GM_Polyline & operator = (GM_Polyline & rhs);
			//!EQUAL TO Operator
			bool operator == (GM_Polyline & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (GM_Polyline & rhs);
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


			//FROM QGLMODELITEM METHODS//////////////////////////////
			//!Return the bounding box of the item 
			virtual GtAABox GetBoundingBox(void);
			//!Return the selection box of the item 
			virtual GtAABox GetSelectionBox(void);

			//FROM QGLMODELITEM METHODS//////////////////////////////
			//render the model item in OpenGL
			virtual void RenderModelItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode);

		protected:
			StlVector<GtPoint3DF, HTL_BASE> m_arrObjPoints;

		private:
			GtPoint3DF m_objNullPoint;
			//OVERRIDDEN DRAWING FUNCTIONS FROM MODEL ITEM
			void DrawCurves(void);
			void DrawPoints(void);
		};

	};//end namespace GtOpenGL
};//end namepace GT
#endif //GM_POLYLINE_H