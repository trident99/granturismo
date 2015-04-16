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

#include ".\GtAppSettings.h"

namespace GT
{
	namespace GtCore
	{

		//default constructor
		GtAppSettings::GtAppSettings(GtObject* ptrParent)
			: GtObject(ptrParent)
			,m_arrSettings()
		{
			m_strType = "GtState";
		};
		//virtual destructor
		GtAppSettings::~GtAppSettings(void)
		{
			m_arrSettings.clear();
			return;
		};
		//!Add a setting to  the map
		void GtAppSettings::AddSetting(std::string & strName, GtVariant & varVal)
		{
			m_arrSettings.insert(strName,varVal);
		};
		//!Update a setting with a new value
		void GtAppSettings::UpdateSetting(std::string & strName, GtVariant & varVal)
		{
			if(m_arrSettings.size() > 0)
			{
				GtSettingsNode* iter;
				iter = m_arrSettings.find(strName);
				if(iter != m_arrSettings.end())
				{
					iter->setValue(varVal);
					return;
				}
			}
			return;
		}
		//!Delete the setting by name
		void GtAppSettings::DeleteSetting(std::string & strName)
		{
			if(m_arrSettings.size() > 0)
			{
				GtSettingsNode* iter;
				iter = m_arrSettings.find(strName);
				if(iter != m_arrSettings.end())
				{
					m_arrSettings.erase(strName);
					return;
				}
			}
			return;	
		};
		//!Delete ALL settings
		void GtAppSettings::DeleteAllSettings(void)
		{
			m_arrSettings.clear();
		}
		//!The number of settings
		size_t GtAppSettings::CountSettings(void)
		{
			return m_arrSettings.size();
		}

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtAppSettings::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			GtObject::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<GtSettingsMap,HTL_CONTAINER>(ptrCurrNode,"m_arrSettings",m_arrSettings,blnWithSubObjects);

			return intReturn;
		};

		int GtAppSettings::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			GtObject::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<GtSettingsMap,HTL_CONTAINER>(ptrCurrNode,"m_arrSettings",m_arrSettings);

			return intReturn;
		};


	};//end namespace GtCore

};//end namespace GT