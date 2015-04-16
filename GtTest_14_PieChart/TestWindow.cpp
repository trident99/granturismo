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

	m_ptrPlot01 = NULL;
	m_ptrSet01 = NULL;

	m_ptrPlot02 = NULL;
	m_ptrSet02 = NULL;

	GtRectI rectNew;
	rectNew.xMin = 0;
	rectNew.xMax = 1200;
	rectNew.yMin = 0;
	rectNew.yMax = 800;
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



};

void TestWindow::InitializeControls(void)
{
	GtRectI rect, rectH, rectV;
	std::string strCmd,strName;

	//LIST MODEL CONTROLS////
	if(!m_ptrPlot01)
	{
		m_ptrPlot01 = new GtPlot2DPieChart(this);

		if(m_ptrPlot01)
		{
			
			rect.xMin = 100;
			rect.xMax = 600;
			rect.yMin = 100;
			rect.yMax = 500;
			m_ptrPlot01->Set_objFrame(rect);
			strCmd = "My Plot";

			GtPlotCanvas* ptrCanvas = m_ptrPlot01->GetCanvasPtr();
			m_ptrSet01 = new GtPlotPie(ptrCanvas);
			
			GtPieItem item;

			item.m_dblVal = 24;
			item.m_objColor.SetRGB(0,255,0);
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 75;
			item.m_objColor.SetRGB(255,0,0);
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 180;
			item.m_objColor.SetRGB(130,130,130);
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 6;
			item.m_objColor.SetRGB(0,0,255);
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 45;
			item.m_objColor.SetRGB(255,130,190);
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 22;
			item.m_objColor.SetRGB(140,240,240);
			m_ptrSet01->m_arrObjPoints.push_back(item);

			long cX,cY;
			cX = (long)(double(rect.xMax - rect.xMin) / 2.0f);
			cY = (long)(double(rect.yMax - rect.yMin) / 2.0f);
			m_ptrSet01->Set_objCenterPos(GtPoint3DI(cX,cY));

			m_ptrSet01->SetInnerRadius(0);
			m_ptrSet01->SetOuterRadius(175);

			m_ptrSet01->UpdateData();
			ptrCanvas->AddItem(m_ptrSet01);

			m_ptrPlot01->Set_strTitle(strCmd);
			m_ptrPlot01->SetVisible(true);
			this->AddSubWidget(m_ptrPlot01);			
		}	

	};

	if(!m_ptrPlot02)
	{
		m_ptrPlot02 = new GtPlot2DPieChart(this);

		if(m_ptrPlot02)
		{
			rect.xMin = 700;
			rect.xMax = 1100;
			rect.yMin = 100;
			rect.yMax = 500;
			m_ptrPlot02->Set_objFrame(rect);
			strCmd = "My Plot2";

			GtPlotCanvas* ptrCanvas = m_ptrPlot02->GetCanvasPtr();
			m_ptrSet02 = new GtPlotPie(ptrCanvas);
			
			GtPieItem item;

			item.m_dblVal = 75;
			item.m_objColor.SetRGB(255,0,0);
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 25;
			item.m_objColor.SetRGB(255,0,255);
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 250;
			item.m_objColor.SetRGB(0,130,0);
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 80;
			item.m_objColor.SetRGB(255,110,0);
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 45;
			item.m_objColor.SetRGB(130,130,190);
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 10;
			item.m_objColor.SetRGB(255,255,0);
			m_ptrSet02->m_arrObjPoints.push_back(item);
			
			long cX,cY;
			cX = (long)(double(rect.xMax - rect.xMin) / 2.0f);
			cY = (long)(double(rect.yMax - rect.yMin) / 2.0f);
			m_ptrSet02->Set_objCenterPos(GtPoint3DI(cX,cY));
			m_ptrSet02->SetInnerRadius(100);
			m_ptrSet02->SetOuterRadius(175);

			m_ptrSet02->UpdateData();
			ptrCanvas->AddItem(m_ptrSet02);

			m_ptrPlot02->Set_strTitle(strCmd);
			m_ptrPlot02->SetVisible(true);
			this->AddSubWidget(m_ptrPlot02);			
		}	

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

