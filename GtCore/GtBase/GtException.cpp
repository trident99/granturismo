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

#include ".\GtException.h"

namespace GT
{
	namespace GtCore
	{

		/*
		samples for outputing exceptions
		printf ("__FILE__ = %s\n", __FILE__);
		printf ("__LINE__ = %d\n", __LINE__);
		printf ("__FUNCTION__ = %s\n", __FUNCTION__);
		printf ("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__);
		*/

		//!Parent set constructor
		GtException::GtException(char* chrFile, ulong lngLine, char* chrMethod, char * chrMessage)
		{
			this->m_strFile = chrFile;
			this->m_strMethod = chrMethod;
			this->m_strMessage = chrMessage;
			this->m_lngLine = lngLine;
		};

		//!Virtual destructor
		GtException::~GtException()
		{
			this->m_strFile.clear();
			this->m_strMethod.clear();
			this->m_strMessage.clear();
			this->m_lngLine = -1;	

		};

		//Assignment Operator
		GtException & GtException::operator= ( GtException & rhs)
		{

			this->m_strFile = rhs.Get_strFile();
			this->m_strMethod = rhs.Get_strMethod();
			this->m_strMessage = rhs.Get_strMessage();
			this->m_lngLine = rhs.Get_lngLine();	
			return *this;

		};

	};//end namespace GtCore

};//end namespace GT