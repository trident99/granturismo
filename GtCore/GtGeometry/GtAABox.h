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
#ifndef GT_AABOX_H
#define GT_AABOX_H

#include ".\GtPoint3DF.h"
using namespace HTL;

namespace GT
{	
	namespace GtCore
	{
		class HTL_DLLAPI GtAABox : public HtlBase
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			GtAABox(void);
			GtAABox(double dblXMin, double dblXMax,
				double dblYMin, double dblYMax,
				double dblZMin, double dblZMax);
			GtAABox(const GtAABox& rhs);
			virtual ~GtAABox(void);
			//PUBLIC OPERATOR
			GtAABox & operator = (const GtAABox & rhs);

			bool operator == (GtAABox & rhs);
			bool operator != (GtAABox & rhs);

			//Bounding Box Validity Checks
			bool IsBoxValid(void);
			bool IsBoxValidXY(void);
			bool IsBoxValidXZ(void);
			bool IsBoxValidYZ(void);
			//Reset and Zero the Box
			void Reset(void);
			void Zero(void);

			//!Area Volume Metrics
			double GetBaseArea(void);
			double GetVolume(void);
			GtPoint3DF GetCentroid(void);
			GtPoint3DF GetBaseCentroid(void);

			//Get Corner Points
			GtPoint3DF GetXMinYMinZMin(void);
			GtPoint3DF GetXMinYMinZMax(void);
			GtPoint3DF GetXMinYMaxZMin(void);
			GtPoint3DF GetXMinYMaxZMax(void);

			GtPoint3DF GetXMaxYMinZMin(void);
			GtPoint3DF GetXMaxYMinZMax(void);
			GtPoint3DF GetXMaxYMaxZMin(void);
			GtPoint3DF GetXMaxYMaxZMax(void);


		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);

		public:
			double m_dblXMin;
			double m_dblXMax;
			double m_dblYMin;
			double m_dblYMax;
			double m_dblZMin;
			double m_dblZMax;
		};
	};//end namespace GtCore
};//end namepace GT
#endif //GT_AABOX_H