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

#ifndef GT_OPENGL_WIDGET_H
#define GT_OPENGL_WIDGET_H

#include ".\GtOpenGLStructs.h"

namespace GT
{
	namespace GtOpenGL
	{

		class HTL_DLLAPI GtOpenGLWidget : public GtWidget
		{
		public:
			//!Parent set constructor
			GtOpenGLWidget(GtObject* ptrParent = NULL , HWND pWndParent = NULL);
			//!Virtual destructor
			virtual ~GtOpenGLWidget(void);

		public:
			//Last viewpoint coordinate information
			GTOBJECT_MEMVAR_BYREF(public, GtViewpoint, objLastViewpoint);
			//!String name for the object
			GTOBJECT_MEMVAR_BYREF(public, GtViewpoint, objCurrViewpoint);
			//!String name for the object
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnInitialized);
		public:
			bool SetParentGL(HWND pWndParent = NULL);
			void EndGL(void);
			//!The rectangle geometry for the widget
			virtual void Set_objFrame(GtRectI & frame);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent){return 0;};
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);
		protected:
			//initialize the opengl window
			virtual void InitializeGL(void);
			//Resize the opengl window
			virtual void ResizeGL(GtRectI & frame);
			//!Paint the opengl graphics
			virtual void PaintGL(void);
			//!Paint the overlay graphics
			virtual void PaintOverlayGL(GtPainter * ptrPainter = NULL);

			virtual bool SetupPixelFormat(HDC hDC);

		protected:
			HWND	m_hParentWnd;
			HGLRC	m_hglrc;
			HDC		m_hDC;
			HGLRC	m_hPrevRC;
			bool    m_bNewRCCreated;
			bool    m_bWeCreatedDC;

			DWORD	m_dwRenderingTime;
			DWORD	m_dwStartRenderingTime;
			bool	m_bFullScreen;
			int		m_nMode;


		};

	};//end namespace GtOpenGL

};//end namespace GT

#endif //GT_OPENGL_WIDGET_H