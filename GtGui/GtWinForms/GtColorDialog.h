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

#ifndef GT_COLOR_DIALOG_H
#define GT_COLOR_DIALOG_H

#include "..\GtBasicControls\GtFrame.h"
#include <modGtEvent.h>
using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtColorDialog : public GtFrame
		{
		public:
			//!Parent set constructor
			GtColorDialog(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtColorDialog(void);

			//MEMBER VARIABLES////////////////////////
			//!Boolean flag for dialog is running
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objSelColor);
			//!Boolean flag for dialog is accepted
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnAccepted);
			//SIGNALS/////////////////////////////////
		public:
			//!Signal for accepting dialog
			HtlSignal00 Accepted;
			//!Signal for rejecting dialog
			HtlSignal00 Rejected;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//INHERITED FUNCTIONS FOR
			void Accept(void);
			void Reject(void);
			int Exec(void);
			void Close(void);
		protected:
			CHOOSECOLOR m_winSelColor;

			GtColor ColorRefToGtColor(COLORREF color);
		};//end GtColorDialog class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_COLOR_DIALOG_H

//BOOL WINAPI ChooseColor(
//  _Inout_  LPCHOOSECOLOR lpcc
//);
//
//typedef struct {
//  DWORD        lStructSize;
//  HWND         hwndOwner;
//  HWND         hInstance;
//  COLORREF     rgbResult;
//  COLORREF     *lpCustColors;
//  DWORD        Flags;
//  LPARAM       lCustData;
//  LPCCHOOKPROC lpfnHook;
//  LPCTSTR      lpTemplateName;
//} CHOOSECOLOR, *LPCHOOSECOLOR;
