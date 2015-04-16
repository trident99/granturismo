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
#include  ".\GtRectF.h"
#include  ".\GtPoint3DF.h"
#include  ".\GtSizeF.h"

#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{
		GtRectF::GtRectF(double dblXMin,double dblXMax,double dblYMin,double dblYMax)
		{
			m_strType = "GtRectF";
			xMin = dblXMin;
			yMin = dblXMax;
			xMax = dblYMin;
			yMax = dblYMax;
		}

		GtRectF::GtRectF(const GtPoint3DF &atopLeft, const GtPoint3DF &abottomRight)
		{
			m_strType = "GtRectF";
			xMin = atopLeft.x;
			yMin = atopLeft.y;
			xMax = abottomRight.x;
			yMax = abottomRight.y;
		}

		GtRectF::GtRectF(const GtPoint3DF &atopLeft, const double awidth, const double aheight)
		{
			m_strType = "GtRectF";
			xMin = atopLeft.x;
			yMin = atopLeft.y;
			xMax = (xMin + awidth - 1);
			yMax = (yMin + aheight - 1);
		}

		GtRectF::~GtRectF()
		{
			this->Zero();
		}

		void GtRectF::Zero(void)
		{ 
			xMin = 0.0f;
			yMin = 0.0f;
			xMax = 0.0f;
			yMax = 0.0f;
		}

		bool GtRectF::IsNull(void) const
		{ return ((xMin == 0.0f)&&(xMax == 0.0f)&&(yMin == 0.0f)&&(yMax == 0.0f)); }

		bool GtRectF::IsValid(void) const
		{ return ((xMin <= xMax) && (yMin <= yMax)); }

		void GtRectF::SetOriginX(double ax)
		{ xMin = ax; }

		void GtRectF::SetOriginY(double ay)
		{ yMin = ay; }

		double GtRectF::GetOriginX(void) const
		{ return xMin; }

		double GtRectF::GetOriginY(void) const
		{ return yMin; }

		void GtRectF::SetLeft(double pos)
		{ xMin = pos; }

		void GtRectF::SetTop(double pos)
		{ yMin = pos; }

		void GtRectF::SetRight(double pos)
		{ xMax = pos; }

		void GtRectF::SetBottom(double pos)
		{ yMax = pos; }

		double GtRectF::GetLeft(void) const
		{ return xMin; }

		double GtRectF::GetTop(void) const
		{ return yMin; }

		double GtRectF::GetRight(void) const
		{ return xMax; }

		double GtRectF::GetBottom(void) const
		{ return yMax; }



		void GtRectF::SetTopLeft(const GtPoint3DF &p)
		{ xMin = p.x; yMin = p.y; }

		void GtRectF::SetBottomRight(const GtPoint3DF &p)
		{ xMax = p.x; yMax = p.y; }

		void GtRectF::SetTopRight(const GtPoint3DF &p)
		{ xMax = p.x; yMin = p.y; }

		void GtRectF::SetBottomLeft(const GtPoint3DF &p)
		{ xMin = p.x; yMax = p.y; }

		GtPoint3DF GtRectF::GetTopLeft(void) const
		{ return GtPoint3DF(xMin, yMin); }

		GtPoint3DF GtRectF::GetBottomRight(void) const
		{ return GtPoint3DF(xMax, yMax); }

		GtPoint3DF GtRectF::GetTopRight(void) const
		{ return GtPoint3DF(xMax, yMin); }

		GtPoint3DF GtRectF::GetBottomLeft(void) const
		{ return GtPoint3DF(xMin, yMax); }



		GtPoint3DF GtRectF::Center(void) const
		{ return GtPoint3DF((xMin+xMax)/2, (yMin+yMax)/2); }

		double GtRectF::Width(void) const
		{ return  xMax - xMin + 1; }

		double GtRectF::Height(void) const
		{ return  yMax - yMin + 1; }

		GtSizeF GtRectF::Size(void) const
		{ return GtSizeF(Width(), Height()); }

		//!Contains the passed in point
		bool GtRectF::Contains(GtPoint3DF & pt)
		{
			if( (pt.x >= this->xMin) && (pt.x <= this->xMax) &&
				(pt.y >= this->yMin) && (pt.y <= this->yMax) )
			{
				return true;
			}
			return false;
		};

		void GtRectF::Translate(float dx, float dy)
		{
			xMin += dx;
			yMin += dy;
			xMax += dx;
			yMax += dy;
		}

		void GtRectF::Translate(const GtPoint3DF &p)
		{
			xMin += p.x;
			yMin += p.y;
			xMax += p.x;
			yMax += p.y;
		}
		//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtRectF::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"xMin",xMin,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"xMax",xMax,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"yMin",yMin,false);
			intReturn &= SetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"yMax",yMax,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;


		};

		int GtRectF::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"xMin",xMin);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"xMax",xMax);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"yMin",yMin);
			intReturn &= GetHtlMemVar<double,CPP_DOUBLE>(ptrCurrNode,"yMax",yMax);
			return intReturn;

		};

	};//end namespace GtCore

};//end namespace GT