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


//default constructor
TestWindow::TestWindow(GtObject* ptrParent)
: GtMainWindow(ptrParent)
{
	m_strType = "TestWindow";
	m_cmdModal = NULL;
	m_cmdModeless = NULL;
	m_cmdChangeColor = NULL;

	m_objModeless.Set_ptrParent(this);
	m_objModeless.Set_blnModal(false);
	m_objModeless.Hide();

	this->InitializeDialog();
	//SetAllWinIDs(m_winID);
};
//virtual destructor
TestWindow::~TestWindow(void)
{
	//this->DeleteAllSubWidgets();
};

void TestWindow::InitializeDialog(void)
{
	std::string strCmd;
	GtRectI rectButton, rectNew;
	rectNew.xMin = 0;
	rectNew.xMax = 500;
	rectNew.yMin = 0;
	rectNew.yMax = 200;
	this->Set_objFrame(rectNew);
	this->Set_objBackBrush(GtBrush(GtColor(140,140,180)));

	if(!m_cmdModal)
	{
		m_cmdModal = new GtButton(this);
		rectButton.xMin = 50;
		rectButton.xMax = 150;
		rectButton.yMin = 50;
		rectButton.yMax = 100;
		if(m_cmdModal)
		{
			m_cmdModal->Set_objFrame(rectButton);
			m_cmdModal->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Modal";
			m_cmdModal->Set_strText(strCmd);
			this->AddSubWidget(m_cmdModal);

			m_cmdModal->Clicked.SlotConnect(this,&TestWindow::OnModal_Clicked);
		}
	}

	if(!m_cmdModeless)
	{
		m_cmdModeless = new GtButton(this);
		rectButton.xMin = 200;
		rectButton.xMax = 300;
		rectButton.yMin = 50;
		rectButton.yMax = 100;
		if(m_cmdModeless)
		{
			m_cmdModeless->Set_objFrame(rectButton);
			m_cmdModeless->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Modeless";
			m_cmdModeless->Set_strText(strCmd);
			this->AddSubWidget(m_cmdModeless);
			m_cmdModeless->Clicked.SlotConnect(this,&TestWindow::OnModeless_Clicked);
		}
	}


	if(!m_cmdChangeColor)
	{
		m_cmdChangeColor = new GtButton(this);
		rectButton.xMin = 350;
		rectButton.xMax = 450;
		rectButton.yMin = 50;
		rectButton.yMax = 100;
		if(m_cmdChangeColor)
		{
			m_cmdChangeColor->Set_objFrame(rectButton);
			m_cmdChangeColor->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Change";
			m_cmdChangeColor->Set_strText(strCmd);
			this->AddSubWidget(m_cmdChangeColor);
			m_cmdChangeColor->Clicked.SlotConnect(this,&TestWindow::OnChangeColor_Clicked);
		}
	}
	this->PostPaint();
	return;

};

//launch the modal dialog
void TestWindow::OnModal_Clicked(void)
{
	TestDialog objModal(this);
	objModal.Set_blnModal(true);
	objModal.Exec();
	this->PostPaint();
	int z = 10;
	return;
};

//show the modeless dialog;
void TestWindow::OnModeless_Clicked(void)
{
	m_objModeless.Show();
};

//change the color of the background
void TestWindow::OnChangeColor_Clicked(void)
{
	//change the color of the background
	int iRed,iGreen,iBlue;

	iRed = m_objRNG.intNextAB(0,255);
	iGreen = m_objRNG.intNextAB(0,255);	
	iBlue = m_objRNG.intNextAB(0,255);
	this->Set_objBackBrush(GtBrush(GtColor(iRed,iGreen,iBlue)));
	this->PostPaint();
};
