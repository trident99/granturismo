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

#ifndef GT_CHECK_BOX_H
#define GT_CHECK_BOX_H

#include ".\GtButton.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtCheckBox : public GtButton
		{
		public:
			//!Parent set constructor
			GtCheckBox(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtCheckBox(void);

			//MEMBER VARIABLES////////////////////////
			//!Accessors for blnChecked
			bool Get_blnChecked(void){return m_blnChecked;};
			void Set_blnChecked(bool isChecked);


			//SIGNALS/////////////////////////////////
		public:

			//MEMBER FUNCTIONS////////////////////////
		public:
			
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);	

		protected:
			//!Boolean flag for checkbox is checked
			bool m_blnChecked;
			//!The box for the check
			GtRectI m_rectCheck;

		};//end GtButton class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_CHECK_BOX_H