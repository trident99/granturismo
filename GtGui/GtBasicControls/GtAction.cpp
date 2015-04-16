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

#include ".\GtAction.h"
#include ".\GtMenu.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
			//!Parent set constructor
		GtAction::GtAction(GtObject* ptrParent)
			:GtWidget(ptrParent)
		{

			m_blnCheckable = false;
			m_blnChecked = false;
			m_blnSeparator = false;
			m_blnIcon = false;
			m_intModifiers = 0;
			m_blnEnabled = true;
			m_ptrData = NULL;
			m_blnHovered = false;
		};
			//!Virtual destructor
		GtAction::~GtAction(void)
		{
			m_blnCheckable = false;
			m_blnChecked = false;
			m_blnSeparator = false;
			m_blnIcon = false;
			m_intModifiers = 0;
			m_blnEnabled = true;
			m_ptrData = NULL;			
		};
		//!Menu Parent Object using a dynamic cast
		GtMenu * GtAction::MenuParent(void)
		{
			return dynamic_cast<GtMenu*>(m_ptrParent);
		};
		//!Conveinience slot for causing a Hovered signal emit
		void GtAction::Hover(void)
		{
			this->Hovered.Emit();
		};
		//!Conveinience slot for causing a Toggled signal emit
		void GtAction::Toggle(void)
		{
			if(m_blnChecked)
			{//currently true, set false
				m_blnChecked = false;
				this->Toggled.Emit(false);
			}else{
				//currently false, set true
				m_blnChecked = true;
				this->Toggled.Emit(true);
			}
		};
		//!Conveinience slot for causing a Triggered signal emit
		void GtAction::Trigger(void)
		{
			this->Triggered.Emit();
		};

		//!Custom Event Processing
		int GtAction::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				if(m_blnCheckable)
				{
					m_blnChecked = !m_blnChecked;
					this->Toggled.Emit(m_blnChecked);
				}

				Triggered.Emit();
				this->PostPaint();
				return 1;
			}


			if( (ptrEvent->m_objType == MouseMove)||
				(ptrEvent->m_objType == MouseHover) )
			{
				GtPoint3DI pos, hoverPos, delta;
				pos.x = gRound(ptrEvent->m_objPos.x);
				pos.y = gRound(ptrEvent->m_objPos.y);

				delta = this->RequestOffset();

				hoverPos.x = pos.x - delta.x;
				hoverPos.y = pos.y - delta.y;
				if(m_objFrame.Contains(hoverPos))
				{
					Hovered.Emit();
					m_blnHovered = true;
					this->PostPaint();
					return 1;
				}
			}
			return 0;
		};
		//!Custom Widget Painting
		int GtAction::OnPaint(GtPainter * painter)
		{
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen oldPen;
			GtBrush oldBrush;
	
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			m_rectCheck = m_objFrame;
			m_rectCheck.xMin = m_rectCheck.xMin + 5;
			m_rectCheck.xMax = m_rectCheck.xMin + 10;
			m_rectCheck.yMin = m_rectCheck.yMin + 5;
			m_rectCheck.yMax = m_rectCheck.yMin + 10;
		
			if(m_blnHovered)
			{
				//draw pressed mode
				painter->Set_objPen(GtPen(GtColor(0,0,255),SolidLine,2));
				painter->Set_objBrush(GtBrush(GtColor(250,250,120)));
			}else{
				//draw released mode
				painter->Set_objPen(GtPen(GtColor(160,160,160),SolidLine,1));
				painter->Set_objBrush(m_objBackBrush);
			}
			painter->GtDrawRect(m_objFrame);

			//if the box is checked draw the check
			if(m_blnChecked)
			{
				GtLineI fore, back;
				GtPen checkPen;
				checkPen.Set_sngWidth(4);
				painter->Set_objPen(checkPen);

				fore.m_P0.x = m_rectCheck.xMin;
				fore.m_P0.y = m_rectCheck.yMin;
				fore.m_P1.x = m_rectCheck.xMax;
				fore.m_P1.y = m_rectCheck.yMax;

				back.m_P0.x = m_rectCheck.xMax;
				back.m_P0.y = m_rectCheck.yMin;
				back.m_P1.x = m_rectCheck.xMin;
				back.m_P1.y = m_rectCheck.yMax;

				painter->GtDrawLine(fore);
				painter->GtDrawLine(back);
			}

			GtPoint3DI pos;
			pos.x = m_objFrame.xMin + 25;
			pos.y = m_objFrame.yMin;
			painter->GtDrawStaticText(m_strText,pos);

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT