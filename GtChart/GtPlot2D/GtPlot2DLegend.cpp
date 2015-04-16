/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
**  Qwt Widget Library
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

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtPlot2DLegend.h"
#include "..\GtPlotModel\GtPlotItem.h"
#include "..\GtPlotModel\GtPlotCanvas.h"
#include ".\GtPlot2DBase.h"
namespace GT
{
	namespace GtChart
	{
		//GtPlot2DLegendItem/////////////////////////////////////////////
		GtPlot2DLegendItem::GtPlot2DLegendItem()
		{
			m_objSymbol.Set_objSymType(SymbolPoint);
			m_objBackColor.SetRGB(255,0,0);
			m_objForeColor.SetRGB(0,0,0);
			m_objFrame.Zero();
		}
		GtPlot2DLegendItem::GtPlot2DLegendItem(const GtPlot2DLegendItem & rhs)
		{
			if(this == &rhs){return;};

			m_strText = rhs.m_strText;
			m_objSymbol = rhs.m_objSymbol;
			m_objBackColor = rhs.m_objBackColor;
			m_objForeColor = rhs.m_objForeColor;
			m_objFrame = rhs.m_objFrame;
			
		};	
		GtPlot2DLegendItem::~GtPlot2DLegendItem(){};
		//!Assignment Operator
		GtPlot2DLegendItem & GtPlot2DLegendItem::operator = (const GtPlot2DLegendItem & rhs)
		{
			if(this != &rhs)
			{
				m_strText = rhs.m_strText;
				m_objSymbol = rhs.m_objSymbol;
				m_objBackColor = rhs.m_objBackColor;
				m_objForeColor = rhs.m_objForeColor;
				m_objFrame = rhs.m_objFrame;
			};
			return *this;
			
		};
		int GtPlot2DLegendItem::Draw( GtPainter *painter)
		{	
			if(!painter){return 0;};//safety check
			painter->Set_objBrush(GtBrush(m_objBackColor));
			painter->Set_objPen(GtPen(m_objForeColor));
			//update geometries
			//BASED ON 25 PIX CELL HEIGHT, 150 PIX CELL WIDTH
			GtLineF midline;
			GtRectI textBox;
			textBox = this->m_objFrame;	
			midline.m_P0.x = m_objFrame.xMin;
			midline.m_P1.x = m_objFrame.xMin + 25;
			midline.m_P0.y = m_objFrame.yMin + 12;
			midline.m_P1.y = m_objFrame.yMin + 12;
			this->m_objSymbol.Set_objCanvasPos(GtPoint3DI((m_objFrame.xMin + 12),(m_objFrame.yMin + 12)));
			textBox.xMin = m_objFrame.xMin + 30;
			//Draw Line
			painter->GtDrawLine(midline);
			//Draw Symbol
			m_objSymbol.Draw(painter);
			//Draw Text
			painter->GtDrawText(m_strText,textBox,0);

			return 1;
		}
		//GtPlot2DLegend//////////////////////////////////////////////////
		//!Parent set constructor
		GtPlot2DLegend::GtPlot2DLegend(GtObject* ptrParent)
			:GtObject(ptrParent)
		{
			//!The boolean flag for whether or not the item is visible
			m_blnVisible = true;
			//!the point in canvas of the item
			m_objPos.Zero();
			//!The z render order of the item
			m_intZOrder = 0;
			m_ptrPlot = NULL;
			m_objFrame.Zero();
			m_objBackColor.SetRGB(255,255,255);
			m_objForeColor.SetRGB(0,0,0);
			m_intMaxWidth = 400;
			m_intMaxHeight = 400;
		};
			//!Virtual destructor
		GtPlot2DLegend::~GtPlot2DLegend(void)
		{
			return;
		};
		//!Get the item at index
		GtPlot2DLegendItem* GtPlot2DLegend::AtItem(size_t index)
		{
			if((index >= 0)&&(index < m_arrItems.size()))
			{
				return m_arrItems.at(index);
			}
			//else return null pointer
			return NULL;
		};
		//!count items
		size_t GtPlot2DLegend::CountItems(void)
		{
			return m_arrItems.size();
		};
		//!Add an item
		void GtPlot2DLegend::AddItem(GtPlot2DLegendItem* ptrItem)
		{
			if(ptrItem)
			{
				m_arrItems.push_back(ptrItem);
			}
		};
		//!Delete an item at index
		void GtPlot2DLegend::DeleteItem(size_t index)
		{
			if((index >= 0)&&(index < m_arrItems.size()))
			{
				delete m_arrItems.at(index);
				m_arrItems.erase(index);
			}
			return;
		};
		//!Delete All Items
		void GtPlot2DLegend::DeleteAllItems(void)
		{
			size_t i, numItems;
			numItems = m_arrItems.size();
			if(numItems <= 0){return;};
			for(i = 0; i < numItems; i++)
			{
				delete m_arrItems.at(i);
			}
			m_arrItems.clear();
		};

		void GtPlot2DLegend::UpdateLegend(void)
		{

			int xCursor,yCursor;
			this->DeleteAllItems();//clear the old
			//if the plot is good, get the canvas and items in the canvas and set their properties
			if(!m_ptrPlot){return;};//safety check
			GtPlotCanvas* ptrCanvas = m_ptrPlot->GetCanvasPtr();
			if(!ptrCanvas){return;};

			size_t i, numItems;
			numItems = ptrCanvas->CountItems();
			if(numItems <= 0){return;};//nothing to do

			xCursor = this->m_objFrame.xMin;
			yCursor = this->m_objFrame.yMin;

			for(i = 0; i < numItems; i++)
			{
				GtPlotItem* ptrCurr = ptrCanvas->AtItem(i);
				if(ptrCurr)
				{
					GtPlot2DLegendItem* ptrNew = new GtPlot2DLegendItem();
					if(ptrNew)
					{
						ptrNew->m_strText = ptrCurr->Get_strText();
						ptrNew->m_objSymbol = ptrCurr->Get_objSymbol();
						ptrNew->m_objForeColor = ptrCurr->Get_objForeColor();
						ptrNew->m_objBackColor = ptrCurr->Get_objBackColor();
						ptrNew->m_objFrame.xMin = xCursor;
						ptrNew->m_objFrame.xMax = xCursor + 150;
						ptrNew->m_objFrame.yMin = yCursor;
						ptrNew->m_objFrame.yMax = yCursor + 25;
						this->AddItem(ptrNew);
						//advance the cursor
						yCursor += 25;
						if((yCursor - m_objFrame.yMin)  > m_intMaxHeight)
						{//then new column needed
							xCursor += 150;//new column
							yCursor = m_objFrame.yMin;//start at top
						}
					}//end new legend item

				}//end current 

			}//end loop through items
			GtWidget objTemp;
			objTemp.PostPaint();
		};

		//!Required Draw function for the plot item, must be implemented
		int GtPlot2DLegend::Draw( GtPainter *painter)
		{
			if(!m_blnVisible){return 0;};//turned off
			if(!painter){return 0;};//safety check
			if(CountItems() <= 0){return 0;};//safety check
			painter->Set_objBrush(GtBrush(m_objBackColor));
			painter->Set_objPen(GtPen(m_objForeColor));
			painter->GtFillRect(m_objFrame);
			size_t i, numItems;
			numItems = m_arrItems.size();
			if(numItems <= 0){return 0;};//nothing to do

			for(i = 0; i < numItems; i++)
			{
				GtPlot2DLegendItem* ptrCurr = m_arrItems.at(i);
				if(ptrCurr)
				{
					if((ptrCurr->m_objFrame.xMax <= m_objFrame.xMax)&&
						(ptrCurr->m_objFrame.yMax <= m_objFrame.yMax))
					{//then inside, render
					ptrCurr->Draw(painter);
					}
				}
			}
			return 1;
		};

	};//end namespace GtChart

};//end namespace GT