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

#pragma once
#pragma warning(push)
#pragma warning (disable : 4005 ) /* macro redefinition */
#define HTL_DLLEXPORT
#pragma warning(pop)

#include ".\GtPixmap.h"

#include <io.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <math.h>
using namespace HTL;

namespace GT
{
	namespace GtCore
	{

		//!Default Constructor
		GtPixmap::GtPixmap()
		{

		};

		GtPixmap::GtPixmap(long width, long height)
		{
		};

		GtPixmap::GtPixmap(const GtPixmap & rhs)
		{

		};
		//!Destructor
		GtPixmap::~GtPixmap()
		{
			//do nothing
		};

		//operator overloads
		GtPixmap & GtPixmap::operator= (const GtPixmap & rhs)
		{
			if(&rhs != this)
			{

			}
			return (*this);
		};

		void GtPixmap::Load(std::string & lpszBitmapFile)
		{
			// Check for valid .BMP file path
			if (!lpszBitmapFile.empty())
			{
				// Open .BMP file
				FILE* file = fopen(lpszBitmapFile.c_str(), ("rb"));
				if (file != NULL)
				{
					// Deinit members
					if (m_lpData != NULL)
					{
						free(m_lpData);
						m_lpData = NULL;
					}

					// Read BITMAPFILEHEADER info
					fread(&m_bfh, 1, sizeof(BITMAPFILEHEADER), file);

					// Read BITMAPINFOHEADER info
					fread(&m_bih, 1, sizeof(BITMAPINFOHEADER), file);

					// Calculate pitch
					m_iBpp = m_bih.biBitCount >> 3;
					m_iPitch = m_iBpp * m_bih.biWidth;
					while ((m_iPitch & 3) != 0)
						m_iPitch++;

					// Check for bit-depth (8, 16, 24 and 32bpp only)
					if (m_bih.biBitCount >= 8)
					{
						if (m_bih.biBitCount == 8)
						{
							// Calculate palette entries
							m_iPaletteEntries = m_bih.biClrUsed;
							if (m_iPaletteEntries == 0)
								m_iPaletteEntries = 256;

							// Read palette info
							fread(m_lpPalette, m_iPaletteEntries, sizeof(RGBQUAD), file);
						}

						// Read image data
						m_dwSize = m_iPitch * m_bih.biHeight;
						m_lpData = (LPBYTE)malloc(m_dwSize*sizeof(BYTE));
						fread(m_lpData, m_dwSize, sizeof(BYTE), file);

						// Convert to 32bpp bitmap
						ConvertTo32Bpp();
					}

					// Close .BMP file
					fclose(file);
				}
			}
		}

		void GtPixmap::Load(LPBYTE lpBitmapData)
		{
			// Check for valid bitmap data buffer
			if (lpBitmapData != NULL)
			{
				// Deinit members
				if (m_lpData != NULL)
				{
					free(m_lpData);
					m_lpData = NULL;
				}

				// Read BITMAPFILEHEADER info
				memcpy(&m_bfh, lpBitmapData, sizeof(BITMAPFILEHEADER));

				// Read BITMAPINFOHEADER info
				memcpy(&m_bih, lpBitmapData+sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));

				// Calculate pitch
				m_iBpp = m_bih.biBitCount >> 3;
				m_iPitch = m_iBpp * m_bih.biWidth;
				while ((m_iPitch & 3) != 0)
					m_iPitch++;

				// Check for bit-depth (8, 16, 24 and 32bpp only)
				if (m_bih.biBitCount >= 8)
				{
					if (m_bih.biBitCount == 8)
					{
						// Calculate palette entries
						m_iPaletteEntries = m_bih.biClrUsed;
						if (m_iPaletteEntries == 0)
							m_iPaletteEntries = 256;

						// Read palette info
						memcpy(m_lpPalette, lpBitmapData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER), m_iPaletteEntries*sizeof(RGBQUAD));
					}

					// Read image data
					m_dwSize = m_iPitch * m_bih.biHeight;
					m_lpData = (LPBYTE)malloc(m_dwSize*sizeof(BYTE));
					memcpy(m_lpData, lpBitmapData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+m_iPaletteEntries*sizeof(RGBQUAD), m_dwSize*sizeof(BYTE));

					// Convert to 32bpp bitmap
					ConvertTo32Bpp();
				}
			}
		}

		void GtPixmap::Load(HBITMAP hBitmap)
		{
			// Check for valid bitmap handle
			if (hBitmap != NULL)
			{
				// Deinit members
				if (m_lpData != NULL)
				{
					free(m_lpData);
					m_lpData = NULL;
				}

				// Get bitmap info
				BITMAP bmp;
				GetObject(hBitmap, sizeof(BITMAP), &bmp);

				// Check for valid bitmap format (16, 24 and 32bpp only)
				if (bmp.bmBitsPixel > 8)
				{
					// Get bitmap data
					m_iBpp = bmp.bmBitsPixel >> 3;
					m_iPitch = bmp.bmWidthBytes;
					m_dwSize = bmp.bmHeight * m_iPitch;
					m_lpData = (LPBYTE)malloc(m_dwSize*sizeof(BYTE));
					GetBitmapBits(hBitmap, m_dwSize*sizeof(BYTE), m_lpData);

					// Format BITMAPFILEHEADER info
					memset(&m_bfh, 0, sizeof(BITMAPFILEHEADER));
					m_bfh.bfType = 'MB';
					m_bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_dwSize;
					m_bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

					// Format BITMAPINFOHEADER info
					memset(&m_bih, 0, sizeof(BITMAPINFOHEADER));
					m_bih.biSize = sizeof(BITMAPINFOHEADER);
					m_bih.biWidth = bmp.bmWidth;
					m_bih.biHeight = bmp.bmHeight;
					m_bih.biPlanes = 1;
					m_bih.biBitCount = bmp.bmBitsPixel;

					// Convert to 32bpp bitmap
					ConvertTo32Bpp();
					FlipVertical();
				}
			}
		}

		void GtPixmap::Save(std::string & lpszBitmapFile)
		{
			// Check for valid .BMP file path
			if (!lpszBitmapFile.empty())
			{
				// Convert to 24bpp bitmap
				ConvertTo24Bpp();

				// Open .BMP file
				FILE* file = fopen(lpszBitmapFile.c_str(), ("wb"));
				if (file != NULL)
				{
					// Write BITMAPFILEHEADER info
					fwrite(&m_bfh, 1, sizeof(BITMAPFILEHEADER), file);

					// Write BITMAPINFOHEADER info
					fwrite(&m_bih, 1, sizeof(BITMAPINFOHEADER), file);

					// Check for palettized bitmap
					if (m_bih.biBitCount == 8)
					{
						// Write palette info
						fwrite(m_lpPalette, m_iPaletteEntries, sizeof(RGBQUAD), file);
					}

					// Write image data
					fwrite(m_lpData, m_dwSize, sizeof(BYTE), file);

					// Close .BMP file
					fclose(file);
				}

				// Convert to 32bpp bitmap
				ConvertTo32Bpp();
			}
		}

		void GtPixmap::Save(LPBYTE lpBitmapData)
		{
			// Check for valid bitmap data buffer
			if (lpBitmapData != NULL)
			{
				// Convert to 24bpp bitmap
				ConvertTo24Bpp();

				// Write BITMAPFILEHEADER info
				memcpy(lpBitmapData, &m_bfh, sizeof(BITMAPFILEHEADER));

				// Write BITMAPINFOHEADER info
				memcpy(lpBitmapData+sizeof(BITMAPFILEHEADER), &m_bih, sizeof(BITMAPINFOHEADER));

				// Check for palettized bitmap
				if (m_bih.biBitCount == 8)
				{
					// Write palette info
					memcpy(lpBitmapData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER), m_lpPalette, m_iPaletteEntries*sizeof(RGBQUAD));
				}

				// Write image data
				memcpy(lpBitmapData+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+m_iPaletteEntries*sizeof(RGBQUAD), m_lpData, m_dwSize*sizeof(BYTE));

				// Convert to 32bpp bitmap
				ConvertTo32Bpp();
			}
		}

		void GtPixmap::Save(HBITMAP& hBitmap)
		{
			// Check for valid bitmap data buffer and handle
			if ((IsValid()) && (hBitmap == NULL))
			{
				// Write bitmap data
				FlipVertical();
				hBitmap = CreateBitmap(m_bih.biWidth, m_bih.biHeight, 1, m_bih.biBitCount, m_lpData);
				FlipVertical();
			}
		}


		void GtPixmap::SetPixel(long x, long y, _PIXEL pixel)
		{
			// Check for valid bitmap
			if (IsValid())
			{
				// Set pixel color
				long _x = max(0, min(m_bih.biWidth-1, x));
				long _y = max(0, min(m_bih.biHeight-1, y));
				DWORD dwTotalOffset = (m_bih.biHeight-1-_y)*m_iPitch + _x*m_iBpp;
				LPDWORD lpData = (LPDWORD)m_lpData;
				lpData[dwTotalOffset>>2] = pixel;
			}
		}

		_PIXEL GtPixmap::GetPixel(long x, long y)
		{
			_PIXEL pixel = _RGB(0,0,0);

			// Check for valid bitmap
			if (IsValid())
			{
				// Get pixel color
				long _x = max(0, min(m_bih.biWidth-1, x));
				long _y = max(0, min(m_bih.biHeight-1, y));
				DWORD dwTotalOffset = (m_bih.biHeight-1-_y)*m_iPitch + _x*m_iBpp;
				LPDWORD lpData = (LPDWORD)m_lpData;
				pixel = lpData[dwTotalOffset>>2];
			}

			return pixel;
		}

		_PIXEL GtPixmap::_RGB2HSV(_PIXEL rgbPixel)
		{
			_PIXEL hsvPixel = 0;

			// Convert RGB value to HSV value
			BYTE red = _GetRValue(rgbPixel);
			BYTE green = _GetGValue(rgbPixel);
			BYTE blue = _GetBValue(rgbPixel);
			BYTE temp = (red + green + blue) / 3;
			float xa = (green - red) / sqrt(2.0f);
			float ya = (2*blue - red - green) / sqrt(6.0f);
			float _hue = _ARGH(xa, ya) * (180.0f / _PI) + 150.0f;
			float _saturation = _ARGH(temp, _MODH((float)(red-temp), (float)(green-temp), (float)(blue-temp))) * 100.0f / atan(sqrt(6.0f));
			float _value = (float)temp / 2.55f;
			if ((_saturation == 0.0f) || (_value == 0.0f))
				_hue = 0.0f;
			if (_hue < 0.0f)
				_hue = _hue + 360.0f;
			if (_hue >= 360.0f)
				_hue = _hue - 360.0f;
			BYTE hue = (BYTE)((_hue / 360.0f) * 255.0f);
			BYTE saturation = (BYTE)((_saturation / 100.0f) * 255.0f);
			BYTE value = (BYTE)((_value / 100.0f) * 255.0f);
			hsvPixel = _RGB(hue, saturation, value);

			return hsvPixel;
		}

		_PIXEL GtPixmap::_HSV2RGB(_PIXEL hsvPixel)
		{
			_PIXEL rgbPixel = 0;

			// Convert HSV value to RGB value
			BYTE hue = _GetRValue(hsvPixel);
			BYTE saturation = _GetGValue(hsvPixel);
			BYTE value = _GetBValue(hsvPixel);
			float _hue = ((float)hue / 255.0f) * 360.0f;
			float _saturation = ((float)saturation / 255.0f) * 100.0f;
			float _value = ((float)value / 255.0f) * 100.0f;
			float _angle = (_hue - 150.0f) * _PI / 180.0f;
			float _ur = _value * 2.55f;
			float _radius = _ur * tan(_saturation * atan(sqrt(6.0f)) / 100.0f);
			float _vr = _radius * cos(_angle) / sqrt(2.0f);
			float _wr = _radius * sin(_angle) / sqrt(6.0f);
			float _red = _ur - _vr - _wr;
			float _green = _ur + _vr - _wr;
			float _blue = _ur + 2*_wr;
			float _rdim;
			if (_red < 0.0f)
			{
				_rdim = _ur / (_vr + _wr);
				_red = 0.0f;
				_green = _ur + (_vr - _wr) * _rdim;
				_blue = _ur + 2*_wr * _rdim;
			}
			else if (_green < 0.0f)
			{
				_rdim = -_ur / (_vr - _wr);
				_red = _ur - (_vr + _wr) * _rdim;
				_green = 0.0f;
				_blue = _ur + 2*_wr * _rdim;
			}
			else if (_blue < 0.0f)
			{
				_rdim = -_ur / (2*_wr);
				_red = _ur - (_vr + _wr) * _rdim;
				_green = _ur + (_vr - _wr) * _rdim;
				_blue = 0.0f;
			}
			if (_red > 255.0f)
			{
				_rdim = (_ur - 255.0f) / (_vr + _wr);
				_red = 255.0f;
				_green = _ur + (_vr - _wr) * _rdim;
				_blue = _ur + 2*_wr * _rdim;
			}
			if (_green > 255.0f)
			{
				_rdim = (255.0f - _ur) / (_vr - _wr);
				_red = _ur - (_vr + _wr) * _rdim;
				_green = 255.0f;
				_blue = _ur + 2*_wr * _rdim;
			}
			if (_blue > 255.0f)
			{
				_rdim = (255.0f - _ur) / (2*_wr);
				_red = _ur - (_vr + _wr) * _rdim;
				_green = _ur + (_vr - _wr) * _rdim;
				_blue = 255.0f;
			}
			BYTE red = (BYTE)_red;
			BYTE green = (BYTE)_green;
			BYTE blue = (BYTE)_blue;
			rgbPixel = _RGB(red, green, blue);

			return rgbPixel;
		}


		void GtPixmap::FlipHorizontal()
		{
			// Check for valid bitmap
			if (IsValid())
			{
				// Calculate flipping params
				long _width = m_bih.biWidth / 2;

				// Flip bitmap horizontaly
				DWORD dwDstHorizontalStartOffset = 0;
				DWORD dwDstHorizontalOffset;
				DWORD dwDstVerticalOffset = 0;
				DWORD dwDstTotalOffset;
				LPDWORD lpDstData = (LPDWORD)m_lpData;
				DWORD dwSrcHorizontalStartOffset = (m_bih.biWidth-1) * m_iBpp;
				DWORD dwSrcHorizontalOffset;
				DWORD dwSrcVerticalOffset = 0;
				DWORD dwSrcTotalOffset;
				LPDWORD lpSrcData = (LPDWORD)m_lpData;
				for (long i=0; i<m_bih.biHeight; i++)
				{
					dwDstHorizontalOffset = dwDstHorizontalStartOffset;
					dwSrcHorizontalOffset = dwSrcHorizontalStartOffset;
					for (long j=0; j<_width; j++)
					{
						// Update destination total offset
						dwDstTotalOffset = dwDstVerticalOffset + dwDstHorizontalOffset;

						// Update source total offset
						dwSrcTotalOffset = dwSrcVerticalOffset + dwSrcHorizontalOffset;

						// Update bitmap
						_PIXEL pixelTmp = lpDstData[dwDstTotalOffset>>2];
						lpDstData[dwDstTotalOffset>>2] = lpSrcData[dwSrcTotalOffset>>2];
						lpSrcData[dwSrcTotalOffset>>2] = pixelTmp;

						// Update destination horizontal offset
						dwDstHorizontalOffset += m_iBpp;

						// Update source horizontal offset
						dwSrcHorizontalOffset -= m_iBpp;
					}

					// Update destination vertical offset
					dwDstVerticalOffset += m_iPitch;

					// Update source vertical offset
					dwSrcVerticalOffset += m_iPitch;
				}
			}
		}

		void GtPixmap::FlipVertical()
		{
			// Check for valid bitmap
			if (IsValid())
			{
				// Calculate flipping params
				long _height = m_bih.biHeight / 2;

				// Flip bitmap verticaly
				DWORD dwDstTotalOffset = 0;
				LPDWORD lpDstData = (LPDWORD)m_lpData;
				DWORD dwSrcTotalOffset = (m_bih.biHeight-1) * m_iPitch;
				LPDWORD lpSrcData = (LPDWORD)m_lpData;
				LPDWORD lpTmpData = (LPDWORD)malloc(m_iPitch*sizeof(BYTE));
				for (long i=0; i<_height; i++)
				{
					// Update bitmap
					memcpy(lpTmpData, lpDstData+(dwDstTotalOffset>>2), m_iPitch*sizeof(BYTE));
					memcpy(lpDstData+(dwDstTotalOffset>>2), lpSrcData+(dwSrcTotalOffset>>2), m_iPitch*sizeof(BYTE));
					memcpy(lpSrcData+(dwSrcTotalOffset>>2), lpTmpData, m_iPitch*sizeof(BYTE));

					// Update destination total offset
					dwDstTotalOffset += m_iPitch;

					// Update source total offset
					dwSrcTotalOffset -= m_iPitch;
				}
				free(lpTmpData);
			}
		}



		void GtPixmap::ConvertToHSV()
		{
			// Check for valid bitmap
			if ((IsValid()) && (m_ColorMode == CM_RGB))
			{
				// Convert RGB bitmap to HSV
				DWORD dwHorizontalOffset;
				DWORD dwVerticalOffset = 0;
				DWORD dwTotalOffset;
				LPDWORD lpDstData = (LPDWORD)m_lpData;
				for (long i=0; i<m_bih.biHeight; i++)
				{
					dwHorizontalOffset = 0;
					for (long j=0; j<m_bih.biWidth; j++)
					{
						// Update total offset
						dwTotalOffset = dwVerticalOffset + dwHorizontalOffset;

						// Update bitmap
						lpDstData[dwTotalOffset>>2] = _RGB2HSV(lpDstData[dwTotalOffset>>2]);

						// Update horizontal offset
						dwHorizontalOffset += m_iBpp;
					}

					// Update vertical offset
					dwVerticalOffset += m_iPitch;
				}

				// Update color mode
				m_ColorMode = CM_HSV;
			}
		}

		void GtPixmap::ConvertToRGB()
		{
			// Check for valid bitmap
			if ((IsValid()) && (m_ColorMode == CM_HSV))
			{
				// Convert HSV bitmap to RGB
				DWORD dwHorizontalOffset;
				DWORD dwVerticalOffset = 0;
				DWORD dwTotalOffset;
				LPDWORD lpDstData = (LPDWORD)m_lpData;
				for (long i=0; i<m_bih.biHeight; i++)
				{
					dwHorizontalOffset = 0;
					for (long j=0; j<m_bih.biWidth; j++)
					{
						// Update total offset
						dwTotalOffset = dwVerticalOffset + dwHorizontalOffset;

						// Update bitmap
						lpDstData[dwTotalOffset>>2] = _HSV2RGB(lpDstData[dwTotalOffset>>2]);

						// Update horizontal offset
						dwHorizontalOffset += m_iBpp;
					}

					// Update vertical offset
					dwVerticalOffset += m_iPitch;
				}

				// Update color mode
				m_ColorMode = CM_RGB;
			}
		}


		void GtPixmap::ConvertTo32Bpp()
		{
			// Check for valid bitmap
			if (IsValid())
			{
				// Calculate new params
				long _bpp = (_BITS_PER_PIXEL_32 >> 3);
				long _pitch = m_bih.biWidth * _bpp;

				// Create temporary bitmap
				DWORD dwSize = _pitch * m_bih.biHeight;
				LPBYTE lpData = (LPBYTE)malloc(dwSize*sizeof(BYTE));

				// Convert bitmap
				DWORD dwDstHorizontalOffset;
				DWORD dwDstVerticalOffset = 0;
				DWORD dwDstTotalOffset;
				LPDWORD lpDstData = (LPDWORD)lpData;
				DWORD dwSrcHorizontalOffset;
				DWORD dwSrcVerticalOffset = 0;
				DWORD dwSrcTotalOffset;
				for (long i=0; i<m_bih.biHeight; i++)
				{
					dwDstHorizontalOffset = 0;
					dwSrcHorizontalOffset = 0;
					for (long j=0; j<m_bih.biWidth; j++)
					{
						// Update destination total offset
						dwDstTotalOffset = dwDstVerticalOffset + dwDstHorizontalOffset;

						// Update source total offset
						dwSrcTotalOffset = dwSrcVerticalOffset + dwSrcHorizontalOffset;

						// Update bitmap
						switch (m_bih.biBitCount)
						{
						case 8:
							{
								BYTE red = m_lpPalette[m_lpData[dwSrcTotalOffset]].rgbRed;
								BYTE green = m_lpPalette[m_lpData[dwSrcTotalOffset]].rgbGreen;
								BYTE blue = m_lpPalette[m_lpData[dwSrcTotalOffset]].rgbBlue;
								lpDstData[dwDstTotalOffset>>2] = _RGB(red, green, blue);
							}
							break;

						case 16:
							{
								LPWORD lpSrcData = (LPWORD)m_lpData;
								BYTE red = (lpSrcData[dwSrcTotalOffset>>1] & 0x7C00) >> 10;
								BYTE green = (lpSrcData[dwSrcTotalOffset>>1] & 0x03E0) >> 5;
								BYTE blue = lpSrcData[dwSrcTotalOffset>>1] & 0x001F;
								lpDstData[dwDstTotalOffset>>2] = _RGB(red, green, blue);
							}
							break;

						case 24:
							{
								lpDstData[dwDstTotalOffset>>2] = _RGB(m_lpData[dwSrcTotalOffset+2], m_lpData[dwSrcTotalOffset+1], m_lpData[dwSrcTotalOffset]);
							}
							break;

						case 32:
							{
								LPDWORD lpSrcData = (LPDWORD)m_lpData;
								lpDstData[dwDstTotalOffset>>2] = lpSrcData[dwSrcTotalOffset>>2];
							}
							break;
						}

						// Update destination horizontal offset
						dwDstHorizontalOffset += _bpp;

						// Update source horizontal offset
						dwSrcHorizontalOffset += m_iBpp;
					}

					// Update destination vertical offset
					dwDstVerticalOffset += _pitch;

					// Update source vertical offset
					dwSrcVerticalOffset += m_iPitch;
				}

				// Update bitmap info
				m_iPitch = _pitch;
				m_iBpp = _bpp;
				free(m_lpData);
				m_dwSize = dwSize;
				m_lpData = lpData;
				m_bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_dwSize;
				m_bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
				m_bih.biBitCount = _BITS_PER_PIXEL_32;
			}
		}

		void GtPixmap::ConvertTo24Bpp()
		{
			// Check for valid bitmap
			if (IsValid())
			{
				// Calculate new params
				long _bpp = (_BITS_PER_PIXEL_24 >> 3);
				long _pitch = m_bih.biWidth * _bpp;
				while ((_pitch & 3) != 0)
					_pitch++;

				// Create temporary bitmap
				DWORD dwSize = _pitch * m_bih.biHeight;
				LPBYTE lpData = (LPBYTE)malloc(dwSize*sizeof(BYTE));

				// Convert bitmap
				DWORD dwDstHorizontalOffset;
				DWORD dwDstVerticalOffset = 0;
				DWORD dwDstTotalOffset;
				DWORD dwSrcHorizontalOffset;
				DWORD dwSrcVerticalOffset = 0;
				DWORD dwSrcTotalOffset;
				LPDWORD lpSrcData = (LPDWORD)m_lpData;
				for (long i=0; i<m_bih.biHeight; i++)
				{
					dwDstHorizontalOffset = 0;
					dwSrcHorizontalOffset = 0;
					for (long j=0; j<m_bih.biWidth; j++)
					{
						// Update destination total offset
						dwDstTotalOffset = dwDstVerticalOffset + dwDstHorizontalOffset;

						// Update source total offset
						dwSrcTotalOffset = dwSrcVerticalOffset + dwSrcHorizontalOffset;

						// Update bitmap
						lpData[dwDstTotalOffset+2] = _GetRValue(lpSrcData[dwSrcTotalOffset>>2]);
						lpData[dwDstTotalOffset+1] = _GetGValue(lpSrcData[dwSrcTotalOffset>>2]);
						lpData[dwDstTotalOffset] = _GetBValue(lpSrcData[dwSrcTotalOffset>>2]);

						// Update destination horizontal offset
						dwDstHorizontalOffset += _bpp;

						// Update source horizontal offset
						dwSrcHorizontalOffset += m_iBpp;
					}

					// Update destination vertical offset
					dwDstVerticalOffset += _pitch;

					// Update source vertical offset
					dwSrcVerticalOffset += m_iPitch;
				}

				// Update bitmap info
				m_iPitch = _pitch;
				m_iBpp = _bpp;
				free(m_lpData);
				m_dwSize = dwSize;
				m_lpData = lpData;
				m_bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + m_dwSize;
				m_bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
				m_bih.biBitCount = _BITS_PER_PIXEL_24;
			}
		}

		float GtPixmap::_ARGH(float xa, float ya)
		{
			float _ARGH = 0.0f;

			// Calculate ARG
			if ((xa == 0.0f) && (ya == 0.0f))
				_ARGH = 0.0f;
			if ((xa == 0.0f) && (ya >= 0.0f))
				_ARGH = _PI / 2;
			if ((ya == 0.0f) && (xa < 0.0f))
				_ARGH = _PI;
			if ((xa == 0.0f) && (ya < 0.0f))
				_ARGH = -_PI / 2;
			if (xa > 0.0f)
				_ARGH = atan(ya / xa);
			if ((xa < 0.0f) && (ya >= 0.0f))
				_ARGH = _PI - atan(-ya / xa);
			if ((xa < 0.0f) && (ya < 0.0f))
				_ARGH = -_PI + atan(-ya / -xa);

			return _ARGH;
		}

		float GtPixmap::_MODH(float x, float y, float z)
		{
			float _MODH = 0.0f;

			// Calculate MOD
			_MODH = sqrt(x*x + y*y + z*z);

			return _MODH;
		}

	};//end namespace GtCore

};//end namespace GT







