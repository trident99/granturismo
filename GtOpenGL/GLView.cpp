// GLView.cpp : Defines the exported functions for the DLL application.
//
#define GLVIEW_EXPORTS

#include "GLView.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// This is the constructor of a class that has been exported.
// see GLView.h for the class definition
CGLView::CGLView()
{
#ifdef WIN32
	m_hWnd = NULL;
	m_hDC = NULL;
	m_hGLRC = NULL;
#else
	m_pXDisplay = NULL;
	m_hGLContext = NULL;
	m_hVisual = NULL;
#endif

	nRange = 100;
	m_bAntiAlias = true;

	ambiLight[0] = 0.3f;
	ambiLight[1] = 0.3f;
	ambiLight[2] = 0.3f;
	ambiLight[3] = 1.0f;

	diffLight[0] = 0.7f;
	diffLight[1] = 0.7f;
	diffLight[2] = 0.7f;
	diffLight[3] = 1.0f;

	specLight[0] = 1.0f;
	specLight[1] = 1.0f;
	specLight[2] = 1.0f;
	specLight[3] = 1.0f;

	// gradient background color
	bgTopR = 77;
	bgTopG  =77;
	bgTopB = 77;
	bgBotR = 236;
	bgBotG = 233;
	bgBotB = 216;


	m_bGradientBg = true;

	return;
}

#ifdef WIN32
void CGLView::SetWindow(HWND ihWnd)
{
	m_hWnd = ihWnd;
}
#else
void CGLView::SetWindow(Display* pDisp, const Window& wnd)
{
	m_pXDisplay = pDisp;
	m_iXWindow = wnd;
}
#endif

void CGLView::Resize(unsigned short iWidth, unsigned short iHeight)
{
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];

	winH = (GLdouble)iHeight;
	winW = (GLdouble)iWidth;

	// setup viewport, projection etc.:
	/* Prevent a divide by zero*/
	if(iHeight == 0)
		iHeight = 1;

#ifdef WIN32
	wglMakeCurrent(m_hDC, m_hGLRC);
#else
	glXMakeCurrent(m_pXDisplay, m_iXWindow, m_hGLContext);
#endif

	glViewport (0, 0, iWidth, iHeight);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	if (iWidth <= iHeight)
		glOrtho (-nRange, nRange, -nRange*iHeight/iWidth, nRange*iHeight/iWidth, -nRange*10000, nRange*10000);
	else
		glOrtho (-nRange*iWidth/iHeight, nRange*iWidth/iHeight, -nRange, nRange, -nRange*10000, nRange*10000);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	/* store limits for gradient background */
	glGetDoublev (GL_PROJECTION_MATRIX, projMatrix);
	glGetDoublev (GL_MODELVIEW_MATRIX, modelMatrix);
	glGetIntegerv (GL_VIEWPORT, viewport);
	gluUnProject (0, 0, 1, modelMatrix, projMatrix, viewport,
		&win_xmin, &win_ymin, &winz);
	gluUnProject (iWidth, iHeight, 1, modelMatrix, projMatrix, viewport,
		&win_xmax, &win_ymax, &winz);

#ifdef WIN32
	wglMakeCurrent(NULL,NULL);
#else
	glXMakeCurrent(m_pXDisplay, None, NULL);
#endif
}

void CGLView::Refresh( void)
{
#ifdef WIN32
	::InvalidateRect(m_hWnd, NULL, FALSE);
#else
	// setup event data
	XWindowAttributes winattr;
	Status st = XGetWindowAttributes(m_pXDisplay, m_iXWindow, &winattr);
	XExposeEvent ev = { Expose, 0, 1, m_pXDisplay, m_iXWindow, 0, 0, winattr.width, winattr.height, 0 };
	// send event to display connection
	XSendEvent(m_pXDisplay, m_iXWindow, False, ExposureMask, (XEvent *) &ev);
	XFlush(m_pXDisplay);
#endif
}

void CGLView::RenderScene(void)
{
#ifdef WIN32
	wglMakeCurrent(m_hDC, m_hGLRC);
#else
	glXMakeCurrent(m_pXDisplay, m_iXWindow, m_hGLContext);
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawGradientBackggRound();	
	DoAntialiasing();
	Setup3DEnvironment();	

	glPushMatrix();
	{
		//Draw stuff here
		glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);

		glColor4ub(125, 255, 255, 255);
		drawTorus(30, 20, 50, 25, false);
	}
	glPopMatrix();

#ifdef WIN32
	SwapBuffers(m_hDC);
	wglMakeCurrent(NULL, NULL);
#else
	glXSwapBuffers(m_pXDisplay, m_iXWindow);
	glXMakeCurrent(m_pXDisplay, None, NULL);
#endif
}

bool CGLView::SetupGLContext(bool iSetPixelFormat)
{
#ifdef WIN32
	if(m_hWnd == NULL)
	{
		return false;
	}

	m_hDC = ::GetDC(m_hWnd);

	if(iSetPixelFormat)
	{
		SetPixelFormat(m_hDC);
	}	

	if (m_hGLRC = ::wglCreateContext(m_hDC))
	{ 
		// try to make it the thread's current rendering context 
		if(false == wglMakeCurrent(m_hDC, m_hGLRC))
		{
			MessageBox(m_hWnd, _T("Failed wglMakeCurrent"), _T("Error!"), MB_ICONERROR);
			return false;
		}
		else
		{
			glClearColor(0.0, 0.0, 0.0, 1.0);
			InitDisplayLists();
		}
	}
	return true;
#else
	int attrListSgl[] =
	{ GLX_RGBA, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4, GLX_BLUE_SIZE, 4,
	GLX_DEPTH_SIZE, 16, None };

	int attrListDbl[] =
	{ GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 4, GLX_GREEN_SIZE, 4,
	GLX_BLUE_SIZE, 4, GLX_DEPTH_SIZE, 16, None };

	m_iXScreen = DefaultScreen(m_pXDisplay);

	m_hVisual = glXChooseVisual(m_pXDisplay, m_iXScreen, attrListDbl);
	if (NULL == m_hVisual)
	{
		m_hVisual = glXChooseVisual(m_pXDisplay, m_iXScreen, attrListSgl);
		cout << "Singlebuffered : true" << endl;
		if(NULL == m_hVisual)
		{
			cerr << "Could not get suitable XVisualInfo\n" << endl;
			return false;
		}
	}
	else
	{
		cout << "Doublebuffered : true\n" << endl;
	}

	// Create the rendering context
	m_hGLContext = glXCreateContext(m_pXDisplay, m_hVisual, 0, GL_TRUE);

	// Create a colormap
	m_ColMap = XCreateColormap(m_pXDisplay, RootWindow(m_pXDisplay, m_hVisual->screen),
		m_hVisual->visual, AllocNone);

	// Make the rendering context current, perform initialization, then
	// deselect it
	if(False == glXMakeCurrent(m_pXDisplay, m_iXWindow, m_hGLContext))
	{
		return false;
	}
	else
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		InitDisplayLists();
	}
	glXMakeCurrent(m_pXDisplay, None, NULL);
	return true;
#endif
}

#ifdef WIN32
int CGLView::SetPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
		1,                                // version number 
		PFD_DRAW_TO_WINDOW |              // support window 
		PFD_SUPPORT_OPENGL |              // support OpenGL 
		PFD_DOUBLEBUFFER,                 // double buffered 
		PFD_TYPE_RGBA,                    // RGBA type 
		24,                               // 24-bit color depth 
		0, 0, 0, 0, 0, 0,                 // color bits ignored 
		0,                                // no alpha buffer 
		0,                                // shift bit ignored 
		0,                                // no accumulation buffer 
		0, 0, 0, 0,                       // accum bits ignored 
		32,                               // 32-bit z-buffer     
		0,                                // no stencil buffer 
		0,                                // no auxiliary buffer 
		PFD_MAIN_PLANE,                   // main layer 
		0,                                // reserved 
		0, 0, 0                           // layer masks ignored 
	}; 

	int  iPixelFormat; 

	// get the device context's best, available pixel format match 
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox(m_hWnd, _T("ChoosePixelFormat Failed"), NULL, MB_ICONERROR);
		return 0;
	}

	// make that match the device context's current pixel format 
	if(::SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox(m_hWnd, _T("SetPixelFormat Failed"), NULL, MB_ICONERROR);
		return 0;
	}

	return 1;
}
#endif

void CGLView::Setup3DEnvironment()
{
	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	// Enable lighting
	glEnable(GL_LIGHTING);
	
	GLfloat position[] = {0.0f, 0.0f, 3.0f, 0.0f};
	GLfloat lmodel_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat local_view[] = {0.0f};

	// Setup and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
}
void CGLView::DoAntialiasing()
{
	if(m_bAntiAlias)
	{
		glEnable (GL_POINT_SMOOTH);
		glEnable (GL_LINE_SMOOTH);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
		glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
		glLineWidth(1.5125f);
		glDepthFunc(GL_ALWAYS);
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable (GL_LINE_SMOOTH);
		glLineWidth (1.2125f);
		glDepthFunc(GL_LESS);
		glDisable (GL_BLEND);
	}
}

void CGLView::DrawGradientBackggRound()
{
	/*gradient background */
	glPushAttrib(GL_ENABLE_BIT);
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_LIGHTING);
	glDisable (GL_TEXTURE_2D);
	glShadeModel (GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL);
	glBegin (GL_POLYGON);
	//glColor3ub (51, 51, 101);
	glColor3ub (bgTopR, bgTopG, bgTopB);
	glVertex3d (win_xmin, win_ymax, winz);
	glVertex3d (win_xmax, win_ymax, winz);
	//glColor3ub (171, 172, 193);
	if(m_bGradientBg)
	{
		glColor3ub (bgBotR, bgBotG, bgBotB);
	}
	glVertex3d (win_xmax, win_ymin, winz);
	glVertex3d (win_xmin, win_ymin, winz);
	glEnd ();
	glPopAttrib();
	/*end gradient background */
}

void CGLView::InitDisplayLists()
{
}

#include <cmath>
//helper function to draw torus removes 'glut' dependency
void GLVIEW_API drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius, bool bShaded)
{
	static double PI = 3.1415926535897932384626433832795;
	double majorStep = 2.0 * PI / numMajor;
	double minorStep = 2.0 * PI / numMinor;
	int i, j;

	GLfloat opacity = 255;

	GLfloat ambiMat[4] = { 0.2f, 0.5f, 0.7f, opacity };

	GLfloat diffMat[4] = { 0.7f, 0.7f, 0.7f, opacity };

	GLfloat specMat[4] = { 1.0f, 1.0f, 1.0f, opacity };

	GLfloat specRef[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLint shine;

	shine = 128;

	opacity = 255;


	// Enable Material
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);

	//Setup Material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat);


	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specRef);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, shine);

	if(!bShaded)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}


	for (i = 0; i < numMajor; ++i) 
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLdouble x0 = cos(a0);
		GLdouble y0 = sin(a0);
		GLdouble x1 = cos(a1);
		GLdouble y1 = sin(a1);

		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= numMinor; ++j) {
			double b = j * minorStep;
			GLdouble c = cos(b);
			GLdouble r = minorRadius * c + majorRadius;
			GLdouble z = minorRadius * sin(b);

			glNormal3d(x0 * c, y0 * c, z / minorRadius);
			glTexCoord2d(i / (GLdouble) numMajor, j / (GLdouble) numMinor);
			glVertex3d(x0 * r, y0 * r, z);

			glNormal3d(x1 * c, y1 * c, z / minorRadius);
			glTexCoord2d((i + 1) / (GLdouble) numMajor, j / (GLdouble) numMinor);
			glVertex3d(x1 * r, y1 * r, z);
		}
		glEnd();
	}
}
