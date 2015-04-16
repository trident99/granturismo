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

#include ".\GtGridColumn.h"

#include ".\GtGridCell.h"
#include ".\GtGridRow.h"
#include ".\GtGridView.h"

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtGridColumn::GtGridColumn(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtGridColumn";
			m_lngColumn = -1;
			m_intWidth = 50;
		};
		//virtual destructor
		GtGridColumn::~GtGridColumn(void)
		{

		};	

		//!Get the cell at column index
		GtGridCell* GtGridColumn::GetCellPtr(int rowIndex)
		{
			size_t i,numCells;
			numCells = m_arrCells.size();
			for(i = 0; i < numCells; i++)
			{
				GtGridCell* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					long testRow = ptrCurr->Get_lngRow();
					if(testRow == rowIndex)
					{
						return ptrCurr;
					}
				}
			}
			//didnt find the index
			return NULL;
		};
		//!The number of cells
		long GtGridColumn::CountCells(void)
		{
			return m_arrCells.size();
		};
		//!Gather cells from the GridView
		void GtGridColumn::ResetCellMembers(void)
		{
			//clear the existing set
			this->m_arrCells.clear();

			GtGridView* ptrGrid = dynamic_cast<GtGridView*>(m_ptrParent);
			if(!ptrGrid){return;};//safety check
			//get the cells with this row
			size_t i,numCells;
			numCells = ptrGrid->CountCells();
			if(numCells <= 0){return;};//safety check
			for(i = 0; i < numCells; i++)
			{
				GtGridCell* ptrCurr = ptrGrid->AtCellPtr(i);
				if(ptrCurr)
				{
					long testCol = ptrCurr->Get_lngColumn();
					if(testCol == this->m_lngColumn)
					{//match add it
						m_arrCells.push_back(ptrCurr);
					}
				}
			}
			return;
		};
		//FORMATTING
		//!Set cell backgrounds
		void GtGridColumn::SetBackggRound(GtBrush & brush)
		{
			size_t i, numCells;
			numCells = m_arrCells.size();
			for(i = 0; i < numCells; i++)
			{
				GtGridCell* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					ptrCurr->Set_objBackBrush(brush);
				}
			}
		};
		//!Set the cell foregrounds
		void GtGridColumn::SetForeggRound(GtBrush & brush)
		{
			size_t i, numCells;
			numCells = m_arrCells.size();
			for(i = 0; i < numCells; i++)
			{
				GtGridCell* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					ptrCurr->Set_objForeBrush(brush);
				}
			}
		};

	};//end namespace GtCore

};//end namespace GT