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
#ifndef GM_MESH_H
#define GM_MESH_H

#include "..\GtCadObject.h"

#include <modHtlContainer.h>
using namespace HTL;

namespace GT
{	
	namespace GtOpenGL
	{
		struct HTL_DLLAPI GtFacet
		{
		public:
			GtFacet()
			{
				m_P0 = 0;
				m_P1 = 0;
				m_P2 = 0;
				m_P3 = 0;
			};

		public:
			long m_P0;
			long m_P1;
			long m_P2;
			long m_P3;
		};

		class HTL_DLLAPI GM_Mesh : public GtCadObject
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			GM_Mesh(GtObject* ptrParent = NULL );
			GM_Mesh(GM_Mesh& rhs);
			virtual ~GM_Mesh(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GM_Mesh & operator = (GM_Mesh & rhs);
			//!EQUAL TO Operator
			bool operator == (GM_Mesh & rhs);
			//!NOT EQUAL TO Operator
			bool operator != (GM_Mesh & rhs);
			//!Clears the polyline of all points
			inline void Clear(void);
			//!Gets the number of points
			inline size_t SizePoints(void);
			//!Gets the number of facets
			inline size_t SizeFacets(void);


			//FROM QGLMODELITEM METHODS//////////////////////////////
			//!Return the bounding box of the item 
			virtual GtAABox GetBoundingBox(void);
			//!Return the selection box of the item 
			virtual GtAABox GetSelectionBox(void);

			//FROM QGLMODELITEM METHODS//////////////////////////////
			//render the model item in OpenGL
			virtual void RenderModelItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode);

		public:
			StlVector<GtPoint3DF, HtlUnknownType> m_arrPoints;
			StlVector<GtFacet, HtlUnknownType> m_arrFacets;
		private:
			//OVERRIDDEN DRAWING FUNCTIONS FROM MODEL ITEM
			void DrawSurfaces(void);
			void DrawCurves(void);
			void DrawPoints(void);
		};

	};//end namespace GtOpenGL
};//end namepace GT
#endif //GM_Mesh_H