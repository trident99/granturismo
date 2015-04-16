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

#include ".\GtListItemModel.h"

namespace GT
{
	namespace GtCore
	{

		//default constructor
		GtListItemModel::GtListItemModel(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtListItemModel";
		};
		//virtual destructor
		GtListItemModel::~GtListItemModel(void)
		{
			this->m_arrRowHeaders.clear();
			this->m_arrColHeaders.clear();
			this->m_arrModel.clear();
		};

		//THESE PURE VIRTUAL FUNCTIONS NEED TO BE IMPLEMENTED IN SUBCLASSES
		//!Get the row count of the 
		//virtual int  CountRows(void) const = 0; 
		//!Get the data at the desired index
		//virtual GtVariant GetData(size_t row) const = 0; 
		//!Syncronize the Abstract Item Model with the real model
		//virtual void UpdateSyncModel(void) = 0;
		///////////////////////////////////////////////////////////////////


		//!Gets the data pointer at the desired index
		void * GtListItemModel::GetDataPtr(size_t row)
		{
			if(m_arrModel.size() <= 0){return NULL;};
			GtListModelIndex obj;
			obj.m_lngRow = row;
			GtListMapIter iter = m_arrModel.find(obj);
			if( iter != m_arrModel.end())
			{
				return iter->m_objData;
			};
			//couldn't find row
			return NULL;
		};
		//!returns the item flags for the object
		int  GtListItemModel::Getflags(size_t row)
		{
			if(m_arrModel.size() <= 0){return NULL;};
			GtListModelIndex obj;
			obj.m_lngRow = row;
			GtListMapIter iter = m_arrModel.find(obj);
			if( iter != m_arrModel.end())
			{
				return iter->m_objKey.m_itemFlag;
			};
			//couldn't find row
			return NULL;
		};

		//!Gets the data pointer at the desired index
		std::string GtListItemModel::GetText(size_t row)
		{
			std::string strRet;
			if(m_arrModel.size() <= 0){return strRet;};
			GtListModelIndex obj;
			obj.m_lngRow = row;
			GtListMapIter iter = m_arrModel.find(obj);
			if( iter != m_arrModel.end())
			{
				GtListModelIndex * ptrKey = &iter->m_objKey;
				if(ptrKey)
				{
					return ptrKey->m_strText;
				}
			};
			//couldn't find it
			return strRet;
		}; 

		//!Get the data at the desired index
		GtListModelIndex * GtListItemModel::GetIndex(size_t row)
		{
			if(m_arrModel.size() <= 0){return NULL;};
			GtListModelIndex obj;
			obj.m_lngRow = row;
			GtListMapIter iter = m_arrModel.find(obj);
			if( iter != m_arrModel.end())
			{
				return &iter->m_objKey;
			};
			//couldn't find it
			return NULL;
		}; 

		//!Determine if the parent node has a child index
		bool  GtListItemModel::HasIndex(size_t row)
		{
			if(m_arrModel.size() <= 0){return false;};
			GtListModelIndex obj;
			obj.m_lngRow = row;
			GtListMapIter iter = m_arrModel.find(obj);
			return (iter != m_arrModel.end());
		};

		//!Get the Horizontal Header string
		std::string  GtListItemModel::GetColumnHeader(size_t col)
		{
			std::string strRet;
			return strRet;
		};
		//!Set the Horizontal Header Data
		void GtListItemModel::SetColumnHeader(size_t col, std::string varVal)
		{
			return;
		};

		//!Get the Vertical Header string
		std::string GtListItemModel::GetRowHeader(size_t row)
		{
			std::string strRet;
			return strRet;
		};
		//!Set the Vertical Header Data
		void GtListItemModel::SetRowHeader(size_t row, std::string varVal)
		{
			return;
		};
		//!Get the pointer to the list map
		GtListIndexMap * GtListItemModel::GetModelMapPtr(void)
		{
			return &m_arrModel;
		};

		int GtListItemModel::SetItemDataPtr(size_t row, void * ptrData)
		{
			GtListModelIndex obj;
			obj.m_lngRow = row;
			GtListMapIter iter = m_arrModel.find(obj);
			if( iter != m_arrModel.end())
			{
				iter->m_objKey.m_ptrData = ptrData;
				iter->m_objData = ptrData;
				return 1;
			};
			//couldn't find row
			return 0;
		};
		//!Create a model index
		GtListModelIndex GtListItemModel::CreateIndex(size_t row, void * ptrData)
		{
			GtListModelIndex obj;
			obj.m_lngRow = row;
			obj.m_ptrData = ptrData;
			return obj;
		}; 

	};//end namespace GtCore

};//end namespace GT