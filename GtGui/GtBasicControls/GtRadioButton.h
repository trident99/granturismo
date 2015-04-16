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

#ifndef GT_RADIO_BUTTON_H
#define GT_RADIO_BUTTON_H

#include ".\GtButton.h"

using namespace HTL;
using namespace GT::GtCore;

namespace GT
{
	namespace GtGui
	{

		class HTL_DLLAPI GtRadioButton : public GtButton
		{
		public:
			//!Parent set constructor
			GtRadioButton(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtRadioButton(void);

			//MEMBER VARIABLES////////////////////////
			//!Accessors for m_intSelIndex
			int GetIndex(void){return m_intSelIndex;};
			void SetIndex(int index);

			//SIGNALS/////////////////////////////////
		public:
			HtlSignal01<int> SelectionChanged;

			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Get the string at the index selected
			std::string AtOption(int index);
			//!Count the number of values
			size_t CountOptions(void);
			//!Add a string value to the selection list
			void AddOption(std::string & strValue);
			//!Clear the selection list
			void ClearOptions(void);



			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent);
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * painter = NULL);	

		protected:

			void UpdateGeometry(void);

			//!Integer selected index
			int m_intSelIndex;
			//!The array of string values for the radio button
			Htl1DList<std::string,HtlUnknownType> m_arrOptions;
			//!The array of boxes that according to strings
			Htl1DList<GtRectI,HTL_BASE> m_arrOptionBoxes;

		};//end GtButton class definition

	}//end namespace GtGui
}//end namespace GT
#endif //GT_RADIO_BUTTON_H