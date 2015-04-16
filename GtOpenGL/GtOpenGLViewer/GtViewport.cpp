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
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtViewport.h"
#include "..\GtOpenGLMath.h"
#include "..\GtOpenGLModel\GtCadObject.h"
#include "..\GtOpenGLModel\GtCadLayer.h"
#include "..\GtOpenGLModel\GtPartModel.h"
#include "..\GtOpenGLModel\GtLight.h"
#include "..\GtOpenGLModel\GtModelObjects\GM_Grid.h"

#include ".\GtFloatingDialog.h"
#include ".\GtSelItemMenu.h"
#include ".\GtViewportMenu.h"

using namespace GT::GtMath;
#define M_PI 3.1415926

namespace GT
{
	namespace GtOpenGL
	{

		GtViewport::GtViewport(GtObject* ptrParent, HWND pWndParent)
			: GtOpenGLWidget(ptrParent,pWndParent)
		{
			this->m_ptrOwner = dynamic_cast<GtWidget*>(ptrParent);//setting owner to the constructor parent
			//boolean flag for Shift Key Pressed;
			this->m_blnShiftKeyPressed = false;	
			//boolean flag for Control Key Pressed
			this->m_blnCtrlKeyPressed = false;


			m_blnAltKeyPressed = false;
			m_blnCKeyPressed = false;
			//Boolean flag for having antialiasing turned on
			this->m_blnAntiAliasing = true;
			//Boolean flag for allowing transparency
			this->m_blnTransparency = true;

			//Boolean flag for having a gradient background
			this->m_blnUniformBackground = false;
			//Boolean flag for drawing the WCS Icon at the Origin
			this->m_blnDrawWCSAtOrigin = true;
			//Boolean flag for drawing the UserCS Icon at its Origin
			this->m_blnDrawUCSAtOrigin = true;
		
			//docking flag
			this->m_blnDocked = true;
			//Boolean flag for locking viewport camera X Axis
			this->m_blnLockXAxis = false;
			//Boolean flag for locking viewport camera Y Axis
			this->m_blnLockYAxis = false;
			//Boolean flag for locking viewport camera Z Axis
			this->m_blnLockZAxis = false;
			//sets to selection enabled
			this->m_blnSelectionEnabled = true;
			//sets to single set
			this->m_blnSingleSelect = false;

			this->m_sngPanSpeed = 1.0f;
			this->m_sngZoomSpeed = 1.0f;
			this->m_sngRotateSpeed = 1.0f;
			this->m_sngCamRotateSpeed = 20.25f;
			//Color for top of gradient
			this->m_objRGBTop.SetRGB(0,0,255);
			//Color for bottom of gradient
			this->m_objRGBBottom.SetRGB(220,220,220);
			//Set up the WCS Grids
			//XYPLANE GRID
			this->m_ptrXYPlaneGrid = new GM_Grid();
			this->m_ptrXYPlaneGrid->Set_objPlane(XYPLANE);
			this->m_ptrXYPlaneGrid->Set_blnVisible(true);
			//XZPLANE GRID
			this->m_ptrXZPlaneGrid = new GM_Grid();
			this->m_ptrXZPlaneGrid->Set_objPlane(XZPLANE);
			this->m_ptrXZPlaneGrid->Set_blnVisible(false);

			//YZPLANE GRID
			this->m_ptrYZPlaneGrid = new GM_Grid();
			this->m_ptrYZPlaneGrid->Set_objPlane(YZPLANE);
			this->m_ptrYZPlaneGrid->Set_blnVisible(false);
			m_objRenderMode = ShadedWithCurves;
			m_objProjectionMode = Orthographic;
			//set the new current viewpoint
			this->InitializeViewpoint();
			m_ptrPartModel = NULL;
			m_ptrMainMenu = NULL;
			m_ptrSelPopUpMenu = NULL;
			//m_ptrFloatingDialog = NULL;
			//Current viewpoint information
			//make last the same as current
			m_objLastViewpoint = m_objCurrViewpoint;
			//initialize the internal QT connections of signals and slots
			InitializeConnections();
			InitializeViewport();
		}

		GtViewport::~GtViewport()
		{
			try{		
				ViewportClosing.Emit();

				if(m_ptrMainMenu)
				{
					delete m_ptrMainMenu;
				};
				if(m_ptrSelPopUpMenu)
				{
					delete m_ptrSelPopUpMenu;
				};
				//if(m_ptrFloatingDialog)
				//{
				//	delete m_ptrFloatingDialog;
				//};
				if(m_ptrPartModel)
				{
					//disconnect(m_ptrPartModel,SIGNAL(SceneModified()),this,SLOT(UpdateViewport()));
				};
			}catch(...){
				//error
				return;
			};
		};

		//THE REQUIRED OPENGL Drawing functions overridden
		void GtViewport::InitializeGL()
		{
			glShadeModel(GL_SMOOTH); //GL_FLAT					// Enables Smooth Shading
			glClearColor(0.6f, 0.6f, 0.6f, 1.0f);				// Gray Background
			glClearDepth(1.0f);									// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
			glDepthFunc(GL_LEQUAL);								// The Type Of Depth Test To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		};


		void GtViewport::PaintGL()
		{
			GtOpenGLWidget::PaintGL();

			try
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
				glLoadIdentity();									// Reset The Modelview Matrix

				glPushMatrix();
				//0)Initialize the 3D environment
				this->InitializeEnvironment();

				//5) Add the Lights
				this->DrawLights();
				//Draw the background
				this->DrawBackggRound();
				//1) Transform the camera to the current viewpoint
				this->TransformToCurrentViewpoint();
				//RENDER PIPELINE
				//2) Setup Antialiasing
				this->DoAntialiasing();

				//3) Draw the World Coordinate System Axes
				this->DrawWorldCoordinateAxes();
				//4) Draw the User Coordinate System Axes
				this->DrawUserCoordinateAxes();

				//6) Draw the display grids
				this->DrawGrids();
				//7) Draw the display axes
				this->DrawAxes();
				//8) Draw the objects in the scene
				this->DrawScene(m_objCurrViewpoint);
				//this->DrawTestPyramid();
				//9) Draw the World Coordinate System Icon
				this->DrawWorldCoordinateIcon();
				//10) Draw the User Coordinate System Icon
				this->DrawUserCoordinateIcon();


				glFlush(); //ensures that the drawing commands are actually executed rather than being stored in a buffer awaiting additional OpenGL commands
				glPopMatrix();

				return;
			}catch(...){
				return;
			};


		};

		void GtViewport::InitializeConnections(void)
		{
			//connect the WCS Grids
			//connect(this->m_ptrXYPlaneGrid,SIGNAL(ModelItemModified()),this,SLOT(PostPaint()));
			//connect(this->m_ptrXZPlaneGrid,SIGNAL(ModelItemModified()),this,SLOT(PostPaint()));
			//connect(this->m_ptrYZPlaneGrid,SIGNAL(ModelItemModified()),this,SLOT(PostPaint()));

		};

		void GtViewport::InitializeViewpoint(void)
		{
			this->m_objCurrViewpoint.m_objRotationCentroid.x = 0;
			this->m_objCurrViewpoint.m_objRotationCentroid.y = 0;
			this->m_objCurrViewpoint.m_objRotationCentroid.z = 0;

			this->m_objCurrViewpoint.m_objViewLocation.x = 10;
			this->m_objCurrViewpoint.m_objViewLocation.y = 10;
			this->m_objCurrViewpoint.m_objViewLocation.z = 5;

			this->m_objCurrViewpoint.m_objRotation.x = 0;
			this->m_objCurrViewpoint.m_objRotation.y = 0;
			this->m_objCurrViewpoint.m_objRotation.z = 0;

			this->m_objCurrViewpoint.m_objUpDir.x = 0;
			this->m_objCurrViewpoint.m_objUpDir.y = 0;
			this->m_objCurrViewpoint.m_objUpDir.z = 1;
			return;
		}

		void GtViewport::InitializeViewport(void)
		{
			GtRectI menuRect;
			menuRect.xMin = 0;
			menuRect.xMax = 50;
			menuRect.yMin = 0;
			menuRect.yMax = 25;
			this->m_ptrMainMenu = new GtViewportMenu(this);
			if(m_ptrMainMenu)
			{
				m_ptrMainMenu->Set_ptrViewportParent(this);
				m_ptrMainMenu->Set_intWidth(200);
				m_ptrMainMenu->Set_objFrame(menuRect);
				this->AddSubWidget(m_ptrMainMenu);
			}


			this->m_ptrSelPopUpMenu = new GtSelItemMenu(this);
			this->AddSubWidget(m_ptrSelPopUpMenu);
			m_ptrSelPopUpMenu->SetVisible(false);

		}
		//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtViewport::SetFocusWidget(GtPoint3DI & pos)
		{
			 GtPoint3DI transPos, offPos;

			 //need to retrieve the root widget, call the parent
			 offPos = this->RequestOffset();
			 transPos.x = pos.x - offPos.x;
			 transPos.y = pos.y - offPos.y;

			if(m_ptrMainMenu)
			{
				if(m_ptrMainMenu->GetVisible())
				{
					GtWidget* ptrRet = m_ptrMainMenu->SetFocusWidget(pos);
					if(ptrRet)
					{
						return ptrRet;
					}
				}
			}

			if(m_ptrSelPopUpMenu)
			{
				if(m_ptrSelPopUpMenu->GetVisible())
				{
					GtWidget* ptrRet = m_ptrSelPopUpMenu->SetFocusWidget(pos);
					if(ptrRet)
					{
						return ptrRet;
					}
				}
			}
			//otherwise call parent class
			return GtWidget::SetFocusWidget(pos);

		}

		//!Custom Event Processing
		int GtViewport::HandleEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return 0;};//safety check

			if((ptrEvent->m_objType == MouseLeftPress)||
				(ptrEvent->m_objType == MouseRightPress))
			{
				this->OnMousePressEvent(ptrEvent);
				return 1;
			};
			if((ptrEvent->m_objType == MouseLeftRelease)||
				(ptrEvent->m_objType == MouseRightRelease))
			{
				this->OnMouseReleaseEvent(ptrEvent);
				return 1;
			};
			if(ptrEvent->m_objType == MouseMove)
			{
				this->OnMouseMoveEvent(ptrEvent);
				return 1;
			};
			if(ptrEvent->m_objType == MouseWheel)
			{
				this->OnWheelEvent(ptrEvent);
				return 1;
			};
			if(ptrEvent->m_objType == KeyPress)
			{
				this->OnKeyPressEvent(ptrEvent);
				return 1;
			};
			if(ptrEvent->m_objType == KeyRelease)
			{
				this->OnKeyReleaseEvent(ptrEvent);
				return 1;
			};

			return 0;
		};




		//Event Handlers
		void GtViewport::OnMousePressEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check

			if(ptrEvent->m_objType == MouseLeftPress) 
			{
				//select object
				GtPoint3DI selPos, off, transPos;
				selPos.x = gRound(ptrEvent->m_objPos.x);
				selPos.y = gRound(ptrEvent->m_objPos.y);
				selPos.z = gRound(ptrEvent->m_objPos.z);

				off = this->RequestOffset();
				transPos.x = selPos.x - off.x - m_objFrame.xMin;
				transPos.y = selPos.y - off.y - m_objFrame.yMin;
				transPos.z = selPos.z - off.z;
				this->ProcessSelection(transPos);
			};	

			//if (ptrEvent->m_objType == MouseRightPress) 
			//{
			//	if (event->modifiers().testFlag(Qt::ControlModifier))
			//	{
			//		//navigation mode see mousemove
			//		//for event handling
			//	};
			//};

			this->m_objLastPoint.x = gRound(ptrEvent->m_objPos.x);
			this->m_objLastPoint.y = gRound(ptrEvent->m_objPos.y);
			this->m_objLastPoint.z = gRound(ptrEvent->m_objPos.z);
		};

		void GtViewport::OnMouseReleaseEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			this->m_objLastPoint.x = gRound(ptrEvent->m_objPos.x);
			this->m_objLastPoint.y = gRound(ptrEvent->m_objPos.y);
			//if (event->buttons() & Qt::RightButton) 
			//{
			//}
		}

		void GtViewport::OnMouseMoveEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check

			double dx = (double)( ptrEvent->m_objPos.x - m_objLastPoint.x ) / (double)this->m_objCurrViewpoint.m_sngWidth;
			double dy = (double)(  ptrEvent->m_objPos.y - m_objLastPoint.y ) / (double)this->m_objCurrViewpoint.m_sngHeight;

			if(ptrEvent->m_objModifiers & LeftMouseModifier)
			{
				//SELECTION MODE
				PostPaint();
			}else if(ptrEvent->m_objModifiers & RightMouseModifier){
				//NAVIGATION MODE
				//RHINO NAVIGATION CONVENTIONS USED
				//SHIFT + RIGHT CLICK MOVE ==> PAN IN CURRENT PLANE
				//CONTROL + RIGHT CLICK MOVE (+-Y DIR) ==> ZOOM IN UP / ZOOM OUT DOWN
				//RIGHT CLICK MOVE (XY) ==> ROTATE X Y Z AROUND CENTROID
				if(this->m_blnCKeyPressed == false)
				{//then in Orbit Mode
					if(ptrEvent->m_objModifiers & ShiftModifier)
					{
						this->Pan( -dx, -dy );
					}else if(ptrEvent->m_objModifiers & ControlModifier){
						this->Zoom( dx, dy );
					}else{
						this->RotateOrbit( dx, dy );
					}
				}else{
					//in Camera Mode
					//rotate XY
					this->RotateCamera( dx, dy );
				}
			};
			//set the new viewpoint
			this->TransformToCurrentViewpoint();
			this->PostPaint();
			this->m_objLastPoint.x = gRound(ptrEvent->m_objPos.x);
			this->m_objLastPoint.y = gRound(ptrEvent->m_objPos.y);
			return;
		};

		void GtViewport::OnMouseDoubleClickEvent(GtEvent * ptrEvent)
		{
			//if (event->buttons() & Qt::LeftButton) //double left click
			//{
			//	//reset viewport
			//	this->InitializeViewpoint();
			//	this->PostPaint();
			//}
		};

		void GtViewport::OnWheelEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			this->m_objLastPoint.x = gRound(ptrEvent->m_objPos.x);
			this->m_objLastPoint.y = gRound(ptrEvent->m_objPos.y);


			float sngZoomOutScale = 1.10;
			float sngZoomInScale = 0.90;
			GtPoint3DF objDiff;

			objDiff.x = this->m_objCurrViewpoint.m_objViewLocation.x - this->m_objCurrViewpoint.m_objRotationCentroid.x;
			objDiff.y = this->m_objCurrViewpoint.m_objViewLocation.y - this->m_objCurrViewpoint.m_objRotationCentroid.y;
			objDiff.z = this->m_objCurrViewpoint.m_objViewLocation.z - this->m_objCurrViewpoint.m_objRotationCentroid.z;

			int intNumSteps = ptrEvent->m_intVal;

			if(intNumSteps == 0){return;}//do nothing
			if(intNumSteps < 0)
			{
				//zoom out
				this->m_objCurrViewpoint.m_objViewLocation.x = this->m_objCurrViewpoint.m_objRotationCentroid.x + (objDiff.x * sngZoomOutScale);
				this->m_objCurrViewpoint.m_objViewLocation.y = this->m_objCurrViewpoint.m_objRotationCentroid.y + (objDiff.y * sngZoomOutScale);
				this->m_objCurrViewpoint.m_objViewLocation.z = this->m_objCurrViewpoint.m_objRotationCentroid.z + (objDiff.z * sngZoomOutScale);

			}else{
				//zoom in
				this->m_objCurrViewpoint.m_objViewLocation.x = this->m_objCurrViewpoint.m_objRotationCentroid.x + (objDiff.x * sngZoomInScale);
				this->m_objCurrViewpoint.m_objViewLocation.y = this->m_objCurrViewpoint.m_objRotationCentroid.y + (objDiff.y * sngZoomInScale);
				this->m_objCurrViewpoint.m_objViewLocation.z = this->m_objCurrViewpoint.m_objRotationCentroid.z + (objDiff.z * sngZoomInScale);
			}
			//set the new viewpoint
			this->TransformToCurrentViewpoint();
			this->PostPaint();

		};

		void GtViewport::OnKeyPressEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			switch(ptrEvent->m_objKey)
			{
			case Key_Shift: 
				{
					this->m_blnShiftKeyPressed = true;

					break;
				}
			case Key_Control: 
				{
					this->m_blnCtrlKeyPressed = true;
					break;
				}
			case Key_Alt: 
				{
					this->m_blnAltKeyPressed = true;
					break;
				}
			case Key_C: 
				{
					this->m_blnCKeyPressed = true;
					break;
				}
			default:
				{
					break;
				}
			}//end switch on Keys
			
			return;
		};

		void GtViewport::OnKeyReleaseEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			switch(ptrEvent->m_objKey)
			{
			case Key_Shift: 
				{
					this->m_blnShiftKeyPressed = false;
					break;
				}
			case Key_Control: 
				{
					this->m_blnCtrlKeyPressed = false;
					break;
				}
			case Key_Alt: 
				{
					this->m_blnAltKeyPressed = false;
					break;
				}
			case Key_C: 
				{
					this->m_blnCKeyPressed = false;
					break;
				}
			default:
				{

					break;
				}
			}//end switch on Keys
			return;
		};

		//0)Initialize the 3D environment
		void GtViewport::InitializeEnvironment()
		{

			glShadeModel(GL_SMOOTH); //GL_FLAT					// Enables Smooth Shading

			glClearColor(1.0f, 1.0f, 1.0f, 0.0f);				// White Background
			glClearStencil(0);                              // clear stencil buffer
			glClearDepth(1.0f);									// Depth Buffer Setup
			glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
			glDepthFunc(GL_LEQUAL);								// The Type Of Depth Test To Do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
			glEnable(GL_NORMALIZE);								// OpenGL auto-normalization of vectors (helpful/required for proper lighting, but a bit slower)

			if(this->m_blnTransparency)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}

			//Reset The Current Modelview Matrix
			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();

			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glLoadIdentity();

		};
		void GtViewport::TransformToCurrentViewpoint(void)
		{
			//glTranslated(this->m_objCurrViewpoint.m_objViewLocation.x,
			//			this->m_objCurrViewpoint.m_objViewLocation.y,
			//			this->m_objCurrViewpoint.m_objViewLocation.z); //initially at (0,0,0), per values in constructor
			//SET UP TRANSFORMATION MATRIX//////////////////////////////////////////////////////////////////////////////
			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glLoadIdentity();									// Reset The Modelview Matrix

			glRotated(this->m_objCurrViewpoint.m_objRotation.x, 1.0, 0.0, 0.0); //now adjust to the current viewing angle
			glRotated(this->m_objCurrViewpoint.m_objRotation.y, 0.0, 1.0, 0.0);
			glRotated(this->m_objCurrViewpoint.m_objRotation.z, 0.0, 0.0, 1.0);
			gluLookAt(this->m_objCurrViewpoint.m_objViewLocation.x,
				this->m_objCurrViewpoint.m_objViewLocation.y,
				this->m_objCurrViewpoint.m_objViewLocation.z,
				this->m_objCurrViewpoint.m_objRotationCentroid.x,
				this->m_objCurrViewpoint.m_objRotationCentroid.y,
				this->m_objCurrViewpoint.m_objRotationCentroid.z,
				this->m_objCurrViewpoint.m_objUpDir.x,
				this->m_objCurrViewpoint.m_objUpDir.y,
				this->m_objCurrViewpoint.m_objUpDir.z);	//(eyeX,eyeY,eyeZ, centerX,centerY,centerZ, upX,upY,upZ) --up being the upward-pointing vector
			//get the model matrix
			glGetFloatv(GL_MODELVIEW_MATRIX , m_arrSngCurrModelMatrix);
			glGetDoublev(GL_MODELVIEW_MATRIX , m_objCurrViewpoint.m_arrDblCurrModelMatrix);

			//SET UP PROJECTION MATRIX//////////////////////////////////////////////////////////////////////////////////
			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();									// Reset The Projection Matrix

			//glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);

			if(this->m_objProjectionMode == Orthographic)
			{
				GLdouble w = (this->m_objCurrViewpoint.m_sngWidth);
				GLdouble h = (this->m_objCurrViewpoint.m_sngHeight);
				GLdouble aspect = w/h;
				GLdouble diam = 0.5f * Diff3D(this->m_objCurrViewpoint.m_objViewLocation,this->m_objCurrViewpoint.m_objRotationCentroid).Mag();
				GLdouble zNear = this->m_objCurrViewpoint.m_sngZNearFieldDist;
				GLdouble zFar = this->m_objCurrViewpoint.m_sngZFarFieldDist;

				if(w <= h)
				{
					glOrtho((-diam), (diam), (-diam / aspect), (diam / aspect), -zFar, zFar);
				}else{
					glOrtho((-diam*aspect), (diam*aspect), (-diam), (diam), -zFar, zFar);
				}

			}else{
				// Calculate The Aspect Ratio Of The Window
				gluPerspective(this->m_objCurrViewpoint.m_sngFieldOfViewAngle,
					((GLdouble)(this->m_objCurrViewpoint.m_sngWidth))/((this->m_objCurrViewpoint.m_sngHeight)),
					this->m_objCurrViewpoint.m_sngZNearFieldDist,
					this->m_objCurrViewpoint.m_sngZFarFieldDist); //if zNear is 0.0, then overlaps render with color interferences
			};
			//get the projection matrix
			glGetFloatv(GL_PROJECTION_MATRIX , m_arrSngCurrProjMatrix);	
			glGetDoublev(GL_PROJECTION_MATRIX , m_objCurrViewpoint.m_arrDblCurrProjMatrix);
			//get the viewport
			glGetIntegerv(GL_VIEWPORT,m_objCurrViewpoint.m_arrIntViewport);
			glMatrixMode(GL_MODELVIEW);

			//11) Update the mouse location based on last position
			this->UpdateMouseLocation(m_objCurrViewpoint);

		};
		//RENDER PIPELINE
		//1) Draw the BackGround
		void GtViewport::DrawBackggRound(void)
		{
			glDisable(GL_LIGHTING);
			glPushAttrib(GL_ENABLE_BIT);
			glDisable(GL_DEPTH_TEST);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glBegin(GL_QUADS);
			//top color
			glColor3f(this->m_objRGBBottom.UnitRed(),this->m_objRGBBottom.UnitGreen(), this->m_objRGBBottom.UnitBlue());
			glVertex2f(-1.0,-1.0);
			glVertex2f(1.0,-1.0);
			//bottom color
			if(this->m_blnUniformBackground == false)
			{
				glColor3ub (this->m_objRGBTop.m_intRed,this->m_objRGBTop.m_intGreen, this->m_objRGBTop.m_intBlue);
			}
			glVertex2f(1.0, 1.0);
			glVertex2f(-1.0, 1.0);
			glEnd();
			glPopMatrix();
			glPopAttrib();
			glEnable(GL_LIGHTING);

		};

		//2) Setup Antialiasing
		void GtViewport::DoAntialiasing()
		{

		};

		//3) Draw the World Coordinate System Icon
		void GtViewport::DrawWorldCoordinateIcon(void)
		{
			//NEED TO MAKE THIS SMARTER WITH SIZING
			GLint viewport[4];// Where The Viewport Values Will Be Stored
			float m[16];//Where the model view matrix will be stored
			glGetIntegerv(GL_VIEWPORT,viewport);	// Retrieves The Viewport Values (X, Y, Width, Height)
			if(this->m_blnDrawWCSAtOrigin)
			{
				this->DrawWCSIconAtCurrLocation();
			}else{
				glViewport(0,0,viewport[2]/5,viewport[3]/5);
				glClear(GL_DEPTH_BUFFER_BIT);
				glMatrixMode(GL_PROJECTION);
				glPushMatrix();
				glLoadIdentity();

				// Calculate The Aspect Ratio Of The Window
				//gluPerspective(this->m_objCurrViewpoint.m_sngFieldOfViewAngle,
				//(GLfloat)(viewport[2])/(GLfloat)(viewport[3]),	0.1f, 10.0f);

				glOrtho(-(GLfloat)(viewport[2])/(GLfloat)(viewport[3]),(GLfloat)(viewport[2])/(GLfloat)(viewport[3]),-1.3,1.3,-2.5,2.5);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();

				Matrix44Assign(m_arrSngCurrModelMatrix,m);
				//glGetFloatv(GL_MODELVIEW_MATRIX,m); //gets the model view matrix
				m[12]=0.0;m[13]=0.0;m[14]=0.0;
				glLoadMatrixf(m);
				//DRAW THE WCS UNIT AXIS ICON
				this->DrawWCSIconAtCurrLocation();
				////
				glViewport(0,0,viewport[2],viewport[3]);
				glPopMatrix();
				glMatrixMode(GL_PROJECTION);
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
			};//end boolean flag check on where to draw the WCS Icon
		};

		void GtViewport::DrawFrustum(void)
		{	
			float DEG2RAD = 3.141593f / 180;
			float sngAspectRatio = this->m_objCurrViewpoint.m_sngHeight /this->m_objCurrViewpoint.m_sngWidth ;
			float sngTangent = tanf(this->m_objCurrViewpoint.m_sngFieldOfViewAngle/2 * DEG2RAD);
			float sngNearHeight = this->m_objCurrViewpoint.m_sngZNearFieldDist * sngTangent;
			float sngNearWidth = sngNearHeight * sngAspectRatio;
			float sngFarHeight = this->m_objCurrViewpoint.m_sngZFarFieldDist * sngTangent;
			float sngFarWidth = sngFarHeight * sngAspectRatio;

			// compute 8 vertices of the frustum
			float vertices[8][3];
			// near top right
			vertices[0][0] = sngNearWidth;     vertices[0][1] = sngNearHeight;    vertices[0][2] = -this->m_objCurrViewpoint.m_sngZNearFieldDist;
			// near top left
			vertices[1][0] = -sngNearWidth;    vertices[1][1] = sngNearHeight;    vertices[1][2] = -this->m_objCurrViewpoint.m_sngZNearFieldDist;
			// near bottom left
			vertices[2][0] = -sngNearWidth;    vertices[2][1] = -sngNearHeight;   vertices[2][2] = -this->m_objCurrViewpoint.m_sngZNearFieldDist;
			// near bottom right
			vertices[3][0] = sngNearWidth;     vertices[3][1] = -sngNearHeight;   vertices[3][2] = -this->m_objCurrViewpoint.m_sngZNearFieldDist;
			// far top right
			vertices[4][0] = sngFarWidth;      vertices[4][1] = sngFarHeight;     vertices[4][2] = -this->m_objCurrViewpoint.m_sngZFarFieldDist;
			// far top left
			vertices[5][0] = -sngFarWidth;     vertices[5][1] = sngFarHeight;     vertices[5][2] = -this->m_objCurrViewpoint.m_sngZFarFieldDist;
			// far bottom left
			vertices[6][0] = -sngFarWidth;     vertices[6][1] = -sngFarHeight;    vertices[6][2] = -this->m_objCurrViewpoint.m_sngZFarFieldDist;
			// far bottom right
			vertices[7][0] = sngFarWidth;      vertices[7][1] = -sngFarHeight;    vertices[7][2] = -this->m_objCurrViewpoint.m_sngZFarFieldDist;

			float colorLine1[4] = { 0.7f, 0.7f, 0.7f, 0.7f };
			float colorLine2[4] = { 0.2f, 0.2f, 0.2f, 0.7f };
			float colorPlane[4] = { 0.5f, 0.5f, 0.5f, 0.5f };

			glDisable(GL_LIGHTING);
			glDisable(GL_CULL_FACE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_LINES);
			glColor4fv(colorLine2);
			glVertex3f(0, 0, 0);
			glColor4fv(colorLine1);
			glVertex3fv(vertices[4]);

			glColor4fv(colorLine2);
			glVertex3f(0, 0, 0);
			glColor4fv(colorLine1);
			glVertex3fv(vertices[5]);

			glColor4fv(colorLine2);
			glVertex3f(0, 0, 0);
			glColor4fv(colorLine1);
			glVertex3fv(vertices[6]);

			glColor4fv(colorLine2);
			glVertex3f(0, 0, 0);
			glColor4fv(colorLine1);
			glVertex3fv(vertices[7]);
			glEnd();

			glColor4fv(colorLine1);
			glBegin(GL_LINE_LOOP);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glEnd();

			glColor4fv(colorLine1);
			glBegin(GL_LINE_LOOP);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
			glEnd();

			glColor4fv(colorPlane);
			glBegin(GL_QUADS);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
			glEnd();

			glEnable(GL_CULL_FACE);
			glEnable(GL_LIGHTING);
		}
		void GtViewport::DrawWCSIconAtCurrLocation(void)
		{
			GLUquadricObj *pObj;	// Temporary, used for quadrics

			// Measurements
			float fAxisRadius = 0.025f;
			float fAxisHeight = 1.0f;
			float fArrowRadius = 0.06f;
			float fArrowHeight = 0.1f;
			// Setup the quadric object
			pObj = gluNewQuadric();
			gluQuadricDrawStyle(pObj, GLU_FILL);
			gluQuadricNormals(pObj, GLU_SMOOTH);
			gluQuadricOrientation(pObj, GLU_OUTSIDE);
			gluQuadricTexture(pObj, GLU_FALSE);

			float shininess = 15.0f;
			float diffuseColor[3] = {0.929524f, 0.796542f, 0.178823f};
			float specularColor[4] = {1.00000f, 0.980392f, 0.549020f, 1.0f};

			// set specular and shiniess using glMaterial (gold-yellow)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); // range 0 ~ 128
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);

			// set ambient and diffuse color using glColorMaterial (gold-yellow)
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			glColor3fv(diffuseColor);


			///////////////////////////////////////////////////////
			// Draw the blue Z axis first, with arrowed head
			glColor3f(0.0f, 0.0f, 1.0f);
			gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, 1.0f);
			gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
			gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
			glPopMatrix();

			///////////////////////////////////////////////////////
			// Draw the Red X axis 2nd, with arrowed head
			glColor3f(1.0f, 0.0f, 0.0f);
			glPushMatrix();
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, 1.0f);
			gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
			glPopMatrix();
			glPopMatrix();

			///////////////////////////////////////////////////////
			// Draw the Green Y axis 3rd, with arrowed head
			glColor3f(0.0f, 1.0f, 0.0f);
			glPushMatrix();
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, 1.0f);
			gluCylinder(pObj, fArrowRadius, 0.0f, fArrowHeight, 10, 1);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
			gluDisk(pObj, fAxisRadius, fArrowRadius, 10, 1);
			glPopMatrix();
			glPopMatrix();

			////////////////////////////////////////////////////////
			// White Sphere at origin
			glColor3f(1.0f, 1.0f, 1.0f);
			gluSphere(pObj, 0.05f, 15, 15);
			glNormal3f(0.0f, 0.0f, 1.0f); //reset the normal; apparently the last normal value produced for the sphere is being carried over

			// Delete the quadric
			gluDeleteQuadric(pObj);
		};

		//4) Draw the World Coordinate System Axes
		void GtViewport::DrawWorldCoordinateAxes(void)
		{

		};

		//5) Draw the User Coordinate System Icon
		void GtViewport::DrawUserCoordinateIcon(void)
		{

		};

		//6) Draw the User Coordinate System Axes
		void GtViewport::DrawUserCoordinateAxes(void)
		{

		};

		//7) Add the Lights
		void GtViewport::DrawLights(void)
		{
			//INITIALIZE VIEWPORT CAMERA LIGHT
			// set up light colors (ambient, diffuse, specular)
			GLfloat lightKa[] = {0.2f, 0.2f, 0.2f, 1.0f};      // ambient light
			GLfloat lightKd[] = {1.0f, 1.0f, 1.0f, 1.0f};      // diffuse light
			GLfloat lightKs[] = {0.8f, 0.8f, 0.8f, 1.0f};      // specular light
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
			glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

			// position the light
			glNormal3f(float(this->m_objCurrViewpoint.m_objViewLocation.x - this->m_objCurrViewpoint.m_objRotationCentroid.x),
				       float(this->m_objCurrViewpoint.m_objViewLocation.y - this->m_objCurrViewpoint.m_objRotationCentroid.y),
				       float(this->m_objCurrViewpoint.m_objViewLocation.z - this->m_objCurrViewpoint.m_objRotationCentroid.z) );
			float lightPos[4] = {0,0,1, 1};

			glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

			glEnable(GL_LIGHT0);                            // MUST enable each light source after configuration
			//TURN ON LIGHTING
			glEnable(GL_LIGHTING);
			glEnable(GL_COLOR_MATERIAL);

		};

		//8) Draw the display grids
		void GtViewport::DrawGrids(void)
		{
			//XY PLANE GRID
			if(this->m_ptrXYPlaneGrid->Get_blnVisible())
			{
				this->m_ptrXYPlaneGrid->RenderModelItem(this->m_objCurrViewpoint,this->m_objRenderMode);
			};
			//XZ PLANE GRID
			if(this->m_ptrXZPlaneGrid->Get_blnVisible())
			{
				this->m_ptrXZPlaneGrid->RenderModelItem(this->m_objCurrViewpoint,this->m_objRenderMode);
			};
			//YZ PLANE GRID
			if(this->m_ptrYZPlaneGrid->Get_blnVisible())
			{
				this->m_ptrYZPlaneGrid->RenderModelItem(this->m_objCurrViewpoint,this->m_objRenderMode);
			};
		};

		//9) Draw the display axes
		void GtViewport::DrawAxes(void)
		{

		};

		//10) Draw the objects in the scene
		void GtViewport::DrawScene(const GtViewpoint & ptrCurrViewPoint)
		{
			try{
				if(this->m_ptrPartModel)
				{
					this->m_ptrPartModel->RenderScene(this->m_objCurrViewpoint,this->m_objRenderMode);
				}
			}catch(...){
				return;
			}
		};
		//11) Update the mouse location based on last position
		void GtViewport::UpdateMouseLocation(GtViewpoint & ptrCurrViewPoint)
		{
			//GLint gluUnProject( GLdouble   winX,  
			//GLdouble   winY,  
			//GLdouble   winZ,  
			//const GLdouble *   model,  
			//const GLdouble *   proj,  
			//const GLint *   view,  
			//GLdouble*   objX,  
			//GLdouble*   objY,  
			//GLdouble*   objZ);

			//viewport[0]=x
			//viewport[1]=y
			//viewport[2]=width
			//viewport[3]=height

			GtPoint3DF objMousePoint;
			GLfloat winX, winY, winZ; 

			//convert the window x and y coords from screen to opengl 
			winX = (float)m_objLastPoint.x; 
			winY = (float)ptrCurrViewPoint.m_arrIntViewport[3] - (float)m_objLastPoint.y; 
			//get the z coord from the pixel buffer
			glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );  
			//unproject the point
			gluUnProject(double(winX),double(winY),double(0.0f),
				ptrCurrViewPoint.m_arrDblCurrModelMatrix, ptrCurrViewPoint.m_arrDblCurrProjMatrix, ptrCurrViewPoint.m_arrIntViewport,
				&(objMousePoint.x),&(objMousePoint.y),&(objMousePoint.z));

			ptrCurrViewPoint.m_objMouseLoc = objMousePoint;
		};

		//Set and Get functions for the Scene Model
		void GtViewport::Set_ptrPartModel(GtPartModel * ptrModel)
		{
			this->m_ptrPartModel = ptrModel;
			//connect(m_ptrPartModel,SIGNAL(SceneModified()),this,SLOT(UpdateViewport()));

			if(m_ptrSelPopUpMenu)
			{
				m_ptrSelPopUpMenu->Set_ptrPartModel(m_ptrPartModel);
			};

		};

		GtPartModel * GtViewport::Get_ptrPartModel(void)
		{
			return this->m_ptrPartModel;
		};


		void GtViewport::Set_dblXTranslation(double dist)
		{
			this->m_objLastViewpoint = this->m_objCurrViewpoint;
			this->m_objCurrViewpoint.m_objViewLocation.x = this->m_objCurrViewpoint.m_objViewLocation.x + dist;
			this->m_objCurrViewpoint.m_objRotationCentroid.x = this->m_objCurrViewpoint.m_objRotationCentroid.x + dist;
			PostPaint();
		};

		void GtViewport::Set_dblYTranslation(double dist)
		{
			this->m_objLastViewpoint = this->m_objCurrViewpoint;
			this->m_objCurrViewpoint.m_objViewLocation.y = this->m_objCurrViewpoint.m_objViewLocation.y + dist;
			this->m_objCurrViewpoint.m_objRotationCentroid.y = this->m_objCurrViewpoint.m_objRotationCentroid.y + dist;
			PostPaint();
		};

		void GtViewport::Set_dblZTranslation(double dist)
		{
			this->m_objLastViewpoint = this->m_objCurrViewpoint;
			this->m_objCurrViewpoint.m_objViewLocation.z = this->m_objCurrViewpoint.m_objViewLocation.z + dist;
			this->m_objCurrViewpoint.m_objRotationCentroid.z = this->m_objCurrViewpoint.m_objRotationCentroid.z + dist;
			PostPaint();
		};

		void GtViewport::Set_dblXRotation(double dblAngle)
		{
			//this->NormalizeAngle(dblAngle);
			this->m_objLastViewpoint = this->m_objCurrViewpoint;
			this->m_objCurrViewpoint.m_objRotation.x = dblAngle;
			PostPaint();
		};

		void GtViewport::Set_dblYRotation(double dblAngle)
		{
			//this->NormalizeAngle(dblAngle);
			this->m_objLastViewpoint = this->m_objCurrViewpoint;
			this->m_objCurrViewpoint.m_objRotation.y = dblAngle;
			PostPaint();
		};

		void GtViewport::Set_dblZRotation(double dblAngle)
		{
			//this->NormalizeAngle(dblAngle);
			this->m_objLastViewpoint = this->m_objCurrViewpoint;
			this->m_objCurrViewpoint.m_objRotation.z = dblAngle;
			PostPaint();
		};

		//Event handlers for the various actions and editors
		//!Sets the viewport to Top View (Looking At XYPlane in the Z Negative Direction)
		void GtViewport::OnSetViewTop_XYPlane_ZNeg(void)
		{
			GtViewpoint objNewViewpoint;
			objNewViewpoint.m_objViewLocation.Set(0.0,0.0,10.0);
			objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
			objNewViewpoint.m_objRotation.Zero();
			objNewViewpoint.m_objUpDir.Set(0.0,1.0,0.0);
			this->Set_objCurrViewpoint(objNewViewpoint);
			this->ZoomExtents();
			this->PostPaint();
			return;
		};
		//!Sets the viewport to Top View (Looking At XYPlane in the Z Positive Direction)
		void GtViewport::OnSetViewBottom_XYPlane_ZPos(void)
		{
			GtViewpoint objNewViewpoint;
			objNewViewpoint.m_objViewLocation.Set(0.0,0.0,-10.0);
			objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
			objNewViewpoint.m_objRotation.Zero();
			objNewViewpoint.m_objUpDir.Set(0.0,1.0,0.0);
			this->Set_objCurrViewpoint(objNewViewpoint);
			this->ZoomExtents();
			this->PostPaint();

			return;
		};
		//!Sets the viewport to Left View (Looking At XZPlane in the Y Negative Direction)
		void GtViewport::OnSetViewLeft_XZPlane_YNeg(void)
		{
			GtViewpoint objNewViewpoint;
			objNewViewpoint.m_objViewLocation.Set(0.0,10.0,0.0);
			objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
			objNewViewpoint.m_objRotation.Zero();
			objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
			this->Set_objCurrViewpoint(objNewViewpoint);
			this->ZoomExtents();
			this->PostPaint();

			return;
		};
		//!Sets the viewport to Right View (Looking At XZPlane in the Y Positive Direction)
		void GtViewport::OnSetViewRight_XZPlane_YPos(void)
		{
			GtViewpoint objNewViewpoint;
			objNewViewpoint.m_objViewLocation.Set(0.0,-10.0,0.0);
			objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
			objNewViewpoint.m_objRotation.Zero();
			objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
			this->Set_objCurrViewpoint(objNewViewpoint);
			this->ZoomExtents();
			this->PostPaint();

			return;

		};
		//!Sets the viewport to Front View (Looking At YZPlane in the X Negative Direction)
		void GtViewport::OnSetViewFront_YZPlane_XNeg(void)
		{
			GtViewpoint objNewViewpoint;
			objNewViewpoint.m_objViewLocation.Set(10.0,0.0,0.0);
			objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
			objNewViewpoint.m_objRotation.Zero();
			objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
			this->Set_objCurrViewpoint(objNewViewpoint);
			this->ZoomExtents();
			this->PostPaint();

			return;
		};
		//!Sets the viewport to Back View (Looking At YZPlane in the X Positive Direction)
		void GtViewport::OnSetViewBack_YZPlane_XPos(void)
		{
			GtViewpoint objNewViewpoint;
			objNewViewpoint.m_objViewLocation.Set(-10.0,0.0,0.0);
			objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
			objNewViewpoint.m_objRotation.Zero();
			objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
			this->Set_objCurrViewpoint(objNewViewpoint);
			this->ZoomExtents();
			this->PostPaint();

			return;
		};


		float GtViewport::GetViewScale(void)
		{
			int intScreenWidth;
			float sngHalfAngle, sngWorldWidth;
			sngHalfAngle = this->m_objCurrViewpoint.m_sngFieldOfViewAngle / (2.0f);
			sngWorldWidth = 2 * (m_objCurrViewpoint.m_sngZNearFieldDist * tan(sngHalfAngle));
			intScreenWidth = m_objFrame.Width();

			return (float(intScreenWidth) / sngWorldWidth);
		};

		void GtViewport::NormalizeAngle(double & dblAngle)
		{//normalize angle to be between -360.0 <= A <= +360.0
			int intMult;
			intMult = int(floor(dblAngle / 360.0f));
			if(dblAngle < 0.0f)
			{
				dblAngle = dblAngle + intMult * 360.0f;
			}else{
				dblAngle = dblAngle - intMult * 360.0f;
			};
		};

		void GtViewport::Pan( double dx, double dy )
		{
			try{
				m_objLastViewpoint = m_objCurrViewpoint;
				//reverse dy coordinate because of microsoft windows screen coordinate convention
				dy = -1.0*dy;
				dx = +1.0*dx;

				GtPoint3DF eye = m_objCurrViewpoint.m_objViewLocation;
				GtPoint3DF center = m_objCurrViewpoint.m_objRotationCentroid;
				GtPoint3DF up = m_objCurrViewpoint.m_objUpDir;
				GtPoint3DF DirX =  m_objCurrViewpoint.m_objUpDir;
				double dblMagY = Mag3D(Cross3D(DirX,Diff3D(eye,center)));
				GtPoint3DF DirY, DirYnum;
				DirYnum = Cross3D(DirX,Diff3D(eye,center));
				DirY.Set(DirYnum.x/dblMagY,DirYnum.y/dblMagY,DirYnum.z/dblMagY);

				double view_angle = m_objCurrViewpoint.m_sngFieldOfViewAngle;
				double object_width = m_objCurrViewpoint.m_sngWidth / m_objCurrViewpoint.m_sngHeight;
				double length = ( eye - center ).Mag() * tan( view_angle * M_PI / 360.0 ) * 2.0;

				m_objCurrViewpoint.m_objViewLocation = m_objCurrViewpoint.m_objViewLocation
					+ (DirY * dx * length * object_width) + (DirX * dy * length);
				m_objCurrViewpoint.m_objRotationCentroid = m_objCurrViewpoint.m_objRotationCentroid
					+ (DirY * dx * length * object_width) + (DirX * dy * length);

			}catch(...){
				return;
			};

		}

		void GtViewport::Zoom( double dx, double dy )
		{
			m_objLastViewpoint = m_objCurrViewpoint;

			GtPoint3DF eye( m_objCurrViewpoint.m_objViewLocation.x, m_objCurrViewpoint.m_objViewLocation.y, m_objCurrViewpoint.m_objViewLocation.z );
			GtPoint3DF center( m_objCurrViewpoint.m_objRotationCentroid.x, m_objCurrViewpoint.m_objRotationCentroid.y, m_objCurrViewpoint.m_objRotationCentroid.z );
			eye = center + ( eye - center ) * ( dy + 1.0 );

			this->m_objCurrViewpoint.m_objViewLocation.x = eye[0];
			this->m_objCurrViewpoint.m_objViewLocation.y = eye[1];
			this->m_objCurrViewpoint.m_objViewLocation.z = eye[2];
		}

		void GtViewport::Zoom( int delta)
		{
			//ZOOM IN OR OUT (Y+ ZOOM IN / Y- ZOOM OUT)
			float sngZoomOutScale = float(1.10f);
			float sngZoomInScale = float(0.90f);
			GtPoint3DF objDiff;

			objDiff.x = this->m_objCurrViewpoint.m_objViewLocation.x - this->m_objCurrViewpoint.m_objRotationCentroid.x;
			objDiff.y = this->m_objCurrViewpoint.m_objViewLocation.y - this->m_objCurrViewpoint.m_objRotationCentroid.y;
			objDiff.z = this->m_objCurrViewpoint.m_objViewLocation.z - this->m_objCurrViewpoint.m_objRotationCentroid.z;

			if(delta > 0)
			{
				//zoom out
				this->m_objCurrViewpoint.m_objViewLocation.x = this->m_objCurrViewpoint.m_objRotationCentroid.x + (objDiff.x * sngZoomOutScale);
				this->m_objCurrViewpoint.m_objViewLocation.y = this->m_objCurrViewpoint.m_objRotationCentroid.y + (objDiff.y * sngZoomOutScale);
				this->m_objCurrViewpoint.m_objViewLocation.z = this->m_objCurrViewpoint.m_objRotationCentroid.z + (objDiff.z * sngZoomOutScale);

			}else{
				//zoom in
				this->m_objCurrViewpoint.m_objViewLocation.x = this->m_objCurrViewpoint.m_objRotationCentroid.x + (objDiff.x * sngZoomInScale);
				this->m_objCurrViewpoint.m_objViewLocation.y = this->m_objCurrViewpoint.m_objRotationCentroid.y + (objDiff.y * sngZoomInScale);
				this->m_objCurrViewpoint.m_objViewLocation.z = this->m_objCurrViewpoint.m_objRotationCentroid.z + (objDiff.z * sngZoomInScale);
			}
		};

		void GtViewport::ZoomExtents(void)
		{
			//calculate the directional vector
			//AABB of the scene
			//calculate the new required spherical radius to fit in view (rhoNew)
			//calculate the polar coordinates
			//assign rhoNew
			//transform back to cartesian
			//offset eye and center to correct locations
			GtPartModel* ptrModel = this->Get_ptrPartModel();
			if(!ptrModel){return;};//safety check
			GtAABox objBoundingBox;
			GtPoint3DF objDirection, objNewCentroid, dblBBMax;
			GtPoint3DF objNewEye,dblNewRad, dblTranslate,objNewEyeTranslate;
			double dblTheta,dblPhi,dblViewAngle;//spherical coord angles
			double dblSceneRad,dblRad,dblRho,dblReqRho;

			//calculate the directional vector
			objDirection.x = this->m_objCurrViewpoint.m_objViewLocation.x - this->m_objCurrViewpoint.m_objRotationCentroid.x;
			objDirection.y = this->m_objCurrViewpoint.m_objViewLocation.y - this->m_objCurrViewpoint.m_objRotationCentroid.y;
			objDirection.z = this->m_objCurrViewpoint.m_objViewLocation.z - this->m_objCurrViewpoint.m_objRotationCentroid.z;

			//calculate the scene bounding box
			if(ptrModel->CountModelItems() <= 0)
			{
				objBoundingBox.m_dblXMin = -5; objBoundingBox.m_dblXMax = 5;
				objBoundingBox.m_dblYMin = -5; objBoundingBox.m_dblYMax = 5;
				objBoundingBox.m_dblZMin = -5; objBoundingBox.m_dblZMax = 5;
			}else{
				objBoundingBox = ptrModel->GetSceneBoundingBox(false);
			}
			//calc the new centroid
			objNewCentroid.x = (objBoundingBox.m_dblXMax + objBoundingBox.m_dblXMin) / (2.0f);
			objNewCentroid.y = (objBoundingBox.m_dblYMax + objBoundingBox.m_dblYMin) / (2.0f);
			objNewCentroid.z = (objBoundingBox.m_dblZMax + objBoundingBox.m_dblZMin) / (2.0f);
			//calculate the required scene radius
			dblBBMax.x = objBoundingBox.m_dblXMax;
			dblBBMax.y = objBoundingBox.m_dblYMax;
			dblBBMax.z = objBoundingBox.m_dblZMax;

			dblNewRad = Diff3D(dblBBMax,objNewCentroid);
			dblSceneRad = Mag3D(dblNewRad);
			if(dblSceneRad < 10.0)
			{//enforce minimum zoom
				dblSceneRad = 10.0;
			};
			dblViewAngle = this->m_objCurrViewpoint.m_sngFieldOfViewAngle / (2.0f);//need half of fovy angle

			dblReqRho = dblSceneRad / tan(dblViewAngle);
			//calculate the theta and phi angles for polar coordinates
			dblRad = Mag2D(objDirection);
			dblRho = Mag3D(objDirection);
			if(dblRad > 0)
			{
				dblTheta = acos((objDirection.x /dblRad));
			}else{
				//purely vertical z direction, assign theta 0;
				dblTheta = 0;
			};
			if(dblRho > 0)
			{
				dblPhi = acos((objDirection.z /dblRho));
			}else{
				dblPhi = 0;
			};

			//spherical coord of new untranslated coordinate is now (dblReqRho,dblTheta,dblPhi)
			//calculate new rotation centroid offsets
			dblTranslate = objNewCentroid;//might need to offset from m_objRotationCentroid
			objNewEye.x = dblReqRho * cos(dblTheta) * sin(dblPhi);
			objNewEye.y = dblReqRho * sin(dblTheta) * sin(dblPhi);
			objNewEye.z = dblReqRho * cos(dblPhi);
			//calculate new eye location
			objNewEyeTranslate = Add3D(objNewEye,dblTranslate);
			//Set the FINAL VALUES
			this->m_objCurrViewpoint.m_objRotationCentroid = objNewCentroid;
			this->m_objCurrViewpoint.m_objViewLocation = objNewEyeTranslate;

			return;		
		};

		void GtViewport::RotateOrbit( double dx, double dy )
		{
			try
			{
				m_objLastViewpoint = m_objCurrViewpoint;

				GtPoint3DF eye = m_objCurrViewpoint.m_objViewLocation;
				GtPoint3DF center = m_objCurrViewpoint.m_objRotationCentroid;
				GtPoint3DF up = m_objCurrViewpoint.m_objUpDir;

				GtPoint3DF axis = ( up ^ ( center - eye ) );
				axis.Normalize();
				eye = RotatePoint( eye, center, up, -dx * M_PI );
				eye = RotatePoint( eye, center, axis, dy * M_PI );
				up = ( RotatePoint( ( center + up ), center, axis, dy * M_PI ) - center );
				up.Normalize();

				this->m_objCurrViewpoint.m_objViewLocation.x = eye[0];
				this->m_objCurrViewpoint.m_objViewLocation.y = eye[1];
				this->m_objCurrViewpoint.m_objViewLocation.z = eye[2];

				this->m_objCurrViewpoint.m_objUpDir.x = up[0];
				this->m_objCurrViewpoint.m_objUpDir.y = up[1];
				this->m_objCurrViewpoint.m_objUpDir.z = up[2];
				return;
			}catch(...){
				return;
			};
		}

		void GtViewport::RotateCamera( double dx, double dy )
		{
			try{
				m_objLastViewpoint = m_objCurrViewpoint;
				double factor = 40.0;
				this->Set_dblXRotation( this->m_objCurrViewpoint.m_objRotation.x + ( factor * dy ) );
				this->Set_dblYRotation( this->m_objCurrViewpoint.m_objRotation.y + ( factor * dx ) );
			}catch(...){
				return;
			};

		}


		std::vector<GtCadObject*> GtViewport::GetSelectedObjects(void)
		{
			m_arrSelection.clear();
			size_t i,intNumItems;
			intNumItems = this->m_ptrPartModel->CountModelItems();
			for(i = 0; i < intNumItems;i++)
			{
				if(m_ptrPartModel->AtModelItem(i)->Get_blnSelected())
				{
					m_arrSelection.push_back(m_ptrPartModel->AtModelItem(i));
				};
			};
			return this->m_arrSelection;
		};



		void GtViewport::UnDockViewport(void)
		{
			try{
				////clean up the floating viewport
				//if(m_ptrFloatingDialog)
				//{
				//	delete m_ptrFloatingDialog;
				//};
				//m_ptrFloatingDialog = new GtFloatingDialog(NULL);
				//m_ptrFloatingDialog->Set_ptrGtViewport(this);
				//this->setParent(m_ptrFloatingDialog);
				//this->m_blnDocked = false;
				//m_ptrFloatingDialog->show();
				//this->painGt();

			}catch(...){
				//error
				return;
			};
		};

		void GtViewport::DockViewport(void)
		{
			try{
				////reset to owner
				//if(m_ptrOwner)
				//{
				//	GtPoint3DF objLoc = this->pos();
				//	QSize objFrameSize = this->m_ptrOwner->size();
				//	this->setParent(this->m_ptrOwner);
				//	this->resize(objFrameSize);
				//	this->m_blnDocked = true;
				//	this->show();
				//	this->m_ptrOwner->update();
				//	this->painGt();
				//}else{
				//	return;
				//};
				////clean up
				//if(m_ptrFloatingDialog)
				//{	
				//	m_ptrFloatingDialog->Set_ptrGtViewport(NULL);
				//	m_ptrFloatingDialog->hide();
				//	delete m_ptrFloatingDialog;
				//	m_ptrFloatingDialog = NULL;
				//};
			}catch(...){
				//error
				return;
			};

		};

		bool SortHitMinDist(GtHitRecord & objA,GtHitRecord & objB)
		{
			return (objA.m_dblHitDist > objB.m_dblHitDist);
		};
		bool SortHitMaxDist(GtHitRecord & objA,GtHitRecord & objB)
		{
			return (objA.m_dblHitDist < objB.m_dblHitDist);
		};

		void GtViewport::ProcessSelection(GtPoint3DI & objSelPoint)
		{	
			std::string strTemp;
			GtPoint3DF objSelCoords;
			GtPoint3DF objSelOrig;
			GtPoint3DF objSelRayDir;
			//convert the viewport to world coordinates
			GtOpenGL::ViewportPickRay(this->m_objCurrViewpoint,objSelPoint,objSelOrig,objSelRayDir);

			//objSelOrig = m_objCurrViewpoint.m_objViewLocation;

			//objSelRayDir = m_objCurrViewpoint.m_objMouseLoc - m_objCurrViewpoint.m_objViewLocation;

			//objSelRayDir.Normalize();

			if(!this->m_blnSelectionEnabled){return;};
			if(!this->m_ptrPartModel){return;};
			if(this->m_ptrPartModel->CountModelItems() <= 0){return;};
			int i, intNumItems;

			//clear the previous selection
			this->m_arrSelection.clear();
			m_ptrPartModel->ClearSelection();

			intNumItems = this->m_ptrPartModel->CountModelItems();
			std::vector<GtHitRecord> arrObjHits;
			for(i = 0; i < intNumItems; i++)
			{
				GtHitRecord objHitTemp;
				objHitTemp.m_blnHit = false;
				GtCadObject * ptrItem = m_ptrPartModel->AtModelItem(i);
				strTemp = ptrItem->Get_strName();
				this->m_ptrPartModel->SelectHitTest(objSelOrig,objSelRayDir, i, objHitTemp);
				if(objHitTemp.m_blnHit)
				{
					arrObjHits.push_back(objHitTemp);
				};
			};



			if(arrObjHits.size() > 0)
			{
				std::sort(arrObjHits.begin(),arrObjHits.end(),SortHitMinDist);
				//make the selection to the closest item

				if(this->m_blnSingleSelect)
				{
					size_t intSelection = arrObjHits.at(0).m_intSelIndex;

					m_ptrPartModel->SelectModelItem(intSelection,true);
				}else{
					//otherwise load context popup selection menu

					/*GtPoint3DF globalPos = this->mapToGlobal(objSelPoint);
					if(m_ptrSelPopUpMenu)
					{
						std::vector<GtCadObject*> arrTemp;
						m_ptrSelPopUpMenu->ClearGtMenu();
						for(int j = 0; j < arrObjHits.size();j++)
						{
							size_t intSelection = arrObjHits.at(j).m_intSelIndex;
							arrTemp.push_back( m_ptrPartModel->AtModelItem(intSelection));
						};
						m_ptrSelPopUpMenu->AddItems(arrTemp);
						m_ptrSelPopUpMenu->Set_objPos(globalPos);
						m_ptrSelPopUpMenu->SetVisible(true);
						arrTemp.clear();
					};//menu pointer check*/
					//m_ptrISAConstraintMenu->popup(globalPos,NULL);
				};

			};
			strTemp.clear();
			m_ptrPartModel->UpdateScene();
			SelectionChanged.Emit();
		};

		void GtViewport::UpdateViewport(void)
		{
			this->PostPaint();
		};


		//void  GtViewport::DrawTestPyramid(void)
		//{
		//	glMatrixMode(GL_MODELVIEW);
		//	glPushMatrix();
		//	glLoadIdentity();
		//	glTranslatef(-1.5f,0.0f,-6.0f);			// translate the view within the viewport relative to current location
		//	//glRotatef(triRotAngle,1.0f,0.0f,0.0f);		// Rotate The Triangle On The Y axis (note: translate, then rotate)
		//	glBegin(GL_TRIANGLES);					// Drawing Using Triangles
		//	glColor3f(1.0f,0.0f,0.0f);				// Red
		//	glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Front)
		//	glColor3f(0.0f,1.0f,0.0f);				// Green
		//	glVertex3f(-1.0f,-1.0f, 1.0f);			// Left Of Triangle (Front)
		//	glColor3f(0.0f,0.0f,1.0f);				// Blue
		//	glVertex3f( 1.0f,-1.0f, 1.0f);			// Right Of Triangle (Front)

		//	glColor3f(1.0f,0.0f,0.0f);				// Red
		//	glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Right)
		//	glColor3f(0.0f,0.0f,1.0f);				// Blue
		//	glVertex3f( 1.0f,-1.0f, 1.0f);			// Left Of Triangle (Right)
		//	glColor3f(0.0f,1.0f,0.0f);				// Green
		//	glVertex3f( 1.0f,-1.0f, -1.0f);			// Right Of Triangle (Right)

		//	glColor3f(1.0f,0.0f,0.0f);				// Red
		//	glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Back)
		//	glColor3f(0.0f,1.0f,0.0f);				// Green
		//	glVertex3f( 1.0f,-1.0f, -1.0f);			// Left Of Triangle (Back)
		//	glColor3f(0.0f,0.0f,1.0f);				// Blue
		//	glVertex3f(-1.0f,-1.0f, -1.0f);			// Right Of Triangle (Back)

		//	glColor3f(1.0f,0.0f,0.0f);				// Red
		//	glVertex3f( 0.0f, 1.0f, 0.0f);			// Top Of Triangle (Left)
		//	glColor3f(0.0f,0.0f,1.0f);				// Blue
		//	glVertex3f(-1.0f,-1.0f,-1.0f);			// Left Of Triangle (Left)
		//	glColor3f(0.0f,1.0f,0.0f);				// Green
		//	glVertex3f(-1.0f,-1.0f, 1.0f);			// Right Of Triangle (Left)
		//	glEnd();								// Finished Drawing the Triangle
		//	glBegin(GL_QUADS);						// Drawing Using Quads
		//	glColor3f(0.0f,0.0f,1.0f);				// Blue
		//	glVertex3f(-1.0f, -1.0f, -1.0f);		// (Bottom)
		//	glColor3f(0.0f,1.0f,0.0f);				// Green
		//	glVertex3f( 1.0f,-1.0f, -1.0f);			// (Bottom)
		//	glColor3f(0.0f,0.0f,1.0f);				// Blue
		//	glVertex3f( 1.0f,-1.0f, 1.0f);			// (Bottom)
		//	glColor3f(0.0f,1.0f,0.0f);				// Green
		//	glVertex3f(-1.0f,-1.0f, 1.0f);			// (Bottom)
		//	glEnd();								// Finished Drawing the Quad
		//	glLoadIdentity();
		//	//triRotAngle += 2.0;

		//	//glTranslatef(1.0f,0.0f,-10.0f);			// translate the view within the viewport relative to current location
		//	//glBegin(GL_TRIANGLES);					// Drawing Using Triangles
		//	//	glVertex3f( 0.0f, 1.0f, 0.0f);			// Top
		//	//	glVertex3f(-1.0f,-1.0f, 0.0f);			// Bottom Left
		//	//	glVertex3f( 1.0f,-1.0f, 0.0f);			// Bottom Right
		//	//glEnd();	


		//	glTranslatef(1.0f,0.0f,-10.0f);
		//	//By drawing in a clockwise order, the square will be drawn as a back face. Meaning the side of the quad we see is actually the back.
		//	glBegin(GL_QUADS);						// Draw A Quad
		//	glVertex3f(-1.0f, 1.0f, 0.0f);			// Top Left
		//	glVertex3f( 1.0f, 1.0f, 0.0f);			// Top Right
		//	glVertex3f( 1.0f,-1.0f, 0.0f);			// Bottom Right
		//	glVertex3f(-1.0f,-1.0f, 0.0f);			// Bottom Left
		//	glEnd();
		//	glPopMatrix();

		//};
	};//end namespace GtOpenGL
};//end namespace GT