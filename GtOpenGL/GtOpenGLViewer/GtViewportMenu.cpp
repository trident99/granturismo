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

#include ".\GtViewportMenu.h"
#include ".\GtViewport.h"

#include "..\GtOpenGLModel\GtCadObject.h"
#include "..\GtOpenGLModel\GtCadLayer.h"
#include "..\GtOpenGLModel\GtPartModel.h"

#include <modGtEvent.h>

namespace GT
{

	namespace GtOpenGL
	{

		GtViewportMenu::GtViewportMenu(GtObject* ptrParent)
			: GtMenu(ptrParent)
		{
			//Set pointers to NULL before GUI initialization	
			//set view menu
			m_ptrSetViewMenu = NULL;
			m_ptrTopViewAction = NULL;
			m_ptrBottomViewAction = NULL;
			m_ptrLeftViewAction = NULL;
			m_ptrRightViewAction = NULL;
			m_ptrFrontViewAction = NULL;
			m_ptrBackViewAction = NULL;
			//lock axis menu
			m_ptrAxisLockMenu = NULL;
			m_ptrToggleLockXAxisAction = NULL;
			m_ptrToggleLockYAxisAction = NULL;
			m_ptrToggleLockZAxisAction = NULL;
			//projection menu
			m_ptrProjectionModeMenu = NULL;
			m_ptrPerspectiveAction = NULL;
			m_ptrOrthographicAction = NULL;
			//set render mode menu
			m_ptrRenderModeMenu = NULL;
			m_ptrCurvesOnlyAction = NULL;
			m_ptrCurvesWithMeshAction = NULL;
			m_ptrShadedAction = NULL;
			m_ptrShadedWithMeshAction = NULL;
			m_ptrShadedWithCurvesAction = NULL;
			m_ptrShadedBoundaryAction = NULL;
			m_ptrShadeSelectedAction = NULL;
			//editors menu
			m_ptrLightingEditorAction = NULL;
			m_ptrViewportPropEditorAction = NULL;

			m_ptrViewDockAction = NULL;
			m_ptrViewUnDockAction = NULL;

			//Pointer fot the viewport parent
			m_ptrViewportParent = NULL;

			//set up the user interface and initialize the toolbar
			Initialize();
		};

		GtViewportMenu::~GtViewportMenu()
		{

		};

		//!Initialize the Tool Bar for the viewport
		void GtViewportMenu::Initialize(void)
		{
			this->CreateActions();
			this->CreateMenus();
		};

		//!Create the Main Menu Actions and connect them to the slots code for handling their events
		void GtViewportMenu::CreateActions(void)
		{
			//SET VIEW ACTIONS

			m_ptrTopViewAction = new GtAction();
			if(m_ptrTopViewAction)
			{
				m_ptrTopViewAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Top View";
				m_ptrTopViewAction->Set_strText(strText);
				m_ptrTopViewAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetTopView_XYPlane_ZNeg);		
				//m_ptrTopViewAction->setStatusTip(tr("(Looking At XYPlane in the Z Negative Direction)"));
			}

			m_ptrBottomViewAction = new GtAction();
			if(m_ptrBottomViewAction)
			{
				m_ptrBottomViewAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Bottom View";
				m_ptrBottomViewAction->Set_strText(strText);
				m_ptrBottomViewAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetBottomView_XYPlane_ZPos);		
				//m_ptrBottomViewAction->setStatusTip(tr("(Looking At XYPlane in the Z Positive Direction)"));
			}

			m_ptrLeftViewAction = new GtAction();
			if(m_ptrLeftViewAction)
			{
				m_ptrLeftViewAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Left View";
				m_ptrLeftViewAction->Set_strText(strText);
				m_ptrLeftViewAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetLeftView_XZPlane_YNeg);		
				//m_ptrLeftViewAction->setStatusTip(tr("(Looking At XZPlane in the Y Negative Direction)"));
			}

			m_ptrRightViewAction = new GtAction();
			if(m_ptrRightViewAction)
			{
				m_ptrRightViewAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Right View";
				m_ptrRightViewAction->Set_strText(strText);
				m_ptrRightViewAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRightView_XZPlane_YPos);		
				//m_ptrRightViewAction->setStatusTip(tr("(Looking At XZPlane in the Y Positive Direction)"));
			}

			m_ptrFrontViewAction = new GtAction();
			if(m_ptrFrontViewAction)
			{
				m_ptrFrontViewAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Front View";
				m_ptrFrontViewAction->Set_strText(strText);
				m_ptrFrontViewAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetFrontView_YZPlane_XNeg);		
				//m_ptrFrontViewAction->setStatusTip(tr("(Looking At YZPlane in the X Negative Direction)"));
			}

			m_ptrBackViewAction = new GtAction();
			if(m_ptrBackViewAction)
			{
				m_ptrBackViewAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Back View";
				m_ptrBackViewAction->Set_strText(strText);
				m_ptrBackViewAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetBackView_YZPlane_XPos);		
				//m_ptrBackViewAction->setStatusTip(tr("(Looking At YZPlane in the X Positive Direction)"));
			}

			//TOGGLE AXIS LOCK ACTIONS

			m_ptrToggleLockXAxisAction = new GtAction();
			if(m_ptrToggleLockXAxisAction)
			{
				m_ptrToggleLockXAxisAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Lock X-Axis";
				m_ptrToggleLockXAxisAction->Set_strText(strText);
				m_ptrToggleLockXAxisAction->Set_blnCheckable(true);
				m_ptrToggleLockXAxisAction->Triggered.SlotConnect(this,&GtViewportMenu::OnToggleLock_XAxis);		
				//m_ptrToggleLockXAxisAction->setStatusTip(tr("(Toggle Locking X-Axis for Viewport)"));
			}

			m_ptrToggleLockYAxisAction = new GtAction();
			if(m_ptrToggleLockYAxisAction)
			{
				m_ptrToggleLockYAxisAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Lock Y-Axis";
				m_ptrToggleLockYAxisAction->Set_strText(strText);
				m_ptrToggleLockYAxisAction->Set_blnCheckable(true);
				m_ptrToggleLockYAxisAction->Triggered.SlotConnect(this,&GtViewportMenu::OnToggleLock_YAxis);		
				//m_ptrToggleLockYAxisAction->setStatusTip(tr("(Toggle Locking Y-Axis for Viewport)"));
			}

			m_ptrToggleLockZAxisAction = new GtAction();
			if(m_ptrToggleLockZAxisAction)
			{
				m_ptrToggleLockZAxisAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Lock Z-Axis";
				m_ptrToggleLockZAxisAction->Set_strText(strText);
				m_ptrToggleLockZAxisAction->Set_blnCheckable(true);
				m_ptrToggleLockZAxisAction->Triggered.SlotConnect(this,&GtViewportMenu::OnToggleLock_ZAxis);		
				//m_ptrToggleLockZAxisAction->setStatusTip(tr("(Toggle Locking Z-Axis for Viewport)"));
			}


			//PROJECTION MODE ACTIONS

			m_ptrPerspectiveAction = new GtAction();
			if(m_ptrPerspectiveAction)
			{
				m_ptrPerspectiveAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Perspective";
				m_ptrPerspectiveAction->Set_strText(strText);
				m_ptrPerspectiveAction->Set_blnCheckable(true);
				m_ptrPerspectiveAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetProjectionMode_Perspective);		
				//m_ptrPerspectiveAction->setStatusTip(tr("(Set Projection Mode: Perspective)"));
			}

			m_ptrOrthographicAction = new GtAction();
			if(m_ptrOrthographicAction)
			{
				m_ptrOrthographicAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Orthographic";
				m_ptrOrthographicAction->Set_strText(strText);
				m_ptrOrthographicAction->Set_blnCheckable(true);
				m_ptrOrthographicAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetProjectionMode_Orthographic);		
				//m_ptrOrthographicAction->setStatusTip(tr("(Set Projection Mode: Orthographic)"));
			}


			//RENDER MODE ACTIONS

			m_ptrCurvesOnlyAction = new GtAction();
			if(m_ptrCurvesOnlyAction)
			{
				m_ptrCurvesOnlyAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "CurvesOnly";
				m_ptrCurvesOnlyAction->Set_strText(strText);
				m_ptrCurvesOnlyAction->Set_blnCheckable(true);
				m_ptrCurvesOnlyAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRenderMode_CurvesOnly);		
				//m_ptrCurvesOnlyAction->setStatusTip(tr("(Set Render Mode: CurvesOnly)"));
			}

			m_ptrCurvesWithMeshAction = new GtAction();
			if(m_ptrCurvesWithMeshAction)
			{
				m_ptrCurvesWithMeshAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "CurvesWithMesh";
				m_ptrCurvesWithMeshAction->Set_strText(strText);
				m_ptrCurvesWithMeshAction->Set_blnCheckable(true);
				m_ptrCurvesWithMeshAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRenderMode_CurvesWithMesh);		
				//m_ptrCurvesWithMeshAction->setStatusTip(tr("(Set Render Mode: CurvesWithMesh)"));
			}

			m_ptrShadedAction = new GtAction();
			if(m_ptrShadedAction)
			{
				m_ptrShadedAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Shaded";
				m_ptrShadedAction->Set_strText(strText);
				m_ptrShadedAction->Set_blnCheckable(true);
				m_ptrShadedAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRenderMode_CurvesWithMesh);		
				//m_ptrShadedAction->setStatusTip(tr("(Set Render Mode: Shaded)"));
			}

			m_ptrShadedWithMeshAction = new GtAction();
			if(m_ptrShadedWithMeshAction)
			{
				m_ptrShadedWithMeshAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "ShadedWithMesh";
				m_ptrShadedWithMeshAction->Set_strText(strText);
				m_ptrShadedWithMeshAction->Set_blnCheckable(true);
				m_ptrShadedWithMeshAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRenderMode_ShadedWithMesh);		
				//m_ptrShadedWithMeshAction->setStatusTip(tr("(Set Render Mode: ShadedWithMesh)"));
			}

			m_ptrShadedWithCurvesAction = new GtAction();
			if(m_ptrShadedWithCurvesAction)
			{
				m_ptrShadedWithCurvesAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "ShadedWithCurves";
				m_ptrShadedWithCurvesAction->Set_strText(strText);
				m_ptrShadedWithCurvesAction->Set_blnCheckable(true);
				m_ptrShadedWithCurvesAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRenderMode_ShadedWithCurves);		
				//m_ptrShadedWithCurvesAction->setStatusTip(tr("Set Render Mode: ShadedWithCurves)"));
			}

			m_ptrShadedBoundaryAction = new GtAction();
			if(m_ptrShadedBoundaryAction)
			{
				m_ptrShadedBoundaryAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "ShadedBoundary";
				m_ptrShadedBoundaryAction->Set_strText(strText);
				m_ptrShadedBoundaryAction->Set_blnCheckable(true);
				m_ptrShadedBoundaryAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRenderMode_ShadedBoundary);		
				//m_ptrShadedBoundaryAction->setStatusTip(tr("(Set Render Mode: ShadedBoundary)"));
			}

			m_ptrShadeSelectedAction = new GtAction();
			if(m_ptrShadeSelectedAction)
			{
				m_ptrShadeSelectedAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "ShadeSelected";
				m_ptrShadeSelectedAction->Set_strText(strText);
				m_ptrShadeSelectedAction->Set_blnCheckable(true);
				m_ptrShadeSelectedAction->Triggered.SlotConnect(this,&GtViewportMenu::OnSetRenderMode_ShadeSelected);		
				//m_ptrShadeSelectedAction->setStatusTip(tr("(Set Render Mode: ShadeSelected)"));
			}

			//LIGHTING EDITOR ACTION
			m_ptrLightingEditorAction = new GtAction();
			if(m_ptrLightingEditorAction)
			{
				m_ptrLightingEditorAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Lighting Editor";
				m_ptrLightingEditorAction->Set_strText(strText);
				m_ptrLightingEditorAction->Triggered.SlotConnect(this,&GtViewportMenu::OnLightingEditor_Clicked);		
				//m_ptrLightingEditorAction->setStatusTip(tr("(Edit Viewport Lighting)"));
			}

			//VIEWPORT PROPERTIES ACTION
			m_ptrViewportPropEditorAction = new GtAction();
			if(m_ptrViewportPropEditorAction)
			{
				m_ptrViewportPropEditorAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Viewport Properties";
				m_ptrViewportPropEditorAction->Set_strText(strText);
				m_ptrViewportPropEditorAction->Triggered.SlotConnect(this,&GtViewportMenu::OnViewportPropEditor_Clicked);		
				//m_ptrViewportPropEditorAction->setStatusTip(tr("(Edit Viewport Properties)"));
			}

			//DOCK AND UNDOCK ACTION
			m_ptrViewDockAction = new GtAction();
			if(m_ptrViewDockAction)
			{
				m_ptrViewDockAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "View DOCK";
				m_ptrViewDockAction->Set_strText(strText);
				m_ptrViewDockAction->Triggered.SlotConnect(this,&GtViewportMenu::OnViewDock_Clicked);		
				//m_ptrViewDockAction->setStatusTip(tr("(Docks the Viewport to its owner)"));
			}

			m_ptrViewUnDockAction = new GtAction();
			if(m_ptrViewUnDockAction)
			{
				m_ptrViewUnDockAction->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "View UNDOCK";
				m_ptrViewUnDockAction->Set_strText(strText);
				m_ptrViewUnDockAction->Triggered.SlotConnect(this,&GtViewportMenu::OnViewUnDock_Clicked);		
				//m_ptrViewUnDockAction->setStatusTip(tr("(UN-Docks the Viewport to a floating window)"));
			}

		};

		//!Create the Main Menu or modify the main menu programmatically
		void GtViewportMenu::CreateMenus(void)
		{
			std::string strText = "View";
			this->Set_strText(strText);
			this->Set_intWidth(150);
			this->Set_objBackBrush(GtBrush(GtColor(160,160,160)));

			//viewpoint sub menu
			m_ptrSetViewMenu = new GtMenu(this);
			if(m_ptrSetViewMenu)
			{
				m_ptrSetViewMenu->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "MySubMenu";
				m_ptrSetViewMenu->Set_strText(strText);
				m_ptrSetViewMenu->Set_intWidth(150);
				this->AddMenu(m_ptrSetViewMenu);
			}
			//add the actions to the sub menu
			m_ptrTopViewAction->Set_ptrParent(m_ptrSetViewMenu);
			m_ptrBottomViewAction->Set_ptrParent(m_ptrSetViewMenu);
			m_ptrLeftViewAction->Set_ptrParent(m_ptrSetViewMenu);
			m_ptrRightViewAction->Set_ptrParent(m_ptrSetViewMenu);
			m_ptrFrontViewAction->Set_ptrParent(m_ptrSetViewMenu);
			m_ptrBackViewAction->Set_ptrParent(m_ptrSetViewMenu);

			m_ptrSetViewMenu->AddAction(m_ptrTopViewAction);
			m_ptrSetViewMenu->AddAction(m_ptrBottomViewAction);
			m_ptrSetViewMenu->AddAction(m_ptrLeftViewAction);
			m_ptrSetViewMenu->AddAction(m_ptrRightViewAction);
			m_ptrSetViewMenu->AddAction(m_ptrFrontViewAction);
			m_ptrSetViewMenu->AddAction(m_ptrBackViewAction);

			//axis lock sub menu
			m_ptrAxisLockMenu = new GtMenu(this);
			if(m_ptrAxisLockMenu)
			{
				m_ptrAxisLockMenu->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Axis Lock";
				m_ptrAxisLockMenu->Set_strText(strText);
				m_ptrAxisLockMenu->Set_intWidth(150);
				this->AddMenu(m_ptrAxisLockMenu);
			}
			m_ptrToggleLockXAxisAction->Set_ptrParent(m_ptrAxisLockMenu);
			m_ptrToggleLockYAxisAction->Set_ptrParent(m_ptrAxisLockMenu);
			m_ptrToggleLockZAxisAction->Set_ptrParent(m_ptrAxisLockMenu);

			m_ptrAxisLockMenu->AddAction(m_ptrToggleLockXAxisAction);
			m_ptrAxisLockMenu->AddAction(m_ptrToggleLockYAxisAction);
			m_ptrAxisLockMenu->AddAction(m_ptrToggleLockZAxisAction);


			//projection sub menu
			m_ptrProjectionModeMenu = new GtMenu(this);
			if(m_ptrProjectionModeMenu)
			{
				m_ptrProjectionModeMenu->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Projection Mode";
				m_ptrProjectionModeMenu->Set_strText(strText);
				m_ptrProjectionModeMenu->Set_intWidth(150);
				this->AddMenu(m_ptrProjectionModeMenu);
			}

			m_ptrPerspectiveAction->Set_ptrParent(m_ptrProjectionModeMenu);
			m_ptrOrthographicAction->Set_ptrParent(m_ptrProjectionModeMenu);

			m_ptrProjectionModeMenu->AddAction(m_ptrPerspectiveAction);
			m_ptrProjectionModeMenu->AddAction(m_ptrOrthographicAction);

			//render mode sub menu
			m_ptrRenderModeMenu = new GtMenu(this);
			if(m_ptrRenderModeMenu)
			{
				m_ptrRenderModeMenu->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
				std::string strText = "Render Mode";
				m_ptrRenderModeMenu->Set_strText(strText);
				m_ptrRenderModeMenu->Set_intWidth(150);
				this->AddMenu(m_ptrRenderModeMenu);
			}

			m_ptrCurvesOnlyAction->Set_ptrParent(m_ptrRenderModeMenu);
			m_ptrCurvesWithMeshAction->Set_ptrParent(m_ptrRenderModeMenu);
			m_ptrShadedAction->Set_ptrParent(m_ptrRenderModeMenu);
			m_ptrShadedWithMeshAction->Set_ptrParent(m_ptrRenderModeMenu);
			m_ptrShadedWithCurvesAction->Set_ptrParent(m_ptrRenderModeMenu);
			m_ptrShadedBoundaryAction->Set_ptrParent(m_ptrRenderModeMenu);
			m_ptrShadeSelectedAction->Set_ptrParent(m_ptrRenderModeMenu);

			m_ptrRenderModeMenu->AddAction(m_ptrCurvesOnlyAction);
			m_ptrRenderModeMenu->AddAction(m_ptrCurvesWithMeshAction);
			m_ptrRenderModeMenu->AddAction(m_ptrShadedAction);
			m_ptrRenderModeMenu->AddAction(m_ptrShadedWithMeshAction);
			m_ptrRenderModeMenu->AddAction(m_ptrShadedWithCurvesAction);
			m_ptrRenderModeMenu->AddAction(m_ptrShadedBoundaryAction);
			m_ptrRenderModeMenu->AddAction(m_ptrShadeSelectedAction);

			this->AddSeparator();
			m_ptrLightingEditorAction->Set_ptrParent(this);
			this->AddAction(m_ptrLightingEditorAction);

			m_ptrViewportPropEditorAction->Set_ptrParent(this);
			this->AddAction(m_ptrViewportPropEditorAction);

			this->AddSeparator();
			m_ptrViewDockAction->Set_ptrParent(this);
			this->AddAction(m_ptrViewDockAction);

			m_ptrViewUnDockAction->Set_ptrParent(this);
			this->AddAction(m_ptrViewUnDockAction);
		};

		//!Sets the pointer to the viewport parent object
		int GtViewportMenu::Set_ptrViewportParent(GtViewport * ptrParent)
		{
			if(ptrParent)
			{
				this->m_ptrViewportParent = ptrParent;
				//get dock state
				bool blnDocked = m_ptrViewportParent->Get_blnDocked();
				if(blnDocked)
				{
					this->m_ptrViewDockAction->Set_blnEnabled(false);
					this->m_ptrViewUnDockAction->Set_blnEnabled(true);
				}else{
					this->m_ptrViewDockAction->Set_blnEnabled(true);
					this->m_ptrViewUnDockAction->Set_blnEnabled(false);
				};

				return 1;
			};
			return 0;
		};
		//!Gets the pointer of the viewport parent object
		GtViewport * GtViewportMenu::Get_ptrViewportParent(void)
		{
			return m_ptrViewportParent;
		};
		//!Clears the pointer to the viewport parent object
		int GtViewportMenu::ClearViewportParentPtr(void)
		{
			this->m_ptrViewportParent = NULL;
			return 1;
		};

		//Event handlers for the various actions and editors
		//!Sets the viewport to Top View (Looking At XYPlane in the Z Negative Direction)
		void GtViewportMenu::OnSetTopView_XYPlane_ZNeg(void)
		{
			GtViewpoint objNewViewpoint;
			if(this->m_ptrViewportParent)
			{
				objNewViewpoint.m_objViewLocation.Set(0.0,0.0,10.0);
				objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
				objNewViewpoint.m_objRotation.Zero();
				objNewViewpoint.m_objUpDir.Set(0.0,1.0,0.0);
				this->m_ptrViewportParent->Set_objCurrViewpoint(objNewViewpoint);
				this->m_ptrViewportParent->ZoomExtents();
				this->PostPaint();
			};
		};
		//!Sets the viewport to Top View (Looking At XYPlane in the Z Positive Direction)
		void GtViewportMenu::OnSetBottomView_XYPlane_ZPos(void)
		{
			GtViewpoint objNewViewpoint;
			if(this->m_ptrViewportParent)
			{
				objNewViewpoint.m_objViewLocation.Set(0.0,0.0,-10.0);
				objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
				objNewViewpoint.m_objRotation.Zero();
				objNewViewpoint.m_objUpDir.Set(0.0,1.0,0.0);
				this->m_ptrViewportParent->Set_objCurrViewpoint(objNewViewpoint);
				this->m_ptrViewportParent->ZoomExtents();
				this->PostPaint();
			};
		};
		//!Sets the viewport to Left View (Looking At XZPlane in the Y Negative Direction)
		void GtViewportMenu::OnSetLeftView_XZPlane_YNeg(void)
		{
			GtViewpoint objNewViewpoint;
			if(this->m_ptrViewportParent)
			{
				objNewViewpoint.m_objViewLocation.Set(0.0,10.0,0.0);
				objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
				objNewViewpoint.m_objRotation.Zero();
				objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
				this->m_ptrViewportParent->Set_objCurrViewpoint(objNewViewpoint);
				this->m_ptrViewportParent->ZoomExtents();
				this->PostPaint();
			}
		};
		//!Sets the viewport to Right View (Looking At XZPlane in the Y Positive Direction)
		void GtViewportMenu::OnSetRightView_XZPlane_YPos(void)
		{
			GtViewpoint objNewViewpoint;
			if(this->m_ptrViewportParent)
			{
				objNewViewpoint.m_objViewLocation.Set(0.0,-10.0,0.0);
				objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
				objNewViewpoint.m_objRotation.Zero();
				objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
				this->m_ptrViewportParent->Set_objCurrViewpoint(objNewViewpoint);
				this->m_ptrViewportParent->ZoomExtents();
				this->PostPaint();
			}
		};
		//!Sets the viewport to Front View (Looking At YZPlane in the X Negative Direction)
		void GtViewportMenu::OnSetFrontView_YZPlane_XNeg(void)
		{
			GtViewpoint objNewViewpoint;
			if(this->m_ptrViewportParent)
			{
				objNewViewpoint.m_objViewLocation.Set(10.0,0.0,0.0);
				objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
				objNewViewpoint.m_objRotation.Zero();
				objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
				this->m_ptrViewportParent->Set_objCurrViewpoint(objNewViewpoint);
				this->m_ptrViewportParent->ZoomExtents();
				this->PostPaint();
			}
		};
		//!Sets the viewport to Back View (Looking At YZPlane in the X Positive Direction)
		void GtViewportMenu::OnSetBackView_YZPlane_XPos(void)
		{
			GtViewpoint objNewViewpoint;
			if(this->m_ptrViewportParent)
			{
				objNewViewpoint.m_objViewLocation.Set(-10.0,0.0,0.0);
				objNewViewpoint.m_objRotationCentroid.Set(0.0,0.0,0.0);
				objNewViewpoint.m_objRotation.Zero();
				objNewViewpoint.m_objUpDir.Set(0.0,0.0,1.0);
				this->m_ptrViewportParent->Set_objCurrViewpoint(objNewViewpoint);
				this->m_ptrViewportParent->ZoomExtents();
				this->PostPaint();
			}
		};

		//!Toggle the locking of the X Axis
		void GtViewportMenu::OnToggleLock_XAxis(void)
		{
			bool blnTemp;
			std::string strTemp;
			if(this->m_ptrViewportParent)
			{
				blnTemp = this->m_ptrViewportParent->Get_blnLockXAxis();
				if(blnTemp)
				{			
					strTemp = "Lock X-Axis";
					m_ptrToggleLockXAxisAction->Set_strText(strTemp);
					m_ptrToggleLockXAxisAction->Set_blnChecked(false);
					this->m_ptrViewportParent->Set_blnLockXAxis(false);
				}else{
					strTemp = "UnLock X-Axis";
					m_ptrToggleLockXAxisAction->Set_strText(strTemp);
					m_ptrToggleLockXAxisAction->Set_blnChecked(true);
					this->m_ptrViewportParent->Set_blnLockXAxis(true);
				};
				return;
			};
		};
		//!Toggle the locking of the Y Axis
		void GtViewportMenu::OnToggleLock_YAxis(void)
		{
			bool blnTemp;
			std::string strTemp;
			if(this->m_ptrViewportParent)
			{
				blnTemp = this->m_ptrViewportParent->Get_blnLockYAxis();
				if(blnTemp)
				{
					strTemp = "Lock Y-Axis";
					m_ptrToggleLockYAxisAction->Set_strText(strTemp);
					m_ptrToggleLockYAxisAction->Set_blnChecked(false);
					this->m_ptrViewportParent->Set_blnLockYAxis(false);
				}else{
					strTemp = "UnLock Y-Axis";
					m_ptrToggleLockYAxisAction->Set_strText(strTemp);
					m_ptrToggleLockYAxisAction->Set_blnChecked(true);
					this->m_ptrViewportParent->Set_blnLockYAxis(true);
				};
				return;
			};
		};
		//!Toggle the locking of the Z Axis
		void GtViewportMenu::OnToggleLock_ZAxis(void)
		{
			bool blnTemp;
			std::string strTemp;
			if(this->m_ptrViewportParent)
			{
				blnTemp = this->m_ptrViewportParent->Get_blnLockZAxis();
				if(blnTemp)
				{			
					strTemp = "Lock Z-Axis";
					m_ptrToggleLockZAxisAction->Set_strText(strTemp);
					m_ptrToggleLockZAxisAction->Set_blnChecked(false);
					this->m_ptrViewportParent->Set_blnLockZAxis(false);
				}else{
					strTemp = "UnLock Z-Axis";
					m_ptrToggleLockZAxisAction->Set_strText(strTemp);
					m_ptrToggleLockZAxisAction->Set_blnChecked(true);
					this->m_ptrViewportParent->Set_blnLockZAxis(true);
				};
				return;
			};
		};

		//!Set the projection mode to perspective mode
		void GtViewportMenu::OnSetProjectionMode_Perspective(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearProjectionModeChecks();
				this->m_ptrPerspectiveAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objProjectionMode(Perspective);
			};
			return;
		};
		//!Set the projection mode to orthographic mode
		void GtViewportMenu::OnSetProjectionMode_Orthographic(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearProjectionModeChecks();
				this->m_ptrOrthographicAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objProjectionMode(Orthographic);
			};
			return;
		};


		//!Set the Render Mode of the Viewport to CurvesOnly
		void GtViewportMenu::OnSetRenderMode_CurvesOnly(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearRenderModeChecks();
				this->m_ptrCurvesOnlyAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objRenderMode(CurvesOnly);
			};
			return;
		};
		//!Set the Render Mode of the Viewport to CurvesOnly
		void GtViewportMenu::OnSetRenderMode_CurvesWithMesh(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearRenderModeChecks();
				this->m_ptrCurvesWithMeshAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objRenderMode(CurvesWithMesh);
			};
			return;
		};
		//!Set the Render Mode of the Viewport to CurvesOnly
		void GtViewportMenu::OnSetRenderMode_Shaded(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearRenderModeChecks();
				this->m_ptrShadedAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objRenderMode(Shaded);
			};
			return;
		};
		//!Set the Render Mode of the Viewport to CurvesOnly
		void GtViewportMenu::OnSetRenderMode_ShadedWithMesh(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearRenderModeChecks();
				this->m_ptrShadedWithMeshAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objRenderMode(ShadedWithMesh);
			};
			return;
		};
		//!Set the Render Mode of the Viewport to CurvesOnly
		void GtViewportMenu::OnSetRenderMode_ShadedWithCurves(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearRenderModeChecks();
				this->m_ptrShadedWithCurvesAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objRenderMode(ShadedWithCurves);
			};
			return;
		};
		//!Set the Render Mode of the Viewport to CurvesOnly
		void GtViewportMenu::OnSetRenderMode_ShadedBoundary(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearRenderModeChecks();
				this->m_ptrShadedBoundaryAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objRenderMode(ShadedBoundary);
			};
			return;
		};
		//!Set the Render Mode of the Viewport to CurvesOnly
		void GtViewportMenu::OnSetRenderMode_ShadeSelected(void)
		{
			if(this->m_ptrViewportParent)
			{
				this->ClearRenderModeChecks();
				this->m_ptrShadeSelectedAction->Set_blnChecked(true);
				this->m_ptrViewportParent->Set_objRenderMode(ShadeSelected);
			};
			return;
		};

		//!Open the Viewport Lighting Editor
		void GtViewportMenu::OnLightingEditor_Clicked(void)
		{
			if(this->m_ptrViewportParent)
			{
				//this->m_ptrViewportParent->Set_objRenderMode(CurvesOnly);
			};
			return;
		};
		//!Open the Viewport Property Editor
		void GtViewportMenu::OnViewportPropEditor_Clicked(void)
		{
			if(this->m_ptrViewportParent)
			{
				/*GtViewportPropDialog objPropDialog;
				objPropDialog.SetViewportPtr(m_ptrViewportParent);
				objPropDialog.exec();*/
			};
			return;
		};


		void GtViewportMenu::OnViewDock_Clicked(void)
		{
			if(this->m_ptrViewportParent)
			{
				m_ptrViewportParent->DockViewport();
				this->m_ptrViewDockAction->Set_blnEnabled(false);
				this->m_ptrViewUnDockAction->Set_blnEnabled(true);
			};
		};

		void GtViewportMenu::OnViewUnDock_Clicked(void)
		{
			if(this->m_ptrViewportParent)
			{
				m_ptrViewportParent->UnDockViewport();
				this->m_ptrViewDockAction->Set_blnEnabled(true);
				this->m_ptrViewUnDockAction->Set_blnEnabled(false);
			};
		};


		void GtViewportMenu::ClearRenderModeChecks(void)
		{
			this->m_ptrCurvesOnlyAction->Set_blnChecked(false);
			this->m_ptrCurvesWithMeshAction->Set_blnChecked(false);
			this->m_ptrShadedAction->Set_blnChecked(false);
			this->m_ptrShadedWithMeshAction->Set_blnChecked(false);
			this->m_ptrShadedWithCurvesAction->Set_blnChecked(false);
			this->m_ptrShadedBoundaryAction->Set_blnChecked(false);
			this->m_ptrShadeSelectedAction->Set_blnChecked(false);
		};

		void GtViewportMenu::ClearProjectionModeChecks(void)
		{
			this->m_ptrPerspectiveAction->Set_blnChecked(false);
			this->m_ptrOrthographicAction->Set_blnChecked(false);
		};

	};//end namespace GtOpenGL
};//end namespace GT