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

#include ".\GtMultiTextEdit.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{


		//default constructor
		GtMultiTextEdit::GtMultiTextEdit(GtObject* ptrParent)
			: GtWidget(ptrParent)
		{
			m_strType = "GtMultiTextEdit";
			m_lngSelStart = 0;
			m_lngSelEnd = 0;

			// Font-related data	
			m_nFontWidth = 0;
			m_nLineHeight = 25;
			// Display-related data
			m_nTabWidthChars = 3;

			// Runtime data
			m_blnMouseDown = false;

			m_objHighColor = GtColor(255,255,0);

			//set the default font
			std::wstring fontfam = L"Arial";
			m_objFont.Set_strFontFamily(fontfam);
			m_objFont.Set_intPoint(20);

			this->ConvGtFontToWinFont();

			//has at least one text line
			GtTextLine objLine;
			objLine.m_lngLine = 0;
			m_arrLines.push_back(objLine);

		};
		//virtual destructor
		GtMultiTextEdit::~GtMultiTextEdit(void)
		{
			m_strText.clear();
		};

		void GtMultiTextEdit::Set_objFont(GtFont varVal)
		{
			GtWidget::Set_objFont(varVal);	
			this->ConvGtFontToWinFont();
		};

		//!Clear the focus
		void GtMultiTextEdit::ClearFocus(GtWidget* ptrNewFocus)
		{
			m_blnFocus = false;
			HideCaret(m_winID);
			DestroyCaret();
		};
		//!Gets the selected sub string
		std::string GtMultiTextEdit::GetSelSubString(void)
		{
			std::string strNull;
			if(m_lngSelStart < 0){return strNull;};//safety check
			if(m_lngSelEnd < 0){return strNull;};//safety check
			long length = m_lngSelEnd - m_lngSelStart;
			if(length < 0){length = 0;};
			return	m_strText.substr(m_lngSelStart, length);
		};



		int GtMultiTextEdit::HandleEvent(GtEvent * ptrEvent)
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
		int GtMultiTextEdit::OnPaint(GtPainter * painter)
		{
			int i, numLines;
			//safety check
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			GtPen oldPen;
			GtBrush oldBrush;
			//draw the background
			painter->Set_objPen(m_objPen);
			painter->Set_objBrush(m_objBackBrush);
			painter->Set_objFont(m_objFont);
			painter->GtFillRect(m_objFrame);
			painter->GtDrawBevelFrameSunken(m_objFrame,2);

			numLines = m_arrLines.size();
			//draw the highlight rect
			for(i = 0; i < numLines; i++)
			{
				GtTextLine* ptrLine = &m_arrLines.at(i);
				if(ptrLine)
				{
					//see if there is any highlighting
					if((ptrLine->m_endHighlight - ptrLine->m_startHighlight) > 0)
					{
						//then draw the highlight
						painter->Set_objBrush(GtBrush(m_objHighColor));
						painter->GtFillRect(ptrLine->m_objHighFrame);
					}

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
		};		


		//!Event handler for character entered
		void GtMultiTextEdit::OnKeyPress(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			// map the mouse-coordinates to a real file-offset-coordinate
			if(ptrEvent->m_objKey == Key_Shift){return;};
			if(ptrEvent->m_objKey == Key_Control){return;};
			if(ptrEvent->m_objKey == Key_Alt){return;};
			if(ptrEvent->m_objKey == Key_Up){return;};
			if(ptrEvent->m_objKey == Key_Down){return;};

			if(ptrEvent->m_objKey == Key_Escape)
			{
				this->ClearSelection();
				this->ClearFocus(NULL);
				this->EndEdit.Emit();
				this->PostPaint();
				return;
			};

			if(ptrEvent->m_objKey == Key_Left)
			{
				m_objCursor.m_charPos--;
				if(m_objCursor.m_charPos < 0){m_objCursor.m_charPos = 0;};
				RepositionCaret();
				this->PostPaint();
				return;
			};

			if(ptrEvent->m_objKey == Key_Right)
			{
				m_objCursor.m_charPos++;
				if(m_objCursor.m_charPos > m_strText.size()){m_objCursor.m_charPos = m_strText.size();};//safey check cursor location
				RepositionCaret();
				this->PostPaint();
				return;
			};
			if(ptrEvent->m_objKey == Key_Right){m_objCursor.m_charPos++;return;};
			//check for backspace and delete first
			if(ptrEvent->m_objKey == Key_Backspace)
			{
				size_t strLen = m_strText.size();
				if(m_objCursor.m_charPos < 0){m_objCursor.m_charPos = 0;};
				if(strLen > 0)
				{
					int len = abs(m_lngSelEnd - m_lngSelStart);
					if(len > 0)
					{
						m_strText.erase(m_lngSelStart,len);
						m_objCursor.m_charPos = m_lngSelStart;
					}else{
						if (m_objCursor.m_charPos > 0)
						{
							m_objCursor.m_charPos--;
						}
						if (m_objCursor.m_charPos < 0){ m_objCursor.m_charPos = 0; }
						m_strText.erase(m_objCursor.m_charPos,1);
					}
					//bound checks
					if(m_objCursor.m_charPos < 0){m_objCursor.m_charPos = 0;};
					if(m_objCursor.m_charPos > m_strText.size()){m_objCursor.m_charPos = strLen - 1;};
					this->RepaginateText();
					this->RepositionCaret();
					this->PostPaint();
				}
				return;
			}
			if(ptrEvent->m_objKey == Key_Delete)
			{
				if(m_strText.size() > 0)
				{
					m_strText.erase(m_objCursor.m_charPos,1);
					this->RepaginateText();
					this->RepositionCaret();
					this->PostPaint();
				}
				return;
			}

			//CHECK FOR COPY CUT AND PASTE
			if ((ptrEvent->m_objKey == Key_C) &&
				(ptrEvent->m_objModifiers & ControlModifier))
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

			if(ptrEvent->m_objKey == Key_Return)
			{
				wchar_t chNew = L'\n';
				m_strText.insert(m_objCursor.m_charPos,1,chNew);
				m_objCursor.m_charPos += 1;
				m_lngSelStart = m_objCursor.m_charPos;
				m_lngSelEnd = m_objCursor.m_charPos;
				this->RepaginateText();
				this->RepositionCaret();
				//get the offset to the insert character
				this->PostPaint();
				return;
			};
			//otherwise type the character
			wchar_t chNew = GtKeyToWChar(ptrEvent->m_objKey,ptrEvent->m_objModifiers);
			if(m_objCursor.m_charPos > m_strText.size()){return;};//safey check cursor location
			if(chNew != NULL)
			{
				m_strText.insert(m_objCursor.m_charPos,1,chNew);
				m_objCursor.m_charPos += 1;
				m_lngSelStart = m_objCursor.m_charPos;
				m_lngSelEnd = m_objCursor.m_charPos;
				this->RepaginateText();
				this->RepositionCaret();
			}
			//get the offset to the insert character
			this->PostPaint();


		};

		//!Event handler for key release
		void GtMultiTextEdit::OnKeyRelease(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			m_lngSelStart = m_objCursor.m_charPos;
			m_lngSelEnd = m_objCursor.m_charPos;
			this->ClearSelection();
			this->PostPaint();
		};

		//!Event handler for horizontal scroll
		void GtMultiTextEdit::OnHorizScroll(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check
			//get the offset f
			this->PostPaint();
		};

		//!Event handler for Left Mouse Click Press
		void GtMultiTextEdit::OnLeftButtonPress(GtEvent * ptrEvent)
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
			m_objCursor = MouseCoordToStringPos(mx, my);

			SetCaretPos(m_objCursor.m_xPos,m_objCursor.m_yPos);

			// reset cursor and selection offsets to the same location
			m_lngSelStart	= m_objCursor.m_charPos;
			m_lngSelEnd		= m_objCursor.m_charPos;
			this->ClearSelection();
			// set capture for mouse-move selections
			m_blnMouseDown = true;
			SetCapture(m_winID);
			this->PostPaint();
			return;
		};

		//!Event handler for Left Mouse Click Press
		void GtMultiTextEdit::OnLeftButtonRelease(GtEvent * ptrEvent)
		{
			if(!ptrEvent){return;};//safety check

			if(m_blnMouseDown)
			{
				m_blnMouseDown = false;
				ReleaseCapture();
			}
			this->PostPaint();
			return;
		};

		//!Event handler for Left Mouse Click Press
		void GtMultiTextEdit::OnMouseMove(GtEvent * ptrEvent)
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
				m_objCursor = this->MouseCoordToStringPos(mx, my);
				// adjust the cursor + selection to the new offset
				m_lngSelEnd = m_objCursor.m_charPos;
				if(m_lngSelEnd != m_lngSelStart)
				{
				//update highlight rectangles
				this->UpdateHighlightRects();
				}
				// always set the caret position because we might be scrolling
				SetCaretPos(m_objCursor.m_xPos, m_objCursor.m_yPos);
				this->PostPaint();
				return;
			}else{
				return;//nothing to do
			}

			return;
		};

		//!Event handler for CTRL + C keystroke event
		void GtMultiTextEdit::OnCopy(GtEvent* ptrEvent)
		{
			//safety check
			if (!ptrEvent){ return; }
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
				lpstrCopy = (LPTSTR)GlobalLock(hglbCopy);
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
		void GtMultiTextEdit::OnCut(GtEvent* ptrEvent)
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
					m_objCursor.m_charPos = m_lngSelStart;
				}
				else{
					return;
				}
				if (m_objCursor.m_charPos < 0){ m_objCursor.m_charPos = 0; };
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
			
			this->RepaginateText();
			this->PostPaint();
			return;


		};
		//!Event handler for CTRL + V keystroke event
		void GtMultiTextEdit::OnPaste(GtEvent* ptrEvent)
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
						if (m_objCursor.m_charPos <= 0){ m_objCursor.m_charPos = 0; }
						strBegin = m_strText.substr(0, m_objCursor.m_charPos);
						if (m_objCursor.m_charPos >= intLen){ m_objCursor.m_charPos = intLen - 1; }
						int intLenEnd = (intLen - m_objCursor.m_charPos);
						strEnd = m_strText.substr(m_objCursor.m_charPos, intLenEnd);

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
					}
					else{
						m_strText = strNew;
					}
				}
				GlobalUnlock(hglbPaste);
			}
			CloseClipboard();
			//render the updated
			this->RepaginateText();
			this->PostPaint();
		};


		//
		//	Convert mouse(client) coordinates to a file-relative offset
		//
		//	Currently only uses the main font so will not support other
		//	fonts introduced by syntax highlighting
		//
		GtCursor GtMultiTextEdit::MouseCoordToStringPos(int mx, int my)
		{
			GtCursor cursorRet;
			if(!m_winID)
			{
				GtWidget* ptrRoot = this->GetRootWidget();
				if(!ptrRoot){return cursorRet;};//safety check
				m_winID = ptrRoot->Get_winID();
			}

			HDC    hdc      = GetDC(m_winID);
			HANDLE hOldFont = SelectObject(hdc, m_winFont.m_hFont);	

			int strLen;
			int pnCharOffset = 0;
			int curx = 0;
			int halfwidth = gRound(double(m_nFontWidth) / 2.0f);
			// get scrollable area
			// clip mouse to edge of window
			pnCharOffset = 0;


			if(m_strText.size() <= 0)
			{
				cursorRet.m_charPos = 0;
				cursorRet.m_lngLine = 0;
				cursorRet.m_xPos = m_objFrame.xMin;
				cursorRet.m_yPos = m_objFrame.yMin;
			}

			if(mx < m_objFrame.xMin){mx = m_objFrame.xMin;}
			if(my < m_objFrame.yMin){my = m_objFrame.yMin;}
			if(my >= m_objFrame.yMax){my = m_objFrame.yMax - 1;}
			if(mx >= m_objFrame.xMax){mx = m_objFrame.xMax  - 1;}
			GtPoint3DI mpos; mpos.x = mx; mpos.y = my;
			//find the line
			int i, numLines;
			numLines = m_arrLines.size();
			for(i = 0; i < numLines; i++)
			{
				GtTextLine * ptrLine = &m_arrLines.at(i);
				if(ptrLine)
				{

					if(ptrLine->m_objFrame.Contains(mpos))
					{//then on this line
						cursorRet.m_lngLine = ptrLine->m_lngLine;
						cursorRet.m_yPos = ptrLine->m_objFrame.yMin;
						//find the xpos
						int slength = ptrLine->m_endPos - ptrLine->m_startPos;
						if(slength <= 0){slength = 0;}
						std::string strTemp = m_strText.substr(ptrLine->m_startPos,slength);
						strLen = strTemp.size();
						int width = CalcStringWidth(hdc, strTemp.c_str(), strLen, 0);
						size_t i, charW, sumW;
						sumW = m_objFrame.xMin;
						//check if first char
						if(mx < (sumW + halfwidth) )
						{
							pnCharOffset = 0;
							cursorRet.m_charPos = ptrLine->m_startPos;
							cursorRet.m_xPos = m_objFrame.xMin;
							SelectObject(hdc, hOldFont);
							ReleaseDC(m_winID, hdc);
							return cursorRet;
						}
						//otherwise cycle through chars
						bool blnPosFound = false;
						i = 0;
						do{	

							charW = CalcStringWidth(hdc, &strTemp[i], 1, 0);
							sumW += charW;
							if( (mx + halfwidth)  < sumW)
							{
								cursorRet.m_charPos = ptrLine->m_startPos + i;
								blnPosFound = true;
								cursorRet.m_xPos = sumW - charW;
							}
							i++;
						}while(( i < strLen)&&(!blnPosFound));

						if(i >= strLen)
						{
							//set to last character
							pnCharOffset = strLen;
							cursorRet.m_charPos = ptrLine->m_startPos + pnCharOffset;
							cursorRet.m_xPos = sumW;
						}

					}//end line contains point
				}//end valid line
			}//end loop through lines

			SelectObject(hdc, hOldFont);
			ReleaseDC(m_winID, hdc);

			return cursorRet;
		}


		void GtMultiTextEdit::ClearSelection(void)
		{
			m_lngSelStart = m_objCursor.m_charPos;
			m_lngSelEnd = m_objCursor.m_charPos;
			int i, numLines;
			numLines = m_arrLines.size();
			for(i = 0; i < numLines;i++)
			{
				GtTextLine* ptrLine = &m_arrLines.at(i);
				if(ptrLine)
				{
					ptrLine->m_endHighlight = 0;
					ptrLine->m_startHighlight = 0;
					ptrLine->m_objHighFrame.Zero();
				}
			}

		};


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
		int GtMultiTextEdit::CalcCtrlCharWidth(HDC hdc, ULONG chValue, GtWinFont *font)
		{
			SIZE sz;
			const wchar_t *str = CtrlStr(chValue % 32);
			GetTextExtentPoint32(hdc, (LPCSTR)str, wcslen(str), &sz);
			return sz.cx + 4;
		}

		//
		//	
		//
		int GtMultiTextEdit::CalcTabWidth(void)
		{
			return m_nTabWidthChars * m_nFontWidth;
		}

		//
		//	Wrapper for GetTextExtentPoint32. Takes into account
		//	control-characters, tabs etc.
		//
		int GtMultiTextEdit::CalcStringWidth(HDC hdc, const char *buf, int len, int nTabOrigin)
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

		int GtMultiTextEdit::CalcStringHeight(HDC hdc)
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

		void GtMultiTextEdit::ConvGtFontToWinFont(void)
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
		ULONG GtMultiTextEdit::RepositionCaret()
		{
			
			int   xpos   = m_objFrame.xMin;
			int   ypos   = m_objFrame.yMin;
			// make sure we are using the right font
			HDC hdc = GetDC(m_winID);
			SelectObject(hdc, m_winFont.m_hFont);

			// now find the x-coordinate on the specified line
			int line = m_objCursor.m_lngLine;
			GtTextLine * ptrLine = &m_arrLines.at(line);
			if(ptrLine)
			{

				int slen = ptrLine->m_endPos - ptrLine->m_startPos;
				int offset = m_objCursor.m_charPos - ptrLine->m_startPos;
				std::string strTemp;
				strTemp  = m_strText.substr(ptrLine->m_startPos, slen);
				int width = this->CalcStringWidth(hdc,strTemp.c_str(),offset,0);
				xpos = ptrLine->m_objFrame.xMin + width;
				ypos = ptrLine->m_objFrame.yMin;
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
		int GtMultiTextEdit::ScrollDir(int counter, int distance)
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

		void GtMultiTextEdit::RepaginateText(void)
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
				ptrLine->m_objFrame.yMin = yCpos;
				ptrLine->m_objFrame.yMax = yCpos + m_nLineHeight;

				ptrLine->m_startPos = lineStart;
				ptrLine->m_endPos = lineEnd;
				//advance to next line
				intCurrLine++;
				yCpos += m_nLineHeight;
				//if auto expand reset the frame
				if(m_blnAutoExpand)
				{
					m_objFrame.yMax = yCpos;
				}
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


		//!Update all of the highlight rects
		void GtMultiTextEdit::UpdateHighlightRects(void)
		{
			int i, j, numLines, strWidth;
			int lineStart,lineEnd, lastLine, lastYPos;
			int intCurrLine = 0;
			size_t intScanPos = 0;
			size_t strLen = m_strText.size();
			// make sure we are using the right font
			HDC hdc = GetDC(m_winID);
			SelectObject(hdc, m_winFont.m_hFont);

			numLines = m_arrLines.size();
			for(i = 0; i < numLines; i++)
			{
				GtTextLine * ptrLine = &m_arrLines.at(i);
				if(ptrLine)
				{
					lineStart = ptrLine->m_startPos;
					lineEnd = ptrLine->m_endPos;

					if((m_lngSelEnd - m_lngSelStart) > 5)
					{
						int z = 10;
					}
					//s
					if((m_lngSelStart > lineStart)&&
						(m_lngSelStart < lineEnd))
					{
						ptrLine->m_startHighlight = m_lngSelStart;
					}else if((m_lngSelStart < lineStart)&&
						(m_lngSelEnd > lineStart))
					{
						ptrLine->m_startHighlight = lineStart;
					}else{
						ptrLine->m_startHighlight = -1;
					}

					if((m_lngSelEnd > lineStart)&&
						(m_lngSelEnd < lineEnd))
					{
						ptrLine->m_endHighlight = m_lngSelEnd;
					}else if((m_lngSelStart < lineEnd)&&
						(m_lngSelEnd > lineEnd))
					{
						ptrLine->m_endHighlight = lineEnd;
					}else{
						ptrLine->m_endHighlight = -1;
					}

					//set the frame
					if(ptrLine->m_startHighlight == ptrLine->m_endHighlight)
					{
						ptrLine->m_objHighFrame.Zero();
					}else{
						ptrLine->m_objHighFrame = ptrLine->m_objFrame;
						int xPosStart  = ptrLine->m_objHighFrame.xMin;
						if(ptrLine->m_startHighlight > lineStart)
						{
							xPosStart += CalcStringWidth(hdc,&m_strText[lineStart],
								(ptrLine->m_startHighlight - lineStart),0);
							ptrLine->m_objHighFrame.xMin = xPosStart;
						}

						int xPosEnd  = ptrLine->m_objHighFrame.xMax;
						if(ptrLine->m_endHighlight < lineEnd)
						{
							xPosEnd = ptrLine->m_objFrame.xMin;
							xPosEnd += CalcStringWidth(hdc,&m_strText[lineStart],
								(ptrLine->m_endHighlight - lineStart),0);
							ptrLine->m_objHighFrame.xMax = xPosEnd;
						}
					}
				}//end line pointer
			}//end loop through lines

			//clean up the HDC
			ReleaseDC(m_winID, hdc);

			//SetCaretPos(xpos, ypos);

		};

		//!Find Next White Space Character
		long GtMultiTextEdit::FindNextWSChar(const std::string & strInput,size_t intStartPos)
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
		long GtMultiTextEdit::FindPrevWSChar(const std::string & strInput,size_t intStartPos)
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

			void GtMultiTextEdit::CursorNext(void)
			{
				m_objCursor.m_charPos++;
				if(m_objCursor.m_charPos >= m_strText.size())
				{
					m_objCursor.m_charPos = m_strText.size() - 1;
				}
			};

			void GtMultiTextEdit::CursorPrev(void)
			{
				m_objCursor.m_charPos--;
				if(m_objCursor.m_charPos <= 0)
				{
					m_objCursor.m_charPos = 0;
				}		
			};

	};//end namespace GtCore

};//end namespace GT