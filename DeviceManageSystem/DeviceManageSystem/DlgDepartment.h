#pragma once
#include "Device.h"
class CDlgDepartment : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDepartment)

public:
	CDlgDepartment(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDepartment();

	enum { IDD = IDD_DIALOG_DEPARTMENT };

public:
	void SetFile(const CString & csFile){ m_csFile = csFile; }
	void InitControl();
	void RefreshData();

protected:
	virtual void OnOK(){}
	virtual void OnCancel(){}
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonSave();

private:
	// 移动控件位置
	void MoveControl();

	// 插入一条数据
	void InsertInfo(Device * pDevice);

private:
/// 控件
	CButton		m_btnNew;
	CButton		m_btnOpen;
	CButton		m_btnDelete;
	CButton		m_btnSave;
	CListCtrl	m_listInfo;
/// 数据
	CString		m_csFile;
};
