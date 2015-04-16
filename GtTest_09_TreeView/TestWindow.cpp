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
#include <modGtMath.h>

//default constructor
TestWindow::TestWindow(GtObject* ptrParent)
: GtMainWindow(ptrParent)
{
	m_strType = "TestWindow";
	//SPROCKET CONTROLS////
	m_lblSprocInfo = NULL;
	m_lblSprocName = NULL;
	m_lblSprocShrtVar01 = NULL;
	m_lblSprocIntVar03 = NULL;
	m_lblSprocSngVar07 = NULL;

	m_txtSprocName = NULL;
	m_txtSprocShrtVar01 = NULL;
	m_txtSprocIntVar03 = NULL;
	m_txtSprocSngVar07 = NULL;

	m_chkBlnTest = NULL;

	//LIST MODEL CONTROLS////
	m_cmdLoadList01 = NULL;
	m_cmdLoadList02 = NULL;
	m_cmdLoadList03 = NULL;
	m_cmdClearList = NULL;
	m_cmdChangeColor = NULL;

	m_tvwSprockets = NULL;
	m_cmdChangeColor = NULL;

	m_ptrSprocketModel = new SprocketTreeModel(this);

	GtRectI rectNew;
	rectNew.xMin = 0;
	rectNew.xMax = 1000;
	rectNew.yMin = 0;
	rectNew.yMax = 600;
	this->Set_objFrame(rectNew);
	this->Set_objBackBrush(GtBrush(GtColor(140, 140, 180)));

	this->InitializeDialog();
	this->PopulateSprockets();

	this->PostPaint();

};
//virtual destructor
TestWindow::~TestWindow(void)
{
	//this->DeleteAllSubWidgets();
};

void TestWindow::InitializeControls(void)
{
	GtRectI rect;
	std::string strCmd;




	//LIST MODEL CONTROLS////
	if(!m_cmdLoadList01)
	{
		m_cmdLoadList01 = new GtButton(this);
		rect.xMin = 50;
		rect.xMax = 150;
		rect.yMin = 25;
		rect.yMax = 100;
		if(m_cmdLoadList01)
		{
			m_cmdLoadList01->Set_objFrame(rect);
			m_cmdLoadList01->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Load List\r\nNo. 01";
			m_cmdLoadList01->Set_strText(strCmd);
			this->AddSubWidget(m_cmdLoadList01);			
		}	
	};
	if(!m_cmdLoadList02)
	{
		m_cmdLoadList02 = new GtButton(this);
		rect.xMin = 50;
		rect.xMax = 150;
		rect.yMin = 125;
		rect.yMax = 200;
		if(m_cmdLoadList02)
		{
			m_cmdLoadList02->Set_objFrame(rect);
			m_cmdLoadList02->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Load List\r\nNo. 02";
			m_cmdLoadList02->Set_strText(strCmd);
			this->AddSubWidget(m_cmdLoadList02);			
		}	
	};

	if(!m_cmdLoadList03)
	{
		m_cmdLoadList03 = new GtButton(this);
		rect.xMin = 50;
		rect.xMax = 150;
		rect.yMin = 225;
		rect.yMax = 300;
		if(m_cmdLoadList03)
		{
			m_cmdLoadList03->Set_objFrame(rect);
			m_cmdLoadList03->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Load List\r\nNo. 03";
			m_cmdLoadList03->Set_strText(strCmd);
			this->AddSubWidget(m_cmdLoadList03);			
		}	
	};

	if(!m_cmdClearList)
	{
		m_cmdClearList = new GtButton(this);
		rect.xMin = 50;
		rect.xMax = 150;
		rect.yMin = 325;
		rect.yMax = 400;
		if(m_cmdClearList)
		{
			m_cmdClearList->Set_objFrame(rect);
			m_cmdClearList->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Clear List\r\nView";
			m_cmdClearList->Set_strText(strCmd);
			this->AddSubWidget(m_cmdClearList);			
		}	
	};
	if(!m_cmdChangeColor)
	{
		m_cmdChangeColor = new GtButton(this);
		rect.xMin = 50;
		rect.xMax = 150;
		rect.yMin = 425;
		rect.yMax = 500;
		if(m_cmdChangeColor)
		{
			m_cmdChangeColor->Set_objFrame(rect);
			m_cmdChangeColor->Set_objBackBrush(GtBrush(GtColor(150,150,150)));
			strCmd = "Change\r\nColor";
			m_cmdChangeColor->Set_strText(strCmd);
			this->AddSubWidget(m_cmdChangeColor);
			
		}
	}

	if(!m_tvwSprockets)
	{
		m_tvwSprockets = new GtTreeView(this);
		rect.xMin = 200;
		rect.xMax = 600;
		rect.yMin = 50;
		rect.yMax = 500;
		if(m_tvwSprockets)
		{
			m_tvwSprockets->Set_objFrame(rect);
			m_tvwSprockets->Set_objBackBrush(GtBrush(GtColor(190,90,160)));
			m_tvwSprockets->SetColumnWidth(0,400);
			strCmd = "ListView";
			m_tvwSprockets->Set_strText(strCmd);
			
			m_tvwSprockets->SetTreeModel(m_ptrSprocketModel);
			this->AddSubWidget(m_tvwSprockets);	
		}
	}

	std::string strName;
	//SPROCKET CONTROLS////

	if(!m_lblSprocInfo)
	{
		m_lblSprocInfo = new GtLabel(this);
		rect.xMin = 650;
		rect.xMax = 850;
		rect.yMin = 50;
		rect.yMax = 75;
		if(m_lblSprocInfo)
		{
			m_lblSprocInfo->Set_objFrame(rect);
			m_lblSprocInfo->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "SPROCKET INFORMATION";
			m_lblSprocInfo->Set_strText(strName);
			this->AddSubWidget(m_lblSprocInfo);	
		}
	}
	//SPROCKET NAME////////////////////////////
	if(!m_lblSprocName)
	{
		m_lblSprocName = new GtLabel(this);
		rect.xMin = 650;
		rect.xMax = 850;
		rect.yMin = 100;
		rect.yMax = 125;
		if(m_lblSprocName)
		{
			m_lblSprocName->Set_objFrame(rect);
			m_lblSprocName->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "Sprocket Name";
			m_lblSprocName->Set_strText(strName);
			this->AddSubWidget(m_lblSprocName);	
		}
	}

	if(!m_txtSprocName)
	{
		m_txtSprocName = new GtSimpleTextEdit(this);
		rect.xMin = 650;
		rect.xMax = 850;
		rect.yMin = 150;
		rect.yMax = 175;
		if(m_txtSprocName)
		{
			m_txtSprocName->Set_objFrame(rect);
			m_txtSprocName->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "nil";
			m_txtSprocName->Set_strText(strName);
			this->AddSubWidget(m_txtSprocName);	
		}
	}
	//SPROCKET SHORT VARIANT 01/////////////////////
	if(!m_lblSprocShrtVar01)
	{
		m_lblSprocShrtVar01 = new GtLabel(this);
		rect.xMin = 650;
		rect.xMax = 850;
		rect.yMin = 200;
		rect.yMax = 225;
		if(m_lblSprocShrtVar01)
		{
			m_lblSprocShrtVar01->Set_objFrame(rect);
			m_lblSprocShrtVar01->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "Short Variant 01";
			m_lblSprocShrtVar01->Set_strText(strName);
			this->AddSubWidget(m_lblSprocShrtVar01);	
		}
	}

	if(!m_txtSprocShrtVar01)
	{
		m_txtSprocShrtVar01 = new GtSimpleTextEdit(this);
		rect.xMin = 650;
		rect.xMax = 850;
		rect.yMin = 230;
		rect.yMax = 255;
		if(m_txtSprocShrtVar01)
		{
			m_txtSprocShrtVar01->Set_objFrame(rect);
			m_txtSprocShrtVar01->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "0";
			m_txtSprocShrtVar01->Set_strText(strName);
			this->AddSubWidget(m_txtSprocShrtVar01);	
		}
	}
	//SPROCKET INT VARIANT 03//////////////////////
	if(!m_lblSprocIntVar03)
	{
		m_lblSprocIntVar03 = new GtLabel(this);
		rect.xMin = 650;
		rect.xMax = 800;
		rect.yMin = 265;
		rect.yMax = 290;
		if(m_lblSprocIntVar03)
		{
			m_lblSprocIntVar03->Set_objFrame(rect);
			m_lblSprocIntVar03->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "Integer Variant 03";
			m_lblSprocIntVar03->Set_strText(strName);
			this->AddSubWidget(m_lblSprocIntVar03);	
		}
	}

	if(!m_txtSprocIntVar03)
	{
		m_txtSprocIntVar03 = new GtSimpleTextEdit(this);
		rect.xMin = 650;
		rect.xMax = 850;
		rect.yMin = 315;
		rect.yMax = 340;
		if(m_txtSprocIntVar03)
		{
			m_txtSprocIntVar03->Set_objFrame(rect);
			m_txtSprocIntVar03->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "0";
			m_txtSprocIntVar03->Set_strText(strName);
			this->AddSubWidget(m_txtSprocIntVar03);	
		}
	}
	//FLOATING VARIANT 07//////////////////////////

	if(!m_lblSprocSngVar07)
	{
		m_lblSprocSngVar07 = new GtLabel(this);
		rect.xMin = 650;
		rect.xMax = 800;
		rect.yMin = 350;
		rect.yMax = 375;
		if(m_lblSprocSngVar07)
		{
			m_lblSprocSngVar07->Set_objFrame(rect);
			m_lblSprocSngVar07->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "Floating Variant 07";
			m_lblSprocSngVar07->Set_strText(strName);
			this->AddSubWidget(m_lblSprocSngVar07);	
		}
	}

	if(!m_txtSprocSngVar07)
	{
		m_txtSprocSngVar07 = new GtSimpleTextEdit(this);
		rect.xMin = 650;
		rect.xMax = 850;
		rect.yMin = 385;
		rect.yMax = 410;
		if(m_txtSprocSngVar07)
		{
			m_txtSprocSngVar07->Set_objFrame(rect);
			m_txtSprocSngVar07->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
			strName = "0.0";
			m_txtSprocSngVar07->Set_strText(strName);
			this->AddSubWidget(m_txtSprocSngVar07);	
		}
	}
//CHECK BOX TEST/////////////

		if(!m_chkBlnTest)
	{
		m_chkBlnTest = new GtCheckBox(this);
		rect.xMin = 650;
		rect.xMax = 800;
		rect.yMin = 425;
		rect.yMax = 450;
		if(m_chkBlnTest)
		{
			m_chkBlnTest->Set_objFrame(rect);
			m_chkBlnTest->Set_objBackBrush(GtBrush(GtColor(130,130,255)));
			strName = "Boolean Test";
			m_chkBlnTest->Set_strText(strName);
			this->AddSubWidget(m_chkBlnTest);	
		}
	}
		//update the gui
		this->PostPaint();
};

void TestWindow::InitializeActions(void)
{

	//LIST MODEL CONTROLS////
	if(m_cmdLoadList01)
	{
		m_cmdLoadList01->Clicked.SlotConnect(this,&TestWindow::OnList01_Clicked);
	};
	if(m_cmdLoadList02)
	{
		m_cmdLoadList02->Clicked.SlotConnect(this,&TestWindow::OnList02_Clicked);
	};

	if(m_cmdLoadList03)
	{
		m_cmdLoadList03->Clicked.SlotConnect(this,&TestWindow::OnList03_Clicked);
	};

	if(m_cmdClearList)
	{
		m_cmdClearList->Clicked.SlotConnect(this,&TestWindow::OnClearList_Clicked);
	};

	if(m_cmdChangeColor)
	{
		m_cmdChangeColor->Clicked.SlotConnect(this,&TestWindow::OnChangeColor_Clicked);
	}

	if(m_tvwSprockets)
	{
		m_tvwSprockets->SelectionChanged.SlotConnect(this,&TestWindow::OnLoadSprocket);
	}
};

//Populate the sprocket collections
void TestWindow::PopulateSprockets(void)
{
	char buf[64];
	std::string strName;
	size_t i, numSproc;

	//BUILD LIST 01////
	numSproc = 2;
	for(i = 0; i < numSproc; i++)
	{	
		sprintf(buf,"SPKT R%03dC%03d",i,0);
		strName = buf;
		Sprocket* ptrNew = new Sprocket();
		ptrNew->Set_strName(strName);
		ptrNew->Set_shrtVar01(m_objRNG.intNextAB(0,255));
		ptrNew->Set_intVar03(m_objRNG.intNextAB(0,32000));
		ptrNew->Set_sngVar07(m_objRNG.dblNextAB(0.0f,10.0f));
		ptrNew->Set_blnTest(gRound(m_objRNG.intNextAB(0,1)));
		ptrNew->GenerateSprockets(0,3);
		m_arrList01.push_back(ptrNew);
	}

	//BUILD LIST 02////
	numSproc = 5;
	for(i = 0; i < numSproc; i++)
	{
		sprintf(buf,"SPKT R%03dC%03d",i,0);
		strName = buf;
		Sprocket* ptrNew = new Sprocket();
		ptrNew->Set_strName(strName);
		ptrNew->Set_shrtVar01(m_objRNG.intNextAB(0,255));
		ptrNew->Set_intVar03(m_objRNG.intNextAB(0,32000));
		ptrNew->Set_sngVar07(m_objRNG.dblNextAB(0.0f,10.0f));
		ptrNew->Set_blnTest(gRound(m_objRNG.intNextAB(0,1)));
		ptrNew->GenerateSprockets(0,5);
		m_arrList02.push_back(ptrNew);
	}

	//BUILD LIST 03////
	numSproc = 10;
	for(i = 0; i < numSproc; i++)
	{
		sprintf(buf,"SPKT R%03dC%03d",i,0);
		strName = buf;
		Sprocket* ptrNew = new Sprocket();
		ptrNew->Set_strName(strName);
		ptrNew->Set_shrtVar01(m_objRNG.intNextAB(0,255));
		ptrNew->Set_intVar03(m_objRNG.intNextAB(0,32000));
		ptrNew->Set_sngVar07(m_objRNG.dblNextAB(0.0f,10.0f));
		ptrNew->Set_blnTest(gRound(m_objRNG.intNextAB(0,1)));
		ptrNew->GenerateSprockets(0,2);
		m_arrList03.push_back(ptrNew);
	}


};

//Load Sprocket List 01
void TestWindow::OnList01_Clicked(void)
{
	m_ptrSprocketModel->SetCollectionPtr(&m_arrList01);
	if(m_tvwSprockets)
	{
		m_tvwSprockets->Reset();
	}
};

//Load Sprocket List 02;
void TestWindow::OnList02_Clicked(void)
{
m_ptrSprocketModel->SetCollectionPtr(&m_arrList02);
	if(m_tvwSprockets)
	{
		m_tvwSprockets->Reset();
	}
};

//Load Sprocket List 03;
void TestWindow::OnList03_Clicked(void)
{
m_ptrSprocketModel->SetCollectionPtr(&m_arrList03);
	if(m_tvwSprockets)
	{
		m_tvwSprockets->Reset();
	}
};

//Load Sprocket List 03;
void TestWindow::OnClearList_Clicked(void)
{
	m_ptrSprocketModel->ClearCollectionPtr();
	if(m_tvwSprockets)
	{
		m_tvwSprockets->Reset();
	}
};

//change the viewed sprocket
void TestWindow::OnLoadSprocket(void)
{
	std::string strTemp;
	char buf[64];
	//get the first in the selection
	GtTreeModelIndex* ptrSel = m_tvwSprockets->GetSelection()->Get_ptrTopLeft();
	if(!ptrSel){return;};
	Sprocket* ptrSproc = (Sprocket*)(ptrSel->m_ptrData);
	if(!ptrSproc){return;};

	if(m_txtSprocName)
	{
		m_txtSprocName->Set_strText(ptrSel->m_strText);
	};

	if(m_txtSprocShrtVar01)
	{
		sprintf(buf,"%d",ptrSproc->Get_shrtVar01());
		strTemp = buf;
		m_txtSprocShrtVar01->Set_strText(strTemp);
	};
	if(m_txtSprocIntVar03)
	{
		sprintf(buf,"%d",ptrSproc->Get_intVar03());
		strTemp = buf;
		m_txtSprocIntVar03->Set_strText(strTemp);
	};

	if(m_txtSprocSngVar07)
	{
		sprintf(buf,"%6.6f",ptrSproc->Get_sngVar07());
		strTemp = buf;
		m_txtSprocSngVar07->Set_strText(strTemp);
	};

	if(m_chkBlnTest)
	{
		m_chkBlnTest->Set_blnChecked(ptrSproc->Get_blnTest());
	};
	return;
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
