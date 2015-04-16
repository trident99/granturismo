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

#include ".\GtColorDialog.h"
#include <modGtProcess.h>
#include <modGtGraphic.h>
namespace GT
{
	namespace GtGui
	{

		//default constructor
		GtColorDialog::GtColorDialog(GtObject* ptrParent)
			: GtFrame(ptrParent)
		{
			m_strType = "GtColorDialog";
			m_strText = "GtColorDialog";

		};
		//virtual destructor
		GtColorDialog::~GtColorDialog(void)
		{
		
		};


			//!Accepting Dialog
		void GtColorDialog::Accept(void )
		{
			m_blnAccepted = true;
			this->Accepted.Emit();
			this->Close();
			return;
		};
		//!Rejecting Dialog
		void GtColorDialog::Reject(void)
		{
			m_blnAccepted = false;
			this->Rejected.Emit();
			this->Close();
			return;
		}; 
		//!Execute the Dialog
		int GtColorDialog::Exec(void)
		{
			m_blnAccepted = ::ChooseColor(&m_winSelColor);

			if(m_blnAccepted)
			{
				this->Accept();
				this->ColorRefToGtColor(m_winSelColor.rgbResult);
				return 1;
			}else{
				this->Reject();
				return 0;
			}
			return 0;
		}
		//!Execute the Dialog
		void GtColorDialog::Close(void)
		{
			m_objSelColor.SetRGB(0,0,0);
			memset(&m_winSelColor,0,sizeof(CHOOSECOLOR));
		}

		GtColor GtColorDialog::ColorRefToGtColor(COLORREF color)
		{
			byte red = GetRValue(color);
			byte green = GetGValue(color);
			byte blue = GetBValue(color);
			m_objSelColor.SetRGB(red,green,blue);
			return m_objSelColor;
		};


	};//end namespace GtCore

};//end namespace GT