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
#include <GtBasicControls\GtToolBox.h>
#include <GtBasicControls\GtTabPage.h>
#include <GtWinForms\GtMainWindow.h>



#include <GtGridView\GtGridCell.h>
#include <GtGridView\GtGridRow.h>
#include <GtGridView\GtGridColumn.h>
#include <GtGridView\GtGridView.h>


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

	GtToolBox* ptrToolBox = new GtToolBox(this);
	if (ptrToolBox)
	{
		GtRectI rectToolBox;
		rectToolBox.xMin = 25;
		rectToolBox.xMax = 300;
		rectToolBox.yMin = 50;
		rectToolBox.yMax = 450;
		ptrToolBox->Set_objFrame(rectToolBox);
		ptrToolBox->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "MyToolBox";
		ptrToolBox->Set_strText(strText);
		ptrToolBox->SetVisible(true);
		this->AddSubWidget(ptrToolBox);
	}


	GtTabPage* ptrPage1 = new GtTabPage(ptrToolBox);
	if (ptrPage1)
	{
		ptrPage1->Set_objBackBrush(GtBrush(GtColor(120, 120, 200)));
		std::string strText = "PageOne";
		ptrPage1->Set_strText(strText);
		ptrPage1->SetVisible(true);
		ptrToolBox->AddTabPage(ptrPage1);
	}

	//add the button
	GtRectI buttonRect;
	GtButton *  ptrButton = new GtButton(ptrPage1);
	if (ptrButton)
	{
		buttonRect.xMin = 50;
		buttonRect.xMax = 175;
		buttonRect.yMin = 50;
		buttonRect.yMax = 150;
		ptrButton->Set_objFrame(buttonRect);
		ptrButton->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "MyButton";
		ptrButton->Set_strText(strText);
		ptrButton->SetVisible(true);
		ptrPage1->AddSubWidget(ptrButton);
	};

	GtTabPage* ptrPage2 = new GtTabPage(ptrToolBox);
	if (ptrPage2)
	{
		ptrPage2->Set_objBackBrush(GtBrush(GtColor(120, 255, 255)));
		std::string strText = "PageTwo";
		ptrPage2->Set_strText(strText);
		ptrPage2->SetVisible(true);
		ptrToolBox->AddTabPage(ptrPage2);
	}


	GtCheckBox* ptrCheck = new GtCheckBox(ptrPage2);
	if (ptrCheck)
	{
		GtRectI checkRect;
		checkRect.xMin = 50;
		checkRect.xMax = 200;
		checkRect.yMin = 50;
		checkRect.yMax = 75;
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
		comboRect.xMin = 50;
		comboRect.xMax = 250;
		comboRect.yMin = 100;
		comboRect.yMax = 125;
		ptrCombo->Set_objFrame(comboRect);
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

	GtTabPage* ptrPage3 = new GtTabPage(ptrToolBox);
	if (ptrPage3)
	{
		ptrPage3->Set_objBackBrush(GtBrush(GtColor(255, 120, 120)));
		std::string strText = "PageThree";
		ptrPage3->Set_strText(strText);
		ptrPage3->SetVisible(true);
		ptrToolBox->AddTabPage(ptrPage3);
	}


	GtRadioButton* ptrRadio = new GtRadioButton(ptrPage3);
	if (ptrRadio)
	{
		GtRectI radioRect;
		radioRect.xMin = 50;
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

	GtTabPage* ptrPage4 = new GtTabPage(ptrToolBox);
	if (ptrPage4)
	{
		ptrPage4->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		std::string strText = "PageFour";
		ptrPage4->Set_strText(strText);
		ptrPage4->SetVisible(true);
		ptrToolBox->AddTabPage(ptrPage4);
	}


	GtSlider *  ptrSlider = new GtSlider(ptrPage4);
	if (ptrSlider)
	{
		GtRectI sliderRect;
		sliderRect.xMin = 50;
		sliderRect.xMax = 250;
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


	GtGridView * ptrGrid = new GtGridView(this);
	if (ptrGrid)
	{
		GtRectI gridRect;
		gridRect.xMin = 350;
		gridRect.xMax = 700;
		gridRect.yMin = 50;
		gridRect.yMax = 450;
		ptrGrid->Set_objFrame(gridRect);
		ptrGrid->Set_intNumFixedRows(1);
		ptrGrid->Set_intNumFixedCols(1);
		ptrGrid->Resize(10, 10);
		//set cells text
		size_t i, j;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				char buf[24];
				sprintf(buf, "R%dC%d", i, j);
				GtGridCell* ptrCell = ptrGrid->GetCellPtr(i, j);
				if (ptrCell)
				{
					std::string str = buf;
					ptrCell->Set_strText(str);
				}
			}//end loop through rows

		}//end loop through columns

		ptrGrid->SetRowHeight(3, 50);
		ptrGrid->SetColumnWidth(4, 100);

		this->AddSubWidget(ptrGrid);
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

