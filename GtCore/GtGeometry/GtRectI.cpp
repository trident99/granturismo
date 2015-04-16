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
#include  ".\GtRectI.h"
#include  ".\GtPoint3DI.h"
#include  ".\GtSizeI.h"

#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{
		GtRectI::GtRectI(long lngXMin, long lngXMax, long lngYMin, long lngYMax)
		{
			m_strType = "GtRectI";
			xMin = lngXMin;
			yMin = lngXMax;
			xMax = lngYMin;
			yMax = lngYMax;
		}

		GtRectI::GtRectI(const GtPoint3DI &atopLeft, const GtPoint3DI &abottomRight)
		{
			m_strType = "GtRectI";
			xMin = atopLeft.x;
			yMin = atopLeft.y;
			xMax = abottomRight.x;
			yMax = abottomRight.y;
		}

		GtRectI::GtRectI(const GtPoint3DI &atopLeft, const long awidth, const long aheight)
		{
			m_strType = "GtRectI";
			xMin = atopLeft.x;
			yMin = atopLeft.y;
			xMax = (xMin + awidth - 1);
			yMax = (yMin + aheight - 1);
		}

		GtRectI::~GtRectI()
		{
			this->Zero();
		}

		//!copy constructor
		GtRectI::GtRectI(const GtRectI& rhs)
		{
			if (&rhs != this)
			{
				xMin = rhs.xMin;
				yMin = rhs.yMin;
				xMax = rhs.xMax;
				yMax = rhs.yMax;
			};
		};

		//!Assignment Operator
		GtRectI & GtRectI::operator = (const GtRectI & rhs)
		{
			if (&rhs != this)
			{
				xMin = rhs.xMin;
				yMin = rhs.yMin;
				xMax = rhs.xMax;
				yMax = rhs.yMax;

			};
			return *this;

		};

		void GtRectI::Zero(void)
		{ 
			xMin = 0;
			yMin = 0;
			xMax = 0;
			yMax = 0;
		}

		bool GtRectI::IsNull(void) const
		{ return ((xMax == xMin - 1) && (yMax == yMin - 1)); }

		bool GtRectI::IsValid(void) const
		{ return ((xMin <= xMax) && (yMin <= yMax)); }

		void GtRectI::SetOriginX(long ax)
		{ xMin = ax; }

		void GtRectI::SetOriginY(long ay)
		{ yMin = ay; }

		long GtRectI::GetOriginX(void) const
		{ return xMin; }

		long GtRectI::GetOriginY(void) const
		{ return yMin; }



		void GtRectI::SetLeft(long pos)
		{ xMin = pos; }

		void GtRectI::SetTop(long pos)
		{ yMin = pos; }

		void GtRectI::SetRight(long pos)
		{ xMax = pos; }

		void GtRectI::SetBottom(long pos)
		{ yMax = pos; }

		long GtRectI::GetLeft(void) const
		{ return xMin; }

		long GtRectI::GetTop(void) const
		{ return yMin; }

		long GtRectI::GetRight(void) const
		{ return xMax; }

		long GtRectI::GetBottom(void) const
		{ return yMax; }




		void GtRectI::SetTopLeft(const GtPoint3DI &p)
		{ xMin = p.x; yMin = p.y; }

		void GtRectI::SetBottomRight(const GtPoint3DI &p)
		{ xMax = p.x; yMax = p.y; }

		void GtRectI::SetTopRight(const GtPoint3DI &p)
		{ xMax = p.x; yMin = p.y; }

		void GtRectI::SetBottomLeft(const GtPoint3DI &p)
		{ xMin = p.x; yMax = p.y; }

		GtPoint3DI GtRectI::GetTopLeft(void) const
		{ return GtPoint3DI(xMin, yMin); }

		GtPoint3DI GtRectI::GetBottomRight(void) const
		{ return GtPoint3DI(xMax, yMax); }

		GtPoint3DI GtRectI::GetTopRight(void) const
		{ return GtPoint3DI(xMax, yMin); }

		GtPoint3DI GtRectI::GetBottomLeft(void) const
		{ return GtPoint3DI(xMin, yMax); }



		GtPoint3DI GtRectI::Center(void) const
		{ return GtPoint3DI((xMin+xMax)/2, (yMin+yMax)/2); }

		long GtRectI::Width(void) const
		{ return  xMax - xMin + 1; }

		long GtRectI::Height(void) const
		{ return  yMax - yMin + 1; }

		GtSizeI GtRectI::Size(void) const
		{ return GtSizeI(Width(), Height()); }

		//!Contains the passed in point
		bool GtRectI::Contains(GtPoint3DI & pt)
		{
			if( (pt.x >= this->xMin) && (pt.x <= this->xMax) &&
				(pt.y >= this->yMin) && (pt.y <= this->yMax) )
			{
				return true;
			}
			return false;
		};




		void GtRectI::Translate(int dx, int dy)
		{
			xMin += dx;
			yMin += dy;
			xMax += dx;
			yMax += dy;
		}

		void GtRectI::Translate(const GtPoint3DI &p)
		{
			xMin += p.x;
			yMin += p.y;
			xMax += p.x;
			yMax += p.y;
		}
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtRectI::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"xMin",xMin,false);
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"xMax",xMax,false);
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"yMin",yMin,false);
			intReturn &= SetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"yMax",yMax,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;
		};

		int GtRectI::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"xMin",xMin);
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"xMax",xMax);
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"yMin",yMin);
			intReturn &= GetHtlMemVar<long,CPP_LONG>(ptrCurrNode,"yMax",yMax);

			return intReturn;
		};

	};//end namespace GtCore

};//end namespace GT