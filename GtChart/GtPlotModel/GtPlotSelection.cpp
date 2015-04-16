/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
**  Qwt Widget Library
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

#include ".\GtPlotSelection.h"

//#include ".\GtIndexSorting.h"

namespace GT
{
	namespace GtChart
	{
		//!Parent set constructor
		GtPlotSelection::GtPlotSelection(GtObject* ptrParent)
			:GtObject(ptrParent)
		{

		};
		//!Virtual destructor
		GtPlotSelection::~GtPlotSelection(void)
		{
			this->ClearSelection();
		};

		//!Add the index to the selection
		void GtPlotSelection::AddSelItem(GtPlotItem* item)
		{
			if(item)
			{
				this->m_arrPtrSelected.push_back(item);
			}
			return;
		};
		//!Remove the index from the selection
		void GtPlotSelection::RemoveSelItem(GtPlotItem* item)
		{
			size_t i, numItems;
			numItems = m_arrPtrSelected.size();
			if(numItems <= 0){return;}

			for(i = 0; i < numItems; i++)
			{
				GtPlotItem* ptrCurr = m_arrPtrSelected.at(i);
				if(ptrCurr)
				{
					if(*ptrCurr == *item)
					{
						//then match, erase
						m_arrPtrSelected.erase(i);
						return;
					}
				};
			};
			return;
		};

		//!Sorts the selection in ascending order (col, row, page order)
		void GtPlotSelection::SortSelection(void)
		{
			//SortPlotListItems(&m_arrPtrSelected);
		};
		//!Clears the selection
		void GtPlotSelection::ClearSelection(void)
		{
			m_arrPtrSelected.clear();
		};

		//QUERYING METHODS//////////////////////////////////
					//!Selection Size
		long GtPlotSelection::Count(void)
		{
			return m_arrPtrSelected.size();
		}
		//!Does the selection have any items
		bool GtPlotSelection::HasSelection(void)
		{
			return (m_arrPtrSelected.size() > 0);
		};

		//!Is the index of interest selected
		bool GtPlotSelection::IsSelected(GtPlotItem* item)
		{
			size_t i, numItems;
			numItems = m_arrPtrSelected.size();
			if(numItems <= 0){return false;};
			if(!item){return false;};

			for(i = 0; i < numItems; i++)
			{
				GtPlotItem* ptrCurr = m_arrPtrSelected.at(i);
				if(ptrCurr)
				{
					if(ptrCurr == item)
					{
						return true;
					}
				};
			};
			return false;
		};


	};//end namespace GtCore

};//end namespace GT