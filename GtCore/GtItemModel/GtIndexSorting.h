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

#ifndef GT_INDEX_SORT_H
#define GT_INDEX_SORT_H

#include "..\GtCoreLibRefs.h"
#include ".\GtListModelIndex.h"
#include ".\GtTableModelIndex.h"
#include ".\GtTreeModelIndex.h"
#include <modHtlContainer.h>
using namespace HTL;

namespace GT
{

	namespace GtCore
	{
		//SORTING ALGORITHMS FOR GTLISTMODELINDEX COLLECTION
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//vector partitioning algorithm
		int ListPartition(GtListIndexColl * ptrCollection, int iLeft, int iRight);
		//vector quicksort algorithm
		int ListQuickSort(GtListIndexColl * ptrCollection, int iStartIndex, int iEndIndex);
		//!Sort the Composite Collection of Requirements - exported
		HTL_DLLAPI int SortListIndexes(GtListIndexColl * ptrCollection);

		//SORTING ALGORITHMS FOR GTTABLEMODELINDEX COLLECTION
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//vector partitioning algorithm
		int TablePartition(GtTableIndexColl * ptrCollection, int iLeft, int iRight);
		//vector quicksort algorithm
		int TableQuickSort(GtTableIndexColl * ptrCollection, int iStartIndex, int iEndIndex);
		//!Sort the Composite Collection of Requirements - exported
		HTL_DLLAPI int SortTableIndexes(GtTableIndexColl * ptrCollection);

		//SORTING ALGORITHMS FOR GTTREEMODELINDEX COLLECTION
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//vector partitioning algorithm
		int TreePartition(GtTreeIndexColl * ptrCollection, int iLeft, int iRight);
		//vector quicksort algorithm
		int TreeQuickSort(GtTreeIndexColl * ptrCollection, int iStartIndex, int iEndIndex);
		//!Sort the Composite Collection of Requirements - exported
		HTL_DLLAPI int SortTreeIndexes(GtTreeIndexColl * ptrCollection);


	}//end namespace GtCore
}//end namespace GT
#endif //GT_INDEX_SORT_H