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

#ifndef GT_GRID_SELECTION_H
#define GT_GRID_SELECTION_H

#include "..\GtGuiLibRefs.h"
#include <modGtGraphic.h>
#include <modGtGeometry.h>

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{
		class GtGridCell;
		class GtGridView;

class HTL_DLLAPI GtGridSelection : public GtObject
		{
		public:
			//!Parent set constructor
			GtGridSelection(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtGridSelection(void);
			//!Copy Constructor
			GtGridSelection(const GtGridSelection& rhs);
			//!Assignment Operator
			GtGridSelection & operator= ( GtGridSelection & rhs);
			//MEMBER VARIABLES////////////////////////
			//!The pointer to the grid view
			GTOBJECT_MEMVAR_BYVAL(public, GtGridView*, ptrGrid);
			//SIGNALS/////////////////////////////////
		public:
			HtlSignal00 SelectionAdd;
			HtlSignal00 SelectionRemove;
			//MEMBER FUNCTIONS////////////////////////
			//!Get of number of cells
			long CountCells(void);
			long CountRows(void);
			long CountColumns(void);
			void GetRange(int & lRow,int & hRow, int & lCol, int & hCol);
			//!Get a cell by its index in the collection
			GtGridCell* GetCell(int index);
			//!Get a cell by its row and column number
			GtGridCell* GetCell(int row, int col);
			//!Add Cell
			void AddCell(GtGridCell* ptrCell);
			//!Add a range of cells
			void AddRangeCells(int lRow,int hRow, int lCol, int hCol);
			//!Clear the selection
			void ClearSelection(void);

		protected:
			//!pointer to the column
			Htl1DList<GtGridCell*,HTL_BASE_PTR> m_arrCells;
			//!Local copy of range extents
			int m_intLRow;
			int m_intHRow;
			int m_intLCol;
			int m_intHCol;
		};//end GtGridRow class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H