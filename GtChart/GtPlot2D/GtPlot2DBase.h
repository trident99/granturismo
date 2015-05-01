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

#ifndef GT_PLOT_2DBASE_H
#define GT_PLOT_2DBASE_H

#include "..\GtChartLibRefs.h"


using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{
		class GtPlotCanvas;
		class GtAxisHorizontal;
		class GtAxisVertical;
		class GtPlot2DLegend;


		class HTL_DLLAPI GtPlot2DBase : public GtWidget
		{
		public:
			//!Parent set constructor
			GtPlot2DBase(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtPlot2DBase(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!Boolean flag for showing Grid X Major Lines
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowGridXMajor);
			//!Boolean flag for showing Grid X Minor Lines
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowGridXMinor);
			//!Boolean flag for showing Grid Y Major Lines
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowGridYMajor);
			//!Boolean flag for showing Grid Y Minor Lines
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnShowGridYMinor);

			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, std::string, strType);
			//!The string designator of the item
			GTOBJECT_MEMVAR_BYREF(public, std::string, strTitle);

			//SIGNALS/////////////////////////////////
		public:			
			//!Signal for action being selected and triggered
			HtlSignal00 Modified;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//HORIZONTAL AXIS ITEMS
			//!The size of the collection of items
			size_t CountHorizAxis(void);
			//!At the item index
			GtAxisHorizontal* AtHorizAxis(size_t index);
			//!Add an Item to the canvas
			void AddHorizAxis(GtAxisHorizontal* ptrItem);
			//!Delete the item at the index
			void DeleteHorizAxis(size_t index);
			//!Delete all items
			void DeleteAllHorizAxis(void);

			//VERTICAL AXIS ITEMS
			//!The size of the collection of items
			size_t CountVertAxis(void);
			//!At the item index
			GtAxisVertical* AtVertAxis(size_t index);
			//!Add an Item to the canvas
			void AddVertAxis(GtAxisVertical* ptrItem);
			//!Delete the item at the index
			void DeleteVertAxis(size_t index);
			//!Delete all items
			void DeleteAllVertAxis(void);

			//CANVAS ACCESSOR
			GtPlotCanvas* GetCanvasPtr(void);
			//LEGEND ACCESSOR
			GtPlot2DLegend* GetLegendPtr(void);

			//GTWIDGET INHERITED FUNCTIONS
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);
			//!update the plot drawing
			void Replot(void);

		protected:
			//!Draw the grid values on the plot
			int DrawGrid(GtPainter * painter = NULL);
			//!Draw the legend on the plot
			int DrawLegend(GtPainter * painter = NULL);
			//!The plot canvas for the plot
			GtPlotCanvas* m_ptrCanvas;
			GtCanvas m_drawCanvas;
			GtPlot2DLegend* m_ptrLegend;
			Htl1DList<GtAxisHorizontal*,HtlUnknownType> m_arrHorizAxis;

			Htl1DList<GtAxisVertical*,HtlUnknownType> m_arrVertAxis;


		};//end GtPlotItem class definition

		//commonly used typedefs
		//typedef Htl1DList<GtPlotItem*,HtlUnknownType> GtPlotItemList;
		//typedef HtlListNode<GtPlotItem*>* GtPlotItemIter;



	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H