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

#ifndef GT_SCROLL_AREA_H
#define GT_SCROLL_AREA_H

#include ".\GtFrame.h"
#include ".\GtHorizScrollBar.h"
#include ".\GtVertScrollBar.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		enum GtScrollBarPolicy
		{
			//QAbstractScrollArea shows a scroll bar when the content is too large to fit and not otherwise. This is the default.
			ScrollBarAsNeeded =	0,
			//QAbstractScrollArea never shows a scroll bar.
			ScrollBarAlwaysOff = 1,	
			//QAbstractScrollArea always shows a scroll bar.
			ScrollBarAlwaysOn = 2	
		};


		class HTL_DLLAPI GtScrollArea : public GtFrame
		{
		public:
			//!Parent set constructor
			GtScrollArea(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtScrollArea(void);

			//MEMBER VARIABLES////////////////////////
			//!The horizontal scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, GtScrollBarPolicy, horizScrollPolicy);
			//!The vertical scroll bar policy
			GTOBJECT_MEMVAR_BYVAL(public, GtScrollBarPolicy, vertScrollPolicy);
			//!The maximum size of the viewport
			GTOBJECT_MEMVAR_BYREF(public, GtSizeI, viewMaxSize);
			//SIGNALS/////////////////////////////////
		public:
			//!Signal for Action object changed
			HtlSignal00 HorizChanged;//value
			//!Signal for Action object changed
			HtlSignal00 VertChanged;//value
			//!Signal for indicating a scroll change
			HtlSignal02<int,int>  ScrollChanged;//dx, dy
			//!Signal for indicating a range change
			HtlSignal02<int,int>  RangeChanged;//min, max
			//MEMBER FUNCTIONS////////////////////////
		public:
			//Get the pointer to the Horizontal scroll bar
			GtHorizScrollBar * GetHorizScrollBar(void);
			//Get the pointer to the Vertical scroll bar
			GtVertScrollBar * GetVertScrollBar(void);
			//Set the viewport target
			void SetTarget(GtWidget* ptrTarget);
			//Clear the target
			void ClearTarget(void);
			//!Scroll Horizontal only
			void ScrollHorizontal(int dx);
			//!Scroll Vertical only
			void ScrollVertical(int dy);
			//!Scroll vertical and horizontal;
			void Scroll(int dx, int dy);

			//!GetRanges
			int GetScrollHorizMin(void){return m_objHorizScroll.Get_intMin();};
			int GetScrollHorizMax(void){return m_objHorizScroll.Get_intMax();};
			int GetScrollVertMin(void){return m_objVertScroll.Get_intMin();};
			int GetScrollVertMax(void){return m_objVertScroll.Get_intMax();};

		public:
			//!Gets the event manager pointer
			virtual GtPoint3DI RequestOffset(void);
			//!Tests and sets the focus widget based on the cursor location provided
			virtual GtWidget* SetFocusWidget(GtPoint3DI & pos);

			virtual void Set_objFrame(GtRectI & frame);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:
			//!The Horizontal Scroll Bar
			GtHorizScrollBar m_objHorizScroll;
			//!The Vertical Scroll Bar
			GtVertScrollBar m_objVertScroll;
			//!The Target Widget
			GtWidget* m_ptrTarget;
			//!The position of the target top left point that is visible
			GtPoint3DI m_objTargetPos;

			void UpdateScrollGeometry(void);

		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_SCROLL_AREA_H




/*We give a simple example, in which we have implemented a scroll area that can scroll any QWidget.
We make the widget a child of the viewport; this way, we do not have to calculate which part of the
widget to draw but can simply move the widget with QWidget::move().
When the area contents or the viewport size changes, we do the following:

    QSize areaSize = viewport()->size();
    QSize  widgetSize = widget->size();

    verticalScrollBar()->setPageStep(areaSize.height());
    horizontalScrollBar()->setPageStep(areaSize.width());
    verticalScrollBar()->setRange(0, widgetSize.height() - areaSize.height());
    horizontalScrollBar()->setRange(0, widgetSize.width() - areaSize.width());
    updateWidgetPosition();

When the scroll bars change value, we need to update the widget position, i.e.,
find the part of the widget that is to be drawn in the viewport:

    int hvalue = horizontalScrollBar()->value();
    int vvalue = verticalScrollBar()->value();
    QPoint topLeft = viewport()->rect().topLeft();

    widget->move(topLeft.x() - hvalue, topLeft.y() - vvalue);

In order to track scroll bar movements, reimplement the virtual function scrollContentsBy().
In order to fine-tune scrolling behavior, connect to a scroll bar's QAbstractSlider::actionTriggered()
signal and adjust the QAbstractSlider::sliderPosition as you wish.*/