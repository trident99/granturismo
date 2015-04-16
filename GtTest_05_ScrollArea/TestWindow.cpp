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

#include ".\TestWindow.h"

#include <GtBasicControls\GtButton.h>
#include <GtBasicControls\GtScrollArea.h>
#include <GtBasicControls\GtVertScrollBar.h>
#include <GtBasicControls\GtHorizScrollBar.h>

#include ".\ButtonGrid.h"


//default constructor
TestWindow::TestWindow(GtObject* ptrParent)
: GtMainWindow(ptrParent)
{
	m_strType = "TestWindow";
	GtRectI rectButton, rectNew;
	rectNew.xMin = 0;
	rectNew.xMax = 1000;
	rectNew.yMin = 0;
	rectNew.yMax = 600;
	this->Set_objFrame(rectNew);
	this->Set_objBackBrush(GtBrush(GtColor(140, 140, 180)));

	this->InitializeDialog();

	this->PostPaint();
	//SetAllWinIDs(m_winID);
};
//virtual destructor
TestWindow::~TestWindow(void)
{
	//this->DeleteAllSubWidgets();
};

void TestWindow::InitializeModels(void)
{



};

void TestWindow::InitializeControls(void)
{
	//set up the main window
	GtMainWindow objMain;
	GtRectI mainRect;

	//add the button
	GtRectI scrollRect;
	GtScrollArea * ptrViewport = new GtScrollArea(this);
	scrollRect.xMin = 50;
	scrollRect.xMax = 500;
	scrollRect.yMin = 50;
	scrollRect.yMax = 500;
	ptrViewport->Set_objFrame(scrollRect);
	ptrViewport->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
	std::string strText = "MyScrollArea";
	ptrViewport->Set_strText(strText);
	ptrViewport->SetVisible(true);
	this->AddSubWidget(ptrViewport);

	ButtonGrid * ptrGrid = new ButtonGrid(ptrViewport);
	ptrViewport->SetTarget(ptrGrid);
	
};

void TestWindow::InitializeActions(void)
{

	//LIST MODEL CONTROLS////
	//if(m_cmdLoadList01)
	//{
	//	m_cmdLoadList01->Clicked.SlotConnect(this,&TestWindow::OnList01_Clicked);
	//};

};

