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

#ifndef GT_PLOT_SELECTION_H
#define GT_PLOT_SELECTION_H

#include ".\GtPlotItem.h"

namespace GT
{

	namespace GtChart
	{

		class HTL_DLLAPI GtPlotSelection : public GtObject
		{
		public:
			//!Parent set constructor
			GtPlotSelection(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtPlotSelection(void);

			//MEMBER VARIABLES////////////////////////
			
		public:
			//ADDING REMOVAL SORTING METHODS/////////////////////
			//!Add the index to the selection
			void AddSelItem(GtPlotItem * item);
			//!Remove the index from the selection
			void RemoveSelItem(GtPlotItem * item);

			//!Sorts the selection in ascending order (col, row, page order)
			void SortSelection(void);
			//!Clears the selection
			void ClearSelection(void);

			//QUERYING METHODS//////////////////////////////////
			//!Selection Size
			long Count(void);
			//!Does the selection have any items
			bool HasSelection(void);
			//!Is the index of interest selected
			bool IsSelected(GtPlotItem * item);

			//RETRIEVAL METHODS////////////////////////////////
			//!Get the pointer to the selected Indexes in a list
			GtPlotItemList* GetSelItemsPtr(void){return &m_arrPtrSelected;}; 

		protected:
			//the collection of selected indexes
			GtPlotItemList m_arrPtrSelected;

		};//end GtPlotSelection class definition

	};//end namespace GtChart
};//end namespace GT
#endif //GT_PLOT_SELECTION_H