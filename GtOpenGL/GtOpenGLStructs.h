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
#ifndef GT_OPENGL_STRUCTS_H
#define GT_OPENGL_STRUCTS_H

#include ".\GtOpenGLEnums.h"

namespace GT
{

	namespace GtOpenGL
	{

		//!GtHitRecord is used in item selection and handling.  It allows hits from a pick ray to be sorted by distance
		struct HTL_EXPORT GtHitRecord
		{
		public:
			GtHitRecord(void)
			{
				m_intSelIndex = -1;
				m_blnHit = false;
				m_dblHitDist = 0.0f;
			};
			//!Selection Index of hit
			size_t m_intSelIndex;
			//!Boolean Flag of Hit
			bool m_blnHit;
			//!Hit Distance
			double m_dblHitDist;
		};



		struct HTL_EXPORT GtViewpoint
		{
		public:
			GtViewpoint();
			//name of the viewpoint
			std::string m_strViewpointName;
			//!the center of rotation
			GtPoint3DF m_objRotationCentroid;
			//!the translation of the viewpoint from the center of rotation
			GtPoint3DF m_objViewLocation;
			GtPoint3DF m_objUpDir;
			//!the X, Y, Z rotation angles
			GtPoint3DF m_objRotation;
			//!Current mouse location in world space on screen
			GtPoint3DF m_objMouseLoc;
			//!Camera Look Direction Vectors
			GtPoint3DF m_objXDir;
			GtPoint3DF m_objYDir;
			GtPoint3DF m_objZDir;
			//!Field of View Angle for perspective projection
			float m_sngFieldOfViewAngle;
			//!View Frustrum Near Field Distance
			float m_sngZNearFieldDist;
			//!View Frustrum Far Field Distance
			float m_sngZFarFieldDist;
			//!Viewport Width
			float m_sngWidth;
			//!Viewport Height
			float m_sngHeight;
			//!Pointer to the QPainter for the overlay graphics
			GtPainter* m_ptrPainter;

			//!Current Viewport coordinates
			int m_arrIntViewport[4];
			//!Current Viewport Model Transformation Matrix
			double m_arrDblCurrModelMatrix[16];
			//!Current Viewport Projection Transformation Matrix
			double m_arrDblCurrProjMatrix[16];
		};
	};//end namespace GtOpenGL
};//end namespace GT
#endif