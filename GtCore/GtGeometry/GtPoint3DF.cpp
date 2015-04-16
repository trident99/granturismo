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
#include  ".\GtPoint3DF.h"

#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		GtPoint3DF::GtPoint3DF(double dblX, double dblY,double dblZ)
		{
			//HtlBase Initialization
			m_strType = "GtPoint3DF";
			this->x = dblX;
			this->y = dblY;
			this->z = dblZ;
		};

		GtPoint3DF::GtPoint3DF(const GtPoint3DF& rhs)
		{
			//HtlBase Initialization
			m_strType = "GtPoint3DF";
			//GtPoint3DF Initialization////////////////////
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return;
		};

		GtPoint3DF & GtPoint3DF::operator = (const GtPoint3DF & rhs)
		{
			if(this == &rhs)
				return *this;

			//HtlBase Initialization
			m_strType = "GtPoint3DF";
			//GtPoint3DF Initialization////////////////////
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return *this;	
		};

		GtPoint3DF::~GtPoint3DF(void)
		{
			return;
		};

		bool GtPoint3DF::operator == (const GtPoint3DF & rhs)
		{
			if(x != rhs.x){return false;};
			if(y != rhs.y){return false;};
			if(z != rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};
		bool GtPoint3DF::operator != (const GtPoint3DF & rhs)
		{
			if(x != rhs.x){return true;};
			if(y != rhs.y){return true;};
			if(z != rhs.z){return true;};
			//made it this far without finding a difference, must be the same
			return false;	
		};

		bool GtPoint3DF::operator < (const GtPoint3DF & rhs)
		{
			if(x > rhs.x){return false;};
			if(y > rhs.y){return false;};
			if(z > rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GtPoint3DF::operator > (const GtPoint3DF & rhs)
		{
			if(x < rhs.x){return false;};
			if(y < rhs.y){return false;};
			if(z < rhs.z){return false;};
			//made it this far without finding a difference, must be the same
			return true;
		};

		bool GtPoint3DF::IsPointValid(void)
		{
			if((x == -1)&&(y == -1)&&(z == -1))
			{
				return false;
			}else{
				return true;
			};
		};
		void GtPoint3DF::Reset(void)
		{
			x = -1;
			y = -1;
			z = -1;
		};
		void GtPoint3DF::Zero(void)
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		};

		void GtPoint3DF::Round(int intNumDecimals)
		{
			x = gRound(x,intNumDecimals);
			y = gRound(y, intNumDecimals);
			z = gRound(z, intNumDecimals);
		};

		void GtPoint3DF::Set(double dblX, double dblY, double dblZ)
		{
			x = dblX;
			y = dblY;
			z = dblZ;
		};
		void GtPoint3DF::Normalize(void)
		{
			double length = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
			if(length <= 0.00001)
			{//safety check on divide by zero
				x = 0; y = 0; z = 0; return;
			};
			//otherwise safe to proceed
			x = x / length;
			y = y / length;
			z = z / length;
		};
		double GtPoint3DF::operator[]( int i ) const
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
		GtPoint3DF GtPoint3DF::operator + ( const GtPoint3DF& w ) const
		{
			return GtPoint3DF( x + w.x, y + w.y, z + w.z );
		};
		GtPoint3DF GtPoint3DF::operator - ( const GtPoint3DF& w ) const
		{
			return GtPoint3DF( x - w.x, y - w.y, z - w.z );
		};
		GtPoint3DF GtPoint3DF::operator * ( double const t ) const
		{
			return GtPoint3DF( x * t, y * t, z * t );
		};
		GtPoint3DF GtPoint3DF::operator / ( double const t ) const
		{
			return (*this) * ( 1.0 / t );
		};
		double GtPoint3DF::operator * ( const GtPoint3DF& w ) const
		{
			return x * w.x + y * w.y + z * w.z;
		};
		GtPoint3DF GtPoint3DF::operator ^ ( const GtPoint3DF& w ) const
		{
			return GtPoint3DF( y * w.z - z * w.y, z * w.x - x * w.z, x * w.y - y * w.x );
		};
		double GtPoint3DF::Mag() const
		{
			return sqrt( x * x + y * y + z * z );
		};
		GtPoint3DF GtPoint3DF::Normalize() const
		{ 
			return (*this) / Mag();
		};

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtPoint3DF::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"x",x,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"y",y,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"z",z,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;


		};

		int GtPoint3DF::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"x",x);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"y",y);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"z",z);
			return intReturn;

		};

		bool SortPoint3DF_Ascending(GtPoint3DF & a, GtPoint3DF & b)
		{
			// a > b causes a descending order sort www.cppreference.com
			return a.x < b.x;
		}
		bool SortPoint3DF_Descending(GtPoint3DF & a, GtPoint3DF & b)
		{
			// a > b causes a descending order sort www.cppreference.com
			return a.x > b.x;
		}
	};//end namespace GtCore

};//end namespace GT