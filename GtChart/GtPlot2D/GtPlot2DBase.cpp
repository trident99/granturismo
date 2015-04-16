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

#include ".\GtPlot2DBase.h"
#include ".\GtPlot2DLegend.h"
#include "..\GtPlotModel\GtPlotCanvas.h"
#include "..\GtPlotAxisScale\GtAxisHorizontal.h"
#include "..\GtPlotAxisScale\GtAxisVertical.h"

namespace GT
{
	namespace GtChart
	{
			//!Parent set constructor
		GtPlot2DBase::GtPlot2DBase(GtObject* ptrParent)
			:GtWidget(ptrParent)
		{
			m_blnShowGridXMajor = true;
			m_blnShowGridXMinor = false;
			m_blnShowGridYMajor = true;
			m_blnShowGridYMinor = false;

			m_ptrCanvas = new GtPlotCanvas(this);
			m_ptrLegend = new GtPlot2DLegend(this);
			if(m_ptrLegend)
			{
				m_ptrLegend->Set_ptrPlot(this);
			}
		};
			//!Virtual destructor
		GtPlot2DBase::~GtPlot2DBase(void)
		{

	
		};
	
		//HORIZONTAL AXIS ITEMS
		//!The size of the collection of items
		size_t GtPlot2DBase::CountHorizAxis(void)
		{
			return m_arrHorizAxis.size();
		};
		//!At the item index
		GtAxisHorizontal* GtPlot2DBase::AtHorizAxis(size_t index)
		{
			if((index >= 0)&&(index < m_arrHorizAxis.size()))
			{
				return m_arrHorizAxis.at(index);
			}
			//otherwise illegal index
			return NULL;
		};
		//!Add an Item to the canvas
		void GtPlot2DBase::AddHorizAxis(GtAxisHorizontal* ptrItem)
		{
			if(ptrItem)
			{
				m_arrHorizAxis.push_back(ptrItem);
			}
		};
		//!Delete the item at the index
		void GtPlot2DBase::DeleteHorizAxis(size_t index)
		{
			if((index >= 0)&&(index < m_arrHorizAxis.size()))
			{
				delete m_arrHorizAxis.at(index);
				m_arrHorizAxis.erase(index);
			}	
		};
		//!Delete all items
		void GtPlot2DBase::DeleteAllHorizAxis(void)
		{
			size_t i, numItems;
			numItems = m_arrHorizAxis.size();
			if(numItems <= 0){return;};
			for(i = 0; i < numItems;i++)
			{
				delete m_arrHorizAxis.at(i);
			}
			m_arrHorizAxis.clear();
		};

		//VERTICAL AXIS ITEMS
		//!The size of the collection of items
		size_t GtPlot2DBase::CountVertAxis(void)
		{
			return m_arrVertAxis.size();
		};
		//!At the item index
		GtAxisVertical* GtPlot2DBase::AtVertAxis(size_t index)
		{
			if((index >= 0)&&(index < m_arrVertAxis.size()))
			{
				return m_arrVertAxis.at(index);
			}
			//otherwise illegal index
			return NULL;
		};
		//!Add an Item to the canvas
		void GtPlot2DBase::AddVertAxis(GtAxisVertical* ptrItem)
		{
			if(ptrItem)
			{
				m_arrVertAxis.push_back(ptrItem);
			}
		};
		//!Delete the item at the index
		void GtPlot2DBase::DeleteVertAxis(size_t index)
		{
			if((index >= 0)&&(index < m_arrVertAxis.size()))
			{
				delete m_arrVertAxis.at(index);
				m_arrVertAxis.erase(index);
			}	
		};
		//!Delete all items
		void GtPlot2DBase::DeleteAllVertAxis(void)
		{
			size_t i, numItems;
			numItems = m_arrVertAxis.size();
			if(numItems <= 0){return;};
			for(i = 0; i < numItems;i++)
			{
				delete m_arrVertAxis.at(i);
			}
			m_arrVertAxis.clear();
		};

		//CANVAS ACCESSOR
		GtPlotCanvas* GtPlot2DBase::GetCanvasPtr(void)
		{
			if(m_ptrCanvas)
			{
				return m_ptrCanvas;
			}else{
				return NULL;
			}
		};
		//LEGEND ACCESSOR
		GtPlot2DLegend* GtPlot2DBase::GetLegendPtr(void)
		{
			if(m_ptrLegend)
			{
				return m_ptrLegend;
			}else{
				return NULL;
			}
		};
		//GTWIDGET INHERITED FUNCTIONS
		//!Custom Event Processing
		int GtPlot2DBase::HandleEvent(GtEvent * ptrEvent)
		{
			return 0;
		};
		//!Custom Widget Painting
		int GtPlot2DBase::OnPaint(GtPainter * painter)
		{
			if(!painter){return 0;};
			painter->Set_objBrush(GtBrush(GtColor(255,255,255)));
			painter->Set_objPen(GtPen(GtColor(0,0,0)));
			painter->GtDrawFrame(m_objFrame);
			//paint the axis first, then the scatter plot
			size_t i , numItems;
			numItems = m_arrHorizAxis.size();
			for(i = 0; i < numItems; i++)
			{
				GtAxisHorizontal* ptrCurr = this->AtHorizAxis(i);
				if(ptrCurr)
				{
					ptrCurr->Draw(painter);
				}
			}
			
			numItems = m_arrVertAxis.size();
			for(i = 0; i < numItems; i++)
			{
				GtAxisVertical* ptrCurr = this->AtVertAxis(i);
				if(ptrCurr)
				{
					ptrCurr->Draw(painter);
				}
			}

			return 1;
		};

		//!Draw the grid values on the plot
		int GtPlot2DBase::DrawGrid(GtPainter * painter)
		{
			if(!painter){return 0;};
			painter->Set_objBrush(GtBrush(GtColor(255,255,255)));
			painter->Set_objPen(GtPen(GtColor(0,0,0)));
			painter->GtDrawFrame(m_objFrame);
			//paint the axis first, then the scatter plot
			size_t numItems;
			numItems = m_arrHorizAxis.size();
			if(numItems > 0)
			{
				if(this->m_blnShowGridXMinor)
				{
					m_arrHorizAxis.at(0)->DrawMinorGrid(m_objFrame,painter);
				}
				if(this->m_blnShowGridXMajor)
				{
					m_arrHorizAxis.at(0)->DrawMajorGrid(m_objFrame,painter);
				};
			}
						
			
			numItems = m_arrVertAxis.size();
			if(numItems > 0)
			{
				if(this->m_blnShowGridYMinor)
				{
					m_arrVertAxis.at(0)->DrawMinorGrid(m_objFrame,painter);
				}
				if(this->m_blnShowGridYMajor)
				{
					m_arrVertAxis.at(0)->DrawMajorGrid(m_objFrame,painter);
				};
			}
			return 1;
		};

		//!Draw the legend on the plot
		int GtPlot2DBase::DrawLegend(GtPainter * painter)
		{
			if(!painter){return 0;};

			if(m_ptrLegend)
			{
				return m_ptrLegend->Draw(painter);
			}
			return 0;
		};

	};//end namespace GtChart

};//end namespace GT