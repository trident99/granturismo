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

#ifndef GT_LIST_SELECTION_H
#define GT_LIST_SELECTION_H

#include "..\modGtBase.h"
#include ".\GtListModelIndex.h"

using namespace HTL;

namespace GT
{

	namespace GtCore
	{
		typedef StlVector<GtListModelIndex*, HtlUnknownType> GtListIndexList;
		typedef StlVector<GtListModelIndex*, HtlUnknownType>::StlIterator GtListIterator;

		class GtListItemModel;

		class HTL_DLLAPI GtListSelection : public GtObject
		{
		public:
			//!Parent set constructor
			GtListSelection(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtListSelection(void);

			//MEMBER VARIABLES////////////////////////
			//!Pointer to the parent object
			GTOBJECT_MEMVAR_BYVAL(public, GtListModelIndex*, ptrTopLeft);
			//!Pointer to the parent object
			GTOBJECT_MEMVAR_BYVAL(public, GtListModelIndex*, ptrBottomRight);
			//!Pointer to the parent object
			GTOBJECT_MEMVAR_BYVAL(public, GtListItemModel*, ptrModel);
			
		public:
			//ADDING REMOVAL SORTING METHODS/////////////////////
			//!Add the index to the selection
			void AddSelIndex(GtListModelIndex * ptrIndex);
			//!Remove the index from the selection
			void RemoveSelIndex(GtListModelIndex * ptrIndex);
			//!Gets the selected range based on the top left and bottom right
			void GetSelectedRange(void);
			//!Sorts the selection in ascending order (col, row, page order)
			void SortSelection(void);
			//!Clears the selection
			void ClearSelection(void);

			//QUERYING METHODS//////////////////////////////////
			//!Selection Size
			long Count(void);
			//!Does the selection have any items
			bool HasSelection(void);
			//!Is the row selected
			bool IsRowSelected(size_t row);
			//!Is the index of interest selected
			bool IsSelected(GtListModelIndex * index);

			//RETRIEVAL METHODS////////////////////////////////
			//!Get the pointer to the selected Indexes in a list
			GtListIndexList* GetSelIndexesPtr(void){return &m_arrPtrIndexes;}; 

		protected:
			//the collection of selected indexes
			GtListIndexList m_arrPtrIndexes;

		};//end HtlBase class definition

}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H