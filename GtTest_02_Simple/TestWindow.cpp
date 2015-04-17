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
#include <GtTextView\GtSimpleTextEdit.h>
//default constructor
TestWindow::TestWindow(GtObject* ptrParent)
: GtMainWindow(ptrParent)
{
	m_strType = "TestWindow";
	std::wstring strCmd;
	GtRectI rectNew;
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

void TestWindow::InitializeControls(void)
{
	std::string strText;

	//add the button
	GtRectI buttonRect;
	GtButton *  ptrButton = new GtButton(this);
	if (ptrButton)
	{
		buttonRect.xMin = 50;
		buttonRect.xMax = 200;
		buttonRect.yMin = 50;
		buttonRect.yMax = 100;
		ptrButton->Set_objFrame(buttonRect);
		ptrButton->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		strText = "MyButton";
		ptrButton->Set_strText(strText);
		ptrButton->SetVisible(true);
		this->AddSubWidget(ptrButton);
	}

	GtRectI checkRect;
	GtCheckBox * ptrCheck = new GtCheckBox(this);
	if (ptrCheck)
	{
		checkRect.xMin = 50;
		checkRect.xMax = 200;
		checkRect.yMin = 150;
		checkRect.yMax = 175;
		ptrCheck->Set_objFrame(checkRect);
		strText = "MyCheckBox";
		ptrCheck->Set_strText(strText);
		ptrCheck->Set_blnChecked(true);
		ptrCheck->SetVisible(true);
		ptrCheck->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		this->AddSubWidget(ptrCheck);
	}

	GtRectI comboRect;
	GtComboBox * ptrCombo = new GtComboBox(this);
	if (ptrCombo)
	{
		comboRect.xMin = 50;
		comboRect.xMax = 250;
		comboRect.yMin = 200;
		comboRect.yMax = 225;
		ptrCombo->Set_objFrame(comboRect);
		ptrCombo->Set_objBackBrush(GtBrush(GtColor(255, 255, 255)));

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

		this->AddSubWidget(ptrCombo);
	}

	GtRectI dateRect;
	GtDateEdit *ptrDate = new GtDateEdit(this);
	if (ptrDate)
	{
		dateRect.xMin = 50;
		dateRect.xMax = 200;
		dateRect.yMin = 250;
		dateRect.yMax = 275;
		ptrDate->Set_objFrame(dateRect);
		strText = "MyDateEdit";
		ptrDate->Set_strText(strText);
		ptrDate->SetVisible(true);
		ptrDate->Set_intDay(07);
		ptrDate->Set_intMonth(10);
		ptrDate->Set_intYear(2014);
		ptrDate->Set_objBackBrush(GtBrush(GtColor(255, 255, 255)));
		this->AddSubWidget(ptrDate);
	}

	GtRectI timeRect;
	GtTimeEdit * ptrTime = new GtTimeEdit(this);

	if (ptrTime)
	{
		timeRect.xMin = 50;
		timeRect.xMax = 200;
		timeRect.yMin = 300;
		timeRect.yMax = 325;
		ptrTime->Set_objFrame(timeRect);
		strText = "MyTimeEdit";
		ptrTime->Set_strText(strText);
		ptrTime->SetVisible(true);
		ptrTime->Set_intHour(05);
		ptrTime->Set_intMinute(30);
		ptrTime->Set_intSecond(45);
		ptrTime->Set_objBackBrush(GtBrush(GtColor(255, 255, 255)));
		this->AddSubWidget(ptrTime);
	}

	GtRectI labelRect;
	GtLabel * ptrLabel = new GtLabel(this);
	if (ptrLabel)
	{
		labelRect.xMin = 50;
		labelRect.xMax = 200;
		labelRect.yMin = 350;
		labelRect.yMax = 375;
		ptrLabel->Set_objFrame(labelRect);
		strText = "MyLabelText";
		ptrLabel->Set_strText(strText);
		ptrLabel->SetVisible(true);
		ptrLabel->Set_objBackBrush(GtBrush(GtColor(255, 255, 255)));
		this->AddSubWidget(ptrLabel);
	}

	GtRectI spinRect;
	GtSpinBox *  ptrSpinBox = new GtSpinBox(this);
	if (ptrSpinBox)
	{
		spinRect.xMin = 50;
		spinRect.xMax = 200;
		spinRect.yMin = 400;
		spinRect.yMax = 425;
		ptrSpinBox->Set_objFrame(spinRect);
		strText = "MySpinBox";
		ptrSpinBox->Set_strText(strText);
		ptrSpinBox->SetVisible(true);
		ptrSpinBox->Set_intValue(85);
		ptrSpinBox->Set_objBackBrush(GtBrush(GtColor(255, 255, 0)));
		this->AddSubWidget(ptrSpinBox);
	}

	GtRectI vscrollRect;
	GtVertScrollBar * ptrVScroll = new GtVertScrollBar(this);
	if (ptrVScroll)
	{
		vscrollRect.xMin = 300;
		vscrollRect.xMax = 325;
		vscrollRect.yMin = 50;
		vscrollRect.yMax = 200;
		ptrVScroll->Set_objFrame(vscrollRect);
		strText = "MyVertScroll";
		ptrVScroll->Set_strText(strText);
		ptrVScroll->Set_intMin(0);
		ptrVScroll->Set_intMax(100);
		ptrVScroll->Set_intValue(75);
		ptrVScroll->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		this->AddSubWidget(ptrVScroll);
	}

	GtRectI hscrollRect;
	GtHorizScrollBar * ptrHScroll = new GtHorizScrollBar(this);
	if (ptrHScroll)
	{
		hscrollRect.xMin = 400;
		hscrollRect.xMax = 600;
		hscrollRect.yMin = 50;
		hscrollRect.yMax = 75;
		ptrHScroll->Set_objFrame(hscrollRect);
		strText = "MyHorizScroll";
		ptrHScroll->Set_strText(strText);
		ptrHScroll->Set_intMin(0);
		ptrHScroll->Set_intMax(100);
		ptrHScroll->Set_intValue(75);
		ptrHScroll->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		this->AddSubWidget(ptrHScroll);
	}

	GtRectI sliderRect;
	GtSlider * ptrSlider = new GtSlider(this);
	if (ptrSlider)
	{
		sliderRect.xMin = 400;
		sliderRect.xMax = 600;
		sliderRect.yMin = 100;
		sliderRect.yMax = 125;
		ptrSlider->Set_objFrame(sliderRect);
		strText = "MySlider";
		ptrSlider->Set_strText(strText);
		ptrSlider->Set_intMin(0);
		ptrSlider->Set_intMax(100);
		ptrSlider->Set_intValue(75);
		ptrSlider->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		this->AddSubWidget(ptrSlider);
	}


	GtRectI progressRect;
	GtProgressBar * ptrProgress = new GtProgressBar(this);
	if (ptrProgress)
	{
		progressRect.xMin = 400;
		progressRect.xMax = 600;
		progressRect.yMin = 150;
		progressRect.yMax = 175;
		ptrProgress->Set_objFrame(progressRect);
		strText = "MyProgressBar";
		ptrProgress->Set_strText(strText);
		ptrProgress->Set_intMin(0);
		ptrProgress->Set_intMax(100);
		ptrProgress->Set_intValue(75);
		ptrProgress->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		this->AddSubWidget(ptrProgress);
	}
	//Hook up the progress bar to the slider.
	//Good example of signal slot with single argument
	if((ptrSlider)&&(ptrProgress))
	{
		ptrSlider->ValueChanged.SlotConnect<GtProgressBar>(ptrProgress, &GtProgressBar::Set_intValue);
	}

	GtRectI radioRect;
	GtRadioButton * ptrRadio = new GtRadioButton(this);
	if (ptrRadio)
	{
		radioRect.xMin = 400;
		radioRect.xMax = 600;
		radioRect.yMin = 200;
		radioRect.yMax = 225;
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
		this->AddSubWidget(ptrRadio);
	}

	GtRectI editRect;
	GtSimpleTextEdit * ptrEdit = new GtSimpleTextEdit(this);
	if (ptrEdit)
	{
		editRect.xMin = 400;
		editRect.xMax = 600;
		editRect.yMin = 350;
		editRect.yMax = 375;
		ptrEdit->Set_objFrame(editRect);
		ptrEdit->Set_objBackBrush(GtBrush(GtColor(255, 255, 255)));
		this->AddSubWidget(ptrEdit);
	}

	return;
};
