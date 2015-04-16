/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
**  Qwt Widget Library
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

#include ".\GtPlotSymbol.h"
#include <modHtlMath.h>

namespace GT
{
	namespace GtChart
	{
			//!Parent set constructor
		GtPlotSymbol::GtPlotSymbol(GtObject* ptrParent)
			:GtObject(ptrParent)
		{
			m_intSize = 5;//default size
			m_objSymType = SymbolPoint;
		};
		GtPlotSymbol::GtPlotSymbol(const GtPlotSymbol & rhs)
		{
			if(this != &rhs)
			{
				m_intSize = rhs.Get_intSize();
				m_objSymType = rhs.Get_objSymType();
				m_objCanvasPos = rhs.Get_objCanvasPos();		
				m_objModelPos = rhs.Get_objModelPos();
			};
		};
			//!Virtual destructor
		GtPlotSymbol::~GtPlotSymbol(void)
		{
			m_objCanvasPos.Zero();
			m_objModelPos.Zero();
		};
		//!Assignment Operator
		GtPlotSymbol & GtPlotSymbol::operator = (const GtPlotSymbol & rhs)
		{
			if(this != &rhs)
			{
				m_intSize = rhs.Get_intSize();
				m_objSymType = rhs.Get_objSymType();
				m_objCanvasPos = rhs.Get_objCanvasPos();		
				m_objModelPos = rhs.Get_objModelPos();
			};
			return *this;

		};
	
		//!Required Draw function for the plot item, must be implemented
		int GtPlotSymbol::Draw( GtPainter *painter)
		{
			if(!painter){return 0;};
			GtRectI rect;
			int sizeHalf = Math::hround(double(m_intSize) / 2.0f);
			rect.xMin = m_objCanvasPos.x - sizeHalf;
			rect.xMax = m_objCanvasPos.x + sizeHalf;
			rect.yMin = m_objCanvasPos.y - sizeHalf;
			rect.yMax = m_objCanvasPos.y + sizeHalf;

			//NOTE WE ARE USING THE PARENT OBJECT'S COLORS
			//FOR BACKGROUND(BRUSH) AND FOREGROUND(PEN)

			switch(m_objSymType)
			{
			case SymbolPoint:
				{
					painter->GtDrawPoint(m_objCanvasPos,m_intSize);
					break;
				}
			case SymbolPlus:
				{
					GtLineI horiz, vert;
					horiz.m_P0.x = rect.xMin;
					horiz.m_P0.y = rect.yMin + sizeHalf;
					horiz.m_P1.x = rect.xMax;
					horiz.m_P1.y = rect.yMin + sizeHalf;

					vert.m_P0.x = rect.xMin + sizeHalf;
					vert.m_P0.y = rect.yMin;
					vert.m_P1.x = rect.xMin + sizeHalf;
					vert.m_P1.y = rect.yMax;
					painter->GtDrawLine(horiz);
					painter->GtDrawLine(vert);
					break;
				}	
			case SymbolCross:
				{
					GtLineI fore, back;
					fore.m_P0.x = rect.xMin;
					fore.m_P0.y = rect.yMin;
					fore.m_P1.x = rect.xMax;
					fore.m_P1.y = rect.yMax;

					back.m_P0.x = rect.xMax;
					back.m_P0.y = rect.yMin;
					back.m_P1.x = rect.xMin;
					back.m_P1.y = rect.yMax;
					painter->GtDrawLine(fore);
					painter->GtDrawLine(back);
					break;
				}				
			case SymbolTriangle:
				{
					painter->GtDrawTriangleUp(rect,0);
					break;
				}	
			case SymbolRect:
				{
					painter->GtFillRect(rect);
					break;
				}
			case SymbolDiamond:
				{
					//draw triangles
					GtPoint3DI pos;
					GtPolylineI diamond;
					//Point 0 bottom
					pos.x = rect.xMin + sizeHalf;
					pos.y = rect.yMin;
					diamond.PushBack(pos);
					//Point 1 right
					pos.x = rect.xMax;
					pos.y = rect.yMin + sizeHalf;
					diamond.PushBack(pos);
					//Point 2 top
					pos.x = rect.xMin + sizeHalf;
					pos.y = rect.yMax;
					diamond.PushBack(pos);
					//Point 3 left
					pos.x = rect.xMin;
					pos.y = rect.yMin + sizeHalf;
					diamond.PushBack(pos);
					//return bottom
					pos.x = rect.xMin + sizeHalf;
					pos.y = rect.yMin;
					diamond.PushBack(pos);

					painter->GtDrawPolygon(diamond);
					break;
				}
			case SymbolStar:
				{
					GtLineI horiz, vert;
					horiz.m_P0.x = rect.xMin;
					horiz.m_P0.y = rect.yMin + sizeHalf;
					horiz.m_P1.x = rect.xMax;
					horiz.m_P1.y = rect.yMin + sizeHalf;

					vert.m_P0.x = rect.xMin + sizeHalf;
					vert.m_P0.y = rect.yMin;
					vert.m_P1.x = rect.xMin + sizeHalf;
					vert.m_P1.y = rect.yMax;
					painter->GtDrawLine(horiz);
					painter->GtDrawLine(vert);

					GtLineI fore, back;
					fore.m_P0.x = rect.xMin;
					fore.m_P0.y = rect.yMin;
					fore.m_P1.x = rect.xMax;
					fore.m_P1.y = rect.yMax;

					back.m_P0.x = rect.xMax;
					back.m_P0.y = rect.yMin;
					back.m_P1.x = rect.xMin;
					back.m_P1.y = rect.yMax;
					painter->GtDrawLine(fore);
					painter->GtDrawLine(back);
					break;
				}

			default:
				{
					painter->GtDrawPoint(m_objCanvasPos,m_intSize);
					break;
				}
			};
			return 1;
		};

	};//end namespace GtChart

};//end namespace GT