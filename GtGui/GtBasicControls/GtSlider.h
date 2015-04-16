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

#ifndef GT_SLIDER_H
#define GT_SLIDER_H

#include "..\GtGuiLibRefs.h"
#include <modGtGraphic.h>
#include <modGtGeometry.h>

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtSlider : public GtWidget
		{
		public:
			//!Parent set constructor
			GtSlider(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtSlider(void);

			//MEMBER VARIABLES////////////////////////
			int Get_intMin(void){return m_intMin;};
			void Set_intMin(int min);

			int Get_intMax(void){return m_intMax;};
			void Set_intMax(int max);

 			int Get_intValue(void){return m_intValue;};
			void Set_intValue(int val);

			//SIGNALS/////////////////////////////////
		public:
			//!Signal for Action object changed
			HtlSignal01<int> ValueChanged;//value
			//!Signal for indicating a range change
			HtlSignal02<int,int>  RangeChanged;//min, max
			//!Signal for Slider pressed with left mouse button
			HtlSignal00 SliderPressed;
			//!Signal for Slider released from left mouse button
			HtlSignal00 SliderReleased;


			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Boolean check to see if slider at maximum
			bool IsAtMinimum(void);
			//!Boolean check to see if slider at minimum
			bool IsAtMaximum(void);
			//!Set the minimum and maximum range settings
			void SetRange(int min, int max);
			//!Increment the position by delta
			void Increment(int idelta);
			//!Decrement the position by delta
			void Decrement(int idelta);


			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);

		protected:
			//!The slider minimum value
			int m_intMin;
			//!The slider maximum value
			int m_intMax;
			//!The current slider value
			int m_intValue;

		private:
			GtRectI m_rectSlider;
			GtPoint3DI m_sliderPos;
			bool m_blnSliderGrab;

		};//end GtSlider class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_SLIDER_H