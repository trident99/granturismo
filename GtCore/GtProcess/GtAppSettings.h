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

#ifndef GT_APPLICATION_SETTINGS_H
#define GT_APPLICATION_SETTINGS_H

#include "..\modGtBase.h"
#include <modHtlContainer.h>

using namespace HTL;

namespace GT
{

	namespace GtCore
	{
		typedef HtlListMap<std::string,STL_STRING,GtVariant,HTL_BASE> GtSettingsMap;
		typedef HtlTreeNode<std::string,GtVariant> GtSettingsNode;
		//!This is the base object that provides signals slots capability as well as a global unique identifier for the object.
		/*!
		This is the base object that provides signals slots capability as well as a
		global unique identifier for the object. It inherits the HtlBase serialization engine
		*/
		class HTL_DLLAPI GtAppSettings : public GtObject
		{
		public:
			//!Parent set constructor
			GtAppSettings(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtAppSettings(void);

			//MEMBER VARIABLES////////////////////////
			//!Pointer to the beginning source state
			GTOBJECT_MEMVAR_BYREF(public, std::string,  strVersion);
			//!Pointer to the ending target state
			GTOBJECT_MEMVAR_BYREF(public, std::string,  strDescription);

			//SIGNALS/////////////////////////////////
		public:
			//!Signal for when the settings are modified
			HtlSignal00  SettingsModified; 


			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Add a setting to  the map
			void AddSetting(std::string & strName, GtVariant & varVal);
			//!Update a setting with a new value
			void UpdateSetting(std::string & strName, GtVariant & varVal);
			//!Delete the setting by name
			void DeleteSetting(std::string & strName);
			//!Delete ALL settings
			void DeleteAllSettings(void);
			//!The number of settings
			size_t CountSettings(void);

			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//!Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//!Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);


		protected:

			GtSettingsMap m_arrSettings; 

		};//end HtlBase class definition

}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H