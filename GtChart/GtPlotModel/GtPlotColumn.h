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

#ifndef GT_PLOT_Column_H
#define GT_PLOT_Column_H

#include ".\GtPlotItem.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtChart
	{
		class GtPlot2DBase;
		class GtAxisHorizontal;
		class GtAxisVertical;

		class HTL_DLLAPI GtColumnItem
		{
		public:
			GtColumnItem();	
			~GtColumnItem();
			//!Assignment Operator
			GtColumnItem & operator = (const GtColumnItem & rhs);

		public:
			double m_dblVal;
			float m_sngPos;
			GtColor m_objColor;
			std::wstring m_strName;
			GtRectI m_objRect;
		};

		class HTL_DLLAPI  GtPlotColumn: public GtPlotItem
		{
		public:
			//!Parent set constructor
			GtPlotColumn(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtPlotColumn(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtPlotColumn & operator = (GtPlotColumn & rhs);

			//!Clears the polyline of all points
			inline void Clear(void);
			//!Gets the number of points
			inline size_t Size(void);
			//!Returns the point at index
			inline GtColumnItem & At(size_t index);
			//!Adds the point3d the the back of the coordinates
			inline void PushBack(GtColumnItem & objNewPoint);
			//!Round the polyline coordinates to number of decimals
			inline void Round(int intNumDecimals);


			//SIGNALS/////////////////////////////////
		public:			
			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Required Draw function for the plot item, must be implemented
			virtual int Draw( GtPainter *painter = NULL);
			//!Get the bounding rectangle of the item
			virtual GtRectI & BoundingModelRect(void);
			//!Get the bounding rectangle of the item
			virtual GtRectI & BoundingCanvasRect(void);

			StlVector<GtColumnItem, HtlUnknownType> m_arrObjPoints;
			std::string m_strObjectName;
		private:
			GtColumnItem m_objNullPoint;

		};//end GtPlotItem class definition

	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H