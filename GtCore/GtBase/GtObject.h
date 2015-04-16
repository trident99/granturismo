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

#ifndef GT_OBJECT_H
#define GT_OBJECT_H

#include "..\GtCoreLibRefs.h"
#include <modHtlSignalSlot.h>

using namespace HTL;

//macros for simple member variable get and set

#ifndef GTOBJECT_MEMVAR_BYVAL
#define GTOBJECT_MEMVAR_BYVAL(access, varType, varName) \
protected: \
	varType m_##varName; \
access :\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType varVal) \
{ \
	this->m_##varName = varVal; \
	this->m_blnModified = true; \
	return ; \
}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType Get_##varName(void) const\
{ \
	return this->m_##varName; \
}; \

#endif

#ifndef GTOBJECT_MEMVAR_BYREF
#define GTOBJECT_MEMVAR_BYREF(access, varType, varName) \
protected: \
	varType m_##varName; \
access :\
	/*HTL Member Variable Accessor Set Function*/ \
	void Set_##varName( varType & varVal) \
{ \
	this->m_##varName = varVal; \
	this->m_blnModified = true; \
	return ; \
}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType Get_##varName(void) const\
{ \
	return this->m_##varName; \
}; \

#endif

#ifndef GTOBJECT_MEMVAR_VIRTUAL
#define GTOBJECT_MEMVAR_VIRTUAL(access, varType, varName) \
protected: \
	varType m_##varName; \
access :\
	/*HTL Member Variable Accessor Set Function*/ \
	virtual void Set_##varName( varType varVal) \
{ \
	this->m_##varName = varVal; \
	this->m_blnModified = true; \
	return ; \
}; \
	/*HTL Member Variable Accessor Get Function*/ \
	varType Get_##varName(void) const\
{ \
	return this->m_##varName; \
}; \

#endif


namespace GT
{

	namespace GtCore
	{

		class GtEvent;
		//!This is the base object that provides signals slots capability as well as a global unique identifier for the object.
		/*!
		This is the base object that provides signals slots capability as well as a
		global unique identifier for the object. It inherits the HtlBase serialization engine
		*/
		class HTL_DLLAPI GtObject : public HtlHasSlots, public HtlBase
		{
		public:
			//!Parent set constructor
			GtObject(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtObject(void);

			//operator overloads
			GtObject & operator= ( GtObject & rhs){return *this;};
			virtual bool operator == (const GtObject & ptrRHS ){return false;};
			virtual bool operator != (const GtObject & ptrRHS ){return false;};
			virtual bool operator < (const GtObject & ptrRHS ){return false;};
			virtual bool operator > (const GtObject & ptrRHS ){return false;};
			virtual bool operator <= (const GtObject & ptrRHS ){return false;};
			virtual bool operator >= (const GtObject & ptrRHS ){return false;};


			//MEMBER VARIABLES////////////////////////
			//!Pointer to the parent object
			GTOBJECT_MEMVAR_BYVAL(public, GtObject*, ptrParent);
			//!pointer to the parent Node
			GTOBJECT_MEMVAR_BYREF(public, HtlGUID128, objGUID);
			//!String name for the object
			GTOBJECT_MEMVAR_BYREF(public, std::string, strName);

			//SIGNALS/////////////////////////////////
		public:
			//!Signal for when the object is destroyed
			HtlSignal00  Destroyed; 

			//MEMBER FUNCTIONS////////////////////////
		public:

			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent){return 0;};

			//!Get the flag
			bool IsModified(void){return m_blnModified;};

			void SetModified(bool blnIsModified){m_blnModified = blnIsModified;};

			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//!Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//!Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		protected:
			//!Object modified dirty flag
			bool m_blnModified;

		};//end HtlBase class definition

}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H