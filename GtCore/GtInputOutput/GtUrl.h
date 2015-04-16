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


#ifndef GT_URL_H
#define GT_URL_H

#include "..\GtCoreLibRefs.h"
#include "..\GtCoreEnums.h"
#include <modHtlString.h>
#include <modHtlContainer.h>

using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		typedef Htl1DList<HtlString,HTL_STRING> HtlStringList;
		typedef std::vector<std::string> StlStringList;
		typedef std::vector<std::wstring> StlWStringList;

		/* WINDOWS STRINGS
		LPSTR = char*
		LPCSTR = const char*
		LPWSTR = wchar_t*
		LPCWSTR = const wchar_t*
		LPTSTR = char* or wchar_t* depending on _UNICODE
		LPCTSTR = const char* or const wchar_t* depending on _UNICODE
		*/



		class HTL_DLLAPI GtUrl
		{
		public:
			//!Default Constructors
			GtUrl(void);
			//copy constructor
			GtUrl(GtUrl & rhs);

			//!Destructor
			~GtUrl();

			//!Assignment Operator
			GtUrl &	operator=(GtUrl & rhs);
			//!Equal Operator
			bool operator==(GtUrl & rhs) const;	
			//!Not Equal Operator
			bool operator!=(GtUrl & rhs) const;

			//!The full file path without the file name
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strUrl);
			//!The user name for the website
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strUserName);
			//!The password for the website
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strPassword);
			//!The host name for the website
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strHostName);
			//!The port for the website
			HTLMEMVAR_BYVAL_STYLE1(public, int, intPort);
			//!The SQL Query for the website
			HTLMEMVAR_BYREF_STYLE1(public, std::string, strSQLQuery);
			//!clears the URL
			void Clear(void);

		};//end GtUrl

	};//end namespace GtCore

};//end namespace GT

#endif