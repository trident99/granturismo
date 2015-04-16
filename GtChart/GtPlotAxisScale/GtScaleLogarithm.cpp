/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**	QT by Nokia
**  Qwt Widget Library
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

#include ".\GtScaleLogarithm.h"
#include <modHtlMath.h>

namespace GT
{
	namespace GtChart
	{
		//!Parent set constructor
		GtScaleLogarithm::GtScaleLogarithm(GtObject* ptrParent)
			:GtScaleBase(ptrParent)
		{
			m_objScaleType = ScaleLogarithm;
		};

		//!Virtual destructor
		GtScaleLogarithm::~GtScaleLogarithm(void)
		{

		};

		//Transform Model to Viewport 
		void GtScaleLogarithm::ModelToViewPt(float & ptModel, float & ptView)
		{
			//linear transformation
			float trans = log10(ptModel);
			ptView = m_sngOrigin + m_sngScale * trans;
			int z = 10;
		};

		//Viewport to Model Transformation
		void GtScaleLogarithm::ViewToModelPt(float & ptView, float & ptModel)
		{
			float trans = pow(10,ptView);
			ptModel = (trans - m_sngOrigin) / m_sngScale;
		};

		void GtScaleLogarithm::Initialize(void)
		{
			float orig0, orig1;
			m_sngScale = (float)(m_pt1.y - m_pt0.y) / (log10(m_pt1.x) - log10(m_pt0.x));
			orig0 = m_pt0.y - m_sngScale * log10(m_pt0.x);
			orig1 = m_pt1.y - m_sngScale * log10(m_pt1.x);
			m_sngOrigin = orig0;
			return;
		};
	

	};//end namespace GtChart

};//end namespace GT