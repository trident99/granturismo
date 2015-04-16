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

#ifndef GT_BUTTON_GRID_H
#define GT_BUTTON_GRID_H

#include <GtBasicControls\GtButton.h>
using namespace HTL;
using namespace GT::GtCore;
using namespace GT::GtGui;

class ButtonGrid : public GtFrame
{
public:
	//!Parent set constructor
	ButtonGrid(GtObject* ptrParent = NULL);
	//!Virtual destructor
	virtual ~ButtonGrid(void);

	void Initialize(void);
	//MEMBER VARIABLES////////////////////////
	//!The boolean flag that indicates if the button is a toggle button type
	//GTOBJECT_MEMVAR_BYVAL(public, bool, blnToggle);

	GtButton * m_ptrButton01;
	GtButton * m_ptrButton02;
	GtButton * m_ptrButton03;
	GtButton * m_ptrButton04;
	GtButton * m_ptrButton05;
	GtButton * m_ptrButton06;
	GtButton * m_ptrButton07;
	GtButton * m_ptrButton08;

	//MEMBER FUNCTIONS////////////////////////
public:

	//!Custom Event Processing
	virtual int HandleEvent(GtEvent * ptrEvent);
	//!Custom Widget Painting
	virtual int OnPaint(GtPainter * painter = NULL);		

};//end GtButton class definition

#endif //GT_BUTTON_GRID_H