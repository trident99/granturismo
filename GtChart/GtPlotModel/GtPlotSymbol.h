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

#ifndef GT_PLOT_SYMBOL_H
#define GT_PLOT_SYMBOL_H

#include "..\GtChartLibRefs.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{


		enum GtSymbolType
		{
			SymbolPoint = 0,
			SymbolPlus,
			SymbolCross,
			SymbolTriangle,
			SymbolRect,
			SymbolDiamond,
			SymbolStar
		};


		class HTL_DLLAPI GtPlotSymbol : public GtObject
		{
		public:
			//!Parent set constructor
			GtPlotSymbol(GtObject* ptrParent = NULL);
			GtPlotSymbol(const GtPlotSymbol & rhs);
			//!Virtual destructor
			virtual ~GtPlotSymbol(void);
			//!Assignment Operator
			GtPlotSymbol & operator = (const GtPlotSymbol & rhs);
			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The pointer to the plot that this item is attached to
			GTOBJECT_MEMVAR_BYVAL(public, int, intSize);
			//!The pointer to the plot that this item is attached to
			GTOBJECT_MEMVAR_BYVAL(public, GtSymbolType, objSymType);
			//!The pointer to the plot that this item is attached to
			GTOBJECT_MEMVAR_BYREF(public, GtPoint3DI, objCanvasPos);
			//!The pointer to the plot that this item is attached to
			GTOBJECT_MEMVAR_BYREF(public, GtPoint3DF, objModelPos);

			//SIGNALS/////////////////////////////////
		public:			
			//!Signal for action being selected and triggered
			//HtlSignal00 Modified;

			//MEMBER FUNCTIONS////////////////////////
		public:

			//!Required Draw function for the plot item, must be implemented
			virtual int Draw( GtPainter *painter = NULL);

		protected:


		};//end GtPlotItem class definition

	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H