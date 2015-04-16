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

#ifndef GT_EXCEPTION_H
#define GT_EXCEPTION_H

#include "..\GtCoreLibRefs.h"


namespace GT
{
	namespace GtCore
	{
				//!This is the base object that provides signals slots capability as well as a global unique identifier for the object.
		/*!
		This is the base object that provides signals slots capability as well as a
		global unique identifier for the object. It inherits the HtlBase serialization engine
		*/
		class HTL_DLLAPI GtException
		{
		public:
			//!Parent set constructor
			GtException(char* chrFile, ulong lngLine, char* chrMethod, char * chrMessage);
			//!Virtual destructor
			virtual ~GtException();

			//operator overloads
			GtException & operator= ( GtException & rhs);


		public:

			//!string file name
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strFile);
			//!line number of error
			HTLMEMVAR_BYREF_STYLE1(public, ulong, lngLine);
			//!pointer to the parent Node
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strMethod);
			//!pointer to the parent Node
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strMessage);

		};//end class QException

	};//end namespace GtCore
};//end namespace GT

#endif//GT_EXCEPTION_H