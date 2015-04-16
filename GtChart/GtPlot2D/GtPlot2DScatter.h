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

#ifndef GT_PLOT_2DSCATTER_H
#define GT_PLOT_2DSCATTER_H

#include ".\GtPlot2DBase.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{


		class HTL_DLLAPI GtPlot2DScatter : public GtPlot2DBase
		{
		public:
			//!Parent set constructor
			GtPlot2DScatter(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtPlot2DScatter(void);

			//MEMBER VARIABLES////////////////////////
			//SIGNALS/////////////////////////////////
		public:			
			//MEMBER FUNCTIONS////////////////////////
		public:
			//GTWIDGET INHERITED FUNCTIONS
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);

		protected:

		};//end GtPlotItem class definition

		//commonly used typedefs
		//typedef Htl1DList<GtPlotItem*,HtlUnknownType> GtPlotItemList;
		//typedef HtlListNode<GtPlotItem*>* GtPlotItemIter;



	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H