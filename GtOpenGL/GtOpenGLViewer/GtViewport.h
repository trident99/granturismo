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


#ifndef GT_VIEWPORT_H
#define GT_VIEWPORT_H
#include "..\GtOpenGLWidget.h"

#include <modGtGraphic.h>
#include <modHtlContainer.h>


namespace GT
{
	namespace GtOpenGL
	{
		class GtCadObject;
		class GtPartModel;
		class GtFloatingDialog;
		class GtLight;
		class GtSelItemMenu;
		class GtViewportMenu;
		class GM_Grid;

		class HTL_DLLAPI GtViewport : public GtOpenGLWidget
		{

		public:
			//!Parent set constructor
			GtViewport(GtObject* ptrParent = NULL, HWND pWndParent = NULL);
			//!Virtual destructor
			virtual ~GtViewport(void);



			bool Get_blnDocked(void){return m_blnDocked;};

			//Set and Get functions for Anti Aliasing (TRUE = active, FALSE = not active)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnAntiAliasingActive);

			//Set and Get functions for drawing the Background as a Gradient (TRUE = gradient, FALSE = solid (top color))
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnUniform);

			//Color for top of gradient
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objRGBTop);

			//Color for bottom of gradient
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objRGBBottom);
			
			//Set and Get functions for WCS Icon at the origin (TRUE = at origin, FALSE = lower left hand corner of viewport)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnUniformBackground);

			//Set and Get functions for WCS Icon at the origin (TRUE = at origin, FALSE = lower left hand corner of viewport)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnDrawWCSAtOrigin);

			//Set and Get functions for UCS Icon at the origin (TRUE = at origin, FALSE = lower left hand corner of viewport)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnDrawUCSAtOrigin);

			//Set and Get functions for Locking the X axis of the viewport camera (TRUE = locked, FALSE = unlocked)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnLockXAxis);

			//Set and Get functions for Locking the Y axis of the viewport camera (TRUE = locked, FALSE = unlocked)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnLockYAxis);

			//Set and Get functions for Locking the Z axis of the viewport camera (TRUE = locked, FALSE = unlocked)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnLockZAxis);

			//Set and Get functions for Selection Enabled(TRUE = enabled, FALSE = disabled)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnSelectionEnabled);

			//Set and Get functions for Single Select Enabled(TRUE = enabled, FALSE = disabled)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnSingleSelect);

			//Set and Get functions for Single Select Enabled(TRUE = enabled, FALSE = disabled)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnAntiAliasing);

			//Set and Get functions for Single Select Enabled(TRUE = enabled, FALSE = disabled)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnTransparency);

			GTOBJECT_MEMVAR_BYVAL(public, GtProjectionMode, objProjectionMode);

			GTOBJECT_MEMVAR_BYVAL(public, GtRenderMode, objRenderMode);


			//Set and Get functions for the Scene Model
			void Set_ptrPartModel(GtPartModel * ptrModel);
			GtPartModel * Get_ptrPartModel(void);
			//Get the Model by 

			//Get the selected objects
			std::vector<GtCadObject*> GetSelectedObjects(void);

		public:
			void Set_dblXTranslation(double dist);
			void Set_dblYTranslation(double dist);
			void Set_dblZTranslation(double dist);

			void Set_dblXRotation(double angle);
			void Set_dblYRotation(double angle);
			void Set_dblZRotation(double angle);
			//Event handlers for the various actions and editors
			//!Sets the viewport to Top View (Looking At XYPlane in the Z Negative Direction)
			void OnSetViewTop_XYPlane_ZNeg(void);
			//!Sets the viewport to Top View (Looking At XYPlane in the Z Positive Direction)
			void OnSetViewBottom_XYPlane_ZPos(void);
			//!Sets the viewport to Left View (Looking At XZPlane in the Y Negative Direction)
			void OnSetViewLeft_XZPlane_YNeg(void);
			//!Sets the viewport to Right View (Looking At XZPlane in the Y Positive Direction)
			void OnSetViewRight_XZPlane_YPos(void);
			//!Sets the viewport to Front View (Looking At YZPlane in the X Negative Direction)
			void OnSetViewFront_YZPlane_XNeg(void);
			//!Sets the viewport to Back View (Looking At YZPlane in the X Positive Direction)
			void OnSetViewBack_YZPlane_XPos(void);

			float GetViewScale(void);

			void Pan( double dx, double dy) ;
			void Zoom( double dx, double dy );
			void Zoom( int delta);
			void ZoomExtents(void);
			void RotateOrbit( double dx, double dy );
			void RotateCamera( double dx, double dy );

			void DockViewport(void);
			void UnDockViewport(void);

			void ProcessSelection(GtPoint3DI & objSelPoint);

			void UpdateViewport(void);

			//OVERRIDE FROM GTOPENGLWIDGET
			//!Tests and sets the focus widget based on the cursor location provided
			virtual GtWidget* SetFocusWidget(GtPoint3DI & pos);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);

		protected:
			//THE REQUIRED OPENGL Drawing functions overridden
			//initialize the opengl window
			virtual void InitializeGL(void);

			//!Paint the opengl graphics
			virtual void PaintGL(void);

			virtual void InitializeConnections(void);
			virtual void InitializeViewpoint(void);
			virtual void InitializeViewport(void);
			//Event Handlers
			void OnMousePressEvent(GtEvent * ptrEvent);
			void OnMouseReleaseEvent(GtEvent * ptrEvent);
			void OnMouseMoveEvent(GtEvent * ptrEvent);
			void OnMouseDoubleClickEvent(GtEvent * ptrEvent);
			void OnWheelEvent(GtEvent * ptrEvent);
			void OnKeyPressEvent(GtEvent * ptrEvent);
			void OnKeyReleaseEvent(GtEvent * ptrEvent);
			void OnResizeEvent(GtEvent * ptrEvent);

			//0)Initialize the 3D environment
			void InitializeEnvironment();
			//Transform the camera to the current viewpoint
			void TransformToCurrentViewpoint(void);
			//RENDER PIPELINE
			//1) Draw the BackGround
			void DrawBackggRound(void);
			//2) Setup Antialiasing
			void DoAntialiasing();
			//3) Draw the World Coordinate System Icon
			void DrawWorldCoordinateIcon(void);
			//4) Draw the World Coordinate System Axes
			void DrawWorldCoordinateAxes(void);
			//5) Draw the User Coordinate System Icon
			void DrawUserCoordinateIcon(void);
			//6) Draw the User Coordinate System Axes
			void DrawUserCoordinateAxes(void);

			void DrawFrustum(void);
			//7) Add the Lights
			void DrawLights(void);
			//8) Draw the display grids
			void DrawGrids(void);
			//9) Draw the display axes
			void DrawAxes(void);
			//10) Draw the objects in the scene
			void DrawScene(const GtViewpoint & ptrCurrViewPoint);

			//11) Update the mouse location based on last position
			void UpdateMouseLocation(GtViewpoint & ptrCurrViewPoint);

			//SIGNALS////////////////////////////////////////////////
		public:
			//signals for viewpoint change
			HtlSignal00 ViewpointChanged;

			HtlSignal00 ViewportClosing;

			HtlSignal00 SelectionChanged;

			//PROTECTED MEMBER VARIABLES
		protected:
			//the owner of the viewport, used for undocking viewport
			GtWidget *m_ptrOwner;

			//boolean flag indicating if viewport is docked or undocked
			bool m_blnDocked;
			//boolean flag for Shift Key Pressed;
			bool m_blnShiftKeyPressed;	
			//boolean flag for Control Key Pressed
			bool m_blnCtrlKeyPressed;
			//boolean flag for Control Key Pressed
			bool m_blnAltKeyPressed;
			//boolean flag for Control Key Pressed
			bool m_blnCKeyPressed;

			//scale for panning speed
			float m_sngPanSpeed;
			//scale for zooming speed
			float m_sngZoomSpeed;
			//scale for rotation speed
			float m_sngRotateSpeed;
			//scale for camera rotation speed
			float m_sngCamRotateSpeed;

			//last mouse point
			GtPoint3DI m_objLastPoint;

			//Saved viewpoint collection
			std::vector<GtViewpoint> m_arrObjSavedViewpoints;
			//The light vector for the anti-aliasing 
			std::vector<GtLight*> m_arrLightsCollection;
			//The current scene model that the viewport is looking at
			GtPartModel * m_ptrPartModel;

			GtViewportMenu * m_ptrMainMenu;

			GtSelItemMenu * m_ptrSelPopUpMenu;

			GM_Grid * m_ptrXYPlaneGrid;
			GM_Grid * m_ptrXZPlaneGrid;
			GM_Grid * m_ptrYZPlaneGrid;

			std::vector<GtCadObject*> m_arrSelection;

			float m_arrSngCurrModelMatrix[16];
			float m_arrSngCurrProjMatrix[16];
			//Draws the unit UCS Icon at the current point in space
			void DrawWCSIconAtCurrLocation(void);
			//draws a test 4 sided pyramid
			void DrawTestPyramid(void);
			//Normalizes a rotation angle
			void NormalizeAngle(double & dblAngle);

		};//end class GtViewport
	};//end namespace GtOpenGL
};//end namespace Gt
#endif // GtVIEWPORT_H
