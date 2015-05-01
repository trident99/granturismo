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

#include ".\GtPlot2DColumn.h"
#include "..\GtPlotModel\GtPlotCanvas.h"
#include "..\GtPlotModel\GtPlotItem.h"
#include "..\GtPlotModel\GtPlotCurve.h"
#include "..\GtPlotAxisScale\GtAxisHorizontal.h"
#include "..\GtPlotAxisScale\GtAxisVertical.h"

namespace GT
{
	namespace GtChart
	{
			//!Parent set constructor
		GtPlot2DColumn::GtPlot2DColumn(GtObject* ptrParent)
			:GtPlot2DBase(ptrParent)
		{

		};
			//!Virtual destructor
		GtPlot2DColumn::~GtPlot2DColumn(void)
		{
	
		};
		//GTWIDGET INHERITED FUNCTIONS
		//!Custom Event Processing
		int GtPlot2DColumn::HandleEvent(GtEvent * ptrEvent)
		{
			return 0;
		};
		//!Custom Widget Painting
		int GtPlot2DColumn::OnPaint(GtPainter * painter)
		{
			if(!painter){return 0;};
			//paint the axis first
			GtPlot2DBase::OnPaint(painter);

			//now paint the scatter plot contents
			//get the canvas
			if(!m_ptrCanvas){return 0;}//no canvas
			size_t numItems;
			numItems = m_ptrCanvas->CountItems();
			if(numItems <= 0){return 0;};//nothing to render
			if(CountHorizAxis() <= 0){return 0;};//nothing to render
			if(CountVertAxis() <= 0){return 0;};//nothing to render		

			m_drawCanvas.m_view = m_objFrame;
			//m_ptrCanvas->ResizeCanvas();
			m_drawCanvas.m_frame = m_ptrCanvas->Get_objFrame();

			//rectify so canvas includes all of real frame
			if(m_drawCanvas.m_view.xMin < m_drawCanvas.m_frame.xMin){m_drawCanvas.m_frame.xMin = m_drawCanvas.m_view.xMin;};
			if(m_drawCanvas.m_view.yMin < m_drawCanvas.m_frame.yMin){m_drawCanvas.m_frame.yMin = m_drawCanvas.m_view.yMin;};
			if(m_drawCanvas.m_view.xMax > m_drawCanvas.m_frame.xMax){m_drawCanvas.m_frame.xMax = m_drawCanvas.m_view.xMax;};
			if(m_drawCanvas.m_view.yMax > m_drawCanvas.m_frame.yMax){m_drawCanvas.m_frame.yMax = m_drawCanvas.m_view.yMax;};
			m_drawCanvas.m_frame.xMax += 100; //100 pixel buffer
			m_drawCanvas.m_frame.yMax += 100; //100 pixel buffer

			m_ptrCanvas->Set_objFrame(m_drawCanvas.m_frame);
			//get upper left point (xmin, ymax) of the displayed area for the canvas
			float top = 0;
			float left = 0;
			//use the first axis for each.
			GtAxisHorizontal* ptrXAxis = this->AtHorizAxis(0);
			if(ptrXAxis)
			{
				float modLeft = ptrXAxis->Get_sngLB();
				ptrXAxis->ModelToViewPt(modLeft,left);
			};
			GtAxisVertical* ptrYAxis = this->AtVertAxis(0);
			if(ptrYAxis)
			{
				float modTop = ptrYAxis->Get_sngUB();
				ptrYAxis->ModelToViewPt(modTop,top);
			};

			m_drawCanvas.m_delta.x = (long)left;
			m_drawCanvas.m_delta.y = (long)top;
			///the destination view frame upper left
			m_drawCanvas.m_dest.x = m_objFrame.xMin;
			m_drawCanvas.m_dest.y = m_objFrame.yMin;
			//paint the actual canvas
			painter->GtStartCanvas(&m_drawCanvas);
			m_ptrCanvas->Draw(painter);
			painter->GtEndCanvas();
			//now draw the grid overlay
			this->m_blnShowGridXMajor = false;
			this->m_blnShowGridXMinor = false;
			this->DrawGrid(painter);
			return 1;
		};

	};//end namespace GtChart

};//end namespace GT