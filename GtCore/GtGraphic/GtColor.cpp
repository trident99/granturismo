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
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtColor.h"
#include "..\GtMath\GtBasicMath.h"
#include <modHtlArchive.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		//!Long conversion of RGB values
		ulong CreateLongRGB(int r, int g, int b)
		{   
			return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff) );
		};

		ulong CreateLongRGBA(int r, int g, int b, int a)
		{   
			return (((r & 0xff) << 24) + ((g & 0xff) << 16)
				+ ((b & 0xff) << 8)	+ (a & 0xff) );
		};




		//!Default Constructor
		GtColor::GtColor(int red, int green, int blue, int alpha)
			: HtlBase()
		{
			this->m_intRed = red;
			this->m_intGreen = green;
			this->m_intBlue = blue;
			this->m_intAlpha = alpha;			
		};

		GtColor::GtColor(GtRGB color)
		{
			this->m_intRed = color.m_intRed;
			this->m_intGreen = color.m_intGreen;
			this->m_intBlue = color.m_intBlue;
			this->m_intAlpha = color.m_intAlpha;	

		};

		GtColor::GtColor(const GtColor & rhs)
		{
			this->m_intRed = rhs.m_intRed;
			this->m_intGreen = rhs.m_intGreen;
			this->m_intBlue = rhs.m_intBlue;
			this->m_intAlpha = rhs.m_intAlpha;
		};
		//!Destructor
		GtColor::~GtColor()
		{
			//do nothing
		};

		//operator overloads
		GtColor & GtColor::operator= (const GtColor & rhs)
		{
			if(&rhs != this)
			{
				this->m_intRed = rhs.m_intRed;
				this->m_intGreen = rhs.m_intGreen;
				this->m_intBlue = rhs.m_intBlue;
				this->m_intAlpha = rhs.m_intAlpha;
			}
			return (*this);
		};

		bool GtColor::operator == (const GtColor & rhs )
		{
			if(	m_intRed != rhs.m_intRed){return false;};
			if(	m_intGreen != rhs.m_intGreen){return false;};
			if(	m_intBlue != rhs.m_intBlue){return false;};
			if(	m_intAlpha != rhs.m_intAlpha){return false;};
			//else made it through, equal
			return true;
		};
		bool GtColor::operator != (const GtColor & rhs )
		{
			if(	m_intRed != rhs.m_intRed){return true;};
			if(	m_intGreen != rhs.m_intGreen){return true;};
			if(	m_intBlue != rhs.m_intBlue){return true;};
			if(	m_intAlpha != rhs.m_intAlpha){return true;};
			//else made it through, equal
			return false;		
		};


		void GtColor::SetRGB( int r, int g, int b, int a )
		{
			this->m_intRed = r;
			this->m_intGreen = g;
			this->m_intBlue = b;
			this->m_intAlpha = a;	
		};

		/*CMYK to RGB conversion formula
		The R,G,B values are given in the range of 0..255.
		The red (R) color is calculated from the cyan (C) and black (K) colors:
		R = 255 × (1-C) × (1-K)
		The green color (G) is calculated from the magenta (M) and black (K) colors:
		G = 255 × (1-M) × (1-K)
		The blue color (B) is calculated from the yellow (Y) and black (K) colors:
		B = 255 × (1-Y) × (1-K)
		*/

		void GtColor::SetCYMK( float c, float y, float m, float k)
		{
			m_intRed = gRound(255.0f * (1.0f - c) * (1.0f - k));
			m_intGreen = gRound(255.0f * (1.0f - m) * (1.0f - k));
			m_intBlue = gRound(255.0f * (1.0f - y) * (1.0f - k));
		};






		/*RGB to CMYK conversion formula
		The R,G,B values are divided by 255 to change the range from 0..255 to 0..1:
		R' = R/255
		G' = G/255
		B' = B/255
		The black key (K) color is calculated from the red (R'), green (G') and blue (B') colors:
		K = 1-max(R', G', B')
		The cyan color (C) is calculated from the red (R') and black (K) colors:
		C = (1-R'-K) / (1-K)
		The magenta color (M) is calculated from the green (G') and black (K) colors:
		M = (1-G'-K) / (1-K)
		The yellow color (Y) is calculated from the blue (B') and black (K) colors:
		Y = (1-B'-K) / (1-K)
		*/



		//!CYMK black color
		int  GtColor::Black(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			return gRound(K * 255.0f);

		};
		//!CYMK black floating point
		float  GtColor::BlackF(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			return (K);
		}; 
		//!CYMK cyan color
		int  GtColor::Cyan(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			float C = (1.0f - R - K) / (1.0f -K);
			return gRound(C * 255.0f);
		};
		//!CYMK cyan floating point
		float  GtColor::CyanF(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			float C = (1.0f - R - K) / (1.0f -K);
			return (C);
		}; 
		//!CYMK magenta color
		int  GtColor::Magenta(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			float M = (1.0f - G - K) / (1.0f -K);
			return gRound(M * 255.0f);
		};
		//!CYMK magenta floating point
		float  GtColor::MagentaF(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			float M = (1.0f - G - K) / (1.0f -K);
			return (M);

		}; 
		//!CYMK yellow color
		int  GtColor::Yellow(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			float Y = (1.0f - B - K) / (1.0f -K);
			return gRound(Y * 255.0f);
		};
		//!CYMK yellow floating point
		float  GtColor::YellowF(void) const
		{
			float R = float(m_intRed)/255.0f;
			float G = float(m_intGreen)/255.0f;
			float B = float(m_intBlue)/255.0f;
			float K = 1.0f - max(R,max(G, B));
			float Y = (1.0f - B - K) / (1.0f -K);
			return (Y);
		}; 

		//!Convert the RGB to a long integer
		ulong GtColor::ToLongRGB(void)
		{
			return ((m_intRed & 0xff) << 16) + ((m_intGreen & 0xff) << 8) + (m_intBlue & 0xff);
		};
		//!Convert the RGB + Alpha to a long integer
		ulong GtColor::ToLongRGBA(void)
		{
			ulong val;
			val = ((m_intRed & 0xff) << 24) + ((m_intGreen & 0xff) << 16)
				+ ((m_intBlue & 0xff) << 8) + (m_intAlpha & 0xff);
			return val;
		};

		//!Make a color that is  percent darker
		GtColor  GtColor::Darker( int percent) const
		{
			float factor = float(percent) / 100.0f;
			float R = (1.0f - factor) * m_intRed;
			float G = (1.0f - factor) * m_intGreen;
			float B = (1.0f - factor) * m_intBlue;
			return GtColor(gRound(R), gRound(G), gRound(B), m_intAlpha);
			
		}; 
		//!Make a color that is  percent lighter
		GtColor  GtColor::Lighter( int percent) const
		{
			float factor = float(percent) / 100.0f;
			float R = (1.0f + factor) * m_intRed;
			R = min(R,255.0f);
			float G = (1.0f + factor) * m_intGreen;
			G= min(G,255.0f);
			float B = (1.0f + factor) * m_intBlue;
			B= min(B,255.0f);
			return GtColor(gRound(R), gRound(G), gRound(B), m_intAlpha);
		};

		bool  GtColor::IsValid(void) const
		{
			if( (m_intRed < 0)||(m_intGreen < 0) ||
				(m_intBlue < 0)||(m_intAlpha < 0) )
			{//then invalid
				return true;
			};
			if( (m_intRed > 255)||(m_intGreen > 255) ||
				(m_intBlue > 255)||(m_intAlpha > 255) )
			{//then invalid
				return true;
			};
			//otherwise valid
			return false;
		}; 

		float GtColor::UnitRed(void)
		{
			return (float(m_intRed)/(255.0f));
		};
		float GtColor::UnitGreen(void)
		{
			return (float(m_intGreen)/(255.0f));
		};
		float GtColor::UnitBlue(void)
		{
			return (float(m_intBlue)/(255.0f));
		};
		float GtColor::UnitAlpha(void)
		{
			return (float(m_intAlpha)/(255.0f));
		};




	//Virtual Inheritance Serialization Engines
		//SERIALIZATION ACCESSOR MACRO///////////////////////////////////////
		int GtColor::Save(HTL::HtlElement * ptrCurrNode, std::string strMemVarName, bool blnWithSubObjects)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Save(ptrCurrNode, strMemVarName, blnWithSubObjects);
			//Standard Member Variables
			intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intRed",m_intRed,false);
			intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intGreen",m_intGreen,false);
			intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intBlue",m_intBlue,false);
			intReturn &= SetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intAlpha",m_intAlpha,false);
			//Sub Object Member Variables
			if(blnWithSubObjects)
			{
				/*...*/
			};

			return intReturn;
		};

		int GtColor::Load(HTL::HtlElement * ptrCurrNode, std::string strMemVarName)
		{

			int intReturn = 0;
			//SAFETY CHECK //put at top of all Serialize Methods
			if(!ptrCurrNode){return 0;};
			//CALL PARENT CLASS Serialize()
			/*...*/
			HtlBase::Load(ptrCurrNode,strMemVarName);
			//Standard Member Variables
			intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intRed",m_intRed);
			intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intGreen",m_intGreen);
			intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intBlue",m_intBlue);
			intReturn &= GetHtlMemVar<int,CPP_INT>(ptrCurrNode,"m_intAlpha",m_intAlpha);

			return intReturn;

		};



	};//end namespace GtCore

};//end namespace GT

