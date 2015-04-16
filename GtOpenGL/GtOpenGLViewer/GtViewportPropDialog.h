#ifndef TGLVIEWPORTPROPDIALOG_H
#define TGLVIEWPORTPROPDIALOG_H

#include <QDialog>
#include "ui_TGLViewportPropDialog.h"
#include "..\modTCADLibRefs.h"


namespace TGL{

	class TGLViewport;
	class TGLOverlayViewport;


	class TGLViewportPropDialog : public QDialog
	{
		Q_OBJECT

	public:
		TGLViewportPropDialog(QWidget *parent = 0);
		~TGLViewportPropDialog();

		void SetViewportPtr(TGLViewport * ptrViewport);
		//render properties///////////////////////////
		void Set_enumProjectionMode(TGLProjectionMode objMode){m_enumProjectionMode = objMode; return;};
		TGLProjectionMode Get_enumProjectionMode(void){return m_enumProjectionMode;};

		void Set_enumRenderMode(TGLRenderMode objMode){m_enumRenderMode = objMode; return;};
		TGLRenderMode Get_enumRenderMode(void){return m_enumRenderMode;};

		void Set_blnAntiAliasingEnable(bool blnEnable){m_blnAntiAliasingEnable = blnEnable; return;};
		bool Get_blnAntiAliasingEnable(void){return m_blnAntiAliasingEnable;};

		//Display Properties//////////////////////////
		void Set_blnUniformBackgroundColor(bool blnUniform){m_blnUniformBackgroundColor = blnUniform; return;};
		bool Get_blnUniformBackgroundColor(void){return m_blnUniformBackgroundColor;};

		void Set_objBackgroundTopColor(TGLColor objColor){m_objBackgroundTopColor = objColor; return;};
		TGLColor Get_objBackgroundTopColor(void){return m_objBackgroundTopColor;};

		void Set_objBackgroundBottomColor(TGLColor objColor){m_objBackgroundBottomColor = objColor; return;};
		TGLColor Get_objBackgroundBottomColor(void){return m_objBackgroundBottomColor;};

		void Set_blnWCSIconAtOrigin(bool blnAtOrigin){m_blnWCSIconAtOrigin = blnAtOrigin; return;};
		bool Get_blnWCSIconAtOrigin(void){return m_blnWCSIconAtOrigin;};

		//Navigation Properties///////////////////////	
		void Set_blnLockXAxis(bool blnLockX){m_blnLockXAxis = blnLockX; return;};
		bool Get_blnLockXAxis(void){return m_blnLockXAxis;};

		void Set_blnLockYAxis(bool blnLockY){m_blnLockYAxis = blnLockY; return;};
		bool Get_blnLockYAxis(void){return m_blnLockYAxis;};

		void Set_blnLockZAxis(bool blnLockZ){m_blnLockZAxis = blnLockZ; return;};
		bool Get_blnLockZAxis(void){return m_blnLockZAxis;};

		void Set_blnLockOrthogonal(bool blnLockOrtho){m_blnLockOrthogonal = blnLockOrtho; return;};
		bool Get_blnLockOrthogonal(void){return m_blnLockOrthogonal;};

	protected:
		void InitializeDialog(void);

		void ApplyViewportProps(void);

		protected slots:
			void OnOK_Click(void);
			void OnCANCEL_Click(void);

			void OnChangeTopColor_Click(void);
			void OnChangeBottomColorClick(void);
	private:
		Ui::TGLViewportPropDialogClass ui;

		TGLViewport * m_ptrViewport;

		//render properties///////////////////////////
		TGLProjectionMode m_enumProjectionMode;
		TGLRenderMode m_enumRenderMode;
		bool m_blnAntiAliasingEnable;
		bool m_blnDisplayOverlay;

		//Display Properties//////////////////////////
		bool m_blnUniformBackgroundColor;
		TGLColor m_objBackgroundTopColor;
		TGLColor m_objBackgroundBottomColor;
		bool m_blnWCSIconAtOrigin;

		//Navigation Properties///////////////////////
		bool m_blnLockXAxis;
		bool m_blnLockYAxis;
		bool m_blnLockZAxis;
		bool m_blnLockOrthogonal;

		//Selection Properties///////////////////////
		bool m_blnSelectionEnabled;
		bool m_blnSingleSelect;


	};
};//end namespace
#endif // TGLVIEWPORTPROPDIALOG_H
