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

#include ".\GtPlotItem.h"

namespace GT
{
	namespace GtChart
	{
			//!Parent set constructor
		GtPlotItem::GtPlotItem(GtObject* ptrParent)
			:GtObject(ptrParent)
		{
			//!The boolean flag for whether or not the item is visible
			m_blnVisible = true;
			//!the point in canvas of the item
			m_objPos.Zero();
			//!The z render order of the item
			m_intZOrder = 0;
			//!The string designator of the item
			m_ptrObj = NULL;

		};
			//!Virtual destructor
		GtPlotItem::~GtPlotItem(void)
		{
			m_ptrObj = NULL;
		};
	

		//!Get the bounding rectangle of the item
		GtRectI &  GtPlotItem::BoundingModelRect(void)
		{
			m_modelRect.Zero();
			return m_modelRect;		
		};
		//!Get the bounding rectangle of the item
		GtRectI & GtPlotItem::BoundingCanvasRect(void)
		{
			m_canvasRect.Zero();
			return m_canvasRect;
		};

	};//end namespace GtChart

};//end namespace GT