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

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtScrollArea.h"

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtScrollArea::GtScrollArea(GtObject* ptrParent)
			:GtFrame(ptrParent)

		{
			m_strType = "GtScrollArea";
			m_ptrTarget = NULL;

			m_objHorizScroll.Set_ptrParent(this);
			m_objVertScroll.Set_ptrParent(this);

			//hook up the scroll bars to the scrolling slots
			m_objHorizScroll.ValueChanged.SlotConnect(this, &GtScrollArea::ScrollHorizontal);
			m_objVertScroll.ValueChanged.SlotConnect(this, &GtScrollArea::ScrollVertical);

		};
			//!Virtual destructor
		GtScrollArea::~GtScrollArea(void)
		{
			m_objHorizScroll.ValueChanged.SlotDisconnect(this);
			m_objVertScroll.ValueChanged.SlotDisconnect(this);
		};
		//Get the pointer to the Horizontal scroll bar
		GtHorizScrollBar * GtScrollArea::GetHorizScrollBar(void)
		{
			return &m_objHorizScroll;
		};
		//Get the pointer to the Vertical scroll bar
		GtVertScrollBar * GtScrollArea::GetVertScrollBar(void)
		{
			return &m_objVertScroll;
		};

		//Set the viewport target
		void GtScrollArea::SetTarget(GtWidget* ptrTarget)
		{
			if(ptrTarget)
			{
				m_ptrTarget = ptrTarget;
				this->UpdateScrollGeometry();
				this->PostPaint();
			}else{
				m_ptrTarget = NULL;
			}

		};
		//Clear the target
		void GtScrollArea::ClearTarget(void)
		{
			m_ptrTarget = NULL;
		};
		//!Scroll Horizontal only
		void GtScrollArea::ScrollHorizontal(int dx)
		{
			int intNewPos, intSMin,intSMax;
			if(!m_ptrTarget){return;};//safety check
			intNewPos = m_objTargetPos.x + dx;
			intSMin = m_objHorizScroll.Get_intMin();
			intSMax = m_objHorizScroll.Get_intMax();
			//bounds check
			if(intNewPos < intSMin)
			{
				//outside lower bound
				return;
			}
			if(intNewPos > intSMax)
			{
				//outside upper bound
				return;
			}
			//otherwise safe to update
			m_objTargetPos.x = intNewPos;
			this->HorizChanged.Emit();
			this->ScrollChanged.Emit(dx,0);
			this->PostPaint();

		};
		//!Scroll Vertical only
		void GtScrollArea::ScrollVertical(int dy)
		{
			int intNewPos, intSMin,intSMax;
			if(!m_ptrTarget){return;};//safety check
			intNewPos = m_objTargetPos.y + dy;
			intSMin = m_objVertScroll.Get_intMin();
			intSMax = m_objVertScroll.Get_intMax();
			//bounds check
			if(intNewPos < intSMin)
			{
				//outside lower bound
				return;
			}
			if(intNewPos > intSMax)
			{
				//outside upper bound
				return;
			}
			//otherwise safe to update
			m_objTargetPos.y = intNewPos;
			this->HorizChanged.Emit();
			this->ScrollChanged.Emit(0,dy);
			this->PostPaint();
		};
		//!Scroll vertical and horizontal;
		void GtScrollArea::Scroll(int dx, int dy)
		{
			bool blnXChanged, blnYChanged;
			int intNewXPos, intNewYPos, intSMin, intSMax;
			if(!m_ptrTarget){return;};//safety check
			
			blnXChanged = true;
			intNewXPos = m_objTargetPos.x + dx;
			intSMin = m_objHorizScroll.Get_intMin();
			intSMax = m_objHorizScroll.Get_intMax();
			//bounds check
			if(intNewXPos < intSMin)
			{
				//outside lower bound
				blnXChanged = false;
			}
			if(intNewXPos > intSMax)
			{
				//outside upper bound
				blnXChanged = false;
			}
			//otherwise safe to update
			if(blnXChanged)
			{
				m_objTargetPos.x = intNewXPos;
				this->HorizChanged.Emit();
			}

			blnYChanged = true;
			intNewYPos = m_objTargetPos.y + dy;
			intSMin = m_objVertScroll.Get_intMin();
			intSMax = m_objVertScroll.Get_intMax();
			//bounds check
			if(intNewYPos < intSMin)
			{
				//outside lower bound
				blnYChanged = false;
			}
			if(intNewYPos > intSMax)
			{
				//outside upper bound
				blnYChanged = false;
			}
			//otherwise safe to update
			if(blnYChanged)
			{
				m_objTargetPos.y = intNewYPos;
				this->HorizChanged.Emit();
			}
			if(blnXChanged || blnYChanged)
			{
				this->ScrollChanged.Emit(dx,dy);
				this->PostPaint();
			}
		};

		void GtScrollArea::Set_objFrame(GtRectI & frame)
		{
			GtWidget::Set_objFrame(frame);
			this->UpdateScrollGeometry();	
		};

		void GtScrollArea::UpdateScrollGeometry(void)
		{

			//set up the scroll bars
			GtRectI rectVert, rectHoriz, rectTarget;

			rectVert = m_objFrame;
			rectVert.xMin = rectVert.xMax - 25;
			rectVert.yMax = rectVert.yMax - 25;
			m_objVertScroll.Set_objFrame(rectVert);

			rectHoriz = m_objFrame;
			rectHoriz.yMin = rectHoriz.yMax - 25;
			rectHoriz.xMax = rectHoriz.xMax - 25;
			m_objHorizScroll.Set_objFrame(rectHoriz);
			//set up the viewport
			m_objViewFrame = m_objFrame;
			m_objViewFrame.xMax = rectVert.xMin;
			m_objViewFrame.yMax = rectHoriz.yMin;

			//set the ranges for the scroll bars
			if(!m_ptrTarget){return;}
			rectTarget = m_ptrTarget->Get_objFrame();
			m_objVertScroll.Set_intMin(0);
			int intVertMax = rectTarget.Height() - m_objViewFrame.Height();
			if(intVertMax <= 0){intVertMax = 0;};
			m_objVertScroll.Set_intMax(intVertMax);

			m_objHorizScroll.Set_intMin(0);
			int intHorizMax = rectTarget.Width() - m_objViewFrame.Width();
			if(intHorizMax <= 0){intHorizMax = 0;};
			m_objHorizScroll.Set_intMax(intHorizMax);

			m_objVertScroll.Set_intValue(0);
			m_objHorizScroll.Set_intValue(0);
			this->PostPaint();
			return;
		};

		//!Gets the event manager pointer
		GtPoint3DI GtScrollArea::RequestOffset(void)
		{
			m_objOffset.Zero();
			if (!m_ptrParent){ return m_objOffset; };
			//need to retrieve the root widget, call the parent
			GtWidget* ptrCast = dynamic_cast<GtWidget*>(m_ptrParent);
			if (ptrCast)
			{
				GtPoint3DI pos = ptrCast->RequestOffset();
				GtRectI frameParent = ptrCast->Get_objFrame();

				m_objOffset.x = pos.x + frameParent.xMin - m_objHorizScroll.Get_intValue();
				m_objOffset.y = pos.y + frameParent.yMin - m_objVertScroll.Get_intValue();
			}
			return m_objOffset;

		};



		//!Tests and sets the focus widget based on the cursor location provided
		GtWidget* GtScrollArea::SetFocusWidget(GtPoint3DI & pos)
		{
			 //quick exclusion check
			 if(!m_objFrame.Contains(pos))
			 {
				 m_blnFocus = false;
				 return NULL;
			 };//point not in frame
			 //Otherwise point inside frame,
			 //check scroll bars
			 GtRectI rectVert, rectHoriz;
			 rectVert = m_objVertScroll.Get_objFrame();
			 rectHoriz = m_objHorizScroll.Get_objFrame();

			 if(rectVert.Contains(pos))
			 {
				m_objVertScroll.Set_blnFocus(true);
				return &m_objVertScroll;
			 }else{
				m_objVertScroll.Set_blnFocus(false);
			 }
			 if(rectHoriz.Contains(pos))
			 {
				m_objHorizScroll.Set_blnFocus(true);
				return &m_objHorizScroll;
			 }else{
				 m_objHorizScroll.Set_blnFocus(false);
			 }
			//check the target
			 if(m_ptrTarget)
			 {
				 GtWidget* ptrTest = NULL;
				 ptrTest = m_ptrTarget->SetFocusWidget(pos);
				 if(ptrTest)
				 {
					 return ptrTest;
				 }
			 }
			 //otherwise scroll area
			 return this;
		};
		//!Custom Event Processing
		int GtScrollArea::HandleEvent(GtEvent * ptrEvent)
		{
			return 0;
		};
		//!Custom Widget Painting
		int GtScrollArea::OnPaint(GtPainter * painter)
		{

			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen oldPen;
			GtBrush oldBrush;
			HDC hdcOld, hdcTarget;
			HWND winIDOld;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			hdcOld = painter->Get_ptrHDC();
			winIDOld = painter->Get_winID();

			GtFrame::OnPaint(painter);

			//render the target window
			if(m_ptrTarget)
			{
				GtCanvas scrollCanvas;
				scrollCanvas.m_view = m_objViewFrame;
				scrollCanvas.m_frame = m_ptrTarget->Get_objFrame();
				scrollCanvas.m_delta.x = m_objHorizScroll.Get_intValue();
				scrollCanvas.m_delta.y = m_objVertScroll.Get_intValue();

				scrollCanvas.m_dest.x = m_objViewFrame.xMin;
				scrollCanvas.m_dest.y = m_objViewFrame.yMin;

				painter->GtStartCanvas(scrollCanvas);
				m_ptrTarget->OnPaint(painter);
				painter->GtEndCanvas();
			}

			//draw the scroll bars
			m_objVertScroll.OnPaint(painter);
			m_objHorizScroll.OnPaint(painter);

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	

	};//end namespace GtGui

};//end namespace GT