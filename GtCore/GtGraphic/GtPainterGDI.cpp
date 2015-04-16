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

#include ".\GtPainterGDI.h"
#include "..\GtMath\GtBasicMath.h"
#include <Windows.h>
#include <GdiPlus.h>
using namespace Gdiplus;
using namespace HTL;

namespace GT
{
	namespace GtCore
	{
		//!Default ructor
		GtPainterGDI::GtPainterGDI() : GtPainter()
			, m_ptrSysPen(NULL)
			, m_ptrSysBrush(NULL)
		{

			memset(&m_winFont,0,sizeof(GtWinFont));
			m_hdcCurr = NULL;
			m_hSel = NULL;
			m_hglCurr = NULL;
			m_hBitmapCurr = NULL;
			m_objFont.Set_intPoint(20);
			std::wstring strFont = L"Arial";
			m_objFont.Set_strFontFamily(strFont);

		};
		//!Destructor
		GtPainterGDI::~GtPainterGDI()
		{
			
		};
		//DRAWING FUNCTIONS//////////////////////////
		//DOUBLE BUFFERING EXAMPLE
		//HDC          hdcMem;
		//HBITMAP      hbmMem;
		//HANDLE       hOld;

		//// Get DC for window
		// hdc = BeginPaint(hwnd, &ps);

		// // Create an off-screen DC for double-buffering
		// hdcMem = CreateCompatibleDC(hdc);
		// hbmMem = CreateCompatibleBitmap(hdc, win_width, win_height);

		// hOld   = SelectObject(hdcMem, hbmMem);

		// // Draw into hdcMem here

		// // Transfer the off-screen DC to the screen
		// BitBlt(hdc, 0, 0, win_width, win_height, hdcMem, 0, 0, SRCCOPY);

		// // Free-up the off-screen DC
		// SelectObject(hdcMem, hOld);
		// DeleteObject(hbmMem);
		// DeleteDC    (hdcMem);

		// EndPaint(hwnd, &ps);

		HDC GtPainterGDI::GetCurrHDC(void)
		{
			return m_hdcCurr;
		};

		HGLRC GtPainterGDI::GetCurrGLDC(void)
		{
			return m_hglCurr;
		};

		HBITMAP GtPainterGDI::GetCurrBitmap(void)
		{

			//!current bitmap handle
			return m_hBitmapCurr;

		}

		//!Begin a Painting Session
		bool GtPainterGDI::GtBeginPainting(void)
		{
			m_hdcFinal = BeginPaint(m_winID, &m_ptrPaint);
			this->m_ptrHDC = m_hdcFinal;

			//set up for OpenGL
			PIXELFORMATDESCRIPTOR m_pfd;

			memset(&m_pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

			m_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			m_pfd.nVersion = 1;
			m_pfd.dwFlags = (PFD_DRAW_TO_WINDOW  |
				PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA);
			m_pfd.iPixelType = PFD_TYPE_RGBA;
			m_pfd.cColorBits = 32;
			m_pfd.cDepthBits = 24;
			m_pfd.iLayerType = PFD_MAIN_PLANE;

			int iPixelFormat = ChoosePixelFormat(m_hdcFinal, &m_pfd);

			if(iPixelFormat == 0)
			{
				//ErrorLog.SetString("ChoosePixelFormat failed!");
				return false;
			}

			if(SetPixelFormat(m_hdcFinal, iPixelFormat, &m_pfd) == FALSE)
			{
				//ErrorLog.SetString("SetPixelFormat failed!");
				return false;
			}

			return true;
		};
		//!End a Painting Session
		bool GtPainterGDI::GtEndPainting(void)
		{
			DeleteDC(m_hdcFinal);
			//ReleaseDC(m_winID,m_hdcFinal);
			EndPaint(m_winID, &m_ptrPaint);
			return true;
		}

		//!Start drawing on a canvas
		void GtPainterGDI::GtStartCanvas(GtCanvas cv)
		{
			size_t numCvs;
			numCvs = m_arrCanvas.size();
			if(numCvs <= 0)
			{//first canvas, parent is final
				cv.m_hdcParent = m_hdcFinal;
			}else{
				//get the hdc from the next one in the stack
				cv.m_hdcParent = m_arrCanvas.back().m_hdcMem;
			}

			cv.m_hdcMem = CreateCompatibleDC(cv.m_hdcParent);
			int win_width, win_height;
			win_width = cv.m_frame.xMax - cv.m_frame.xMin;
			win_height = cv.m_frame.yMax - cv.m_frame.yMin;
			cv.m_hbmMem = CreateCompatibleBitmap(m_hdcFinal, win_width, win_height);

			m_hSel   = SelectObject(cv.m_hdcMem, cv.m_hbmMem);
			m_hdcCurr = cv.m_hdcMem;
			m_hBitmapCurr = cv.m_hbmMem;

			m_arrCanvas.push_back(cv);
			return;
		};
		//!Start drawing on a canvas
		void GtPainterGDI::GtEndCanvas(void)
		{
			size_t numCvs;
			numCvs = m_arrCanvas.size();
			if(numCvs <= 0){return;};

			GtCanvas topCv = m_arrCanvas.back();
			int win_width, win_height;
			win_width = topCv.m_view.xMax - topCv.m_view.xMin;
			win_height = topCv.m_view.yMax - topCv.m_view.yMin;
			// Transfer the off-screen DC to the screen
			bool success = BitBlt(topCv.m_hdcParent, topCv.m_dest.x, topCv.m_dest.y, win_width, win_height,
				topCv.m_hdcMem, topCv.m_delta.x, topCv.m_delta.y, SRCCOPY);

			// Free-up the off-screen DC
			SelectObject(topCv.m_hdcMem, m_hSel);
			DeleteObject(topCv.m_hbmMem);
			DeleteDC    (topCv.m_hdcMem);
			m_arrCanvas.pop_back();//pop it off the stack

			numCvs = m_arrCanvas.size();
			if(numCvs <= 0)
			{
				m_hdcCurr = NULL;
				return;
			};
			//otherwise get the next current
			m_hdcCurr = m_arrCanvas.back().m_hdcMem;
			m_hBitmapCurr = m_arrCanvas.back().m_hbmMem;

		};
		//!Reset a Painting Session
		bool GtPainterGDI::GtReset(void)
		{
			return true;
		};
		//!Clear the Painter
		void GtPainterGDI::GtClear(void)
		{

		};

		//!Draw a Line
		void  GtPainterGDI::GtDrawLine (  GtLineF & line, bool blnOffset )
		{
			GtSetSystemPen();
			SelectObject(m_hdcCurr, m_ptrSysPen);	
			if(!blnOffset)
			{
				::MoveToEx(m_hdcCurr, gRound(line.m_P0.x), gRound(line.m_P0.y), NULL);
				::LineTo(m_hdcCurr, gRound(line.m_P1.x), gRound(line.m_P1.y));
			}else{
				::MoveToEx(m_hdcCurr, gRound(line.m_P0.x + m_ptOffset.x), gRound(line.m_P0.y + m_ptOffset.y), NULL);
				::LineTo(m_hdcCurr, gRound(line.m_P1.x + m_ptOffset.x), gRound(line.m_P1.y + m_ptOffset.y));
			}
			return;
		};
		void  GtPainterGDI::GtDrawLine (  GtLineI & line, bool blnOffset )
		{
			GtSetSystemPen();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			if(!blnOffset)
			{
				::MoveToEx(m_hdcCurr, (line.m_P0.x), (line.m_P0.y), NULL);
				::LineTo(m_hdcCurr, gRound(line.m_P1.x), (line.m_P1.y));	
			}else{
				::MoveToEx(m_hdcCurr, (line.m_P0.x + m_ptOffset.x), (line.m_P0.y + m_ptOffset.y), NULL);
				::LineTo(m_hdcCurr, gRound(line.m_P1.x + m_ptOffset.x), (line.m_P1.y + m_ptOffset.y));			
			}
			return;
		};
		void  GtPainterGDI::GtDrawLine (  GtPoint3DF & p1,  GtPoint3DF & p2, bool blnOffset )
		{
			GtSetSystemPen();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			if(!blnOffset)
			{
				::MoveToEx(m_hdcCurr, gRound(p1.x), gRound(p1.y), NULL);
				::LineTo(m_hdcCurr, gRound(p2.x), gRound(p2.y));
			}else{
				::MoveToEx(m_hdcCurr, gRound(p1.x + m_ptOffset.x), gRound(p1.y + m_ptOffset.y), NULL);
				::LineTo(m_hdcCurr, gRound(p2.x + m_ptOffset.x), gRound(p2.y + m_ptOffset.y));
			};
			return;
		};
		void  GtPainterGDI::GtDrawLine (  GtPoint3DI & p1,  GtPoint3DI & p2, bool blnOffset )
		{
			GtSetSystemPen();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			if(!blnOffset)
			{
				::MoveToEx(m_hdcCurr, (p1.x), (p1.y), NULL);
				::LineTo(m_hdcCurr, (p2.x), (p2.y));
			}else{
				::MoveToEx(m_hdcCurr, (p1.x + m_ptOffset.x), (p1.y + m_ptOffset.y), NULL);
				::LineTo(m_hdcCurr, (p2.x + m_ptOffset.x), (p2.y + m_ptOffset.y));
			};
			return;

		};
		void  GtPainterGDI::GtDrawLine ( int x1, int y1, int x2, int y2, bool blnOffset )
		{
			GtSetSystemPen();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			if(!blnOffset)
			{
				::MoveToEx(m_hdcCurr, (x1), (y1), NULL);
				::LineTo(m_hdcCurr, (x2), (y2));
			}else{
				::MoveToEx(m_hdcCurr, (x1 + m_ptOffset.x), (y1 + m_ptOffset.y), NULL);
				::LineTo(m_hdcCurr, (x2 + m_ptOffset.x), (y2  + m_ptOffset.y));
			};
			return;
		};
		//!Draw a 2D Point
		void  GtPainterGDI::GtDrawPoint (  GtPoint3DF & pos,float sngRadius, bool blnOffset )
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysBrush);			
			RECT objRect;

			if(!blnOffset)
			{

				if(sngRadius <= 1.0f)
				{

					objRect.left = (gRound(pos.x)-1);
					objRect.right = (gRound(pos.x)+1);
					objRect.top = (gRound(pos.y)-1);
					objRect.bottom = (gRound(pos.y)+1);
					//then single pixel case, draws a 3 pixel point
					::FillRect(m_hdcCurr, &objRect, m_ptrSysBrush);
					return;
				}
				//otherwise draw circle
				// Create the Rect object that defines the ellipse.
				objRect.left = gRound(pos.x - sngRadius / 2.0f);
				objRect.right = gRound(pos.x + sngRadius / 2.0f);
				objRect.top = gRound(pos.y - sngRadius / 2.0f);
				objRect.bottom = gRound(pos.y + sngRadius / 2.0f);

				::Ellipse(m_hdcCurr, objRect.left, objRect.top, objRect.right, objRect.bottom);

				return;
			}else{
				GtPoint3DF transPos;
				transPos.x = pos.x + m_ptOffset.x;
				transPos.y = pos.y + m_ptOffset.y;
				transPos.z = pos.z + m_ptOffset.z;

				if(sngRadius <= 1.0f)
				{

					objRect.left = (gRound(transPos.x)-1);
					objRect.right = (gRound(transPos.x)+1);
					objRect.top = (gRound(transPos.y)-1);
					objRect.bottom = (gRound(transPos.y)+1);
					//then single pixel case, draws a 3 pixel point
					::FillRect(m_hdcCurr, &objRect, m_ptrSysBrush);
					return;
				}
				//otherwise draw circle
				// Create the Rect object that defines the ellipse.
				objRect.left = gRound(transPos.x - sngRadius / 2.0f);
				objRect.right = gRound(transPos.x + sngRadius / 2.0f);
				objRect.top = gRound(transPos.y - sngRadius / 2.0f);
				objRect.bottom = gRound(transPos.y + sngRadius / 2.0f);

				::Ellipse(m_hdcCurr, objRect.left, objRect.top, objRect.right, objRect.bottom);

				return;

			};
			return;
		};

		void  GtPainterGDI::GtDrawPoint (  GtPoint3DI & pos,int intRadius, bool blnOffset )
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysBrush);	
			RECT objRect;

			if(!blnOffset)
			{

				if(intRadius <= 1.0f)
				{

					objRect.left = (gRound(pos.x)-1);
					objRect.right = (gRound(pos.x)+1);
					objRect.top = (gRound(pos.y)-1);
					objRect.bottom = (gRound(pos.y)+1);
					//then single pixel case, draws a 3 pixel point
					::FillRect(m_hdcCurr, &objRect, m_ptrSysBrush);
					return;
				}
				//otherwise draw circle
				// Create the Rect object that defines the ellipse.
				objRect.left = gRound(pos.x - intRadius / 2.0f);
				objRect.right = gRound(pos.x + intRadius / 2.0f);
				objRect.top = gRound(pos.y - intRadius / 2.0f);
				objRect.bottom = gRound(pos.y + intRadius / 2.0f);

				::Ellipse(m_hdcCurr, objRect.left, objRect.top, objRect.right, objRect.bottom);

				return;
			}else{
				GtPoint3DI transPos;
				transPos.x = pos.x + m_ptOffset.x;
				transPos.y = pos.y + m_ptOffset.y;
				transPos.z = pos.z + m_ptOffset.z;

				if(intRadius <= 1.0f)
				{

					objRect.left = ((transPos.x)-1);
					objRect.right = ((transPos.x)+1);
					objRect.top = ((transPos.y)-1);
					objRect.bottom = ((transPos.y)+1);
					//then single pixel case, draws a 3 pixel point
					::FillRect(m_hdcCurr, &objRect, m_ptrSysBrush);
					return;
				}
				//otherwise draw circle
				// Create the Rect object that defines the ellipse.
				objRect.left = gRound(transPos.x - intRadius / 2.0f);
				objRect.right = gRound(transPos.x + intRadius / 2.0f);
				objRect.top = gRound(transPos.y - intRadius / 2.0f);
				objRect.bottom = gRound(transPos.y + intRadius / 2.0f);

				::Ellipse(m_hdcCurr, objRect.left, objRect.top, objRect.right, objRect.bottom);

				return;

			};
			return;
		};
		void  GtPainterGDI::GtDrawPoint ( int x, int y, int intRadius, bool blnOffset )
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysBrush);				
			RECT objRect;
	
			if(!blnOffset)
			{

				if(intRadius <= 1)
				{

					objRect.left = (x-1);
					objRect.right = (x+1);
					objRect.top = (y-1);
					objRect.bottom = (y+1);
					//then single pixel case, draws a 3 pixel point
					::FillRect(m_hdcCurr, &objRect, m_ptrSysBrush);
					return;
				}
				//otherwise draw circle
				// Create the Rect object that defines the ellipse.
				objRect.left = gRound(x - intRadius / 2.0f);
				objRect.right = gRound(x + intRadius / 2.0f);
				objRect.top = gRound(y - intRadius / 2.0f);
				objRect.bottom = gRound(y + intRadius / 2.0f);

				::Ellipse(m_hdcCurr, objRect.left, objRect.top, objRect.right, objRect.bottom);

				return;
			}else{
				GtPoint3DI transPos;
				transPos.x = x + m_ptOffset.x;
				transPos.y = y + m_ptOffset.y;
				transPos.z = m_ptOffset.z;

				if(intRadius <= 1.0f)
				{

					objRect.left = (gRound(transPos.x)-1);
					objRect.right = (gRound(transPos.x)+1);
					objRect.top = (gRound(transPos.y)-1);
					objRect.bottom = (gRound(transPos.y)+1);
					//then single pixel case, draws a 3 pixel point
					::FillRect(m_hdcCurr, &objRect, m_ptrSysBrush);
					return;
				}
				//otherwise draw circle
				// Create the Rect object that defines the ellipse.
				objRect.left = gRound(transPos.x - intRadius / 2.0f);
				objRect.right = gRound(transPos.x + intRadius / 2.0f);
				objRect.top = gRound(transPos.y - intRadius / 2.0f);
				objRect.bottom = gRound(transPos.y + intRadius / 2.0f);

				::Ellipse(m_hdcCurr, objRect.left, objRect.top, objRect.right, objRect.bottom);

				return;

			};
			return;

		};
		//!Draw Multiple 2D Points
		void  GtPainterGDI::GtDrawPoints (  GtPolylineF & points, float sngRadius, bool blnOffset)
		{
			size_t i, numPts;
			numPts = points.m_arrObjPoints.size();
			if(!blnOffset)
			{
				for(i = 0; i < numPts; i++)
				{
					GtPoint3DF objPt = points.m_arrObjPoints.at(i);	
					this->GtDrawPoint(objPt,sngRadius,false);
				}
			}else{
				for(i = 0; i < numPts; i++)
				{
					GtPoint3DF objPt = points.m_arrObjPoints.at(i);
					objPt.x += m_ptOffset.x;
					objPt.y += m_ptOffset.y;
					objPt.z += m_ptOffset.z;
					this->GtDrawPoint(objPt,sngRadius,false);
				}
			}
			return;
		};
		void  GtPainterGDI::GtDrawPoints (  GtPolylineI & points,int intRadius, bool blnOffset )
		{
			size_t i, numPts;
			numPts = points.m_arrObjPoints.size();
			if(!blnOffset)
			{
				for(i = 0; i < numPts; i++)
				{
					GtPoint3DI objPt = points.m_arrObjPoints.at(i);	
					this->GtDrawPoint(objPt,intRadius,false);
				}
			}else{
				for(i = 0; i < numPts; i++)
				{
					GtPoint3DI objPt = points.m_arrObjPoints.at(i);
					objPt.x += m_ptOffset.x;
					objPt.y += m_ptOffset.y;
					objPt.z += m_ptOffset.z;
					this->GtDrawPoint(objPt,intRadius,false);
				}
			}
			return;
		};
		//!Draw a Closed Polygon
		void  GtPainterGDI::GtDrawPolygon (  GtPolylineF & points, GtFillRule fillRule, bool blnOffset)
		{
				size_t i, numPts;
				numPts = points.m_arrObjPoints.size();
				if(numPts <= 1){return;};//no line to draw
				POINT  poly[500];//max 20 points
				memset(&poly[0],0,500 * sizeof(POINT));

				if(!blnOffset)
				{
					for(i = 0; i < numPts; i++)
					{
						poly[i].x = gRound(points.m_arrObjPoints.at(i).x);
						poly[i].y = gRound(points.m_arrObjPoints.at(i).y);
					}
				}else{
					for(i = 0; i < numPts; i++)
					{
						poly[i].x = gRound(points.m_arrObjPoints.at(i).x) + m_ptOffset.x;
						poly[i].y = gRound(points.m_arrObjPoints.at(i).y) + m_ptOffset.y;
					}

				}


				GtSetSystemPen();
				GtSetSystemBrush();
				SelectObject(m_hdcCurr, m_ptrSysPen);
				SelectObject(m_hdcCurr, m_ptrSysBrush);
				::Polygon(m_hdcCurr,&poly[0],numPts);
				return;
		};
		void  GtPainterGDI::GtDrawPolygon (  GtPolylineI & points, GtFillRule fillRule, bool blnOffset)
		{
				size_t i, numPts;
				numPts = points.m_arrObjPoints.size();
				if(numPts <= 1){return;};//no line to draw
				POINT  poly[500];//max 20 points
				memset(&poly[0],0,500 * sizeof(POINT));
				if(!blnOffset)
				{
					for(i = 0; i < numPts; i++)
					{
						poly[i].x = (points.m_arrObjPoints.at(i).x);
						poly[i].y = (points.m_arrObjPoints.at(i).y);
					}
				}else{
					for(i = 0; i < numPts; i++)
					{
						poly[i].x = (points.m_arrObjPoints.at(i).x) + m_ptOffset.x;
						poly[i].y = (points.m_arrObjPoints.at(i).y) + m_ptOffset.y;
					}
				}
				GtSetSystemPen();
				GtSetSystemBrush();
				SelectObject(m_hdcCurr, m_ptrSysPen);
				SelectObject(m_hdcCurr, m_ptrSysBrush);
				::Polygon(m_hdcCurr,&poly[0],numPts);
				return;
		};
		//!Draw a Polyline
		void  GtPainterGDI::GtDrawPolyline (  GtPolylineF & points, bool blnOffset )
		{
				size_t i, numPts;
				numPts = points.m_arrObjPoints.size();
				if(numPts <= 1){return;};//no line to draw
				if(!blnOffset)
				{
					for(i = 0; i < numPts -1; i++)
					{
						GtPoint3DI ptA, ptB;
						ptA.x = gRound(points.m_arrObjPoints.at(i).x);
						ptA.y = gRound(points.m_arrObjPoints.at(i).y);

						ptB.x = gRound(points.m_arrObjPoints.at(i+1).x);
						ptB.y = gRound(points.m_arrObjPoints.at(i+1).y);
						this->GtDrawLine(ptA,ptB);
					}
				}else{
					for(i = 0; i < numPts -1; i++)
					{
						GtPoint3DI ptA, ptB;
						ptA.x = gRound(points.m_arrObjPoints.at(i).x) + m_ptOffset.x;
						ptA.y = gRound(points.m_arrObjPoints.at(i).y) + m_ptOffset.y;

						ptB.x = gRound(points.m_arrObjPoints.at(i+1).x) + m_ptOffset.x;
						ptB.y = gRound(points.m_arrObjPoints.at(i+1).y) + m_ptOffset.y;
						this->GtDrawLine(ptA,ptB);
					}
				}
				return;
		};
		void  GtPainterGDI::GtDrawPolyline (  GtPolylineI & points, bool blnOffset )
		{
			size_t i, numPts;
			numPts = points.m_arrObjPoints.size();
			if(numPts <= 1){return;};//no line to draw

			if(!blnOffset)
			{
				for(i = 0; i < numPts -1; i++)
				{
					GtPoint3DI ptA, ptB;
					ptA.x = points.m_arrObjPoints.at(i).x;
					ptA.y = points.m_arrObjPoints.at(i).y;

					ptB.x = points.m_arrObjPoints.at(i+1).x;
					ptB.y = points.m_arrObjPoints.at(i+1).y;
					this->GtDrawLine(ptA,ptB);
				}
			}else{
				for(i = 0; i < numPts -1; i++)
				{
					GtPoint3DI ptA, ptB;
					ptA.x = points.m_arrObjPoints.at(i).x + m_ptOffset.x;
					ptA.y = points.m_arrObjPoints.at(i).y + m_ptOffset.y;

					ptB.x = points.m_arrObjPoints.at(i+1).x + m_ptOffset.x;
					ptB.y = points.m_arrObjPoints.at(i+1).y + m_ptOffset.y;
					this->GtDrawLine(ptA,ptB);
				}
			}
			return;
		};
		//!Draw a Rectangle
		void  GtPainterGDI::GtDrawRect (  GtRectF & rect, bool blnOffset )
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMin),
					gRound(rect.xMax), gRound(rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, gRound(rect.xMin) + m_ptOffset.x, gRound(rect.yMin)+ m_ptOffset.y,
					gRound(rect.xMax)+ m_ptOffset.x, gRound(rect.yMax)+ m_ptOffset.y);
			}

		};
		void  GtPainterGDI::GtDrawRect (  GtRectI & rect, bool blnOffset )
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, (rect.xMin), (rect.yMin),
					(rect.xMax), (rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, (rect.xMin) + m_ptOffset.x, (rect.yMin)+ m_ptOffset.y,
					(rect.xMax)+ m_ptOffset.x, (rect.yMax)+ m_ptOffset.y);
			}
		};


		//!Draw a Rectangle Frame
		void  GtPainterGDI::GtDrawFrame (  GtRectF & rect, bool blnOffset )
		{
			GtSetSystemPen();
			SelectObject(m_hdcCurr, m_ptrSysPen);	
			if(!blnOffset)
			{
				::MoveToEx(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMin), NULL);
				::LineTo(m_hdcCurr, gRound(rect.xMax), gRound(rect.yMin));
				::LineTo(m_hdcCurr, gRound(rect.xMax), gRound(rect.yMax));
				::LineTo(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMax));
				::LineTo(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMin));
			}else{
				::MoveToEx(m_hdcCurr, gRound(rect.xMin)+ m_ptOffset.x, gRound(rect.yMin)+ m_ptOffset.y, NULL);
				::LineTo(m_hdcCurr, gRound(rect.xMax)+ m_ptOffset.x, gRound(rect.yMin)+ m_ptOffset.y);
				::LineTo(m_hdcCurr, gRound(rect.xMax)+ m_ptOffset.x, gRound(rect.yMax)+ m_ptOffset.y);
				::LineTo(m_hdcCurr, gRound(rect.xMin)+ m_ptOffset.x, gRound(rect.yMax)+ m_ptOffset.y);
				::LineTo(m_hdcCurr, gRound(rect.xMin)+ m_ptOffset.x, gRound(rect.yMin)+ m_ptOffset.y);
			}
			return;
		}; 

		void  GtPainterGDI::GtDrawFrame (  GtRectI & rect, bool blnOffset )
		{
			GtSetSystemPen();
			SelectObject(m_hdcCurr, m_ptrSysPen);			
			if(!blnOffset)
			{
				::MoveToEx(m_hdcCurr, (rect.xMin), (rect.yMin), NULL);
				::LineTo(m_hdcCurr, (rect.xMax), (rect.yMin));
				::LineTo(m_hdcCurr, (rect.xMax), (rect.yMax));
				::LineTo(m_hdcCurr, (rect.xMin), (rect.yMax));
				::LineTo(m_hdcCurr, (rect.xMin), (rect.yMin));
			}else{
				::MoveToEx(m_hdcCurr, (rect.xMin)+ m_ptOffset.x, (rect.yMin)+ m_ptOffset.y, NULL);
				::LineTo(m_hdcCurr, (rect.xMax)+ m_ptOffset.x, (rect.yMin)+ m_ptOffset.y);
				::LineTo(m_hdcCurr, (rect.xMax)+ m_ptOffset.x, (rect.yMax)+ m_ptOffset.y);
				::LineTo(m_hdcCurr, (rect.xMin)+ m_ptOffset.x, (rect.yMax)+ m_ptOffset.y);
				::LineTo(m_hdcCurr, (rect.xMin)+ m_ptOffset.x, (rect.yMin)+ m_ptOffset.y);
			}
			return;
		};
		//!Draw a gRounded Rectangle
		void  GtPainterGDI::GtDrawRoundedRect (  GtRectF & rect, float radius, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
			::RoundRect(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMin), 
				gRound(rect.xMax), gRound(rect.yMax), gRound(radius), gRound(radius));
			}else{
			::RoundRect(m_hdcCurr, gRound(rect.xMin + m_ptOffset.x), gRound(rect.yMin + m_ptOffset.y), 
				gRound(rect.xMax + m_ptOffset.x), gRound(rect.yMax + m_ptOffset.y), gRound(radius), gRound(radius));
			}

		};
		void  GtPainterGDI::GtDrawRoundedRect (  GtRectI & rect, int radius, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::RoundRect(m_hdcCurr, (rect.xMin), (rect.yMin),
					(rect.xMax), (rect.yMax), radius, radius);
			}else{
				::RoundRect(m_hdcCurr, (rect.xMin + m_ptOffset.x), (rect.yMin + m_ptOffset.y),
					(rect.xMax + m_ptOffset.x), (rect.yMax + m_ptOffset.y), radius, radius);
			}
		};
		//!Erase the graphics in the rectangle
		void  GtPainterGDI::GtEraseRect (  GtRectF & rect, bool blnOffset )
		{
			GtBrush brush(GtColor(255,255,255,255));
			this->m_objBrush = brush;
			GtSetSystemPen();
			GtSetSystemBrush();
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMin), gRound(rect.xMax), gRound(rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, gRound(rect.xMin) + m_ptOffset.x, gRound(rect.yMin) + m_ptOffset.y,
					gRound(rect.xMax) + m_ptOffset.x, gRound(rect.yMax) + m_ptOffset.y);
			}
		};
		void  GtPainterGDI::GtEraseRect (  GtRectI & rect, bool blnOffset )
		{
			GtBrush brush(GtColor(255,255,255,255));
			this->m_objBrush = brush;
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, (rect.xMin), (rect.yMin), (rect.xMax), (rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, (rect.xMin) + m_ptOffset.x, (rect.yMin) + m_ptOffset.y,
					(rect.xMax) + m_ptOffset.x, (rect.yMax) + m_ptOffset.y);
			}
		};
		void  GtPainterGDI::GtEraseRect ( int x, int y, int width, int height, bool blnOffset )
		{
			GtBrush brush(GtColor(255,255,255,255));
			this->m_objBrush = brush;
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, (x), (y), (x + width), (y + height));
			}else{
				::Rectangle(m_hdcCurr, (x + m_ptOffset.x), (y + m_ptOffset.y),
					(x + width + m_ptOffset.x), (y + height + m_ptOffset.y));
			}
		};
		//!Fill the rectangle
		void  GtPainterGDI::GtFillRect (  GtRectF & rect, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMin), gRound(rect.xMax), gRound(rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, gRound(rect.xMin + m_ptOffset.x), gRound(rect.yMin + m_ptOffset.y),
					gRound(rect.xMax + m_ptOffset.x), gRound(rect.yMax + m_ptOffset.y));
			}
		};
		void  GtPainterGDI::GtFillRect (  GtRectI & rect, bool blnOffset)
		{

			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, (rect.xMin), (rect.yMin), (rect.xMax), (rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, (rect.xMin + m_ptOffset.x), (rect.yMin + m_ptOffset.y),
					(rect.xMax + m_ptOffset.x), (rect.yMax + m_ptOffset.y));
			}
		};
		void  GtPainterGDI::GtFillRect (  GtRectF & rect,  GtColor & val, bool blnOffset )
		{
			GtBrush brush(val);
			m_objBrush = brush;
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, gRound(rect.xMin), gRound(rect.yMin), gRound(rect.xMax), gRound(rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, gRound(rect.xMin + m_ptOffset.x), gRound(rect.yMin + m_ptOffset.y),
					gRound(rect.xMax + m_ptOffset.x), gRound(rect.yMax + m_ptOffset.y));
			}
		};
		void  GtPainterGDI::GtFillRect (  GtRectI & rect,  GtColor & val, bool blnOffset )
		{
			GtBrush brush(val);
			m_objBrush = brush;
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, (rect.xMin), (rect.yMin), (rect.xMax), (rect.yMax));
			}else{
				::Rectangle(m_hdcCurr, (rect.xMin + m_ptOffset.x), (rect.yMin + m_ptOffset.y),
					(rect.xMax + m_ptOffset.x), (rect.yMax + m_ptOffset.y));
			}
		};
		void  GtPainterGDI::GtFillRect ( int x, int y, int width, int height, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);

			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, (x), (y), (x + width), (y + height));
			}else{
				::Rectangle(m_hdcCurr, (x + m_ptOffset.x), (y + m_ptOffset.y),
					(x + width + m_ptOffset.x), (y + height + m_ptOffset.y));
			}
		};
		void  GtPainterGDI::GtFillRect ( int x, int y, int width, int height,  GtColor & val, bool blnOffset )
		{	
			GtBrush brush(val);
			m_objBrush = brush;
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Rectangle(m_hdcCurr, (x), (y), (x + width), (y + height));
			}else{
				::Rectangle(m_hdcCurr, (x + m_ptOffset.x), (y + m_ptOffset.y),
					(x + width + m_ptOffset.x), (y + height + m_ptOffset.y));
			}
		};

		//!Draw Triangles
		void GtPainterGDI::GtDrawTriangleUp(GtRectI& rect, int shrink, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);

			//draw triangles
			GtPoint3DI pos;
			GtPolylineI tri;
			if(!blnOffset)
			{
				//top triangle
				pos.x = rect.xMin + (long)((double)rect.Width() / 2.0f);
				pos.y = rect.yMin + shrink;
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink;
				pos.y = rect.yMax - shrink;
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink;
				pos.y = rect.yMax - shrink;
				tri.PushBack(pos);
			}else{
				//top triangle
				pos.x = rect.xMin + (long)((double)rect.Width() / 2.0f) + m_ptOffset.x;
				pos.y = rect.yMin + shrink + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink + m_ptOffset.x;
				pos.y = rect.yMax - shrink + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink + m_ptOffset.x;
				pos.y = rect.yMax - shrink + m_ptOffset.y;
				tri.PushBack(pos);
			}
			GtDrawPolygon(tri);
			return;
		};
		void GtPainterGDI::GtDrawTriangleDown(GtRectI& rect, int shrink, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);

			//draw triangles
			GtPoint3DI pos;
			GtPolylineI tri;
			if(!blnOffset)
			{
				//bottom triangle
				pos.x = rect.xMin + (long)((double)rect.Width() / 2.0f);
				pos.y = rect.yMax - shrink;
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink;
				pos.y = rect.yMin + shrink;
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink;
				pos.y = rect.yMin + shrink;
				tri.PushBack(pos);
			}else{
				//bottom triangle
				pos.x = rect.xMin + (long)((double)rect.Width() / 2.0f) + m_ptOffset.x;
				pos.y = rect.yMax - shrink + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink + m_ptOffset.x;
				pos.y = rect.yMin + shrink + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink + m_ptOffset.x;
				pos.y = rect.yMin + shrink + m_ptOffset.y;
				tri.PushBack(pos);
			}
			GtDrawPolygon(tri);
			return;
		};
		void GtPainterGDI::GtDrawTriangleLeft(GtRectI& rect, int shrink, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			GtPoint3DI pos;
			GtPolylineI tri;

			if(!blnOffset)
			{
				//draw triangles
				pos.x = rect.xMin + shrink;
				pos.y = rect.yMin + (long)((double)rect.Height() / 2.0f);
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink;
				pos.y = rect.yMax - shrink;
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink;
				pos.y = rect.yMin + shrink;
				tri.PushBack(pos);
			}else{
			//draw triangles
				pos.x = rect.xMin + shrink + m_ptOffset.x;
				pos.y = rect.yMin + (long)((double)rect.Height() / 2.0f) + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink + m_ptOffset.x;
				pos.y = rect.yMax - shrink + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMax - shrink + m_ptOffset.x;
				pos.y = rect.yMin + shrink + m_ptOffset.y;
				tri.PushBack(pos);
			}

			GtDrawPolygon(tri);

			return;
		};
		void GtPainterGDI::GtDrawTriangleRight(GtRectI& rect, int shrink, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);

			
			GtPoint3DI pos;
			GtPolylineI tri;

			if(!blnOffset)
			{
				//draw triangles
				pos.x = rect.xMax - shrink;
				pos.y = rect.yMin + (long)((double)rect.Height() / 2.0f);
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink;
				pos.y = rect.yMin + shrink;
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink;
				pos.y = rect.yMax - shrink;
				tri.PushBack(pos);
			}else{
				//draw triangles
				pos.x = rect.xMax - shrink + m_ptOffset.x;
				pos.y = rect.yMin + (long)((double)rect.Height() / 2.0f) + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink + m_ptOffset.x;
				pos.y = rect.yMin + shrink + m_ptOffset.y;
				tri.PushBack(pos);
				pos.x = rect.xMin + shrink + m_ptOffset.x;
				pos.y = rect.yMax - shrink + m_ptOffset.y;
				tri.PushBack(pos);
			}

			GtDrawPolygon(tri);

			return;
		};
		//!Draw Ellipse
		void GtPainterGDI::GtDrawEllipse(GtRectI& rect, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			if(!blnOffset)
			{
				::Ellipse(m_hdcCurr, rect.xMin, rect.yMin, rect.xMax, rect.yMax);
			}else{
				::Ellipse(m_hdcCurr, rect.xMin + m_ptOffset.x, rect.yMin + m_ptOffset.y,
					rect.xMax + m_ptOffset.x, rect.yMax + m_ptOffset.y);
			}
		};

		//!Draw Circle
		void GtPainterGDI::GtDrawCircle(GtPoint3DI & center, int radius, bool blnOffset)
		{
			GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);	
			if(!blnOffset)
			{
				::Ellipse(m_hdcCurr, (center.x - radius), (center.y - radius),
					(center.x + radius), (center.y + radius));
			}else{
				::Ellipse(m_hdcCurr, (center.x - radius + m_ptOffset.x), (center.y - radius + m_ptOffset.y),
					(center.x + radius + m_ptOffset.x), (center.y + radius + m_ptOffset.y));
			}
		};

		void GtPainterGDI::GtDrawPie(GtPoint3DI & center, int radius,float sngStartDeg,float sngSpan, bool blnOffset)
		{
			GtPoint3DF ptTemp;
			double dblStartRad, dblEndRad, degRad;
		    GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			GtPolylineF points;
			degRad = 0.0174532925;//one degree
			if(!blnOffset)
			{
				//first and last point are center, right hand rule wrap
				ptTemp.x = (double)center.x;
				ptTemp.y = (double)center.y;
				points.PushBack(ptTemp);

				//next first point on arc
				deg2rad(sngStartDeg, dblStartRad);
				deg2rad((sngStartDeg + sngSpan), dblEndRad);
				//points on arc
				for(double i = dblStartRad; i < dblEndRad; )
				{
					ptTemp.x = radius * cos (i) + center.x;
					ptTemp.y = radius * sin (i) + center.y;

					points.PushBack(ptTemp);

					i += (2.0f * degRad);//2 degree increments
				}
				//last point on arc
				ptTemp.x = radius * cos (dblEndRad) + center.x;
				ptTemp.y = radius * sin (dblEndRad) + center.y;
				points.PushBack(ptTemp);

				//center point close
				ptTemp.x = (double)center.x;
				ptTemp.y = (double)center.y;
				points.PushBack(ptTemp);


				this->GtDrawPolygon(points);
				this->GtDrawPolyline(points);

			}else{
				//first and last point are center, right hand rule wrap
				ptTemp.x = (double)center.x + m_ptOffset.x;
				ptTemp.y = (double)center.y + m_ptOffset.y;
				points.PushBack(ptTemp);

				//next first point on arc
				deg2rad(sngStartDeg, dblStartRad);
				deg2rad((sngStartDeg + sngSpan), dblEndRad);
				//points on arc
				for(double i = dblStartRad; i < dblEndRad; )
				{
					ptTemp.x = radius * cos (i) + m_ptOffset.x;
					ptTemp.y = radius * sin (i) + m_ptOffset.y;

					points.PushBack(ptTemp);

					i += (2.0f * degRad);//2 degree increments
				}
				//last point on arc
				ptTemp.x = radius * cos (dblEndRad)+ m_ptOffset.x;
				ptTemp.y = radius * sin (dblEndRad)+ m_ptOffset.y;
				points.PushBack(ptTemp);

				//center point close
				ptTemp.x = (double)center.x + m_ptOffset.x;
				ptTemp.y = (double)center.y + m_ptOffset.y;
				points.PushBack(ptTemp);

				this->GtDrawPolygon(points);
				this->GtDrawPolyline(points);
			}
		
		};

		void GtPainterGDI::GtDrawArcPie(GtPoint3DI & center, int inRad, int outRad, float sngStartDeg, float sngSpan, bool blnOffset)
		{
			GtPoint3DF ptTemp;
			double dblStartRad, dblEndRad, degRad;
		    GtSetSystemPen();
			GtSetSystemBrush();
			SelectObject(m_hdcCurr, m_ptrSysPen);
			SelectObject(m_hdcCurr, m_ptrSysBrush);
			GtPolylineF points;
			degRad = 0.0174532925;//one degree
			if(!blnOffset)
			{				
				deg2rad(sngStartDeg, dblStartRad);
				deg2rad((sngStartDeg + sngSpan), dblEndRad);
				//first and last point are center, right hand rule wrap
				ptTemp.x = inRad * cos (dblStartRad) + center.x;
				ptTemp.y = inRad * sin (dblStartRad) + center.y;
				points.PushBack(ptTemp);

				ptTemp.x = outRad * cos (dblStartRad) + center.x;
				ptTemp.y = outRad * sin (dblStartRad) + center.y;
				points.PushBack(ptTemp);

				//next first point on arc
				//points on outer arc
				for(double i = dblStartRad; i < dblEndRad; )
				{
					ptTemp.x = outRad * cos (i) + center.x;
					ptTemp.y = outRad * sin (i) + center.y;
					points.PushBack(ptTemp);

					i += (2.0f * degRad);//2 degree increments
				}

				//last point on arc
				ptTemp.x = outRad * cos (dblEndRad) + center.x;
				ptTemp.y = outRad * sin (dblEndRad) + center.y;
				points.PushBack(ptTemp);

				//points on outer arc
				for(double i = dblEndRad; i > dblStartRad; )
				{
					ptTemp.x = inRad * cos (i) + center.x;
					ptTemp.y = inRad * sin (i) + center.y;
					points.PushBack(ptTemp);

					i -= (2.0f * degRad);//2 degree increments
				}

				ptTemp.x = inRad * cos (dblStartRad) + center.x;
				ptTemp.y = inRad * sin (dblStartRad) + center.y;
				points.PushBack(ptTemp);

				this->GtDrawPolygon(points);
				this->GtDrawPolyline(points);
			}else{
				deg2rad(sngStartDeg, dblStartRad);
				deg2rad((sngStartDeg + sngSpan), dblEndRad);
				//first and last point are center, right hand rule wrap
				ptTemp.x = inRad * cos (dblStartRad) + center.x + m_ptOffset.x;
				ptTemp.y = inRad * sin (dblStartRad) + center.y + m_ptOffset.y;
				points.PushBack(ptTemp);

				ptTemp.x = outRad * cos (dblStartRad) + center.x + m_ptOffset.x;
				ptTemp.y = outRad * sin (dblStartRad) + center.y + m_ptOffset.y;
				points.PushBack(ptTemp);

				//next first point on arc
				//points on outer arc
				for(double i = dblStartRad; i < dblEndRad; )
				{
					ptTemp.x = outRad * cos (i) + center.x + m_ptOffset.x;
					ptTemp.y = outRad * sin (i) + center.y + m_ptOffset.y;
					points.PushBack(ptTemp);

					i += (2.0f * degRad);//2 degree increments
				}

				//last point on arc
				ptTemp.x = outRad * cos (dblEndRad) + center.x + m_ptOffset.x;
				ptTemp.y = outRad * sin (dblEndRad) + center.y + m_ptOffset.y;
				points.PushBack(ptTemp);

				//points on outer arc
				for(double i = dblEndRad; i > dblStartRad; )
				{
					ptTemp.x = inRad * cos (i) + center.x + m_ptOffset.x;
					ptTemp.y = inRad * sin (i) + center.y + m_ptOffset.y;
					points.PushBack(ptTemp);

					i -= (2.0f * degRad);//2 degree increments
				}

				ptTemp.x = inRad * cos (dblStartRad) + center.x + m_ptOffset.x;
				ptTemp.y = inRad * sin (dblStartRad) + center.y + m_ptOffset.y;
				points.PushBack(ptTemp);

				this->GtDrawPolygon(points);
				this->GtDrawPolyline(points);
			}
		
		};

		//!Draw a Static Text string
		void GtPainterGDI::GtDrawStaticText (  std::string & strText, GtPoint3DF & topLeftPos, bool blnOffset )
		{
			//wcslen for wide char, strlen for standard char
			GtSetSystemFont(); 
			SelectObject(m_hdcCurr,m_winFont.m_hFont);
			SetBkMode(m_hdcCurr, TRANSPARENT);
			if(!blnOffset)
			{
			::TextOut(m_hdcCurr,gRound(topLeftPos.x),gRound(topLeftPos.y),
				(LPCSTR)strText.c_str(), strlen(strText.c_str()));
			}else{
			::TextOut(m_hdcCurr,gRound(topLeftPos.x + m_ptOffset.x),gRound(topLeftPos.y + m_ptOffset.y),
				(LPCSTR)strText.c_str(), strlen(strText.c_str()));
			}
			//set back to opaque
			SetBkMode(m_hdcCurr, OPAQUE);

		};
		void  GtPainterGDI::GtDrawStaticText (  std::string & strText, GtPoint3DI & topLeftPos, bool blnOffset )
		{
			GtSetSystemFont(); 
			SelectObject(m_hdcCurr,m_winFont.m_hFont);
			SetBkMode(m_hdcCurr, TRANSPARENT);
			if(!blnOffset)
			{
			::TextOut(m_hdcCurr,(topLeftPos.x),(topLeftPos.y),
				(LPCSTR)strText.c_str(), strlen(strText.c_str()));
			}else{
			::TextOut(m_hdcCurr,(topLeftPos.x + m_ptOffset.x),(topLeftPos.y + m_ptOffset.y),
				(LPCSTR)strText.c_str(), strlen(strText.c_str()));
			}
			SetBkMode(m_hdcCurr, OPAQUE);
		};
		void  GtPainterGDI::GtDrawStaticText ( std::string & strText, int left, int top, bool blnOffset )
		{
			GtSetSystemFont();
			SelectObject(m_hdcCurr,m_winFont.m_hFont);
			SelectObject(m_hdcCurr,m_ptrSysBrush);
			if(!blnOffset)
			{
			::TextOut(m_hdcCurr,(left),(top),
				(LPCSTR)strText.c_str(), strlen(strText.c_str()));
			}else{
			::TextOut(m_hdcCurr,(left + m_ptOffset.x),(top + m_ptOffset.y),
				(LPCSTR)strText.c_str(), strlen(strText.c_str()));
			}	
		};
		////!Draw the text string in the bounding rectangle
		void  GtPainterGDI::GtDrawText (  std::string & strText, GtPoint3DF & pos,  bool blnOffset )
		{
			//BOOL ExtTextOut(
			//  _In_  HDC hdc,
			//  _In_  int X,
			//  _In_  int Y,
			//  _In_  UINT fuOptions,
			//  _In_  const RECT *lprc,
			//  _In_  LPCTSTR lpString,
			//  _In_  UINT cbCount,
			//  _In_  const INT *lpDx
			//);
			GtSetSystemFont(); 
			SelectObject(m_hdcCurr,m_winFont.m_hFont);
			SetBkMode(m_hdcCurr, TRANSPARENT);
			if(!blnOffset)
			{
				::ExtTextOut(m_hdcCurr,gRound(pos.x),gRound(pos.y),ETO_CLIPPED,
					NULL, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}else{
				::ExtTextOut(m_hdcCurr,gRound(pos.x + m_ptOffset.x),gRound(pos.y + m_ptOffset.y),ETO_CLIPPED,
					NULL, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}

			SetBkMode(m_hdcCurr, OPAQUE);

			return;
		};
		void  GtPainterGDI::GtDrawText (  std::string & strText, GtPoint3DI & pos,  bool blnOffset )
		{
			GtSetSystemFont(); 
			SelectObject(m_hdcCurr,m_winFont.m_hFont);
			SetBkMode(m_hdcCurr, TRANSPARENT);
			if(!blnOffset)
			{
				::ExtTextOut(m_hdcCurr,(pos.x),(pos.y),ETO_CLIPPED,
					NULL, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}else{
				::ExtTextOut(m_hdcCurr,(pos.x + m_ptOffset.x),(pos.y + m_ptOffset.y),ETO_CLIPPED,
					NULL, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}
			SetBkMode(m_hdcCurr, OPAQUE);
			return;
		};
		void  GtPainterGDI::GtDrawText (  std::string & strText, GtRectF & boundRect, int flags,  bool blnOffset)
		{
			RECT bound;	

		
			GtSetSystemFont(); 
			SelectObject(m_hdcCurr,m_winFont.m_hFont);
			SetBkMode(m_hdcCurr, TRANSPARENT);
			if(!blnOffset)
			{
				bound.left = gRound(boundRect.xMin);
				bound.right = gRound(boundRect.xMax);
				bound.top = gRound(boundRect.yMin);
				bound.bottom = gRound(boundRect.yMax);

				::ExtTextOut(m_hdcCurr,(bound.left),(bound.top),ETO_CLIPPED,
					&bound, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}else{
				bound.left = gRound(boundRect.xMin + m_ptOffset.x);
				bound.right = gRound(boundRect.xMax + m_ptOffset.x);
				bound.top = gRound(boundRect.yMin + m_ptOffset.y);
				bound.bottom = gRound(boundRect.yMax + m_ptOffset.y);

				::ExtTextOut(m_hdcCurr,(bound.left),(bound.top),ETO_CLIPPED,
					&bound, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}
			SetBkMode(m_hdcCurr, OPAQUE);
			return;
		};
		void  GtPainterGDI::GtDrawText (  std::string & strText, GtRectI & boundRect, int flags,  bool blnOffset)
		{
			RECT bound;	
			GtSetSystemFont(); 
			SelectObject(m_hdcCurr,m_winFont.m_hFont);
			SetBkMode(m_hdcCurr, TRANSPARENT);
			if(!blnOffset)
			{
				bound.left = (boundRect.xMin);
				bound.right = (boundRect.xMax);
				bound.top = (boundRect.yMin);
				bound.bottom = (boundRect.yMax);

				::ExtTextOut(m_hdcCurr,(bound.left),(bound.top),ETO_CLIPPED,
					&bound, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}else{
				bound.left = (boundRect.xMin + m_ptOffset.x);
				bound.right = (boundRect.xMax + m_ptOffset.x);
				bound.top = (boundRect.yMin + m_ptOffset.y);
				bound.bottom = (boundRect.yMax + m_ptOffset.y);

				::ExtTextOut(m_hdcCurr,(bound.left),(bound.top),ETO_CLIPPED,
					&bound, (LPCSTR)strText.c_str(), strlen(strText.c_str()), NULL);
			}

			SetBkMode(m_hdcCurr, OPAQUE);
			return;
		};
		//!Draw the Pixmap in the target rectangle or at the desired point
		void  GtPainterGDI::GtDrawPixmap (  GtRectF & target,  GtPixmap & pixmap,  GtRectF & source, bool blnOffset )
		{
			//TODO
		};
		void  GtPainterGDI::GtDrawPixmap (  GtRectI & target,  GtPixmap & pixmap,  GtRectI & source, bool blnOffset )
		{
			//TODO
		};
		void  GtPainterGDI::GtDrawPixmap (  GtPoint3DF & point,  GtPixmap & pixmap,  GtRectF & source, bool blnOffset )
		{
			//TODO
		};
		void  GtPainterGDI::GtDrawPixmap (  GtPoint3DI & point,  GtPixmap & pixmap,  GtRectI & source, bool blnOffset )
		{
			//TODO
		};
		void  GtPainterGDI::GtDrawPixmap (  GtPoint3DF & point,  GtPixmap & pixmap, bool blnOffset )
		{
			//TODO
		};
		void  GtPainterGDI::GtDrawPixmap (  GtPoint3DI & point,  GtPixmap & pixmap, bool blnOffset )
		{
			//TODO
		};
		//!Tile the Pixmap in the bounding rectangle
		void  GtPainterGDI::GtDrawTiledPixmap (  GtRectF & rectangle,  GtPixmap & pixmap, bool blnOffset)
		{
			//TODO
		};
		void  GtPainterGDI::GtDrawTiledPixmap (  GtRectI & rectangle,  GtPixmap & pixmap, bool blnOffset)
		{
			//TODO
		};

		//!Translate the coordinate system
		void GtPainterGDI::GtTranslate(int dx, int dy)
		{
			//reset
			SetViewportOrgEx(m_hdcCurr,0,0,NULL);

			m_ptOffset.x += dx;
			m_ptOffset.y += dy;
			//::MoveToEx(m_hdcCurr,m_ptOffset.x,m_ptOffset.y,NULL);
			SetViewportOrgEx(m_hdcCurr,m_ptOffset.x,m_ptOffset.y,NULL);
		};
		void GtPainterGDI::GtTranslate(GtPoint3DI delta)
		{
			//reset
			SetViewportOrgEx(m_hdcCurr,0,0,NULL);

			m_ptOffset.x += delta.x;
			m_ptOffset.y += delta.y;
			m_ptOffset.z += delta.z;

			//::MoveToEx(m_hdcCurr,m_ptOffset.x,m_ptOffset.y,NULL);
			SetViewportOrgEx(m_hdcCurr,m_ptOffset.x,m_ptOffset.y,NULL);
		};

		void GtPainterGDI::GtSetSystemPen(void)
		{

			if(m_ptrSysPen)
			{
				DeleteObject(m_ptrSysPen);
				m_ptrSysPen = NULL;
			}

			COLORREF qLineColor;
			qLineColor = RGB(m_objPen.Get_objColor().m_intRed,
				m_objPen.Get_objColor().m_intGreen,
				m_objPen.Get_objColor().m_intBlue);
			m_ptrSysPen = CreatePen(PS_SOLID, gRound(m_objPen.Get_sngWidth()), qLineColor);

			return;
		};
		void GtPainterGDI::GtSetSystemBrush(void)
		{
			if(m_ptrSysBrush)
			{
				DeleteObject(m_ptrSysBrush);
				m_ptrSysBrush = NULL;
			}
			GtColor bg = m_objBrush.Get_objColor();
			COLORREF bColor = RGB(bg.m_intRed,bg.m_intGreen,bg.m_intBlue);
			switch(m_objBrush.Get_objStyle())
			{
			
			case Dense1Pattern: //TODO
			case Dense2Pattern: //TODO
			case Dense3Pattern: //TODO
			case Dense4Pattern: //TODO
			case Dense5Pattern: //TODO
			case Dense6Pattern: //TODO
			case Dense7Pattern: //TODO
			case SolidPattern:
				{
					m_ptrSysBrush = ::CreateSolidBrush(bColor);
					break;
				}
			case HorzontalPattern:
				{
					//hatch forggRound always black
					m_ptrSysBrush = ::CreateHatchBrush(HS_HORIZONTAL, bColor);
					break;
				}
			case VerticalPattern:
				{
					//hatch forggRound always black
					m_ptrSysBrush = ::CreateHatchBrush(HS_VERTICAL, bColor);
					break;
				}
			case CrossPattern:
				{
					//hatch forggRound always black
					m_ptrSysBrush = ::CreateHatchBrush(HS_CROSS, bColor);
					break;
				}
			case BackDiagPattern:
				{
					//hatch forggRound always black
					m_ptrSysBrush = ::CreateHatchBrush(HS_BDIAGONAL, bColor);
					break;
				}
			case ForeDiagPattern:
				{
					//hatch forggRound always black
					m_ptrSysBrush = ::CreateHatchBrush(HS_FDIAGONAL, bColor);
					break;
				}
			case DiagCrossPattern:
				{
					//hatch forggRound always black
					m_ptrSysBrush = ::CreateHatchBrush(HS_DIAGCROSS, bColor);
					break;
				}
			case LinearGradientPattern:
			case RadialGradientPattern:
			default:
				{
					m_ptrSysBrush = ::CreateSolidBrush(bColor);
					break;
				}
			}
		};

		void GtPainterGDI::GtSetSystemFont(void)
		{

			std::wstring strFont = m_objFont.Get_strFontFamily();
			int intPoint = m_objFont.Get_intPoint();
			
			if(m_winFont.m_hFont)
			{
				/*DeleteObject(m_winFont.m_hFont);
				m_winFont.m_hFont = NULL;*/
				return;
			}

			m_winFont.m_hFont = CreateFont(intPoint, 0, 0, 0,FW_NORMAL,
				FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_ROMAN,
				(LPCSTR)strFont.c_str());

			// need a DC to query font data
			HDC    hdc  = GetDC(0);
			HANDLE hold = SelectObject(hdc, m_winFont.m_hFont);

			// get font settings
			GetTextMetrics(hdc, &(m_winFont.m_textMetrics)) ;
			// cleanup
			SelectObject(hdc, hold);
			ReleaseDC(0, hdc);

			return;

		};


	};//end namespace GtCore

};//end namespace GT

