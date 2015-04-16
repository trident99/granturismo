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
#include ".\SprocketListModel.h"


int StringToWString(std::wstring &ws, const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

//!Default Constructor
SprocketListModel::SprocketListModel(GtObject* ptrParent)
:GtListItemModel(ptrParent)
,m_ptrCollection(NULL)
{
	m_ptrCollection = NULL;

};
//!Destructor
SprocketListModel::~SprocketListModel()
{
	this->ClearCollectionPtr();
	this->UpdateSyncModel();		
};

//!Set the collection pointer being viewed
void SprocketListModel::SetCollectionPtr(Htl1DList<Sprocket*,HTL_BASE_PTR>*  ptrColl)
{
	if(ptrColl)
	{
		m_ptrCollection = ptrColl;
		this->UpdateSyncModel();
	}		
};
//!Clear the collection pointer to NULL
void SprocketListModel::ClearCollectionPtr(void)
{
	m_ptrCollection = NULL;
	this->UpdateSyncModel();
};

//INHERITED REQUIRED MEMBER FUNCTIONS
//!Get the row count of the 
size_t SprocketListModel::CountRows(void)
{
	if(!m_ptrCollection){return 0;};
	return m_ptrCollection->size();
}; 
//!Get the data at the desired index
GtVariant SprocketListModel::GetData(size_t row)
{
	//all data for sprocket gotten through index in this case
	GtVariant objNull;
	return objNull;
};

void SprocketListModel::ClearModel(void)
{
	GtListMapIter iter;
	int i, numItems;
	numItems = m_arrModel.size();
	for (iter = m_arrModel.begin(); iter != m_arrModel.end();)
	{
		(*iter).m_objData = NULL;
		iter = iter->m_ptrNext;
	}
	this->m_arrModel.clear();
};


//!Syncronize the Abstract Item Model with the real model
void SprocketListModel::UpdateSyncModel(void)
{
	this->ClearModel();
	if(!m_ptrCollection){return;};
	size_t i, num;
	num = m_ptrCollection->size();
	for(i = 0; i < num;i++)
	{
		Sprocket* ptrCurr = m_ptrCollection->at(i);
		void* ptrInsert = (void*)ptrCurr;//need explicit cast to pass pointer by reference
		if(ptrCurr)
		{
			GtListModelIndex key;
			key.m_lngRow = i;
			key.m_ptrData = m_ptrCollection->at(i);
			//StringToWString(key.m_strText ,(ptrCurr->Get_strName()));
			key.m_strText = ptrCurr->Get_strName();
			m_arrModel.insert(key,ptrInsert);

		}
	}

};