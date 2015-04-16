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

#ifndef GT_CADOBJECT_H
#define GT_CADOBJECT_H
#include "..\GtOpenGLStructs.h"

using namespace GT::GtCore;

namespace GT
{

	namespace GtOpenGL
	{

		class GtCadLayer;

		class HTL_DLLAPI GtCadObject : public GtObject
		{

		public:
			GtCadObject(GtObject* ptrParent = NULL);
			~GtCadObject();

			//!Boolean flag for is visible
			GTOBJECT_MEMVAR_BYVAL(public, HtlGUID128, objGUID);
			//!Boolean flag for is visible
			GTOBJECT_MEMVAR_BYREF(public, std::wstring, strText);

			//!Boolean flage for if object is visible
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnVisible);
			//!Boolean flag for displaying the surface or mesh	
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowSurface);
			//!Boolean flag for displaying the Nurbs Curves, or Polyline
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowCurves);
			//!Boolean flag for displaying the Handel Points, end Points, and Non-Nurbs Control Net Points
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowPoints);
			//!Boolean flag for displaying the Nurbs Control Net Points and connector grid lines
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowControlNet);

			//boolean flage for is locked
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnLocked);
			//boolean flag for use override render mode
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnRenderOverride);
			//boolean flag for is selected
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnSelected);
			//override render mode
			GTOBJECT_MEMVAR_BYVAL(public, GtRenderMode, enumRenderOverrideMode);
			//This is the override material for formalized rendering
			GTOBJECT_MEMVAR_BYVAL(public, GtMaterial, objRenderMaterial);
			//material used for mesh and Nurb surfaces
			GTOBJECT_MEMVAR_BYVAL(public, GtMaterial, objSurfMaterial);
			//material used for line, polyline and Nurb curves
			GTOBJECT_MEMVAR_BYVAL(public, GtMaterial, objCurveMaterial);
			//material used for control points
			GTOBJECT_MEMVAR_BYVAL(public, GtMaterial, objPointMaterial);
			//material used for control network
			GTOBJECT_MEMVAR_BYVAL(public, GtMaterial, objNetMaterial);

			GTOBJECT_MEMVAR_BYREF(public,GtAABox,objBoundingBox);

			GTOBJECT_MEMVAR_BYVAL(public, bool, blnBoxUpdate);

			GTOBJECT_MEMVAR_BYVAL(public, GtCadLayer*, ptrLayer);
			//!Return the bounding box of the item 
			virtual GtAABox GetBoundingBox(void);
			//!Return the selection box of the item 
			virtual GtAABox GetSelectionBox(void);

			void SetGeomModified(void);

			//Object Manipulation
			virtual void Move(GtPoint3DF objDist);
			virtual void Scale(GtPoint3DF objFactors);
			virtual void Transform(float ptrMatrix[16]);

			//SLOTS/////////////////////////////////
			//render the model item in OpenGL
			virtual void RenderItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode);
			virtual void RenderOverlay(const GtViewpoint & ptrCurrViewPoint);

			//SIGNALS//////////////////////////////
			HtlSignal00 ModelItemModified;

		protected:
			bool m_blnGeomModified;

			virtual void DrawSurfaces(void);
			virtual void DrawMesh(void);
			virtual void DrawCurves(void);
			virtual void DrawPoints(void);
			virtual void DrawControlNet(void);
		};//end class TCadObject

	};//end namespace GtOpenGL
};//end namespace GT
#endif // GT_CADOBJECT_H
