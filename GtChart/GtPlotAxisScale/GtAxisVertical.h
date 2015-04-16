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

#ifndef GT_AXIS_VERTICAL_H
#define GT_AXIS_VERTICAL_H

#include ".\GtScaleBase.h"
#include "..\GtPlotModel\GtPlotItem.h"
using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{

		class HTL_DLLAPI GtAxisVertical : public GtPlotItem
		{
		public:
			//!Parent set constructor
			GtAxisVertical(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtAxisVertical(void);

			//MEMBER VARIABLES////////////////////////
//!The lower bound for the scale
			GTOBJECT_MEMVAR_BYVAL(public, float, sngLB);
			//!The upper bound for the scale
			GTOBJECT_MEMVAR_BYVAL(public, float, sngUB);
			//!The delta major
			GTOBJECT_MEMVAR_BYVAL(public, float, sngMajor);
			//!The delta minor
			GTOBJECT_MEMVAR_BYVAL(public, float, sngMinor);
			//!The frame for the scale
			GTOBJECT_MEMVAR_BYVAL(public, GtRectI, objFrame);
			//!The the actual scale object
			GTOBJECT_MEMVAR_BYVAL(public, GtScaleBase* , ptrScale);

			//!The number printing format (C++ style printf format)
			GTOBJECT_MEMVAR_BYREF(public, std::string, strFormat);
			//!The label for the axis
			GTOBJECT_MEMVAR_BYREF(public, std::wstring, strLabel);
			//SIGNALS/////////////////////////////////
		public:			
			//MEMBER FUNCTIONS////////////////////////
		public:

			void ModelToViewPt(float & ptModel, float & ptView);
			void ModelToViewPt(long & ptModel, long & ptView);

			void ViewToModelPt(float & ptView, float & ptModel);
			void ViewToModelPt(long & ptView, long & ptModel);

			void Update(void);
			//!Required Draw function for the plot item, must be implemented
			virtual int Draw( GtPainter *painter = NULL);
			int DrawMajorGrid(GtRectI & frame, GtPainter * painter = NULL);
			int DrawMinorGrid(GtRectI & frame, GtPainter * painter = NULL);

			//!Get the bounding rectangle of the item
			virtual GtRectI BoundingRect(void);
		protected:


		};//end GtPlotItem class definition


	}//end namespace GtChart
}//end namespace GT
#endif //GT_SCALE_BASE_H