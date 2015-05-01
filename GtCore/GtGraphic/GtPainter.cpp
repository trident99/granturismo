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

#include ".\GtPainter.h"


using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		GtCanvas::GtCanvas()
		{
			m_blnInitialized = false;
			//!handle for parent hdc (or final)
			m_hdcParent = 0;
			//!handle for memory hdc
			m_hdcMem = 0;
			//!handle for memory bitmap
			m_hbmMem = 0;

			m_view.Zero();

			m_frame.Zero();

			m_dest.Zero();

			m_delta.Zero();
		};
		GtCanvas::~GtCanvas()
		{
			this->Clear();
		};

		void GtCanvas::Initialize(void)
		{
			if(m_blnInitialized){return;}//do only once

			if(m_hdcParent)
			{
				m_hdcMem = CreateCompatibleDC(m_hdcParent);
				int win_width, win_height;
				win_width = m_frame.xMax - m_frame.xMin;
				win_height = m_frame.yMax - m_frame.yMin;
				m_hbmMem = CreateCompatibleBitmap(m_hdcParent, win_width, win_height);
				m_blnInitialized = true;
			};

		};

		void GtCanvas::Clear (void)
		{
			DeleteObject(m_hbmMem);
			DeleteDC(m_hdcMem);
		};

		void GtCanvas::Reset (void)
		{
			DeleteObject(m_hbmMem);
			DeleteDC(m_hdcMem);
			m_hdcMem = CreateCompatibleDC(m_hdcParent);
			int win_width, win_height;
			win_width = m_frame.xMax - m_frame.xMin;
			win_height = m_frame.yMax - m_frame.yMin;
			m_hbmMem = CreateCompatibleBitmap(m_hdcParent, win_width, win_height);
			m_blnInitialized = true;
		};



		//!Default ructor
		GtPainter::GtPainter()
		{


		};
		//!Destructor
		GtPainter::~GtPainter()
		{

		};

		HDC GtPainter::GetCurrHDC(void){return NULL;};
		HGLRC GtPainter::GetCurrGLDC(void){return NULL;};
		HBITMAP GtPainter::GetCurrBitmap(void){return NULL;};


		//DRAWING FUNCTIONS//////////////////////////
		//!Begin a Painting Session
		bool GtPainter::GtBeginPainting(void){return false;};
		//!End a Painting Session
		bool GtPainter::GtEndPainting(void){return false;};
		//!Start drawing on a canvas
		void GtPainter::GtStartCanvas(GtCanvas * ptrCV){return;};
		//!Start drawing on a canvas
		void GtPainter::GtEndCanvas(void){return;};
		//!Reset a Painting Session
		bool GtPainter::GtReset(void){return false;};
		//!Clear the Painter
		void GtPainter::GtClear(void){return;};

		//!Draw a Line
		void  GtPainter::GtDrawLine (  GtLineF & line, bool blnOffset ){return;}; 
		void  GtPainter::GtDrawLine (  GtLineI & line, bool blnOffset ){return;};
		void  GtPainter::GtDrawLine (  GtPoint3DF & p1,  GtPoint3DF & p2, bool blnOffset ){return;}; 
		void  GtPainter::GtDrawLine (  GtPoint3DI & p1,  GtPoint3DI & p2, bool blnOffset ){return;};
		void  GtPainter::GtDrawLine ( int x1, int y1, int x2, int y2, bool blnOffset ){return;};
		//!Draw a 2D Point
		void  GtPainter::GtDrawPoint (  GtPoint3DF & position,float sngRadius, bool blnOffset ){return;};
		void  GtPainter::GtDrawPoint (  GtPoint3DI & position,int intRadius, bool blnOffset ){return;}; 
		void  GtPainter::GtDrawPoint ( int x, int y, int intRadius, bool blnOffset ){return;};
		//!Draw Multiple 2D Points
		void  GtPainter::GtDrawPoints (  GtPolylineF & points, float sngRadius, bool blnOffset){return;}; 
		void  GtPainter::GtDrawPoints (  GtPolylineI & points,int intRadius, bool blnOffset ){return;};
		//!Draw a Closed Polygon
		void  GtPainter::GtDrawPolygon (  GtPolylineF & points, GtFillRule fillRule, bool blnOffset){return;}; 
		void  GtPainter::GtDrawPolygon (  GtPolylineI & points, GtFillRule fillRule, bool blnOffset){return;};
		//!Draw a Polyline
		void  GtPainter::GtDrawPolyline (  GtPolylineF & points, bool blnOffset ){return;};
		void  GtPainter::GtDrawPolyline (  GtPolylineI & points, bool blnOffset ){return;};
		//!Draw a Rectangle
		void  GtPainter::GtDrawRect (  GtRectF & rect, bool blnOffset ){return;}; 
		void  GtPainter::GtDrawRect (  GtRectI & rect, bool blnOffset ){return;};
		//!Draw a Rectangle Frame
		void  GtPainter::GtDrawFrame (  GtRectF & rect, bool blnOffset ){return;}; 
		void  GtPainter::GtDrawFrame (  GtRectI & rect, bool blnOffset ){return;};
		//!Draw a Bevel Raised or Sunken Frame
		void  GtPainter::GtDrawBevelFrameRaised (  GtRectI & rect, int width, bool blnOffset){return;};
		void  GtPainter::GtDrawBevelFrameSunken (  GtRectI & rect, int width, bool blnOffset){return;};
		//!Draw a Rounded Rectangle
		void  GtPainter::GtDrawRoundedRect (  GtRectF & rect, float radius, bool blnOffset){return;};
		void  GtPainter::GtDrawRoundedRect (  GtRectI & rect, int radius, bool blnOffset){return;};
		//!Erase the graphics in the rectangle
		void  GtPainter::GtEraseRect (  GtRectF & rect, bool blnOffset ){return;};
		void  GtPainter::GtEraseRect (  GtRectI & rect, bool blnOffset ){return;};
		void  GtPainter::GtEraseRect ( int x, int y, int width, int height, bool blnOffset ){return;};
		//!Fill the rectangle
		void  GtPainter::GtFillRect (  GtRectF & rect, bool blnOffset ){return;};  
		void  GtPainter::GtFillRect (  GtRectI & rect, bool blnOffset ){return;}; 
		void  GtPainter::GtFillRect (  GtRectF & rect,  GtColor & val, bool blnOffset ){return;}; 
		void  GtPainter::GtFillRect (  GtRectI & rect,  GtColor & val, bool blnOffset ){return;}; 
		void  GtPainter::GtFillRect ( int x, int y, int width, int height, bool blnOffset ){return;}; 
		void  GtPainter::GtFillRect ( int x, int y, int width, int height,  GtColor & val, bool blnOffset ){return;};
		//!Draw Triangles
		void GtPainter::GtDrawTriangleUp(GtRectI& rect, int shrink, bool blnOffset){return;};
		void GtPainter::GtDrawTriangleDown(GtRectI& rect, int shrink, bool blnOffset){return;};
		void GtPainter::GtDrawTriangleLeft(GtRectI& rect, int shrink, bool blnOffset){return;};
		void GtPainter::GtDrawTriangleRight(GtRectI& rect, int shrink, bool blnOffset){return;};
		//!Draw Ellipse
		void GtPainter::GtDrawEllipse(GtRectI& rect, bool blnOffset){return;};
		//!Draw Circle
		void GtPainter::GtDrawCircle(GtPoint3DI & center, int radius, bool blnOffset){return;};
		void GtPainter::GtDrawPie(GtPoint3DI & center, int radius,float sngStartDeg,float sngSpan, bool blnOffset){return;};
		void GtPainter::GtDrawArcPie(GtPoint3DI & center, int inRad, int outRad, float sngStartDeg, float sngSpan, bool blnOffset){return;};
		//!Draw a Static Text string
		void  GtPainter::GtDrawStaticText(std::string & strText, GtPoint3DI & topLeftPos, bool blnOffset ){ return; };
		void  GtPainter::GtDrawStaticText(std::string & strText, GtPoint3DF & topLeftPos, bool blnOffset){ return; };
		void  GtPainter::GtDrawStaticText(std::string & strText, int left, int top, bool blnOffset){ return; };
		//!Draw the text string in the bounding rectangle
		void  GtPainter::GtDrawText(std::string & strText, GtPoint3DF & pos, bool blnOffset){ return; };
		void  GtPainter::GtDrawText(std::string & strText, GtPoint3DI & pos, bool blnOffset){ return; };
		void  GtPainter::GtDrawText(std::string & strText, GtRectF & boundRect, int flags, bool blnOffset){ return; };
		void  GtPainter::GtDrawText(std::string & strText, GtRectI & boundRect, int flags, bool blnOffset){ return; };

		//!Draw the Pixmap in the target rectangle or at the desired point
		void  GtPainter::GtDrawPixmap (  GtRectF & target,  GtPixmap & pixmap,  GtRectF & source, bool blnOffset){return;}; 
		void  GtPainter::GtDrawPixmap (  GtRectI & target,  GtPixmap & pixmap,  GtRectI & source, bool blnOffset){return;}; 
		void  GtPainter::GtDrawPixmap (  GtPoint3DF & point,  GtPixmap & pixmap,  GtRectF & source, bool blnOffset){return;}; 
		void  GtPainter::GtDrawPixmap (  GtPoint3DI & point,  GtPixmap & pixmap,  GtRectI & source, bool blnOffset){return;}; 
		void  GtPainter::GtDrawPixmap (  GtPoint3DF & point,  GtPixmap & pixmap, bool blnOffset){return;};
		void  GtPainter::GtDrawPixmap (  GtPoint3DI & point,  GtPixmap & pixmap, bool blnOffset){return;};
		//!Tile the Pixmap in the bounding rectangle
		void  GtPainter::GtDrawTiledPixmap (  GtRectF & rectangle,  GtPixmap & pixmap, bool blnOffset){return;}; 
		void  GtPainter::GtDrawTiledPixmap (  GtRectI & rectangle,  GtPixmap & pixmap, bool blnOffset){return;}; 
		//!Translate the coordinate system
		void GtPainter::GtTranslate(int dx, int dy){return;};
		void GtPainter::GtTranslate(GtPoint3DI delta){return;};

		void GtPainter::GtSetSystemPen(void){return;};
		void GtPainter::GtSetSystemBrush(void){return;};
		void GtPainter::GtSetSystemFont(void){return;};
	

	};//end namespace GtCore

};//end namespace GT

