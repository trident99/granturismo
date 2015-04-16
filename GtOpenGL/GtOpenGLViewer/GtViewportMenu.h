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

#ifndef GT_VIEWPORT_MENU_H
#define GT_VIEWPORT_MENU_H

#include "..\GtOpenGLStructs.h"
#include <GtBasicControls\GtMenu.h>

namespace GT
{
	namespace GtOpenGL
	{

		class GtViewport;

		class GtViewportMenu : public GtMenu
		{

		public:
			GtViewportMenu(GtObject* ptrParent = NULL);
			virtual ~GtViewportMenu();

			void Initialize(void);
			//!Create the Main Menu Actions and connect them to the slots code for handling their events
			void CreateActions(void);
			//!Create the Main Menu or modify the main menu programmatically
			void CreateMenus(void);
			//!Sets the pointer to the viewport parent object
			int Set_ptrViewportParent(GtViewport * ptrParent);
			//!Gets the pointer of the viewport parent object
			GtViewport * Get_ptrViewportParent(void);
			//!Clears the pointer to the viewport parent object
			int ClearViewportParentPtr(void);

		public:
			//Event handlers for the various actions and editors
			//!Sets the viewport to Top View (Looking At XYPlane in the Z Negative Direction)
			void OnSetTopView_XYPlane_ZNeg(void);
			//!Sets the viewport to Top View (Looking At XYPlane in the Z Positive Direction)
			void OnSetBottomView_XYPlane_ZPos(void);
			//!Sets the viewport to Left View (Looking At XZPlane in the Y Negative Direction)
			void OnSetLeftView_XZPlane_YNeg(void);
			//!Sets the viewport to Right View (Looking At XZPlane in the Y Positive Direction)
			void OnSetRightView_XZPlane_YPos(void);
			//!Sets the viewport to Front View (Looking At YZPlane in the X Negative Direction)
			void OnSetFrontView_YZPlane_XNeg(void);
			//!Sets the viewport to Back View (Looking At YZPlane in the X Positive Direction)
			void OnSetBackView_YZPlane_XPos(void);

			//!Toggle the locking of the X Axis
			void OnToggleLock_XAxis(void);
			//!Toggle the locking of the Y Axis
			void OnToggleLock_YAxis(void);
			//!Toggle the locking of the Z Axis
			void OnToggleLock_ZAxis(void);

			//!Set the projection mode to perspective mode
			void OnSetProjectionMode_Perspective(void);
			//!Set the projection mode to orthographic mode
			void OnSetProjectionMode_Orthographic(void);

			//!Set the Render Mode of the Viewport to CurvesOnly
			void OnSetRenderMode_CurvesOnly(void);
			//!Set the Render Mode of the Viewport to CurvesOnly
			void OnSetRenderMode_CurvesWithMesh(void);
			//!Set the Render Mode of the Viewport to CurvesOnly
			void OnSetRenderMode_Shaded(void);
			//!Set the Render Mode of the Viewport to CurvesOnly
			void OnSetRenderMode_ShadedWithMesh(void);
			//!Set the Render Mode of the Viewport to CurvesOnly
			void OnSetRenderMode_ShadedWithCurves(void);
			//!Set the Render Mode of the Viewport to CurvesOnly
			void OnSetRenderMode_ShadedBoundary(void);
			//!Set the Render Mode of the Viewport to CurvesOnly
			void OnSetRenderMode_ShadeSelected(void);

			//!Open the Viewport Lighting Editor
			void OnLightingEditor_Clicked(void);
			//!Open the Viewport Property Editor
			void OnViewportPropEditor_Clicked(void);

			void OnViewDock_Clicked(void);

			void OnViewUnDock_Clicked(void);

		private://PRIVATE MEMBER VARIABLES

			GtMenu *m_ptrSetViewMenu;
			GtAction * m_ptrTopViewAction;
			GtAction * m_ptrBottomViewAction;
			GtAction * m_ptrLeftViewAction;
			GtAction * m_ptrRightViewAction;
			GtAction * m_ptrFrontViewAction;
			GtAction * m_ptrBackViewAction;

			GtMenu *m_ptrAxisLockMenu;
			GtAction * m_ptrToggleLockXAxisAction;
			GtAction * m_ptrToggleLockYAxisAction;
			GtAction * m_ptrToggleLockZAxisAction;

			GtMenu *m_ptrProjectionModeMenu;
			GtAction * m_ptrPerspectiveAction;
			GtAction * m_ptrOrthographicAction;

			GtMenu *m_ptrRenderModeMenu;
			GtAction * m_ptrCurvesOnlyAction;
			GtAction * m_ptrCurvesWithMeshAction;
			GtAction * m_ptrShadedAction;
			GtAction * m_ptrShadedWithMeshAction;
			GtAction * m_ptrShadedWithCurvesAction;
			GtAction * m_ptrShadedBoundaryAction;
			GtAction * m_ptrShadeSelectedAction;

			GtAction * m_ptrLightingEditorAction;
			GtAction * m_ptrViewportPropEditorAction;

			GtAction * m_ptrViewDockAction;
			GtAction * m_ptrViewUnDockAction;

			//Pointer fot the viewport parent
			GtViewport * m_ptrViewportParent;

			void ClearRenderModeChecks(void);
			void ClearProjectionModeChecks(void);

		};//end class TGLViewportToolBar
	};//end namespace GtOpenGL
};//end namespace TGL
#endif // TGLVIEWTOOLBAR_H

