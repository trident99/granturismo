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


#ifndef GT_GRAPHIC_STRUCTS_H
#define GT_GRAPHIC_STRUCTS_H

#include "..\GtCoreLibRefs.h"

namespace GT
{
	namespace GtCore
	{

		struct HTL_DLLAPI GtRGB
		{
		public:
			GtRGB()
			{
				//!red component
				m_intRed = 255;
				//!green component
				m_intGreen = 255;
				//!blue component
				m_intBlue = 255;
				//!alpha component
				m_intAlpha = 255;
			};

			//!red component
			int m_intRed;
			//!green component
			int m_intGreen;
			//!blue component
			int m_intBlue;
			//!alpha component
			int m_intAlpha;

		};

		struct HTL_DLLAPI GtCYMK
		{
		public:
			GtCYMK()
			{
				//!red component
				m_intCyan = 0;
				//!green component
				m_intMagenta = 0;
				//!blue component
				m_intYellow = 0;
				//!alpha component
				m_intBlack = 0;
			};

			//!red component
			int m_intCyan;
			//!green component
			int m_intMagenta;
			//!blue component
			int m_intYellow;
			//!alpha component
			int m_intBlack;

		};
		
		struct HTL_DLLAPI GtPixmapPoint
		{
		public:
			long x;
			long y;
			long pix;
		};

		struct HTL_DLLAPI GtPixmapSize
		{
		public:
			long dx;
			long dy;
		};

		struct HTL_DLLAPI GtPixmapQuad
		{
		public:
			GtPixmapPoint p1;
			GtPixmapPoint p2;
			GtPixmapPoint p3;
			GtPixmapPoint p4;
		};

	};//end namespace GtCore

};//end namespace GT

#endif//GT_GRAPHIC_ENUMS_H