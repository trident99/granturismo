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

#ifndef GT_SCALE_LOGARITHM_H
#define GT_SCALE_LOGARITHM_H

#include ".\GtScaleBase.h"
using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{

		class HTL_DLLAPI GtScaleLogarithm : public GtScaleBase
		{
		public:
			//!Parent set constructor
			GtScaleLogarithm(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtScaleLogarithm(void);

			//!The upper bound of the scale
			GTOBJECT_MEMVAR_BYVAL(public, GtPoint3DF, pt0);
						//!The upper bound of the scale
			GTOBJECT_MEMVAR_BYVAL(public, GtPoint3DF, pt1);

			//MEMBER VARIABLES////////////////////////
			//SIGNALS/////////////////////////////////
		public:			
			//MEMBER FUNCTIONS////////////////////////
		public:

			virtual void ModelToViewPt(float & ptModel, float & ptView);

			virtual void ViewToModelPt(float & ptView, float & ptModel);

			virtual void Initialize(void);
		protected:


		};//end GtPlotItem class definition


	}//end namespace GtChart
}//end namespace GT
#endif //GT_SCALE_BASE_H