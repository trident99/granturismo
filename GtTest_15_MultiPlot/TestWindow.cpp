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
	m_ptrCurve02 = NULL;
	m_ptrSet03 = NULL;
	m_cmdPlot = NULL;

	GtRectI rectNew;
	rectNew.xMin = 0;
	rectNew.xMax = 1000;
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


	//add the button
	GtRectI buttonRect;
	m_cmdPlot = new GtButton(this);
	if (m_cmdPlot)
	{
		buttonRect.xMin = 25;
		buttonRect.xMax = 100;
		buttonRect.yMin = 25;
		buttonRect.yMax = 75;
		m_cmdPlot->Set_objFrame(buttonRect);
		m_cmdPlot->Set_objBackBrush(GtBrush(GtColor(160, 160, 160)));
		strName = "PLOT";
		m_cmdPlot->Set_strText(strName);
		m_cmdPlot->SetVisible(true);
		this->AddSubWidget(m_cmdPlot);
	}



	//LIST MODEL CONTROLS////
	if(!m_ptrPlot01)
	{
		m_ptrPlot01 = new GtPlot2DGeneric(this);

		if(m_ptrPlot01)
		{
			
			rect.xMin = 200;
			rect.xMax = 900;
			rect.yMin = 100;
			rect.yMax = 500;
			m_ptrPlot01->Set_objFrame(rect);
			strCmd = "My Plot";

			GtPlotCanvas* ptrCanvas = m_ptrPlot01->GetCanvasPtr();
			GtAxisHorizontal * ptrX1Axis = new GtAxisHorizontal(m_ptrPlot01);
			if(ptrX1Axis)
			{
				rectH.xMin = 200;
				rectH.xMax = 900;
				rectH.yMin = 500;
				rectH.yMax = 525;
				ptrX1Axis->Set_objFrame(rectH);
				ptrX1Axis->Set_sngLB(0);
				ptrX1Axis->Set_sngUB(6);
				ptrX1Axis->Set_sngMajor(1);
				ptrX1Axis->Update();
				m_ptrPlot01->AddHorizAxis(ptrX1Axis);

			}


			GtAxisVertical * ptrY1Axis = new GtAxisVertical(m_ptrPlot01);
			if(ptrY1Axis)
			{
				rectV.xMin = 175;
				rectV.xMax = 200;
				rectV.yMin = 100;
				rectV.yMax = 500;
				ptrY1Axis->Set_objFrame(rectV);
				ptrY1Axis->Set_sngLB(0);
				ptrY1Axis->Set_sngUB(50);
				ptrY1Axis->Set_sngMajor(10);
				ptrY1Axis->Set_sngMinor(2);
				ptrY1Axis->Update();
				m_ptrPlot01->AddVertAxis(ptrY1Axis);
			}

			m_ptrSet01 = new GtPlotColumn(ptrCanvas);
			m_ptrSet01->Set_ptrXAxis(ptrX1Axis);
			m_ptrSet01->Set_ptrYAxis(ptrY1Axis);

			GtColumnItem item;
			item.m_dblVal = 5;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 25;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 37;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 10;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 45;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			item.m_dblVal = 15;
			m_ptrSet01->m_arrObjPoints.push_back(item);
			ptrCanvas->AddItem(m_ptrSet01);


			m_ptrCurve02 = new GtPlotCurve(ptrCanvas);
			m_ptrCurve02->Set_ptrXAxis(ptrX1Axis);
			m_ptrCurve02->Set_ptrYAxis(ptrY1Axis);

			GtPlotSymbol objSym;
			objSym.Set_intSize(10);
			objSym.Set_objSymType(SymbolDiamond);
			//objSym.Set_objSymType(SymbolTriangle);
			m_ptrCurve02->Set_objSymbol(objSym);
			m_ptrCurve02->Set_objBackColor(GtColor(255,0,0));
			m_ptrCurve02->Set_objForeColor(GtColor(0,0,255));

			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(1,10.0));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(2,30.0));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(3,45.0));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(4,50.0));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(5,37.0));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(6,5.0));
			ptrCanvas->AddItem(m_ptrCurve02);


			GtAxisHorizontal * ptrX2Axis = new GtAxisHorizontal(m_ptrPlot01);
			if(ptrX2Axis)
			{
				rectH.xMin = 200;
				rectH.xMax = 900;
				rectH.yMin = 550;
				rectH.yMax = 575;
				ptrX2Axis->Set_objFrame(rectH);
				ptrX2Axis->Set_sngLB( -2.0f);
				ptrX2Axis->Set_sngUB( 8.0f);
				ptrX2Axis->Update();
				m_ptrPlot01->AddHorizAxis(ptrX2Axis);

			}


			GtAxisVertical * ptrY2Axis = new GtAxisVertical(m_ptrPlot01);
			if(ptrY2Axis)
			{
				rectV.xMin = 125;
				rectV.xMax = 150;
				rectV.yMin = 100;
				rectV.yMax = 500;
				ptrY2Axis->Set_objFrame(rectV);
				ptrY2Axis->Set_sngLB( -2.0f);
				ptrY2Axis->Set_sngUB( 2.0f);
				ptrY2Axis->Set_sngMajor(0.25f);
				ptrY2Axis->Set_sngMinor(0.05f);
				ptrY2Axis->Set_strFormat(std::string("%3.2f"));
				ptrY2Axis->Update();
				m_ptrPlot01->AddVertAxis(ptrY2Axis);
			}

			m_ptrSet03 = new GtPlotPointSet(ptrCanvas);
			m_ptrSet03->Set_ptrXAxis(ptrX2Axis);
			m_ptrSet03->Set_ptrYAxis(ptrY2Axis);
			GtPlotSymbol objSym2;
			objSym2.Set_intSize(10);
			objSym2.Set_objSymType(SymbolDiamond);
			//objSym.Set_objSymType(SymbolTriangle);
			m_ptrSet03->Set_objSymbol(objSym2);
			m_ptrSet03->Set_objBackColor(GtColor(255,100,0));
			m_ptrSet03->Set_objForeColor(GtColor(0,0,255));

			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(0	,0));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(0.2	,0.198669331));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(0.4	,0.389418342));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(0.6	,0.564642473));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(0.8	,0.717356091));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(1	,0.841470985));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(1.2	,0.932039086));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(1.4	,0.98544973));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(1.6	,0.999573603));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(1.8	,0.973847631));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(2	,0.909297427));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(2.2	,0.808496404));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(2.4	,0.675463181));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(2.6	,0.515501372));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(2.8	,0.33498815));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(3	,0.141120008));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(3.2	,-0.058374143));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(3.4	,-0.255541102));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(3.6	,-0.442520443));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(3.8	,-0.611857891));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(4	,-0.756802495));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(4.2	,-0.871575772));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(4.4	,-0.951602074));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(4.6	,-0.993691004));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(4.8	,-0.996164609));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(5	,-0.958924275));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(5.2	,-0.883454656));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(5.4	,-0.772764488));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(5.6	,-0.631266638));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(5.8	,-0.464602179));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(6	,-0.279415498));
			m_ptrSet03->m_arrObjPoints.push_back(GtPoint3DF(6.2831852	,0));
			ptrCanvas->AddItem(m_ptrSet03);

			m_ptrPlot01->Set_strTitle(strCmd);
			m_ptrPlot01->SetVisible(true);
			this->AddSubWidget(m_ptrPlot01);			
		}	

	};

	
};

void TestWindow::InitializeActions(void)
{

	//LIST MODEL CONTROLS////
	if(m_cmdPlot)
	{
		m_cmdPlot->Clicked.SlotConnect(this, &TestWindow::OnPlot_Click);
	};

};


void TestWindow::OnPlot_Click(void)
{
	this->PostPaint();
};