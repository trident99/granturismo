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

#ifndef GT_TEST_DIALOG_H
#define GT_TEST_DIALOG_H

#include <modHtlRandNumGen.h>
#include <GtWinforms\GtDialog.h>
#include <GtBasicControls\GtButton.h>

using namespace HTL;
using namespace GT::GtCore;


class TestDialog : public GtDialog
{
public:
	//!Parent set constructor
	TestDialog(GtObject* ptrParent = NULL);
	//!Virtual destructor
	virtual ~TestDialog(void);

	//MEMBER VARIABLES////////////////////////

	//SIGNALS/////////////////////////////////
public:

	//MEMBER FUNCTIONS////////////////////////
public:
	void InitializeDialog(void);
	//change the color of the background
	void OnChangeColor_Clicked(void);

protected:

	GtButton * m_cmdOK;
	GtButton * m_cmdCANCEL;
	GtButton * m_cmdChangeColor;
	HtlUniform m_objRNG;
};//end HtlBase class definition

#endif //GT_MAIN_WINDOW_H