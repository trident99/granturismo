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

#include "windows.h"
#include <cstdlib>

#include ".\TestWindow.h"

#include <modGtProcess.h>
#include <modGtGeometry.h>


using namespace HTL;
using namespace GT::GtCore;
using namespace GT::GtGui;

//int WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
//LPSTR lpCmdLine, int nCmdShow)

//int main(int argc, char *argv[])

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)

{
	int argc = 0;
	char argv = '0';
	//set up the application
	GtApplication::GtApplicationInit(argc, &argv);
	GtApplication* ptrApp = GtApplication::GetAppInstancePtr();
	//set up the event win handle and start the event loop
	if (ptrApp)
	{
		//set up the main window
		TestWindow objMain;
		objMain.Show();

		ptrApp->Set_winID(objMain.Get_winID());
		ptrApp->Set_ptrWindow(&objMain);
		ptrApp->Execute();
	}

	try
	{
		GtApplication::Quit();
		exit(0);
	}
	catch (...){};
	return 0;
};