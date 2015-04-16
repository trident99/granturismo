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

#ifndef GT_OPENGL_LIB_REFS_H
#define GT_OPENGL_LIB_REFS_H



//custom macros
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h> 
	//#include <GL\glut32.h>
	//#include <GL\glaux.h>
#endif

#ifndef OPENGL_GT_INCLUDES
	#define OPENGL_GT_INCLUDES
	#include <modGtBase.h>
	#include <modGtMath.h>
	#include <modGtGeometry.h>
	#include <modGtGraphic.h>
	using namespace GT::GtCore;
#endif

#ifndef OPENGL_HTL_INCLUDES
	#define OPENGL_HTL_INCLUDES
	#include <modHtlGlobal.h>
	#include <modHtlBase.h>
	using namespace HTL;
#endif


#endif //GT_OPENGL_LIB_REFS_H