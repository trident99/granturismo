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

#ifndef GT_FLOATING_DIALOG_H
#define GT_FLOATING_DIALOG_H

#include <GtWinForms\GtDialog.h>

namespace GT
{
	namespace GtOpenGL
	{

		class GtViewport;

		class GtFloatingDialog : public GtDialog
		{
		public:
			GtFloatingDialog(GtObject* ptrParent = NULL);
			~GtFloatingDialog();

			void Set_ptrViewport(GtViewport* ptrViewport);
			GtViewport* Get_ptrViewport(void);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
		protected:
			virtual void OnCloseEvent( GtEvent * ptrEvent = NULL) {return;};
			virtual void OnResizeEvent ( GtEvent * ptrEvent = NULL);
			virtual void OnKeyPressEvent ( GtEvent * ptrEvent = NULL);
		private:
			//pointer to the TGL Viewport
			GtViewport * m_ptrGtView;
		};
	};//end namespace GtOpenGL
};//end namespace TGL
#endif // TGLFLOATINGDIALOG_H
