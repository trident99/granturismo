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

#include  ".\GM_Polyline.h"

namespace GT
{
	namespace GtOpenGL
	{

		GM_Polyline::GM_Polyline(GtObject* ptrParent)
			: GtCadObject(ptrParent)
		{
			//HtlBase Initialization
			m_strType = "GM_Polyline";
			//GM_Polyline Initialization////////////////////
			m_objNullPoint.Zero();
			return;
		};


		GM_Polyline::GM_Polyline(GM_Polyline& rhs)
			: GtCadObject(rhs)
		{
			//HtlBase Initialization
			m_strType = "GM_Polyline";
			//GM_Polyline Initialization////////////////////
			size_t i, intNumPts;
			m_arrObjPoints.clear();
			intNumPts = rhs.Size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.push_back(rhs.m_arrObjPoints.at(i));
			};
			return;
		};

		GM_Polyline & GM_Polyline::operator = (GM_Polyline & rhs)
		{
			if(this == &rhs)
				return *this;

			HtlBase::operator=(rhs);

			//ORSSerializable Initialization
			m_strType = "GM_Polyline";
			//GM_Polyline Initialization////////////////////
			size_t i, intNumPts;
			m_arrObjPoints.clear();
			intNumPts = rhs.Size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.push_back(rhs.m_arrObjPoints.at(i));
			};
			return *this;	
		};

		GM_Polyline::~GM_Polyline(void)
		{
			return;
		};


		bool GM_Polyline::operator == (GM_Polyline & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrObjPoints.size();
			intRHSNumPoints = rhs.m_arrObjPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return false;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrObjPoints.at(i) != rhs.m_arrObjPoints.at(i)){return false;};
			}
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GM_Polyline::operator != (GM_Polyline & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrObjPoints.size();
			intRHSNumPoints = rhs.m_arrObjPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return true;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrObjPoints.at(i) != rhs.m_arrObjPoints.at(i)){return true;};
			}
			//made it this far without finding a difference, must be the same
			return false;
		};

		void GM_Polyline::Clear(void)
		{
			m_arrObjPoints.clear();
		};
		size_t GM_Polyline::Size(void)
		{
			return m_arrObjPoints.size();
		};
		GtPoint3DF & GM_Polyline::At(size_t intIndex)
		{
			size_t intNumPoints;
			intNumPoints = m_arrObjPoints.size();
			if((intIndex >= 0) && (intIndex < intNumPoints))
			{
				return m_arrObjPoints.at(intIndex);
			}else{
				return m_objNullPoint;
			};
		};
		void GM_Polyline::PushBack(GtPoint3DF & objNewPoint)
		{
			m_arrObjPoints.push_back(objNewPoint);
			return;
		};
		void GM_Polyline::Round(int intNumDecimals)
		{
			size_t i, intNumPoints;
			intNumPoints = m_arrObjPoints.size();
			if(intNumPoints <= 0){return;};
			for(i = 0; i < intNumPoints; i++)
			{
				m_arrObjPoints.at(i).Round(intNumDecimals);
			};
		};


		//!Return the bounding box of the item 
		GtAABox GM_Polyline::GetBoundingBox(void)
		{
			if(!this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				return this->m_objBoundingBox;
			};


			int i, intUboundI;
			intUboundI = m_arrObjPoints.size();
			if(intUboundI > 0)
			{
				m_objBoundingBox.m_dblXMin = m_arrObjPoints.at(0).x;
				m_objBoundingBox.m_dblXMax = m_arrObjPoints.at(0).x;
				m_objBoundingBox.m_dblYMin = m_arrObjPoints.at(0).y;
				m_objBoundingBox.m_dblYMax = m_arrObjPoints.at(0).y;
				m_objBoundingBox.m_dblZMin = m_arrObjPoints.at(0).z;
				m_objBoundingBox.m_dblZMax = m_arrObjPoints.at(0).z;
			}else{
				return m_objBoundingBox;
			};


			for(i = 0; i < intUboundI; i++)
			{
				if(m_arrObjPoints.at(i).x < m_objBoundingBox.m_dblXMin)
				{
					m_objBoundingBox.m_dblXMin = m_arrObjPoints.at(i).x;
				};
				if(m_arrObjPoints.at(i).x > m_objBoundingBox.m_dblXMax)
				{
					m_objBoundingBox.m_dblXMax = m_arrObjPoints.at(i).x;
				};

				if(m_arrObjPoints.at(i).y < m_objBoundingBox.m_dblYMin)
				{
					m_objBoundingBox.m_dblYMin = m_arrObjPoints.at(i).y;
				};
				if(m_arrObjPoints.at(i).y > m_objBoundingBox.m_dblYMax)
				{
					m_objBoundingBox.m_dblYMax = m_arrObjPoints.at(i).y;
				};

				if(m_arrObjPoints.at(i).z < m_objBoundingBox.m_dblZMin)
				{
					m_objBoundingBox.m_dblZMin = m_arrObjPoints.at(i).z;
				};
				if(m_arrObjPoints.at(i).z > m_objBoundingBox.m_dblZMax)
				{
					m_objBoundingBox.m_dblZMax = m_arrObjPoints.at(i).z;
				};
			};

			return m_objBoundingBox;
		};

		//!Return the bounding box of the item 
		GtAABox GM_Polyline::GetSelectionBox(void)
		{

			if(this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				this->GetBoundingBox();
			};
			//otherwise return the already calculated box

			return this->m_objBoundingBox;
		};




		void GM_Polyline::RenderModelItem( const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode)
		{
			//THIS FUNCTION CAN BE OVERRIDDEN IF DESIRED BUT THIS IS THE DEFAULT BEHAVIOR

			this->DrawCurves();
			this->DrawPoints();
			return;
		};

		void GM_Polyline::DrawCurves(void)
		{
			int i, intUboundI;

			intUboundI = this->m_arrObjPoints.size();
			if(intUboundI <= 0)
			{
				return;
			};
			//Make sure lighting is turned on
			glDisable(GL_LIGHTING);
			glMatrixMode(GL_MODELVIEW);
			//PUSH MODEL VIEW MATRIX
			glPushMatrix();
			//DRAW THE OBJECTS
			if(this->m_blnSelected)
			{	
				//Set colors to selection colors		
				//Gold 255-215-0 ffd700   
				//Yellow 255-255-0 ffff00  
				float arrSngDiffColor[3] = {1.0f, 0.843137f,0.0f};//gold
				float arrSngSpecColor[4] = {this->m_objCurveMaterial.m_objSpecularColor.UnitRed(),
					this->m_objCurveMaterial.m_objSpecularColor.UnitGreen(),
					this->m_objCurveMaterial.m_objSpecularColor.UnitBlue(),
					this->m_objCurveMaterial.m_objSpecularColor.UnitAlpha()};

				// set specular and shiniess using glMaterial (gold-yellow)
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->m_objSurfMaterial.m_sngShininess); // range 0 ~ 128
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arrSngSpecColor);

				// set ambient and diffuse color using glColorMaterial (gold-yellow)
				glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
				glColor3fv(arrSngDiffColor);

			}else{
				//Set colors to object colors		
				float arrSngDiffColor[4] =  {this->m_objCurveMaterial.m_objDiffuseColor.UnitRed(),
					this->m_objCurveMaterial.m_objDiffuseColor.UnitGreen(),
					this->m_objCurveMaterial.m_objDiffuseColor.UnitBlue()};
				float arrSngSpecColor[4] = {this->m_objCurveMaterial.m_objSpecularColor.UnitRed(),
					this->m_objCurveMaterial.m_objSpecularColor.UnitGreen(),
					this->m_objCurveMaterial.m_objSpecularColor.UnitBlue(),
					this->m_objCurveMaterial.m_objSpecularColor.UnitAlpha()};

				// set specular and shiniess using glMaterial (gold-yellow)
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->m_objSurfMaterial.m_sngShininess); // range 0 ~ 128
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arrSngSpecColor);

				// set ambient and diffuse color using glColorMaterial (gold-yellow)
				glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
				glColor3fv(arrSngDiffColor);
			}
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			//DRAW THE CURVES -->NORMALS OUT
			glLineWidth(2.0f);

			glBegin(GL_LINE_STRIP);
			for(i = 0; i < intUboundI; i++)
			{
				glVertex3f(float(m_arrObjPoints.at(i).x), float(m_arrObjPoints.at(i).y), float(m_arrObjPoints.at(i).z));
			}
			glEnd();
			//set line width back to default
			glLineWidth(1.0f);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_LIGHTING);

		};
		void GM_Polyline::DrawPoints(void)
		{

		};



	};//end namespace GtOpenGL
};//end namespace GT