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

#include ".\GtGraphicEnums.h"

using namespace GT::GtCore;


namespace HTL
{


	//CONVERSION FUNCTIONS FOR GtPenJoinStyle//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtPenJoinStyle>(GtPenJoinStyle enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case MiterJoin: {strReturn = "MiterJoin";  return; break;};
			case BevelJoin: {strReturn = "BevelJoin";  return; break;};
			case RoundJoin: {strReturn = "RoundJoin";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "BevelJoin";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};

	template <>
	HTL_EXPORT void stringToEnum<GtPenJoinStyle>(std::string & strVal, GtPenJoinStyle & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = BevelJoin; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "MiterJoin"){enumValReturn = MiterJoin; return;};
			if(strVal == "BevelJoin"){enumValReturn = BevelJoin; return;};
			if(strVal == "RoundJoin"){enumValReturn = RoundJoin; return;};

			//DEFUALT UNKNOWN
			enumValReturn = BevelJoin;
			return;
		}catch(...){
			enumValReturn = BevelJoin;
			return;
		};
	};

	//CONVERSION FUNCTIONS FOR GtPenStyle//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtPenStyle>(GtPenStyle enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case NoPen: {strReturn = "NoPen";  return; break;};
			case SolidLine: {strReturn = "SolidLine";  return; break;};
			case DashLine: {strReturn = "DashLine";  return; break;};
			case DotLine: {strReturn = "DotLine";  return; break;};
			case DashDotLine: {strReturn = "DashDotLine";  return; break;};
			case DashDotDotLine: {strReturn = "DashDotDotLine";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "SolidLine";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};

	template <>
	HTL_EXPORT void stringToEnum<GtPenStyle>(std::string & strVal, GtPenStyle & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = SolidLine; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "NoPen"){enumValReturn = NoPen; return;};
			if(strVal == "SolidLine"){enumValReturn = SolidLine; return;};
			if(strVal == "DashLine"){enumValReturn = DashLine; return;};
			if(strVal == "DotLine"){enumValReturn = DotLine; return;};
			if(strVal == "DashDotLine"){enumValReturn = DashDotLine; return;};
			if(strVal == "DashDotDotLine"){enumValReturn = DashDotDotLine; return;};

			//DEFUALT UNKNOWN
			enumValReturn = SolidLine;
			return;
		}catch(...){
			enumValReturn = SolidLine;
			return;
		};
	};
	//CONVERSION FUNCTIONS FOR GtBrushStyle//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtBrushStyle>(GtBrushStyle enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case NoBrush: {strReturn = "NoBrush";  return; break;};
			case SolidPattern: {strReturn = "SolidPattern";  return; break;};
			case Dense1Pattern: {strReturn = "Dense1Pattern";  return; break;};
			case Dense2Pattern: {strReturn = "Dense2Pattern";  return; break;};
			case Dense3Pattern: {strReturn = "Dense3Pattern";  return; break;};
			case Dense4Pattern: {strReturn = "Dense4Pattern";  return; break;};
			case Dense5Pattern: {strReturn = "Dense5Pattern";  return; break;};
			case Dense6Pattern: {strReturn = "Dense6Pattern";  return; break;};
			case Dense7Pattern: {strReturn = "Dense7Pattern";  return; break;};
			case HorzontalPattern: {strReturn = "HorzontalPattern";  return; break;};
			case VerticalPattern: {strReturn = "VerticalPattern";  return; break;};
			case CrossPattern: {strReturn = "CrossPattern";  return; break;};
			case BackDiagPattern: {strReturn = "BackDiagPattern";  return; break;};
			case ForeDiagPattern: {strReturn = "ForeDiagPattern";  return; break;};
			case DiagCrossPattern: {strReturn = "DiagCrossPattern";  return; break;};
			case LinearGradientPattern: {strReturn = "LinearGradientPattern";  return; break;};
			case RadialGradientPattern: {strReturn = "RadialGradientPattern";  return; break;};
			case TexturePattern: {strReturn = "TexturePattern";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "SolidPattern";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};
	template <>
	HTL_EXPORT void stringToEnum<GtBrushStyle>(std::string & strVal, GtBrushStyle & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = SolidPattern; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "NoBrush"){enumValReturn = NoBrush; return;};
			if(strVal == "SolidPattern"){enumValReturn = SolidPattern; return;};
			if(strVal == "Dense1Pattern"){enumValReturn = Dense1Pattern; return;};
			if(strVal == "Dense2Pattern"){enumValReturn = Dense2Pattern; return;};
			if(strVal == "Dense3Pattern"){enumValReturn = Dense3Pattern; return;};
			if(strVal == "Dense4Pattern"){enumValReturn = Dense4Pattern; return;};
			if(strVal == "Dense5Pattern"){enumValReturn = Dense5Pattern; return;};
			if(strVal == "Dense6Pattern"){enumValReturn = Dense6Pattern; return;};
			if(strVal == "Dense7Pattern"){enumValReturn = Dense7Pattern; return;};
			if(strVal == "HorzontalPattern"){enumValReturn = HorzontalPattern; return;};
			if(strVal == "VerticalPattern"){enumValReturn = VerticalPattern; return;};
			if(strVal == "CrossPattern"){enumValReturn = CrossPattern; return;};
			if(strVal == "BackDiagPattern"){enumValReturn = BackDiagPattern; return;};
			if(strVal == "ForeDiagPattern"){enumValReturn = ForeDiagPattern; return;};
			if(strVal == "DiagCrossPattern"){enumValReturn = DiagCrossPattern; return;};
			if(strVal == "LinearGradientPattern"){enumValReturn = LinearGradientPattern; return;};
			if(strVal == "RadialGradientPattern"){enumValReturn = RadialGradientPattern; return;};
			if(strVal == "TexturePattern"){enumValReturn = TexturePattern; return;};

			//DEFUALT UNKNOWN
			enumValReturn = SolidPattern;
			return;
		}catch(...){
			enumValReturn = SolidPattern;
			return;
		};
	};
	//CONVERSION FUNCTIONS FOR GtColorMode//////////////////////////
	template<>
	void HTL::enumToString<GtColorMode>(GtColorMode enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case CM_RGB: {strReturn = "CM_RGB";  return; break;};
			case CM_HSV: {strReturn = "CM_HSV";  return; break;};
			case CM_CYMK: {strReturn = "CM_CYMK";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "CM_RGB";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};

	template <>
	void stringToEnum<GtColorMode>(std::string & strVal, GtColorMode & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = CM_RGB; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "CM_RGB"){enumValReturn = CM_RGB; return;};
			if(strVal == "CM_HSV"){enumValReturn = CM_HSV; return;};
			if(strVal == "CM_CYMK"){enumValReturn = CM_CYMK; return;};

			//DEFUALT UNKNOWN
			enumValReturn = CM_RGB;
			return;
		}catch(...){
			enumValReturn = CM_RGB;
			return;
		};
	};

	//CONVERSION FUNCTIONS FOR GtFillRule//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtFillRule>(GtFillRule enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case OddEvenFill: {strReturn = "OddEvenFill";  return; break;};
			case WindingFill: {strReturn = "WindingFill";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "OddEvenFill";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};

	template <>
	HTL_EXPORT void stringToEnum<GtFillRule>(std::string & strVal, GtFillRule & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = OddEvenFill; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "OddEvenFill"){enumValReturn = OddEvenFill; return;};
			if(strVal == "WindingFill"){enumValReturn = WindingFill; return;};

			//DEFUALT UNKNOWN
			enumValReturn = OddEvenFill;
			return;
		}catch(...){
			enumValReturn = OddEvenFill;
			return;
		};
	};
	//CONVERSION FUNCTIONS FOR GtContextMenuPolicy//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtContextMenuPolicy>(GtContextMenuPolicy enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case NoContextMenu: {strReturn = "NoContextMenu";  return; break;};
			case DefaultContextMenu: {strReturn = "DefaultContextMenu";  return; break;};
			case ActionsContextMenu: {strReturn = "ActionsContextMenu";  return; break;};
			case CustomContextMenu: {strReturn = "CustomContextMenu";  return; break;};
			case PreventContextMenu: {strReturn = "PreventContextMenu";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "NoContextMenu";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};

	template <>
	HTL_EXPORT void stringToEnum<GtContextMenuPolicy>(std::string & strVal, GtContextMenuPolicy & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = NoContextMenu; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "NoContextMenu"){enumValReturn = NoContextMenu; return;};
			if(strVal == "DefaultContextMenu"){enumValReturn = DefaultContextMenu; return;};
			if(strVal == "ActionsContextMenu"){enumValReturn = ActionsContextMenu; return;};
			if(strVal == "CustomContextMenu"){enumValReturn = CustomContextMenu; return;};
			if(strVal == "PreventContextMenu"){enumValReturn = PreventContextMenu; return;};

			//DEFUALT UNKNOWN
			enumValReturn = NoContextMenu;
			return;
		}catch(...){
			enumValReturn = NoContextMenu;
			return;
		};
	};
	//CONVERSION FUNCTIONS FOR GtFocusPolicy//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtFocusPolicy>(GtFocusPolicy enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case NoFocus: {strReturn = "NoFocus";  return; break;};
			case TabFocus: {strReturn = "TabFocus";  return; break;};
			case ClickFocus: {strReturn = "ClickFocus";  return; break;};
			case StrongFocus: {strReturn = "StrongFocus";  return; break;};
			case WheelFocus: {strReturn = "WheelFocus";  return; break;};

				//DEFUALT UNKNOWN
			default: {strReturn = "NoFocus";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};
	template <>
	HTL_EXPORT void stringToEnum<GtFocusPolicy>(std::string & strVal, GtFocusPolicy & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = NoFocus; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "NoFocus"){enumValReturn = NoFocus; return;};
			if(strVal == "TabFocus"){enumValReturn = TabFocus; return;};
			if(strVal == "ClickFocus"){enumValReturn = ClickFocus; return;};
			if(strVal == "StrongFocus"){enumValReturn = StrongFocus; return;};
			if(strVal == "WheelFocus"){enumValReturn = WheelFocus; return;};

			//DEFUALT UNKNOWN
			enumValReturn = NoFocus;
			return;
		}catch(...){
			enumValReturn = NoFocus;
			return;
		};
	};
	//CONVERSION FUNCTIONS FOR GtWindowFlag//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtWindowFlag>(GtWindowFlag enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case NoWindowFlags: {strReturn = "NoWindowFlags";  return; break;};
			case ShowMinimize: {strReturn = "ShowMinimize";  return; break;};
			case ShowMaximize: {strReturn = "ShowMaximize";  return; break;};
			case ShowClose: {strReturn = "ShowClose";  return; break;};
			case ShowStatusBar: {strReturn = "ShowStatusBar";  return; break;};
			case ShowProgressBar: {strReturn = "ShowProgressBar";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "NoWindowFlags";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};
	template <>
	HTL_EXPORT void stringToEnum<GtWindowFlag>(std::string & strVal, GtWindowFlag & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = NoWindowFlags; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "NoWindowFlags"){enumValReturn = NoWindowFlags; return;};
			if(strVal == "ShowMinimize"){enumValReturn = ShowMinimize; return;};
			if(strVal == "ShowMaximize"){enumValReturn = ShowMaximize; return;};
			if(strVal == "ShowClose"){enumValReturn = ShowClose; return;};
			if(strVal == "ShowStatusBar"){enumValReturn = ShowStatusBar; return;};
			if(strVal == "ShowProgressBar"){enumValReturn = ShowProgressBar; return;};
			//DEFUALT UNKNOWN
			enumValReturn = NoWindowFlags;
			return;
		}catch(...){
			enumValReturn = NoWindowFlags;
			return;
		};
	};
	//CONVERSION FUNCTIONS FOR GtWindowType//////////////////////////
	template<>
	HTL_EXPORT void HTL::enumToString<GtWindowType>(GtWindowType enumVal, std::string & strReturn)
	{
		try{
			switch(enumVal)
			{
			case WidgetType: {strReturn = "WidgetType";  return; break;};
			case MainWindow: {strReturn = "MainWindow";  return; break;};
			case SubWindow: {strReturn = "SubWindow";  return; break;};
			case DialogModal: {strReturn = "DialogModal";  return; break;};
			case DialogModeless: {strReturn = "DialogModeless";  return; break;};
			case Popup: {strReturn = "Popup";  return; break;};
			case SpashScreen: {strReturn = "SpashScreen";  return; break;};
				//DEFUALT UNKNOWN
			default: {strReturn = "WidgetType";  return; break;};

			};
		}catch(...){
			strReturn = "";
		};
		return;

	};
	template <>
	HTL_EXPORT void stringToEnum<GtWindowType>(std::string & strVal, GtWindowType & enumValReturn)
	{
		try{
			if(strVal.empty()){enumValReturn = WidgetType; return;};
			//check by comparison
			//HTL CPLUSPLUS NATIVE TYPES
			if(strVal == "WidgetType"){enumValReturn = WidgetType; return;};
			if(strVal == "MainWindow"){enumValReturn = MainWindow; return;};
			if(strVal == "SubWindow"){enumValReturn = SubWindow; return;};
			if(strVal == "DialogModal"){enumValReturn = DialogModal; return;};
			if(strVal == "DialogModeless"){enumValReturn = DialogModeless; return;};
			if(strVal == "Popup"){enumValReturn = Popup; return;};
			if(strVal == "SpashScreen"){enumValReturn = SpashScreen; return;};
			//DEFUALT UNKNOWN
			enumValReturn = WidgetType;
			return;
		}catch(...){
			enumValReturn = WidgetType;
			return;
		};
	};

};//end namespace