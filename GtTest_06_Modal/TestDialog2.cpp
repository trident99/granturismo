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

#include ".\TestDialog2.h"

//default constructor
TestDialog2::TestDialog2(GtObject* ptrParent)
: GtDialog(ptrParent)
{
	m_strType = "TestDialog2";

	m_cmdHIDE = NULL;
	m_cmdChangeColor = NULL;

	this->InitializeDialog();
	//SetAllWinIDs(m_winID);
};
//virtual destructor
TestDialog2::~TestDialog2(void)
{
	this->DeleteAllSubWidgets();
};

void TestDialog2::InitializeDialog(void)
{
	std::string strCmd;
	GtRectI rectButton, rectNew;
	rectNew.xMin = 0;
	rectNew.xMax = 500;
	rectNew.yMin = 0;
	rectNew.yMax = 200;
	this->Set_objFrame(rectNew);
	this->Set_objBackBrush(GtBrush(GtColor(140,140,180)));

	if(!m_cmdHIDE)
	{
		m_cmdHIDE = new GtButton(this);
		rectButton.xMin = 50;
		rectButton.xMax = 150;
		rectButton.yMin = 50;
		rectButton.yMax = 100;
		if(m_cmdHIDE)
		{
			m_cmdHIDE->Set_objFrame(rectButton);
			m_cmdHIDE->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "HIDE";
			m_cmdHIDE->Set_strText(strCmd);
			this->AddSubWidget(m_cmdHIDE);

			m_cmdHIDE->Clicked.SlotConnect<GtDialog>((GtDialog*)this,&GtDialog::Hide);
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
			strCmd = "Color";
			m_cmdChangeColor->Set_strText(strCmd);
			this->AddSubWidget(m_cmdChangeColor);
			m_cmdChangeColor->Clicked.SlotConnect<TestDialog2>(this,&TestDialog2::OnChangeColor_Clicked);
		}
	}
	m_objEventManager.PostPaint();
	return;

};
//change the color of the background
void TestDialog2::OnChangeColor_Clicked(void)
{
	//change the color of the background
	int iRed,iGreen,iBlue;

	iRed = m_objRNG.intNextAB(0,255);
	iGreen = m_objRNG.intNextAB(0,255);	
	iBlue = m_objRNG.intNextAB(0,255);
	this->Set_objBackBrush(GtBrush(GtColor(iRed,iGreen,iBlue)));
	this->PostPaint();
};
