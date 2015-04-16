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

#include ".\GtScaleBase.h"

namespace GT
{
	namespace GtChart
	{
		//!Parent set constructor
		GtScaleBase::GtScaleBase(GtObject* ptrParent)
			:GtObject(ptrParent)
		{
			m_objScaleType = ScaleLinear;
			m_sngScale = 1.0f;
			m_sngOrigin = 0.0f;
		};

		//!Virtual destructor
		GtScaleBase::~GtScaleBase(void)
		{

		};

		//Transform Model to Viewport 
		void GtScaleBase::ModelToViewPt(float & ptModel, float & ptView)
		{
			//linear transformation
			ptView = m_sngOrigin + m_sngScale * ptModel;		
		};

		//Viewport to Model Transformation
		void GtScaleBase::ViewToModelPt(float & ptView, float & ptModel)
		{
			ptModel = (ptView - m_sngOrigin) / m_sngScale;
		};
		void GtScaleBase::Initialize(void)
		{
			return;
		};
	

	};//end namespace GtChart

};//end namespace GT