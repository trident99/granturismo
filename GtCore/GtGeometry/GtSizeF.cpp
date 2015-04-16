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
#include  ".\GtSizeF.h"
#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{


		//GtSizeF(void);
		GtSizeF::GtSizeF(double dX, double dY)
		{
			m_strType = "GtSizeF";
			deltaX = dX;
			deltaY = dY;
		};
		GtSizeF::GtSizeF(const GtSizeF& rhs)
		{
			m_strType = "GtSizeF";
			deltaX = rhs.deltaX;
			deltaY = rhs.deltaY;			
		};
		GtSizeF::~GtSizeF(void)
		{
			this->Zero();
		};
		//PUBLIC OPERATOR
		//!Assignment Operator
		GtSizeF & GtSizeF::operator = (const GtSizeF & rhs)
		{
			deltaX = rhs.deltaX;
			deltaY = rhs.deltaY;
			return *this;
		};
		//!EQUAL TO Operator
		bool GtSizeF::operator == (const GtSizeF & rhs)
		{
			double dblDifX,dblDifY, dblSigma;
			dblSigma = 0.0001f;
			dblDifX = fabs(deltaX - rhs.deltaX);
			dblDifY = fabs(deltaY - rhs.deltaY);
			return ((dblDifX <= dblSigma) && (dblDifY <= dblSigma));
		};
		//!NOT EQUAL TO Operator
		bool GtSizeF::operator != (const GtSizeF & rhs)
		{
			double dblDifX,dblDifY, dblSigma;
			dblSigma = 0.0001f;
			dblDifX = fabs(deltaX - rhs.deltaX);
			dblDifY = fabs(deltaY - rhs.deltaY);
			return ((dblDifX > dblSigma) || (dblDifY > dblSigma));
		};
		//!LESS THAN Operator
		bool GtSizeF::operator < (const GtSizeF & rhs)
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
		bool GtSizeF::operator > (const GtSizeF & rhs)
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
		GtSizeF & GtSizeF::operator*=(double factor)
		{
			deltaX = deltaX * factor;
			deltaY = deltaY * factor;
			return *this;
		};
		//!Additive compound operator
		GtSizeF & GtSizeF::operator+=(const GtSizeF & rhs)
		{
			deltaX = deltaX + rhs.deltaX;
			deltaY = deltaY + rhs.deltaY;
			return *this;
		};
		//!Subtractive compound operator
		GtSizeF & GtSizeF::operator-=(const GtSizeF & rhs)
		{
			deltaX = deltaX - rhs.deltaX;
			deltaY = deltaY - rhs.deltaY;
			return *this;
		};
		//!Divisive compound operator
		GtSizeF & GtSizeF::operator/=(double divisor)
		{
			if(fabs(divisor) <= 0.0001){return *this;};//divide by zero
			//otherwise proceed
			deltaX = deltaX / divisor;
			deltaY = deltaY / divisor;
			return *this;
		};
		//!zero the size
		void GtSizeF::Zero(void)
		{
			deltaX = 0;
			deltaY = 0;
		};
		//Is the size null
		bool GtSizeF::IsNull(void) const
		{
			double dblX,dblY, dblSigma;
			dblSigma = 0.0001f;
			dblX = fabs(deltaX);
			dblY = fabs(deltaY);
			return ((dblX <= dblSigma) && (dblY <= dblSigma));
		};
		//Is the size valid
		bool GtSizeF::IsValid(void) const
		{
			double dblX,dblY, dblSigma;
			dblSigma = 0.1f;
			dblX = fabs(deltaX);
			dblY = fabs(deltaY);	
			return ((dblX * dblY) >= dblSigma);//has area
		};
		//Transpose the size
		void GtSizeF::Transpose(void)
		{
			double dblTemp;
			dblTemp = deltaX;
			deltaX = deltaY;
			deltaY = dblTemp;		
		};

		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtSizeF::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"deltaX",deltaX,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"deltaY",deltaY,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;


		};

		int GtSizeF::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"deltaX",deltaX);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"deltaY",deltaY);
			return intReturn;

		};

	};//end namespace GtCore

};//end namespace GT