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

#ifndef GT_PLOT_PIE_H
#define GT_PLOT_PIE_H

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

		class HTL_DLLAPI GtPieItem
		{
		public:
			GtPieItem();	
			
			GtPieItem(const GtPieItem & rhs);
			~GtPieItem();
			//!Assignment Operator
			GtPieItem & operator = (const GtPieItem & rhs);

		public:
			double m_dblVal;
			double m_dblPercent;
			float m_sngStartDeg;
			float m_sngSpanDeg;
			float m_sngInRad;
			float m_sngOutRad;
			GtColor m_objColor;
			std::wstring m_strName;
			GtRectI m_objRect;
		};

		class HTL_DLLAPI  GtPlotPie: public GtPlotItem
		{
		public:
			//!Parent set constructor
			GtPlotPie(GtObject* ptrParent = NULL);

			//!Virtual destructor
			virtual ~GtPlotPie(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtPlotPie & operator = (GtPlotPie & rhs);

			//!The pointer to the plot that this item is attached to
			GTOBJECT_MEMVAR_BYREF(public, GtPoint3DI, objCenterPos);


			void SetInnerRadius(float innerRad);
			void SetOuterRadius(float outerRad);

			//!Clears the polyline of all points
			inline void Clear(void);
			//!Gets the number of points
			inline size_t Size(void);
			//!Returns the point at index
			inline GtPieItem & At(size_t index);
			//!Adds the point3d the the back of the coordinates
			inline void PushBack(GtPieItem & objNewPoint);
			//!Round the polyline coordinates to number of decimals
			inline void Round(int intNumDecimals);
			//!Update the percents
			void UpdateData(void);

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

			StlVector<GtPieItem, HtlUnknownType> m_arrObjPoints;
			std::string m_strObjectName;
		private:
			GtPieItem m_objNullPoint;


		};//end GtPlotItem class definition

	}//end namespace GtChart
}//end namespace GT
#endif //GT_PLOT_ITEM_H