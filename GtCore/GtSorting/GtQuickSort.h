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

#ifndef GT_QUICKSORT_H
#define GT_QUICKSORT_H

#include "..\GtCoreLibRefs.h"
#include <modHtlContainer.h>
using namespace HTL;

namespace GT
{

	namespace GtCore
	{
//template<typeName TObj> 
//typedef bool (*CompFuncPtr)(TObj & ptrA, TObj & ptrB);
////SORTING ALGORITHMS FOR COMPOSITE COLLECTION OF REQUIREMENTS
////////////////////////////////////////////////////////////////////////////////////////////////////
////vector partitioning algorithm
//	template<typename TObj, HtlObjectType TObjEnum>
//	int ReqCompPartition(Htl1DVector<TObj,TObjEnum> * ptrCollection, int iLeft, int iRight, CompFuncPtr LTFunc, CompFuncPtr GTFunc, CompFuncPtr EQFunc )
//	{
//		if(!ptrCollection){return 0;};
//		TObj ptrPivot = ptrCollection->at(iRight);
//		try{
//			while(iLeft < iRight)
//			{
//				while(ptrCollection->at(iLeft) < ptrPivot)
//				{
//					iLeft++;
//				}
//				while(ptrCollection->at(iRight) > ptrPivot)
//				{
//					iRight--;
//				}
//				if(ptrCollection->at(iLeft)	== ptrCollection->at(iRight))
//				{
//					iLeft++;
//				}else if (iLeft < iRight){
//					ptrCollection->SwapObjects(iLeft,iRight);
//				}
//			}
//
//			return iRight;
//		}catch(...){
//			return -1;
//		}
//
//	};
//	//vector quicksort algorithm
//	template<typename TObj, HtlObjectType TObjEnum>
//	int GtQuickSort(Htl1DVector<TObj,TObjEnum> * ptrCollection, int iStartIndex, int iEndIndex, CompFuncPtr LTFunc, CompFuncPtr GTFunc, CompFuncPtr EQFunc )
//	{
//		try{
//			if(!ptrCollection){return 0;};
//			//pivot element
//			int intSplitPoint;
//
//			if(iStartIndex < iEndIndex)
//			{
//				//return the position where the pivot belongs
//				intSplitPoint = ReqCompPartition(ptrCollection,iStartIndex,iEndIndex);
//				ReqCompQuickSort(ptrCollection,iStartIndex, intSplitPoint - 1);
//				ReqCompQuickSort(ptrCollection,intSplitPoint + 1, iEndIndex);
//			}
//			return 1;
//		}catch(...){return -1;};
//	}
//
//	//!Sort the Composite Collection of Requirements - exported
//	int SortCompRequirements(HtlCompositeManager<FRMRequirement,HTL_BASE> * ptrCollection, CompFuncPtr LTFunc, CompFuncPtr GTFunc, CompFuncPtr EQFunc )
//	{
//		if(!ptrCollection){return 0;};
//		int intRet;
//		int intNum = ptrCollection->Size();
//		intRet = ReqCompQuickSort(ptrCollection,0,(intNum - 1));
//		return intRet;
//		
//	};

	}//end namespace GtCore
}//end namespace GT
#endif //GT_QUICKSORT_H