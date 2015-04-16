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

#include ".\GtFrame.h"
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtFrame::GtFrame(GtObject* ptrParent)
			: GtWidget(ptrParent)
		{
			m_strType = "GtFrame";
			m_objFrameStyle = FramePlain;
			m_intFrameWidth = 1;
		};
		//virtual destructor
		GtFrame::~GtFrame(void)
		{

		};

		//!Custom Widget Painting
		int GtFrame::OnPaint(GtPainter * ptrPainter)
		{
			//safety check
			if(!ptrPainter){return 0;};
			GtPen inPen, outPen, oldPen;
			GtBrush oldBrush;
			GtRectI inRect, outRect;
			
			int delta = 2;
			//INITIALIZE PENS AND BRUSHES

			//record current painter settings
			oldPen = ptrPainter->Get_objPen();
			oldBrush = ptrPainter->Get_objBrush();
			delta = gRound(outPen.Get_sngWidth() / 2.0f);
			if(delta <= 0){delta = 1;};//minimum delta
			//calculate the rectangles, both inner and outer
			outRect =  m_objFrame;
			inRect.xMin = outRect.xMin + delta;
			inRect.xMax = outRect.xMax - delta;
			inRect.yMin = outRect.yMin + delta;
			inRect.yMax = outRect.yMax - delta;
			//set the pens, brush, draw background
			ptrPainter->Set_objBrush(m_objBackBrush);
			ptrPainter->GtFillRect(outRect);
			//set the inner and outer pens then draw the rects
			switch(m_objFrameStyle)
			{
			case FramePlain:
				{
					//If FramePlain then use outer pen only

					ptrPainter->Set_objPen(m_objPen);
					ptrPainter->GtDrawRect(outRect);
					break;
				}
			case FrameRaised:
				{
					//If FrameRaised then set inPen to the desired
					//set outPen to a lighter version of inPen to create raised effect
					inPen = m_objPen;
					GtColor objFade = m_objPen.Get_objColor();
					objFade.Lighter(25);
					outPen.Set_objColor(objFade);
					//outer first
					ptrPainter->Set_objPen(outPen);
					ptrPainter->GtDrawRect(outRect);
					//inner second
					ptrPainter->Set_objPen(inPen);
					ptrPainter->GtDrawRect(inRect);
					break;
				}

			case FrameSunken:
				{
					//If FrainSunken then set outPen to the desired
					//set inPen to a lighter version of outPen to create sunken effect
					outPen = m_objPen;
					GtColor objFade = m_objPen.Get_objColor();
					objFade.Lighter(25);
					inPen.Set_objColor(objFade);
					//inner first
					ptrPainter->Set_objPen(inPen);
					ptrPainter->GtDrawRect(inRect);
					//outer second
					ptrPainter->Set_objPen(outPen);
					ptrPainter->GtDrawRect(outRect);

					break;
				}
			}//end switch(style)
			//finished, reset old brushes and pens
			ptrPainter->Set_objPen(oldPen);
			ptrPainter->Set_objBrush(oldBrush);
			//call parent class
			GtWidget::OnPaint(ptrPainter);
			return 1;
		};		

	};//end namespace GtCore

};//end namespace GT