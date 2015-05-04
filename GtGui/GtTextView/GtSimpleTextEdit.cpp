/*
**	This file is part of the GT Core Library.
**  It is based on a merger of QT along with development of new classes.
**  License information is in the License.h file
**	This software was merged and developed by:
**	
**  Anthony Daniels
**
**  It is strongly based on 
**	NeatPad by www.catch22.net
**  Thank you for the contributions and tutorials
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

#include ".\GtSimpleTextEdit.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//enforced upper limit on string size
#define MAX_BUFFER_SIZE 256


		//default constructor
		GtSimpleTextEdit::GtSimpleTextEdit(GtObject* ptrParent)
			: GtWidget(ptrParent)
		{
			m_strType = "GtSimpleTextEdit";
			m_lngSelStart = 0;
			m_lngSelEnd = 0;
			m_lngCursor = 0;
			m_nHScrollPos = 0;

			// Font-related data	
			m_nFontWidth = 0;
			m_nLineHeight = 0;
			// Scrollbar-related data
			m_nHScrollPos = 0;
			m_nHScrollMax = 256;

			// Display-related data
			m_nTabWidthChars = 3;

			// Runtime data
			m_blnMouseDown = false;
			m_nScrollTimer = 0;
			m_nScrollCounter = 0;

			m_objHighColor = GtColor(255,255,0);

			//set the default font
			std::wstring fontfam = L"Arial";
			m_objFont.Set_strFontFamily(fontfam);
			m_objFont.Set_intPoint(20);

			this->ConvGtFontToWinFont();
		};
		//virtual destructor
		GtSimpleTextEdit::~GtSimpleTextEdit(void)
		{
			m_strText.clear();
		};

		void GtSimpleTextEdit::Set_objFont(GtFont varVal)
		{
			GtWidget::Set_objFont(varVal);	
			this->ConvGtFontToWinFont();
		};

		//!Clear the focus
		void GtSimpleTextEdit::ClearFocus(GtWidget* ptrNewFocus)
		{
			m_blnFocus = false;
			HideCaret(m_winID);
			DestroyCaret();
		};
		//!Gets the selected sub string
		std::string GtSimpleTextEdit::GetSelSubString(void)
		{
			std::string strNull;
			if(m_lngSelStart < 0){return strNull;};//safety check
			if(m_lngSelEnd < 0){return strNull;};//safety check
			long length = m_lngSelEnd - m_lngSelStart;
			if(length < 0){length = 0;};
			return	m_strText.substr(m_lngSelStart, length);
		};



		int GtSimpleTextEdit::HandleEvent(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return 0;};//safety check

			switch(ptrEvent->m_objType)
			{
			case MouseLeftPress:
				{
					this->OnLeftButtonPress(ptrEvent);
					return 1;
					break;
				}
			case MouseLeftRelease:
				{
					this->OnLeftButtonRelease(ptrEvent);
					return 1;
					break;
				}
			case MouseMove:
				{
					this->OnMouseMove(ptrEvent);
					return 1;
					break;
				}
			case KeyPress:
				{
					this->OnKeyPress(ptrEvent);
					return 1;
					break;
				}
			case KeyRelease:
				{
					this->OnKeyRelease(ptrEvent);
					return 1;
					break;
				}
			}
			return 0;
		};


		//!Custom Widget Painting
		int GtSimpleTextEdit::OnPaint(GtPainter * ptrPainter)
		{
			//safety check
			if(!m_blnVisible){return 0;};
			if(!ptrPainter){return 0;};
			GtPen oldPen;
			GtBrush oldBrush;
			//draw the background
			ptrPainter->Set_objPen(m_objPen);
			ptrPainter->Set_objBrush(m_objBackBrush);
			ptrPainter->Set_objFont(m_objFont);
			ptrPainter->GtFillRect(m_objFrame);
			ptrPainter->GtDrawBevelFrameSunken(m_objFrame,2);

			//draw the highlight rect
			
			if((m_lngSelEnd - m_lngSelStart) > 0)
			{
				ptrPainter->Set_objPen(GtPen(GtColor(255,255,0)));
				ptrPainter->Set_objBrush(GtBrush(m_objHighColor));
				ptrPainter->GtFillRect(m_objHighRect);	
			}
			//draw the text

			if(m_strText.size() > 0)
			{
				std::string strTemp;
				size_t len = m_strText.size() - m_nHScrollPos;
				strTemp = m_strText.substr(m_nHScrollPos,len);
				GtPoint3DI pos;
				pos.x = m_objFrame.xMin;
				pos.y = m_objFrame.yMin;
				//ptrPainter->GtDrawText(pos,strTemp);
				ptrPainter->GtDrawText(strTemp,m_objFrame,0);
			}

			//finished, reset old brushes and pens
			ptrPainter->Set_objPen(oldPen);
			ptrPainter->Set_objBrush(oldBrush);

			return 1;
		};		


		//!Event handler for character entered
		void GtSimpleTextEdit::OnKeyPress(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			// map the mouse-coordinates to a real file-offset-coordinate
			if(ptrEvent->m_objKey == Key_Shift){return;};
			if(ptrEvent->m_objKey == Key_Control){return;};
			if(ptrEvent->m_objKey == Key_Alt){return;};
			if(ptrEvent->m_objKey == Key_Up){return;};
			if(ptrEvent->m_objKey == Key_Down){return;};

			if(ptrEvent->m_objKey == Key_Return)
			{
				this->ClearFocus(NULL);
				this->EndEdit.Emit();
				return;
			};

			if(ptrEvent->m_objKey == Key_Left)
			{
				m_lngCursor--;
				if(m_lngCursor < 0){m_lngCursor = 0;};
				RepositionCaret();
				this->PostPaint();
				return;
			};

			if(ptrEvent->m_objKey == Key_Right)
			{
				m_lngCursor++;
				if(m_lngCursor > m_strText.size()){m_lngCursor = m_strText.size();};//safey check cursor location
				RepositionCaret();
				this->PostPaint();
				return;
			};
			if(ptrEvent->m_objKey == Key_Right){m_lngCursor++;return;};
			//check for backspace and delete first
			if(ptrEvent->m_objKey == Key_Backspace)
			{
				if(m_strText.size() > 0)
				{
					int len = abs(m_lngSelEnd - m_lngSelStart);
					if(len > 0)
					{
						m_strText.erase(m_lngSelStart,len);
						m_lngCursor = m_lngSelStart;
					}else{
						m_lngCursor--;
						if (m_lngCursor < 0){ m_lngCursor = 0; };
						m_strText.erase(m_lngCursor,1);
						
					}
					if(m_lngCursor < 0){m_lngCursor = 0;};
					RepositionCaret();
					this->PostPaint();
				}
				return;
			}
			if(ptrEvent->m_objKey == Key_Delete)
			{
				if(m_strText.size() > 0)
				{
					m_strText.erase(m_lngCursor,1);
					this->PostPaint();
				}
				return;
			}
			//CHECK FOR COPY AND PASTE
			if ((ptrEvent->m_objKey == Key_C) && 
				(ptrEvent->m_objModifiers & ControlModifier) )
			{
				if (m_strText.size() > 0)
				{
					this->OnCopy(ptrEvent);
				}
				return;
			}
			if ((ptrEvent->m_objKey == Key_X) &&
				(ptrEvent->m_objModifiers & ControlModifier))
			{
				if (m_strText.size() > 0)
				{
					this->OnCut(ptrEvent);
				}
				return;
			}

			if ((ptrEvent->m_objKey == Key_V) &&
				(ptrEvent->m_objModifiers & ControlModifier))
			{
				this->OnPaste(ptrEvent);
				return;
			}
			//otherwise type the character
			wchar_t chNew = GtKeyToWChar(ptrEvent->m_objKey,ptrEvent->m_objModifiers);
			if(m_lngCursor > m_strText.size()){return;};//safey check cursor location
			if(chNew != NULL)
			{
				m_strText.insert(m_lngCursor,1,chNew);
				m_lngCursor += 1;
				m_lngSelStart = m_lngCursor;
				m_lngSelEnd = m_lngCursor;
				RepositionCaret();
			}
			//get the offset to the insert character
			this->PostPaint();


		};

		//!Event handler for key release
		void GtSimpleTextEdit::OnKeyRelease(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			m_lngSelStart = m_lngCursor;
			m_lngSelEnd = m_lngCursor;
			this->PostPaint();
		};

		//!Event handler for horizontal scroll
		void GtSimpleTextEdit::OnHorizScroll(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			//get the offset f
			this->PostPaint();
		};

		//!Event handler for Left Mouse Click Press
		void GtSimpleTextEdit::OnLeftButtonPress(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check

			if(m_winID == NULL)
			{//get the winID from the root
				GtWidget* root = this->GetRootWidget();
				if(root)
				{
					m_winID = root->Get_winID();
				}
			}

			CreateCaret(m_winID, (HBITMAP)NULL, 2, m_nLineHeight);
			RepositionCaret();

			ShowCaret(m_winID);

			ULONG nLineNo;
			ULONG nCharOff;
			ULONG nFileOff;
			int   px, mx, my;
			mx = gRound(ptrEvent->m_objPos.x);
			my = gRound(ptrEvent->m_objPos.y);

			// map the mouse-coordinates to a real file-offset-coordinate
			MouseCoordToStringPos(mx, my, nCharOff, px);

			SetCaretPos(px, m_objFrame.yMin);

			// reset cursor and selection offsets to the same location
			m_lngSelStart	= nCharOff;
			m_lngSelEnd		= nCharOff;
			m_lngCursor		= nCharOff;
			m_objHighRect = m_objFrame;
			m_objHighRect.xMin = px;
			m_objHighRect.xMax = px;
			// set capture for mouse-move selections
			m_blnMouseDown = true;
			SetCapture(m_winID);
			this->PostPaint();
			return;
		};

		//!Event handler for Left Mouse Click Press
		void GtSimpleTextEdit::OnLeftButtonRelease(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check

			if(m_blnMouseDown)
			{
				// cancel the scroll-timer if it is still running
				if(m_nScrollTimer != 0)
				{
					KillTimer(m_winID, m_nScrollTimer);
					m_nScrollTimer = 0;
				}

				m_blnMouseDown = false;
				ReleaseCapture();
			}
			this->PostPaint();
			return;
		};

		//!Event handler for Left Mouse Click Press
		void GtSimpleTextEdit::OnMouseMove(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check

			if(m_blnMouseDown)
			{
				ULONG	nLineNo, nCharOff, nFileOff;
				int cx,mx, my;

				mx = gRound(ptrEvent->m_objPos.x);
				my = gRound(ptrEvent->m_objPos.y);
				POINT	pt = { mx, my };

				// get new cursor offset+coordinates
				MouseCoordToStringPos(mx, my, nCharOff, cx);

				// update the region of text that has changed selection state

				// adjust the cursor + selection to the new offset
				m_lngSelEnd = nCharOff;
				m_lngCursor	= nCharOff;
				m_objHighRect.xMax = cx;
				// always set the caret position because we might be scrolling
				SetCaretPos(cx, m_objFrame.yMin);
				this->PostPaint();
				return;
			}else{
				return;//nothing to do
			}

			return;
		};
		//!Event handler for CTRL + C keystroke event
		void GtSimpleTextEdit::OnCopy(GtEvent* ptrEvent)
		{
			//safety check
			if (!ptrEvent){ return;}
			HGLOBAL hglbCopy;
			LPTSTR lpstrCopy;

			GtWidget* ptrRoot = this->GetRootWidget();
			if (!ptrRoot){ return; }
			m_winID = ptrRoot->Get_winID();
			if (!OpenClipboard(m_winID))
			{//couldn't open clipboard
				return;
			}

			EmptyClipboard();

			//get the substring to copy
			int intLen = m_lngSelEnd - m_lngSelStart;
			if (intLen <= 0)
			{ //copy the whole edit

				hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (m_strText.size() + 1) * sizeof(TCHAR));
				if (!hglbCopy){ CloseClipboard(); return; }
				lpstrCopy = (LPTSTR) GlobalLock(hglbCopy);
				memcpy(lpstrCopy, m_strText.c_str(), m_strText.size());
				lpstrCopy[m_strText.size()] = 0;
				GlobalUnlock(hglbCopy);
				SetClipboardData(CF_TEXT, (LPTSTR)lpstrCopy);
				CloseClipboard();
				return;
			};//nothing to copy

			//otherwise get substring
			std::string strCopy = m_strText.substr(m_lngSelStart, m_lngSelEnd);
			hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (strCopy.size() + 1) * sizeof(TCHAR));
			if (!hglbCopy){ CloseClipboard(); return; }
			lpstrCopy = (LPTSTR)GlobalLock(hglbCopy);
			memcpy(lpstrCopy, strCopy.c_str(), strCopy.size());
			lpstrCopy[strCopy.size()] = 0;
			GlobalUnlock(hglbCopy);
			SetClipboardData(CF_TEXT, (LPTSTR)lpstrCopy);
			CloseClipboard();
			return;
		};
		//!Event handler for CTRL + X keystroke event
		void GtSimpleTextEdit::OnCut(GtEvent* ptrEvent)
		{
			//safety check
			if (!ptrEvent){ return; }
			std::string strCopy;
			if (m_strText.size() > 0)
			{
				int len = abs(m_lngSelEnd - m_lngSelStart);
				if (len > 0)
				{
					strCopy = m_strText.substr(m_lngSelStart, len);
					m_strText.erase(m_lngSelStart, len);
					m_lngCursor = m_lngSelStart;
				}
				else{
					return;
				}
				if (m_lngCursor < 0){ m_lngCursor = 0; };
				RepositionCaret();
			}

			HGLOBAL hglbCopy;
			LPTSTR lpstrCopy;

			GtWidget* ptrRoot = this->GetRootWidget();
			if (!ptrRoot){ return; }
			m_winID = ptrRoot->Get_winID();
			if (!OpenClipboard(m_winID))
			{//couldn't open clipboard
				return;
			}

			EmptyClipboard();

			//otherwise get substring
			
			hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (strCopy.size() + 1) * sizeof(TCHAR));
			if (!hglbCopy){ CloseClipboard(); return; }
			lpstrCopy = (LPTSTR)GlobalLock(hglbCopy);
			memcpy(lpstrCopy, strCopy.c_str(), strCopy.size());
			lpstrCopy[strCopy.size()] = 0;
			GlobalUnlock(hglbCopy);
			SetClipboardData(CF_TEXT, (LPTSTR)lpstrCopy);
			CloseClipboard();
			return;


		};
		//!Event handler for CTRL + V keystroke event
		void GtSimpleTextEdit::OnPaste(GtEvent* ptrEvent)
		{
			//safety check
			if (!ptrEvent){ return; }

			HGLOBAL hglbPaste;
			LPTSTR lpstrPaste;

			GtWidget* ptrRoot = this->GetRootWidget();
			if (!ptrRoot){ return; }
			m_winID = ptrRoot->Get_winID();
			if (!OpenClipboard(m_winID))
			{//couldn't open clipboard
				return;
			}
			if (!IsClipboardFormatAvailable(CF_TEXT)){ return; }
			hglbPaste = GetClipboardData(CF_TEXT);
			if (hglbPaste != NULL)
			{
				lpstrPaste = (LPTSTR)GlobalLock(hglbPaste);
				if (lpstrPaste != NULL)
				{
					//replace text
					int intLen = m_strText.size();
					std::string strBegin, strEnd;
					
					std::string strNew(lpstrPaste);
					//paste beginning
					if (m_strText.size() > 0)
					{
						if (m_lngCursor <= 0){ m_lngCursor = 0; }
						strBegin = m_strText.substr(0, m_lngCursor);
						if (m_lngCursor >= intLen){ m_lngCursor = intLen - 1; }
						int intLenEnd = (intLen - m_lngCursor);
						strEnd = m_strText.substr(m_lngCursor, intLenEnd);

						if (strBegin.size() > 0)
						{
							m_strText = strBegin;
						}
						else{
							m_strText.clear();
						}
						//insert text
						m_strText += strNew;
						if (strEnd.size() > 0)
						{
							m_strText += strEnd;
						}
					}else{
						m_strText = strNew;
					}
				}
				GlobalUnlock(hglbPaste);
			}
			CloseClipboard();
			//render the updated
			this->PostPaint();
		};
		//
		//	Convert mouse(client) coordinates to a file-relative offset
		//
		//	Currently only uses the main font so will not support other
		//	fonts introduced by syntax highlighting
		//
		BOOL GtSimpleTextEdit::MouseCoordToStringPos(	int		 mx,			// [in]  mouse x-coord
			int		 my,			// [in]  mouse y-coord
			ULONG	&pnCharOffset,	// [out] char-offset from start of line
			int		&px				// [out] adjusted x coord of caret
			)
		{
			if(!m_winID)
			{
				GtWidget* ptrRoot = this->GetRootWidget();
				if(!ptrRoot){return false;};//safety check
				m_winID = ptrRoot->Get_winID();
			}

			HDC    hdc      = GetDC(m_winID);
			HANDLE hOldFont = SelectObject(hdc, m_winFont.m_hFont);	

			wchar_t buf[MAX_BUFFER_SIZE];
			int   strLen;
			int	  curx = 0;
			int  halfwidth = gRound(double(m_nFontWidth) / 2.0f);
			// get scrollable area
			// clip mouse to edge of window
			pnCharOffset = 0;
			px = m_objFrame.xMin;
			if(mx < m_objFrame.xMin){mx = m_objFrame.xMin;}
			if(my < m_objFrame.yMin){my = m_objFrame.yMin;}
			if(my >= m_objFrame.yMax){my = m_objFrame.yMax - 1;}
			if(mx >= m_objFrame.xMax){mx = m_objFrame.xMax  - 1;}

			mx += m_nHScrollPos * m_nFontWidth;

			// character offset within the line is more complicated. We have to 
			// grab some text
			strLen = m_strText.size();

			// find it's width
			if(strLen <= 0)
			{
				pnCharOffset = 0;
				px = m_objFrame.xMin;
				return true;
			}
			int width = CalcStringWidth(hdc, m_strText.c_str(), strLen, 0);
			size_t i, charW, sumW;
			sumW = m_objFrame.xMin;
			//check if first char
			if(mx < (sumW + halfwidth) )
			{
				pnCharOffset = 0;
				px = m_objFrame.xMin;
				SelectObject(hdc, hOldFont);
				ReleaseDC(m_winID, hdc);
				return true;
			}
			//otherwise cycle through chars
			bool blnPosFound = false;
			i = 0;
			do{	
				
				charW = CalcStringWidth(hdc, &m_strText[i], 1, 0);
				sumW += charW;
				if( (mx + halfwidth)  < sumW)
				{
					pnCharOffset = i;
					blnPosFound = true;
					px = sumW - charW;
				}
				i++;
			}while(( i < strLen)&&(!blnPosFound));

			if(i >= strLen)
			{
				//set to last character
				pnCharOffset = strLen;
				px = sumW;
			}

			SelectObject(hdc, hOldFont);
			ReleaseDC(m_winID, hdc);

			return 1;
		}

		static const wchar_t *CtrlStr(DWORD ch)
		{
			static const wchar_t *reps[] = 
			{
				L"NUL", L"SOH", L"STX", L"ETX", L"EOT", L"ENQ", L"ACK", L"BEL",
				L"BS",  L"HT",  L"LF",  L"VT",  L"FF",  L"CR",  L"SO",  L"SI",
				L"DLE", L"DC1", L"DC2", L"DC3", L"DC4", L"NAK", L"SYN", L"ETB",
				L"CAN", L"EM",  L"SUB", L"ESC", L"FS",  L"GS",  L"RS",  L"US"
			};

			return ch < ' ' ? reps[ch] : L"???";
		}

		//
		//	Return width of specified control-character
		//
		int GtSimpleTextEdit::CalcCtrlCharWidth(HDC hdc, ULONG chValue, GtWinFont *font)
		{
			SIZE sz;
			const wchar_t *str = CtrlStr(chValue % 32);
			GetTextExtentPoint32(hdc, (LPCSTR)str, wcslen(str), &sz);
			return sz.cx + 4;
		}


		//
		//	
		//
		int GtSimpleTextEdit::CalcTabWidth(void)
		{
			return m_nTabWidthChars * m_nFontWidth;
		}

		//
		//	Wrapper for GetTextExtentPoint32. Takes into account
		//	control-characters, tabs etc.
		//
		int GtSimpleTextEdit::CalcStringWidth(HDC hdc, const char *buf, int len, int nTabOrigin)
		{
			SIZE	sz;
			int		width = 0;

			const int TABWIDTHPIXELS = CalcTabWidth();

			for(int i = 0, lasti = 0; i <= len; i++)
			{
				if(i == len || buf[i] == '\t' || buf[i] < 32)
				{
					GetTextExtentPoint32(hdc, (LPCSTR)(buf + lasti), i - lasti, &sz);
					width += sz.cx;

					if(i < len && buf[i] == '\t')
					{
						width += TABWIDTHPIXELS - ((width - nTabOrigin) % TABWIDTHPIXELS);
						lasti  = i + 1;
					}
					else if(i < len && buf[i] < 32)
					{
						width += CalcCtrlCharWidth(hdc, buf[i], &m_winFont);
						lasti  = i + 1;
					}
				}
			}

			return width;
		}

		void GtSimpleTextEdit::ConvGtFontToWinFont(void)
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

		//
		//	Set the caret position based on m_nCursorOffset,
		//	typically used whilst scrolling 
		//	(i.e. not due to mouse clicks/keyboard input)
		//
		ULONG GtSimpleTextEdit::RepositionCaret()
		{
			
			int   xpos   = m_objFrame.xMin;
			int   ypos   = m_objFrame.yMin;

			// make sure we are using the right font
			HDC hdc = GetDC(m_winID);
			SelectObject(hdc, m_winFont.m_hFont);

			// now find the x-coordinate on the specified line
			size_t i = 0;
			if(m_lngCursor < 0){m_lngCursor = 0;};//illegal index check
			if(m_strText.size() > 0)
			{
				while(i < m_lngCursor)
				{
					xpos   += CalcStringWidth(hdc, &m_strText[i], 1, 0);
					i++;
				}
			}

			ReleaseDC(m_winID, hdc);

			SetCaretPos(xpos, ypos);
			return 0;
		}

		//
		//	return direction to scroll (+1,-1 or 0) based on 
		//  distance of mouse from window edge
		//
		//	"counter" is used to achieve variable-speed scrolling
		//
		int GtSimpleTextEdit::ScrollDir(int counter, int distance)
		{
			int amt;

			// amount to scroll based on distance of mouse from window
			if(abs(distance) < 16)			amt = 8;
			else if(abs(distance) < 48)		amt = 3;
			else							amt = 1;

			if(counter % amt == 0)
				return distance < 0 ? -1 : 1;
			else
				return 0;
		}


	};//end namespace GtCore

};//end namespace GT