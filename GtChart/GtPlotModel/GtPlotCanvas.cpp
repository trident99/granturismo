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

#include ".\GtPlotCanvas.h"

namespace GT
{
	namespace GtChart
	{
		//!Parent set constructor
		GtPlotCanvas::GtPlotCanvas(GtObject* ptrParent)
			:GtObject(ptrParent)
		{
			//!The pointer to the plot that this item is attached to
			m_ptrPlot = NULL;
			//!the point in canvas of the item
			m_objFrame.Zero();

		};
		
		//!Virtual destructor
		GtPlotCanvas::~GtPlotCanvas(void)
		{
			m_ptrPlot = NULL;
		};
	
		//!The size of the collection of items
		size_t GtPlotCanvas::CountItems(void)
		{
			return m_arrItems.size();
		};

		//!At the item index
		GtPlotItem* GtPlotCanvas::AtItem(size_t index)
		{
			if((index >= 0)&&(index < m_arrItems.size()))
			{
				return m_arrItems.at(index);
			}
			//else
			return NULL;
		};

		//!Add an Item to the canvas
		void GtPlotCanvas::AddItem(GtPlotItem* ptrItem)
		{
			if(ptrItem)
			{
				m_arrItems.push_back(ptrItem);
				this->ResizeCanvas();
			}
		};

		//!Delete the item at the index
		void GtPlotCanvas::DeleteItem(size_t index)
		{
			if((index >= 0)&&(index < m_arrItems.size()))
			{
				delete m_arrItems.at(index);
				m_arrItems.erase(index);
			}
		};

		//!Delete all items
		void GtPlotCanvas::DeleteAllItems(void)
		{
			size_t i, numItems;
			numItems = m_arrItems.size();
			if(numItems <= 0){return;};//safety check
			for(i = 0; i < numItems;i++)
			{
				delete m_arrItems.at(i);
			}
			m_arrItems.clear();
		};

		void GtPlotCanvas::ResizeCanvas(void)
		{
			GtRectI rectTemp;
			m_objFrame.Zero();
			if(CountItems() <= 0){return;};//safety check

			size_t i, numItems;
			numItems = m_arrItems.size();
	
			//set first one
			GtPlotItem* ptrCurr = m_arrItems.at(0);
			if(ptrCurr)
			{
				m_objFrame = ptrCurr->BoundingCanvasRect();
			}

			for(i = 0; i < numItems; i++)
			{
				ptrCurr = m_arrItems.at(i);
				if(ptrCurr)
				{
					rectTemp = ptrCurr->BoundingCanvasRect();
				}
				if(rectTemp.xMin < m_objFrame.xMin){m_objFrame.xMin = rectTemp.xMin;};
				if(rectTemp.yMin < m_objFrame.yMin){m_objFrame.yMin = rectTemp.yMin;};
				if(rectTemp.xMax > m_objFrame.xMax){m_objFrame.xMax = rectTemp.xMax;};
				if(rectTemp.yMax > m_objFrame.yMax){m_objFrame.yMax = rectTemp.yMax;};
				if(m_objFrame.xMin > m_objFrame.xMax)
				{
					long temp = m_objFrame.xMin;
					m_objFrame.xMin = m_objFrame.xMax;
					m_objFrame.xMax = temp;
				}

				if(m_objFrame.yMin > m_objFrame.yMax)
				{
					long temp = m_objFrame.yMin;
					m_objFrame.yMin = m_objFrame.yMax;
					m_objFrame.yMax = temp;
				}
			}
			//add buffer
			m_objFrame.xMin = 0;
			m_objFrame.yMin = 0;
			m_objFrame.xMax += 100;
			m_objFrame.yMax += 100;
			return;
		};

		//!Required Draw function for the plot item, must be implemented
		int GtPlotCanvas::Draw( GtPainter *painter)
		{
			if(!painter){return 0;};//safety check
			if(CountItems() <= 0){return 0;};//safety check
			painter->Set_objBrush(GtBrush(GtColor(255,255,255)));
			painter->GtFillRect(m_objFrame);
			size_t i, numItems;
			numItems = m_arrItems.size();
	
			for(i = 0; i < numItems; i++)
			{
				GtPlotItem* ptrCurr = m_arrItems.at(i);
				if(ptrCurr)
				{
					ptrCurr->Draw(painter);
				}
			}
			return 0;
		};




	};//end namespace GtChart

};//end namespace GT