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

	m_txtItemName = NULL;
	m_ptrPlot01 = NULL;
	m_ptrCurve01 = NULL;
	m_ptrCurve02 = NULL;

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

	//LIST MODEL CONTROLS////
	if(!m_ptrPlot01)
	{
		m_ptrPlot01 = new GtPlot2DScatter(this);

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

				ptrScale->Set_pt0(GtPoint3DF(0.1,100));
				ptrScale->Set_pt1(GtPoint3DF(1000,600));
				ptrScale->Initialize();

				ptrXAxis->Set_ptrScale(ptrScale);
				ptrXAxis->Set_sngLB(0.10f);
				ptrXAxis->Set_sngUB(1000.0f);
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
			m_ptrCurve01 = new GtPlotCurve(ptrCanvas);
			m_ptrCurve01->Set_ptrXAxis(ptrXAxis);
			m_ptrCurve01->Set_ptrYAxis(ptrYAxis);

			GtPlotSymbol objSym;
			objSym.Set_intSize(10);
			objSym.Set_objSymType(SymbolDiamond);
			//objSym.Set_objSymType(SymbolTriangle);
			m_ptrCurve01->Set_objSymbol(objSym);
			m_ptrCurve01->Set_objBackColor(GtColor(255,0,0));
			m_ptrCurve01->Set_objForeColor(GtColor(0,0,255));

			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(0.1,1.0));
			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(0.8,3.4));
			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(40.0,2.5));
			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(500.0,6.0));
			ptrCanvas->AddItem(m_ptrCurve01);


			m_ptrCurve02 = new GtPlotCurve(ptrCanvas);
			m_ptrCurve02->Set_ptrXAxis(ptrXAxis);
			m_ptrCurve02->Set_ptrYAxis(ptrYAxis);

			GtPlotSymbol objSym2;
			objSym2.Set_intSize(10);
			objSym2.Set_objSymType(SymbolTriangle);
			//objSym.Set_objSymType(SymbolTriangle);
			m_ptrCurve02->Set_objSymbol(objSym2);
			m_ptrCurve02->Set_objBackColor(GtColor(0,255,0));
			m_ptrCurve02->Set_objForeColor(GtColor(255,0,255));

			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(10.0,1.0));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(50.0,4.5));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(200.0,2.5));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(800.0,6.0));
			ptrCanvas->AddItem(m_ptrCurve02);

			m_ptrPlot01->Set_strTitle(strCmd);
			m_ptrPlot01->SetVisible(true);
			this->AddSubWidget(m_ptrPlot01);			
		}	

	};

	//if(!m_txtItemName)
	//{
	//	m_txtItemName = new GtSimpleTextEdit(this);
	//	rect.xMin = 50;
	//	rect.xMax = 400;
	//	rect.yMin = 525;
	//	rect.yMax = 550;
	//	if(m_txtItemName)
	//	{
	//		m_txtItemName->Set_objFrame(rect);
	//		m_txtItemName->Set_objBackBrush(GtBrush(GtColor(255,255,255)));
	//		strName = L"nil";
	//		m_txtItemName->Set_strText(strName);
	//		this->AddSubWidget(m_txtItemName);	
	//	}
	//}

};

void TestWindow::InitializeActions(void)
{

	//LIST MODEL CONTROLS////
	//if(m_cmdLoadList01)
	//{
	//	m_cmdLoadList01->Clicked.SlotConnect(this,&TestWindow::OnList01_Clicked);
	//};

};

