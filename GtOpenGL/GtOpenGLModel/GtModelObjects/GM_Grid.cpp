/*
**	This file is part of the TridentCAD
**	This software was merged and developed by:
**	
**  Anthony Daniels
**
**  TridentCAD is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to TridentCAD.
**
**  TridentCAD is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with TridentCAD.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)


#include ".\GM_Grid.h"

namespace GT
{
	namespace GtOpenGL
	{

		GM_Grid::GM_Grid()
			: GtCadObject()
		{
			//set the grid color to default dark gray
			this->m_objCurveMaterial.m_objDiffuseColor.SetRGB(50,50,50,255);
			this->m_objCurveMaterial.m_objSpecularColor.SetRGB(0,0,0,255);
			//set default for plane orientation
			this->m_objPlane = XYPLANE;
			this->m_dblSize = 10.0f;
			this->m_dblDelta = 1.0f;
		};

		GM_Grid::~GM_Grid()
		{

		};

		void GM_Grid::Set_objPlane(GtPlaneType objPlane)
		{
			this->m_objPlane = objPlane;
		};

		GtPlaneType GM_Grid::Get_objPlane(void) const
		{
			return m_objPlane;
		};

		//Set and Get for the custom display plane
		void GM_Grid::Set_objCustomPlane(GtPlane objPlane)
		{
			this->m_objCustomPlane = objPlane;
		};

		GtPlane GM_Grid::Get_objCustomPlane(void) const
		{
			return m_objCustomPlane;
		};

		//Set and Get for the dblSize 
		void GM_Grid::Set_dblSize(double dblSize)
		{
			this->m_dblSize = dblSize;
		};

		double GM_Grid::Get_dblSize(void) const
		{
			return m_dblSize;
		};

		//Set and Get for the object render override 
		void GM_Grid::Set_dblDelta(double dblDelta)
		{
			this->m_dblDelta = dblDelta;
		};

		double GM_Grid::Get_dblDelta(void) const
		{
			return m_dblDelta;
		};
		//render the grid
		void GM_Grid::RenderModelItem(const GtViewpoint & ptrCurrViewPoint, GtRenderMode enumRenderMode)
		{
			GtPoint3DF objOrigin,objNormal,objUpDir;
			objUpDir.Set(0.0f,0.0f,1.0f);
			switch(this->m_objPlane)
			{
			case XYPLANE:
				{
					objOrigin.Set(0.0f,0.0f,0.0f);//WCSORIGIN
					objNormal.Set(0.0f,0.0f,1.0f);//Z
					objUpDir.Set(0.0f,1.0f,0.0f);//Y
					break;
				};
			case XZPLANE:
				{
					objOrigin.Set(0.0f,0.0f,0.0f);//WCSORIGIN
					objNormal.Set(0.0f,1.0f,0.0f);//Y
					objUpDir.Set(0.0f,0.0f,1.0f);//Z

					break;
				};
			case YZPLANE:
				{
					objOrigin.Set(0.0f,0.0f,0.0f);//WCSORIGIN
					objNormal.Set(1.0f,0.0f,0.0f);//X
					objUpDir.Set(0.0f,0.0f,1.0f);//Z
					break;
				};
			case CUSTOMPLANE:
				{
					objOrigin = this->m_objCustomPlane.m_objOrigin;
					objNormal = this->m_objCustomPlane.m_objNormal;
					objUpDir.Set(0.0f,1.0f,0.0f);//Z
					break;
				};
			default:
				{
					//default is XYPLANE
					objOrigin.Set(0.0f,0.0f,0.0f);//WCSORIGIN
					objNormal.Set(0.0f,0.0f,1.0f);//Z
					objUpDir.Set(0.0f,1.0f,0.0f);//Y
					break;
				};
			}//end switch on orientation
			this->RenderGrid(objOrigin,objNormal,objUpDir);

		}

		void GM_Grid::RenderOverlay(const GtViewpoint & ptrCurrViewPoint)
		{
			return;
		};

		void GM_Grid::RenderGrid(GtPoint3DF objOrigin, GtPoint3DF objNormal, GtPoint3DF objUpDir)
		{
			int i,intNumSteps;
			GtPoint3DF objPosStart,objPosEnd,objNegStart,objNegEnd;

			objNormal.Normalize();
			objUpDir.Normalize();
			GtPoint3DF objRightDir = GtMath::Cross3D(objNormal,objUpDir);
			objRightDir.Normalize();

			// disable lighting
			glDisable(GL_LIGHTING);
			glMatrixMode(GL_MODELVIEW);
			//PUSH MODEL VIEW MATRIX
			glPushMatrix();
			GtColor objGridColor = this->m_objCurveMaterial.m_objDiffuseColor;
			glColor3f(objGridColor.UnitRed(), objGridColor.UnitGreen(),objGridColor.UnitBlue());


			//find how many steps in size

			intNumSteps = gRound(ceil(m_dblSize / m_dblDelta));//ensures even number of steps

			//create horizontal lines
			for(i = 0 ; i < intNumSteps + 1; i++)
			{	

				objPosStart.x = objOrigin.x + (-m_dblSize * objRightDir.x) + (i * m_dblDelta* objUpDir.x);
				objPosStart.y = objOrigin.y + (-m_dblSize * objRightDir.y) + (i * m_dblDelta* objUpDir.y);
				objPosStart.z = objOrigin.z + (-m_dblSize * objRightDir.z) + (i * m_dblDelta* objUpDir.z);

				objPosEnd.x = objOrigin.x + (m_dblSize * objRightDir.x) + (i * m_dblDelta* objUpDir.x);
				objPosEnd.y = objOrigin.y + (m_dblSize * objRightDir.y) + (i * m_dblDelta* objUpDir.y);
				objPosEnd.z = objOrigin.z + (m_dblSize * objRightDir.z) + (i * m_dblDelta* objUpDir.z);

				glBegin(GL_LINES);
				glVertex3f(float(objPosStart.x),float(objPosStart.y),float(objPosStart.z));
				glVertex3f(float(objPosEnd.x),float(objPosEnd.y),float(objPosEnd.z));
				glEnd();

				objNegStart.x = objOrigin.x + (-m_dblSize * objRightDir.x) + (-i * m_dblDelta* objUpDir.x);
				objNegStart.y = objOrigin.y + (-m_dblSize * objRightDir.y) + (-i * m_dblDelta* objUpDir.y);
				objNegStart.z = objOrigin.z + (-m_dblSize * objRightDir.z) + (-i * m_dblDelta* objUpDir.z);

				objNegEnd.x = objOrigin.x + (m_dblSize * objRightDir.x) + (-i * m_dblDelta* objUpDir.x);
				objNegEnd.y = objOrigin.y + (m_dblSize * objRightDir.y) + (-i * m_dblDelta* objUpDir.y);
				objNegEnd.z = objOrigin.z + (m_dblSize * objRightDir.z) + (-i * m_dblDelta* objUpDir.z);

				glBegin(GL_LINES);
				glVertex3f(float(objNegStart.x),float(objNegStart.y),float(objNegStart.z));
				glVertex3f(float(objNegEnd.x),float(objNegEnd.y),float(objNegEnd.z));
				glEnd();
			};

			//create the vertical lines

			for(i = 0 ; i < intNumSteps + 1; i++)
			{	

				objPosStart.x = objOrigin.x + (-m_dblSize * objUpDir.x) + (i * m_dblDelta* objRightDir.x);
				objPosStart.y = objOrigin.y + (-m_dblSize * objUpDir.y) + (i * m_dblDelta* objRightDir.y);
				objPosStart.z = objOrigin.z + (-m_dblSize * objUpDir.z) + (i * m_dblDelta* objRightDir.z);

				objPosEnd.x = objOrigin.x + (m_dblSize * objUpDir.x) + (i * m_dblDelta* objRightDir.x);
				objPosEnd.y = objOrigin.y + (m_dblSize * objUpDir.y) + (i * m_dblDelta* objRightDir.y);
				objPosEnd.z = objOrigin.z + (m_dblSize * objUpDir.z) + (i * m_dblDelta* objRightDir.z);

				glBegin(GL_LINES);
				glVertex3f(float(objPosStart.x),float(objPosStart.y),float(objPosStart.z));
				glVertex3f(float(objPosEnd.x),float(objPosEnd.y),float(objPosEnd.z));
				glEnd();

				objNegStart.x = objOrigin.x + (-m_dblSize * objUpDir.x) + (-(i * m_dblDelta)* objRightDir.x);
				objNegStart.y = objOrigin.y + (-m_dblSize * objUpDir.y) + (-(i * m_dblDelta)* objRightDir.y);
				objNegStart.z = objOrigin.z + (-m_dblSize * objUpDir.z) + (-(i * m_dblDelta)* objRightDir.z);

				objNegEnd.x = objOrigin.x + (m_dblSize * objUpDir.x) + (-(i * m_dblDelta)* objRightDir.x);
				objNegEnd.y = objOrigin.y + (m_dblSize * objUpDir.y) + (-(i * m_dblDelta)* objRightDir.y);
				objNegEnd.z = objOrigin.z + (m_dblSize * objUpDir.z) + (-(i * m_dblDelta)* objRightDir.z);

				glBegin(GL_LINES);
				glVertex3f(float(objNegStart.x),float(objNegStart.y),float(objNegStart.z));
				glVertex3f(float(objNegEnd.x),float(objNegEnd.y),float(objNegEnd.z));
				glEnd();
			};
			//POP MODEL VIEW MATRIX
			glPopMatrix();
			// enable lighting back
			glEnable(GL_LIGHTING);
			glMatrixMode(GL_MODELVIEW);
		};

	};//end namespace GtOpenGL
};//end namespace GT