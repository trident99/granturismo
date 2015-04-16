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

#include <modGtEvent.h>

#include ".\GtGridCell.h"
#include ".\GtGridRow.h"
#include ".\GtGridColumn.h"
#include ".\GtGridView.h"

#include "..\GtBasicControls\GtCheckBox.h"
#include "..\GtBasicControls\GtComboBox.h"
#include "..\GtBasicControls\GtSpinBox.h"

namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtGridCell::GtGridCell(GtObject* ptrParent)
			: GtSimpleTextEdit(ptrParent)
		{
			m_strType = "GtGridCell";
			m_lngRow = 0;
			m_lngColumn = 0;
			//set flags
			m_blnEditable = true;
			m_blnNumeric = false;
			//set pointers
			m_ptrDelegate = NULL;
			m_ptrRow = NULL;
			m_ptrColumn = NULL;

			m_objBackBrush = GtBrush(GtColor(255,255,255));

		};
		//virtual destructor
		GtGridCell::~GtGridCell(void)
		{
			m_ptrDelegate = NULL;
			m_ptrRow = NULL;
			m_ptrColumn = NULL;
		};
		//conveinience functions for common delegates
		GtCheckBox* GtGridCell::GetCheckBox(void)
		{
			return dynamic_cast<GtCheckBox*>(m_ptrDelegate);
		};
		GtComboBox* GtGridCell::GetComboBox(void)
		{
			return dynamic_cast<GtComboBox*>(m_ptrDelegate);
		};
		GtSpinBox* GtGridCell::GetSpinBox(void)
		{
			return dynamic_cast<GtSpinBox*>(m_ptrDelegate);
		};
		//!returns the numeric value of the cell
		double GtGridCell::Get_dblValue(void)
		{
			double dblRet = 0.0f;
			sscanf(m_strText.c_str(),"%6.6f", &dblRet);
			return dblRet;
		};

		//!Get the pointer to the column we are in
		GtGridColumn* GtGridCell::GetColumnPtr(void)
		{
			//can only get a column if this cell is in a grid view
			GtGridView* grid = dynamic_cast<GtGridView*>(m_ptrParent);
			m_ptrColumn = grid->GetColumnPtr(m_lngColumn);
			return m_ptrColumn;
			
		};
		//!Get the pointer to the row we are in
		GtGridRow* GtGridCell::GetRowPtr(void)
		{
			//can only get a row if this cell is in a grid view
			GtGridView* grid = dynamic_cast<GtGridView*>(m_ptrParent);
			m_ptrRow = grid->GetRowPtr(m_lngRow);
			return m_ptrRow;
		};
		//!Start modification of the cell
		void GtGridCell::StartModify(void)
		{
			m_blnModifyCell = true;
		};
		//!End the modification of the cell
		void GtGridCell::EndModify(void)
		{
			m_blnModifyCell = false;
		};

		//!Custom Event Processing
		int GtGridCell::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};
			if(!m_blnEditable){return 0;};

			if(m_ptrDelegate == NULL)
			{//no delegate, have the cell handle it
				GtSimpleTextEdit::HandleEvent(ptrEvent);
				return 1;
			}

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				//if there is a delegate hover the delegate over the cell
				//and hand off event processing to it
				if((m_ptrDelegate)&&(!m_blnModifyCell))
				{
					m_ptrDelegate->Set_objFrame(m_objFrame);
					m_ptrDelegate->SetVisible(true);
					this->StartModify();
					m_ptrDelegate->HandleEvent(ptrEvent);
				}//end row delegate
			}
			if( (ptrEvent->m_objType == KeyPress)&&
				(ptrEvent->m_objKey == Key_Return ) )
			{
				//then finished editing
				if((m_ptrDelegate)&&(m_blnModifyCell))
				{
					m_ptrDelegate->Set_objFrame(m_objFrame);
					m_ptrDelegate->SetVisible(false);
					this->EndModify();
					return  1;
				}//end row delegate
				//if there is a delegate hover the delegate over the cell
			}

			//and hand off event processing to it
			if((m_ptrDelegate)&&(m_blnModifyCell))
			{
				//still modifying
				m_ptrDelegate->HandleEvent(ptrEvent);
			}//end row delegate

			return 0;
		};
		//!Custom Widget Painting
		int GtGridCell::OnPaint(GtPainter * painter)
		{
			//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen oldPen;
			GtBrush oldBrush;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();

			if(m_ptrDelegate == NULL)
			{
				GtSimpleTextEdit::OnPaint(painter);
			}else{
				//draw the delegate
				m_ptrDelegate->Set_objFrame(m_objFrame);
				m_ptrDelegate->OnPaint(painter);
			}

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};		

	};//end namespace GtGui

};//end namespace GT