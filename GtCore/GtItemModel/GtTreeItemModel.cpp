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

#include ".\GtTreeItemModel.h"

namespace GT
{
	namespace GtCore
	{

		//default constructor
		GtTreeItemModel::GtTreeItemModel(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtTreeItemModel";
			m_objRootIndex.m_lngRow = -1;//illegal index
			m_objRootIndex.m_lngCol = -1;//illegal index
			m_objRootIndex.m_blnExpanded = true;//root always expanded
			m_objRootIndex.m_strText = "ROOT";
		};
		//virtual destructor
		GtTreeItemModel::~GtTreeItemModel(void)
		{
			this->m_arrRowHeaders.clear();
			this->m_arrColHeaders.clear();
			this->DeleteAllIndexes();
		};

		//THESE PURE VIRTUAL FUNCTIONS NEED TO BE IMPLEMENTED IN SUBCLASSES
		//!Get the row count of the 
		//virtual int  CountRows(void) const = 0; 
		//!Get the column count of the model
		//virtual int  CountColumns(void) = 0; 
		//!Get the data at the desired index
		//virtual GtVariant GetData(size_t row) const = 0; 
		//!Syncronize the Abstract Item Model with the real model
		//virtual void UpdateSyncModel(void) = 0;
		///////////////////////////////////////////////////////////////////
		//!Create a model index
		GtTreeModelIndex* GtTreeItemModel::CreateIndex(size_t row, size_t col, void * ptrData)
		{
			GtTreeModelIndex* ptrNew = new GtTreeModelIndex();
			ptrNew->m_lngRow = row;
			ptrNew->m_lngCol = col;
			ptrNew->m_ptrData = ptrData;

			m_arrModel.push_back(ptrNew);
			return ptrNew;
		}; 


		void GtTreeItemModel::DeleteAllIndexes(void)
		{
			size_t i, numNodes;
			numNodes = m_arrModel.size();
			for(i = 0; i < numNodes; i++)
			{
			GtTreeModelIndex* ptrCurr = m_arrModel.at(i);
			delete ptrCurr;
			}
			m_arrModel.clear();
		};

		//!Gets the data pointer at the desired index
		void * GtTreeItemModel::GetDataPtr(size_t row, size_t col)
		{
			GtTreeModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTreeMapIter iter = FindNodeByIndex(obj);
			if( iter != m_arrModel.end())
			{
				GtTreeModelIndex* ptrIndex = iter->m_data;
				return ptrIndex->m_ptrData;
			};
			//couldn't find row
			return NULL;
		};
		//!returns the item flags for the object
		int  GtTreeItemModel::Getflags(size_t row, size_t col)
		{
			GtTreeModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTreeMapIter iter = FindNodeByIndex(obj);
			if( iter != m_arrModel.end())
			{
				GtTreeModelIndex* ptrIndex = iter->m_data;
				return ptrIndex->m_itemFlag;
			};
			//couldn't find row
			return NULL;
		};

		//!Get the data at the desired index
		GtTreeModelIndex * GtTreeItemModel::AtIndex(size_t index)
		{
			
			if((index >= 0)&&(index <= 	m_arrModel.size()))
			{
				GtTreeModelIndex *ptrRet = m_arrModel.at(index);
				if(ptrRet)
				{
					return ptrRet;
				}else{
					return NULL;
				}
			}
			return NULL;
		};


		//!Get the data at the desired index
		GtTreeModelIndex * GtTreeItemModel::GetIndex(size_t row, size_t col)
		{
			GtTreeModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTreeMapIter iter = FindNodeByIndex(obj);
			if( iter != m_arrModel.end())
			{
				GtTreeModelIndex* ptrIndex = iter->m_data;
				return ptrIndex;
			};
			//couldn't find it
			return NULL;
		}; 

		//!Determine if the parent node has a child index
		bool  GtTreeItemModel::HasIndex(size_t row, size_t col)
		{
			GtTreeModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTreeMapIter iter = FindNodeByIndex(obj);
			return ((iter != m_arrModel.end())&&(iter != NULL));
		};

		//!Get the Horizontal Header string
		std::string  GtTreeItemModel::GetColumnHeader(size_t col)
		{
			std::string strRet;
			return strRet;
		};
		//!Set the Horizontal Header Data
		void GtTreeItemModel::SetColumnHeader(size_t col, std::string varVal)
		{
			return;
		};

		//!Get the Vertical Header string
		std::string GtTreeItemModel::GetRowHeader(size_t row)
		{
			std::string strRet;
			return strRet;
		};
		//!Set the Vertical Header Data
		void GtTreeItemModel::SetRowHeader(size_t row, std::string varVal)
		{
			return;
		};
		//!Get the pointer to the list map
		GtTreeIndexMap * GtTreeItemModel::GetModelMapPtr(void)
		{
			return &m_arrModel;
		};

		int GtTreeItemModel::SetItemDataPtr(size_t row, size_t col, void * ptrData)
		{
			GtTreeModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTreeMapIter iter = FindNodeByIndex(obj);
			if( iter != m_arrModel.end())
			{
				GtTreeModelIndex* ptrIndex = iter->m_data;
				ptrIndex->m_ptrData = ptrData;
				return 1;
			};
			//couldn't find row
			return 0;
		};

		GtTreeMapIter GtTreeItemModel::FindNodeByIndex(GtTreeModelIndex & index)
		{
			if(m_arrModel.size() <= 0){return NULL;};
			GtTreeMapIter iter = m_arrModel.begin();
			while(iter != m_arrModel.end())
			{
				if(*(iter->m_data) == index){return iter;};

				iter = m_arrModel.next();
			}
			return NULL;
		};

		GtTreeMapIter GtTreeItemModel::FindNodeByData(void * ptrData)
		{
			if(m_arrModel.size() <= 0){return NULL;};
			GtTreeMapIter iter = m_arrModel.begin();
			while(iter != m_arrModel.end())
			{
				GtTreeModelIndex* ptrCurr = iter->m_data;
				if(ptrCurr)
				{
					if(ptrCurr->m_ptrData == ptrData){return iter;};
				}
				iter = m_arrModel.next();
			}
			return NULL;
		};
	};//end namespace GtCore

};//end namespace GT