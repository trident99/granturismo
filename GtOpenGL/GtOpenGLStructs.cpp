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

#include ".\GtOpenGLStructs.h"
namespace GT
{
	namespace GtOpenGL
	{

		GtViewpoint::GtViewpoint()
		{
			m_strViewpointName = "";
			m_objRotationCentroid.Zero();
			m_objViewLocation.Zero();
			m_objRotation.Zero();
			m_objUpDir.Zero();
			m_objUpDir.z = 1.0f;

			m_objXDir.Zero();
			m_objXDir.x = 1.0f;

			m_objYDir.Zero();
			m_objYDir.y = 1.0f;

			m_objZDir.Zero();
			m_objZDir.z = 1.0f;

			m_sngFieldOfViewAngle = 45.0f;
			m_sngZNearFieldDist = 0.1f;
			m_sngZFarFieldDist = 1000.0f;
			m_sngWidth = 740;
			m_sngHeight = 480;
			//column major model matrix
			m_arrDblCurrModelMatrix[0] = 0.0f; m_arrDblCurrModelMatrix[4] = 0.0f; m_arrDblCurrModelMatrix[8] = 0.0f;  m_arrDblCurrModelMatrix[12] = 0.0f;
			m_arrDblCurrModelMatrix[1] = 0.0f; m_arrDblCurrModelMatrix[5] = 0.0f; m_arrDblCurrModelMatrix[9] = 0.0f;  m_arrDblCurrModelMatrix[13] = 0.0f;
			m_arrDblCurrModelMatrix[2] = 0.0f; m_arrDblCurrModelMatrix[6] = 0.0f; m_arrDblCurrModelMatrix[10] = 0.0f; m_arrDblCurrModelMatrix[14] = 0.0f;
			m_arrDblCurrModelMatrix[3] = 0.0f; m_arrDblCurrModelMatrix[7] = 0.0f; m_arrDblCurrModelMatrix[11] = 0.0f; m_arrDblCurrModelMatrix[15] = 0.0f;
			//column major view matrix
			m_arrDblCurrProjMatrix[0] = 0.0f; m_arrDblCurrProjMatrix[4] = 0.0f; m_arrDblCurrProjMatrix[8] = 0.0f;  m_arrDblCurrProjMatrix[12] = 0.0f;
			m_arrDblCurrProjMatrix[1] = 0.0f; m_arrDblCurrProjMatrix[5] = 0.0f; m_arrDblCurrProjMatrix[9] = 0.0f;  m_arrDblCurrProjMatrix[13] = 0.0f;
			m_arrDblCurrProjMatrix[2] = 0.0f; m_arrDblCurrProjMatrix[6] = 0.0f; m_arrDblCurrProjMatrix[10] = 0.0f; m_arrDblCurrProjMatrix[14] = 0.0f;
			m_arrDblCurrProjMatrix[3] = 0.0f; m_arrDblCurrProjMatrix[7] = 0.0f; m_arrDblCurrProjMatrix[11] = 0.0f; m_arrDblCurrProjMatrix[15] = 0.0f;
			//viewport 
			m_arrIntViewport[0] = 0;
			m_arrIntViewport[1] = 0;
			m_arrIntViewport[2] = 0;
			m_arrIntViewport[3] = 0;
			//painter pointer
			m_ptrPainter = NULL;

		};
	};//end namespace GtOpenGL

};//end namespace GT