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
	m_ptrPlot02 = NULL;
	m_ptrSet01 = NULL;
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
		m_ptrPlot01 = new GtPlot2DCurve(this);

		if(m_ptrPlot01)
		{
			GtAxisHorizontal * ptrXAxis = new GtAxisHorizontal(m_ptrPlot01);
			if(ptrXAxis)
			{
				rectH.xMin = 50;
				rectH.xMax = 500;
				rectH.yMin = 500;
				rectH.yMax = 525;
				ptrXAxis->Set_objFrame(rectH);
				ptrXAxis->Update();
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

			rect.xMin = 50;
			rect.xMax = 500;
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

			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(1.0,1.0));
			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(2.5,3.4));
			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(5.25,2.5));
			m_ptrCurve01->m_arrObjPoints.push_back(GtPoint3DF(11.0,6.0));
			std::string strTemp1 = "Curve One";
			m_ptrCurve01->Set_strText(strTemp1);
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

			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(-5.0,1.0));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(1.0,4.5));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(6.5,2.5));
			m_ptrCurve02->m_arrObjPoints.push_back(GtPoint3DF(8.0,6.0));
			std::string strTemp2 = "Curve Two";
			m_ptrCurve02->Set_strText(strTemp2);
			ptrCanvas->AddItem(m_ptrCurve02);


			GtRectI rectLegend;
			rectLegend.xMin = 350;
			rectLegend.xMax = 600;
			rectLegend.yMin = 50;
			rectLegend.yMax = 125;
			//Sync the Legend with the newly added points
			GtPlot2DLegend* ptrLegend = m_ptrPlot01->GetLegendPtr();
			ptrLegend->Set_objFrame(rectLegend);
			ptrLegend->UpdateLegend();

			m_ptrPlot01->Set_strTitle(strCmd);
			m_ptrPlot01->SetVisible(true);
			this->AddSubWidget(m_ptrPlot01);			
		}	

	};

	if(!m_ptrPlot02)
	{
		m_ptrPlot02 = new GtPlot2DScatter(this);

		if(m_ptrPlot02)
		{
			rect.xMin = 700;
			rect.xMax = 1100;
			rect.yMin = 100;
			rect.yMax = 500;
			m_ptrPlot02->Set_objFrame(rect);
			strCmd = "My Plot2";



			GtAxisHorizontal * ptrXAxis = new GtAxisHorizontal(m_ptrPlot02);
			if(ptrXAxis)
			{
				rectH.xMin = 700;
				rectH.xMax = 1100;
				rectH.yMin = 500;
				rectH.yMax = 525;
				ptrXAxis->Set_objFrame(rectH);
				ptrXAxis->Update();
				m_ptrPlot02->AddHorizAxis(ptrXAxis);

			}


			GtAxisVertical * ptrYAxis = new GtAxisVertical(m_ptrPlot02);
			if(ptrYAxis)
			{
				rectV.xMin = 650;
				rectV.xMax = 675;
				rectV.yMin = 100;
				rectV.yMax = 500;
				ptrYAxis->Set_objFrame(rectV);
				ptrYAxis->Set_sngLB( -2.0f);
				ptrYAxis->Set_sngUB( 2.0f);
				ptrYAxis->Set_sngMajor(0.25f);
				ptrYAxis->Set_sngMinor(0.05f);
				ptrYAxis->Update();
				m_ptrPlot02->AddVertAxis(ptrYAxis);
			}

			GtPlotCanvas* ptrCanvas = m_ptrPlot02->GetCanvasPtr();
			m_ptrSet01 = new GtPlotPointSet(ptrCanvas);
			m_ptrSet01->Set_ptrXAxis(ptrXAxis);
			m_ptrSet01->Set_ptrYAxis(ptrYAxis);
			GtPlotSymbol objSym;
			objSym.Set_intSize(10);
			objSym.Set_objSymType(SymbolDiamond);
			//objSym.Set_objSymType(SymbolTriangle);
			m_ptrSet01->Set_objSymbol(objSym);
			m_ptrSet01->Set_objBackColor(GtColor(255,0,0));
			m_ptrSet01->Set_objForeColor(GtColor(0,0,255));

			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(0	,0));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(0.2	,0.198669331));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(0.4	,0.389418342));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(0.6	,0.564642473));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(0.8	,0.717356091));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(1	,0.841470985));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(1.2	,0.932039086));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(1.4	,0.98544973));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(1.6	,0.999573603));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(1.8	,0.973847631));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(2	,0.909297427));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(2.2	,0.808496404));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(2.4	,0.675463181));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(2.6	,0.515501372));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(2.8	,0.33498815));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(3	,0.141120008));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(3.2	,-0.058374143));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(3.4	,-0.255541102));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(3.6	,-0.442520443));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(3.8	,-0.611857891));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(4	,-0.756802495));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(4.2	,-0.871575772));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(4.4	,-0.951602074));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(4.6	,-0.993691004));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(4.8	,-0.996164609));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(5	,-0.958924275));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(5.2	,-0.883454656));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(5.4	,-0.772764488));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(5.6	,-0.631266638));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(5.8	,-0.464602179));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(6	,-0.279415498));
			m_ptrSet01->m_arrObjPoints.push_back(GtPoint3DF(6.2831852	,0));
			std::string strTemp = "My Sine Wave";
			m_ptrSet01->Set_strText(strTemp);
			ptrCanvas->AddItem(m_ptrSet01);


			GtRectI rectLegend;
			rectLegend.xMin = 900;
			rectLegend.xMax = 1050;
			rectLegend.yMin = 150;
			rectLegend.yMax = 200;
			//Sync the Legend with the newly added points
			GtPlot2DLegend* ptrLegend = m_ptrPlot02->GetLegendPtr();
			ptrLegend->Set_objFrame(rectLegend);
			ptrLegend->UpdateLegend();

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

