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
#include <GtBasicControls\GtCheckBox.h>
#include <GtBasicControls\GtVertScrollBar.h>
#include <GtBasicControls\GtHorizScrollBar.h>
#include <GtBasicControls\GtSlider.h>
#include <GtBasicControls\GtProgressBar.h>
#include <GtBasicControls\GtComboBox.h>
#include <GtBasicControls\GtDateEdit.h>
#include <GtBasicControls\GtTimeEdit.h>
#include <GtBasicControls\GtLabel.h>
#include <GtBasicControls\GtRadioButton.h>
#include <GtBasicControls\GtSpinBox.h>
#include <GtBasicControls\GtAction.h>
#include <GtBasicControls\GtMenu.h>
#include <GtBasicControls\GtTabBar.h>
#include <GtBasicControls\GtTabPage.h>
#include <GtBasicControls\GtToolBar.h>

#include <GtTextView\GtSimpleTextEdit.h>
#include <GtTextView\GtMultiTextEdit.h>

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

	GtTabBar* ptrTabBar = new GtTabBar(this);
	if (ptrTabBar)
	{
		GtRectI rectTabBar;
		rectTabBar.xMin = 50;
		rectTabBar.xMax = 600;
		rectTabBar.yMin = 50;
		rectTabBar.yMax = 300;
		ptrTabBar->Set_objFrame(rectTabBar);
		ptrTabBar->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "MyTabBar";
		ptrTabBar->Set_strText(strText);
		ptrTabBar->Set_intTabWidth(150);
		ptrTabBar->SetVisible(true);
		this->AddSubWidget(ptrTabBar);
	}


	GtMultiTextEdit * ptrTextEdit = new GtMultiTextEdit(this);
	if (ptrTextEdit)
	{
		GtRectI rectText;
		rectText.xMin = 650;
		rectText.xMax = 900;
		rectText.yMin = 50;
		rectText.yMax = 300;
		ptrTextEdit->Set_objFrame(rectText);
		ptrTextEdit->Set_objBackBrush(GtBrush(GtColor(255, 255, 255)));
		ptrTextEdit->Set_blnAutoExpand(false);
		ptrTextEdit->SetVisible(true);
		this->AddSubWidget(ptrTextEdit);

	}


	GtTabPage* ptrPage1 = new GtTabPage(ptrTabBar);
	if (ptrPage1)
	{
		ptrPage1->Set_objBackBrush(GtBrush(GtColor(120, 120, 200)));
		std::string strText = "PageOne";
		ptrPage1->Set_strText(strText);
		ptrPage1->SetVisible(true);
		ptrTabBar->AddTabPage(ptrPage1);
	}

	//add the button
	GtRectI buttonRect;
	GtButton *  ptrButton = new GtButton(ptrPage1);
	if (ptrButton)
	{
		buttonRect.xMin = 100;
		buttonRect.xMax = 200;
		buttonRect.yMin = 50;
		buttonRect.yMax = 100;
		ptrButton->Set_objFrame(buttonRect);
		ptrButton->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "MyButton";
		ptrButton->Set_strText(strText);
		ptrButton->SetVisible(true);
		ptrPage1->AddSubWidget(ptrButton);
	};

	GtTabPage* ptrPage2 = new GtTabPage(ptrTabBar);
	if (ptrPage2)
	{
		ptrPage2->Set_objBackBrush(GtBrush(GtColor(120, 255, 255)));
		std::string strText = "PageTwo";
		ptrPage2->Set_strText(strText);
		ptrPage2->SetVisible(true);
		ptrTabBar->AddTabPage(ptrPage2);
	}


	GtCheckBox* ptrCheck = new GtCheckBox(ptrPage2);
	if (ptrCheck)
	{
		GtRectI checkRect;
		checkRect.xMin = 100;
		checkRect.xMax = 200;
		checkRect.yMin = 50;
		checkRect.yMax = 100;
		ptrCheck->Set_objFrame(checkRect);
		std::string strText;
		strText = "MyCheckBox";
		ptrCheck->Set_strText(strText);
		ptrCheck->Set_blnChecked(true);
		ptrCheck->SetVisible(true);
		ptrCheck->Set_objBackBrush(GtBrush(GtColor(255, 255, 0)));
		ptrPage2->AddSubWidget(ptrCheck);
	}


	GtComboBox* ptrCombo = new GtComboBox(ptrPage2);
	if (ptrCombo)
	{
		GtRectI comboRect;
		comboRect.xMin = 100;
		comboRect.xMax = 300;
		comboRect.yMin = 150;
		comboRect.yMax = 175;
		ptrCombo->Set_objFrame(comboRect);
		//set color BEFORE adding items
		ptrCombo->Set_objBackBrush(GtBrush(GtColor(255, 255, 255)));

		std::string strText;
		strText = "MyComboBox";
		ptrCombo->Set_strText(strText);

		GtComboBoxItem item;
		item.m_strText = "OptionOne";
		ptrCombo->AddItem(item);
		item.m_strText = "OptionTwo";
		ptrCombo->AddItem(item);
		item.m_strText = "OptionThree";
		ptrCombo->AddItem(item);
		ptrCombo->Set_intWidth(200);
		ptrCombo->SetVisible(true);
		ptrPage2->AddSubWidget(ptrCombo);
	}

	GtTabPage* ptrPage3 = new GtTabPage(ptrTabBar);
	if (ptrPage3)
	{
		ptrPage3->Set_objBackBrush(GtBrush(GtColor(255, 120, 120)));
		std::string strText = "PageThree";
		ptrPage3->Set_strText(strText);
		ptrPage3->SetVisible(true);
		ptrTabBar->AddTabPage(ptrPage3);
	}


	GtRadioButton* ptrRadio = new GtRadioButton(ptrPage3);
	if (ptrRadio)
	{
		GtRectI radioRect;
		radioRect.xMin = 100;
		radioRect.xMax = 200;
		radioRect.yMin = 50;
		radioRect.yMax = 100;
		std::string strText;
		ptrRadio->Set_objFrame(radioRect);
		strText = "MyRadioButton";
		ptrRadio->Set_strText(strText);
		strText = "Option One";
		ptrRadio->AddOption(strText);
		strText = "Option Two";
		ptrRadio->AddOption(strText);
		strText = "Option Three";
		ptrRadio->AddOption(strText);
		ptrRadio->SetIndex(1);
		ptrRadio->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		ptrPage3->AddSubWidget(ptrRadio);
	}


	GtMenu * ptrMenu = new GtMenu(ptrPage3);
	if (ptrMenu)
	{
		GtRectI menuRect;
		menuRect.xMin = 250;
		menuRect.xMax = 400;
		menuRect.yMin = 50;
		menuRect.yMax = 75;
		ptrMenu->Set_objFrame(menuRect);
		ptrMenu->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "MyMenu";
		ptrMenu->Set_strText(strText);
		ptrMenu->SetVisible(true);
		ptrMenu->Set_intWidth(150);
		ptrPage3->AddSubWidget(ptrMenu);
	}

	GtAction * ptrAct1 = new GtAction(ptrMenu);
	if (ptrMenu)
	{
		ptrAct1->Set_blnCheckable(true);
		ptrAct1->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "ActionOne";
		ptrAct1->Set_strText(strText);
		ptrMenu->AddAction(ptrAct1);
	}
	GtAction * ptrAct2 = new GtAction(ptrMenu);
	if (ptrMenu)
	{
		ptrAct2->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "ActionTwo";
		ptrAct2->Set_strText(strText);
		ptrMenu->AddAction(ptrAct2);
	}

	GtMenu * ptrSubMenu = new GtMenu(ptrMenu);
	if (ptrSubMenu)
	{
		ptrSubMenu->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "MySubMenu";
		ptrSubMenu->Set_strText(strText);
		ptrSubMenu->Set_intWidth(150);
		ptrMenu->AddMenu(ptrSubMenu);
	}

	GtAction * ptrAct3 = new GtAction(ptrSubMenu);
	if (ptrAct3)
	{
		ptrAct3->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "ActionThree";
		ptrAct3->Set_strText(strText);
		ptrSubMenu->AddAction(ptrAct3);
	}
	GtAction * ptrAct4 = new GtAction(ptrMenu);
	if (ptrAct4)
	{
		ptrAct4->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "ActionFour";
		ptrAct4->Set_strText(strText);
		ptrSubMenu->AddAction(ptrAct4);
	}


	GtTabPage* ptrPage4 = new GtTabPage(ptrTabBar);
	if (ptrPage4)
	{
		ptrPage4->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "PageFour";
		ptrPage4->Set_strText(strText);
		ptrPage4->SetVisible(true);
		ptrTabBar->AddTabPage(ptrPage4);
	}


	GtSlider *  ptrSlider = new GtSlider(ptrPage4);
	if (ptrSlider)
	{
		GtRectI sliderRect;
		sliderRect.xMin = 100;
		sliderRect.xMax = 300;
		sliderRect.yMin = 50;
		sliderRect.yMax = 75;
		ptrSlider->Set_objFrame(sliderRect);
		std::string strText;
		strText = "MySlider";
		ptrSlider->Set_strText(strText);
		ptrSlider->Set_intMin(0);
		ptrSlider->Set_intMax(100);
		ptrSlider->Set_intValue(75);
		ptrSlider->Set_objBackBrush(GtBrush(GtColor(200, 200, 200)));
		ptrPage4->AddSubWidget(ptrSlider);
	}


	GtToolBar* ptrToolBar = new GtToolBar(ptrPage4);
	if (ptrToolBar)
	{
		GtRectI rectBar;
		rectBar.xMin = 100;
		rectBar.xMax = 350;
		rectBar.yMin = 100;
		rectBar.yMax = 150;
		ptrToolBar->Set_objFrame(rectBar);
		std::string strText;
		strText = "MyToolBar";
		ptrToolBar->Set_strText(strText);
		ptrToolBar->Set_objBackBrush(GtBrush(GtColor(130, 130, 200)));
		ptrPage4->AddSubWidget(ptrToolBar);
	}

	//add the button

	GtButton *  ptrAdd = new GtButton(ptrToolBar);
	if (ptrAdd)
	{
		GtRectI rectAdd;
		rectAdd.xMin = 10;
		rectAdd.xMax = 60;
		rectAdd.yMin = 0;
		rectAdd.yMax = 50;
		ptrAdd->Set_objFrame(rectAdd);
		ptrAdd->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "ADD";
		ptrAdd->Set_strText(strText);
		ptrAdd->SetVisible(true);
		ptrToolBar->AddSubWidget(ptrAdd);
	};

	GtButton *  ptrDel = new GtButton(ptrToolBar);
	if (ptrDel)
	{
		GtRectI rectSub;
		rectSub.xMin = 65;
		rectSub.xMax = 115;
		rectSub.yMin = 0;
		rectSub.yMax = 50;
		ptrDel->Set_objFrame(rectSub);
		ptrDel->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "DEL";
		ptrDel->Set_strText(strText);
		ptrDel->SetVisible(true);
		ptrToolBar->AddSubWidget(ptrDel);
	};

	GtButton *  ptrDelAll = new GtButton(ptrToolBar);
	if (ptrDelAll)
	{
		GtRectI rectDel;
		rectDel.xMin = 120;
		rectDel.xMax = 225;
		rectDel.yMin = 0;
		rectDel.yMax = 50;
		ptrDelAll->Set_objFrame(rectDel);
		ptrDelAll->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "DEL ALL";
		ptrDelAll->Set_strText(strText);
		ptrDelAll->SetVisible(true);
		ptrToolBar->AddSubWidget(ptrDelAll);
	};
};

void TestWindow::InitializeActions(void)
{

	//LIST MODEL CONTROLS////
	//if(m_cmdLoadList01)
	//{
	//	m_cmdLoadList01->Clicked.SlotConnect(this,&TestWindow::OnList01_Clicked);
	//};

};

