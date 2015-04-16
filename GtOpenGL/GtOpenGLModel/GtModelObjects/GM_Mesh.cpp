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

#include  ".\GM_Mesh.h"

namespace GT
{
	namespace GtOpenGL
	{

		GM_Mesh::GM_Mesh(GtObject* ptrParent)
			: GtCadObject(ptrParent)
		{
			//HtlBase Initialization
			m_strType = "GM_Mesh";
			//GM_Mesh Initialization////////////////////
			return;
		};


		GM_Mesh::GM_Mesh(GM_Mesh& rhs)
			: GtCadObject(rhs)
		{
			//HtlBase Initialization
			m_strType = "GM_Mesh";
			//GM_Mesh Initialization////////////////////
			size_t i, intNumPts, intNumFacets;
			m_arrPoints.clear();
			intNumPts = rhs.SizePoints();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrPoints.push_back(rhs.m_arrPoints.at(i));
			};
			intNumFacets = rhs.SizeFacets();
			for(i = 0; i < intNumFacets;i++)
			{
				this->m_arrFacets.push_back(rhs.m_arrFacets.at(i));
			};

			return;
		};

		GM_Mesh & GM_Mesh::operator = (GM_Mesh & rhs)
		{
			if(this != &rhs)
			{
				HtlBase::operator=(rhs);

				//ORSSerializable Initialization
				m_strType = "GM_Mesh";
				//GM_Mesh Initialization////////////////////
				size_t i, intNumPts, intNumFacets;
				m_arrPoints.clear();
				intNumPts = rhs.SizePoints();
				for(i = 0; i < intNumPts; i++)
				{
					this->m_arrPoints.push_back(rhs.m_arrPoints.at(i));
				};
				intNumFacets = rhs.SizeFacets();
				for(i = 0; i < intNumFacets;i++)
				{
					this->m_arrFacets.push_back(rhs.m_arrFacets.at(i));
				};
			};
			return *this;	
		};

		GM_Mesh::~GM_Mesh(void)
		{
			return;
		};


		bool GM_Mesh::operator == (GM_Mesh & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrPoints.size();
			intRHSNumPoints = rhs.m_arrPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return false;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrPoints.at(i) != rhs.m_arrPoints.at(i)){return false;};
			}
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GM_Mesh::operator != (GM_Mesh & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrPoints.size();
			intRHSNumPoints = rhs.m_arrPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return true;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrPoints.at(i) != rhs.m_arrPoints.at(i)){return true;};
			}
			//made it this far without finding a difference, must be the same
			return false;
		};

		void GM_Mesh::Clear(void)
		{
			m_arrPoints.clear();
		};
		size_t GM_Mesh::SizePoints(void)
		{
			return m_arrPoints.size();
		};
		size_t GM_Mesh::SizeFacets(void)
		{
			return m_arrFacets.size();
		};


		//!Return the bounding box of the item 
		GtAABox GM_Mesh::GetBoundingBox(void)
		{
			if(!this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				return this->m_objBoundingBox;
			};


			int i, intUboundI;
			intUboundI = m_arrPoints.size();
			if(intUboundI > 0)
			{
				m_objBoundingBox.m_dblXMin = m_arrPoints.at(0).x;
				m_objBoundingBox.m_dblXMax = m_arrPoints.at(0).x;
				m_objBoundingBox.m_dblYMin = m_arrPoints.at(0).y;
				m_objBoundingBox.m_dblYMax = m_arrPoints.at(0).y;
				m_objBoundingBox.m_dblZMin = m_arrPoints.at(0).z;
				m_objBoundingBox.m_dblZMax = m_arrPoints.at(0).z;
			}else{
				return m_objBoundingBox;
			};


			for(i = 0; i < intUboundI; i++)
			{
				if(m_arrPoints.at(i).x < m_objBoundingBox.m_dblXMin)
				{
					m_objBoundingBox.m_dblXMin = m_arrPoints.at(i).x;
				};
				if(m_arrPoints.at(i).x > m_objBoundingBox.m_dblXMax)
				{
					m_objBoundingBox.m_dblXMax = m_arrPoints.at(i).x;
				};

				if(m_arrPoints.at(i).y < m_objBoundingBox.m_dblYMin)
				{
					m_objBoundingBox.m_dblYMin = m_arrPoints.at(i).y;
				};
				if(m_arrPoints.at(i).y > m_objBoundingBox.m_dblYMax)
				{
					m_objBoundingBox.m_dblYMax = m_arrPoints.at(i).y;
				};

				if(m_arrPoints.at(i).z < m_objBoundingBox.m_dblZMin)
				{
					m_objBoundingBox.m_dblZMin = m_arrPoints.at(i).z;
				};
				if(m_arrPoints.at(i).z > m_objBoundingBox.m_dblZMax)
				{
					m_objBoundingBox.m_dblZMax = m_arrPoints.at(i).z;
				};
			};

			return m_objBoundingBox;
		};

		//!Return the bounding box of the item 
		GtAABox GM_Mesh::GetSelectionBox(void)
		{

			if(this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				this->GetBoundingBox();
			};
			//otherwise return the already calculated box

			return this->m_objBoundingBox;
		};




		void GM_Mesh::RenderModelItem( const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode)
		{
			//THIS FUNCTION CAN BE OVERRIDDEN IF DESIRED BUT THIS IS THE DEFAULT BEHAVIOR

			this->DrawCurves();
			this->DrawPoints();
			return;
		};


		//Private drawing routines for different modes of drawing
		void GM_Mesh::DrawSurfaces(void)
		{		
			//Make sure lighting is turned on
			glEnable(GL_LIGHTING);
			glMatrixMode(GL_MODELVIEW);
			//PUSH MODEL VIEW MATRIX
			glPushMatrix();
			//DRAW THE OBJECTS
			if(this->m_blnSelected)
			{	
				//Set colors to selection colors		
				//Gold 255-215-0 ffd700   
				//Yellow 255-255-0 ffff00  
				float arrSngDiffColor[3] = {1.0f, 1.0f,0.0f};
				float arrSngSpecColor[4] = {this->m_objSurfMaterial.m_objSpecularColor.UnitRed(),
					this->m_objSurfMaterial.m_objSpecularColor.UnitGreen(),
					this->m_objSurfMaterial.m_objSpecularColor.UnitBlue(),
					this->m_objSurfMaterial.m_objSpecularColor.UnitAlpha()};

				// set specular and shiniess using glMaterial (gold-yellow)
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->m_objSurfMaterial.m_sngShininess); // range 0 ~ 128
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arrSngSpecColor);

				// set ambient and diffuse color using glColorMaterial (gold-yellow)
				glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
				glColor4fv(arrSngDiffColor);

			}else{
				//Set colors to object colors		
				float arrSngDiffColor[4] =  {this->m_objSurfMaterial.m_objDiffuseColor.UnitRed(),
					this->m_objSurfMaterial.m_objDiffuseColor.UnitGreen(),
					this->m_objSurfMaterial.m_objDiffuseColor.UnitBlue(),
					this->m_objSurfMaterial.m_objDiffuseColor.UnitAlpha()};
				float arrSngSpecColor[4] = {this->m_objSurfMaterial.m_objSpecularColor.UnitRed(),
					this->m_objSurfMaterial.m_objSpecularColor.UnitGreen(),
					this->m_objSurfMaterial.m_objSpecularColor.UnitBlue(),
					this->m_objSurfMaterial.m_objSpecularColor.UnitAlpha()};

				// set specular and shiniess using glMaterial (gold-yellow)
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->m_objSurfMaterial.m_sngShininess); // range 0 ~ 128
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, arrSngSpecColor);

				// set ambient and diffuse color using glColorMaterial (gold-yellow)
				glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
				glColor4fv(arrSngDiffColor);
			}

			size_t i, numFacets;
			numFacets = this->SizeFacets();
			
			glBegin(GL_QUADS);
			for(i = 0; i < numFacets; i++)
			{
				GtFacet curr = this->m_arrFacets.at(i);
				//calculate the facet normal
				GtPoint3DF vecA, vecB, vecNormal;

				vecA = GtMath::Diff3D(m_arrPoints.at(curr.m_P1),m_arrPoints.at(curr.m_P0));
				vecB = GtMath::Diff3D(m_arrPoints.at(curr.m_P2),m_arrPoints.at(curr.m_P0));
				vecNormal = GtMath::Cross3D(vecA,vecB);
				//XMIN PLANE //p0,p4,p7,p3
				glNormal3f(float(vecNormal.x),float(vecNormal.y),float(vecNormal.z));						//required for shading
				// Draw A Quad
				glVertex3f(float(m_arrPoints.at(curr.m_P0).x), float(m_arrPoints.at(curr.m_P0).y), float(m_arrPoints.at(curr.m_P0).z));
				glVertex3f(float(m_arrPoints.at(curr.m_P1).x), float(m_arrPoints.at(curr.m_P1).y), float(m_arrPoints.at(curr.m_P1).z));
				glVertex3f(float(m_arrPoints.at(curr.m_P2).x), float(m_arrPoints.at(curr.m_P2).y), float(m_arrPoints.at(curr.m_P2).z));
				glVertex3f(float(m_arrPoints.at(curr.m_P3).x), float(m_arrPoints.at(curr.m_P3).y), float(m_arrPoints.at(curr.m_P3).z));
				// Done Drawing The Quad
			}
			glEnd();

			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		};

		void GM_Mesh::DrawCurves(void)
		{
			size_t i, numPoints, numFacets;

			numPoints = this->m_arrPoints.size();
			numFacets =  this->m_arrFacets.size();

			if(numPoints <= 0)
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
			
			for(i = 0; i < numFacets; i++)
			{
				GtFacet curr = this->m_arrFacets.at(i);
					//required for shading
				glBegin(GL_LINE_STRIP);
				// Draw A Quad
				glVertex3f(float(m_arrPoints.at(curr.m_P0).x), float(m_arrPoints.at(curr.m_P0).y), float(m_arrPoints.at(curr.m_P0).z));
				glVertex3f(float(m_arrPoints.at(curr.m_P1).x), float(m_arrPoints.at(curr.m_P1).y), float(m_arrPoints.at(curr.m_P1).z));
				glVertex3f(float(m_arrPoints.at(curr.m_P2).x), float(m_arrPoints.at(curr.m_P2).y), float(m_arrPoints.at(curr.m_P2).z));
				glVertex3f(float(m_arrPoints.at(curr.m_P3).x), float(m_arrPoints.at(curr.m_P3).y), float(m_arrPoints.at(curr.m_P3).z));
				//end at start
				glVertex3f(float(m_arrPoints.at(curr.m_P0).x), float(m_arrPoints.at(curr.m_P0).y), float(m_arrPoints.at(curr.m_P0).z));
				glEnd();
				// Done Drawing The Quad
			}

			//set line width back to default
			glLineWidth(1.0f);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_LIGHTING);

		};
		void GM_Mesh::DrawPoints(void)
		{

		};



	};//end namespace GtOpenGL
};//end namespace GT