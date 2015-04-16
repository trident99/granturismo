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
#include ".\SprocketTableModel.h"

int StringToWString(std::wstring &ws, const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

//!Default Constructor
SprocketTableModel::SprocketTableModel(GtObject* ptrParent)
:GtTableItemModel(ptrParent)
,m_ptrCollection(NULL)
{
	m_ptrCollection = NULL;
	this->UpdateSyncModel();
};
//!Destructor
SprocketTableModel::~SprocketTableModel()
{
	this->ClearCollectionPtr();
	this->UpdateSyncModel();		
};

//!Set the collection pointer being viewed
void SprocketTableModel::SetCollectionPtr(Htl2DArray<Sprocket*,HTL_BASE_PTR>*  ptrColl)
{
	if(ptrColl)
	{
		m_ptrCollection = ptrColl;
		this->UpdateSyncModel();
	}		
};
//!Clear the collection pointer to NULL
void SprocketTableModel::ClearCollectionPtr(void)
{
	m_ptrCollection = NULL;
	this->UpdateSyncModel();
};

//INHERITED REQUIRED MEMBER FUNCTIONS
//!Get the row count of the 
size_t SprocketTableModel::CountRows(void)
{
	int iLow,iHigh;
	if(!m_ptrCollection){return 0;};
	m_ptrCollection->GetParam1Range(iLow,iHigh);
	return (iHigh - iLow);
}; 

//!Get the column count of the model
size_t SprocketTableModel::CountColumns(void)
{
	int iLow,iHigh;
	if(!m_ptrCollection){return 0;};
	m_ptrCollection->GetParam2Range(iLow,iHigh);
	return (iHigh - iLow);
}; 
//!Get the data at the desired index
GtVariant SprocketTableModel::GetData(size_t row, size_t col)
{
	//all data for sprocket gotten through index in this case
	GtVariant objNull;
	return objNull;
};
//!Syncronize the Abstract Item Model with the real model
void SprocketTableModel::UpdateSyncModel(void)
{
	this->m_arrModel.clear();
	if(!m_ptrCollection){return;};
	size_t i, count;
	count = m_ptrCollection->size();
	if(count <= 0){return;}
	
	for(i = 0; i < count;i++)
	{
		Htl2DIndex index = m_ptrCollection->atkey(i);
		Sprocket* ptrCurr = m_ptrCollection->at(i);
		void* ptrInsert = (void*)ptrCurr;//need explicit cast to pass pointer by reference
		if(ptrCurr)
		{
			GtTableModelIndex key;
			key.m_lngRow = index.m_lngX;
			key.m_lngCol = index.m_lngY;
			key.m_ptrData = ptrCurr;
			//StringToWString(key.m_strText ,(ptrCurr->Get_strName()));
			key.m_strText = ptrCurr->Get_strName();
			m_arrModel.insert(key,ptrInsert);
		}
	}

};