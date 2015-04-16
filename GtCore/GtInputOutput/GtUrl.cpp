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

#include ".\GtUrl.h"

namespace GT
{
	namespace GtCore
	{

		//!Default Constructors
		GtUrl::GtUrl(void)
		{
			//do nothing
		};
		//copy constructor
		GtUrl::GtUrl(GtUrl & rhs)
		{
			m_strUrl = rhs.Get_strUrl();
			m_strUserName = rhs.Get_strUserName();
			m_strPassword = rhs.Get_strPassword();
			m_strHostName = rhs.Get_strHostName();
			m_intPort = rhs.Get_intPort();
			m_strSQLQuery = rhs.Get_strSQLQuery();	
		};

		//!Destructor
		GtUrl::~GtUrl()
		{
			this->Clear();	
		};

		//!Assignment Operator
		GtUrl &	GtUrl::operator=(GtUrl & rhs)
		{
			if(&rhs != this)//self assignement check
			{
				m_strUrl = rhs.Get_strUrl();
				m_strUserName = rhs.Get_strUserName();
				m_strPassword = rhs.Get_strPassword();
				m_strHostName = rhs.Get_strHostName();
				m_intPort = rhs.Get_intPort();
				m_strSQLQuery = rhs.Get_strSQLQuery();
			}
			return *this;
		};
		//!Equal Operator
		bool GtUrl::operator==(GtUrl & rhs) const
		{
			if(&rhs == this)//self assignement check
			{
				return true;
			}else{
				return (m_strUrl == rhs.Get_strUrl());
			};
			return false;
		};	
		//!Not Equal Operator
		bool GtUrl::operator!=(GtUrl & rhs) const
		{
			if(&rhs == this)//self assignement check
			{
				return false;
			}else{
				return (m_strUrl != rhs.Get_strUrl());
			};
			return true;		
		};

		//!clears the URL
		void GtUrl::Clear(void)
		{
			m_strUrl.clear();
			m_strUserName.clear();
			m_strPassword.clear();
			m_strHostName.clear();
			m_intPort = 0;
			m_strSQLQuery.clear();

		};


	};//end namespace GtCore

};//end namespace GT