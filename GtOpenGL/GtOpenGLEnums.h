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
#ifndef GT_OPENGL_ENUMS_H
#define GT_OPENGL_ENUMS_H
#include ".\GtOpenGLLibRefs.h"

namespace GT{

	namespace GtOpenGL
	{
		// Create a string with last error message
		HTL_DLLAPI std::string GetLastErrorStdStr();

		//!Projection Mode for OpenGL
		enum HTL_DLLAPI GtProjectionMode
		{
			Perspective = 0,
			Orthographic = 1,
		};

		//!Render Mode for viewer
		enum HTL_DLLAPI GtRenderMode
		{
			CurvesOnly = 0,
			CurvesWithMesh = 1,
			Shaded = 2,
			ShadedWithMesh = 3,
			ShadedWithCurves= 4,
			ShadedBoundary = 5,
			ShadeSelected = 6
		};

		//!Enumerated Plane Description
		enum HTL_DLLAPI GtPlaneType
		{
			XYPLANE = 0,
			XZPLANE = 1,
			YZPLANE = 2,
			CUSTOMPLANE = 4
		};

		enum HTL_DLLAPI GtOriginType
		{
			CENTROID = 0,
			BOTTOMCENTROID = 1,
			TOPCENTROID = 2
		};

	};//end namspace GtOpenGL
};//end namespace GT

using namespace GT::GtOpenGL;

namespace HTL
{
	//enum to string and string to enum translators
	//GtProjectionMode////////////////////////////////////////
	template <>
	HTL_EXPORT void enumToString<GtProjectionMode>(GtProjectionMode enumVal, std::string & strReturn);
	
	template <>
	HTL_EXPORT void stringToEnum<GtProjectionMode>(std::string & strVal, GtProjectionMode & enumValReturn);

	//GtRenderMode////////////////////////////////////////////
	template <>
	HTL_EXPORT void enumToString<GtRenderMode>(GtRenderMode enumVal, std::string & strReturn);
	
	template <>
	HTL_EXPORT void stringToEnum<GtRenderMode>(std::string & strVal, GtRenderMode & enumValReturn);

	//GtPlaneType////////////////////////////////////////////
	template <>
	HTL_EXPORT void enumToString<GtPlaneType>(GtPlaneType enumVal, std::string & strReturn);
	
	template <>
	HTL_EXPORT void stringToEnum<GtPlaneType>(std::string & strVal, GtPlaneType & enumValReturn);

	//GtOriginType//////////////////////////////////////////
	template <>
	HTL_EXPORT void enumToString<GtOriginType>(GtOriginType enumVal, std::string & strReturn);
	
	template <>
	HTL_EXPORT void stringToEnum<GtOriginType>(std::string & strVal, GtOriginType & enumValReturn);


};//end namespace HTL




#endif