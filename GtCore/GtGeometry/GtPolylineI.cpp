/*
**	This file is part of the TridentCAD
**	This software was merged and developed by:
**	
**  Anthony Daniels
**
**  TridentCAD is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to TridentCAD.
**
**  TridentCAD is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with TridentCAD.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include  ".\GtPolylineI.h"
#include <modHtlArchive.h>

namespace GT
{

	namespace GtCore
	{
		GtPolylineI::GtPolylineI(void)
			: HtlBase()
		{
			//HtlBase Initialization
			m_strType = "GtPolylineI";
			//GtPolylineI Initialization////////////////////
			m_objNullPoint.Zero();
			return;
		};


		GtPolylineI::GtPolylineI(GtPolylineI& rhs)
			: HtlBase(rhs)
		{
			//HtlBase Initialization
			m_strType = "GtPolylineI";
			//GtPolylineI Initialization////////////////////
			size_t i, intNumPts;
			m_arrObjPoints.clear();
			intNumPts = rhs.Size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.push_back(rhs.m_arrObjPoints.at(i));
			};
			return;
		};

		GtPolylineI & GtPolylineI::operator = (GtPolylineI & rhs)
		{
			if(this == &rhs)
				return *this;

			HtlBase::operator=(rhs);

			//ORSSerializable Initialization
			m_strType = "GtPolylineI";
			//GtPolylineI Initialization////////////////////
			size_t i, intNumPts;
			m_arrObjPoints.clear();
			intNumPts = rhs.Size();
			for(i = 0; i < intNumPts; i++)
			{
				this->m_arrObjPoints.push_back(rhs.m_arrObjPoints.at(i));
			};
			return *this;	
		};

		GtPolylineI::~GtPolylineI(void)
		{
			return;
		};


		bool GtPolylineI::operator == (GtPolylineI & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrObjPoints.size();
			intRHSNumPoints = rhs.m_arrObjPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return false;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrObjPoints.at(i) != rhs.m_arrObjPoints.at(i)){return false;};
			}
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GtPolylineI::operator != (GtPolylineI & rhs)
		{
			size_t i, intLHSNumPoints, intRHSNumPoints;
			intLHSNumPoints = m_arrObjPoints.size();
			intRHSNumPoints = rhs.m_arrObjPoints.size();
			if(intLHSNumPoints != intRHSNumPoints){return true;};
			//if number of points same must compare all of them
			for(i = 0; i < intLHSNumPoints; i++)
			{
				if(m_arrObjPoints.at(i) != rhs.m_arrObjPoints.at(i)){return true;};
			}
			//made it this far without finding a difference, must be the same
			return false;
		};

		void GtPolylineI::Clear(void)
		{
			m_arrObjPoints.clear();
		};
		size_t GtPolylineI::Size(void)
		{
			return m_arrObjPoints.size();
		};
		GtPoint3DI & GtPolylineI::At(size_t intIndex)
		{
			size_t intNumPoints;
			intNumPoints = m_arrObjPoints.size();
			if((intIndex >= 0) && (intIndex < intNumPoints))
			{
				return m_arrObjPoints.at(intIndex);
			}else{
				return m_objNullPoint;
			};
		};
		void GtPolylineI::PushBack(GtPoint3DI & objNewPoint)
		{
			m_arrObjPoints.push_back(objNewPoint);
			return;
		};


		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtPolylineI::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar< StlVector<GtPoint3DI, HTL_BASE> ,STL_CONTAINER>(ptrCurrNode,"m_arrObjPoints",m_arrObjPoints,true);


			return intReturn;


		};

		int GtPolylineI::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			//Standard Member Variables
			intReturn &= GetHtlMemVar< StlVector<GtPoint3DI, HTL_BASE> ,STL_CONTAINER>(ptrCurrNode,"m_arrObjPoints",m_arrObjPoints);
			return intReturn;

		};

	};//end namespace GtCore

};//end namespace GT