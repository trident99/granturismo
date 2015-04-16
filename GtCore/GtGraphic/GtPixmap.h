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

/*
** GIVE CREDIT WHERE CREDIT IS DUE
** GtPixmap is a slimmed down version of the 
** CBitmapEx - Free C++ Bitmap Manipulation Class
** written by:
** darkoman 
** Software Developer (Senior) Elektromehanika d.o.o. Nis 
** Serbia Serbia 
** Thank you very much for the code contribution
*/

#ifndef GT_PIXMAP_H
#define GT_PIXMAP_H

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include ".\GtColor.h"

namespace GT
{
	namespace GtCore
	{

#define _PI	3.1415926f											// Value of PI
#define _BITS_PER_PIXEL_32	32									// 32-bit color depth
#define _BITS_PER_PIXEL_24	24									// 24-bit color depth
#define _PIXEL	DWORD											// Pixel
#define _RGB(r,g,b)	(((r) << 16) | ((g) << 8) | (b))			// Convert to RGB
#define _GetRValue(c)	((BYTE)(((c) & 0x00FF0000) >> 16))		// Red color component
#define _GetGValue(c)	((BYTE)(((c) & 0x0000FF00) >> 8))		// Green color component
#define _GetBValue(c)	((BYTE)((c) & 0x000000FF))				// Blue color component


//DEFINES KEPT FOR FUTURE REFERENCE
//typedef long fixed;												// Our new fixed point type
//#define itofx(x) ((x) << 8)										// Integer to fixed point
//#define ftofx(x) (long)((x) * 256)								// Float to fixed point
//#define dtofx(x) (long)((x) * 256)								// Double to fixed point
//#define fxtoi(x) ((x) >> 8)										// Fixed point to integer
//#define fxtof(x) ((float) (x) / 256)							// Fixed point to float
//#define fxtod(x) ((double)(x) / 256)							// Fixed point to double
//#define Mulfx(x,y) (((x) * (y)) >> 8)							// Multiply a fixed by a fixed
//#define Divfx(x,y) (((x) << 8) / (y))							// Divide a fixed by a fixed

		//!This class is a basic container for a bitmap image. 
		//It is based on the CBitmapEx class developed by darkoman of the Code Project (www.codeproject.com)
		class HTL_DLLAPI GtPixmap
		{
		public:
			//!Default Constructor
			GtPixmap();
			GtPixmap(long width, long height);
			//!Copy Constructor
			GtPixmap(const GtPixmap & rhs);
			//!Destructor
			~GtPixmap();

			//Operator overloads
			GtPixmap & operator= (const GtPixmap & rhs);
		public:

			void Load(std::string & lpszBitmapFile);
			void Load(LPBYTE lpBitmapData);
			void Load(HBITMAP hBitmap);
			void Save(std::string & lpszBitmapFile);
			void Save(LPBYTE lpBitmapData);
			void Save(HBITMAP& hBitmap);

		public:
			LPBITMAPFILEHEADER GetFileInfo() {return &m_bfh;}
			LPBITMAPINFOHEADER GetInfo() {return &m_bih;}
			long GetWidth() {return m_bih.biWidth;}
			long GetHeight() {return m_bih.biHeight;}
			long GetPitch() {return m_iPitch;}
			long GetBpp() {return (m_iBpp<<3);}
			long GetPaletteEntries() {return m_iPaletteEntries;}
			LPRGBQUAD GetPalette() {return m_lpPalette;}
			DWORD GetSize() {return m_dwSize;}
			LPBYTE GetData() {return m_lpData;}
			bool IsValid() {return (m_lpData != NULL);}

		public:
			void FlipHorizontal();
			void FlipVertical();
			void ConvertToHSV();
			void ConvertToRGB();
			void ConvertTo32Bpp();
			void ConvertTo24Bpp();
			void SetPixel(long x, long y, _PIXEL pixel);
			_PIXEL GetPixel(long x, long y);

		private:
			// Private methods
			_PIXEL _RGB2HSV(_PIXEL rgbPixel);
			_PIXEL _HSV2RGB(_PIXEL hsvPixel);
			float _ARGH(float xa, float ya);
			float _MODH(float x, float y, float z);

		private:
			// Private members
			//!Bitmap file header
			BITMAPFILEHEADER m_bfh;
			//!Bitmap Information Header
			BITMAPINFOHEADER m_bih;
			//!Palette Entries
			long m_iPaletteEntries;
			//!Color Palette
			RGBQUAD m_lpPalette[256];
			//!Pixel pitch
			long m_iPitch;
			//!Bits Per Pixel
			long m_iBpp;
			//!Image Size
			DWORD m_dwSize;
			//!Pixel Data
			LPBYTE m_lpData;
			//!Image Color Mode
			GtColorMode m_ColorMode;

		};//end GtEvent

	};//end namespace GtCore

};//end namespace GT

#endif//GT_PIXMAP_H