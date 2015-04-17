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

#ifndef GT_WIDGET_H
#define GT_WIDGET_H

#include "..\GtCoreLibRefs.h"
#include "..\modGtBase.h"
#include "..\modGtGeometry.h"

#include ".\GtFont.h"
#include ".\GtBrush.h"
#include ".\GtPen.h"
#include ".\GtPainter.h"

using namespace HTL;


namespace GT
{
	namespace GtCore
	{
		class GtWidget;
		class GtEventManager;

		typedef Htl1DList<GtWidget*,HTL_BASE_PTR> GtWidgetList;

		class HTL_DLLAPI GtWidget : public GtObject
		{
		public:
			//!Parent set constructor
			GtWidget(GtObject* ptrParent = NULL);
			//!Virtual destructor
			virtual ~GtWidget(void);

			//MEMBER VARIABLES////////////////////////
			//!String name for the object
			GTOBJECT_MEMVAR_BYREF(public, std::string, strName);
			//!String title for the object
			//!The rectangle geometry for the widget
			std::string Get_strText(void){return m_strText;};
			virtual void Set_strText(std::string & str);

			//FLAGS
			//!Boolean flag for has focus
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnFocus);
			//!Boolean flag for is modal(true), or modeless(false)
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnModal);
			//!Boolean flag for full screen
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnFullScreen);
			//!Boolean flag for is active window
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnIsActiveWin);
			//!Boolean flag for is minimized
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnMinimized);
			//!Boolean flag for is maximized
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnMaximized);
			//!Boolean flag for accepts drops from drag operations
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnAcceptsDrops);
			//!Boolean flag for autofill background
			GTOBJECT_MEMVAR_BYVAL(public, bool, blnAutoFillBackground);


			//!Window ID
			GTOBJECT_MEMVAR_BYVAL(public, HWND, winID);
			//!GtWindowsFlags
			GTOBJECT_MEMVAR_BYVAL(public, int, intWinFlags);
			//!Context Menu Policy
			GTOBJECT_MEMVAR_BYVAL(public, GtContextMenuPolicy, objContextPolicy);
			//!Focus Policy
			GTOBJECT_MEMVAR_BYVAL(public, GtFocusPolicy, objFocusPolicy);

			//!Top Widget for GUI
			void SetTopWidget(GtWidget* ptrObj);
			GtWidget* GetTopWidget(void);


			//STYLESHEET
			//!Font for the object text
			GTOBJECT_MEMVAR_BYREF(public, GtFont, objFont);	
			//!Paint Brush for the background 
			GTOBJECT_MEMVAR_BYREF(public, GtBrush, objBackBrush);	
			//!Paint Brush for the Foreground
			GTOBJECT_MEMVAR_BYREF(public, GtBrush, objForeBrush);	
			//!Paint Brush for the Foreground
			GTOBJECT_MEMVAR_BYREF(public, GtPen, objPen);
			//!Integer Paint Order
			GTOBJECT_MEMVAR_BYVAL(public, int, intPaintOrder);
			//!Integer Tab Order
			GTOBJECT_MEMVAR_BYVAL(public, int, intTabOrder);

			//GEOMETRY
			//!Paint Brush for the Foreground
			GTOBJECT_MEMVAR_BYREF(public, GtPoint3DI, objPos);
			//!Paint Brush for the Foreground
			GTOBJECT_MEMVAR_BYREF(public, GtPoint3DI, objOffset);
			//!The rectangle geometry for the widget
			GtRectI Get_objFrame(void){return m_objFrame;};
			virtual void Set_objFrame(GtRectI & frame);
			//!The minimum height of the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intMinHeight);
			//!The maximum height of the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intMaxHeight);
			//!The minimum width of the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intMinWidth);
			//!The maximum width of the widget
			GTOBJECT_MEMVAR_BYVAL(public, int, intMaxWidth);


			//SIGNALS/////////////////////////////////
		public:
			//!Signal for when the object is painted
			HtlSignal00  Painted; 
			//!Signal for when the object is closed
			HtlSignal00  Closed; 
			//MEMBER FUNCTIONS////////////////////////
		public:
			//!Gets the root widget for this structure
			virtual GtWidget* GetRootWidget(void);
			//!Gets the event manager pointer
			virtual GtEventManager* GetEventManager(void);
			//!Gets the event manager pointer
			virtual GtPoint3DI RequestOffset(void);
			//Post a paint event
			virtual void PostPaint(void);
			//Post a regular event
			virtual void PostEvent(GtEvent evnt);
			//!Custom Event Processing
			virtual int HandleEvent(GtEvent * ptrEvent){return 0;};
			//!Custom Widget Painting
			virtual int OnPaint(GtPainter * ptrPainter = NULL);
			//!Activate the window
			void ActivateWindow();
			//!Does the widget have focus
			bool HasFocus() const{return m_blnFocus;};
			//!Clear the focus
			virtual void ClearFocus(GtWidget* ptrNewFocus){m_blnFocus = false;};
			//!Set the visibility of the widget
			void SetVisible( bool blnIsVisible);
			bool GetVisible(void){return m_blnVisible;};
			//!Set the enabled of the widget
			void SetEnabled( bool blnIsEnabled);
			bool GetEnabled(void){return m_blnEnabled;};

			//!Get the pointer to the parent widget
			GtWidget *	GetParentWidget();
			//!Get the sub widget at the x,y position
			GtWidget *	SubWidgetAtPos(int x, int y);
			//!Get the sub widget at the position
			GtWidget *	SubWidgetAtPos(GtPoint3DI & p);
			//!Get the sub widget at the index
			GtWidget * AtSubWidget(size_t index);
			//!Get the sub widget at the index
			GtWidget * AtSubWidget(std::string strName);
			//!Add a subwidget to the collection
			int AddSubWidget(GtWidget* ptrAdd);
			//!Delete the subwidget with the pointer
			int DeleteSubWidget(GtWidget* ptrDel);
			//!Delete the sub widget at the index
			int DeleteSubWidget(size_t index);
			//!Delete ALL sub widgets
			int DeleteAllSubWidgets(void);
			//!Sort the sub widgets by their intPaintOrder
			void SortByOrder(void);
			//Get the child widgets bounding rectangle
			GtRectI	SubWidgetsRect();

			//!Get the height of the widget
			int	GetHeight() const;
			//!Get the width of the widget
			int	GetWidth() const;
			//!Get the position of the top left corner
			GtPoint3DI	GetPosition();
			//!Mapping coordinate points///////////////
			GtPoint3DI	mapFromGlobal(const GtPoint3DI & pos);
			GtPoint3DI	mapFromParent(const GtPoint3DI & pos);
			GtPoint3DI	mapToGlobal(const GtPoint3DI & pos);
			GtPoint3DI	mapToParent(const GtPoint3DI & pos);
			//!check to see if widget is under current mouse location
			bool	IsUnderMouse();

			bool   Contains(GtPoint3DI & pos);


			//!Hide the widget
			virtual void Hide();
			//!Show the widget
			virtual void Show();
			//!Close the widget
			virtual void Close();
			//!Show the widget FullScreen
			virtual void ShowFullScreen(){};
			//!Show the widget maximized
			virtual void ShowMaximized(){};
			//!Show the widget minimized
			virtual void ShowMinimized(){};
			//!Update the widget 
			virtual void Update(){this->PostPaint();};
			//!Tests and sets the focus widget based on the cursor location provided
			virtual GtWidget* SetFocusWidget(GtPoint3DI & pos);

		protected:
			//!Boolean flag for is visible
			bool m_blnVisible;
			//!Boolean flag for is enabled
			bool m_blnEnabled;
			//!String for display
			std::string m_strText;
			//!Main widget frame
			GtRectI m_objFrame;
			//!Collection of Child Widgets
			GtWidgetList m_arrSubWidgets;
			//!The root widget
			GtWidget* m_ptrRoot;

			static GtWidget* m_ptrTopWidget;
			//!pointer to the event manager
			GtEventManager* m_ptrEvMan;
		};//end HtlBase class definition

	}//end namespace GtCore
}//end namespace GT
#endif //GT_OBJECT_H