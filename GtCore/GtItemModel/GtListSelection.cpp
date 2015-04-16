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

#include ".\GtListSelection.h"
#include ".\GtListItemModel.h"
#include ".\GtIndexSorting.h"

namespace GT
{
	namespace GtCore
	{
		//!Parent set constructor
		GtListSelection::GtListSelection(GtObject* ptrParent)
			:GtObject(ptrParent)
		{
			m_ptrTopLeft = NULL;
			m_ptrBottomRight = NULL;
		};
		//!Virtual destructor
		GtListSelection::~GtListSelection(void)
		{
			m_ptrTopLeft = NULL;
			m_ptrBottomRight = NULL;
			this->ClearSelection();
		};

		//!Add the index to the selection
		void GtListSelection::AddSelIndex(GtListModelIndex * ptrIndex)
		{
			if(ptrIndex)
			{
				this->m_arrPtrIndexes.push_back(ptrIndex);
			}
			return;
		};
		//!Remove the index from the selection
		void GtListSelection::RemoveSelIndex(GtListModelIndex * ptrIndex)
		{
			GtListIterator iter;

			for(iter = m_arrPtrIndexes.begin(); iter != m_arrPtrIndexes.end(); ++iter)
			{
				if(*(*iter) == *ptrIndex)
				{
					m_arrPtrIndexes.erase(iter);
					return;
				};
			};
			return;
		};
		//!Gets the selected range based on the top left and bottom right
		void GtListSelection::GetSelectedRange(void)
		{
			if(!this->m_ptrModel){return;};//safety check
			if(!this->m_ptrTopLeft){return;};//safety check
			if(!this->m_ptrBottomRight){return;};//safety check

			m_arrPtrIndexes.clear();
			size_t i,iLow, iHigh;
			iLow = m_ptrTopLeft->m_lngRow;
			iHigh = m_ptrBottomRight->m_lngRow;

			for(i = iLow; i <= iHigh ; i++)
			{
				GtListModelIndex* ptrSel = m_ptrModel->GetIndex(i);
				m_arrPtrIndexes.push_back(ptrSel);
			}//end i loop
		};
		//!Sorts the selection in ascending order (col, row, page order)
		void GtListSelection::SortSelection(void)
		{
			//SortListIndexes(&m_arrPtrIndexes);
		};
		//!Clears the selection
		void GtListSelection::ClearSelection(void)
		{
			m_ptrTopLeft = NULL;
			m_ptrBottomRight = NULL;
			m_arrPtrIndexes.clear();
		};

		//QUERYING METHODS//////////////////////////////////
					//!Selection Size
		long GtListSelection::Count(void)
		{
			return m_arrPtrIndexes.size();
		}
		//!Does the selection have any items
		bool GtListSelection::HasSelection(void)
		{
			return (m_arrPtrIndexes.size() > 0);
		};
		//!Is the row selected
		bool GtListSelection::IsRowSelected(size_t row)
		{
			size_t i, numIndexes;
			numIndexes = m_arrPtrIndexes.size();
			for(i = 0; i < numIndexes; i++)
			{
				if(m_arrPtrIndexes.at(i)->m_lngRow == row)
				{
					return true;
				}
			}
			return false;
		};
		//!Is the index of interest selected
		bool GtListSelection::IsSelected(GtListModelIndex * index)
		{
			size_t i, numIndexes;
			numIndexes = m_arrPtrIndexes.size();
			for(i = 0; i < numIndexes; i++)
			{
				if(m_arrPtrIndexes.at(i) == index)
				{
					return true;
				}
			}
			return false;
		};


	};//end namespace GtCore

};//end namespace GT