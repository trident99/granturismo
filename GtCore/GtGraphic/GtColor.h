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


#ifndef GT_COLOR_H
#define GT_COLOR_H

#include "..\GtCoreLibRefs.h"
#include ".\GtGraphicEnums.h"
#include ".\GtGraphicStructs.h"
using namespace HTL;

namespace GT
{
	namespace GtCore
	{
		//!Long conversion of RGB values
		ulong CreateLongRGB(int r, int g, int b);
		ulong CreateLongRGBA(int r, int g, int b, int a);

		class HTL_DLLAPI GtColor : public HtlBase
		{
		public:
			//!Default Constructor
			GtColor(int red = 255, int green = 255, int blue = 255, int alpha = 255);
			GtColor(GtRGB color);
			GtColor(const GtColor & rhs);
			//!Destructor
			~GtColor();

			//operator overloads
			GtColor & operator= (const GtColor & rhs);
			virtual bool operator == (const GtColor & ptrRHS );
			virtual bool operator != (const GtColor & ptrRHS );

		public:
			void SetRGB( int r, int g, int b, int a = 255 );//[0,255]
			void SetCYMK( float c, float y, float m, float k);//[0.0,1.0]
			//!CYMK black color [0,255]
			int  Black(void) const;
			//!CYMK black floating point [0.0,1.0]
			float  BlackF(void) const; 
			//!CYMK cyan color [0,255]
			int  Cyan(void) const;
			//!CYMK cyan floating point [0.0,1.0]
			float  CyanF(void) const; 
			//!CYMK magenta color [0,255]
			int  Magenta(void) const;
			//!CYMK magenta floating point [0.0,1.0]
			float  MagentaF(void) const; 
			//!CYMK yellow color [0,255]
			int  Yellow(void) const ;
			//!CYMK yellow floating point [0.0,1.0]
			float  YellowF(void) const; 
			//!Convert the RGB to a long integer
			ulong ToLongRGB(void);
			//!Convert the RGB + Alpha to a long integer
			ulong ToLongRGBA(void);

			//!Make a color that is  percent darker [0,100]
			GtColor  Darker( int percent = 15 ) const; 
			//!Make a color that is  percent lighter [0,100]
			GtColor  Lighter( int percent = 15 ) const;
			//!Is this a valid color
			bool  IsValid(void) const;
			//Get normalized color components [0,1]
			float UnitRed(void);
			float UnitGreen(void);
			float UnitBlue(void);
			float UnitAlpha(void);
		public:
			//SERIALIZATION FUNCTIONS///////////////////////////////////////
			//!Save member data to the current element node
			virtual int Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects);
			//!Load member data from the current element node
			virtual int Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName);


		public:
			//!Red Color component
			int m_intRed;
			//!Green Color component
			int m_intGreen;
			//!Blue Color component
			int m_intBlue;
			//!Alpha Color component
			int m_intAlpha;

		};//end GtEvent

	};//end namespace GtCore

};//end namespace GT

#endif//GT_EVENT_H