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
#include  ".\GtSizeI.h"
#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{


		//GtSizeI(void);
		GtSizeI::GtSizeI(long dX, long dY)
		{
			m_strType = "GtSizeI";
			deltaX = dX;
			deltaY = dY;
		};
		GtSizeI::GtSizeI(const GtSizeI& rhs)
		{
			m_strType = "GtSizeI";
			deltaX = rhs.deltaX;
			deltaY = rhs.deltaY;			
		};
		GtSizeI::~GtSizeI(void)
		{
			this->Zero();
		};
		//PUBLIC OPERATOR
		//!Assignment Operator
		GtSizeI & GtSizeI::operator = (const GtSizeI & rhs)
		{
			deltaX = rhs.deltaX;
			deltaY = rhs.deltaY;
			return *this;
		};
		//!EQUAL TO Operator
		bool GtSizeI::operator == (const GtSizeI & rhs)
		{
			long lngDifX,lngDifY, lngSigma;
			lngSigma = 0;
			lngDifX = abs(deltaX - rhs.deltaX);
			lngDifY = abs(deltaY - rhs.deltaY);
			return ((lngDifX <= lngSigma) && (lngDifY <= lngSigma));
		};
		//!NOT EQUAL TO Operator
		bool GtSizeI::operator != (const GtSizeI & rhs)
		{
			long lngDifX,lngDifY, lngSigma;
			lngSigma = 0;
			lngDifX = abs(deltaX - rhs.deltaX);
			lngDifY = abs(deltaY - rhs.deltaY);
			return ((lngDifX > lngSigma) || (lngDifY > lngSigma));
		};
		//!LESS THAN Operator
		bool GtSizeI::operator < (const GtSizeI & rhs)
		{
			if(deltaX < rhs.deltaX)
			{
				if(deltaY < rhs.deltaY)
				{
					return true;
				}
			}
			return false;
		};
		//!GREATER THAN Operator
		bool GtSizeI::operator > (const GtSizeI & rhs)
		{
			if(deltaX > rhs.deltaX)
			{
				if(deltaY > rhs.deltaY)
				{
					return true;
				}
			}
			return false;
		};
		//!Multiplicative compound operator
		GtSizeI & GtSizeI::operator*=(double factor)
		{
			deltaX = (long)(deltaX * factor);
			deltaY = (long)(deltaY * factor);
			return *this;
		};
		//!Additive compound operator
		GtSizeI & GtSizeI::operator+=(const GtSizeI & rhs)
		{
			deltaX = deltaX + rhs.deltaX;
			deltaY = deltaY + rhs.deltaY;
			return *this;
		};
		//!Subtractive compound operator
		GtSizeI & GtSizeI::operator-=(const GtSizeI & rhs)
		{
			deltaX = deltaX - rhs.deltaX;
			deltaY = deltaY - rhs.deltaY;
			return *this;
		};
		//!Divisive compound operator
		GtSizeI & GtSizeI::operator/=(double divisor)
		{
			if(divisor == 0){return *this;};//divide by zero
			//otherwise proceed
			deltaX = (long)(deltaX / divisor);
			deltaY = (long)(deltaY / divisor);
			return *this;
		};
		//!zero the size
		void GtSizeI::Zero(void)
		{
			deltaX = 0;
			deltaY = 0;
		};
		//Is the size null
		bool GtSizeI::IsNull(void) const
		{
			long lngX,lngY, lngSigma;
			lngSigma = 0;
			lngX = abs(deltaX);
			lngY = abs(deltaY);
			return ((lngX <= lngSigma) && (lngY <= lngSigma));
		};
		//Is the size valid
		bool GtSizeI::IsValid(void) const
		{
			long lngX,lngY, lngSigma;
			lngSigma = 0;
			lngX = abs(deltaX);
			lngY = abs(deltaY);	
			return ((lngX * lngY) >= lngSigma);//has area
		};
		//Transpose the size
		void GtSizeI::Transpose(void)
		{
			long lngTemp;
			lngTemp = deltaX;
			deltaX = deltaY;
			deltaY = lngTemp;		
		};

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtSizeI::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"deltaX",deltaX,false);
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"deltaY",deltaY,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;


		};

		int GtSizeI::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"deltaX",deltaX);
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"deltaY",deltaY);
			return intReturn;

		};

	};//end namespace GtCore

};//end namespace GT