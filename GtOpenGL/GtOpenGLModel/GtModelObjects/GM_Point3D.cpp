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

#include  ".\GM_Point3D.h"

namespace GT
{
	namespace GtOpenGL
	{
		//GM_Point3D::GM_Point3D(void)
		//: HtlBase()
		//{

		//	//HtlBase Initialization
		//	m_strType = "GM_Point3D";
		//	//GM_Point3D Initialization////////////////////
		//	this->Zero();
		//	return;
		//};

		GM_Point3D::GM_Point3D(double dblX, double dblY,double dblZ)
			: GtCadObject()
		{
			//HtlBase Initialization
			m_strType = "GM_Point3D";
			this->x = dblX;
			this->y = dblY;
			this->z = dblZ;
		};

		GM_Point3D::GM_Point3D(const GM_Point3D& rhs) 
			: GtCadObject()
		{
			//HtlBase Initialization
			m_strType = "GM_Point3D";
			//GM_Point3D Initialization////////////////////
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return;
		};

		GM_Point3D & GM_Point3D::operator = (const GM_Point3D & rhs)
		{
			if(this != &rhs)
			{
				//HtlBase Initialization
				m_strType = "GM_Point3D";
				//GM_Point3D Initialization////////////////////
				this->x = rhs.x;
				this->y = rhs.y;
				this->z = rhs.z;
			}
			return *this;	
		};

		GM_Point3D::~GM_Point3D(void)
		{
			return;
		};

		bool GM_Point3D::operator == (const GM_Point3D & rhs)
		{
			if(x != rhs.x){return false;};
			if(y != rhs.y){return false;};
			if(z != rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};
		bool GM_Point3D::operator != (const GM_Point3D & rhs)
		{
			if(x != rhs.x){return true;};
			if(y != rhs.y){return true;};
			if(z != rhs.z){return true;};
			//made it this far without finding a difference, must be the same
			return false;	
		};

		bool GM_Point3D::operator < (const GM_Point3D & rhs)
		{
			if(x > rhs.x){return false;};
			if(y > rhs.y){return false;};
			if(z > rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GM_Point3D::operator > (const GM_Point3D & rhs)
		{
			if(x < rhs.x){return false;};
			if(y < rhs.y){return false;};
			if(z < rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};


		void GM_Point3D::Zero(void)
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		};

		void GM_Point3D::Round(int intNumDecimals)
		{
			x = gRound(x,intNumDecimals);
			y = gRound(y,intNumDecimals);
			z = gRound(z,intNumDecimals);
		};

		void GM_Point3D::Set(double dblX, double dblY, double dblZ)
		{
			x = dblX;
			y = dblY;
			z = dblZ;
		};
		void GM_Point3D::Normalize(void)
		{
			double length = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
			if(length <= 0.00001)
			{//safety check on divide by zero
				x = 0; y = 0; z = 0; return;
			};
			//otherwise safe to proceed
			x = x / length;
			y = y / length;
			z = z / length;
		};
		double GM_Point3D::operator[]( int i ) const
		{
			switch( i )
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			}
			return -1;
		};

		//!Return the bounding box of the item 
		GtAABox GM_Point3D::GetBoundingBox(void)
		{
			if(!this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				return this->m_objBoundingBox;
			};

			m_objBoundingBox.m_dblXMin = this->x - 0.05;
			m_objBoundingBox.m_dblXMax = this->x + 0.05;

			m_objBoundingBox.m_dblYMin = this->y - 0.05;
			m_objBoundingBox.m_dblYMax = this->y + 0.05;

			m_objBoundingBox.m_dblZMin = this->z - 0.05;
			m_objBoundingBox.m_dblZMax = this->z + 0.05;

			return m_objBoundingBox;
		};

		//!Return the bounding box of the item 
		GtAABox GM_Point3D::GetSelectionBox(void)
		{

			if(this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				this->GetBoundingBox();
			};
			//otherwise return the already calculated box

			return this->m_objBoundingBox;
		};

		//Private drawing routines for different modes of drawing
		void GM_Point3D::DrawSurfaces(void)
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

			//DRAW THE SURFACES -->NORMALS OUT
			GLUquadricObj *pObj;	// Temporary, used for quadrics
			pObj = gluNewQuadric();
			glTranslatef(float(this->x),float(this->y),float(this->z));
			gluSphere(pObj, float(0.05), 10, 10);

			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		};

	};//end namespace GtOpenGL
};//end namespace GT