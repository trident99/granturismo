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


#ifndef GT_TABLE_MODEL_INDEX_H
#define GT_TABLE_MODEL_INDEX_H

#include ".\GtItemEnums.h"
#include "..\modGtGeometry.h"
#include <modHtlContainer.h>
using namespace HTL;



namespace GT
{
	namespace GtCore
	{
		class GtObject;
		class GtTableItemModel;
		class GtTableModelIndex;

		typedef bool(*BoolTableIndexComp)(GtTableModelIndex*,GtTableModelIndex*);
		typedef Htl1DVector<GtTableModelIndex*,HtlUnknownType> GtTableIndexColl;
		typedef Htl1DVector<GtTableModelIndex*,HtlUnknownType>::Iterator GtTableIndexIter;

		class HTL_DLLAPI GtTableModelIndex
		{
		public:
			//!Default Constructor
			GtTableModelIndex();
			GtTableModelIndex(GtTableModelIndex & rhs);
			//!Destructor
			~GtTableModelIndex();

			//Assignment Operator Overload
			GtTableModelIndex & operator = (GtTableModelIndex & rhs);
			bool operator == (const GtTableModelIndex & rhs );
			bool operator != (const GtTableModelIndex & rhs );
			bool operator < (const GtTableModelIndex & rhs );
			bool operator > (const GtTableModelIndex & rhs );
			bool operator <= (const GtTableModelIndex & rhs );
			bool operator >= (const GtTableModelIndex & rhs );

			//!Clear the model index
			void Clear(void);

		public:
			//This object is intended to be a struct so public member variables is acceptable
			std::string m_strText;
			//!boolean flag to indicate the data object has been modified
			bool m_blnModified;
			//boolean flage for visible
			bool m_blnVisible;
			//!The row y coordinate
			long m_lngRow;
			//!The column x coordinate
			long m_lngCol;
			//The pointer to the data object at that index
			void* m_ptrData;
			//!Pointer to the abstract item model
			GtTableItemModel* m_ptrModel;
			//!rect frame for the cell
			GtRectI m_objFrame;
		};//end GtTableModelIndex

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_H