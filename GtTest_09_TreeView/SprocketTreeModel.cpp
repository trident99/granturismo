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
#include ".\SprocketTreeModel.h"

int StringToWString(std::wstring &ws, const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

//!Default Constructor
SprocketTreeModel::SprocketTreeModel(GtObject* ptrParent)
:GtTreeItemModel(ptrParent)
,m_ptrCollection(NULL)
{
	m_ptrCollection = NULL;

};
//!Destructor
SprocketTreeModel::~SprocketTreeModel()
{
	this->ClearCollectionPtr();
	this->UpdateSyncModel();		
};

//!Set the collection pointer being viewed
void SprocketTreeModel::SetCollectionPtr(Htl1DList<Sprocket*,HTL_BASE_PTR>*  ptrColl)
{
	if(ptrColl)
	{
		m_ptrCollection = ptrColl;
		this->UpdateSyncModel();
	}		
};
//!Clear the collection pointer to NULL
void SprocketTreeModel::ClearCollectionPtr(void)
{
	m_ptrCollection = NULL;
	this->UpdateSyncModel();
};

//INHERITED REQUIRED MEMBER FUNCTIONS

//!Get the column count of the model
int SprocketTreeModel::CountColumns(void)
{
	return 3;
}; 
//!Get the data at the desired index
GtVariant SprocketTreeModel::GetData(size_t row, size_t col)
{
	//all data for sprocket gotten through index in this case
	GtVariant objNull;
	return objNull;
};
//!Syncronize the Abstract Item Model with the real model
void SprocketTreeModel::UpdateSyncModel(void)
{	
	//clear the old model
	m_objRootIndex.m_arrSubNodes.clear();
	this->DeleteAllIndexes();
	if(!m_ptrCollection){return;};
	size_t i, count;
	count = m_ptrCollection->size();
	if(count <= 0){return;}
	
	GtTreeModelIndex* parent = &m_objRootIndex;
	for(i = 0; i < count;i++)
	{
		Sprocket* ptrCurr = m_ptrCollection->at(i);
		if(ptrCurr)
		{
			GtTreeModelIndex* ptrNode = this->CreateIndex(this->Size(),0,ptrCurr);
			std::string strName;
			strName = ptrCurr->Get_strName();
			ptrNode->m_strText = strName;
			ptrNode->m_ptrData = (void*)ptrCurr;
			parent->m_arrSubNodes.push_back(ptrNode);
			ptrNode->m_ptrParent = parent;

			//LOAD CHILDREN
			ptrCurr->TreeLoadSprocket(this,ptrNode);
		}
		
	}
	//reindex model
	long lngRealRow = 0;
	m_objRootIndex.ReIndexNode(lngRealRow,0);
	return;
};