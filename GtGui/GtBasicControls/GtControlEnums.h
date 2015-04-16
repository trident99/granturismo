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


#ifndef GT_CONTROL_ENUMS_H
#define GT_CONTROL_ENUMS_H

#include "..\GtGuiLibRefs.h"
using namespace HTL;

namespace GT
{
	namespace GtGui
	{
		enum GtFrameStyle
		{
			FramePlain = 0,  //the frame and contents appear level with the surroundings
			FrameRaised	= 2, //the frame and contents appear raised;
			//draws a 3D raised line using the light and dark colors of the current color group
			FrameSunken = 4, //the frame and contents appear sunken; 
			//draws a 3D sunken line using the light and dark colors of the current color group
		};


	};//end namespace GtCore

};//end namespace GT

//Enumerated type translation functions
namespace HTL
{
	using namespace GT::GtGui;

	//CONVERSION FUNCTIONS FOR GtPenJoinStyle//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtFrameStyle>(GtFrameStyle enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtFrameStyle>(std::string & strVal, GtFrameStyle & enumValReturn);

}

#endif//GT_GRAPHIC_ENUMS_H