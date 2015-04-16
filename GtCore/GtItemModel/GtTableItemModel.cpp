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

#include ".\GtTableItemModel.h"

namespace GT
{
	namespace GtCore
	{

		//default constructor
		GtTableItemModel::GtTableItemModel(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtTableItemModel";
		};
		//virtual destructor
		GtTableItemModel::~GtTableItemModel(void)
		{
			this->m_arrRowHeaders.clear();
			this->m_arrColHeaders.clear();
			this->m_arrModel.clear();
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


		//!Gets the data pointer at the desired index
		void * GtTableItemModel::GetDataPtr(size_t row, size_t col)
		{
			if(m_arrModel.size() <= 0)
			{
				return NULL;//safety check
			}

			GtTableModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTableMapIter iter = m_arrModel.find(obj);
			if( iter != m_arrModel.end())
			{
				return &iter->m_objData;
			};
			//couldn't find row
			return NULL;
		};

					//!Get the data at the desired index
		GtTableModelIndex * GtTableItemModel::GetIndex(size_t index)
		{
			if(m_arrModel.size() <= 0)
			{
				return NULL;//safety check
			}
			if((index >= 0)&&(index < m_arrModel.size()))
			{
				return &m_arrModel.atkey(index);
			}
			//couldn't find it
			return NULL;	
			
		}; 


		//!Get the data at the desired index
		GtTableModelIndex * GtTableItemModel::GetIndex(size_t row, size_t col)
		{
			if(m_arrModel.size() <= 0)
			{
				return NULL;//safety check
			}

			GtTableModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTableMapIter iter = m_arrModel.find(obj);
			if( iter != m_arrModel.end())
			{
				return &iter->m_objKey;
			};
			//couldn't find it
			return NULL;
		}; 

		//!Determine if the parent node has a child index
		bool  GtTableItemModel::HasIndex(size_t row, size_t col)
		{
			if(m_arrModel.size() <= 0)
			{
				return false;//safety check
			}

			GtTableModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTableMapIter iter = m_arrModel.find(obj);
			return (iter != m_arrModel.end());
		};

		//!Get the Horizontal Header string
		std::string  GtTableItemModel::GetColumnHeader(size_t col)
		{
			std::string strRet;
			if((col >= 0)&&(col< m_arrColHeaders.size()))
			{
				return m_arrColHeaders.at(col);
			}
			return strRet;
		};
		//!Set the Horizontal Header Data
		void GtTableItemModel::SetColumnHeader(size_t col, std::string varVal)
		{
			std::string strNull;
			size_t i, currSize;
			currSize = m_arrColHeaders.size();
			if(col >= currSize)
			{//then neet to add
				for(i = currSize; i < (col +1);i++)
				{
					m_arrColHeaders.push_back(strNull);
				}
			}
			//assign new column header
			m_arrColHeaders.at(col) = varVal;
			return;
		};

		//!Get the Vertical Header string
		std::string GtTableItemModel::GetRowHeader(size_t row)
		{
			std::string strRet;
			if((row >= 0)&&(row< m_arrRowHeaders.size()))
			{
				return m_arrRowHeaders.at(row);
			}
			return strRet;
		};
		//!Set the Vertical Header Data
		void GtTableItemModel::SetRowHeader(size_t row, std::string varVal)
		{
			std::string strNull;
			size_t i, currSize;
			currSize = m_arrRowHeaders.size();
			if(row >= currSize)
			{//then neet to add
				for(i = currSize; i < (row +1);i++)
				{
					m_arrRowHeaders.push_back(strNull);
				}
			}
			//assign new column header
			m_arrRowHeaders.at(row) = varVal;
			return;
		};
		//!Get the pointer to the list map
		GtTableIndexMap * GtTableItemModel::GetModelMapPtr(void)
		{
			return &m_arrModel;
		};

		int GtTableItemModel::SetItemDataPtr(size_t row, size_t col, void * ptrData)
		{
			if(m_arrModel.size() <= 0){return 0;};//nothing to do
			GtTableModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			GtTableMapIter iter = m_arrModel.find(obj);
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
		GtTableModelIndex GtTableItemModel::CreateIndex(size_t row, size_t col, void * ptrData)
		{
			GtTableModelIndex obj;
			obj.m_lngRow = row;
			obj.m_lngCol = col;
			obj.m_ptrData = ptrData;
			return obj;
		}; 


	};//end namespace GtCore

};//end namespace GT