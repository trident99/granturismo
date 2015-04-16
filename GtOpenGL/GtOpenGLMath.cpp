/*
**	This file is part of the GT OpenGL Library.
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

#include ".\GtOpenGLMath.h"

namespace GT
{
	namespace GtOpenGL
	{

		void LookAtMatrix(GtViewpoint & ptrCurrViewPoint, double* ptrMatrixOut)
		{
			//get x y and z axis based on eye and rotation center
			if(!ptrMatrixOut){return;}//safety check
			//if(sizeof(ptrMatrixOut) != (16 * sizeof(double))){return;};//safety check
			//x axis = rot - eye
			GtPoint3DF xaxis,yaxis,zaxis, negEye;
			negEye= ptrCurrViewPoint.m_objViewLocation * (-1.0);
			//xaxis = ptrCurrViewPoint.m_objViewLocation - ptrCurrViewPoint.m_objRotationCentroid;
			xaxis = ptrCurrViewPoint.m_objRotationCentroid - ptrCurrViewPoint.m_objViewLocation;
			yaxis = GtMath::Cross3D(ptrCurrViewPoint.m_objUpDir,xaxis);
			zaxis = GtMath::Cross3D(xaxis,yaxis);
			xaxis.Normalize();
			yaxis.Normalize();
			zaxis.Normalize();
			ptrMatrixOut[0] = xaxis.x;
			ptrMatrixOut[1] = xaxis.y;
			ptrMatrixOut[2] = xaxis.z;
			ptrMatrixOut[3] = GtMath::Dot3D(xaxis,negEye);

			ptrMatrixOut[4] = yaxis.x;
			ptrMatrixOut[5] = yaxis.y;
			ptrMatrixOut[6] = yaxis.z;
			ptrMatrixOut[7] = GtMath::Dot3D(yaxis,negEye);

			ptrMatrixOut[8] = zaxis.x;
			ptrMatrixOut[9] = zaxis.y;
			ptrMatrixOut[10] = zaxis.z;
			ptrMatrixOut[11] = GtMath::Dot3D(zaxis,negEye);

			ptrMatrixOut[12] = 0.0f;
			ptrMatrixOut[13] = 0.0f;
			ptrMatrixOut[14] = 0.0f;
			ptrMatrixOut[15] = 1.0f;

		}


		int glhUnProjectf(float winx, float winy, float winz, double *modelview, double *projection, int *viewport, double *objectCoordinate);

		void ViewportPickRay(GtViewpoint & ptrCurrViewPoint, const GtPoint3DI & objScreenPoint, GtPoint3DF & objRayOrig, GtPoint3DF & objRayDir)
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

			GtPoint3DF objRayEnd, objRayScreen;
			GtPoint3DI objMouseCheck;
			GLfloat winX, winY, winZ; 
			winX = (float)objScreenPoint.x ;
			winY = ((float)ptrCurrViewPoint.m_arrIntViewport[3] - (float)objScreenPoint.y);
			//convert the window x and y coords from screen to opengl 
			//get the z coord from the pixel buffer
			glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );  
			//unproject the point
			double arrModelMatrix[16];

			LookAtMatrix(ptrCurrViewPoint,arrModelMatrix);

			gluUnProject(double(winX),double(winY),double(0.1),
				ptrCurrViewPoint.m_arrDblCurrModelMatrix, ptrCurrViewPoint.m_arrDblCurrProjMatrix, ptrCurrViewPoint.m_arrIntViewport,
				&(objRayScreen.x),&(objRayScreen.y),&(objRayScreen.z));

				
			WorldToViewportCoord(ptrCurrViewPoint,objRayScreen,objMouseCheck);


			gluUnProject(double(winX),double(winY),double(0.5),
				ptrCurrViewPoint.m_arrDblCurrModelMatrix, ptrCurrViewPoint.m_arrDblCurrProjMatrix, ptrCurrViewPoint.m_arrIntViewport,
				&(objRayEnd.x),&(objRayEnd.y),&(objRayEnd.z));
			
			objRayOrig = objRayScreen;
			
			objRayDir = GtMath::Diff3D(objRayEnd,objRayScreen);

			objRayDir.Normalize();


			return;
		};


		//NEHE DEMO EXAMPLE CODE
		//CVector3 GetOGLPos(int x, int y)
		//
		//{
		//
		//    GLint viewport[4];
		//    GLdouble modelview[16];
		//    GLdouble projection[16];
		//    GLfloat winX, winY, winZ;
		//    GLdouble posX, posY, posZ;
		//
		//    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
		//    glGetDoublev( GL_PROJECTION_MATRIX, projection );
		//    glGetIntegerv( GL_VIEWPORT, viewport );
		//
		//    winX = (float)x;
		//    winY = (float)viewport[3] - (float)y;
		//
		//    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
		//    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
		//
		//    return CVector3(posX, posY, posZ);
		//
		//}

		void ViewportToWorldCoord(const GtViewpoint & ptrCurrViewPoint, const GtPoint3DI & objScreenPoint, GtPoint3DF & objWCSPoint)
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
			winX = (float)objScreenPoint.x; 
			winY = (float)ptrCurrViewPoint.m_arrIntViewport[3] - (float)objScreenPoint.y; 
			//get the z coord from the pixel buffer
			glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );  
			//unproject the point
			gluUnProject(double(winX),double(winY),double(1.0f),
				ptrCurrViewPoint.m_arrDblCurrModelMatrix, ptrCurrViewPoint.m_arrDblCurrProjMatrix, ptrCurrViewPoint.m_arrIntViewport,
				&(objWCSPoint.x),&(objWCSPoint.y),&(objWCSPoint.z));
		};
		void WorldToViewportCoord(const GtViewpoint & ptrCurrViewPoint, const GtPoint3DF & objWCSPoint, GtPoint3DI & objScreenLoc)
		{
			//GLint gluProject( GLdouble   objX,  
			// GLdouble   objY,  
			// GLdouble   objZ,  
			// const GLdouble *   model,  
			// const GLdouble *   proj,  
			// const GLint *   view,  
			// GLdouble*   winX,  
			// GLdouble*   winY,  
			// GLdouble*   winZ); 
			GtPoint3DF objScreen;

			gluProject(objWCSPoint.x, objWCSPoint.y, objWCSPoint.z,
				ptrCurrViewPoint.m_arrDblCurrModelMatrix, ptrCurrViewPoint.m_arrDblCurrProjMatrix, ptrCurrViewPoint.m_arrIntViewport,
				&objScreen.x, &objScreen.y, &objScreen.z);

			//objScreenLoc.setX(ptrCurrViewPoint.m_arrIntViewport[2] - objScreen.x); 
			objScreenLoc.x = (long)(objScreen.x); 
			objScreenLoc.y = (long)(ptrCurrViewPoint.m_arrIntViewport[3] - objScreen.y);
		};

		GtHitRecord RayIntersectAABB(GtPoint3DF & objOrig, GtPoint3DF & objRayDir, GtAABox & objTestBox)
		{
			//based on ray box intersection algorithm from A. Williams, S. Barrus, et al.
			//University of Utah
			GtHitRecord objHit;
			double dblTMin, dblTMax, dblTxMin, dblTxMax, dblTyMin, dblTyMax, dblTzMin, dblTzMax;
			double dblTStart = 0.0f; //beginning of ray interval - HARD CODED
			double dblTEnd = 10000.0f; //end of ray interval - HARD CODED

			//origin inside box check
			dblTMin = 0.0f;

			if( (objOrig.x >= objTestBox.m_dblXMin) &&
				(objOrig.x <= objTestBox.m_dblXMax) &&
				(objOrig.y >= objTestBox.m_dblYMin) &&
				(objOrig.y <= objTestBox.m_dblYMax) &&
				(objOrig.z >= objTestBox.m_dblZMin) &&
				(objOrig.z <= objTestBox.m_dblZMax) )
			{
				//then origin inside box
				objHit.m_blnHit= true;
				objHit.m_dblHitDist = 0.0f;
				return objHit;
			};

			//initialize TMin
			if(fabs(objRayDir.x) > 0.0001f) 
			{
				dblTxMin = (objTestBox.m_dblXMin - objOrig.x) / (objRayDir.x);
				dblTxMax = (objTestBox.m_dblXMax - objOrig.x) / (objRayDir.x);
				if(dblTxMax < dblTxMin)
				{
					double dblTemp = dblTxMin;
					dblTxMin = dblTxMax;
					dblTxMax = dblTemp;
				};
				dblTMin = dblTxMin;
				dblTMax = dblTxMax;
			}else{
				dblTxMin = -1.0f;
				dblTxMax = -1.0f;
			};
			if(fabs(objRayDir.y) > 0.0001f) 
			{
				dblTyMin = (objTestBox.m_dblYMin - objOrig.y) / (objRayDir.y);
				dblTyMax = (objTestBox.m_dblYMax - objOrig.y) / (objRayDir.y);
				if(dblTyMax < dblTyMin)
				{
					double dblTemp = dblTyMin;
					dblTyMin = dblTyMax;
					dblTyMax = dblTemp;
				};
				dblTMin = dblTyMin;
				dblTMax = dblTyMax;
			}else{
				dblTyMin = -1.0f;
				dblTyMax = -1.0f;	
			};
			if(fabs(objRayDir.z) > 0.0001f) 
			{
				dblTzMin = (objTestBox.m_dblZMin - objOrig.z) / (objRayDir.z);
				dblTzMax = (objTestBox.m_dblZMax - objOrig.z) / (objRayDir.z);
				if(dblTzMax < dblTzMin)
				{
					double dblTemp = dblTzMin;
					dblTzMin = dblTzMax;
					dblTzMax = dblTemp;
				};
				dblTMin = dblTzMin;
				dblTMax = dblTzMax;
			}else{
				dblTzMin = -1.0f;
				dblTzMax = -1.0f;	
			};

			//SET TMin, TMax based on planes
			if( (dblTxMin > 0) && (dblTxMin > dblTMin) ){ dblTMin = dblTxMin;};
			if( (dblTxMax > 0) && (dblTxMax < dblTMax) ){ dblTMax = dblTxMax;};

			if( (dblTyMin > 0) && (dblTyMin > dblTMin) ){ dblTMin = dblTyMin;};
			if( (dblTyMax > 0) && (dblTyMax < dblTMax) ){ dblTMax = dblTyMax;};

			if( (dblTzMin > 0) && (dblTzMin > dblTMin) ){ dblTMin = dblTzMin;};
			if( (dblTzMax > 0) && (dblTzMax < dblTMax) ){ dblTMax = dblTzMax;};

			//quit out if bad TMin, either ray directions is all zeros
			//or something else is wrong
			//if( dblTMin > dblTMax){objHit.m_blnHit = false; return objHit;};
			if( dblTMax < 0.0f){objHit.m_blnHit = false; return objHit;};
			//get coordinate for intersection point

			GtPoint3DF objHitPoint;
			objHitPoint.x = objOrig.x + dblTMin * objRayDir.x;
			objHitPoint.y = objOrig.y + dblTMin * objRayDir.y;
			objHitPoint.z = objOrig.z + dblTMin * objRayDir.z;

			//test intersection point
			if( (objHitPoint.x >= objTestBox.m_dblXMin) &&
				(objHitPoint.x <= objTestBox.m_dblXMax) &&
				(objHitPoint.y >= objTestBox.m_dblYMin) &&
				(objHitPoint.y <= objTestBox.m_dblYMax) &&
				(objHitPoint.z >= objTestBox.m_dblZMin) &&
				(objHitPoint.z <= objTestBox.m_dblZMax) )
			{
				//then origin inside box
				objHit.m_blnHit= true;
			}else{
				//then origin inside box
				objHit.m_blnHit= false;
			};

			objHit.m_dblHitDist = dblTMin;
			return objHit;

		};

void MultiplyMatrices4by4OpenGL_FLOAT(double *result, double *matrix1, double *matrix2)
		{
			result[0]=matrix1[0]*matrix2[0]+
				matrix1[4]*matrix2[1]+
				matrix1[8]*matrix2[2]+
				matrix1[12]*matrix2[3];
			result[4]=matrix1[0]*matrix2[4]+
				matrix1[4]*matrix2[5]+
				matrix1[8]*matrix2[6]+
				matrix1[12]*matrix2[7];
			result[8]=matrix1[0]*matrix2[8]+
				matrix1[4]*matrix2[9]+
				matrix1[8]*matrix2[10]+
				matrix1[12]*matrix2[11];
			result[12]=matrix1[0]*matrix2[12]+
				matrix1[4]*matrix2[13]+
				matrix1[8]*matrix2[14]+
				matrix1[12]*matrix2[15];
			result[1]=matrix1[1]*matrix2[0]+
				matrix1[5]*matrix2[1]+
				matrix1[9]*matrix2[2]+
				matrix1[13]*matrix2[3];
			result[5]=matrix1[1]*matrix2[4]+
				matrix1[5]*matrix2[5]+
				matrix1[9]*matrix2[6]+
				matrix1[13]*matrix2[7];
			result[9]=matrix1[1]*matrix2[8]+
				matrix1[5]*matrix2[9]+
				matrix1[9]*matrix2[10]+
				matrix1[13]*matrix2[11];
			result[13]=matrix1[1]*matrix2[12]+
				matrix1[5]*matrix2[13]+
				matrix1[9]*matrix2[14]+
				matrix1[13]*matrix2[15];
			result[2]=matrix1[2]*matrix2[0]+
				matrix1[6]*matrix2[1]+
				matrix1[10]*matrix2[2]+
				matrix1[14]*matrix2[3];
			result[6]=matrix1[2]*matrix2[4]+
				matrix1[6]*matrix2[5]+
				matrix1[10]*matrix2[6]+
				matrix1[14]*matrix2[7];
			result[10]=matrix1[2]*matrix2[8]+
				matrix1[6]*matrix2[9]+
				matrix1[10]*matrix2[10]+
				matrix1[14]*matrix2[11];
			result[14]=matrix1[2]*matrix2[12]+
				matrix1[6]*matrix2[13]+
				matrix1[10]*matrix2[14]+
				matrix1[14]*matrix2[15];
			result[3]=matrix1[3]*matrix2[0]+
				matrix1[7]*matrix2[1]+
				matrix1[11]*matrix2[2]+
				matrix1[15]*matrix2[3];
			result[7]=matrix1[3]*matrix2[4]+
				matrix1[7]*matrix2[5]+
				matrix1[11]*matrix2[6]+
				matrix1[15]*matrix2[7];
			result[11]=matrix1[3]*matrix2[8]+
				matrix1[7]*matrix2[9]+
				matrix1[11]*matrix2[10]+
				matrix1[15]*matrix2[11];
			result[15]=matrix1[3]*matrix2[12]+
				matrix1[7]*matrix2[13]+
				matrix1[11]*matrix2[14]+
				matrix1[15]*matrix2[15];
		}

		void MultiplyMatrixByVector4by4OpenGL_FLOAT(double *resultvector, const double *matrix, const double *pvector)
		{
			resultvector[0]=matrix[0]*pvector[0]+matrix[4]*pvector[1]+matrix[8]*pvector[2]+matrix[12]*pvector[3];
			resultvector[1]=matrix[1]*pvector[0]+matrix[5]*pvector[1]+matrix[9]*pvector[2]+matrix[13]*pvector[3];
			resultvector[2]=matrix[2]*pvector[0]+matrix[6]*pvector[1]+matrix[10]*pvector[2]+matrix[14]*pvector[3];
			resultvector[3]=matrix[3]*pvector[0]+matrix[7]*pvector[1]+matrix[11]*pvector[2]+matrix[15]*pvector[3];
		}

#define SWAP_ROWS_DOUBLE(a, b) { double *_tmp = a; (a)=(b); (b)=_tmp; }
#define SWAP_ROWS_FLOAT(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(c)*4+(r)]

		//This code comes directly from GLU except that it is for float
		int glhInvertMatrixf2(double *m, double *out)
		{
			double wtmp[4][8];
			double m0, m1, m2, m3, s;
			double *r0, *r1, *r2, *r3;
			r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];
			r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1),
				r0[2] = MAT(m, 0, 2), r0[3] = MAT(m, 0, 3),
				r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
				r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1),
				r1[2] = MAT(m, 1, 2), r1[3] = MAT(m, 1, 3),
				r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
				r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1),
				r2[2] = MAT(m, 2, 2), r2[3] = MAT(m, 2, 3),
				r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
				r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1),
				r3[2] = MAT(m, 3, 2), r3[3] = MAT(m, 3, 3),
				r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
			/* choose pivot - or die */
			if (fabsf(r3[0]) > fabsf(r2[0]))
				SWAP_ROWS_DOUBLE(r3, r2);
			if (fabsf(r2[0]) > fabsf(r1[0]))
				SWAP_ROWS_DOUBLE(r2, r1);
			if (fabsf(r1[0]) > fabsf(r0[0]))
				SWAP_ROWS_DOUBLE(r1, r0);
			if (0.0 == r0[0])
				return 0;
			/* eliminate first variable     */
			m1 = r1[0] / r0[0];
			m2 = r2[0] / r0[0];
			m3 = r3[0] / r0[0];
			s = r0[1];
			r1[1] -= m1 * s;
			r2[1] -= m2 * s;
			r3[1] -= m3 * s;
			s = r0[2];
			r1[2] -= m1 * s;
			r2[2] -= m2 * s;
			r3[2] -= m3 * s;
			s = r0[3];
			r1[3] -= m1 * s;
			r2[3] -= m2 * s;
			r3[3] -= m3 * s;
			s = r0[4];
			if (s != 0.0) {
				r1[4] -= m1 * s;
				r2[4] -= m2 * s;
				r3[4] -= m3 * s;
			}
			s = r0[5];
			if (s != 0.0) {
				r1[5] -= m1 * s;
				r2[5] -= m2 * s;
				r3[5] -= m3 * s;
			}
			s = r0[6];
			if (s != 0.0) {
				r1[6] -= m1 * s;
				r2[6] -= m2 * s;
				r3[6] -= m3 * s;
			}
			s = r0[7];
			if (s != 0.0) {
				r1[7] -= m1 * s;
				r2[7] -= m2 * s;
				r3[7] -= m3 * s;
			}
			/* choose pivot - or die */
			if (fabsf(r3[1]) > fabsf(r2[1]))
				SWAP_ROWS_DOUBLE(r3, r2);
			if (fabsf(r2[1]) > fabsf(r1[1]))
				SWAP_ROWS_DOUBLE(r2, r1);
			if (0.0 == r1[1])
				return 0;
			/* eliminate second variable */
			m2 = r2[1] / r1[1];
			m3 = r3[1] / r1[1];
			r2[2] -= m2 * r1[2];
			r3[2] -= m3 * r1[2];
			r2[3] -= m2 * r1[3];
			r3[3] -= m3 * r1[3];
			s = r1[4];
			if (0.0 != s) {
				r2[4] -= m2 * s;
				r3[4] -= m3 * s;
			}
			s = r1[5];
			if (0.0 != s) {
				r2[5] -= m2 * s;
				r3[5] -= m3 * s;
			}
			s = r1[6];
			if (0.0 != s) {
				r2[6] -= m2 * s;
				r3[6] -= m3 * s;
			}
			s = r1[7];
			if (0.0 != s) {
				r2[7] -= m2 * s;
				r3[7] -= m3 * s;
			}
			/* choose pivot - or die */
			if (fabsf(r3[2]) > fabsf(r2[2]))
				SWAP_ROWS_DOUBLE(r3, r2);
			if (0.0 == r2[2])
				return 0;
			/* eliminate third variable */
			m3 = r3[2] / r2[2];
			r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
				r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];
			/* last check */
			if (0.0 == r3[3])
				return 0;
			s = 1.0 / r3[3];		/* now back substitute row 3 */
			r3[4] *= s;
			r3[5] *= s;
			r3[6] *= s;
			r3[7] *= s;
			m2 = r2[3];			/* now back substitute row 2 */
			s = 1.0 / r2[2];
			r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
				r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
			m1 = r1[3];
			r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
				r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
			m0 = r0[3];
			r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
				r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
			m1 = r1[2];			/* now back substitute row 1 */
			s = 1.0 / r1[1];
			r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
				r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
			m0 = r0[2];
			r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
				r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
			m0 = r0[1];			/* now back substitute row 0 */
			s = 1.0 / r0[0];
			r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
				r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
			MAT(out, 0, 0) = r0[4];
			MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6];
			MAT(out, 0, 3) = r0[7], MAT(out, 1, 0) = r1[4];
			MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6];
			MAT(out, 1, 3) = r1[7], MAT(out, 2, 0) = r2[4];
			MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6];
			MAT(out, 2, 3) = r2[7], MAT(out, 3, 0) = r3[4];
			MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6];
			MAT(out, 3, 3) = r3[7];
			return 1;
		}




		int glhProjectf(float objx, float objy, float objz, double *modelview, double *projection, int *viewport, double *windowCoordinate)
		{
			//Transformation vectors
			float fTempo[8];
			//Modelview transform
			fTempo[0]=modelview[0]*objx+modelview[4]*objy+modelview[8]*objz+modelview[12];  //w is always 1
			fTempo[1]=modelview[1]*objx+modelview[5]*objy+modelview[9]*objz+modelview[13];
			fTempo[2]=modelview[2]*objx+modelview[6]*objy+modelview[10]*objz+modelview[14];
			fTempo[3]=modelview[3]*objx+modelview[7]*objy+modelview[11]*objz+modelview[15];
			//Projection transform, the final row of projection matrix is always [0 0 -1 0]
			//so we optimize for that.
			fTempo[4]=projection[0]*fTempo[0]+projection[4]*fTempo[1]+projection[8]*fTempo[2]+projection[12]*fTempo[3];
			fTempo[5]=projection[1]*fTempo[0]+projection[5]*fTempo[1]+projection[9]*fTempo[2]+projection[13]*fTempo[3];
			fTempo[6]=projection[2]*fTempo[0]+projection[6]*fTempo[1]+projection[10]*fTempo[2]+projection[14]*fTempo[3];
			fTempo[7]=-fTempo[2];
			//The result normalizes between -1 and 1
			if(fTempo[7]==0.0)	//The w value
				return 0;
			fTempo[7]=1.0/fTempo[7];
			//Perspective division
			fTempo[4]*=fTempo[7];
			fTempo[5]*=fTempo[7];
			fTempo[6]*=fTempo[7];
			//Window coordinates
			//Map x, y to range 0-1
			windowCoordinate[0]=(fTempo[4]*0.5+0.5)*viewport[2]+viewport[0];
			windowCoordinate[1]=(fTempo[5]*0.5+0.5)*viewport[3]+viewport[1];
			//This is only correct when glDepthRange(0.0, 1.0)
			windowCoordinate[2]=(1.0+fTempo[6])*0.5;	//Between 0 and 1
			return 1;
		}

		int glhUnProjectf(float winx, float winy, float winz, double *modelview, double *projection, int *viewport, double *objectCoordinate)
		{
			//Transformation matrices
			double m[16], A[16];
			double in[4], out[4];
			//Calculation for inverting a matrix, compute projection x modelview
			//and store in A[16]
			MultiplyMatrices4by4OpenGL_FLOAT(A, projection, modelview);
			//Now compute the inverse of matrix A
			if(glhInvertMatrixf2(A, m)==0)
				return 0;
			//Transformation of normalized coordinates between -1 and 1
			in[0]=(winx-(float)viewport[0])/(float)viewport[2]*2.0-1.0;
			in[1]=(winy-(float)viewport[1])/(float)viewport[3]*2.0-1.0;
			in[2]=2.0*winz-1.0;
			in[3]=1.0;
			//Objects coordinates
			MultiplyMatrixByVector4by4OpenGL_FLOAT(out, m, in);
			if(out[3]==0.0)
				return 0;
			out[3]=1.0/out[3];
			objectCoordinate[0]=out[0]*out[3];
			objectCoordinate[1]=out[1]*out[3];
			objectCoordinate[2]=out[2]*out[3];
			return 1;
		}

		

	};//end namespace GtOpenGL
};//end namespace GT
