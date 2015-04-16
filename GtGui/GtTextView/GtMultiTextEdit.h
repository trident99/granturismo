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



#ifndef GT_MULTI_TEXT_EDIT_H
#define GT_MULTI_TEXT_EDIT_H

#include "..\GtBasicControls\GtFrame.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
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


		class HTL_DLLAPI GtMultiTextEdit : public GtWidget
		{
		public:
			//!Parent set constructor
			GtMultiTextEdit(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtMultiTextEdit(void);

			//MEMBER VARIABLES////////////////////////
			//GEOMETRY
			//!The Cursor Point
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnAutoExpand);
			//!The highlight color for the widget
			GTOBJECT_MEMVAR_BYREF(public, GtColor, objHighColor);
			//!The Selection Start Point
			GTOBJECT_MEMVAR_BYVAL(public, long, lngSelStart);
			//!The Selection End Point
			GTOBJECT_MEMVAR_BYVAL(public, long, lngSelEnd);
			//!The Cursor Point
			GTOBJECT_MEMVAR_BYREF(public, GtCursor, objCursor);

			virtual void Set_objFont(GtFont varVal);

			//SIGNALS/////////////////////////////////
		public:
			//!Signal marking the beginning of an edit session
			HtlSignal00 BeginEdit;
			//!Signal marking the ending of an edit session
			HtlSignal00 EndEdit;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Gets the selected sub string
			std::string GetSelSubString(void);
			//conveinience functions, same as Get_strText
			void SetTextString(std::string & str){m_strText = str;};
			std::string GetTextString(void){return m_strText;};
			
			//!Clear the focus
			virtual void ClearFocus(GtWidget* ptrNewFocus);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);		

		protected:

			//!Event handler for character entered
			void OnKeyPress(GtEvent * ptrEvent);
			//!Event handler for key release
			void OnKeyRelease(GtEvent * ptrEvent);
			//!Event handler for horizontal scroll
			void OnHorizScroll(GtEvent * ptrEvent);
			//!Event handler for Left Mouse Click Press
			void OnLeftButtonPress(GtEvent * ptrEvent);
			//!Event handler for Left Mouse Click Press
			void OnLeftButtonRelease(GtEvent * ptrEvent);
			//!Event handler for Left Mouse Click Press
			void OnMouseMove(GtEvent * ptrEvent);
			//!Event handler for CTRL + C keystroke event
			void OnCopy(GtEvent* ptrEvent);
			//!Event handler for CTRL + X keystroke event
			void OnCut(GtEvent* ptrEvent);
			//!Event handler for CTRL + V keystroke event
			void OnPaste(GtEvent* ptrEvent);

		private:
			// Font-related data	
			int		m_nFontWidth;
			int		m_nLineHeight;

			// Display-related data
			int		m_nTabWidthChars;

			// Runtime data
			bool	m_blnMouseDown;

			GtPoint3DI m_objLastPos;

			GtWinFont m_winFont;
			//!The text Lines
			Htl1DList<GtTextLine,HtlUnknownType> m_arrLines;
			//NOTE: GtWidget m_strText contains the
			//contents of the edit control

			GtCursor  MouseCoordToStringPos(int mx, int my);
			ULONG RepositionCaret(void);

			void ClearSelection(void);
			int CalcCtrlCharWidth(HDC hdc, ULONG chValue, GtWinFont *fa);
			int CalcTabWidth(void);
			int CalcStringWidth(HDC hdc, const char *buf, int len, int nTabOrigin);
			int CalcStringHeight(HDC hdc);
			int ScrollDir(int counter, int distance);
			void ConvGtFontToWinFont(void);

			//!Pagination functions
			void RepaginateText(void);
			//!Update all of the highlight rects
			void UpdateHighlightRects(void);
			//!Find the next White Space Character
			long FindNextWSChar(const std::string & strInput,size_t intStartPos);
			//!Find the previous White Space Character
			long FindPrevWSChar(const std::string & strInput,size_t intStartPos);

			void CursorNext(void);

			void CursorPrev(void);
		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H