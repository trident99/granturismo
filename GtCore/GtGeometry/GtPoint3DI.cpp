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

#include "..\GtMath\GtBasicMath.h"
#include  ".\GtPoint3DI.h"
#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		GtPoint3DI::GtPoint3DI(long lngX, long lngY, long lngZ)
		{
			//HtlBase Initialization
			m_strType = "GtPoint3DI";
			this->x = lngX;
			this->y = lngY;
			this->z = lngZ;
		};

		GtPoint3DI::GtPoint3DI(const GtPoint3DI& rhs)
		{
			//HtlBase Initialization
			m_strType = "GtPoint3DI";
			//GtPoint3DI Initialization////////////////////
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return;
		};

		GtPoint3DI & GtPoint3DI::operator = (const GtPoint3DI & rhs)
		{
			if(this == &rhs)
				return *this;

			//HtlBase Initialization
			m_strType = "GtPoint3DI";
			//GtPoint3DI Initialization////////////////////
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return *this;	
		};

		GtPoint3DI::~GtPoint3DI(void)
		{
			return;
		};

		bool GtPoint3DI::operator == (const GtPoint3DI & rhs)
		{
			if(x != rhs.x){return false;};
			if(y != rhs.y){return false;};
			if(z != rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};
		bool GtPoint3DI::operator != (const GtPoint3DI & rhs)
		{
			if(x != rhs.x){return true;};
			if(y != rhs.y){return true;};
			if(z != rhs.z){return true;};
			//made it this far without finding a difference, must be the same
			return false;	
		};

		bool GtPoint3DI::operator < (const GtPoint3DI & rhs)
		{
			if(x > rhs.x){return false;};
			if(y > rhs.y){return false;};
			if(z > rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GtPoint3DI::operator > (const GtPoint3DI & rhs)
		{
			if(x < rhs.x){return false;};
			if(y < rhs.y){return false;};
			if(z < rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GtPoint3DI::IsPointValid(void)
		{
			if((x == -1)&&(y == -1)&&(z == -1))
			{
				return false;
			}else{
				return true;
			};
		};
		void GtPoint3DI::Reset(void)
		{
			x = -1;
			y = -1;
			z = -1;
		};
		void GtPoint3DI::Zero(void)
		{
			x = 0;
			y = 0;
			z = 0;
		};

		void GtPoint3DI::Set(long lngX, long lngY, long lngZ)
		{
			x = lngX;
			y = lngY;
			z = lngZ;
		};

		long GtPoint3DI::operator[]( int i ) const
		{
			switch( i )
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			}
			return -1;
		};

		//point3D functions
		GtPoint3DI GtPoint3DI::operator + ( const GtPoint3DI& w ) const
		{
			return GtPoint3DI( x + w.x, y + w.y, z + w.z );
		};
		GtPoint3DI GtPoint3DI::operator - ( const GtPoint3DI& w ) const
		{
			return GtPoint3DI( x - w.x, y - w.y, z - w.z );
		};
		GtPoint3DI GtPoint3DI::operator * ( long const t ) const
		{
			return GtPoint3DI( x * t, y * t, z * t );
		};
		GtPoint3DI GtPoint3DI::operator / ( long const t ) const
		{
			long xNew,yNew,zNew;
			xNew = gRound(double(x)/double(t));
			yNew = gRound(double(y)/double(t));
			zNew = gRound(double(z)/double(t));
			return GtPoint3DI(xNew,yNew,zNew);
		};
		double GtPoint3DI::operator * ( const GtPoint3DI& w ) const
		{
			return x * w.x + y * w.y + z * w.z;
		};
		GtPoint3DI GtPoint3DI::operator ^ ( const GtPoint3DI& w ) const
		{
			return GtPoint3DI( y * w.z - z * w.y, z * w.x - x * w.z, x * w.y - y * w.x );
		};
		double GtPoint3DI::Mag() const
		{
			return sqrt( double(x * x + y * y + z * z ));
		};


		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtPoint3DI::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"x",x,false);
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"y",y,false);
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"z",z,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;


		};

		int GtPoint3DI::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"x",x);
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"y",y);
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"z",z);
			return intReturn;

		};

		bool SortPoint3DI_Ascending(GtPoint3DI & a, GtPoint3DI & b)
		{
			// a > b causes a descending order sort www.cppreference.com
			return a.x < b.x;
		}
		bool SortPoint3DI_Descending(GtPoint3DI & a, GtPoint3DI & b)
		{
			// a > b causes a descending order sort www.cppreference.com
			return a.x > b.x;
		}
	};//end namespace GtCore

};//end namespace GT