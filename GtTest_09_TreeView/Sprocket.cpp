/*
The High Performance Template Library is a Licensed as LGPL.
It is intended to provide a base object Testitecture, with
Serialization, thread control, etc.  
It is based on a merger of QT, BOOST, STL, and SigSlots.
License information is in the HtlLicense.h file
October 2012
*/
//#pragma once
//#pragma warning(push)
//#pragma warning (disable : 4005 ) /* macro redefinition */
//#define HTL_DLLEXPORT
//#pragma warning(pop)

#include ".\Sprocket.h"
#include <modHtlArchive.h>
#include <modGtMath.h>

namespace HTL
{

	Sprocket::Sprocket(Sprocket* parent)
		:HtlBase()
	{
		m_strType = "Sprocket";
		m_objType = HTL_BASE;

		m_ptrParent = parent;

		m_blnTest =false;
		m_shrtVar01 = 0;
		m_ushrtVar02 = 0;
		m_intVar03 = 0;
		m_uintVar04 = 0;
		m_lngVar05 = 0;
		m_ulngVar06 = 0;
		m_sngVar07 = 0.0f;
		m_dblVar08 = 0.0f;
	};

	//virtual destructor
	Sprocket::~Sprocket(void)
	{
		this->DeleteAllSprockets();
	}

	HtlUniform* Sprocket::GetRNGPtr(void)
	{
		return &m_objRNG;
	};

	Sprocket &	Sprocket::operator= ( Sprocket & ptrRHS )
	{
		m_strName = ptrRHS.Get_strName();
		m_blnTest = ptrRHS.Get_blnTest();
		m_shrtVar01 = ptrRHS.Get_shrtVar01();
		m_ushrtVar02 = ptrRHS.Get_ushrtVar02();
		m_intVar03 = ptrRHS.Get_intVar03();
		m_uintVar04 = ptrRHS.Get_uintVar04();
		m_lngVar05 = ptrRHS.Get_lngVar05();
		m_ulngVar06 = ptrRHS.Get_ulngVar06();
		m_sngVar07 = ptrRHS.Get_sngVar07();
		m_dblVar08 = ptrRHS.Get_dblVar08();
		return *this;
	};



	//Virtual Inheritance Serialization Engines
	//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
	int Sprocket::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
		//Standard Member Variables
		intReturn &= SetHtlMemVar<std::string,STL_STRING>(ptrCurrNode,"m_strName",m_strName,blnWithSubObjects);
		intReturn &= SetHtlMemVar<bool,CPP_BOOL>(ptrCurrNode,"m_blnTest",m_blnTest,blnWithSubObjects);
		intReturn &= SetHtlMemVar<short,CPP_SHORT>(ptrCurrNode,"m_shrtVar01",m_shrtVar01,blnWithSubObjects);
		intReturn &= SetHtlMemVar<ushort,CPP_USHORT>(ptrCurrNode,"m_ushrtVar02",m_ushrtVar02,blnWithSubObjects);
		intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intVar03",m_intVar03,blnWithSubObjects);
		intReturn &= SetHtlMemVar<uint,CPP_UINT>(ptrCurrNode,"m_uintVar04",m_uintVar04,blnWithSubObjects);
		intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"m_lngVar05",m_lngVar05,blnWithSubObjects);
		intReturn &= SetHtlMemVar<ulong,CPP_ULONG>(ptrCurrNode,"m_ulngVar06",m_ulngVar06,blnWithSubObjects);
		intReturn &= SetHtlMemVar<float,CPP_FLOAT>(ptrCurrNode,"m_sngVar07",m_sngVar07,blnWithSubObjects);
		intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblVar08",m_dblVar08,blnWithSubObjects);
		//Sub Object Member Variables
		if(blnWithSubObjects)
		{
			/*...*/
		};

		return intReturn;


	};

	int Sprocket::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
	{

		int intReturn = 0;
		//SAFETY CHECK //put at top of all Serialize Methods
		if(!ptrCurrNode){return 0;};
		//CALL PARENT CLASS Serialize()
		/*...*/
		HtlBase::Load(ptrCurrNode,strMemVarName);
		//Standard Member Variables
		intReturn &= GetHtlMemVar<std::string,STL_STRING>(ptrCurrNode,"m_strName",m_strName);
		intReturn &= GetHtlMemVar<bool,CPP_BOOL>(ptrCurrNode,"m_blnTest",m_blnTest);
		intReturn &= GetHtlMemVar<short,CPP_SHORT>(ptrCurrNode,"m_shrtVar01",m_shrtVar01);
		intReturn &= GetHtlMemVar<ushort,CPP_USHORT>(ptrCurrNode,"m_ushrtVar02",m_ushrtVar02);
		intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intVar03",m_intVar03);
		intReturn &= GetHtlMemVar<uint,CPP_UINT>(ptrCurrNode,"m_uintVar04",m_uintVar04);
		intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"m_lngVar05",m_lngVar05);
		intReturn &= GetHtlMemVar<ulong,CPP_ULONG>(ptrCurrNode,"m_ulngVar06",m_ulngVar06);
		intReturn &= GetHtlMemVar<float,CPP_FLOAT>(ptrCurrNode,"m_sngVar07",m_sngVar07);
		intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblVar08",m_dblVar08);
		return intReturn;

	};

	//!Use the random number generator to populate this sprocket's data
	void Sprocket::GenerateData(void)
	{
		
		char buf[24];
		sprintf(buf,"SPKT %04d",GetRNGPtr()->intNextAB(0,255));
		std::string strName = buf;
		this->Set_strName(strName);
		this->Set_shrtVar01(GetRNGPtr()->intNextAB(0,255));
		this->Set_intVar03(GetRNGPtr()->intNextAB(0,32000));
		this->Set_sngVar07(GetRNGPtr()->dblNextAB(0.0f,10.0f));
		this->Set_blnTest(gRound(GetRNGPtr()->intNextAB(0,1)));

	};
	//!Randomly Generate the Sprockets for this level
	void Sprocket::GenerateSprockets(int level, int levelMax)
	{
		//find out how many sprockets to generate 2 - 5
		int num = GetRNGPtr()->intNextAB(2,5);
		int i;
		//check the depth
		level += 1;
		if(level > levelMax){return;}
		//cleared to make sub sprockets
		for(i = 0; i < num ; i++)
		{
			Sprocket* ptrNew = new Sprocket(this);
			ptrNew->GenerateData();
			ptrNew->GenerateSprockets(level, levelMax);
			m_arrSprockets.push_back(ptrNew);
		}
	};
	//!Delete all the sprockets from the sub collection
	void Sprocket::DeleteAllSprockets(void)
	{
		int i, num;
		num = m_arrSprockets.size();
		for(i = 0; i < num; i++)
		{
			Sprocket * ptrCurr = m_arrSprockets.at(i);
			delete ptrCurr;
		}
		m_arrSprockets.clear();
	};


	void Sprocket::TreeLoadSprocket(GtTreeItemModel* ptrModel,GtTreeModelIndex * parent)
	{
		if(!ptrModel){return;};
		//make a node for each sprocket in collection;
		//assume this node already in the
		int i, num;
		num = m_arrSprockets.size();
		for(i = 0; i < num;i++)
		{
			Sprocket* ptrCurr = m_arrSprockets.at(i);
			if(ptrCurr)
			{
				GtTreeModelIndex* ptrNode = ptrModel->CreateIndex(ptrModel->Size(),0,m_arrSprockets.at(i));
				std::string strName;
				strName = ptrCurr->Get_strName();
				ptrNode->m_strText = strName;
				ptrNode->m_ptrData = (void*)ptrCurr;
				parent->m_arrSubNodes.push_back(ptrNode);
				ptrNode->m_ptrParent = parent;

				//LOAD CHILDREN
				ptrCurr->TreeLoadSprocket(ptrModel,ptrNode);
			}
		}
	};

};