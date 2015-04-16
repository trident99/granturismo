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

#ifndef GT_TEST_WINDOW_H
#define GT_TEST_WINDOW_H

#include <modHtlRandNumGen.h>
#include <GtWinforms\GtMainWindow.h>
#include <GtBasicControls\GtLabel.h>
#include <GtBasicControls\GtCheckBox.h>
#include <GtBasicControls\GtButton.h>
#include <GtTextView\GtSimpleTextEdit.h>

#include <GtModelView\GtTreeView.h>
#include <GtModelView\GtTableRow.h>
#include <GtModelView\GtTableColumn.h>

#include ".\SprocketTreeModel.h"

using namespace HTL;
using namespace GT::GtCore;
using namespace GT::GtGui;

class TestWindow : public GtMainWindow
{
public:
	//!Parent set constructor
	TestWindow(GtObject* ptrParent = NULL);
	//!Virtual destructor
	virtual ~TestWindow(void);

	//MEMBER VARIABLES////////////////////////

	//SIGNALS/////////////////////////////////
public:

	//MEMBER FUNCTIONS////////////////////////
public:
	//!Initialize the Controls
	virtual void InitializeControls(void);
	//!Initialize the Actions
	virtual void InitializeActions(void);

	//Populate the sprocket collections
	void PopulateSprockets(void);
	//Load Sprocket List 01
	void OnList01_Clicked(void);
	//Load Sprocket List 02;
	void OnList02_Clicked(void);
	//Load Sprocket List 03;
	void OnList03_Clicked(void);
	//Clear the list view
	void OnClearList_Clicked(void);
	//change the color of the background
	void OnChangeColor_Clicked(void);
	//change the viewed sprocket
	void OnLoadSprocket(void);

protected:

	//SPROCKET CONTROLS////
	GtLabel * m_lblSprocInfo;
	GtLabel * m_lblSprocName;
	GtLabel * m_lblSprocShrtVar01;
	GtLabel * m_lblSprocIntVar03;
	GtLabel * m_lblSprocSngVar07;

	GtSimpleTextEdit * m_txtSprocName;
	GtSimpleTextEdit * m_txtSprocShrtVar01;
	GtSimpleTextEdit * m_txtSprocIntVar03;
	GtSimpleTextEdit * m_txtSprocSngVar07;

	GtCheckBox * m_chkBlnTest;

	//LIST MODEL CONTROLS////
	GtButton * m_cmdLoadList01;
	GtButton * m_cmdLoadList02;
	GtButton * m_cmdLoadList03;
	GtButton * m_cmdClearList;
	GtButton * m_cmdChangeColor;

	GtTreeView * m_tvwSprockets;

	HtlUniform m_objRNG;

protected:
	SprocketTreeModel* m_ptrSprocketModel;

	Htl1DList<Sprocket*,HTL_BASE_PTR> m_arrList01;
	Htl1DList<Sprocket*,HTL_BASE_PTR> m_arrList02;
	Htl1DList<Sprocket*,HTL_BASE_PTR> m_arrList03;

};//end HtlBase class definition

#endif //GT_MAIN_WINDOW_H