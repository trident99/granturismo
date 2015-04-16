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

#ifndef GM_VECTOR_H
#define GM_VECTOR_H
#include "..\GtCadObject.h"

namespace GT
{
	namespace GtOpenGL
	{

		class GM_Vector : public GtCadObject
		{

		public:
			GM_Vector(GtObject* ptrParent = NULL );
			~GM_Vector();

			//Set and Get for Radius
			void Set_dblVectorRadius(double dblRadius);
			double Get_dblVectorRadius(void);

			//Set and Get for Radius
			void Set_dblArrowRadius(double dblRadius);
			double Get_dblArrowRadius(void);

			//Set and Get for Height
			void Set_dblArrowHeight(double dblHeight);
			double Get_dblArrowHeight(void);

			//Set and Get for Number of Mesh Panels
			void Set_intNumSections(int intNumSections);
			int Get_intNumSections(void);

			//Set and Get for Origin
			void Set_objStart(GtPoint3DF objPoint);
			GtPoint3DF Get_objStart(void);

			//Set and Get for Rotation
			void Set_objEnd(GtPoint3DF objPoint);
			GtPoint3DF Get_objEnd(void);

			//Set and Get for Rotation
			void Set_blnDrawArrow(bool blnDrawArrow);
			bool Get_blnDrawArrow(void);

			//FROM QGLMODELBOX METHODS//////////////////////////////
			//!Return the bounding box of the item 
			virtual GtAABox GetBoundingBox(void);
			//!Return the selection box of the item 
			virtual GtAABox GetSelectionBox(void);

			public:
				//FROM QGLMODELITEM METHODS//////////////////////////////
				//render the model item in OpenGL
				virtual void RenderModelItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode);
				virtual void RenderOverlay(const GtViewpoint & ptrCurrViewPoint);

				//!Update the control points for the box
				void UpdateGeometry(void);

		private:
			//!boolean flag for draw arrow
			bool m_blnDrawArrow;
			//!Cylinder Vector Radius
			double m_dblVectorRadius;
			//!Arrow Radius
			double m_dblArrowRadius;
			//!Arrow Height
			double m_dblArrowHeight;
			//!Width YDir (without rotation)
			int m_intNumSections;
			//!Show Text
			bool m_blnShowText;

			//!Origin point
			GtPoint3DF m_objStart;
			//!End point
			GtPoint3DF m_objEnd;
			//!End point
			GtPoint3DF m_objArrowBase;

			std::vector<GtPoint3DF> m_arrObjArrowDiskPoints;

			GLUquadricObj *m_ptrQStartDisk;
			GLUquadricObj *m_ptrQEndDisk;
			GLUquadricObj *m_ptrQCylinder;
			GLUquadricObj *m_ptrQCone;
			GLUquadricObj *m_ptrQConeDisk;

			//OVERRIDDEN DRAWING FUNCTIONS FROM MODEL ITEM
			void DrawSurfaces(void);
			void DrawCurves(void);
			void DrawPoints(void);
			//draw the arrows and cylinders curves
			void DrawArrowCurves(void);
			void DrawCylinderCurves(void);
			//draw the arrow and cylinder surfaces
			void DrawArrowSurfaces(void);
			void DrawCylinderSurfaces(void);

		};//end class

	};//end namespace GtOpenGL
};//end namespace GT
#endif //GM_VECTOR_H