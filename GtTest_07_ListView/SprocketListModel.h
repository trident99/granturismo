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


#ifndef GT_SPROCKET_LIST_MODEL_H
#define GT_SPROCKET_LIST_MODEL_H

#include <modGtItemModel.h>
#include ".\Sprocket.h"
using namespace HTL;
using namespace GT::GtCore;

class SprocketListModel: public GtListItemModel
{
public:
	//!Default Constructor
	SprocketListModel(GtObject* ptrParent = NULL);
	//!Destructor
	virtual ~SprocketListModel();
	
	//!Set the collection pointer being viewed
	void SetCollectionPtr(Htl1DList<Sprocket*,HTL_BASE_PTR>*  ptrColl);
	//!Clear the collection pointer to NULL
	void ClearCollectionPtr(void);

	//INHERITED REQUIRED MEMBER FUNCTIONS
	//!Get the row count of the 
	virtual size_t CountRows(void); 
	//!Get the data at the desired index
	virtual GtVariant GetData(size_t row);
	//!Syncronize the Abstract Item Model with the real model
	virtual void UpdateSyncModel(void);

	void ClearModel(void);


protected:

	Htl1DList<Sprocket*,HTL_BASE_PTR> * m_ptrCollection;

};//end GtAbstractItemModel


#endif//GT_SPROCKET_LIST_MODEL_H