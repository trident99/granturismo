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

#include ".\GtCheckBox.h"
#include <modGtEvent.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtCheckBox::GtCheckBox(GtObject* ptrParent)
			:GtButton(ptrParent)
		{
			m_blnChecked = false;
		};
			//!Virtual destructor
		GtCheckBox::~GtCheckBox(void)
		{
			
		};

		void GtCheckBox::Set_blnChecked(bool isChecked)
		{
			m_blnChecked = isChecked;
			Toggled.Emit(m_blnChecked);
			this->PostPaint();
		};
		//!Custom Event Processing
		int GtCheckBox::HandleEvent(GtEvent * ptrEvent)
		{
			if(ptrEvent->m_objType == MouseLeftPress)
			{
				m_blnChecked = !m_blnChecked;
			}

			GtButton::HandleEvent(ptrEvent);
			return 0;
		};
		//!Custom Widget Painting
		int GtCheckBox::OnPaint(GtPainter * painter)
		{
			//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen oldPen;
			GtBrush oldBrush;
			GtPoint3DI textPos;
			int width = 4;
			//INITIALIZE PENS AND BRUSHES

			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);

			textPos.x = m_objFrame.xMin + 30;
			textPos.y = m_objFrame.yMin;
			
			m_rectCheck = m_objFrame;
			m_rectCheck.xMax =m_rectCheck.xMin + 25; 
			m_rectCheck.yMax =m_rectCheck.yMin + 25;
			//draw the check box
			painter->GtDrawRect(m_rectCheck);
			//if the box is checked draw the check
			if(m_blnChecked)
			{
				GtLineI fore, back;
				GtPen checkPen;
				checkPen.Set_sngWidth(4);
				painter->Set_objPen(checkPen);

				fore.m_P0.x = m_rectCheck.xMin + 5;
				fore.m_P0.y = m_rectCheck.yMin + 5;
				fore.m_P1.x = m_rectCheck.xMax - 5;
				fore.m_P1.y = m_rectCheck.yMax - 5;
				
				back.m_P0.x = m_rectCheck.xMax - 5;
				back.m_P0.y = m_rectCheck.yMin + 5;
				back.m_P1.x = m_rectCheck.xMin + 5;
				back.m_P1.y = m_rectCheck.yMax - 5;

				painter->GtDrawLine(fore);
				painter->GtDrawLine(back);
			}

			//Draw the text
			painter->Set_objPen(m_objPen);
			painter->GtDrawStaticText(m_strText,textPos);

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);

			return 0;
		};	

	};//end namespace GtCore

};//end namespace GT