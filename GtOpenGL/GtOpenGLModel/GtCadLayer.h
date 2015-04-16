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

#ifndef GT_CADLAYER_H
#define GT_CADLAYER_H
#include "..\GtOpenGLStructs.h"

using namespace HTL;

namespace GT
{
	namespace GtOpenGL
	{
		class HTL_DLLAPI GtCadLayer : public HtlBase
		{

		public:
			GtCadLayer();
			~GtCadLayer();

		};//end class GtCadLayer
	};//end namespace GtOpenGL
};//end namespace GT
#endif //GT_CADLAYER_H