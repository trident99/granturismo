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


#ifndef GT_VARIANT_H
#define GT_VARIANT_H
#include "..\GtCoreEnums.h"
#include <modHtlBase.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{
	 class GtObject;
	//!Variant Data type
	 union GtVarData
        {
            char c;
            uchar uc;
            short s;
            ushort us;
            int i;
            uint ui;
            long l;
            ulong ul;
            bool b;
            double d;
            float f;
            longlong ll;
            ulonglong ull;
            GtObject *ptrObj;
            void *ptrVoid;
        };

		//!This is the base object that provides a unioned variant type for basic types as well as pointers to objects
		class HTL_DLLAPI GtVariant : public HtlBase
		{
		public:
			//!Constructors
			GtVariant();
			GtVariant(char varVal);
			GtVariant(uchar varVal);
			GtVariant(short varVal);
			GtVariant(ushort varVal);
			GtVariant(long varVal);
			GtVariant(ulong varVal);
			GtVariant(longlong varVal);
			GtVariant(ulonglong varVal);
			GtVariant(float varVal);
			GtVariant(double varVal);
			GtVariant(GtObject* varVal);
			GtVariant(void* varVal);
			GtVariant(std::string & varVal);
			//!Virtual destructor
			virtual ~GtVariant(void);

		public:
			//!Assignment operators/////////////////////////////////////////
			GtVariant & operator= ( const GtVariant & rhs);
			GtVariant & operator= ( const char & rhs);
			GtVariant & operator= ( const uchar & rhs);
			GtVariant & operator= ( const short & rhs);
			GtVariant & operator= ( const ushort & rhs);
			GtVariant & operator= ( const int & rhs);
			GtVariant & operator= ( const uint & rhs);
			GtVariant & operator= ( const long & rhs);
			GtVariant & operator= ( const ulong & rhs);
			GtVariant & operator= ( const longlong & rhs);
			GtVariant & operator= ( const ulonglong & rhs);
			GtVariant & operator= ( const float & rhs);
			GtVariant & operator= ( const double & rhs);
			GtVariant & operator= ( GtObject* & rhs);
			GtVariant & operator= ( void* & rhs);
			GtVariant & operator= ( std::string & rhs);

			//!Equal Operators//////////////////////////////////////////////
			bool operator == (const char & rhs ){return (m_varData.c == rhs);};
			bool operator == (const uchar & rhs ){return (m_varData.uc == rhs);};
			bool operator == (const short & rhs ){return (m_varData.s == rhs);};
			bool operator == (const ushort & rhs ){return (m_varData.us == rhs);};
			bool operator == (const int & rhs ){return (m_varData.i == rhs);};
			bool operator == (const uint & rhs ){return (m_varData.ui == rhs);};
			bool operator == (const long & rhs ){return (m_varData.l == rhs);};
			bool operator == (const ulong & rhs ){return (m_varData.ul == rhs);};
			bool operator == (const longlong & rhs ){return (m_varData.ll == rhs);};
			bool operator == (const ulonglong & rhs ){return (m_varData.ull == rhs);};
			bool operator == (const float & rhs ){return (m_varData.f == rhs);};
			bool operator == (const double & rhs ){return (m_varData.d == rhs);};
			bool operator == (const std::string & rhs ){return (m_strData == rhs);};

			//!Not Equal Operators/////////////////////////////////////////
			bool operator != (const char & rhs ){return (m_varData.c != rhs);};
			bool operator != (const uchar & rhs ){return (m_varData.uc != rhs);};
			bool operator != (const short & rhs ){return (m_varData.s != rhs);};
			bool operator != (const ushort & rhs ){return (m_varData.us != rhs);};
			bool operator != (const int & rhs ){return (m_varData.i != rhs);};
			bool operator != (const uint & rhs ){return (m_varData.ui != rhs);};
			bool operator != (const long & rhs ){return (m_varData.l != rhs);};
			bool operator != (const ulong & rhs ){return (m_varData.ul != rhs);};
			bool operator != (const longlong & rhs ){return (m_varData.ll != rhs);};
			bool operator != (const ulonglong & rhs ){return (m_varData.ull != rhs);};
			bool operator != (const float & rhs ){return (m_varData.f != rhs);};
			bool operator != (const double & rhs ){return (m_varData.d != rhs);};
			bool operator != (const std::string & rhs ){return (m_strData != rhs);};

			//!Less Than Operators/////////////////////////////////////////
			bool operator < (const char & rhs ){return (m_varData.c < rhs);};
			bool operator < (const uchar & rhs ){return (m_varData.uc < rhs);};
			bool operator < (const short & rhs ){return (m_varData.s < rhs);};
			bool operator < (const ushort & rhs ){return (m_varData.us < rhs);};
			bool operator < (const int & rhs ){return (m_varData.i < rhs);};
			bool operator < (const uint & rhs ){return (m_varData.ui < rhs);};
			bool operator < (const long & rhs ){return (m_varData.l < rhs);};
			bool operator < (const ulong & rhs ){return (m_varData.ul < rhs);};
			bool operator < (const longlong & rhs ){return (m_varData.ll < rhs);};
			bool operator < (const ulonglong & rhs ){return (m_varData.ull < rhs);};
			bool operator < (const float & rhs ){return (m_varData.f < rhs);};
			bool operator < (const double & rhs ){return (m_varData.d < rhs);};
			bool operator < (const std::string & rhs ){return (m_strData < rhs);};
			
			//!Greater Than Operators///////////////////////////////////////
			bool operator > (const char & rhs ){return (m_varData.c > rhs);};
			bool operator > (const uchar & rhs ){return (m_varData.uc > rhs);};
			bool operator > (const short & rhs ){return (m_varData.s > rhs);};
			bool operator > (const ushort & rhs ){return (m_varData.us > rhs);};
			bool operator > (const int & rhs ){return (m_varData.i > rhs);};
			bool operator > (const uint & rhs ){return (m_varData.ui > rhs);};
			bool operator > (const long & rhs ){return (m_varData.l > rhs);};
			bool operator > (const ulong & rhs ){return (m_varData.ul > rhs);};
			bool operator > (const longlong & rhs ){return (m_varData.ll > rhs);};
			bool operator > (const ulonglong & rhs ){return (m_varData.ull > rhs);};
			bool operator > (const float & rhs ){return (m_varData.f > rhs);};
			bool operator > (const double & rhs ){return (m_varData.d > rhs);};
			bool operator > (const std::string & rhs ){return (m_strData > rhs);};

			//!Less Than Equal Operators////////////////////////////////////
			bool operator <= (const char & rhs ){return (m_varData.c <= rhs);};
			bool operator <= (const uchar & rhs ){return (m_varData.uc <= rhs);};
			bool operator <= (const short & rhs ){return (m_varData.s <= rhs);};
			bool operator <= (const ushort & rhs ){return (m_varData.us <= rhs);};
			bool operator <= (const int & rhs ){return (m_varData.i <= rhs);};
			bool operator <= (const uint & rhs ){return (m_varData.ui <= rhs);};
			bool operator <= (const long & rhs ){return (m_varData.l <= rhs);};
			bool operator <= (const ulong & rhs ){return (m_varData.ul <= rhs);};
			bool operator <= (const longlong & rhs ){return (m_varData.ll <= rhs);};
			bool operator <= (const ulonglong & rhs ){return (m_varData.ull <= rhs);};
			bool operator <= (const float & rhs ){return (m_varData.f <= rhs);};
			bool operator <= (const double & rhs ){return (m_varData.d <= rhs);};
			bool operator <= (const std::string & rhs ){return (m_strData <= rhs);};

			//!Greater Than Equal Operators/////////////////////////////////
			bool operator >= (const char & rhs ){return (m_varData.c >= rhs);};
			bool operator >= (const uchar & rhs ){return (m_varData.uc >= rhs);};
			bool operator >= (const short & rhs ){return (m_varData.s >= rhs);};
			bool operator >= (const ushort & rhs ){return (m_varData.us >= rhs);};
			bool operator >= (const int & rhs ){return (m_varData.i >= rhs);};
			bool operator >= (const uint & rhs ){return (m_varData.ui >= rhs);};
			bool operator >= (const long & rhs ){return (m_varData.l >= rhs);};
			bool operator >= (const ulong & rhs ){return (m_varData.ul >= rhs);};
			bool operator >= (const longlong & rhs ){return (m_varData.ll >= rhs);};
			bool operator >= (const ulonglong & rhs ){return (m_varData.ull >= rhs);};
			bool operator >= (const float & rhs ){return (m_varData.f >= rhs);};
			bool operator >= (const double & rhs ){return (m_varData.d >= rhs);};
			bool operator >= (const std::string & rhs ){return (m_strData >= rhs);};

		public:
			//MEMBER FUNCTIONS//////////////////////////////////////////////
			GtVarType GetVarType(void) const {return m_varType;};
			GtVarData GetVarData(void) const {return m_varData;};
			char GetChar(void) const {return m_varData.c;};
			uchar GetUChar(void) const {return m_varData.uc;};
			short GetShort(void) const {return m_varData.s;};
			ushort GetUShort(void) const {return m_varData.us;};
			int GetInt(void) const {return m_varData.i;};
			uint GetUInt(void) const {return m_varData.ui;};
			long GetLong(void) const {return m_varData.l;};
			ulong GetULong(void) const {return m_varData.ul;};
			longlong GetLongLong(void) const {return m_varData.ll;};
			ulonglong GetULongLong(void) const {return m_varData.ull;};
			float GetFloat(void) const {return m_varData.f;};
			float GetSingle(void) const {return m_varData.f;};
			double GetDouble(void) const {return m_varData.d;};
			bool GetBool(void) const {return m_varData.b;};
			GtObject* GetGtObjPtr(void) const {return m_varData.ptrObj;};
		    void* GetVoidPtr(void) const {return m_varData.ptrVoid;};
			std::string GetString(void){return m_strData;};
			//get a pointer to the variant object
			template<typename TObj>
			TObj* GetVarObjPtr(void)
			{
				return dynamic_cast<TObj*>(m_varData.ptrVoid);
			};

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//!Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//!Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		protected:
			//!The enumerated variant type
			GtVarType m_varType;
			//!The actual variant data
			GtVarData m_varData;
			//!String data incase it is a string
			std::string m_strData;

		};//end GtVariant class definition





	};//end namespace GtCore
};//end namespace GT

#endif