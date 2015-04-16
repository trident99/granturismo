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

#include ".\GtTreeModelIndex.h"
#include ".\GtTreeItemModel.h"
#include <modHtlArchive.h>

namespace GT
{
	namespace GtCore
	{

		//!Default Constructor
		GtTreeModelIndex::GtTreeModelIndex()
		{
			this->Clear();
			m_blnVisible = true;
		};
		GtTreeModelIndex::GtTreeModelIndex(GtTreeModelIndex & rhs)
		{
			m_itemFlag = rhs.m_itemFlag;
			m_blnModified = rhs.m_blnModified;
			m_blnExpanded = rhs.m_blnExpanded;
			//m_blnVisible not copied	
			//!The coordinates
			m_lngRow = rhs.m_lngRow;
			m_lngCol = rhs.m_lngCol;
			m_lngLevel = rhs.m_lngLevel;
			m_lngSubRow = rhs.m_lngSubRow;
			//parent model
			m_ptrParent = rhs.m_ptrParent;
			m_ptrModel = rhs.m_ptrModel;
			//for(size_t i = 0; i < m_arrSubNodes.size();i++)
			//{
			//	m_arrSubNodes.push_back(rhs.m_arrSubNodes.at(i));
			//}
			return;
		};
		//!Destructor
		GtTreeModelIndex::~GtTreeModelIndex()
		{
			this->Clear();
		};

		//Assignment Operator Overload
		GtTreeModelIndex & GtTreeModelIndex::operator = (GtTreeModelIndex & rhs)
		{
			if(&rhs != this)
			{
				m_itemFlag = rhs.m_itemFlag;
				m_blnModified = rhs.m_blnModified;
				m_blnExpanded = rhs.m_blnExpanded;
				//m_blnVisible not copied	
				//!The coordinates
				m_lngRow = rhs.m_lngRow;
				m_lngCol = rhs.m_lngCol;
				m_lngLevel = rhs.m_lngLevel;
				m_lngSubRow = rhs.m_lngSubRow;

				m_ptrParent = rhs.m_ptrParent;
				m_ptrModel = rhs.m_ptrModel;
				//for(size_t i = 0; i < m_arrSubNodes.size();i++)
				//{
				//	m_arrSubNodes.push_back(rhs.m_arrSubNodes.at(i));
				//}
			}
			return (*this);
		};
		bool GtTreeModelIndex::operator == (const GtTreeModelIndex & rhs )
		{
			if(m_lngRow != rhs.m_lngRow){return false;};
			if(m_lngCol != rhs.m_lngCol){return false;};
			if(m_lngLevel != rhs.m_lngLevel){return false;};
			if(m_lngSubRow != rhs.m_lngSubRow){return false;};
			return true;
		};
		bool GtTreeModelIndex::operator != (const GtTreeModelIndex & rhs )
		{
			if(m_lngRow != rhs.m_lngRow){return true;};
			if(m_lngCol != rhs.m_lngCol){return true;};
			if(m_lngLevel != rhs.m_lngLevel){return true;};
			if(m_lngSubRow != rhs.m_lngSubRow){return true;};
			return false;
		};
		bool GtTreeModelIndex::operator < (const GtTreeModelIndex & rhs )
		{
			if(m_lngRow < rhs.m_lngRow){return true;};
			if(m_lngCol < rhs.m_lngCol){return true;};
			if(m_lngLevel < rhs.m_lngLevel){return true;};
			if(m_lngSubRow < rhs.m_lngSubRow){return true;};

			return false;
		};
		bool GtTreeModelIndex::operator > (const GtTreeModelIndex & rhs )
		{
			if(m_lngRow > rhs.m_lngRow){return true;};
			if(m_lngCol > rhs.m_lngCol){return true;};
			if(m_lngLevel > rhs.m_lngLevel){return true;};
			if(m_lngSubRow > rhs.m_lngSubRow){return true;};
			return false;
		};
		bool GtTreeModelIndex::operator <= (const GtTreeModelIndex & rhs )
		{
			if(m_lngRow <= rhs.m_lngRow){return true;};
			if(m_lngCol <= rhs.m_lngCol){return true;};
			if(m_lngLevel <= rhs.m_lngLevel){return true;};
			if(m_lngSubRow <= rhs.m_lngSubRow){return true;};
			return false;
		};
		bool GtTreeModelIndex::operator >= (const GtTreeModelIndex & rhs )
		{
			if(m_lngRow >= rhs.m_lngRow){return true;};
			if(m_lngCol >= rhs.m_lngCol){return true;};
			if(m_lngLevel >= rhs.m_lngLevel){return true;};
			if(m_lngSubRow >= rhs.m_lngSubRow){return true;};
			return false;
		};

		void GtTreeModelIndex::GatherChildren(void)
		{
			m_arrSubNodes.clear();
			if(!m_ptrModel){return;};//safety check
			GtTreeIndexMap* ptrList = m_ptrModel->GetModelMapPtr();
			if(ptrList)
			{	
				size_t numIndexes;
				numIndexes = ptrList->size();
				GtTreeMapIter iter;
				for(iter = ptrList->begin();
					iter != ptrList->end(); iter = ptrList->next())
				{
					GtTreeModelIndex* ptrCurr = (iter->m_data);
					if(ptrCurr->m_ptrParent == this)
					{
						this->m_arrSubNodes.push_back(ptrCurr);
					}
				}
				//sort the list by their m_irow index
				this->SortChildren();
			}


			return;
		};

		//!Sort the children by the comparator
		void GtTreeModelIndex::SortChildren(void)
		{


		};
		void GtTreeModelIndex::ReIndexNode(long & lngRow, long lngLevel)
		{
			size_t i, numSubs;
			//set this node
			
			lngRow += 1;
			this->m_lngRow = lngRow;
			this->m_lngLevel = lngLevel + 1;
			//now set children
			numSubs = m_arrSubNodes.size();
			for(i = 0; i < numSubs; i++)
			{
				GtTreeModelIndex* ptrCurr = m_arrSubNodes.at(i);
				if(ptrCurr)
				{
					ptrCurr->ReIndexNode(lngRow,m_lngLevel);
				}
			}
		};
		void GtTreeModelIndex::Clear(void)
		{
			m_itemFlag = NoItemFlags;
			m_blnModified = false;
			m_blnExpanded = false;
			m_blnVisible = true;
			m_lngRow = -1;//illegal index
			m_lngCol = -1;//illegal index
			m_lngLevel = -1;//illegal index
			m_lngSubRow = -1;//illegal index
			m_ptrParent = NULL;
			m_ptrModel = NULL;
			m_ptrData = NULL;
			m_arrData.clear();
			m_arrSubNodes.clear();
			return;
		};

	};//end namespace GtCore

};//end namespace GT