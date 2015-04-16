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

namespace HTL
{
	Sprocket::Sprocket()
		:HtlBase()
	{
		m_strType = "Sprocket";
		m_objType = HTL_BASE;

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
	Sprocket::~Sprocket(void){};



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



};