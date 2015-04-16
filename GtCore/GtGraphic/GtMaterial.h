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
#ifndef GT_MATERIAL_H
#define GT_MATERIAL_H

#include ".\GtColor.h"

using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		class HTL_DLLAPI GtMaterial : public HtlBase
		{
		public:
			GtMaterial();
			GtMaterial(const GtMaterial& rhs);
			virtual ~GtMaterial(void);
			//PUBLIC OPERATOR
			//!Assignment Operator
			GtMaterial & operator = (const GtMaterial & rhs);

		public:
			//!Shininess Reflection
			float m_sngShininess;
			//!Diffuse Color
			GtColor m_objDiffuseColor;
			//!Specular Color
			GtColor m_objSpecularColor;
		};
	};//end namespace GtCore

};//end namespace TCAD
#endif