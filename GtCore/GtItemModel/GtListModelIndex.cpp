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

#include ".\GtListModelIndex.h"
#include ".\GtListItemModel.h"
#include <modHtlArchive.h>

namespace GT
{
	namespace GtCore
	{

		//!Default Constructor
		GtListModelIndex::GtListModelIndex()
		{
			this->Clear();
		};
		GtListModelIndex::GtListModelIndex(const GtListModelIndex & rhs)
		{
			m_strText = rhs.m_strText;
			m_itemFlag = rhs.m_itemFlag;
			m_blnModified = rhs.m_blnModified;
			m_lngRow = rhs.m_lngRow;
			m_ptrData = rhs.m_ptrData;
			m_ptrModel = rhs.m_ptrModel;
			return;
		};
		//!Destructor
		GtListModelIndex::~GtListModelIndex()
		{
			this->Clear();
		};

		//Assignment Operator Overload
		GtListModelIndex & GtListModelIndex::operator = (const GtListModelIndex & rhs)
		{
			if(&rhs != this)
			{
				m_strText = rhs.m_strText;
				m_itemFlag = rhs.m_itemFlag;
				m_blnModified = rhs.m_blnModified;
				m_lngRow = rhs.m_lngRow;
				m_ptrData = rhs.m_ptrData;
				m_ptrModel = rhs.m_ptrModel;
			}
			return (*this);
		};
		bool GtListModelIndex::operator == (const GtListModelIndex & rhs )
		{
			if(m_lngRow != rhs.m_lngRow){return false;};
			return true;
		};
		bool GtListModelIndex::operator != (const GtListModelIndex & rhs )
		{
			if(m_lngRow != rhs.m_lngRow){return true;};
			return false;
		};
		bool GtListModelIndex::operator < (const GtListModelIndex & rhs )
		{
			if(m_lngRow < rhs.m_lngRow){return true;};
			return false;
		};
		bool GtListModelIndex::operator > (const GtListModelIndex & rhs )
		{
			if(m_lngRow > rhs.m_lngRow){return true;};
			return false;
		};
		bool GtListModelIndex::operator <= (const GtListModelIndex & rhs )
		{
			if(m_lngRow <= rhs.m_lngRow){return true;};
			return false;
		};
		bool GtListModelIndex::operator >= (const GtListModelIndex & rhs )
		{
			if(m_lngRow >= rhs.m_lngRow){return true;};
			return false;
		};

		void GtListModelIndex::Clear(void)
		{
			m_strText.clear();
			m_itemFlag = NoItemFlags;
			m_blnModified = false;
			m_blnVisible = true;
			m_lngRow = -1;//illegal index
			m_ptrData = NULL;
			m_ptrModel = NULL;
			return;
		};

	};//end namespace GtCore

};//end namespace GT