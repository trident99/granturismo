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

#ifndef GT_PLOT_CANVAS_H
#define GT_PLOT_CANVAS_H

#include ".\GtPlotItem.h"

using namespace HTL;
using namespace GT::GtCore;
//using namespace GT::GtGui;

namespace GT
{
	namespace GtChart
	{
		class GtPlot2DBase;

		class HTL_DLLAPI GtPlotCanvas : public GtObject
		{
		public:
			//!Parent set constructor
			GtPlotCanvas(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtPlotCanvas(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The pointer to the plot that this item is attached to
			GTOBJECT_MEMVAR_BYVAL(public, GtPlot2DBase*, ptrPlot);
			//!The frame of the Canvas
			GTOBJECT_MEMVAR_BYVAL(public, GtRectI, objFrame);
			//SIGNALS/////////////////////////////////
		public:			
			//!Signal for action being selected and triggered
			HtlSignal00 Resized;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!The size of the collection of items
			size_t CountItems(void);
			//!At the item index
			GtPlotItem* AtItem(size_t index);
			//!Add an Item to the canvas
			void AddItem(GtPlotItem* ptrItem);
			//!Delete the item at the index
			void DeleteItem(size_t index);
			//!Delete all items
			void DeleteAllItems(void);

			void ResizeCanvas(void);
			//!Required Draw function for the plot item, must be implemented
			virtual int Draw( GtPainter *painter = NULL);

		protected:
			GtPlotItemList m_arrItems;
		};//end GtPlotItem class definition

	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H