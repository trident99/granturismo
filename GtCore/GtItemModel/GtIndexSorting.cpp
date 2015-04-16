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

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtIndexSorting.h"

namespace GT
{
	namespace GtCore
	{
		//SORTING ALGORITHMS FOR GTLISTMODELINDEX COLLECTION
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//vector partitioning algorithm
		int ListPartition(GtListIndexColl * ptrCollection, int iLeft, int iRight)
		{
			if(!ptrCollection){return 0;};
			GtListModelIndex* ptrPivot = ptrCollection->at(iRight);
			if(!ptrPivot){return 0;};
			try{
				while(iLeft < iRight)
				{
					while(*(ptrCollection->at(iLeft)) < *ptrPivot)
					{
						iLeft++;
					}
					while(*(ptrCollection->at(iRight)) > *ptrPivot)
					{
						iRight--;
					}
					if(*(ptrCollection->at(iLeft)) == *(ptrCollection->at(iRight)))
					{
						iLeft++;
					}else if (iLeft < iRight){
						//SwapObjects
						GtListModelIndex* ptrTemp = ptrCollection->at(iLeft);
						ptrCollection->at(iLeft) = ptrCollection->at(iRight);
						ptrCollection->at(iRight) = ptrTemp;
					}
				}

				return iRight;
			}catch(...){
				return -1;
			}

		};
		//vector quicksort algorithm
		int ListQuickSort(GtListIndexColl * ptrCollection, int iStartIndex, int iEndIndex)
		{
			try{
				if(!ptrCollection){return 0;};
				//pivot element
				int intSplitPoint;

				if(iStartIndex < iEndIndex)
				{
					//return the position where the pivot belongs
					intSplitPoint = ListPartition(ptrCollection,iStartIndex,iEndIndex);
					ListQuickSort(ptrCollection,iStartIndex, intSplitPoint - 1);
					ListQuickSort(ptrCollection,intSplitPoint + 1, iEndIndex);
				}
				return 1;
			}catch(...){return -1;};
		}

		//!Sort the Composite Collection of Requirements - exported
		int SortListIndexes(GtListIndexColl * ptrCollection)
		{
			if(!ptrCollection){return 0;};
			int intRet;
			int intNum = ptrCollection->size();
			intRet = ListQuickSort(ptrCollection,0,(intNum - 1));
			return intRet;	
		};
		//SORTING ALGORITHMS FOR GTTABLEMODELINDEX COLLECTION
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//vector partitioning algorithm
		int TablePartition(GtTableIndexColl * ptrCollection, int iLeft, int iRight)
		{
			if(!ptrCollection){return 0;};
			GtTableModelIndex* ptrPivot = ptrCollection->at(iRight);
			if(!ptrPivot){return 0;};
			try{
				while(iLeft < iRight)
				{
					while(*(ptrCollection->at(iLeft)) < *ptrPivot)
					{
						iLeft++;
					}
					while(*(ptrCollection->at(iRight)) > *ptrPivot)
					{
						iRight--;
					}
					if(*(ptrCollection->at(iLeft)) == *(ptrCollection->at(iRight)))
					{
						iLeft++;
					}else if (iLeft < iRight){
						//SwapObjects
						GtTableModelIndex* ptrTemp = ptrCollection->at(iLeft);
						ptrCollection->at(iLeft) = ptrCollection->at(iRight);
						ptrCollection->at(iRight) = ptrTemp;
					}
				}

				return iRight;
			}catch(...){
				return -1;
			}

		};
		//vector quicksort algorithm
		int TableQuickSort(GtTableIndexColl * ptrCollection, int iStartIndex, int iEndIndex)
		{
			try{
				if(!ptrCollection){return 0;};
				//pivot element
				int intSplitPoint;

				if(iStartIndex < iEndIndex)
				{
					//return the position where the pivot belongs
					intSplitPoint = TablePartition(ptrCollection,iStartIndex,iEndIndex);
					TableQuickSort(ptrCollection,iStartIndex, intSplitPoint - 1);
					TableQuickSort(ptrCollection,intSplitPoint + 1, iEndIndex);
				}
				return 1;
			}catch(...){return -1;};
		}

		//!Sort the Composite Collection of Requirements - exported
		int SortTableIndexes(GtTableIndexColl * ptrCollection)
		{
			if(!ptrCollection){return 0;};
			int intRet;
			int intNum = ptrCollection->size();
			intRet = TableQuickSort(ptrCollection,0,(intNum - 1));
			return intRet;	
		};

		//SORTING ALGORITHMS FOR GTTREEMODELINDEX COLLECTION
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//vector partitioning algorithm
		int TreePartition(GtTreeIndexColl * ptrCollection, int iLeft, int iRight)
		{
			if(!ptrCollection){return 0;};
			GtTreeModelIndex* ptrPivot = ptrCollection->at(iRight);
			if(!ptrPivot){return 0;};
			try{
				while(iLeft < iRight)
				{
					while(*(ptrCollection->at(iLeft)) < *ptrPivot)
					{
						iLeft++;
					}
					while(*(ptrCollection->at(iRight)) > *ptrPivot)
					{
						iRight--;
					}
					if(*(ptrCollection->at(iLeft)) == *(ptrCollection->at(iRight)))
					{
						iLeft++;
					}else if (iLeft < iRight){
						//SwapObjects
						GtTreeModelIndex* ptrTemp = ptrCollection->at(iLeft);
						ptrCollection->at(iLeft) = ptrCollection->at(iRight);
						ptrCollection->at(iRight) = ptrTemp;
					}
				}

				return iRight;
			}catch(...){
				return -1;
			}

		};
		//vector quicksort algorithm
		int TreeQuickSort(GtTreeIndexColl * ptrCollection, int iStartIndex, int iEndIndex)
		{
			try{
				if(!ptrCollection){return 0;};
				//pivot element
				int intSplitPoint;

				if(iStartIndex < iEndIndex)
				{
					//return the position where the pivot belongs
					intSplitPoint = TreePartition(ptrCollection,iStartIndex,iEndIndex);
					TreeQuickSort(ptrCollection,iStartIndex, intSplitPoint - 1);
					TreeQuickSort(ptrCollection,intSplitPoint + 1, iEndIndex);
				}
				return 1;
			}catch(...){return -1;};
		}

		//!Sort the Composite Collection of Requirements - exported
		int SortTreeIndexes(GtTreeIndexColl * ptrCollection)
		{
			if(!ptrCollection){return 0;};
			int intRet;
			int intNum = ptrCollection->size();
			intRet = TreeQuickSort(ptrCollection,0,(intNum - 1));
			return intRet;	
		};

	};//end namespace GtCore

};//end namespace GT