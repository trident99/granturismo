/*
**	This file is part of the TridentCAD
**	This software was merged and developed by:
**	
**  Anthony Daniels
**
**  TridentCAD is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  The United States of America Department of Defense has unlimited 
**	usage, redistribution, and modification rights to TridentCAD.
**
**  TridentCAD is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with TridentCAD.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include  ".\GtMaterial.h"

namespace GT
{
	namespace GtCore
	{

		//GtPPLANE///////////////////////////////////////////////////////
		GtMaterial::GtMaterial()
		{
			m_sngShininess = 5.0f;
		};

		GtMaterial::GtMaterial(const GtMaterial & rhs)
		{
			m_sngShininess = rhs.m_sngShininess;
			m_objDiffuseColor = rhs.m_objDiffuseColor;
			m_objSpecularColor = rhs.m_objSpecularColor;
		};
		GtMaterial::~GtMaterial()
		{
			return;
		};
		GtMaterial & GtMaterial::operator = (const GtMaterial & rhs)
		{
			if(this != &rhs)
			{
				m_sngShininess = rhs.m_sngShininess;
				m_objDiffuseColor = rhs.m_objDiffuseColor;
				m_objSpecularColor = rhs.m_objSpecularColor;
			}
			return *this;
		};


	};//end namespace GtCore

};//end namespace GT