#include ".\TGLOverlayViewport.h"


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

using namespace TGL;

TGLOverlayViewport::TGLOverlayViewport(QWidget *parent)
: TGLViewport(parent)
{
	//initialize the internal QT connections of signals and slots
	InitializeViewport();
}

TGLOverlayViewport::~TGLOverlayViewport()
{

}

//THE REQUIRED OPENGL Drawing functions overridden
void TGLOverlayViewport::initializeGL()
{
	TGLViewport::initializeGL();
	return;
};

void TGLOverlayViewport::resizeGL(GLsizei width, GLsizei height)// Resize And Initialize The GL Window
{
	TGLViewport::resizeGL(width, height);
	return;
};

void TGLOverlayViewport::paintGL()
{
	// Put OpenGL code here
	TGLViewport::paintGL();
	this->update();
};

void TGLOverlayViewport::paintEvent(QPaintEvent *event)
{
	QPainter objPainter( this );
	m_objCurrViewpoint.m_ptrPainter = &objPainter;
	objPainter.beginNativePainting();
	// Maybe necessary
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// Put OpenGL code here
	this->paintGL();
	// Necessary if used glPush-es above 
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
	objPainter.endNativePainting();

	//PERFORM 2D OVERLAY RENDERING
	//draw the scene objects overlays
	this->DrawOverlay(this->m_objCurrViewpoint);
	objPainter.end();
	//DEBUGGING CODE
	//objPainter.fillRect( 10, 10, 100, 100,
	//	QColor( 255, 0, 0 ) );

};

void TGLOverlayViewport::InitializeViewport(void)
{
	setAutoFillBackground(false);
	setMinimumSize(50, 50);
	return;
};

void TGLOverlayViewport::DrawOverlay(const TGLViewpoint & ptrCurrViewPoint)
{
	try{
		if(this->m_ptrPartModel)
		{
			this->m_ptrPartModel->RenderOverlay(this->m_objCurrViewpoint);
		}
	}catch(...){
		return;
	}
};




////paintOverlayGL()
// QPixmap pixmap(textWidth, textHeight);
// pixmap.fill(Qt::transparent);
//
// QPainter painter(&pixmap);
// painter.drawText(0, 0, textWidth, textHeight, Qt::AlignCenter | Qt::TextWordWrap, QString("My message..."));
//
// QImage image = pixmap.toImage();
// QImage glImage = TGLWidget::convertToGLFormat(image);
//
// glMatrixMode(GL_PROJECTION);
// glLoadIdentity();  
//#ifdef QT_OPENGL_ES
// glOrthof(0.0, width(), 0.0, height(), -100.0, 100.0);
//#else
// glOrtho(0.0, width(), 0.0, height(), -100.0, 100.0);


//QPainter p( this ); p.beginNativePainting();
//// Maybe necessary
//glPushAttrib(GL_ALL_ATTRIB_BITS);
//glMatrixMode(GL_PROJECTION);
//glPushMatrix();
//glMatrixMode(GL_MODELVIEW);
//glPushMatrix();
//// Put OpenGL code here
//// Necessary if used glPush-es above 
//glMatrixMode(GL_PROJECTION);
//glPopMatrix();
//glMatrixMode(GL_MODELVIEW);
//glPopMatrix();
//glPopAttrib();
//p.endNativePainting();
//p.fillRect( 10, 10, 100, 100,
//		   QColor( 255, 0, 0 ) ); 