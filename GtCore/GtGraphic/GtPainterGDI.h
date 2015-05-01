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


#ifndef GT_PAINTER_GDI_H
#define GT_PAINTER_GDI_H

#include ".\GtPainter.h"

using namespace HTL;

namespace GT
{
	namespace GtCore
	{


		//The GtPainter is a windows GDI painter for painting the 2D Graphics of the windows system and their widgets
		class HTL_DLLAPI GtPainterGDI : public GtPainter
		{
		public:
			//!Default ructor
			GtPainterGDI();
			//!Destructor
			~GtPainterGDI();

			virtual HDC GetCurrHDC(void);
			virtual HGLRC GetCurrGLDC(void);
			virtual HBITMAP GetCurrBitmap(void);

		public:
			//DRAWING FUNCTIONS//////////////////////////
			//!Begin a Painting Session
			virtual bool GtBeginPainting(void);
			//!End a Painting Session
			virtual bool GtEndPainting(void);

			//!Start drawing on a canvas
			virtual void GtStartCanvas(GtCanvas * ptrCV);
			//!Start drawing on a canvas
			virtual void GtEndCanvas(void);

			//!Reset a Painting Session
			virtual bool GtReset(void);
			//!Clear the Painter
			virtual void GtClear(void);

			//!Draw a Line
			virtual void  GtDrawLine (  GtLineF & line, bool blnOffset = false); 
			virtual void  GtDrawLine (  GtLineI & line, bool blnOffset = false); 
			virtual void  GtDrawLine (  GtPoint3DF & p1,  GtPoint3DF & p2, bool blnOffset = false); 
			virtual void  GtDrawLine (  GtPoint3DI & p1,  GtPoint3DI & p2, bool blnOffset = false);
			virtual void  GtDrawLine ( int x1, int y1, int x2, int y2, bool blnOffset = false); 
			//!Draw a 2D Point
			virtual void  GtDrawPoint (  GtPoint3DF & position,float sngRadius, bool blnOffset = false); 
			virtual void  GtDrawPoint (  GtPoint3DI & position,int intRadius, bool blnOffset = false); 
			virtual void  GtDrawPoint ( int x, int y, int intRadius, bool blnOffset = false); 
			//!Draw Multiple 2D Points
			virtual void  GtDrawPoints (  GtPolylineF & points, float sngRadius, bool blnOffset = false); 
			virtual void  GtDrawPoints (  GtPolylineI & points,int intRadius, bool blnOffset = false);
			//!Draw a Closed Polygon
			virtual void  GtDrawPolygon (  GtPolylineF & points, GtFillRule fillRule = OddEvenFill, bool blnOffset = false); 
			virtual void  GtDrawPolygon (  GtPolylineI & points, GtFillRule fillRule = OddEvenFill, bool blnOffset = false);
			//!Draw a Polyline
			virtual void  GtDrawPolyline (  GtPolylineF & points, bool blnOffset = false );
			virtual void  GtDrawPolyline (  GtPolylineI & points, bool blnOffset = false );
			//!Draw a Rectangle
			virtual void  GtDrawRect (  GtRectF & rect, bool blnOffset = false ); 
			virtual void  GtDrawRect (  GtRectI & rect, bool blnOffset = false ); 
			//!Draw a Rectangle Frame
			virtual void  GtDrawFrame (  GtRectF & rect, bool blnOffset = false ); 
			virtual void  GtDrawFrame (  GtRectI & rect, bool blnOffset = false );
			//!Draw a Bevel Raised or Sunken Frame
			virtual void  GtDrawBevelFrameRaised (  GtRectI & rect, int width, bool blnOffset = false  ); 
			virtual void  GtDrawBevelFrameSunken (  GtRectI & rect, int width, bool blnOffset = false  );

			//!Draw a Rounded Rectangle
			virtual void  GtDrawRoundedRect (  GtRectF & rect, float radius, bool blnOffset = false); 
			virtual void  GtDrawRoundedRect (  GtRectI & rect, int radius, bool blnOffset = false); 
			//!Erase the graphics in the rectangle
			virtual void  GtEraseRect (  GtRectF & rect, bool blnOffset = false ); 
			virtual void  GtEraseRect (  GtRectI & rect, bool blnOffset = false ); 
			virtual void  GtEraseRect ( int x, int y, int width, int height, bool blnOffset = false );
			//!Fill the rectangle
			virtual void  GtFillRect (  GtRectF & rect, bool blnOffset = false );  
			virtual void  GtFillRect (  GtRectI & rect, bool blnOffset = false ); 
			virtual void  GtFillRect (  GtRectF & rect,  GtColor & val, bool blnOffset = false ); 
			virtual void  GtFillRect (  GtRectI & rect,  GtColor & val, bool blnOffset = false ); 
			virtual void  GtFillRect ( int x, int y, int width, int height, bool blnOffset = false ); 
			virtual void  GtFillRect ( int x, int y, int width, int height,  GtColor & val, bool blnOffset = false ); 
			//!Draw Triangles
			virtual void GtDrawTriangleUp(GtRectI& rect, int shrink, bool blnOffset = false);
			virtual void GtDrawTriangleDown(GtRectI& rect, int shrink, bool blnOffset = false);
			virtual void GtDrawTriangleLeft(GtRectI& rect, int shrink, bool blnOffset = false);
			virtual void GtDrawTriangleRight(GtRectI& rect, int shrink, bool blnOffset = false);
			//!Draw Ellipse
			virtual void GtDrawEllipse(GtRectI& rect, bool blnOffset = false);
			//!Draw Circle
			virtual void GtDrawCircle(GtPoint3DI & center, int radius, bool blnOffset = false);
			virtual void GtDrawPie(GtPoint3DI & center, int radius,float sngStartDeg,float sngSpan, bool blnOffset = false);
			virtual void GtDrawArcPie(GtPoint3DI & center, int inRad, int outRad, float sngStartDeg, float sngSpan, bool blnOffset = false);
			//!Draw a Static Text string
			virtual void  GtDrawStaticText(std::string & strText, GtPoint3DI & topLeftPos, bool blnOffset = false);
			virtual void  GtDrawStaticText(std::string & strText, GtPoint3DF & topLeftPos, bool blnOffset = false);
			virtual void  GtDrawStaticText(std::string & strText, int left, int top, bool blnOffset = false);
			//!Draw the text string in the bounding rectangle
			virtual void  GtDrawText(std::string & strText, GtPoint3DF & pos, bool blnOffset = false);
			virtual void  GtDrawText(std::string & strText, GtPoint3DI & pos, bool blnOffset = false);
			virtual void  GtDrawText(std::string & strText, GtRectF & boundRect, int flags, bool blnOffset = false);
			virtual void  GtDrawText(std::string & strText, GtRectI & boundRect, int flags, bool blnOffset = false);
			//!Draw the Pixmap in the target rectangle or at the desired point
			virtual void  GtDrawPixmap (  GtRectF & target,  GtPixmap & pixmap,  GtRectF & source, bool blnOffset = false); 
			virtual void  GtDrawPixmap (  GtRectI & target,  GtPixmap & pixmap,  GtRectI & source, bool blnOffset = false); 
			virtual void  GtDrawPixmap (  GtPoint3DF & point,  GtPixmap & pixmap,  GtRectF & source, bool blnOffset = false); 
			virtual void  GtDrawPixmap (  GtPoint3DI & point,  GtPixmap & pixmap,  GtRectI & source, bool blnOffset = false); 
			virtual void  GtDrawPixmap (  GtPoint3DF & point,  GtPixmap & pixmap, bool blnOffset = false); 
			virtual void  GtDrawPixmap (  GtPoint3DI & point,  GtPixmap & pixmap, bool blnOffset = false);
			//!Tile the Pixmap in the bounding rectangle
			virtual void  GtDrawTiledPixmap (  GtRectF & rectangle,  GtPixmap & pixmap, bool blnOffset = false); 
			virtual void  GtDrawTiledPixmap (  GtRectI & rectangle,  GtPixmap & pixmap, bool blnOffset = false); 
			//!Translate the coordinate system
			virtual void GtTranslate(int dx, int dy);
			virtual void GtTranslate(GtPoint3DI delta);


			private:
			virtual void GtSetSystemPen(void);
			virtual void GtSetSystemBrush(void);
			virtual void GtSetSystemFont(void);
			//windows required painting variables
			PAINTSTRUCT m_ptrPaint;
			//!window hdc handle
			HDC m_hdcCurr;
			//!current bitmap handle
			HBITMAP m_hBitmapCurr;
			//!window hdc handle
			HGLRC m_hglCurr;
			//!window hdc handle
			HDC m_hdcFinal;
			//!Windows GDI Pen
			HPEN m_ptrSysPen;
			//!Windows GDI Brush
			HBRUSH m_ptrSysBrush;
			//!Current handle
			HANDLE m_hSel;


			GtWinFont m_winFont;

			PIXELFORMATDESCRIPTOR m_pfd;

			Htl1DList<GtCanvas*,HtlUnknownType> m_arrCanvas;


		};//end GtPainter

	};//end namespace GtCore

};//end namespace GT

#endif//GT_PAINTER_GDI_H
