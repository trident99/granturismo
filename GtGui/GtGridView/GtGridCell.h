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

#ifndef GT_GRID_CELL_H
#define GT_GRID_CELL_H

#include "..\GtTextView\GtSimpleTextEdit.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{
		//common delegates
		class GtCheckBox;
		class GtComboBox;
		class GtSpinBox;

		class GtGridRow;
		class GtGridColumn;

		class HTL_DLLAPI GtGridCell : public GtSimpleTextEdit
		{
		public:
			//!Parent set constructor
			GtGridCell(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtGridCell(void);

			//MEMBER VARIABLES////////////////////////
			//NOTE: Value of the Cell is stored in m_strText
			//!The boolean flage for is the cell a numeric only cell
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnNumeric);
			//!The boolean flag for is the cell editable
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnEditable);
			//GEOMETRY
			//!The row of the cell
			GTOBJECT_MEMVAR_BYVAL(public, long, lngRow);
			//!The column of the cell
			GTOBJECT_MEMVAR_BYVAL(public, long, lngColumn);
			//!The row of the cell
			GTOBJECT_MEMVAR_BYVAL(public, int, intWidth);
			//!The column of the cell
			GTOBJECT_MEMVAR_BYVAL(public, int, intHeight);

			//!The cell delegate if one is assigned
			GTOBJECT_MEMVAR_BYVAL(public, GtWidget*, ptrDelegate);
			void ClearDelegate(void){m_ptrDelegate = NULL;};

			//conveinience functions for common delegates
			GtCheckBox* GetCheckBox(void);
			GtComboBox* GetComboBox(void);
			GtSpinBox* GetSpinBox(void);
			//SIGNALS/////////////////////////////////
		public:
			HtlSignal00 StartEdit;
			HtlSignal00 EndEdit;
			//MEMBER FUNCTIONS////////////////////////
			//!returns the numeric value of the cell
			double Get_dblValue(void);
			//!Get the pointer to the column we are in
			GtGridColumn* GetColumnPtr(void);
			//!Get the pointer to the row we are in
			GtGridRow* GetRowPtr(void);
			//!Start modification of the cell
			void StartModify(void);
			//!End the modification of the cell
			void EndModify(void);
		public:

			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:
			//!pointer to the column
			GtGridColumn* m_ptrColumn;
			//!pointer to the row
			GtGridRow* m_ptrRow;
			//!boolean flage for editing
			bool m_blnModifyCell;
		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H