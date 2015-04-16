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

#include ".\GtOpenGLEnums.h"
namespace GT
{
	namespace GtOpenGL
	{
		// Create a string with last error message
		std::string GetLastErrorStdStr()
		{
			DWORD error = GetLastError();
			if (error)
			{
				LPVOID lpMsgBuf;
				DWORD bufLen = FormatMessage(
					FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					error,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR) &lpMsgBuf,
					0, NULL );
				if (bufLen)
				{
					LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
					std::string result(lpMsgStr, lpMsgStr+bufLen);

					LocalFree(lpMsgBuf);

					return result;
				}
			}
			return std::string();
		};

	};//end namespace GtOpenGL
};//end namespace GT

namespace HTL{

	template <>
	void enumToString<GtProjectionMode>(GtProjectionMode enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
				//HTL CPLUSPLUS NATIVE TYPES
			case Perspective: {strReturn = "Perspective";  return; break;};
			case Orthographic: {strReturn = "Orthographic";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "Orthographic";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;
	};
	
	template <>
	void stringToEnum<GtProjectionMode>(std::string & strVal, GtProjectionMode & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = Orthographic; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "Perspective"){enumValReturn = Perspective; return;};
			if(strVal == "Orthographic"){enumValReturn = Orthographic; return;};
			//DEFUALT UNKNOWN
			enumValReturn = Orthographic;
			return;
		}catch(...){
			enumValReturn = Orthographic;
			return;
		};
	};


	template <>
	void enumToString<GtRenderMode>(GtRenderMode enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
				//HTL CPLUSPLUS NATIVE TYPES
			case CurvesOnly: {strReturn = "CurvesOnly";  return; break;};
			case CurvesWithMesh: {strReturn = "CurvesWithMesh";  return; break;};
			case Shaded: {strReturn = "Shaded";  return; break;};
			case ShadedWithCurves: {strReturn = "ShadedWithCurves";  return; break;};
			case ShadedWithMesh: {strReturn = "ShadedWithMesh";  return; break;};
			case ShadedBoundary: {strReturn = "ShadedBoundary";  return; break;};
			case ShadeSelected: {strReturn = "ShadeSelected";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "ShadedWithCurves";  return; break;};
			};
		}catch(...){
			strReturn = "";
		};
		return;
	};
	
	template <>
	void stringToEnum<GtRenderMode>(std::string & strVal, GtRenderMode & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = ShadedWithCurves; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "CurvesOnly"){enumValReturn = CurvesOnly; return;};
			if(strVal == "CurvesWithMesh"){enumValReturn = CurvesWithMesh; return;};
			if(strVal == "Shaded"){enumValReturn = Shaded; return;};
			if(strVal == "ShadedWithCurves"){enumValReturn = ShadedWithCurves; return;};
			if(strVal == "ShadedWithMesh"){enumValReturn = ShadedWithMesh; return;};
			if(strVal == "ShadedBoundary"){enumValReturn = ShadedBoundary; return;};
			if(strVal == "ShadeSelected"){enumValReturn = ShadeSelected; return;};
			//DEFUALT UNKNOWN
			enumValReturn = ShadedWithCurves;
			return;
		}catch(...){
			enumValReturn = ShadedWithCurves;
			return;
		};
	};

	template <>
	void enumToString<GtPlaneType>(GtPlaneType enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
				//HTL CPLUSPLUS NATIVE TYPES
			case XYPLANE: {strReturn = "XYPLANE";  return; break;};
			case XZPLANE: {strReturn = "XZPLANE";  return; break;};
			case YZPLANE: {strReturn = "YZPLANE";  return; break;};
			case CUSTOMPLANE: {strReturn = "CUSTOMPLANE";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "CUSTOMPLANE";  return; break;};
			};
		}catch(...){
			strReturn = "";
		};
		return;
	};
	
	template <>
	void stringToEnum<GtPlaneType>(std::string & strVal, GtPlaneType & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = CUSTOMPLANE; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "XYPLANE"){enumValReturn = XYPLANE; return;};
			if(strVal == "XZPLANE"){enumValReturn = XZPLANE; return;};
			if(strVal == "YZPLANE"){enumValReturn = YZPLANE; return;};
			if(strVal == "CUSTOMPLANE"){enumValReturn = CUSTOMPLANE; return;};
			//DEFUALT UNKNOWN
			enumValReturn = CUSTOMPLANE;
			return;
		}catch(...){
			enumValReturn = CUSTOMPLANE;
			return;
		};
	};



	template <>
	void enumToString<GtOriginType>(GtOriginType enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
				//HTL CPLUSPLUS NATIVE TYPES
			case CENTROID: {strReturn = "CENTROID";  return; break;};
			case BOTTOMCENTROID: {strReturn = "BOTTOMCENTROID";  return; break;};
			case TOPCENTROID: {strReturn = "TOPCENTROID";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "CENTROID";  return; break;};
			};
		}catch(...){
			strReturn = "";
		};
		return;
	};
	
	template <>
	void stringToEnum<GtOriginType>(std::string & strVal, GtOriginType & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = CENTROID; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "CENTROID"){enumValReturn = CENTROID; return;};
			if(strVal == "BOTTOMCENTROID"){enumValReturn = BOTTOMCENTROID; return;};
			if(strVal == "TOPCENTROID"){enumValReturn = TOPCENTROID; return;};
			//DEFUALT UNKNOWN
			enumValReturn = CENTROID;
			return;
		}catch(...){
			enumValReturn = CENTROID;
			return;
		};
	};

};//end namespace HTL