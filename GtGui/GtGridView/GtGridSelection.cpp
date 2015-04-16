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

#include ".\GtGridSelection.h"

#include ".\GtGridCell.h"
#include ".\GtGridRow.h"
#include ".\GtGridColumn.h"
#include ".\GtGridView.h"

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtGridSelection::GtGridSelection(GtObject* ptrParent)
			: GtObject(ptrParent)
		{
			m_strType = "GtGridSelection";
			m_ptrGrid = NULL;
			m_intLRow = -1;
			m_intHRow = -1;
			m_intLCol = -1;
			m_intHCol = -1;
		};
		//virtual destructor
		GtGridSelection::~GtGridSelection(void)
		{
			this->ClearSelection();
			m_ptrGrid = NULL;
		};	
		//!Copy Constructor
		GtGridSelection::GtGridSelection(const GtGridSelection& rhs)
		{
			
		};
		//!Assignment Operator
		GtGridSelection & GtGridSelection::operator= ( GtGridSelection & rhs)
		{
			return *this;
			
		};

		//!Get of number of cells
		long GtGridSelection::CountCells(void)
		{
			return m_arrCells.size();
		};

		long GtGridSelection::CountRows(void)
		{
			size_t i, num;
			num = m_arrCells.size();
			if(num <= 0){return 0;};//nothing to do
			GtGridCell* ptrCurr = m_arrCells.at(0);
			if(ptrCurr)
			{
				m_intLRow = ptrCurr->Get_lngRow();
				m_intHRow = ptrCurr->Get_lngRow();
			}else{
				return 0;//invalid first cell, bad selection
			}

			for(i = 0; i < num; i++)
			{
				GtGridCell* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					if(m_intLRow < ptrCurr->Get_lngRow())
					{
						m_intLRow = ptrCurr->Get_lngRow();
					}
					if(m_intHRow > ptrCurr->Get_lngRow())
					{
						m_intHRow = ptrCurr->Get_lngRow();
					}
				}//end cell check
			}//end loop through cells
			//initialize
			int numRows = m_intHRow - m_intLRow;
			return numRows;	
		};

		long GtGridSelection::CountColumns(void)
		{
			//initialize
			size_t i, num;
			num = m_arrCells.size();
			if(num <= 0){return 0;};//nothing to do
			GtGridCell* ptrCurr = m_arrCells.at(0);
			if(ptrCurr)
			{
				m_intLCol = ptrCurr->Get_lngColumn();
				m_intHCol = ptrCurr->Get_lngColumn();
			}else{
				return 0;//invalid first cell, bad selection
			}

			for(i = 0; i < num; i++)
			{
				GtGridCell* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					if(m_intLCol < ptrCurr->Get_lngColumn())
					{
						m_intLCol = ptrCurr->Get_lngColumn();
					}
					if(m_intHCol > ptrCurr->Get_lngColumn())
					{
						m_intHCol = ptrCurr->Get_lngColumn();
					}
				}//end cell check
			}//end loop through cells
			//initialize
			int numCols = m_intHCol - m_intLCol;
			return numCols;
		};

		void GtGridSelection::GetRange(int & lRow,int & hRow, int & lCol, int & hCol)
		{
			//initialize
			lRow = m_intLRow = 0;
			hRow = m_intHRow = 0;
			lCol = m_intLCol = 0;
			hCol = m_intHCol = 0;

			size_t i, num;
			num = m_arrCells.size();
			if(num <= 0){return;};//nothing to do
			GtGridCell* ptrCurr = m_arrCells.at(0);
			if(ptrCurr)
			{
				m_intLRow = ptrCurr->Get_lngRow();
				m_intHRow = ptrCurr->Get_lngRow();
				m_intLCol = ptrCurr->Get_lngColumn();
				m_intHCol = ptrCurr->Get_lngColumn();
			}else{
				return;//invalid first cell, bad selection
			}

			for(i = 0; i < num; i++)
			{
				GtGridCell* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					if(m_intLRow < ptrCurr->Get_lngRow())
					{
						m_intLRow = ptrCurr->Get_lngRow();
					}
					if(m_intHRow > ptrCurr->Get_lngRow())
					{
						m_intHRow = ptrCurr->Get_lngRow();
					}
					if(m_intLCol < ptrCurr->Get_lngColumn())
					{
						m_intLCol = ptrCurr->Get_lngColumn();
					}
					if(m_intHCol > ptrCurr->Get_lngColumn())
					{
						m_intHCol = ptrCurr->Get_lngColumn();
					}
				}//end cell check
			}//end loop through cells
			//initialize
			lRow = m_intLRow;
			hRow = m_intHRow;
			lCol = m_intLCol;
			hCol = m_intHCol;
		};

		//!Get a cell by its index in the collection
		GtGridCell* GtGridSelection::GetCell(int index)
		{
				size_t i, num;
			num = m_arrCells.size();
			if(num <= 0){return NULL;};//nothing to do
			
			if((index >= 0) && (index < num))
			{
				GtGridCell* ptrCurr = m_arrCells.at(index);
				if(ptrCurr)
				{
					return ptrCurr;
				}
			}
			//didn't find it
			return NULL;
		};

		//!Get a cell by its row and column number
		GtGridCell* GtGridSelection::GetCell(int row, int col)
		{
			size_t i, num;
			num = m_arrCells.size();
			if(num <= 0){return NULL;};//nothing to do
			for(i = 0; i < num; i++)
			{
				GtGridCell* ptrCurr = m_arrCells.at(i);
				if(ptrCurr)
				{
					if((ptrCurr->Get_lngRow() == row)&&
						(ptrCurr->Get_lngColumn() == col) )
					{
						return ptrCurr;
					}
				}
			}
			//didn't find it
			return NULL;
		};

		//!Add Cell
		void GtGridSelection::AddCell(GtGridCell* ptrCell)
		{
			if(ptrCell)
			{
				m_arrCells.push_back(ptrCell);
			}
		};

		//!Add a range of cells
		void GtGridSelection::AddRangeCells(int lRow,int hRow, int lCol, int hCol)
		{
			//first safety checks
			if(!m_ptrGrid){return;};//no grid
			if((lRow< 0) || (lRow > hRow)){return;};//invalid index
			if((hRow< 0) || (hRow < lRow)){return;};//invalid index
			if((lCol< 0) || (lCol > hCol)){return;};//invalid index
			if((hCol< 0) || (hCol < lCol)){return;};//invalid index

			int i,j;
			for(i = lRow; i <= hRow; i++)
			{			
				for(j = lCol; j <= hCol; j++)
				{
					GtGridCell* ptrGet = m_ptrGrid->GetCellPtr(i,j);
					if(ptrGet)
					{
						this->AddCell(ptrGet);
					}
				}
			}
		};

		//!Clear the selection
		void GtGridSelection::ClearSelection(void)
		{
			m_intLRow = -1;
			m_intHRow = -1;
			m_intLCol = -1;
			m_intHCol = -1;
			m_arrCells.clear();
		};

	};//end namespace GtCore

};//end namespace GT