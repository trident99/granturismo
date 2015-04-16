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

#include  ".\GtAABox.h"
#include "..\GtMath\GtBasicMath.h"
using namespace GT;
using namespace GT::GtCore;

#include "modHtlArchive.h"
using namespace HTL;

namespace GT{
	namespace GtCore
	{

		GtAABox::GtAABox(void)
			: HtlBase()
		{
			//HtlBase Initialization
			m_strType = "GtAABox";
			//GtAABox Initialization////////////////////
			this->Zero();
			return;
		};

		GtAABox::GtAABox(    double dblXMin, double dblXMax,
			double dblYMin, double dblYMax,
			double dblZMin, double dblZMax)
			: HtlBase()
		{
			//HtlBase Initialization
			m_strType = "GtAABox";
			//set coordinates
			m_dblXMin = dblXMin;
			m_dblXMax = dblXMax;
			m_dblYMin = dblYMin;
			m_dblYMax = dblYMax;
			m_dblZMin = dblZMin;
			m_dblZMax = dblZMax;
		};

		GtAABox::GtAABox(const GtAABox& rhs)
			: HtlBase(rhs)
		{
			//HtlBase Initialization
			m_strType = "GtAABox";
			//GtAABox Initialization////////////////////
			m_dblXMin = rhs.m_dblXMin;
			m_dblXMax = rhs.m_dblXMax;
			m_dblYMin = rhs.m_dblYMin;
			m_dblYMax = rhs.m_dblYMax;
			m_dblZMin = rhs.m_dblZMin;
			m_dblZMax = rhs.m_dblZMax;

			return;
		};

		GtAABox & GtAABox::operator = (const GtAABox & rhs)
		{
			if(this != &rhs)
			{
				HtlBase::operator=(rhs);
				//HtlBase Initialization
				m_strType = "GtAABox";
				//GtAABox Initialization////////////////////
				m_dblXMin = rhs.m_dblXMin;
				m_dblXMax = rhs.m_dblXMax;
				m_dblYMin = rhs.m_dblYMin;
				m_dblYMax = rhs.m_dblYMax;
				m_dblZMin = rhs.m_dblZMin;
				m_dblZMax = rhs.m_dblZMax;
			}
			return *this;	
		};

		GtAABox::~GtAABox(void)
		{
			return;
		};

		bool GtAABox::operator == (GtAABox & rhs)
		{
			if(m_dblXMin != rhs.m_dblXMin){return false;};
			if(m_dblXMax != rhs.m_dblXMax){return false;};

			if(m_dblYMin != rhs.m_dblYMin){return false;};
			if(m_dblYMax != rhs.m_dblYMax){return false;};

			if(m_dblZMin != rhs.m_dblZMin){return false;};
			if(m_dblZMax != rhs.m_dblZMax){return false;};

			//made it this far without finding a difference, must be the same
			return true;
		};
		bool GtAABox::operator != (GtAABox & rhs)
		{
			if(m_dblXMin != rhs.m_dblXMin){return true;};
			if(m_dblXMax != rhs.m_dblXMax){return true;};

			if(m_dblYMin != rhs.m_dblYMin){return true;};
			if(m_dblYMax != rhs.m_dblYMax){return true;};

			if(m_dblZMin != rhs.m_dblZMin){return true;};
			if(m_dblZMax != rhs.m_dblZMax){return true;};
			//made it this far without finding a difference, must be the same
			return false;	
		};
		bool GtAABox::IsBoxValid(void)
		{
			if( (abs(m_dblXMax - m_dblXMin) *
				abs(m_dblYMax - m_dblYMin) *
				abs(m_dblZMax - m_dblZMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		bool GtAABox::IsBoxValidXY(void)
		{
			if( (abs(m_dblXMax - m_dblXMin) *
				abs(m_dblYMax - m_dblYMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		bool GtAABox::IsBoxValidXZ(void)
		{
			if( (abs(m_dblXMax - m_dblXMin) *
				abs(m_dblZMax - m_dblZMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		bool GtAABox::IsBoxValidYZ(void)
		{
			if( (abs(m_dblYMax - m_dblYMin) *
				abs(m_dblZMax - m_dblZMin) ) <= 0.000001)
			{
				//then no volume for box, invalid box
				return false;
			}else{
				return true;
			};
		};
		void GtAABox::Reset(void)
		{
			m_dblXMin = -1;
			m_dblXMax = -1;
			m_dblYMin = -1;
			m_dblYMax = -1;
			m_dblZMin = -1;
			m_dblZMax = -1;
		};
		void GtAABox::Zero(void)
		{
			m_dblXMin = 0.0f;
			m_dblXMax = 0.0f;
			m_dblYMin = 0.0f;
			m_dblYMax = 0.0f;
			m_dblZMin = 0.0f;
			m_dblZMax = 0.0f;
		};
		double GtAABox::GetBaseArea(void)
		{
			return (fabs(m_dblXMax - m_dblXMin) * fabs(m_dblYMax - m_dblYMin));
		};

		double GtAABox::GetVolume(void)
		{
			return (fabs(m_dblXMax - m_dblXMin) * fabs(m_dblYMax - m_dblYMin)* fabs(m_dblZMax - m_dblZMin));
		};
		GtPoint3DF GtAABox::GetCentroid(void)
		{
			GtPoint3DF objPointTemp;
			objPointTemp.x = (m_dblXMin + m_dblXMax) / (2.0f);
			objPointTemp.y = (m_dblYMin + m_dblYMax) / (2.0f);
			objPointTemp.z = (m_dblZMin + m_dblZMax) / (2.0f);
			return objPointTemp;
		};
		GtPoint3DF GtAABox::GetBaseCentroid(void)
		{
			GtPoint3DF objPointTemp;
			objPointTemp.x = (m_dblXMin + m_dblXMax) / (2.0f);
			objPointTemp.y = (m_dblYMin + m_dblYMax) / (2.0f);
			objPointTemp.z = (m_dblZMin);
			return objPointTemp;
		};

		GtPoint3DF GtAABox::GetXMinYMinZMin(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMin,m_dblZMin);
		};
		GtPoint3DF GtAABox::GetXMinYMinZMax(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMin,m_dblZMax);
		};
		GtPoint3DF GtAABox::GetXMinYMaxZMin(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMax,m_dblZMin);
		};
		GtPoint3DF GtAABox::GetXMinYMaxZMax(void)
		{
			return GtPoint3DF(m_dblXMin,m_dblYMax,m_dblZMax);
		};

		GtPoint3DF GtAABox::GetXMaxYMinZMin(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMin,m_dblZMin);
		};
		GtPoint3DF GtAABox::GetXMaxYMinZMax(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMin,m_dblZMax);
		};
		GtPoint3DF GtAABox::GetXMaxYMaxZMin(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMax,m_dblZMin);
		};
		GtPoint3DF GtAABox::GetXMaxYMaxZMax(void)
		{
			return GtPoint3DF(m_dblXMax,m_dblYMax,m_dblZMax);
		};

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtAABox::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblXMin",m_dblXMin,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblXMax",m_dblXMax,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblYMin",m_dblYMin,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblYMax",m_dblYMax,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblZMin",m_dblZMin,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblZMax",m_dblZMax,false);

			return intReturn;
		};

		int GtAABox::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblXMin",m_dblXMin);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblXMax",m_dblXMax);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblYMin",m_dblYMin);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblYMax",m_dblYMax);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblZMin",m_dblZMin);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"m_dblZMax",m_dblZMax);
			return intReturn;

		};

	};//end namespace GtCore
};//end namespace GT