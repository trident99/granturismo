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


#ifndef GT_BRUSH_H
#define GT_BRUSH_H

#include "..\GtCoreLibRefs.h"
#include ".\GtColor.h"
#include ".\GtPixmap.h"
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		class HTL_DLLAPI GtBrush : public HtlBase
		{
		public:
			//!Default Constructor
			GtBrush();
			GtBrush ( GtColor & color, GtBrushStyle style = SolidPattern );
			GtBrush(const GtBrush & rhs);
			//!Destructor
			~GtBrush();

			//operator overloads
			GtBrush & operator= (const GtBrush & rhs);
			virtual bool operator == (GtBrush & ptrRHS );
			virtual bool operator != (GtBrush & ptrRHS );

		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//!Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//!Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);


			//!Brush fill style
			HTLMEMVAR_BYVAL_STYLE1(public, GtBrushStyle, objStyle);
			//!Brush color
			HTLMEMVAR_BYREF_STYLE1(public, GtColor, objColor);
			//!Alpha Color component
			HTLMEMVAR_BYREF_STYLE1(public, GtPixmap, objTexture);

		};//end GtEvent

	};//end namespace GtCore

};//end namespace GT

#endif//GT_BRUSH_H