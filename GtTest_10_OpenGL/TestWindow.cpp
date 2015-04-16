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
#include <GtOpenGLModel\GtModelObjects\GM_AABox.h>
//#include <GtOpenGLModel\GtCadObject.h>
//#include <GtOpenGLModel\GtCadObject.h>

//default constructor
TestWindow::TestWindow(GtObject* ptrParent)
: GtMainWindow(ptrParent)
{
	m_strType = "TestWindow";

	m_txtItemName = NULL;
	m_ptrModel = NULL;
	m_ptrViewport = NULL;

	GtRectI rectNew;
	rectNew.xMin = 0;
	rectNew.xMax = 1000;
	rectNew.yMin = 0;
	rectNew.yMax = 600;
	this->Set_objFrame(rectNew);
	this->Set_objBackBrush(GtBrush(GtColor(140, 140, 180)));

	this->InitializeDialog();

	//SetAllWinIDs(m_winID);
};
//virtual destructor
TestWindow::~TestWindow(void)
{
	//this->DeleteAllSubWidgets();
};


void TestWindow::InitializeModels(void)
{
	m_ptrModel = new GtPartModel();
	GtMaterial mat;
	std::string strName;

	if (!m_ptrModel){ return; };
	//add a couple of boxes
	GM_AABox* ptrNewBox = new GM_AABox();

	ptrNewBox->m_dblXMin = 5; ptrNewBox->m_dblXMax = 10;
	ptrNewBox->m_dblYMin = 5; ptrNewBox->m_dblYMax = 10;
	ptrNewBox->m_dblZMin = 2; ptrNewBox->m_dblZMax = 4;
	mat.m_objDiffuseColor.SetRGB(255,0,0);
	ptrNewBox->Set_objSurfMaterial(mat);
	strName = "Box 001";
	ptrNewBox->Set_strName(strName);
	m_ptrModel->AddModelItem(ptrNewBox);

//add a couple of boxes
	ptrNewBox = new GM_AABox();

	ptrNewBox->m_dblXMin = -5; ptrNewBox->m_dblXMax = -2;
	ptrNewBox->m_dblYMin = -2; ptrNewBox->m_dblYMax = 2;
	ptrNewBox->m_dblZMin = 0; ptrNewBox->m_dblZMax = 4;
	mat.m_objDiffuseColor.SetRGB(30,170,100);
	ptrNewBox->Set_objSurfMaterial(mat);
	strName = "Box 002";
	ptrNewBox->Set_strName(strName);
	m_ptrModel->AddModelItem(ptrNewBox);


	//add a couple of boxes
	ptrNewBox = new GM_AABox();

	ptrNewBox->m_dblXMin = 2; ptrNewBox->m_dblXMax = 4;
	ptrNewBox->m_dblYMin = -5; ptrNewBox->m_dblYMax = -2;
	ptrNewBox->m_dblZMin = -5; ptrNewBox->m_dblZMax = -2;
	mat.m_objDiffuseColor.SetRGB(170,0,170);
	ptrNewBox->Set_objSurfMaterial(mat);
	strName = "Box 003";
	ptrNewBox->Set_strName(strName);
	m_ptrModel->AddModelItem(ptrNewBox);

	if( (m_ptrViewport) && (m_ptrModel))
	{
		m_ptrViewport->Set_ptrPartModel(m_ptrModel);
	}

};

void TestWindow::InitializeControls(void)
{
	GtRectI rect;
	std::string strCmd,strName;

	//LIST MODEL CONTROLS////
	if(!m_ptrViewport)
	{
		m_ptrViewport = new GtViewport(this,this->m_winID);
		rect.xMin = 50;
		rect.xMax = 500;
		rect.yMin = 50;
		rect.yMax = 500;
		if(m_ptrViewport)
		{

			m_ptrViewport->Set_objFrame(rect);
			strCmd = "My Viewport";

			m_ptrViewport->Set_ptrPartModel(m_ptrModel);
			m_ptrViewport->Set_strText(strCmd);
			m_ptrViewport->SetVisible(true);
			m_ptrViewport->Set_blnSingleSelect(true);
			this->AddSubWidget(m_ptrViewport);			
		}	
	};

	if(!m_txtItemName)
	{
		m_txtItemName = new GtSimpleTextEdit(this);
		rect.xMin = 50;
		rect.xMax = 400;
		rect.yMin = 525;
		rect.yMax = 550;
		if(m_txtItemName)
		{
			m_txtItemName->Set_objFrame(rect);
			m_txtItemName->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "nil";
			m_txtItemName->Set_strText(strName);
			this->AddSubWidget(m_txtItemName);	
		}
	}

};

void TestWindow::InitializeActions(void)
{

	//LIST MODEL CONTROLS////
	//if(m_cmdLoadList01)
	//{
	//	m_cmdLoadList01->Clicked.SlotConnect(this,&TestWindow::OnList01_Clicked);
	//};

};

