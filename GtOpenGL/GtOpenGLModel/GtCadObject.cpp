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

#include ".\GtCadObject.h"
#include ".\GtCadLayer.h"

namespace GT
{
	namespace GtOpenGL
	{

		GtCadObject::GtCadObject(GtObject* ptrParent)
			: GtObject(ptrParent)
		{

			//set default flag settings
			this->m_blnLocked = false;
			this->m_blnRenderOverride = false;
			this->m_blnSelected = false;
			this->m_blnShowControlNet = false;
			this->m_blnShowCurves = true;
			this->m_blnShowPoints = false;
			this->m_blnShowSurface = true;
			this->m_blnVisible = true;
			this->m_blnBoxUpdate = true;
		}

		GtCadObject::~GtCadObject()
		{

		}

		//!Return the bounding box of the item 
		GtAABox GtCadObject::GetBoundingBox(void)
		{
			GtAABox objRetAABB;
			objRetAABB.Zero();
			return objRetAABB;
		};

		//!Return the bounding box of the item 
		GtAABox GtCadObject::GetSelectionBox(void)
		{
			GtAABox objRetAABB;
			objRetAABB.Zero();
			return objRetAABB;
		};

		void GtCadObject::SetGeomModified(void)
		{
			this->m_blnGeomModified = true;
		};

		//Transformation Factors
		void GtCadObject::Move(GtPoint3DF objDist){};
		void GtCadObject::Scale(GtPoint3DF objFactors){};
		void GtCadObject::Transform(float ptrMatrix[16]){};

		void GtCadObject::RenderItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode)
		{
			//THIS FUNCTION CAN BE OVERRIDDEN IF DESIRED BUT THIS IS THE DEFAULT BEHAVIOR
			switch(enumRenderMode)
			{
			case CurvesOnly:
				{
					this->DrawCurves();
					break;
				};
			case CurvesWithMesh:
				{
					this->DrawCurves();
					this->DrawMesh();
					break;
				};
			case Shaded:
				{
					this->DrawSurfaces();
					this->DrawPoints();
					this->DrawControlNet();
					break;
				};
			case ShadedWithMesh:
				{
					this->DrawSurfaces();
					this->DrawMesh();
					this->DrawPoints();
					break;
				};
			case ShadedWithCurves:
				{
					this->DrawSurfaces();
					this->DrawCurves();
					this->DrawPoints();
					this->DrawControlNet();
					break;
				};
			case ShadedBoundary:
				{
					this->DrawSurfaces();
					this->DrawCurves();
					break;
				};
			case ShadeSelected:
				{
					if(this->m_blnSelected)
					{
						this->DrawSurfaces();
					}
					this->DrawCurves();
					this->DrawPoints();
					this->DrawControlNet();
					break;
				};
			default:
				{
					//default behavior is shaded with curves
					this->DrawSurfaces();
					this->DrawCurves();
					this->DrawPoints();
					this->DrawControlNet();
					break;
				};
			};//end switch on statement
			return;
		};

		void GtCadObject::RenderOverlay(const GtViewpoint & ptrCurrViewPoint)
		{
			return;
		};

		void GtCadObject::DrawSurfaces(void)
		{
			//THIS FUNCTION MUST BE OVERRIDDEN FOR EVERY MODEL OBJECT THAT IS USED
			return;
		};

		void GtCadObject::DrawMesh(void)
		{
			//THIS FUNCTION MUST BE OVERRIDDEN FOR EVERY MODEL OBJECT THAT IS USED
			return;
		};

		void GtCadObject::DrawCurves(void)
		{
			//THIS FUNCTION MUST BE OVERRIDDEN FOR EVERY MODEL OBJECT THAT IS USED
			return;
		};

		void GtCadObject::DrawPoints(void)
		{
			//THIS FUNCTION MUST BE OVERRIDDEN FOR EVERY MODEL OBJECT THAT IS USED
			return;
		};

		void GtCadObject::DrawControlNet(void)
		{
			//THIS FUNCTION MUST BE OVERRIDDEN FOR EVERY MODEL OBJECT THAT IS USED
			return;
		};

	};//end namespace GtOpenGL

};//end namespace GT