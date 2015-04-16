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

//#pragma once
//#pragma warning(push)
//#pragma warning (disable : 4005 ) /* macro redefinition */
//#define HTL_DLLEXPORT
//#pragma warning(pop)

#include ".\ButtonGrid.h"
#include <GtBasicControls\GtComboBox.h>
#include <GtBasicControls\GtCheckBox.h>
#include <modGtEvent.h>

//!Parent set constructor
ButtonGrid::ButtonGrid(GtObject* ptrParent)
:GtFrame(ptrParent)
{
	m_ptrButton01 = NULL;
	m_ptrButton02 = NULL;
	m_ptrButton03 = NULL;
	m_ptrButton04 = NULL;
	m_ptrButton05 = NULL;
	m_ptrButton06 = NULL;
	m_ptrButton07 = NULL;
	m_ptrButton08 = NULL;
	m_objBackBrush = GtBrush(GtColor(255,50,50));
	this->Initialize();
};
//!Virtual destructor
ButtonGrid::~ButtonGrid(void)
{
	this->DeleteAllSubWidgets();
};

void ButtonGrid::Initialize(void)
{
	m_objFrame.xMin = 0;
	m_objFrame.xMax = 600;
	m_objFrame.yMin = 0;
	m_objFrame.yMax = 600;

	GtRectI newRect;
	std::string strText;

	m_ptrButton01 = new GtButton(this);
	if(m_ptrButton01)
	{
		newRect.xMin = 50;
		newRect.xMax = 100;
		newRect.yMin = 50;
		newRect.yMax = 100;
		m_ptrButton01->Set_objFrame(newRect);
		strText = "ONE";
		m_ptrButton01->Set_strText(strText);
		m_ptrButton01->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
		this->AddSubWidget(m_ptrButton01);
	};

	m_ptrButton02 = new GtButton(this);
	if(m_ptrButton02)
	{
		newRect.xMin = 150;
		newRect.xMax = 200;
		newRect.yMin = 150;
		newRect.yMax = 200;
		m_ptrButton02->Set_objFrame(newRect);
		strText = "TWO";
		m_ptrButton02->Set_strText(strText);
		m_ptrButton02->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
		this->AddSubWidget(m_ptrButton02);
	};

	m_ptrButton03 = new GtButton(this);
	if(m_ptrButton03)
	{
		newRect.xMin = 250;
		newRect.xMax = 300;
		newRect.yMin = 250;
		newRect.yMax = 300;
		m_ptrButton03->Set_objFrame(newRect);
		strText = "THREE";
		m_ptrButton03->Set_strText(strText);
		m_ptrButton03->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
		this->AddSubWidget(m_ptrButton03);
	};

	m_ptrButton04 = new GtButton(this);
	if(m_ptrButton04)
	{
		newRect.xMin = 350;
		newRect.xMax = 400;
		newRect.yMin = 350;
		newRect.yMax = 400;
		m_ptrButton04->Set_objFrame(newRect);
		strText = "FOUR";
		m_ptrButton04->Set_strText(strText);
		m_ptrButton04->Set_objBackBrush(GtBrush(GtColor(160,160,160)));
		this->AddSubWidget(m_ptrButton04);
	};

	GtComboBox* ptrCombo = new GtComboBox(this);
	if(ptrCombo)
	{
		GtRectI comboRect;
		comboRect.xMin = 150;
		comboRect.xMax = 350;
		comboRect.yMin = 50;
		comboRect.yMax = 75;
		ptrCombo->Set_objFrame(comboRect);
		//set color BEFORE adding items
		ptrCombo->Set_objBackBrush(GtBrush(GtColor(255,255,255)));

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
		this->AddSubWidget(ptrCombo);
	}

		GtCheckBox* ptrCheck = new GtCheckBox(this);
		if(ptrCheck)
		{
			GtRectI checkRect;
			checkRect.xMin = 150;
			checkRect.xMax = 250;
			checkRect.yMin = 100;
			checkRect.yMax = 150;
			ptrCheck->Set_objFrame(checkRect);
			std::string strText;
			strText = "MyCheckBox";
			ptrCheck->Set_strText(strText);
			ptrCheck->Set_blnChecked(true);
			ptrCheck->SetVisible(true);
			ptrCheck->Set_objBackBrush(GtBrush(GtColor(255,255,0)));
			this->AddSubWidget(ptrCheck);
		}

};


//!Custom Event Processing
int ButtonGrid::HandleEvent(GtEvent * ptrEvent)
{
	return 0;
};
//!Custom Widget Painting
int ButtonGrid::OnPaint(GtPainter * painter)
{
	if(!m_blnVisible){return 0;};
	if(!painter){return 0;};
	//paint the frame
	GtPen inPen, outPen, oldPen;
	GtBrush oldBrush;
	GtRectI inRect, outRect;

	int delta = 2;
	//INITIALIZE PENS AND BRUSHES

	//record current painter settings
	oldPen = painter->Get_objPen();
	oldBrush = painter->Get_objBrush();

	GtFrame::OnPaint(painter);

	//finished, reset old brushes and pens
	painter->Set_objPen(oldPen);
	painter->Set_objBrush(oldBrush);
	return 1;
};	