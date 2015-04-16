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


#ifndef GT_GRAPHIC_ENUMS_H
#define GT_GRAPHIC_ENUMS_H

#include "..\GtCoreLibRefs.h"
using namespace HTL;

namespace GT
{
	namespace GtCore
	{
		//!Pen joint type enumerator
		enum GtPenJoinStyle
		{
			MiterJoin = 0x00, //The outer edges of the lines are extended to meet at an angle, and this area is filled. 
			BevelJoin = 0x40, //The triangular notch between the two lines is filled. 
			RoundJoin = 0x80, //A circular arc between the two lines is filled. 
		};

		//!Pen drawing style enumerator
		enum GtPenStyle
		{
			NoPen = 0, //no line at all. For example, QPainter::drawRect() fills but does not draw any boundary line. 
			SolidLine = 1, //A plain line. 
			DashLine = 2, //Dashes separated by a few pixels. 
			DotLine = 3, //Dots separated by a few pixels. 
			DashDotLine = 4, //Alternate dots and dashes. 
			DashDotDotLine = 5 //One dash, two dots, one dash, two dots. 
		};

		//!Brush drawing style enumerator
		enum GtBrushStyle
		{
			NoBrush = 0, //No brush pattern. 
			SolidPattern = 1, // Uniform color. 
			Dense1Pattern = 2, // Extremely dense brush pattern. 
			Dense2Pattern = 3, // Very dense brush pattern. 
			Dense3Pattern = 4, // Somewhat dense brush pattern. 
			Dense4Pattern = 5, // Half dense brush pattern. 
			Dense5Pattern = 6, // Somewhat sparse brush pattern. 
			Dense6Pattern = 7, // Very sparse brush pattern. 
			Dense7Pattern = 8, // Extremely sparse brush pattern. 
			HorzontalPattern = 9, // Horizontal lines. 
			VerticalPattern = 10, // Vertical lines. 
			CrossPattern = 11, // Crossing horizontal and vertical lines. 
			BackDiagPattern = 12, // Backward diagonal lines. 
			ForeDiagPattern = 13, // Forward diagonal lines. 
			DiagCrossPattern = 14, // Crossing diagonal lines. 
			LinearGradientPattern = 15, // Linear gradient (set using a dedicated QBrush constructor). 
			RadialGradientPattern = 16, // Radial gradient (set using a dedicated QBrush constructor). 
			TexturePattern = 20, // Custom pattern (see GtBrush::SetTexture()). 
		};

		//!The color scheme mode for the image
		enum GtColorMode
		{
			CM_RGB = 0,
			CM_HSV = 1,
			CM_CYMK = 2
		};

		enum GtFillRule
		{
			OddEvenFill = 0, 
			//Specifies that the region is filled using the odd even fill rule.
			//With this rule, we determine whether a point is inside the shape by using the following method.
			//Draw a horizontal line from the point to a location outside the shape, and count the number of intersections.
			//If the number of intersections is an odd number, the point is inside the shape. This mode is the default. 
			WindingFill = 1 
			//Specifies that the region is filled using the non zero winding rule. 
			//With this rule, we determine whether a point is inside the shape by using the following method.
			//Draw a horizontal line from the point to a location outside the shape.
			//Determine whether the direction of the line at each intersection point is up or down.
			//The winding number is determined by summing the direction of each intersection.
			//If the number is non zero, the point is inside the shape.
			//This fill mode can also in most cases be considered as the intersection of closed shapes. 
		};

		enum GtContextMenuPolicy
		{
			NoContextMenu =	0,	//the widget does not feature a context menu, context menu handling is deferred to the widget's parent.
			DefaultContextMenu = 1,	//the widget's QWidget::contextMenuEvent() handler is called.
			ActionsContextMenu = 2,	//the widget displays its QWidget::actions() as context menu.
			CustomContextMenu =	3,	//the widget emits the QWidget::customContextMenuRequested() signal.
			PreventContextMenu = 4	//the widget does not feature a context menu, and in contrast to NoContextMenu, the handling is not deferred to the widget's parent. This means that all right mouse button events are guaranteed to be delivered to the widget itself through mousePressEvent(), and mouseReleaseEvent().
		};

		enum GtFocusPolicy
		{
			NoFocus	= 0x00,	//the widget does not accept focus.
			TabFocus = 0x01, //the widget accepts focus by tabbing.
			ClickFocus = 0x02,	//the widget accepts focus by clicking.
			StrongFocus	= TabFocus | ClickFocus | 0x04,	//the widget accepts focus by both tabbing and clicking.
			WheelFocus	= StrongFocus | 0x08	//like Qt::StrongFocus plus the widget accepts focus by using the mouse wheel.
		};

		enum GtWindowFlag
		{
			NoWindowFlags = 0x0000,
			ShowMinimize = 0x0002,
			ShowMaximize = 0x0004,
			ShowClose = 0x0008,
			ShowStatusBar = 0x0010,
			ShowProgressBar = 0x0020
		};
		
		enum GtWindowType
		{
			WidgetType = 0x0000,
			MainWindow = 0x0002,
			SubWindow = 0x0004,
			DialogModal = 0x0008,
			DialogModeless = 0x0010,
			Popup = 0x0020,
			SpashScreen = 0x0040 
		};

	};//end namespace GtCore

};//end namespace GT

//Enumerated type translation functions
namespace HTL
{
	using namespace GT::GtCore;


	//CONVERSION FUNCTIONS FOR GtPenJoinStyle//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtPenJoinStyle>(GtPenJoinStyle enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtPenJoinStyle>(std::string & strVal, GtPenJoinStyle & enumValReturn);

	//CONVERSION FUNCTIONS FOR GtPenStyle//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtPenStyle>(GtPenStyle enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtPenStyle>(std::string & strVal, GtPenStyle & enumValReturn);
	
	//CONVERSION FUNCTIONS FOR GtBrushStyle//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtBrushStyle>(GtBrushStyle enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtBrushStyle>(std::string & strVal, GtBrushStyle & enumValReturn);

	//CONVERSION FUNCTIONS FOR GtColorMode//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtColorMode>(GtColorMode enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtColorMode>(std::string & strVal, GtColorMode & enumValReturn);

	//CONVERSION FUNCTIONS FOR GtFillRule//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtFillRule>(GtFillRule enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtFillRule>(std::string & strVal, GtFillRule & enumValReturn);

	//CONVERSION FUNCTIONS FOR GtContextMenuPolicy//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtContextMenuPolicy>(GtContextMenuPolicy enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtContextMenuPolicy>(std::string & strVal, GtContextMenuPolicy & enumValReturn);

	//CONVERSION FUNCTIONS FOR GtFocusPolicy//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtFocusPolicy>(GtFocusPolicy enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtFocusPolicy>(std::string & strVal, GtFocusPolicy & enumValReturn);

	//CONVERSION FUNCTIONS FOR GtWindowFlag//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtWindowFlag>(GtWindowFlag enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtWindowFlag>(std::string & strVal, GtWindowFlag & enumValReturn);

	//CONVERSION FUNCTIONS FOR GtWindowType//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtWindowType>(GtWindowType enumVal, std::string & strReturn);

	template <>
	HTL_EXPORT void stringToEnum<GtWindowType>(std::string & strVal, GtWindowType & enumValReturn);
}

#endif//GT_GRAPHIC_ENUMS_H