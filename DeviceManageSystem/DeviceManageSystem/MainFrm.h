#pragma once
#include "DepartmentBar.h"
#include "ClassificationBar.h"

class CMainFrame : public CFrameWndEx
{
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 重写
public:
	virtual ~CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	// Ribbon Button
	afx_msg void OnButtonNavigation();
	afx_msg void OnButtonDetail();
	afx_msg void OnButtonTransfer();
	afx_msg void OnButtonMaintain();
	afx_msg void OnButtonScrapped();
	afx_msg void OnButtonReport();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonExit();

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

protected:
	CMFCRibbonBar				m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages			m_PanelImages;
	CMFCRibbonStatusBar			m_wndStatusBar;
	CDepartmentBar				m_wndDepartmentBar;
	CClassificationBar			m_wndClassificationBar;
};
