/*
**	This file is part of the TGLViewer Framework.
**	This software was developed by:
**
**	Anthony S. Daniels, Justin Gillespie	
**	The University of Michigan
**	Department of Naval Architecture & Marine Engineering
**	Department of Computer Science
**
**  TGLViewer is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  TGLViewer is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with TGLViewer.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef TGLOVERLAYVIEWPORT_H
#define TGLOVERLAYVIEWPORT_H
#include ".\TGLViewport.h"

namespace TGL
{
	class TGLSceneModel;
	class TGLLight;
	class TGLGrid;

	class TGLOverlayViewport : public TGLViewport
	{
		Q_OBJECT

	public:
		TGLOverlayViewport(QWidget *parent = 0);
		~TGLOverlayViewport();

protected:
	//THE REQUIRED OPENGL Drawing functions overridden
	virtual void initializeGL(void);
	virtual void resizeGL(GLsizei width, GLsizei height);
	virtual void paintEvent(QPaintEvent *event);
	virtual void paintGL(void);
	virtual void InitializeViewport(void);
	//draw the 2D overlay items on top of the OpenGL displayed graphic
	void DrawOverlay(const TGLViewpoint & ptrCurrViewPoint);

	private:

	};//end class TGLViewport
};//end namespace TGL
#endif // TGLVIEWPORT_H
