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

#include ".\GtButton.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtButton::GtButton(GtObject* ptrParent)
			:GtFrame(ptrParent)
		{
			m_strType = "GtButton";
		};
			//!Virtual destructor
		GtButton::~GtButton(void)
		{
			
		};

		//!Custom Event Processing
		int GtButton::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};
			GtPoint3DI pos, offset, transPos;
			offset = this->RequestOffset();
			pos.x = gRound(ptrEvent->m_objPos.x);
			pos.y = gRound(ptrEvent->m_objPos.y);
			transPos.x = pos.x - offset.x;
			transPos.y = pos.y - offset.y;

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				m_blnToggle = !m_blnToggle;
				this->Toggled.Emit(m_blnToggle);

				m_blnButtonUp = false;	
				Pressed.Emit();
				this->PostPaint();
				return 1;
			}
			if(ptrEvent->m_objType == MouseLeftRelease)
			{

				if((m_blnButtonUp == false)&&
					(m_objFrame.Contains(transPos)))
				{
					//then releasing a click
					Clicked.Emit();
				}

				m_blnButtonUp = true;	
				Released.Emit();
				this->PostPaint();
				return 1;
			}
			return 0;
		};
		//!Custom Widget Painting
		int GtButton::OnPaint(GtPainter * painter)
		{
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen inPen, outPen, oldPen;
			GtBrush oldBrush;
			GtRectI inRect, outRect;
			
			int delta = 2;
			//INITIALIZE PENS AND BRUSHES

			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			delta = gRound(outPen.Get_sngWidth() / 2.0f);
			if(delta <= 0){delta = 1;};//minimum delta
			//calculate the rectangles, both inner and outer
			outRect =  m_objFrame;
			inRect.xMin = outRect.xMin + delta;
			inRect.xMax = outRect.xMax - delta;
			inRect.yMin = outRect.yMin + delta;
			inRect.yMax = outRect.yMax - delta;
			//set the pens, brush, draw background
			if(!m_blnButtonUp)
			{
				//draw pressed mode
				painter->Set_objPen(GtPen(GtColor(0,0,255),SolidLine,4));
				painter->Set_objBrush(GtBrush(GtColor(250,250,120)));
			}else{
				//draw released mode
				painter->Set_objPen(m_objPen);
				painter->Set_objBrush(m_objBackBrush);
			}
			painter->GtDrawRoundedRect(outRect,10);

			GtPoint3DI pos;
			pos.x = m_objFrame.xMin + 5;
			pos.y = m_objFrame.yMin + 10;
			inRect = m_objFrame;
			inRect.xMin += 5;
			inRect.xMax -= 5;
			inRect.yMin += 5;
			inRect.yMax -= 5;
			painter->GtDrawText(m_strText,inRect,(DT_LEFT| DT_WORDBREAK));

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT