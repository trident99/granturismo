/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
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

#ifndef GT_TABLE_COLUMN_H
#define GT_TABLE_COLUMN_H

#include "..\GtGuiLibRefs.h"
#include <modGtGraphic.h>
#include <modGtGeometry.h>
#include <modGtItemModel.h>

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{
		class HTL_DLLAPI GtTableColumn : public GtObject
		{
		public:
			//!Parent set constructor
			GtTableColumn(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtTableColumn(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The row of the cell
			GTOBJECT_MEMVAR_BYVAL(public, long, lngColumn);
			//!The column of the cell
			GTOBJECT_MEMVAR_BYVAL(public, int, intWidth);
			//SIGNALS/////////////////////////////////
		public:
			HtlSignal00 Resized;

			//MEMBER FUNCTIONS////////////////////////
			//!Get the cell at column index
			GtTableModelIndex* GetCellPtr(int rowIndex);
			//!The number of cells
			long CountCells(void);
			//!Gather cells from the TableView
			void ResetCellMembers(void);
		protected:
			//!pointer to the column
			Htl1DList<GtTableModelIndex*,HtlUnknownType> m_arrCells;
		};//end GtTableColumn class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H