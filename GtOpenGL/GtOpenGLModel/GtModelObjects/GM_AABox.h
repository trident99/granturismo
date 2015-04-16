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
#ifndef GM_AABOX_H
#define GM_AABOX_H

#include "..\GtCadObject.h"

namespace GT
{
	namespace GtOpenGL
	{

		class HTL_DLLAPI GM_AABox : public GtCadObject
		{
			//PUBLIC CONSTRUCTORS & DESTRUCTOR
		public:
			GM_AABox(void);
			GM_AABox(double dblXMin, double dblXMax,
				double dblYMin, double dblYMax,
				double dblZMin, double dblZMax);
			GM_AABox(GM_AABox& rhs);
			virtual ~GM_AABox(void);
			//PUBLIC OPERATOR
			GM_AABox & operator = (GM_AABox & rhs);

			bool operator == (GM_AABox & rhs);
			bool operator != (GM_AABox & rhs);
		public:
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
			//FROM QGLMODELBOX METHODS//////////////////////////////
			//!Return the bounding box of the item 
			virtual GtAABox GetBoundingBox(void);
			//!Return the selection box of the item 
			virtual GtAABox GetSelectionBox(void);

			virtual void RenderOverlay(const GtViewpoint & ptrCurrViewPoint);

		public:
			double m_dblXMin;
			double m_dblXMax;
			double m_dblYMin;
			double m_dblYMax;
			double m_dblZMin;
			double m_dblZMax;

		private:

			//OVERRIDDEN DRAWING FUNCTIONS FROM MODEL ITEM
			void DrawSurfaces(void);
			void DrawCurves(void);
			void DrawPoints(void);
		};
	};//end namespace GtOpenGL
};//end namespace GT
#endif //GT_AABOX_H