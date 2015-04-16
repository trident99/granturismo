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

#include ".\GM_AABox.h"
#include "..\..\GtOpenGLMath.h"

namespace GT
{
	namespace GtOpenGL
	{

		GM_AABox::GM_AABox(void)
			: GtCadObject()
		{
			//HtlBase Initialization
			m_strType = "GM_AABox";
			//GM_AABox Initialization////////////////////
			this->Zero();
			return;
		};

		GM_AABox::GM_AABox(    double dblXMin, double dblXMax,
			double dblYMin, double dblYMax,
			double dblZMin, double dblZMax)
			: GtCadObject()
		{
			//HtlBase Initialization
			m_strType = "GM_AABox";
			//set coordinates
			m_dblXMin = dblXMin;
			m_dblXMax = dblXMax;
			m_dblYMin = dblYMin;
			m_dblYMax = dblYMax;
			m_dblZMin = dblZMin;
			m_dblZMax = dblZMax;
		};

		GM_AABox::GM_AABox(GM_AABox& rhs)
			: GtCadObject(rhs)
		{
			//HtlBase Initialization
			m_strType = "GM_AABox";
			//GM_AABox Initialization////////////////////
			m_dblXMin = rhs.m_dblXMin;
			m_dblXMax = rhs.m_dblXMax;
			m_dblYMin = rhs.m_dblYMin;
			m_dblYMax = rhs.m_dblYMax;
			m_dblZMin = rhs.m_dblZMin;
			m_dblZMax = rhs.m_dblZMax;

			return;
		};

		GM_AABox & GM_AABox::operator = (GM_AABox & rhs)
		{
			if(this != &rhs)
			{
				HtlBase::operator=(rhs);
				//HtlBase Initialization
				m_strType = "GM_AABox";
				//GM_AABox Initialization////////////////////
				m_dblXMin = rhs.m_dblXMin;
				m_dblXMax = rhs.m_dblXMax;
				m_dblYMin = rhs.m_dblYMin;
				m_dblYMax = rhs.m_dblYMax;
				m_dblZMin = rhs.m_dblZMin;
				m_dblZMax = rhs.m_dblZMax;
			}
			return *this;	
		};

		GM_AABox::~GM_AABox(void)
		{
			return;
		};

		bool GM_AABox::operator == (GM_AABox & rhs)
		{
			if(m_dblXMin != rhs.m_dblXMin){return false;};
			if(m_dblXMax != rhs.m_dblXMax){return false;};

			if(m_dblYMin != rhs.m_dblYMin){return false;};
			if(m_dblYMax != rhs.m_dblYMax){return false;};

			if(m_dblZMin != rhs.m_dblZMin){return false;};
			if(m_dblZMax != rhs.m_dblZMax){return false;};

			//made it this far without finding a difference, must be the same
			return true;
		};
		bool GM_AABox::operator != (GM_AABox & rhs)
		{
			if(m_dblXMin != rhs.m_dblXMin){return true;};
			if(m_dblXMax != rhs.m_dblXMax){return true;};

			if(m_dblYMin != rhs.m_dblYMin){return true;};
			if(m_dblYMax != rhs.m_dblYMax){return true;};

			if(m_dblZMin != rhs.m_dblZMin){return true;};
			if(m_dblZMax != rhs.m_dblZMax){return true;};
			//made it this far without finding a difference, must be the same
			return false;	
		};
		bool GM_AABox::IsBoxValid(void)
		{
			if( (abs(m_dblXMax - m_dblXMin) *
				abs(m_dblYMax - m_dblYMin) *
				abs(m_dblZMax - m_dblZMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		bool GM_AABox::IsBoxValidXY(void)
		{
			if( (abs(m_dblXMax - m_dblXMin) *
				abs(m_dblYMax - m_dblYMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		bool GM_AABox::IsBoxValidXZ(void)
		{
			if( (abs(m_dblXMax - m_dblXMin) *
				abs(m_dblZMax - m_dblZMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		bool GM_AABox::IsBoxValidYZ(void)
		{
			if( (abs(m_dblYMax - m_dblYMin) *
				abs(m_dblZMax - m_dblZMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		void GM_AABox::Reset(void)
		{
			m_dblXMin = -1;
			m_dblXMax = -1;
			m_dblYMin = -1;
			m_dblYMax = -1;
			m_dblZMin = -1;
			m_dblZMax = -1;
		};
		void GM_AABox::Zero(void)
		{
			m_dblXMin = 0.0f;
			m_dblXMax = 0.0f;
			m_dblYMin = 0.0f;
			m_dblYMax = 0.0f;
			m_dblZMin = 0.0f;
			m_dblZMax = 0.0f;
		};
		double GM_AABox::GetBaseArea(void)
		{
			return (fabs(m_dblXMax - m_dblXMin) * fabs(m_dblYMax - m_dblYMin));
		};

		double GM_AABox::GetVolume(void)
		{
			return (fabs(m_dblXMax - m_dblXMin) * fabs(m_dblYMax - m_dblYMin)* fabs(m_dblZMax - m_dblZMin));
		};
		GtPoint3DF GM_AABox::GetCentroid(void)
		{
			GtPoint3DF objPointTemp;
			objPointTemp.x = (m_dblXMin + m_dblXMax) / (2.0f);
			objPointTemp.y = (m_dblYMin + m_dblYMax) / (2.0f);
			objPointTemp.z = (m_dblZMin + m_dblZMax) / (2.0f);
			return objPointTemp;
		};
		GtPoint3DF GM_AABox::GetBaseCentroid(void)
		{
			GtPoint3DF objPointTemp;
			objPointTemp.x = (m_dblXMin + m_dblXMax) / (2.0f);
			objPointTemp.y = (m_dblYMin + m_dblYMax) / (2.0f);
			objPointTemp.z = (m_dblZMin);
			return objPointTemp;
		};

		GtPoint3DF GM_AABox::GetXMinYMinZMin(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMin,m_dblZMin);
		};
		GtPoint3DF GM_AABox::GetXMinYMinZMax(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMin,m_dblZMax);
		};
		GtPoint3DF GM_AABox::GetXMinYMaxZMin(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMax,m_dblZMin);
		};
		GtPoint3DF GM_AABox::GetXMinYMaxZMax(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMax,m_dblZMax);
		};

		GtPoint3DF GM_AABox::GetXMaxYMinZMin(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMin,m_dblZMin);
		};
		GtPoint3DF GM_AABox::GetXMaxYMinZMax(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMin,m_dblZMax);
		};
		GtPoint3DF GM_AABox::GetXMaxYMaxZMin(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMax,m_dblZMin);
		};
		GtPoint3DF GM_AABox::GetXMaxYMaxZMax(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMax,m_dblZMax);
		};



		void GM_AABox::RenderOverlay(const GtViewpoint & ptrCurrViewPoint)
		{
			if(!ptrCurrViewPoint.m_ptrPainter){return;};
			GtPainter * ptrPainter = ptrCurrViewPoint.m_ptrPainter;
			GtPoint3DI objScreenPoint;
			GtPoint3DF objOrigin = this->GetCentroid();
			WorldToViewportCoord(ptrCurrViewPoint,objOrigin,objScreenPoint);
			int radius = 4;
			GtBrush objBrush(GtColor(this->m_objSurfMaterial.m_objDiffuseColor.m_intRed,
				this->m_objSurfMaterial.m_objDiffuseColor.m_intGreen,
				this->m_objSurfMaterial.m_objDiffuseColor.m_intBlue));

			ptrPainter->Set_objBrush(objBrush);
			ptrPainter->GtDrawCircle(objScreenPoint,radius);
			//think this is where the memory leaking is
			std::string strLabel = "CENTROID";
			ptrPainter->GtDrawStaticText(strLabel,objScreenPoint);
		};


		//Private drawing routines for different modes of drawing
		void GM_AABox::DrawSurfaces(void)
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
			//POINTS USED FOR RENDERING OF THE BOX 8 OF THEM AND THEY ARE OBJECT ORIENTED -NOT- AXIS ALIGNED
			//RHINO ORIENTATION USED FOR POINT ORDER
			GtPoint3DF m_objXMinYMinZMin = this->GetXMinYMinZMin();//RHINO POINT 0
			GtPoint3DF m_objXMaxYMinZMin = this->GetXMaxYMinZMin();//RHINO POINT 1
			GtPoint3DF m_objXMaxYMaxZMin = this->GetXMaxYMaxZMin();//RHINO POINT 2
			GtPoint3DF m_objXMinYMaxZMin = this->GetXMinYMaxZMin();//RHINO POINT 3
			GtPoint3DF m_objXMinYMinZMax = this->GetXMinYMinZMax();//RHINO POINT 4
			GtPoint3DF m_objXMaxYMinZMax = this->GetXMaxYMinZMax();//RHINO POINT 5
			GtPoint3DF m_objXMaxYMaxZMax = this->GetXMaxYMaxZMax();//RHINO POINT 6
			GtPoint3DF m_objXMinYMaxZMax = this->GetXMinYMaxZMax();//RHINO POINT 7
			//XMIN PLANE //p0,p4,p7,p3
			glNormal3f(-1,0,0);						//required for shading
			glBegin(GL_QUADS);						// Draw A Quad
			glVertex3f(float(m_objXMinYMinZMin.x), float(m_objXMinYMinZMin.y), float(m_objXMinYMinZMin.z));
			glVertex3f(float(m_objXMinYMinZMax.x), float(m_objXMinYMinZMax.y), float(m_objXMinYMinZMax.z));
			glVertex3f(float(m_objXMinYMaxZMax.x), float(m_objXMinYMaxZMax.y), float(m_objXMinYMaxZMax.z));
			glVertex3f(float(m_objXMinYMaxZMin.x), float(m_objXMinYMaxZMin.y), float(m_objXMinYMaxZMin.z));
			glEnd();							// Done Drawing The Quad
			//XMAX PLANE //p1,p2,p6,p5
			glNormal3f(1,0,0);						//required for shading
			glBegin(GL_QUADS);						// Draw A Quad
			glVertex3f(float(m_objXMaxYMinZMin.x), float(m_objXMaxYMinZMin.y), float(m_objXMaxYMinZMin.z));
			glVertex3f(float(m_objXMaxYMaxZMin.x), float(m_objXMaxYMaxZMin.y), float(m_objXMaxYMaxZMin.z));
			glVertex3f(float(m_objXMaxYMaxZMax.x), float(m_objXMaxYMaxZMax.y), float(m_objXMaxYMaxZMax.z));
			glVertex3f(float(m_objXMaxYMinZMax.x), float(m_objXMaxYMinZMax.y), float(m_objXMaxYMinZMax.z));
			glEnd();							// Done Drawing The Quad

			//YMIN PLANE //p0,p1,p5,p4
			glNormal3f(0,-1,0);						//required for shading
			glBegin(GL_QUADS);						// Draw A Quad
			glVertex3f(float(m_objXMinYMinZMin.x), float(m_objXMinYMinZMin.y), float(m_objXMinYMinZMin.z));
			glVertex3f(float(m_objXMaxYMinZMin.x), float(m_objXMaxYMinZMin.y), float(m_objXMaxYMinZMin.z));
			glVertex3f(float(m_objXMaxYMinZMax.x), float(m_objXMaxYMinZMax.y), float(m_objXMaxYMinZMax.z));
			glVertex3f(float(m_objXMinYMinZMax.x), float(m_objXMinYMinZMax.y), float(m_objXMinYMinZMax.z));
			glEnd();							// Done Drawing The Quad
			//YMAX PLANE //p2,p3,p7,p6
			glNormal3f(0,1,0);						//required for shading
			glBegin(GL_QUADS);						// Draw A Quad
			glVertex3f(float(m_objXMaxYMaxZMin.x), float(m_objXMaxYMaxZMin.y), float(m_objXMaxYMaxZMin.z));
			glVertex3f(float(m_objXMinYMaxZMin.x), float(m_objXMinYMaxZMin.y), float(m_objXMinYMaxZMin.z));
			glVertex3f(float(m_objXMinYMaxZMax.x), float(m_objXMinYMaxZMax.y), float(m_objXMinYMaxZMax.z));
			glVertex3f(float(m_objXMaxYMaxZMax.x), float(m_objXMaxYMaxZMax.y), float(m_objXMaxYMaxZMax.z));
			glEnd();							// Done Drawing The Quad

			//ZMIN PLANE
			glNormal3f(0,0,-1);						//required for shading
			glBegin(GL_QUADS);	//p1,p0,p3,p2					// Draw A Quad
			glVertex3f(float(m_objXMaxYMinZMin.x), float(m_objXMaxYMinZMin.y), float(m_objXMaxYMinZMin.z));
			glVertex3f(float(m_objXMinYMinZMin.x), float(m_objXMinYMinZMin.y), float(m_objXMinYMinZMin.z));
			glVertex3f(float(m_objXMinYMaxZMin.x), float(m_objXMinYMaxZMin.y), float(m_objXMinYMaxZMin.z));
			glVertex3f(float(m_objXMaxYMaxZMin.x), float(m_objXMaxYMaxZMin.y), float(m_objXMaxYMaxZMin.z));
			glEnd();							// Done Drawing The Quad
			//ZMAX PLANE //p4,p5,p6,p7
			glNormal3f(0,0,1);						//required for shading
			glBegin(GL_QUADS);						// Draw A Quad
			glVertex3f(float(m_objXMinYMinZMax.x), float(m_objXMinYMinZMax.y), float(m_objXMinYMinZMax.z));
			glVertex3f(float(m_objXMaxYMinZMax.x), float(m_objXMaxYMinZMax.y), float(m_objXMaxYMinZMax.z));
			glVertex3f(float(m_objXMaxYMaxZMax.x), float(m_objXMaxYMaxZMax.y), float(m_objXMaxYMaxZMax.z));
			glVertex3f(float(m_objXMinYMaxZMax.x), float(m_objXMinYMaxZMax.y), float(m_objXMinYMaxZMax.z));
			glEnd();							// Done Drawing The Quad

			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		};

		void GM_AABox::DrawCurves(void)
		{
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
			//DRAW THE SURFACES -->NORMALS OUT
			//POINTS USED FOR RENDERING OF THE BOX 8 OF THEM AND THEY ARE OBJECT ORIENTED -NOT- AXIS ALIGNED
			//RHINO ORIENTATION USED FOR POINT ORDER
			GtPoint3DF m_objXMinYMinZMin = this->GetXMinYMinZMin();//RHINO POINT 0
			GtPoint3DF m_objXMaxYMinZMin = this->GetXMaxYMinZMin();//RHINO POINT 1
			GtPoint3DF m_objXMaxYMaxZMin = this->GetXMaxYMaxZMin();//RHINO POINT 2
			GtPoint3DF m_objXMinYMaxZMin = this->GetXMinYMaxZMin();//RHINO POINT 3
			GtPoint3DF m_objXMinYMinZMax = this->GetXMinYMinZMax();//RHINO POINT 4
			GtPoint3DF m_objXMaxYMinZMax = this->GetXMaxYMinZMax();//RHINO POINT 5
			GtPoint3DF m_objXMaxYMaxZMax = this->GetXMaxYMaxZMax();//RHINO POINT 6
			GtPoint3DF m_objXMinYMaxZMax = this->GetXMinYMaxZMax();//RHINO POINT 7

			glLineWidth(2.0f);
			//XMIN PLANE //p0,p4,p7,p3
			glNormal3f(-1,0,0);						//required for shading
			glBegin(GL_LINE_STRIP);						// Draw A Quad
			glVertex3f(float(m_objXMinYMinZMin.x), float(m_objXMinYMinZMin.y), float(m_objXMinYMinZMin.z));
			glVertex3f(float(m_objXMinYMinZMax.x), float(m_objXMinYMinZMax.y), float(m_objXMinYMinZMax.z));
			glVertex3f(float(m_objXMinYMaxZMax.x), float(m_objXMinYMaxZMax.y), float(m_objXMinYMaxZMax.z));
			glVertex3f(float(m_objXMinYMaxZMin.x), float(m_objXMinYMaxZMin.y), float(m_objXMinYMaxZMin.z));
			glEnd();							// Done Drawing The Quad
			//XMAX PLANE //p1,p2,p6,p5
			glNormal3f(1,0,0);						//required for shading
			glBegin(GL_LINE_STRIP);						// Draw A Quad
			glVertex3f(float(m_objXMaxYMinZMin.x), float(m_objXMaxYMinZMin.y), float(m_objXMaxYMinZMin.z));
			glVertex3f(float(m_objXMaxYMaxZMin.x), float(m_objXMaxYMaxZMin.y), float(m_objXMaxYMaxZMin.z));
			glVertex3f(float(m_objXMaxYMaxZMax.x), float(m_objXMaxYMaxZMax.y), float(m_objXMaxYMaxZMax.z));
			glVertex3f(float(m_objXMaxYMinZMax.x), float(m_objXMaxYMinZMax.y), float(m_objXMaxYMinZMax.z));
			glEnd();							// Done Drawing The Quad

			//YMIN PLANE //p0,p1,p5,p4
			glNormal3f(0,-1,0);						//required for shading
			glBegin(GL_LINE_STRIP);						// Draw A Quad
			glVertex3f(float(m_objXMinYMinZMin.x), float(m_objXMinYMinZMin.y), float(m_objXMinYMinZMin.z));
			glVertex3f(float(m_objXMaxYMinZMin.x), float(m_objXMaxYMinZMin.y), float(m_objXMaxYMinZMin.z));
			glVertex3f(float(m_objXMaxYMinZMax.x), float(m_objXMaxYMinZMax.y), float(m_objXMaxYMinZMax.z));
			glVertex3f(float(m_objXMinYMinZMax.x), float(m_objXMinYMinZMax.y), float(m_objXMinYMinZMax.z));
			glEnd();							// Done Drawing The Quad
			//YMAX PLANE //p2,p3,p7,p6
			glNormal3f(0,1,0);						//required for shading
			glBegin(GL_LINE_STRIP);						// Draw A Quad
			glVertex3f(float(m_objXMaxYMaxZMin.x), float(m_objXMaxYMaxZMin.y), float(m_objXMaxYMaxZMin.z));
			glVertex3f(float(m_objXMinYMaxZMin.x), float(m_objXMinYMaxZMin.y), float(m_objXMinYMaxZMin.z));
			glVertex3f(float(m_objXMinYMaxZMax.x), float(m_objXMinYMaxZMax.y), float(m_objXMinYMaxZMax.z));
			glVertex3f(float(m_objXMaxYMaxZMax.x), float(m_objXMaxYMaxZMax.y), float(m_objXMaxYMaxZMax.z));
			glEnd();							// Done Drawing The Quad

			//ZMIN PLANE
			glNormal3f(0,0,-1);						//required for shading
			glBegin(GL_LINE_STRIP);	//p1,p0,p3,p2					// Draw A Quad
			glVertex3f(float(m_objXMaxYMinZMin.x), float(m_objXMaxYMinZMin.y), float(m_objXMaxYMinZMin.z));
			glVertex3f(float(m_objXMinYMinZMin.x), float(m_objXMinYMinZMin.y), float(m_objXMinYMinZMin.z));
			glVertex3f(float(m_objXMinYMaxZMin.x), float(m_objXMinYMaxZMin.y), float(m_objXMinYMaxZMin.z));
			glVertex3f(float(m_objXMaxYMaxZMin.x), float(m_objXMaxYMaxZMin.y), float(m_objXMaxYMaxZMin.z));
			glEnd();							// Done Drawing The Quad
			//ZMAX PLANE //p4,p5,p6,p7
			glNormal3f(0,0,1);						//required for shading
			glBegin(GL_LINE_STRIP);						// Draw A Quad
			glVertex3f(float(m_objXMinYMinZMax.x), float(m_objXMinYMinZMax.y), float(m_objXMinYMinZMax.z));
			glVertex3f(float(m_objXMaxYMinZMax.x), float(m_objXMaxYMinZMax.y), float(m_objXMaxYMinZMax.z));
			glVertex3f(float(m_objXMaxYMaxZMax.x), float(m_objXMaxYMaxZMax.y), float(m_objXMaxYMaxZMax.z));
			glVertex3f(float(m_objXMinYMaxZMax.x), float(m_objXMinYMaxZMax.y), float(m_objXMinYMaxZMax.z));
			glEnd();							// Done Drawing The Quad
			//set line width back to default
			glLineWidth(1.0f);
			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_LIGHTING);

		};
		void GM_AABox::DrawPoints(void)
		{

		};

		//!Return the bounding box of the item 
		GtAABox GM_AABox::GetBoundingBox(void)
		{
			GtAABox retBox;
			retBox.m_dblXMin = this->m_dblXMin;
			retBox.m_dblXMax = this->m_dblXMax;
			retBox.m_dblYMin = this->m_dblYMin;
			retBox.m_dblYMax = this->m_dblYMax;
			retBox.m_dblZMin = this->m_dblZMin;
			retBox.m_dblZMax = this->m_dblZMax;
			return retBox;
		};
		//!Return the selection box of the item 
		GtAABox GM_AABox::GetSelectionBox(void)
		{
			GtAABox retBox;
			retBox.m_dblXMin = this->m_dblXMin;
			retBox.m_dblXMax = this->m_dblXMax;
			retBox.m_dblYMin = this->m_dblYMin;
			retBox.m_dblYMax = this->m_dblYMax;
			retBox.m_dblZMin = this->m_dblZMin;
			retBox.m_dblZMax = this->m_dblZMax;
			return retBox;
		};

	};//end namespace GtOpenGL
};//end namespace GT