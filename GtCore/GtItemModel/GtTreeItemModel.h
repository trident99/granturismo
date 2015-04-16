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


#ifndef GT_TREE_ITEM_MODEL_H
#define GT_TREE_ITEM_MODEL_H

#include "..\GtCoreLibRefs.h"
#include "..\modGtBase.h"
#include ".\GtItemEnums.h"
#include ".\GtTreeModelIndex.h"

namespace GT
{
	namespace GtCore
	{
		typedef Htl1DList<GtTreeModelIndex*,HtlUnknownType> GtTreeIndexMap;
		typedef HtlListNode<GtTreeModelIndex*>* GtTreeMapIter;

		class HTL_DLLAPI GtTreeItemModel: public GtObject
		{
		public:
			//!Default Constructor
			GtTreeItemModel(GtObject* ptrParent = NULL);
			//!Destructor
			virtual ~GtTreeItemModel();

			//PURE VIRTUAL FUNCTION, NEED TO BE IMPLEMENTED
			//!Create a model index
			GtTreeModelIndex* CreateIndex(size_t row, size_t col, void * ptrData = 0);
			//!Delete All Indexes
			void DeleteAllIndexes(void);

			//!Get the row count of the model
			virtual int  Size(void){return m_arrModel.size();}; 
			//!Get the row count of the model
			virtual int  CountRows(void){return m_arrModel.size();}; 
			//!Get the column count of the model
			virtual int  CountColumns(void) = 0; 
			//!Get the data at the desired index
			virtual GtVariant GetData(size_t row, size_t col) = 0;
			
			//!Syncronize the Abstract Item Model with the real model
			virtual void UpdateSyncModel(void) = 0;
			//!Syncronize the Abstract Item Model ROW with the real model
			virtual void UpdateSyncNode(GtTreeModelIndex * parent) = 0;
			//!Gather child nodes for 

			//!Get the data at the desired index
			GtTreeModelIndex * AtIndex(size_t index);
			//!Get the data at the desired index
			virtual GtTreeModelIndex * GetIndex(size_t row, size_t col);
			//!Gets the data pointer at the desired index
			virtual void * GetDataPtr(size_t row, size_t col);
			//!returns the item flags for the object
			virtual int Getflags(size_t row, size_t col);
			//!Determine if the parent node has a child index
			bool  HasIndex(size_t row, size_t col); 
			
			//!Get the Horizontal Header string
			virtual std::string  GetColumnHeader(size_t col);
			//!Set the Horizontal Header Data
			virtual void SetColumnHeader(size_t col, std::string varVal);	
			
			//!Get the Vertical Header string
			virtual std::string GetRowHeader(size_t row);
			//!Set the Vertical Header Data
			virtual void SetRowHeader(size_t row, std::string varVal);
			//!Get the pointer to the list map
			GtTreeIndexMap * GetModelMapPtr(void);
			
			virtual int SetItemDataPtr(size_t row, size_t col, void * ptrData); 


			GtTreeModelIndex* GetRootNodePtr(void){return &m_objRootIndex;};

		protected:
			GtTreeModelIndex m_objRootIndex;
			//The actual index map for the model
			GtTreeIndexMap m_arrModel;
			//!The row header strings
			Htl1DList<std::string, STL_STRING> m_arrRowHeaders;
			//!The Column Header strings
			Htl1DList<std::string, STL_STRING> m_arrColHeaders;

			GtTreeMapIter FindNodeByIndex(GtTreeModelIndex & index);
			GtTreeMapIter FindNodeByData(void * ptrData);

		};//end GtAbstractItemModel

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_H