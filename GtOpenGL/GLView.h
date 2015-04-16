// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GLVIEW_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GLVIEW_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
// We add the condition WIN32 for UNIX/Linux portability
#ifdef GLVIEW_EXPORTS
#ifdef WIN32
#define GLVIEW_API __declspec(dllexport)
#else
#define GLVIEW_API
#endif
#else
#ifdef WIN32
#define GLVIEW_API __declspec(dllimport)
#else
#define GLVIEW_API
#endif
#endif


#ifdef WIN32
#include <windows.h> // required by OpenGL and must be included before gl.h
#include <TCHAR.H>  // for unicode support
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#ifndef WIN32
#include <GL/glx.h>
#endif

// This class is exported from the GLView.dll
class GLVIEW_API CGLView 
{
public:
	CGLView(void);

#ifdef WIN32
	void SetWindow(HWND ihWnd);
#else
	void SetWindow(Display* pDisp, const Window& wnd);
#endif
	bool SetupGLContext(bool iSetPixelFormat);
	void Resize(unsigned short iWidth, unsigned short iHeight);
	void RenderScene(void);
	void Refresh( void);

private:
#ifdef WIN32
	int SetPixelFormat(HDC hdc);
#endif
	void Setup3DEnvironment();
	void DrawGradientBackggRound();
	void InitDisplayLists();
	void DoAntialiasing();

private:

#ifdef WIN32
	HWND m_hWnd;
	HDC  m_hDC;
	HGLRC m_hGLRC;
#else
	Display* m_pXDisplay;
	int m_iXScreen;
	Window m_iXWindow;
	GLXContext m_hGLContext;
	XVisualInfo *m_hVisual;
	Colormap m_ColMap;
#endif

	GLdouble nRange;	
	GLdouble win_xmax,
		win_xmin,
		win_ymax,
		win_ymin,
		winz,
		winH,
		winW;

	bool m_bGradientBg;
	bool m_bAntiAlias;

	GLubyte bgTopR;
	GLubyte bgTopG;
	GLubyte bgTopB;
	GLubyte bgBotR;
	GLubyte bgBotG;
	GLubyte bgBotB;

	GLfloat ambiLight[4];
	GLfloat diffLight[4];
	GLfloat specLight[4];

};



void GLVIEW_API drawTorus(int numMajor, int numMinor, float majorRadius, float minorRadius, bool bShaded = true);


