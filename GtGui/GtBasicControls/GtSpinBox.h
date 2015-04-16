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

#ifndef GT_SPIN_BOX_H
#define GT_SPIN_BOX_H

#include ".\GtFrame.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtSpinBox : public GtFrame
		{
		public:
			//!Parent set constructor
			GtSpinBox(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtSpinBox(void);

			//MEMBER VARIABLES////////////////////////
			int Get_intMin(void){return m_intMin;};
			void Set_intMin(int min);

			int Get_intMax(void){return m_intMax;};
			void Set_intMax(int max);

 			int Get_intValue(void){return m_intValue;};
			void Set_intValue(int val);

			 int Get_intDelta(void){return m_intDelta;};
			 void Set_intDelta(int val){m_intDelta = val;};
			//SIGNALS/////////////////////////////////
		public:
			//!Signal for Action object changed
			HtlSignal01<int> ValueChanged;//value
			//!Signal for indicating a range change
			HtlSignal02<int,int>  RangeChanged;//min, max


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
			//!The delta to increment or decrement by
			int m_intDelta;

		private:
			//drawing rectangles
			GtRectI m_rectValue;
			GtRectI m_rectValueIncr;
			GtRectI m_rectValueDecr;

		};//end GtSlider class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_SLIDER_H