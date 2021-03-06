#pragma once
#include "DlgDepartment.h"

class CDeviceManageSystemView : public CView
{
protected:
	CDeviceManageSystemView();
	virtual ~CDeviceManageSystemView();
	DECLARE_DYNCREATE(CDeviceManageSystemView)

public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg LRESULT OnUpdateDepartment(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	bool CreateDepartmentView();
	void InitDepartmentView();
	void MoveDepartmentView();
	void DestroyDepartmentView();

private:
	CDlgDepartment	* m_pDepartView;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


