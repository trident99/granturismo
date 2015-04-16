/*
**	This String is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h String
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


#ifndef GT_String_INOUT_STREAM_H
#define GT_String_INOUT_STREAM_H

#include "..\GtCoreLibRefs.h"
#include "..\GtCoreEnums.h"

#include <sstream>
using namespace std;

namespace GT
{
	namespace GtCore
	{

		class HTL_DLLAPI GtStringInOutStream : public stringstream
		{
		public:
			//!Default Constructor
			GtStringInOutStream();

			//!Destructor
			~GtStringInOutStream();

			//operators input
			istream& operator>> (longlong & val);
			istream& operator>> (ulonglong & val);

			//operators output
			ostream& operator<< (longlong val);
			ostream& operator<< (ulonglong val);

		};//end GtStringInOutStream

	};//end namespace GtCore

};//end namespace GT

#endif//GT_String_INOUT_STREAM_H