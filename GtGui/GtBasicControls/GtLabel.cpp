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

#include ".\GtLabel.h"

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtLabel::GtLabel(GtObject* ptrParent)
			: GtWidget(ptrParent)
		{
			m_strType = "GtLabel";
		};
		//virtual destructor
		GtLabel::~GtLabel(void)
		{

		};
			//!Custom Event Processing
		int GtLabel::HandleEvent(GtEvent * ptrEvent)
		{
			return 0;
		};
		//!Custom Widget Painting
		int GtLabel::OnPaint(GtPainter * painter)
		{
			//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen oldPen;
			GtBrush oldBrush;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);

			GtPoint3DI textPos;
			textPos.x = m_objFrame.xMin + 5;
			textPos.y = m_objFrame.yMin + 2;
			painter->GtDrawStaticText(m_strText,textPos);
			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 0;
		};		

	};//end namespace GtCore

};//end namespace GT