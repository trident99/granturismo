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

#include ".\GtProgressBar.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtProgressBar::GtProgressBar(GtObject* ptrParent)
			:GtSlider(ptrParent)
		{
			m_intMin = 0;
			m_intMax = 100;
			m_intValue = 0;
		};

		//!Virtual destructor
		GtProgressBar::~GtProgressBar(void)
		{
			m_intValue = 0;
		};


		//!Custom Event Processing
		int GtProgressBar::HandleEvent(GtEvent * ptrEvent)
		{
			return 0;
		};
		//!Custom Widget Painting
		int GtProgressBar::OnPaint(GtPainter * painter)
		{
			//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen valPen, oldPen;
			GtBrush oldBrush;

			GtPoint3DI checkPos, textPos;
			int width = 4;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);

			//render normal
			//render compact mode
			//draw buttons
			painter->Set_objBrush(GtBrush(GtColor(150,150,150)));
			m_objFrame = m_objFrame;
			m_objFrame.yMax = m_objFrame.yMin + 25;			
			painter->GtDrawRect(m_objFrame);
			
			GtLineI bar;
			float percent = ((float)m_intValue) / ((float)(m_intMax - m_intMin));
			int posX = m_objFrame.xMin + gRound(percent * (m_objFrame.xMax - m_objFrame.xMin));
			
			float halfHeight = (m_objFrame.yMax + m_objFrame.yMin) / 2.0f;
			m_rectBarUpper = m_objFrame;
			m_rectBarUpper.xMin += 2; 
			m_rectBarUpper.xMax = posX; 
			m_rectBarUpper.yMin = m_objFrame.yMin + 5;
			m_rectBarUpper.yMax = gRound(halfHeight);
			painter->Set_objPen(GtPen(GtColor(0,200,0)));
			painter->Set_objBrush(GtBrush(GtColor(0,200,0)));
			painter->GtDrawRect(m_rectBarUpper);

			m_rectBarLower = m_objFrame;
			m_rectBarLower.xMin += 2; 
			m_rectBarLower.xMax = posX; 
			m_rectBarLower.yMin = gRound(halfHeight);
			m_rectBarLower.yMax = m_objFrame.yMax - 5;
			painter->Set_objPen(GtPen(GtColor(0,180,0)));
			painter->Set_objBrush(GtBrush(GtColor(0,180,0)));
			painter->GtDrawRect(m_rectBarLower);

			//Draw Marker

			bar.m_P0.x = posX ;
			bar.m_P0.y = m_objFrame.yMin;
			bar.m_P1.x = posX;
			bar.m_P1.y = m_objFrame.yMin + 25;

			painter->Set_objPen(GtPen(GtColor(0,0,0),SolidLine,4.0));
			painter->GtDrawLine(bar);


			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);

			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT