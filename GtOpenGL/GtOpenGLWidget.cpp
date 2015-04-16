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

#include ".\GtOpenGLWidget.h"
#include <GtProcess\GtApplication.h>
#include <modGtEvent.h>

namespace GT
{
	namespace GtOpenGL
	{
		void WriteOpenGLPixelsToHBITMAP( HBITMAP dstHBITMAP, HDC dstDC, GtCanvas & cv );
		LRESULT CALLBACK WndWidgetProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		//default constructor
		GtOpenGLWidget::GtOpenGLWidget(GtObject* ptrParent, HWND pWndParent)
			: GtWidget(ptrParent)
		{
			m_strType = "GtOpenGLWidget";

			m_hParentWnd = pWndParent;
			m_hglrc = NULL;
			m_hDC = NULL;
			m_hPrevRC = NULL;
			m_bNewRCCreated = false;
			m_bWeCreatedDC = false;

			m_dwRenderingTime = 0;
			m_dwStartRenderingTime = 0;
			m_bFullScreen = false;
			m_nMode = 0;

			m_blnInitialized = false;


			////Set up window class
			//WNDCLASS wnd;
			//wnd.cbClsExtra = 0;
			//wnd.cbWndExtra = 0;
			//wnd.hCursor = LoadCursor(0, IDC_ARROW);
			//wnd.hIcon = LoadIcon(0, IDI_WINLOGO);
			//wnd.lpszMenuName = 0;
			//wnd.style = CS_OWNDC;
			//wnd.hbrBackground = 0;
			//wnd.lpfnWndProc = WndWidgetProc;//no window procedure
			//wnd.hInstance = GetModuleHandle(NULL);
			//wnd.lpszClassName = L"GtOpenGLWidget";

			////Register window class
			//RegisterClass(&wnd);

			//
			//this->m_winID = CreateWindow(
			//	L"GtOpenGLWidget",      /* Classname */
			//	L"View",       /* Title Text */
			//	(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS),  /* default window */
			//	CW_USEDEFAULT,        /* Windows decides the position */
			//	CW_USEDEFAULT,        /* where the window ends up on the screen */
			//	100,                  /* The programs width */
			//	100,                  /* and height in pixels */
			//	pWndParent,         /* The window is a child-window to desktop */
			//	NULL,                 /* No menu */
			//	GetModuleHandle(NULL), /* Program Instance handler */
			//	NULL                  /* No Window Creation data */
			//	);

			//ShowWindow(m_winID,SW_HIDE);
			//UpdateWindow(m_winID);

			////register with Application HWND server 
			//GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
			//if(ptrApp)
			//{
			//	ptrApp->RegisterHandle(m_winID,this);
			//}

			m_hDC = GetDC(pWndParent);
			//this->SetupPixelFormat(m_hDC);
			this->SetParentGL(NULL);

		};
		//virtual destructor
		GtOpenGLWidget::~GtOpenGLWidget(void)
		{
			this->EndGL();
			return;
		};
			
		//!Custom Widget Painting
		int GtOpenGLWidget::OnPaint(GtPainter * painter)
		{
			if(!m_blnVisible){return 0;};//on off check
			if(!painter){return 0;};//safety check
			//painter->GtEndPainting();
			//end GDI to paint OpenGL

			if(!m_blnInitialized)
			{
				this->InitializeGL();
			}

			GtCanvas glCanvas;
			glCanvas.m_view = m_objFrame;
			glCanvas.m_frame = m_objFrame;
			glCanvas.m_delta.x = 0;
			glCanvas.m_delta.y = 0;

			glCanvas.m_dest.x = m_objFrame.xMin;
			glCanvas.m_dest.y = m_objFrame.yMin;
			//draw the frame
			painter->GtDrawFrame(m_objFrame);

			//do the opengl painting
			this->PaintGL();
			//rebegin GDI to paint overlays

			WriteOpenGLPixelsToHBITMAP(painter->GetCurrBitmap(),painter->GetCurrHDC(),glCanvas);

			//SwapBuffers(m_hDC);
			wglMakeCurrent(NULL, NULL);

			//paint overlays second
			this->PaintOverlayGL(painter);

			//paint subwidgets such as menus, buttons, etc.
			GtWidget::OnPaint(painter);
			return 1;
		};

		void GtOpenGLWidget::Set_objFrame(GtRectI & frame)
		{
			GtWidget::Set_objFrame(frame);
			//now sync the window
			RECT rect;
			
			rect.left = frame.xMin;
			rect.right = frame.xMax;
			rect.top = frame.yMin;
			rect.bottom = frame.yMax;
			//resize the window
			SetWindowPos(m_winID,HWND_TOP,rect.left,rect.top,
				frame.Width(),frame.Height(),SWP_SHOWWINDOW);

			this->ResizeGL(frame);
			this->InitializeGL();

			ShowWindow(m_winID,SW_SHOW);
			this->PostPaint();
		};

		//initialize the opengl window
		void GtOpenGLWidget::InitializeGL(void)
		{

		};



		void GtOpenGLWidget::ResizeGL(GtRectI & frame)// Resize And Initialize The GL Window
		{
			if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
			{
				std::string strErr = GetLastErrorStdStr();
				return;
			}

			int height = frame.Height();
			int width = frame.Width();
			if (height == 0)										// Prevent A Divide By Zero By
			{
				height += 1;										// Making Height Equal One
			}
			glViewport(frame.xMin, frame.yMin, width, height);
			//glViewport(0, 0, width, height);// Reset The Current Viewport
			this->m_objCurrViewpoint.m_sngFieldOfViewAngle = 45.0f;
			this->m_objCurrViewpoint.m_sngHeight = (float)height;
			this->m_objCurrViewpoint.m_sngWidth = (float)width;
			this->m_objCurrViewpoint.m_sngZNearFieldDist = 0.1f;
			this->m_objCurrViewpoint.m_sngZFarFieldDist = 1000.0f;
			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();									// Reset The Projection Matrix

			// Calculate The Aspect Ratio Of The Window
			gluPerspective(this->m_objCurrViewpoint.m_sngFieldOfViewAngle,
				(GLdouble)width/(GLdouble)height,
				this->m_objCurrViewpoint.m_sngZNearFieldDist,
				this->m_objCurrViewpoint.m_sngZFarFieldDist); //if zNear is 0.0, then overlaps render with color interferences

			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glLoadIdentity();									// Reset The Modelview Matrix
			wglMakeCurrent(NULL,NULL);
			return;
		}
		//!Paint the opengl graphics
		void GtOpenGLWidget::PaintGL(void)
		{
			if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
			{
				std::string strErr = GetLastErrorStdStr();
				return;
			}
			//ENTER ALL OPENGL PAINTING CODE HERE
		};
		//!Paint the overlay graphics
		void GtOpenGLWidget::PaintOverlayGL(GtPainter * painter)
		{
			//ENTER ALL 2D OVERLAY GRAPHICS PAINTING HERE
		};


		bool GtOpenGLWidget::SetParentGL(HWND pWndParent)
		{


			// If NULL is passed instead of a valid DC,
			// it is a request to create a DC for last used window.
			// Pass NULL if you want to make last used window RC current again.
			//if(pWndParent)
			//{
			//	//m_hParentWnd = pWndParent;
			m_hDC = GetDC(m_hParentWnd);
			//}else{return false;};

			PIXELFORMATDESCRIPTOR  pfd;
			int  iPixelFormat;

			// get the current pixel format index  
			iPixelFormat = GetPixelFormat(m_hDC); 

			// obtain a detailed description of that pixel format  
			DescribePixelFormat(m_hDC, iPixelFormat, 
				sizeof(PIXELFORMATDESCRIPTOR), &pfd);
		

			RECT inval;
			inval.left = m_objFrame.xMin;
			inval.right = m_objFrame.xMax;
			inval.top = m_objFrame.yMin;
			inval.bottom = m_objFrame.yMax;
			::InvalidateRect(m_hParentWnd,&inval,FALSE);

			// Make sure that previous RC is inactivated.
			wglMakeCurrent(m_hDC, NULL);

			if((m_hglrc = wglCreateContext(m_hDC)) == NULL)
			{
				std::string strErr = GetLastErrorStdStr();
				return 0;
			}

			if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
			{
				std::string strErr = GetLastErrorStdStr();
				return 0;
			}
			m_dwStartRenderingTime = GetTickCount();
			return true;
		};


		DWORD GetTimeDif(DWORD dwStartTime)
		{
			DWORD dwTickCount = GetTickCount();
			if(dwTickCount < dwStartTime)
				return dwTickCount + 0xFFFFFFFF - dwStartTime;
			return dwTickCount - dwStartTime;
		};

		void GtOpenGLWidget::EndGL(void)
		{
			// Synchronize access to surface
			// ( on Win95 may be remove to increased performance)
			glFlush();
			//SwapBuffers(m_hDC);
			// Free currently selected OpenGL RC, 
			// so the other window belonging to
			// this thread may also do the OpenGL rendering.
			wglMakeCurrent(m_hDC, NULL);//make not current
			wglDeleteContext(m_hglrc);//delete the resource
			m_dwRenderingTime = GetTimeDif(m_dwStartRenderingTime);
			if(m_dwRenderingTime == 0)
				m_dwRenderingTime = 10;  
			
			return;
		};


		bool GtOpenGLWidget::SetupPixelFormat(HDC hDC)
		{
			//set up for OpenGL
			PIXELFORMATDESCRIPTOR m_pfd;

			memset(&m_pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

			m_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			m_pfd.nVersion = 1;
			m_pfd.dwFlags = (PFD_DRAW_TO_WINDOW  | PFD_SUPPORT_OPENGL |
				PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER);
			m_pfd.iPixelType = PFD_TYPE_RGBA;
			m_pfd.cColorBits = 32;
			m_pfd.cDepthBits = 24;
			m_pfd.iLayerType = PFD_MAIN_PLANE;

			int iPixelFormat = ChoosePixelFormat(m_hDC, &m_pfd);

			if(iPixelFormat == 0)
			{
				//ErrorLog.SetString("ChoosePixelFormat failed!");
				return false;
			}

			if(SetPixelFormat(m_hDC, iPixelFormat, &m_pfd) == FALSE)
			{
				//ErrorLog.SetString("SetPixelFormat failed!");
				return false;
			}

			return true;
		}

		HtlSpinLock g_ProcLock;
		using namespace GT::GtCore;
		//WndProc function
		LRESULT CALLBACK WndWidgetProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{

			switch(msg)
			{
			//case WM_MOUSEMOVE:
			case WM_PAINT:
				{
					GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
					if(ptrApp)
					{
						GtWidget* ptrWidget = dynamic_cast<GtWidget*>(ptrApp->GetHandleObject(hWnd));
						if(ptrWidget)
						{
							ptrWidget->PostPaint();
						}
					}
					//local paint to diffuse infinite paint calls
					HDC ptrHDC;
					PAINTSTRUCT ptrPaint;						
					ptrHDC = ::BeginPaint(hWnd, &ptrPaint);
					::EndPaint(hWnd, &ptrPaint);
					return 0;
				}
			case WM_CLOSE:
				{			
					
					return 0;
					break;
				}
			case WM_DESTROY:
				{			
					//PostQuitMessage(0);
					return 0;
					break;
				}
			}
			HtlGUID128 lockNull;
			//g_ProcLock.lock(lockNull);
			MSG currMsg;
			//PeekMessage(&currMsg,hWnd,0,0,PM_REMOVE);
			currMsg.message = msg;
			currMsg.wParam = wParam;
			currMsg.lParam = lParam;
			GtEvent currEvent;
			currEvent = CreateGtEvent(currMsg);


			if(currEvent.m_objType != EventUnknown)
			{
				if(currEvent.m_objType == MouseWheel)
				{
					int z = 10;
				}
				GtApplication * ptrApp = GtApplication::GetAppInstancePtr();
				if(ptrApp)
				{
					GtWidget* ptrWidget = dynamic_cast<GtWidget*>(ptrApp->GetHandleObject(hWnd));
					if(ptrWidget)
					{
						ptrWidget->HandleEvent(&currEvent);
					}
				}
			}
			//standard windows processing
			//TranslateMessage(&currMsg);
			//DispatchMessage(&currMsg);
			//g_ProcLock.unlock(lockNull);

			return DefWindowProc(hWnd, msg, wParam, lParam);
		}


		void WriteOpenGLPixelsToHBITMAP( HBITMAP dstHBITMAP, HDC dstDC, GtCanvas & cv )
		{

			int win_width, win_height;
			win_width = cv.m_view.Width();
			win_height = cv.m_view.Height();

			BITMAPINFO bitmapInfo;
			{
				::memset( &bitmapInfo, 0, sizeof( BITMAPINFO ) );
				bitmapInfo.bmiHeader.biSize        = sizeof( BITMAPINFOHEADER );
				bitmapInfo.bmiHeader.biPlanes      = 1;
				bitmapInfo.bmiHeader.biBitCount    = 32;
				bitmapInfo.bmiHeader.biCompression = BI_RGB;
				bitmapInfo.bmiHeader.biWidth       = win_width;
				bitmapInfo.bmiHeader.biHeight      = win_height;
				bitmapInfo.bmiHeader.biSizeImage   = win_width * win_height * 4; // Size 4, assuming RGBA from OpenGL
			}

			void    *bmBits = NULL;
			HDC     memDC   = ::CreateCompatibleDC( dstDC );
			HBITMAP memBM   = ::CreateDIBSection( NULL, &bitmapInfo, DIB_RGB_COLORS, &bmBits, NULL, 0 );


			::glReadPixels( cv.m_dest.x,
				cv.m_dest.y,
				win_width,
				win_height,
				GL_BGRA_EXT,
				GL_UNSIGNED_BYTE,
				bmBits );
			HGDIOBJ prevBitmap = ::SelectObject( memDC, memBM );
			HGDIOBJ obj        = ::SelectObject( dstDC, dstHBITMAP );

			// Remember that OpenGL origin is at bottom, left, but bitmaps are top, left
			BitBlt(dstDC, cv.m_dest.x, cv.m_dest.y, win_width, win_height,
				memDC, cv.m_delta.x, cv.m_delta.y, SRCCOPY);

			::SelectObject( memDC, prevBitmap );
			::DeleteObject( memBM );
			::DeleteDC( memDC );                    
		}

	};//end namespace GtOpenGL

};//end namespace GT

