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

#ifndef GT_STATUS_BAR_H
#define GT_STATUS_BAR_H

#include "..\GtGuiLibRefs.h"
#include ".\GtControlEnums.h"
#include <modGtGraphic.h>
#include <modGtGeometry.h>

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtStatusBar : public GtWidget
		{
		public:
			//!Parent set constructor
			GtStatusBar(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtStatusBar(void);

			//MEMBER VARIABLES////////////////////////

			//SIGNALS/////////////////////////////////
			HtlSignal00 MessageChanged;
		public:
			//MEMBER FUNCTIONS////////////////////////
			//!Display the message for the duration in milliseconds
			//msecs = 0 means display without timeout
			void SetMessage(std::string mess, int msecs);

		public:

			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:

		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H