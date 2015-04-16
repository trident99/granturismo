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

#ifndef GT_PLOT2D_LEGEND_H
#define GT_PLOT2D_LEGEND_H

#include "..\GtChartLibRefs.h"
#include "..\GtPlotModel\GtPlotSymbol.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{
		class GtPlot2DBase;


		class HTL_DLLAPI GtPlot2DLegendItem
		{
		public:
			GtPlot2DLegendItem();	
			GtPlot2DLegendItem(const GtPlot2DLegendItem & rhs);	
			~GtPlot2DLegendItem();
			//!Assignment Operator
			GtPlot2DLegendItem & operator = (const GtPlot2DLegendItem & rhs);
			//!Required Draw function for the plot item, must be implemented
			int Draw( GtPainter *painter = NULL);
		public:
			//name
			std::string m_strText;
			GtColor m_objBackColor;
			GtColor m_objForeColor;
			GtPlotSymbol m_objSymbol;
			GtRectI m_objFrame;

		};//end class def

		//commonly used typedefs
		typedef Htl1DList<GtPlot2DLegendItem*,HtlUnknownType> GtPlot2DLegendItemList;
		typedef HtlListNode<GtPlot2DLegendItem*>* GtPlot2DLegendItemIter;

		class HTL_DLLAPI GtPlot2DLegend : public GtObject
		{
		public:
			//!Parent set constructor
			GtPlot2DLegend(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtPlot2DLegend(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The boolean flag for whether or not the item is visible
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnVisible);
			//!The boolean flag for whether or not the item is visible
			GTOBJECT_MEMVAR_BYVAL(public, int, intMaxHeight);
			//!The boolean flag for whether or not the item is visible
			GTOBJECT_MEMVAR_BYVAL(public, int, intMaxWidth);

			//!the point in canvas of the item
			GTOBJECT_MEMVAR_BYVAL(public, GtPoint3DI, objPos);
			//!The z render order of the item
			GTOBJECT_MEMVAR_BYVAL(public, int, intZOrder);
			//!The z render order of the item
			GTOBJECT_MEMVAR_BYVAL(public, GtPlot2DBase*, ptrPlot);

			//!The rectangle for the item
			GTOBJECT_MEMVAR_BYREF(public, GtRectI, objFrame);
			//!The foreground color
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objForeColor);
			//!The background color
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objBackColor);

			//SIGNALS/////////////////////////////////
		public:			
			//!Signal for action being selected and triggered
			HtlSignal00 Modified;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Get the item at index
			GtPlot2DLegendItem* AtItem(size_t index);
			//!count items
			size_t CountItems(void);



			//!Show the item
			void Show(void){m_blnVisible = true;};
			//!Hide the item
			void Hide(void){m_blnVisible = false;};

			void UpdateLegend(void);

			//!Required Draw function for the plot item, must be implemented
			int Draw( GtPainter *painter = NULL);

		protected:
			GtPlot2DLegendItemList m_arrItems;
			
			//!Add an item
			void AddItem(GtPlot2DLegendItem* ptrItem);
			//!Delete an item at index
			void DeleteItem(size_t index);
			//!Delete All Items
			void DeleteAllItems(void);
			
		};//end GtPlotItem class definition


	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H