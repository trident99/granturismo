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


#ifndef GT_LIST_MODEL_INDEX_H
#define GT_LIST_MODEL_INDEX_H

#include ".\GtItemEnums.h"
#include "..\modGtGeometry.h"
#include <modHtlContainer.h>
using namespace HTL;



namespace GT
{
	namespace GtCore
	{
		class GtObject;
		class GtListItemModel;
		class GtListModelIndex;

		typedef bool(*BoolListIndexComp)(GtListModelIndex*,GtListModelIndex*);
		typedef Htl1DVector<GtListModelIndex*,HtlUnknownType> GtListIndexColl;
		typedef Htl1DVector<GtListModelIndex*,HtlUnknownType>::Iterator GtListIndexIter;

		class HTL_DLLAPI GtListModelIndex
		{
		public:
			//!Default Constructor
			GtListModelIndex();
			GtListModelIndex(const GtListModelIndex & rhs);
			//!Destructor
			~GtListModelIndex();

			//Assignment Operator Overload
			GtListModelIndex & operator = (const GtListModelIndex & rhs);
			bool operator == (const GtListModelIndex & rhs );
			bool operator != (const GtListModelIndex & rhs );
			bool operator < (const GtListModelIndex & rhs );
			bool operator > (const GtListModelIndex & rhs );
			bool operator <= (const GtListModelIndex & rhs );
			bool operator >= (const GtListModelIndex & rhs );
			//!Clear the model index
			void Clear(void);

		public:
			//This object is intended to be a struct so public member variables is acceptable
			std::string m_strText;
			//!The itemflags that indicate what features the model index has
			int m_itemFlag;
			//!boolean flag to indicate the data object has been modified
			bool m_blnModified;
			//!boolean flag for visible
			bool m_blnVisible;
			//!The row i coordinate
			long m_lngRow;
			//The pointer to the data object at that index
			void* m_ptrData;
			//!Pointer to the abstract item model
			GtListItemModel* m_ptrModel;
			//!rect frame for the cell
			GtRectI m_objFrame;

		};//end GtModelIndex

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_H