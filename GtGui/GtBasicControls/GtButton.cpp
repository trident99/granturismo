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

#include ".\GtButton.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtButton::GtButton(GtObject* ptrParent)
			:GtFrame(ptrParent)
		{
			m_strType = "GtButton";

			//set the default font
			std::wstring fontfam = L"Arial";
			m_objFont.Set_strFontFamily(fontfam);
			m_objFont.Set_intPoint(20);

			this->ConvGtFontToWinFont();

		};
			//!Virtual destructor
		GtButton::~GtButton(void)
		{
			
		};

		void GtButton::Set_strText(std::string & str)
		{
			m_strText = str;
			this->RepaginateText();
		};

		//!Custom Event Processing
		int GtButton::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};
			GtPoint3DI pos, offset, transPos;
			offset = this->RequestOffset();
			pos.x = gRound(ptrEvent->m_objPos.x);
			pos.y = gRound(ptrEvent->m_objPos.y);
			transPos.x = pos.x - offset.x;
			transPos.y = pos.y - offset.y;

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				m_blnToggle = !m_blnToggle;
				this->Toggled.Emit(m_blnToggle);

				m_blnButtonUp = false;	
				Pressed.Emit();
				this->PostPaint();
				return 1;
			}
			if(ptrEvent->m_objType == MouseLeftRelease)
			{

				if((m_blnButtonUp == false)&&
					(m_objFrame.Contains(transPos)))
				{
					//then releasing a click
					Clicked.Emit();
				}

				m_blnButtonUp = true;	
				Released.Emit();
				this->PostPaint();
				return 1;
			}
			return 0;
		};
		//!Custom Widget Painting
		int GtButton::OnPaint(GtPainter * painter)
		{
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen inPen, outPen, oldPen;
			GtBrush oldBrush;
			GtRectI inRect, outRect;
			
			int delta = 2;
			//INITIALIZE PENS AND BRUSHES

			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			delta = gRound(outPen.Get_sngWidth() / 2.0f);
			if(delta <= 0){delta = 1;};//minimum delta
			//calculate the rectangles, both inner and outer
			outRect =  m_objFrame;
			inRect.xMin = outRect.xMin + delta;
			inRect.xMax = outRect.xMax - delta;
			inRect.yMin = outRect.yMin + delta;
			inRect.yMax = outRect.yMax - delta;
			//set the pens, brush, draw background
			if(!m_blnButtonUp)
			{
				//draw pressed mode
				painter->Set_objPen(GtPen(GtColor(0,0,255),SolidLine,4));
				painter->Set_objBrush(GtBrush(GtColor(250,250,120)));
			}else{
				//draw released mode
				painter->Set_objPen(m_objPen);
				painter->Set_objBrush(m_objBackBrush);
			}
			painter->GtDrawRect(outRect);
			//draw beveling
			if(m_blnButtonUp)
			{
				painter->GtDrawBevelFrameRaised(outRect,4);
			}else{
				painter->GtDrawBevelFrameSunken(outRect,4);
			}

			int i, numLines;
			numLines = m_arrLines.size();
			//draw the highlight rect
			for(i = 0; i < numLines; i++)
			{
				GtTextLine* ptrLine = &m_arrLines.at(i);
				if(ptrLine)
				{
					//draw the string for that line
					int length = ptrLine->m_endPos - ptrLine->m_startPos + 1;
					std::string strTemp = m_strText.substr(ptrLine->m_startPos,length);
					painter->GtDrawText(strTemp,ptrLine->m_objFrame,0);
				}

			}

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);

			return 1;

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 1;
		};	


		void GtButton::RepaginateText(void)
		{
			int i, j, numLines, strWidth;
			int lineStart,lineEnd, lastLine, lastYPos;
			int intCurrLine = 0;
			size_t intScanPos = 0;
			size_t strLen = m_strText.size();

			if(m_strText.size() <= 0)
			{
				m_arrLines.clear();
				//clear the lines down to one
				//has at least one text line
				GtTextLine objLine;
				objLine.m_lngLine = 0;
				m_arrLines.push_back(objLine);
			}

			int   xCpos   = m_objFrame.xMin;
			int   yCpos   = m_objFrame.yMin;
			// make sure we are using the right font
			HDC hdc = GetDC(m_winID);
			SelectObject(hdc, m_winFont.m_hFont);

			m_nLineHeight = CalcStringHeight(hdc);
			strWidth = 0;
			lineStart = 0;
			lastLine = 0;
			// now find the x-coordinate on the specified line
			for(i = 0; i < strLen; i++)
			{
				//scan the string until end of line reached.
				//backoff to previous whitespace to make the line break
				//break the line and go to the next line (create line if necessary)
				//continue to scann until end of string
				strWidth += CalcStringWidth(hdc, &m_strText[i], 1, 0);
				if(strWidth < m_objFrame.Width())
				{
					//continue
					if(i == m_objCursor.m_charPos)
					{
						m_objCursor.m_xPos = strWidth;
						m_objCursor.m_yPos = yCpos;
						m_objCursor.m_lngLine = intCurrLine;
					}
					//check for line break '\n'
					if(m_strText[i] == L'\n')
					{
						//line break
						//end of line, need to handle it
						lineEnd = i;

						//make the line
						if(intCurrLine >= m_arrLines.size())
						{//need to add a line
							GtTextLine objLine;
							objLine.m_lngLine = intCurrLine;
							m_arrLines.push_back(objLine);
						}

						//get the line of interest
						GtTextLine* ptrLine = &m_arrLines.at(intCurrLine);
						if(ptrLine)
						{
							ptrLine->m_objFrame = m_objFrame;
							ptrLine->m_objFrame.xMin += 5;
							ptrLine->m_objFrame.yMin = yCpos;
							ptrLine->m_objFrame.yMax = yCpos + m_nLineHeight;

							ptrLine->m_startPos = lineStart;
							ptrLine->m_endPos = lineEnd;
							//advance to next line
							intCurrLine++;
							m_objCursor.m_lngLine = intCurrLine;
							yCpos += m_nLineHeight;
							lineStart = lineEnd + 1;
							i = lineStart;//rewind i to break
							strWidth = 0;//for new line
						}
					}

				}else{
					//end of line, need to handle it
					lineEnd = FindPrevWSChar(m_strText,i);

					//make the line
					if(intCurrLine >= m_arrLines.size())
					{//need to add a line
						GtTextLine objLine;
						objLine.m_lngLine = intCurrLine;
						m_arrLines.push_back(objLine);
					}

					//get the line of interest
					GtTextLine* ptrLine = &m_arrLines.at(intCurrLine);
					if(ptrLine)
					{
						ptrLine->m_objFrame = m_objFrame;
						ptrLine->m_objFrame.xMin += 5;
						ptrLine->m_objFrame.yMin = yCpos;
						ptrLine->m_objFrame.yMax = yCpos + m_nLineHeight;

						ptrLine->m_startPos = lineStart;
						ptrLine->m_endPos = lineEnd;
						//advance to next line
						intCurrLine++;
						m_objCursor.m_lngLine = intCurrLine;
						yCpos += m_nLineHeight;
						lineStart = lineEnd + 1;
						i = lineStart;//rewind i to break
						strWidth = 0;//for new line
					}
				}
			}//end loop i through characters
			//handling for last line, ran out of characters for this line
			//partial line
			lineEnd = m_strText.size() - 1;
			//make the line
			if(intCurrLine >= m_arrLines.size())
			{//need to add a line
				GtTextLine objLine;
				objLine.m_lngLine = intCurrLine;
				m_arrLines.push_back(objLine);
			}

			//get the line of interest
			GtTextLine* ptrLine = &m_arrLines.at(intCurrLine);
			if(ptrLine)
			{
				ptrLine->m_objFrame = m_objFrame;
				ptrLine->m_objFrame.xMin += 5;
				ptrLine->m_objFrame.yMin = yCpos;
				ptrLine->m_objFrame.yMax = yCpos + m_nLineHeight;

				ptrLine->m_startPos = lineStart;
				ptrLine->m_endPos = lineEnd;
				//advance to next line
				intCurrLine++;
				yCpos += m_nLineHeight;

				//set the line counters
				lineStart = lineEnd + 1;
				i = lineStart;//rewind i to break
				strWidth = 0;//for new line
			}

			//delete the unused lines
			for(j = intCurrLine; j < m_arrLines.size();j++)
			{
				m_arrLines.pop_back();
			}

			//clean up the HDC
			ReleaseDC(m_winID, hdc);

			//SetCaretPos(xpos, ypos);
		}


		//!Find Next White Space Character
		long GtButton::FindNextWSChar(const std::string & strInput,size_t intStartPos)
		{
			long intCursor,lngStringSize;
			//cycle until white space found
			lngStringSize = strInput.size();
			intCursor = intStartPos;

			while(intCursor < lngStringSize)
			{
				if( (int)(strInput[intCursor]) <= 32)
				{
					//32 or less is the white space characters of ASCII
					//then whitespace found
					return intCursor;
				}else{
					//not whitespace increment counter
					intCursor++;
				};
			};
			//no white space found return illegal index
			return -1;
		};

		//!Find Next White Space Character
		long GtButton::FindPrevWSChar(const std::string & strInput,size_t intStartPos)
		{
			long intCursor,lngStringSize;
			//cycle until white space found
			lngStringSize = strInput.size();
			intCursor = intStartPos;

			while(intCursor > 0)
			{
				if( (int)(strInput[intCursor]) <= 32)
				{
					//32 or less is the white space characters of ASCII
					//then whitespace found
					return intCursor;
				}else{
					//not whitespace increment counter
					intCursor--;
				};
			};
			//no white space found return illegal index
			return -1;
		};

				//
		//	
		//
		int GtButton::CalcTabWidth(void)
		{
			return m_nTabWidthChars * m_nFontWidth;
		}
		//
		//	Wrapper for GetTextExtentPoint32. Takes into account
		//	control-characters, tabs etc.
		//
		int GtButton::CalcStringWidth(HDC hdc, const char *buf, int len, int nTabOrigin)
		{
			SIZE	sz;
			int		width = 0;

			const int TABWIDTHPIXELS = CalcTabWidth();

			for(int i = 0; i < len; i++)
			{
				if(buf[i] == '\t')
				{
					width += TABWIDTHPIXELS;
				}
				else if(buf[i] < 32)
				{
					//do nothing, control character
					width += m_nFontWidth;
				}else{
					//normal character
					GetTextExtentPoint32(hdc, (LPCSTR)&buf[i], 1, &sz);
					width += sz.cx;
				}
			}

			return width;
		}

		int GtButton::CalcStringHeight(HDC hdc)
		{
			SIZE	sz;
			int		height = 0;
			wchar_t * buf = L"ABCXYZ";
				//GetTextExtentPoint32W(
				//    __in HDC hdc,
			//    __in_ecount(c) LPCWSTR lpString,
			//    __in int c,
			//    __out LPSIZE psizl
			//    );
			GetTextExtentPoint32(hdc, (LPCSTR)buf, sizeof(buf), &sz);
			height = sz.cy;
			return height;
		}


		void GtButton::ConvGtFontToWinFont(void)
		{
			std::wstring strFont = m_objFont.Get_strFontFamily();
			int intPoint = m_objFont.Get_intPoint();

			if(m_winFont.m_hFont)
			{
				DeleteObject(m_winFont.m_hFont);
				m_winFont.m_hFont = NULL;
			}

			m_winFont.m_hFont = CreateFont(intPoint, 0, 0, 0,FW_NORMAL,
				FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_ROMAN,
				(LPCSTR)strFont.c_str());

			// need a DC to query font data
			HDC    hdc  = GetDC(0);
			HANDLE hold = SelectObject(hdc, m_winFont.m_hFont);

			// get font settings
			GetTextMetrics(hdc, &(m_winFont.m_textMetrics)) ;
			//set line height
			m_nLineHeight = m_objFrame.yMax - m_objFrame.yMin - 5;
			if(m_nLineHeight < 20){m_nLineHeight = 20;};//min practical line height
			// cleanup
			SelectObject(hdc, hold);
			ReleaseDC(0, hdc);

			m_nFontWidth = m_winFont.m_textMetrics.tmAveCharWidth;

			return;
		};


	};//end namespace GtCore

};//end namespace GT