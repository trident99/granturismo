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

#ifndef GT_CORE_STRUCTS_H
#define GT_CORE_STRUCTS_H

#include ".\GtCoreLibRefs.h"
#include ".\modGtGeometry.h"

using namespace HTL;

namespace GT
{
	namespace GtCore
	{
			struct HTL_DLLAPI GtTextLine
		{
		public:
			GtTextLine()
			{
				m_lngLine = 0;
				m_startPos = 0;
				m_endPos = 0;
				m_startHighlight = 0;
				m_endHighlight = 0;
			};
			//operator overloads
			GtTextLine & operator= ( GtTextLine & rhs)
			{
				if(&rhs != this)
				{
					m_objFrame = rhs.m_objFrame;
					m_lngLine = rhs.m_lngLine;
					m_startPos = rhs.m_startPos;
					m_endPos = rhs.m_endPos;
					m_startHighlight = rhs.m_startHighlight;
					m_endHighlight = rhs.m_endHighlight;
				};
				return *this;
			};

		public:
			//!The drawing rect for the text line
			GtRectI m_objFrame;
			//!The drawing rect for the text line
			GtRectI m_objHighFrame;
			//!The line number
			size_t m_lngLine;
			//!The starting cursor position of the line
			size_t m_startPos;
			//!The ending cursor position of the line
			size_t m_endPos;
			//!The start highlight position
			long m_startHighlight;
			//!The end highlight position
			long m_endHighlight;

		};

			
		struct HTL_DLLAPI GtCursor
		{
		public:
			GtCursor()
			{
				m_lngLine = 0;
				m_charPos = 0;
				m_xPos = 0;
				m_yPos = 0;
			}

			GtCursor & operator= ( GtCursor & rhs)
			{
				if(&rhs != this)
				{
					m_lngLine = rhs.m_lngLine;
					m_charPos = rhs.m_charPos;
					m_xPos = rhs.m_xPos;
					m_yPos = rhs.m_yPos;
				};
				return *this;
			};
		public:
			//!The line number
			size_t m_lngLine;
			//character position
			size_t m_charPos;
			//!The xPos in the control
			int m_xPos;
			//!The yPos in the control
			int m_yPos;
		};


	};//end namespace GtCore
};//end namespace GT

#endif