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

#ifndef GT_PLOT_ITEM_H
#define GT_PLOT_ITEM_H

#include "..\GtChartLibRefs.h"
#include ".\GtPlotSymbol.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{
		class GtPlot2DBase;
		class GtAxisHorizontal;
		class GtAxisVertical;

		class HTL_DLLAPI GtPlotItem : public GtObject
		{
		public:
			//!Parent set constructor
			GtPlotItem(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtPlotItem(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The boolean flag for whether or not the item is visible
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnVisible);
			//!the point in canvas of the item
			GTOBJECT_MEMVAR_BYVAL(public, GtPoint3DI, objPos);
			//!The z render order of the item
			GTOBJECT_MEMVAR_BYVAL(public, int, intZOrder);
			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, std::string, strText);
			//!The string designator of the item
			GTOBJECT_MEMVAR_BYVAL(public, void*, ptrObj);

			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objForeColor);
			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objBackColor);
			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, GtAxisHorizontal*, ptrXAxis);
			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, GtAxisVertical*, ptrYAxis);
			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, GtPlotSymbol, objSymbol);

			//SIGNALS/////////////////////////////////
		public:			
			//!Signal for action being selected and triggered
			HtlSignal00 Modified;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Show the item
			void Show(void){m_blnVisible = true;};
			//!Hide the item
			void Hide(void){m_blnVisible = false;};

			//!Required Draw function for the plot item, must be implemented
			virtual int Draw( GtPainter *painter = NULL) = 0;
			//!Get the bounding rectangle of the item
			virtual GtRectI & BoundingModelRect(void);
			//!Get the bounding rectangle of the item
			virtual GtRectI & BoundingCanvasRect(void);

		protected:
			GtRectI m_modelRect;
			GtRectI m_canvasRect;

		};//end GtPlotItem class definition

		//commonly used typedefs
		typedef Htl1DList<GtPlotItem*,HtlUnknownType> GtPlotItemList;
		typedef HtlListNode<GtPlotItem*>* GtPlotItemIter;



	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H