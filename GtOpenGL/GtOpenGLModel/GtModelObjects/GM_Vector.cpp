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
#include ".\GM_Vector.h"
#include "..\..\GtOpenGLMath.h"


namespace GT
{
	namespace GtOpenGL
	{

		GM_Vector::GM_Vector(GtObject* ptrParent)
			: GtCadObject(ptrParent)
		{
			//m_strISAGLTypeName = "GM_Vector";
			//set the grid color to default dark gray
			this->m_objCurveMaterial.m_objDiffuseColor.SetRGB(50,50,50,255);
			this->m_objCurveMaterial.m_objSpecularColor.SetRGB(0,0,0,255);

			this->m_objSurfMaterial.m_objDiffuseColor.SetRGB(150,150,150,255);
			this->m_objSurfMaterial.m_objSpecularColor.SetRGB(0,0,0,255);
			//set default for plane orientation

			//!boolean flag for draw arrow
			this->m_blnDrawArrow = true;
			//!Cylinder Vector Radius
			this->m_dblVectorRadius = 0.01f;
			//!Arrow Radius
			this->m_dblArrowRadius = 0.05f;
			//!Arrow Height
			this->m_dblArrowHeight = 0.05f;
			//!Width YDir (without rotation)
			this->m_intNumSections = 10;
			//!Show Text
			this->m_blnShowText = true;

			this->m_ptrQStartDisk = NULL;
			this->m_ptrQEndDisk = NULL;
			this->m_ptrQCylinder = NULL;
			this->m_ptrQCone = NULL;
			this->m_ptrQConeDisk = NULL;

			//make the quadratics
			this->m_ptrQStartDisk = gluNewQuadric();
			this->m_ptrQEndDisk = gluNewQuadric();
			this->m_ptrQCylinder = gluNewQuadric();
			this->m_ptrQCone = gluNewQuadric();
			this->m_ptrQConeDisk = gluNewQuadric();
		};

		GM_Vector::~GM_Vector()
		{
			if(m_ptrQStartDisk)
			{
				gluDeleteQuadric(m_ptrQStartDisk);
			};

			if(m_ptrQEndDisk)
			{
				gluDeleteQuadric(m_ptrQEndDisk);
			};

			if(m_ptrQCylinder)
			{
				gluDeleteQuadric(m_ptrQCylinder);
			};

			if(m_ptrQCone)
			{
				gluDeleteQuadric(m_ptrQCone);
			};

			if(m_ptrQConeDisk)
			{
				gluDeleteQuadric(m_ptrQConeDisk);
			};
		};


		//Set and Get for Radius
		void GM_Vector::Set_dblVectorRadius(double dblRadius)
		{
			this->m_dblVectorRadius = dblRadius;
			this->UpdateGeometry();
			ModelItemModified.Emit();
		};

		double GM_Vector::Get_dblVectorRadius(void)
		{
			return m_dblVectorRadius;
		};

		//Set and Get for Radius
		void GM_Vector::Set_dblArrowRadius(double dblRadius)
		{
			this->m_dblArrowRadius = dblRadius;
			this->UpdateGeometry();
			ModelItemModified.Emit();
		};

		double GM_Vector::Get_dblArrowRadius(void)
		{
			return m_dblArrowRadius;
		};

		//Set and Get for Height
		void GM_Vector::Set_dblArrowHeight(double dblHeight)
		{
			this->m_dblArrowHeight = dblHeight;
			this->UpdateGeometry();
			ModelItemModified.Emit();
		};

		double GM_Vector::Get_dblArrowHeight(void)
		{
			return m_dblArrowHeight;
		};

		//Set and Get for Number of Mesh Panels
		void GM_Vector::Set_intNumSections(int intNumSections)
		{
			this->m_intNumSections = intNumSections;
			this->UpdateGeometry();
			ModelItemModified.Emit();
		};

		int GM_Vector::Get_intNumSections(void)
		{
			return m_intNumSections;
		};

		//Set and Get for Origin
		void GM_Vector::Set_objStart(GtPoint3DF objPoint)
		{
			this->m_objStart = objPoint;
			this->UpdateGeometry();
			ModelItemModified.Emit();
		};

		GtPoint3DF GM_Vector::Get_objStart(void)
		{
			return m_objStart;
		};

		//Set and Get for Rotation
		void GM_Vector::Set_objEnd(GtPoint3DF objPoint)
		{
			this->m_objEnd = objPoint;
			this->UpdateGeometry();
			ModelItemModified.Emit();
		};

		GtPoint3DF GM_Vector::Get_objEnd(void)
		{
			return m_objEnd;
		};

		//!Return the bounding box of the item 
		GtAABox GM_Vector::GetBoundingBox(void)
		{
			if(!this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				return this->m_objBoundingBox;
			};


			m_objBoundingBox.m_dblXMin = m_objStart.x;
			m_objBoundingBox.m_dblXMax = m_objStart.x;
			m_objBoundingBox.m_dblYMin = m_objStart.y;
			m_objBoundingBox.m_dblYMax = m_objStart.y;
			m_objBoundingBox.m_dblZMin = m_objStart.z;
			m_objBoundingBox.m_dblZMax = m_objStart.z;

			if(m_objEnd.x < m_objBoundingBox.m_dblXMin){m_objBoundingBox.m_dblXMin = m_objEnd.x;};
			if(m_objEnd.x > m_objBoundingBox.m_dblXMax){m_objBoundingBox.m_dblXMax = m_objEnd.x;};
			if(m_objEnd.y < m_objBoundingBox.m_dblYMin){m_objBoundingBox.m_dblYMin = m_objEnd.y;};
			if(m_objEnd.y > m_objBoundingBox.m_dblYMax){m_objBoundingBox.m_dblYMax = m_objEnd.y;};
			if(m_objEnd.z < m_objBoundingBox.m_dblZMin){m_objBoundingBox.m_dblZMin = m_objEnd.z;};
			if(m_objEnd.z > m_objBoundingBox.m_dblZMax){m_objBoundingBox.m_dblZMax = m_objEnd.z;};
			return m_objBoundingBox;
		};
		//!Return the bounding box of the item 
		GtAABox GM_Vector::GetSelectionBox(void)
		{

			if(this->m_blnBoxUpdate)
			{
				//return the already calculated bounding box
				this->GetBoundingBox();
			};
			//otherwise return the already calculated box

			return this->m_objBoundingBox;
		};

		void GM_Vector::RenderModelItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode)
		{
			//THIS FUNCTION CAN BE OVERRIDDEN IF DESIRED BUT THIS IS THE DEFAULT BEHAVIOR
			if(!m_blnVisible){return;};
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
					break;
				};
			case Shaded:
				{
					this->DrawSurfaces();
					break;
				};
			case ShadedWithMesh:
				{
					this->DrawSurfaces();
					break;
				};
			case ShadedWithCurves:
				{
					this->DrawSurfaces();
					this->DrawCurves();
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
					break;
				};
			default:
				{
					//default behavior is shaded with curves
					this->DrawSurfaces();
					this->DrawCurves();
					break;
				};

			};//end switch on statement
			//this->m_blnUpdateGLList = false;

			return;
		};

		void GM_Vector::RenderOverlay(const GtViewpoint & ptrCurrViewPoint)
		{
			//if not visible quit out
			if(!m_blnVisible){return;};
			//safety code check
			if(!ptrCurrViewPoint.m_ptrPainter){return;};
			//get the location of the dot
			GtPainter * painter = ptrCurrViewPoint.m_ptrPainter;
			//convert the call out global coordinates to screen local coordinates
			GtPoint3DF objMidPoint;
			GtPoint3DI objDisplayPoint;
			objMidPoint.x = (this->m_objStart.x + this->m_objEnd.x ) / (2.0f);
			objMidPoint.y = (this->m_objStart.y + this->m_objEnd.y ) / (2.0f);
			objMidPoint.z = (this->m_objStart.z + this->m_objEnd.z ) / (2.0f);

			WorldToViewportCoord(ptrCurrViewPoint,objMidPoint, objDisplayPoint);
			//save the current painter state
			if(m_blnShowText)
			{

				//QPen objPen(QColor(0,0,0));
				//painter->setPen(objPen);
				//QString strMultiLine;
				//strMultiLine = QString::fromStdString(m_strText);
				//QRectF objViewport = painter->viewport();
				//QRectF objBoundingRect = painter->boundingRect(objViewport,Qt::AlignLeft|Qt::TextWordWrap ,strMultiLine);
				//painter->drawText(QRectF(objDisplayPoint.x(),objDisplayPoint.y(),objBoundingRect.width(),objBoundingRect.height())
				//	,Qt::AlignLeft|Qt::TextWordWrap ,strMultiLine);
			};
			//restore the current painter state

			return;
		};


		//!Update the control points for the box
		void GM_Vector::UpdateGeometry(void)
		{
			GtPoint3DF objLocXDir,objLocYDir,objLocZDir,objUpDir,objPointTemp;
			GtPoint3DF objNormal, objUnitNormal,objDir;
			std::vector<GtPoint3DF> arrObjNonTransDiskPoints;
			//individual members 
			int i, intUboundI;
			float sngRotMatrix[16], sngPointTemp[4], sngOutTemp[4];
			double dblElevationAngle, dblPI, dblDeltaRad;
			double dblThetaRad;
			double dblParamT = 0.95f;
			dblPI = 3.1415926;
			//Rotation matrix
			/*
			M = m0,m4,m8,m12
			m1,m5,m9,m13
			m2,m6,m10,m14
			m3,m7,m11,m15
			*/
			dblDeltaRad = (2 * dblPI) / double(m_intNumSections);
			arrObjNonTransDiskPoints.clear();
			m_arrObjArrowDiskPoints.clear();
			//calculate the end point

			objDir = m_objEnd - m_objStart;

			m_objArrowBase.x = m_objStart.x + dblParamT * objDir.x;
			m_objArrowBase.y = m_objStart.y + dblParamT * objDir.y;
			m_objArrowBase.z = m_objStart.z + dblParamT * objDir.z;

			//arrow normal and unit normal
			objNormal = m_objEnd - m_objArrowBase;
			objUnitNormal = objNormal;
			objUnitNormal.Normalize();
			//Calculate the directional vectors
			objLocZDir = objUnitNormal;
			dblElevationAngle = GtMath::Angle3D(GtPoint3DF(0.0f,0.0f,1.0f),objUnitNormal);
			if(abs(dblElevationAngle) < 0.05)
			{//then close to gimble lock, use y axis as up
				objUpDir.Set(0.0,1.0,0.0);
			}else{
				//use Z Axis as updir
				objUpDir.Set(0.0,0.0,1.0);
			}
			objLocXDir = GtMath::Cross3D(objUpDir,objLocZDir);
			objLocXDir.Normalize();
			objLocYDir = GtMath::Cross3D(objLocZDir,objLocXDir);
			objLocYDir.Normalize();
			//Now we have our transformation matrix
			sngRotMatrix[0] = (float)objLocXDir.x;
			sngRotMatrix[1] = (float)objLocXDir.y;
			sngRotMatrix[2] = (float)objLocXDir.z;
			sngRotMatrix[3] = (float)0.0f;
			sngRotMatrix[4] = (float)objLocYDir.x;
			sngRotMatrix[5] = (float)objLocYDir.y;
			sngRotMatrix[6] = (float)objLocYDir.z;
			sngRotMatrix[7] = (float)0.0f;
			sngRotMatrix[8] = (float)objLocZDir.x;
			sngRotMatrix[9] = (float)objLocZDir.y;
			sngRotMatrix[10] = (float)objLocZDir.z;
			sngRotMatrix[11] = (float)0.0f;
			sngRotMatrix[12] = (float)m_objArrowBase.x;
			sngRotMatrix[13] = (float)m_objArrowBase.y;
			sngRotMatrix[14] = (float)m_objArrowBase.z;
			sngRotMatrix[15] = (float)0.0f;

			//calculate the disk points without orientation
			for(dblThetaRad = 0.0f ; dblThetaRad < (2.0f * dblPI) ; dblThetaRad += dblDeltaRad)
			{
				objPointTemp.Zero();
				objPointTemp.x = m_dblArrowRadius* cos(dblThetaRad);
				objPointTemp.y = m_dblArrowRadius* sin(dblThetaRad);
				arrObjNonTransDiskPoints.push_back(objPointTemp);
			}
			//now transform the disk
			intUboundI = arrObjNonTransDiskPoints.size();
			for(i = 0; i < intUboundI;i++)
			{
				sngPointTemp[0] = (float)arrObjNonTransDiskPoints.at(i).x;
				sngPointTemp[1] = (float)arrObjNonTransDiskPoints.at(i).y;
				sngPointTemp[2] = (float)arrObjNonTransDiskPoints.at(i).z;
				sngPointTemp[3] = (float)1.0f;

				GtMath::MultMatrix44Vector4(sngRotMatrix,sngPointTemp,sngOutTemp);
				objPointTemp.Zero();
				objPointTemp.x = sngOutTemp[0];
				objPointTemp.y = sngOutTemp[1];
				objPointTemp.z = sngOutTemp[2];
				m_arrObjArrowDiskPoints.push_back(objPointTemp);
			};
			return;
		};
		//Private drawing routines for different modes of drawing
		void GM_Vector::DrawSurfaces(void)
		{		
			this->DrawCylinderSurfaces();
			if(this->m_blnDrawArrow)
			{
				this->DrawArrowSurfaces();
			};
			return;
		};

		void GM_Vector::DrawCurves(void)
		{
			this->DrawCylinderCurves();
			if(this->m_blnDrawArrow)
			{
				this->DrawArrowCurves();
			};
			return;
		};
		void GM_Vector::DrawPoints(void)
		{

		};

		void GM_Vector::DrawArrowCurves(void)
		{
			int i, intUboundI;
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
			//DRAW THE CONE//////////////////////////////////////
			intUboundI = m_arrObjArrowDiskPoints.size();
			for(i = 0; i < intUboundI - 1;i++)
			{
				glBegin(GL_LINE_STRIP);
				glVertex3f(float(m_objArrowBase.x),float(m_objArrowBase.y),float(m_objArrowBase.z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i).x),float(m_arrObjArrowDiskPoints.at(i).y),float(m_arrObjArrowDiskPoints.at(i).z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i+1).x),float(m_arrObjArrowDiskPoints.at(i+1).y),float(m_arrObjArrowDiskPoints.at(i+1).z));
				glVertex3f(float(m_objArrowBase.x),float(m_objArrowBase.y),float(m_objArrowBase.z));
				glEnd();
			}
			//close the set by doing the last one manually
			glBegin(GL_LINE_STRIP);
			glVertex3f(float(m_objArrowBase.x),float(m_objArrowBase.y),float(m_objArrowBase.z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(intUboundI - 1).x),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).y),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(0).x),float(m_arrObjArrowDiskPoints.at(0).y),float(m_arrObjArrowDiskPoints.at(0).z));
			glVertex3f(float(m_objArrowBase.x),float(m_objArrowBase.y),float(m_objArrowBase.z));
			glEnd();
			//DRAW THE DISK/////////////////////////////////////
			intUboundI = m_arrObjArrowDiskPoints.size();
			for(i = 0; i < intUboundI - 1;i++)
			{
				glBegin(GL_LINE_STRIP);
				glVertex3f(float(m_objEnd.x),float(m_objEnd.y),float(m_objEnd.z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i).x),float(m_arrObjArrowDiskPoints.at(i).y),float(m_arrObjArrowDiskPoints.at(i).z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i+1).x),float(m_arrObjArrowDiskPoints.at(i+1).y),float(m_arrObjArrowDiskPoints.at(i+1).z));
				glVertex3f(float(m_objEnd.x),float(m_objEnd.y),float(m_objEnd.z));
				glEnd();
			}
			//close the set by doing the last one manually
			glBegin(GL_LINE_STRIP);
			glVertex3f(float(m_objEnd.x),float(m_objEnd.y),float(m_objEnd.z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(intUboundI - 1).x),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).y),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(0).x),float(m_arrObjArrowDiskPoints.at(0).y),float(m_arrObjArrowDiskPoints.at(0).z));
			glVertex3f(float(m_objEnd.x),float(m_objEnd.y),float(m_objEnd.z));
			glEnd();

			//set line width back to default
			glLineWidth(1.0f);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_LIGHTING);


		};


		void GM_Vector::DrawCylinderCurves(void)
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
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			//DRAW THE CURVES -->NORMALS OUT
			if(this->m_blnSelected)
			{	
				glLineWidth(3.0f);
			}else{
				glLineWidth(2.0f);
			};

			glBegin(GL_LINE_STRIP);
			glVertex3f(float(m_objStart.x), float(m_objStart.y), float(m_objStart.z));
			glVertex3f(float(m_objEnd.x), float(m_objEnd.y), float(m_objEnd.z));
			glEnd();
			//set line width back to default
			glLineWidth(1.0f);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_LIGHTING);
		};

		//draw the arrow and cylinder surfaces
		void GM_Vector::DrawArrowSurfaces(void)
		{
			int i, intUboundI;
			GtPoint3DF objVectA, objVectB, objNormal;
			GtPoint3DF objDir;
			double dblParamT = 0.90f;
			//Make sure lighting is turned on
			glEnable(GL_LIGHTING);
			glMatrixMode(GL_MODELVIEW);

			objNormal = m_objEnd - m_objStart;

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

			//DRAW THE SURFACES -->NORMALS OUT/////
			//DRAW THE CONE//////////////////////////////////////
			intUboundI = m_arrObjArrowDiskPoints.size();
			for(i = 0; i < intUboundI - 1;i++)
			{
				objVectA = GtMath::Diff3D(m_arrObjArrowDiskPoints.at(i),m_objArrowBase);
				objVectB = GtMath::Diff3D(m_arrObjArrowDiskPoints.at(i+1),m_objArrowBase);
				objNormal = GtMath::Cross3D(objVectB,objVectA);
				objNormal.Normalize();
				glNormal3f(float(objNormal.x),float(objNormal.y),float(objNormal.z));
				glBegin(GL_TRIANGLES);
				glVertex3f(float(m_objArrowBase.x),float(m_objArrowBase.y),float(m_objArrowBase.z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i).x),float(m_arrObjArrowDiskPoints.at(i).y),float(m_arrObjArrowDiskPoints.at(i).z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i+1).x),float(m_arrObjArrowDiskPoints.at(i+1).y),float(m_arrObjArrowDiskPoints.at(i+1).z));
				glEnd();
			}
			//close the set by doing the last one manually
			objVectA = GtMath::Diff3D(m_arrObjArrowDiskPoints.at(intUboundI - 1),m_objArrowBase);
			objVectB = GtMath::Diff3D(m_arrObjArrowDiskPoints.at(0),m_objArrowBase);
			objNormal = GtMath::Cross3D(objVectB,objVectA);
			objNormal.Normalize();
			glNormal3f(float(objNormal.x),float(objNormal.y),float(objNormal.z));
			glBegin(GL_TRIANGLES);
			glVertex3f(float(m_objArrowBase.x),float(m_objArrowBase.y),float(m_objArrowBase.z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(intUboundI - 1).x),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).y),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(0).x),float(m_arrObjArrowDiskPoints.at(0).y),float(m_arrObjArrowDiskPoints.at(0).z));
			glEnd();
			//DRAW THE DISK/////////////////////////////////////
			objNormal = GtMath::Diff3D(m_objEnd,m_objArrowBase);
			objNormal.Normalize();
			glNormal3f(float(objNormal.x),float(objNormal.y),float(objNormal.z));
			intUboundI = m_arrObjArrowDiskPoints.size();
			for(i = 0; i < intUboundI - 1;i++)
			{
				glBegin(GL_TRIANGLES);
				glVertex3f(float(m_objEnd.x),float(m_objEnd.y),float(m_objEnd.z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i).x),float(m_arrObjArrowDiskPoints.at(i).y),float(m_arrObjArrowDiskPoints.at(i).z));
				glVertex3f(float(m_arrObjArrowDiskPoints.at(i+1).x),float(m_arrObjArrowDiskPoints.at(i+1).y),float(m_arrObjArrowDiskPoints.at(i+1).z));
				glEnd();
			}
			//close the set by doing the last one manually
			glBegin(GL_TRIANGLES);
			glVertex3f(float(m_objEnd.x),float(m_objEnd.y),float(m_objEnd.z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(intUboundI - 1).x),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).y),float(m_arrObjArrowDiskPoints.at(intUboundI - 1).z));
			glVertex3f(float(m_arrObjArrowDiskPoints.at(0).x),float(m_arrObjArrowDiskPoints.at(0).y),float(m_arrObjArrowDiskPoints.at(0).z));
			glEnd();
			//Draw the Disk Cap at the End
			//POP MODEL VIEW MATRIX
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		};

		void GM_Vector::DrawCylinderSurfaces(void)
		{

			float vx = (float)(this->m_objEnd.x - this->m_objStart.x);
			float vy = (float)(this->m_objEnd.y - this->m_objStart.y);
			float vz = (float)(this->m_objEnd.z - this->m_objStart.z);
			//handle the degenerate case of z1 == z2 with an approximation
			if(vz == 0)
				vz = (float)(0.0001f);

			float v = sqrt( vx*vx + vy*vy + vz*vz );
			float ax = (float)(57.2957795*acos( vz/v ));
			if ( vz < 0.0 ) 
			{
				ax = -ax;
			};
			float rx = -vy*vz;
			float ry = vx*vz;

			//if quadratics haven't been made make them
			if(!m_ptrQStartDisk){m_ptrQStartDisk = gluNewQuadric();};
			if(!m_ptrQEndDisk){m_ptrQEndDisk = gluNewQuadric();};
			if(!m_ptrQCylinder){m_ptrQCylinder = gluNewQuadric();};

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
				float arrSngDiffColor[4] = {1.0f, 1.0f, 0.0f, 1.0f};
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

			//draw the cylinder body
			glTranslatef( (float)m_objStart.x, (float)m_objStart.y, (float)m_objStart.z );
			glRotatef(ax, rx, ry, 0.0);
			gluQuadricOrientation(m_ptrQCylinder,GLU_OUTSIDE);
			gluCylinder(m_ptrQCylinder, m_dblVectorRadius, m_dblVectorRadius, v, m_intNumSections, 1);
			//draw the first cap
			gluQuadricOrientation(m_ptrQStartDisk,GLU_INSIDE);
			gluDisk( m_ptrQStartDisk, 0.0, m_dblVectorRadius, m_intNumSections, 1);
			glTranslatef( 0,0,v );
			//draw the second cap
			gluQuadricOrientation(m_ptrQEndDisk,GLU_OUTSIDE);
			gluDisk( m_ptrQEndDisk, 0.0, m_dblVectorRadius, m_intNumSections, 1);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			//
			return;
		};

	};//end namespace GtOpenGL

};//end namespace GT