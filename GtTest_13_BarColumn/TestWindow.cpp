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
		m_ptrPlot01 = new GtPlot2DBar(this);

		if(m_ptrPlot01)
		{
			GtAxisHorizontal * ptrXAxis = new GtAxisHorizontal(m_ptrPlot01);
			if(ptrXAxis)
			{
				rectH.xMin = 100;
				rectH.xMax = 600;
				rectH.yMin = 500;
				rectH.yMax = 525;
				ptrXAxis->Set_objFrame(rectH);
				ptrXAxis->Update();
				GtScaleLogarithm*  ptrScale = new GtScaleLogarithm(ptrXAxis);
				
				ptrXAxis->Set_sngLB(0.10f);
				ptrXAxis->Set_sngUB(1000.0f);
				ptrScale->Set_pt0(GtPoint3DF(0.1,100));
				ptrScale->Set_pt1(GtPoint3DF(1000,600));
				ptrScale->Initialize();

				ptrXAxis->Set_ptrScale(ptrScale);

				ptrXAxis->Set_sngMajor(10);
				m_ptrPlot01->AddHorizAxis(ptrXAxis);

			}


			GtAxisVertical * ptrYAxis = new GtAxisVertical(m_ptrPlot01);
			if(ptrYAxis)
			{
				rectV.xMin = 25;
				rectV.xMax = 50;
				rectV.yMin = 100;
				rectV.yMax = 500;
				ptrYAxis->Set_objFrame(rectV);
				ptrYAxis->Set_sngLB(0);
				ptrYAxis->Set_sngUB(6);
				ptrYAxis->Update();
				m_ptrPlot01->AddVertAxis(ptrYAxis);
			}

			rect.xMin = 100;
			rect.xMax = 600;
			rect.yMin = 100;
			rect.yMax = 500;
			m_ptrPlot01->Set_objFrame(rect);
			strCmd = "My Plot";

			GtPlotCanvas* ptrCanvas = m_ptrPlot01->GetCanvasPtr();
			m_ptrSet01 = new GtPlotBar(ptrCanvas);
			m_ptrSet01->Set_ptrXAxis(ptrXAxis);
			m_ptrSet01->Set_ptrYAxis(ptrYAxis);

			
			GtBarItem item;

			item.m_dblVal = 0.5;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 25;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 250;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 12;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 645;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 6;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			ptrCanvas->AddItem(m_ptrSet01);

			m_ptrPlot01->Set_strTitle(strCmd);
			m_ptrPlot01->SetVisible(true);
			this->AddSubWidget(m_ptrPlot01);			
		}	

	};

	if(!m_ptrPlot02)
	{
		m_ptrPlot02 = new GtPlot2DColumn(this);

		if(m_ptrPlot02)
		{
			GtAxisHorizontal * ptrXAxis = new GtAxisHorizontal(m_ptrPlot02);
			if(ptrXAxis)
			{
				rectH.xMin = 700;
				rectH.xMax = 1100;
				rectH.yMin = 500;
				rectH.yMax = 525;
				ptrXAxis->Set_objFrame(rectH);
				ptrXAxis->Set_sngLB(0);
				ptrXAxis->Set_sngUB(6);
				ptrXAxis->Update();
				ptrXAxis->Set_sngMajor(1);
				m_ptrPlot02->AddHorizAxis(ptrXAxis);

			}


			GtAxisVertical * ptrYAxis = new GtAxisVertical(m_ptrPlot02);
			if(ptrYAxis)
			{
				rectV.xMin = 675;
				rectV.xMax = 700;
				rectV.yMin = 100;
				rectV.yMax = 500;
				ptrYAxis->Set_objFrame(rectV);
				ptrYAxis->Update();
				GtScaleLogarithm*  ptrScale = new GtScaleLogarithm(ptrYAxis);
				
				ptrYAxis->Set_sngLB(0.10f);
				ptrYAxis->Set_sngUB(1000.0f);
				ptrScale->Set_pt0(GtPoint3DF(0.1,100));
				ptrScale->Set_pt1(GtPoint3DF(1000,500));
				ptrScale->Initialize();

				ptrYAxis->Set_ptrScale(ptrScale);
				m_ptrPlot02->AddVertAxis(ptrYAxis);
			}

			rect.xMin = 700;
			rect.xMax = 1100;
			rect.yMin = 100;
			rect.yMax = 500;
			m_ptrPlot02->Set_objFrame(rect);
			strCmd = "My Plot2";

			GtPlotCanvas* ptrCanvas = m_ptrPlot02->GetCanvasPtr();
			m_ptrSet02 = new GtPlotColumn(ptrCanvas);
			m_ptrSet02->Set_ptrXAxis(ptrXAxis);
			m_ptrSet02->Set_ptrYAxis(ptrYAxis);

			
			GtColumnItem item;

			item.m_dblVal = 0.5;
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 25;
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 250;
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 12;
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 645;
			m_ptrSet02->m_arrObjPoints.push_back(item);
			item.m_dblVal = 6;
			m_ptrSet02->m_arrObjPoints.push_back(item);
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

