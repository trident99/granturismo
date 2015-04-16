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

#include ".\GtToolBar.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtToolBar::GtToolBar(GtObject* ptrParent)
			:GtFrame(ptrParent)
		{
			
		};
			//!Virtual destructor
		GtToolBar::~GtToolBar(void)
		{
			
		};

		//!Custom Event Processing
		int GtToolBar::HandleEvent(GtEvent * ptrEvent)
		{
			return 0;
		};
		//!Custom Widget Painting
		int GtToolBar::OnPaint(GtPainter * painter)
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
		
				//draw released mode
			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);
			painter->GtDrawRoundedRect(m_objFrame,5);

			painter->Set_objBrush(GtBrush(GtColor(160,160,160)));
			m_rectHandle = m_objFrame;
			m_rectHandle.xMax = m_rectHandle.xMin + 5;
			painter->GtDrawRoundedRect(m_rectHandle,5);

			//draw buttons and menus local
			GtWidget::OnPaint(painter);

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtCore

};//end namespace GT