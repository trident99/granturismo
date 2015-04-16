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

#include ".\GtRadioButton.h"
#include <modGtEvent.h>
#include <modGtMath.h>

namespace GT
{
	namespace GtGui
	{
		//!Parent set constructor
		GtRadioButton::GtRadioButton(GtObject* ptrParent)
			:GtButton(ptrParent)
		{
			m_intSelIndex = -1;
		};
			//!Virtual destructor
		GtRadioButton::~GtRadioButton(void)
		{
			
		};
		//!Accessors for m_intSelIndex
		void GtRadioButton::SetIndex(int index)
		{
			if((index <0) || (index >= m_arrOptions.size()) )
			{//then illegal index, do nothing
				return;
			}
			//otherwise set the index
			if(m_intSelIndex != index)
			{
				SelectionChanged.Emit(index);
			}
			m_intSelIndex = index;
		};
		//!Add a string value to the selection list
		void GtRadioButton::AddOption(std::string & strValue)
		{
			if(!strValue.empty())
			{
				m_arrOptions.push_back(strValue);
				this->UpdateGeometry();
			}
		};
		//!Clear the selection list
		void GtRadioButton::ClearOptions(void)
		{
			m_arrOptions.clear();
		};
		//!Count the number of values
		size_t GtRadioButton::CountOptions(void)
		{
			return m_arrOptions.size();
		};
		//!Get the string at the index selected
		std::string GtRadioButton::AtOption(int index)
		{
			std::string strNull;
			if( (index >= 0) && (index < m_arrOptions.size()) )
			{
				return m_arrOptions.at(index);
			}else{
				return strNull;
			}
		};

		void GtRadioButton::UpdateGeometry(void)
		{
			m_arrOptionBoxes.clear();
			size_t i, numOpts,iCurrY,iDy,iDs;
			numOpts = m_arrOptions.size();
			iDy = 25;
			iDs = 5;
			for(i = 0 ; i < numOpts;i++)
			{
				GtRectI newRect;
				newRect.xMin = m_objFrame.xMin;
				newRect.xMax = newRect.xMin + iDy;
				newRect.yMin = m_objFrame.yMin + (i * (iDy+iDs));
				newRect.yMax = newRect.yMin + iDy;
				m_arrOptionBoxes.push_back(newRect);
			}
			//update main frame
			m_objFrame.yMax = m_objFrame.yMin + (numOpts * (iDy+iDs));
			m_objFrame.xMax = m_objFrame.xMin + iDy;
		};

		//!Custom Event Processing
		int GtRadioButton::HandleEvent(GtEvent * ptrEvent)
		{
			//safety check
			if(!ptrEvent){return 0;};

			if(ptrEvent->m_objType == MouseLeftPress)
			{
				int intNewSel = -1;
				GtPoint3DI pos, hoverPos, delta;
				pos.x = gRound(ptrEvent->m_objPos.x);
				pos.y = gRound(ptrEvent->m_objPos.y);

				delta = this->RequestOffset();

				hoverPos.x = pos.x - delta.x;
				hoverPos.y = pos.y - delta.y;
				//drawing rectangles

				size_t i, numOpts;
				numOpts = m_arrOptionBoxes.size();
				for(i = 0; i < numOpts; i++)
				{
					if(m_arrOptionBoxes.at(i).Contains(hoverPos))
					{
						intNewSel = i;
						if(intNewSel != m_intSelIndex)
						{
							this->SetIndex(intNewSel);
							this->PostPaint();
							return 1;
						}else{
							//no selection change
							return 0;
						}
					}
				}//end loop through boxes
							
			}//end mouseleftpress
			return 0;
		};
		//!Custom Widget Painting
		int GtRadioButton::OnPaint(GtPainter * painter)
		{
			if(!m_blnVisible){return 0;};
			if(!painter){return 0;};
			//paint the frame
			GtPen oldPen;
			GtBrush oldBrush;
			//INITIALIZE PENS AND BRUSHES
			//record current painter settings
			oldPen = painter->Get_objPen();
			oldBrush = painter->Get_objBrush();
			//calculate the option boxes
			size_t i, numOpts;
			numOpts = m_arrOptions.size();
			for(i = 0; i < numOpts; i++)
			{
				//draw button
				if(m_intSelIndex == i)
				{//then selected
					painter->Set_objPen(m_objPen);
					painter->Set_objBrush(GtBrush(GtColor(0,0,0)));
				}else{
					painter->Set_objPen(m_objPen);
					painter->Set_objBrush(GtBrush(GtColor(255,255,255)));
				}
				painter->GtDrawEllipse(m_arrOptionBoxes.at(i));
				//draw text
				GtPoint3DI textPos;
				textPos.x = m_arrOptionBoxes.at(i).xMax + 5;
				textPos.y = m_arrOptionBoxes.at(i).yMin + 5;
				painter->GtDrawStaticText(m_arrOptions.at(i),textPos);

			}

			//finished, reset old brushes and pens
			painter->Set_objPen(oldPen);
			painter->Set_objBrush(oldBrush);
			return 0;

		};	

	};//end namespace GtCore

};//end namespace GT