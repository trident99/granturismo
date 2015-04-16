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


#ifndef GT_LIST_ITEM_MODEL_H
#define GT_LIST_ITEM_MODEL_H

#include "..\GtCoreLibRefs.h"
#include <modHtlContainer.h>
#include "..\modGtBase.h"
#include ".\GtItemEnums.h"
#include ".\GtListModelIndex.h"

namespace GT
{
	namespace GtCore
	{
		typedef HtlListMap<GtListModelIndex,HtlUnknownType,void*,HtlUnknownType> GtListIndexMap;
		typedef HtlTreeNode<GtListModelIndex,void*>* GtListMapIter;


		class HTL_DLLAPI GtListItemModel: public GtObject
		{
		public:
			//!Default Constructor
			GtListItemModel(GtObject* ptrParent = NULL);
			//!Destructor
			virtual ~GtListItemModel();

			//PURE VIRTUAL FUNCTION, NEED TO BE IMPLEMENTED
			//!Get the row count of the 
			virtual size_t  CountRows(void) = 0; 
			//!Get the data at the desired index
			virtual GtVariant GetData(size_t row) = 0;
			//!Syncronize the Abstract Item Model with the real model
			virtual void UpdateSyncModel(void) = 0;

			//!Get the data at the desired index
			virtual GtListModelIndex *GetIndex(size_t row);
			//!Gets the data pointer at the desired index
			virtual std::string GetText(size_t row);
			//!Gets the data pointer at the desired index
			virtual void * GetDataPtr(size_t row);
			//!returns the item flags for the object
			virtual int Getflags(size_t row);
			//!Determine if the parent node has a child index
			bool  HasIndex(size_t row); 
			
			//!Get the Horizontal Header string
			virtual std::string  GetColumnHeader(size_t col);
			//!Set the Horizontal Header Data
			virtual void SetColumnHeader(size_t col, std::string varVal);	
			
			//!Get the Vertical Header string
			virtual std::string GetRowHeader(size_t row);
			//!Set the Vertical Header Data
			virtual void SetRowHeader(size_t row, std::string varVal);
			//!Get the pointer to the list map
			GtListIndexMap * GetModelMapPtr(void);
			
			virtual int SetItemDataPtr(size_t row, void * ptrData); 


		protected:
			//The actual index map for the model
			GtListIndexMap m_arrModel;
			//!The row header strings
			Htl1DList<std::string, STL_STRING> m_arrRowHeaders;
			//!The Column Header strings
			Htl1DList<std::string, STL_STRING> m_arrColHeaders;
			//!Create a model index
			GtListModelIndex CreateIndex(size_t row, void * ptrData = 0); 

		};//end GtAbstractItemModel

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_H