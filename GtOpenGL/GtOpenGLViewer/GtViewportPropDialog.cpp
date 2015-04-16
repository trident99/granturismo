#include "TGLViewportPropDialog.h"
#include ".\TGLViewport.h"
#include ".\TGLOverlayViewport.h"
using namespace TGL;

TGLViewportPropDialog::TGLViewportPropDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	InitializeDialog();
}

TGLViewportPropDialog::~TGLViewportPropDialog()
{

}


void TGLViewportPropDialog::InitializeDialog(void)
{
	//INITIALIZE CONTROLS
	ui.cmbProjectionMode->addItem("Perspective");
	ui.cmbProjectionMode->addItem("Orthographic");

	ui.cmbRenderMode->addItem("CurvesOnly");
	ui.cmbRenderMode->addItem("CurvesWithMesh");
	ui.cmbRenderMode->addItem("Shaded");
	ui.cmbRenderMode->addItem("ShadedWithMesh");
	ui.cmbRenderMode->addItem("ShadedWithCurves");
	ui.cmbRenderMode->addItem("ShadedBoundary");
	ui.cmbRenderMode->addItem("ShadeSelected");	
	//INITIALIZE ACTIONS
	//connect event handler for OK exit editor
	connect(ui.cmdOK,SIGNAL(clicked() ),this,SLOT(OnOK_Click() ) );
	//connect event handler for Cancel exit editor
	connect(ui.cmdCANCEL,SIGNAL(clicked() ),this,SLOT(OnCANCEL_Click() ) );
	//connect event handler for Cancel exit editor
	connect(ui.cmdSelBackgroundTopColor,SIGNAL(clicked() ),this,SLOT(OnChangeTopColor_Click() ) );
	//connect event handler for Cancel exit editor
	connect(ui.cmdSelBackgroundBottomColor,SIGNAL(clicked() ),this,SLOT(OnChangeBottomColorClick() ) );
};


void TGLViewportPropDialog::SetViewportPtr(TGLViewport * ptrViewport)
{
	int intIndexSel;
	QString strFormat;//"background-color: rgb(180, 200, 255);"

	if(ptrViewport)
	{
		m_ptrViewport = ptrViewport;
		//import all of the settings
		//projection mode
		this->m_enumProjectionMode = m_ptrViewport->Get_enumProjectionMode();
		intIndexSel = 0;
		if(m_enumProjectionMode == TCAD::Perspective){intIndexSel = ui.cmbProjectionMode->findText("Perspective");};
		if(m_enumProjectionMode == TCAD::Orthographic){intIndexSel = ui.cmbProjectionMode->findText("Orthographic");};
		if(intIndexSel < 0){intIndexSel = 0;};
		ui.cmbProjectionMode->setCurrentIndex(intIndexSel);

		//render mode
		this->m_enumRenderMode = m_ptrViewport->Get_enumRenderMode();
		intIndexSel = 0;
		if(m_enumRenderMode == TCAD::CurvesOnly){intIndexSel = ui.cmbRenderMode->findText("CurvesOnly");};
		if(m_enumRenderMode == TCAD::CurvesWithMesh){intIndexSel = ui.cmbRenderMode->findText("CurvesWithMesh");};
		if(m_enumRenderMode == TCAD::Shaded){intIndexSel = ui.cmbRenderMode->findText("Shaded");};
		if(m_enumRenderMode == TCAD::ShadedWithMesh){intIndexSel = ui.cmbRenderMode->findText("ShadedWithMesh");};
		if(m_enumRenderMode == TCAD::ShadedWithCurves){intIndexSel = ui.cmbRenderMode->findText("ShadedWithCurves");};
		if(m_enumRenderMode == TCAD::ShadedBoundary){intIndexSel = ui.cmbRenderMode->findText("ShadedBoundary");};
		if(m_enumRenderMode == TCAD::ShadeSelected){intIndexSel = ui.cmbRenderMode->findText("ShadeSelected");};
		if(intIndexSel < 0){intIndexSel = 0;};
		ui.cmbRenderMode->setCurrentIndex(intIndexSel);
		//antialiasing
		this->m_blnAntiAliasingEnable = m_ptrViewport->Get_blnAntiAliasing();
		ui.chkBlnAntiAliasing->setChecked(m_blnAntiAliasingEnable);

		//Display Properties//////////////////////////
		//uniform background
		this->m_blnUniformBackgroundColor = m_ptrViewport->Get_blnUniformBackground();
		ui.chkBlnUniformBackground->setChecked(m_blnUniformBackgroundColor);
		//top background color
		this->m_objBackgroundTopColor = m_ptrViewport->Get_objRGBTop();
		strFormat = "background-color: rgb(";
		strFormat.append(QString::number(m_objBackgroundTopColor.m_intRed) );
		strFormat.append(", ");
		strFormat.append(QString::number(m_objBackgroundTopColor.m_intGreen) );
		strFormat.append(", ");
		strFormat.append(QString::number(m_objBackgroundTopColor.m_intBlue) );
		strFormat.append(")");  
		ui.frmBackgroundTopColor->setStyleSheet(strFormat);
		//bottom background color
		this->m_objBackgroundBottomColor = m_ptrViewport->Get_objRGBBottom();
		strFormat = "background-color: rgb(";
		strFormat.append(QString::number(m_objBackgroundBottomColor.m_intRed) );
		strFormat.append(", ");
		strFormat.append(QString::number(m_objBackgroundBottomColor.m_intGreen) );
		strFormat.append(", ");
		strFormat.append(QString::number(m_objBackgroundBottomColor.m_intBlue) );
		strFormat.append(")");  
		ui.frmBackgroundBottomColor->setStyleSheet(strFormat);
		//WCS Icon at origin
		this->m_blnWCSIconAtOrigin = m_ptrViewport->Get_blnDrawWCSAtOrigin();
		ui.chkBlnWCSIconAtOrigin->setChecked(m_blnWCSIconAtOrigin);
		//Navigation Properties///////////////////////
		//lock X Axis
		this->m_blnLockXAxis = m_ptrViewport->Get_blnLockXAxis();
		ui.chkBlnLockXAxis->setChecked(m_blnLockXAxis);
		//lock Y Axis
		this->m_blnLockYAxis = m_ptrViewport->Get_blnLockYAxis();
		ui.chkBlnLockYAxis->setChecked(m_blnLockYAxis);
		//lock Z Axis
		this->m_blnLockZAxis = m_ptrViewport->Get_blnLockZAxis();
		ui.chkBlnLockZAxis->setChecked(m_blnLockZAxis);

		this->m_blnSelectionEnabled = m_ptrViewport->Get_blnSelectionEnabled();
		ui.chkBlnSelectionEnabled->setChecked(m_blnSelectionEnabled);

		this->m_blnSingleSelect = m_ptrViewport->Get_blnSingleSelect();
		ui.chkBlnSingleSelect->setChecked(m_blnSingleSelect);
	};
};

void TGLViewportPropDialog::ApplyViewportProps(void)
{
	
	if(m_ptrViewport)
	{
		//Render Properties//////////////////////
		//projection mode
		QString strProjectionMode = ui.cmbProjectionMode->currentText();
		m_enumProjectionMode = Perspective;//default value
		if(strProjectionMode ==  "Perspective"){m_enumProjectionMode = Perspective;};
		if(strProjectionMode ==  "Orthographic"){m_enumProjectionMode = Orthographic;};
		m_ptrViewport->Set_enumProjectionMode(m_enumProjectionMode);
		//render mode
		QString strRenderMode = ui.cmbRenderMode->currentText();
		m_enumRenderMode = ShadedWithCurves;//default value
		if(strRenderMode ==  "CurvesOnly"){m_enumRenderMode = CurvesOnly;};
		if(strRenderMode ==  "CurvesWithMesh"){m_enumRenderMode = CurvesWithMesh;};
		if(strRenderMode ==  "Shaded"){m_enumRenderMode = Shaded;};
		if(strRenderMode ==  "ShadedWithMesh"){m_enumRenderMode = ShadedWithMesh;};
		if(strRenderMode ==  "ShadedWithCurves"){m_enumRenderMode = ShadedWithCurves;};
		if(strRenderMode ==  "ShadedBoundary"){m_enumRenderMode = ShadedBoundary;};
		if(strRenderMode ==  "ShadeSelected"){m_enumRenderMode = ShadeSelected;};
		m_ptrViewport->Set_enumRenderMode(m_enumRenderMode);
		//anti-aliasing
		m_blnAntiAliasingEnable = ui.chkBlnAntiAliasing->isChecked();
		m_ptrViewport->Set_blnAntiAliasing(m_blnAntiAliasingEnable);
		//Display Properties//////////////////////////
		//uniform background
		m_blnUniformBackgroundColor = ui.chkBlnUniformBackground->isChecked();
		m_ptrViewport->Set_blnUniformBackground(m_blnUniformBackgroundColor);
		//top color
		m_ptrViewport->Set_objRGBTop(m_objBackgroundTopColor);
		//bottom color
		m_ptrViewport->Set_objRGBBottom(m_objBackgroundBottomColor);
		//WCS Icon At Origin
		m_blnWCSIconAtOrigin = ui.chkBlnWCSIconAtOrigin->isChecked();
		m_ptrViewport->Set_blnDrawWCSAtOrigin(m_blnWCSIconAtOrigin);
		//Navigation Properties//////////////////////////
		//lock x axis
		m_blnLockXAxis = ui.chkBlnUniformBackground->isChecked();
		m_ptrViewport->Set_blnLockXAxis(m_blnLockXAxis);
		//lock y axis
		m_blnLockYAxis = ui.chkBlnUniformBackground->isChecked();
		m_ptrViewport->Set_blnLockYAxis(m_blnLockYAxis);
		//lock z axis
		m_blnLockZAxis = ui.chkBlnUniformBackground->isChecked();
		m_ptrViewport->Set_blnLockZAxis(m_blnLockZAxis);

		this->m_blnSelectionEnabled = ui.chkBlnSelectionEnabled->isChecked();
		m_ptrViewport->Set_blnSelectionEnabled(m_blnSelectionEnabled);

		this->m_blnSingleSelect = ui.chkBlnSingleSelect->isChecked();
		m_ptrViewport->Set_blnSingleSelect(m_blnSingleSelect);

	};
	
};

void TGLViewportPropDialog::OnOK_Click(void)
{
	this->ApplyViewportProps();
	this->accept();
	return;
};

void TGLViewportPropDialog::OnCANCEL_Click(void)
{
	this->reject();
	return;
};

void TGLViewportPropDialog::OnChangeTopColor_Click(void)
{
	QColorDialog dlgColorMap;
	if(dlgColorMap.exec())
	{
		//then color accepted
		QColor objColorSelected = dlgColorMap.selectedColor();
		//QPalette palette = ui.frmCompColor->palette();
		//palette.setColor( backgroundRole(), objColorSelected );
		//ui.frmCompColor->setPalette( palette );
		//ui.frmCompColor->setAutoFillBackground( true );
		QString strFormat;//"background-color: rgb(180, 200, 255);"

		strFormat = "background-color: rgb(";
		strFormat.append(QString::number(objColorSelected.red()) );
		strFormat.append(", ");
		strFormat.append(QString::number(objColorSelected.green()) );
		strFormat.append(", ");
		strFormat.append(QString::number(objColorSelected.blue()) );
		strFormat.append(")");  

		ui.frmBackgroundTopColor->setStyleSheet(strFormat);
		m_objBackgroundTopColor.m_intRed = objColorSelected.red();
		m_objBackgroundTopColor.m_intGreen = objColorSelected.green();
		m_objBackgroundTopColor.m_intBlue = objColorSelected.blue();
	}else{
		return;
	};
};

void TGLViewportPropDialog::OnChangeBottomColorClick(void)
{
	QColorDialog dlgColorMap;
	if(dlgColorMap.exec())
	{
		//then color accepted
		QColor objColorSelected = dlgColorMap.selectedColor();
		//QPalette palette = ui.frmCompColor->palette();
		//palette.setColor( backgroundRole(), objColorSelected );
		//ui.frmCompColor->setPalette( palette );
		//ui.frmCompColor->setAutoFillBackground( true );
		QString strFormat;//"background-color: rgb(180, 200, 255);"

		strFormat = "background-color: rgb(";
		strFormat.append(QString::number(objColorSelected.red()) );
		strFormat.append(", ");
		strFormat.append(QString::number(objColorSelected.green()) );
		strFormat.append(", ");
		strFormat.append(QString::number(objColorSelected.blue()) );
		strFormat.append(")");  
			
		ui.frmBackgroundBottomColor->setStyleSheet(strFormat);
		m_objBackgroundBottomColor.m_intRed = objColorSelected.red();
		m_objBackgroundBottomColor.m_intGreen = objColorSelected.green();
		m_objBackgroundBottomColor.m_intBlue = objColorSelected.blue();
	}else{
		return;
	};
};



