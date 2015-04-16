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


#ifndef GT_TREE_MODEL_INDEX_H
#define GT_TREE_MODEL_INDEX_H

#include ".\GtItemEnums.h"
#include <modHtlContainer.h>
#include "..\modGtGeometry.h"
#include "..\GtGraphic\GtColor.h"
using namespace HTL;



namespace GT
{
	namespace GtCore
	{
		class GtObject;
		class GtTreeItemModel;
		class GtTreeModelIndex;

		typedef bool(*BoolIndexComparator)(GtTreeModelIndex*,GtTreeModelIndex*);
		typedef StlVector<GtTreeModelIndex*,HtlUnknownType> GtTreeIndexColl;
		typedef StlVector<GtTreeModelIndex*,HtlUnknownType>::StlIterator GtTreeIndexIter;

		struct HTL_DLLAPI GtTreeData
		{
		public:
			GtTreeData()
			{
				m_ptrData = NULL;
			};
			//Assignment Operator Overload
			GtTreeData & operator = (GtTreeData & rhs)
			{
				if(&rhs != this)
				{
					m_strText = rhs.m_strText;
					//The pointer to the data object at that index
					m_ptrData = rhs.m_ptrData;
					//frame for the data
					m_objFrame = rhs.m_objFrame;
					//color for the cell
					m_objBackColor = rhs.m_objBackColor;
				}
				return *this;
			};

		public:
			std::wstring m_strText;
			//The pointer to the data object at that index
			void* m_ptrData;
			//frame for the data
			GtRectI m_objFrame;
			//color for the cell
			GtColor m_objBackColor;
		};

		class HTL_DLLAPI GtTreeModelIndex
		{
		public:
			//!Default Constructor
			GtTreeModelIndex();
			GtTreeModelIndex(GtTreeModelIndex & rhs);
			//!Destructor
			~GtTreeModelIndex();

			//Assignment Operator Overload
			GtTreeModelIndex & operator = (GtTreeModelIndex & rhs);
			bool operator == (const GtTreeModelIndex & rhs );
			bool operator != (const GtTreeModelIndex & rhs );
			bool operator < (const GtTreeModelIndex & rhs );
			bool operator > (const GtTreeModelIndex & rhs );
			bool operator <= (const GtTreeModelIndex & rhs );
			bool operator >= (const GtTreeModelIndex & rhs );
			//!does the node have children
			bool HasChildren(void){return (m_arrSubNodes.size() > 0);};
			//!Gather the child nodes from the model
			void GatherChildren(void);
			//!Sort the children by the comparator
			void SortChildren(void);
			//!Clear the model index
			void Clear(void);
			//reindex the node, this is a recursive function
			void ReIndexNode(long & lngRow, long lngLevel);

		public:
			std::string m_strText;
			//!The itemflags that indicate what features the model index has
			int m_itemFlag;
			//!boolean flag to indicate the data object has been modified
			bool m_blnModified;
			//!boolean flag to indicate that this model index has been expanded
			bool m_blnExpanded;
			//!boolean flag for visible
			bool m_blnVisible;
			//COORDINATES INFORMATION
			//!The row y coordinate
			long m_lngRow;	
			//!The column x coordinate
			long m_lngCol;
			//!The level or page z coordinate
			long m_lngLevel;
			//!The sub-row in a tree or embedded view
			long m_lngSubRow;
			//!Frame for the drawing
			GtRectI m_objFrame;
			//!The frame for the expand/ contract control
			GtRectI m_objCtrl;
			
			void* m_ptrData;
			//!The pointer to the parent model index
			GtTreeModelIndex* m_ptrParent;
			//!Pointer to the abstract item model
			GtTreeItemModel* m_ptrModel;

			//the columns of data for this tree node
			HtlListMap<Htl1DIndex,HtlUnknownType,GtTreeData,HtlUnknownType> m_arrData;

			//the collection of sub nodes
			Htl1DList<GtTreeModelIndex*,HtlUnknownType> m_arrSubNodes;


		};//end GtTreeModelIndex

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_H