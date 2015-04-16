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

#include ".\GtTableRow.h"
#include ".\GtTableColumn.h"
#include ".\GtTableView.h"

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtTableRow::GtTableRow(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtTableRow";
			m_lngRow = -1;
			m_intHeight = 25;
		};
		//virtual destructor
		GtTableRow::~GtTableRow(void)
		{

		};	

		//!Get the cell at column index
		GtTableModelIndex* GtTableRow::GetCellPtr(int colIndex)
		{
			size_t i,numCells;
			numCells = m_arrCells.size();
			for(i = 0; i < numCells; i++)
			{
				GtTableModelIndex* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					long testCol = ptrCurr->m_lngCol;
					if(testCol == colIndex)
					{
						return ptrCurr;
					}
				}
			}
			//didnt find the index
			return NULL;
		};
		//!The number of cells
		long GtTableRow::CountCells(void)
		{
			return m_arrCells.size();
		};
		//!Gather cells from the TableView
		void GtTableRow::ResetCellMembers(void)
		{
			//clear the existing set
			this->m_arrCells.clear();

			GtTableView* ptrTable = dynamic_cast<GtTableView*>(m_ptrParent);
			if(!ptrTable){return;};//safety check
			//get the cells with this row
			size_t i,numCells;
			numCells = ptrTable->CountCells();
			if(numCells <= 0){return;};//safety check
			for(i = 0; i < numCells; i++)
			{
				GtTableModelIndex* ptrCurr = ptrTable->GetCellPtr(i);
				if(ptrCurr)
				{
					long testRow = ptrCurr->m_lngRow;
					if(testRow == this->m_lngRow)
					{//match add it
						m_arrCells.push_back(ptrCurr);
					}
				}
			}
			return;
		};


	};//end namespace GtCore

};//end namespace GT