#pragma once
#include "Device.h"

class CDlgDeviceDetail : public CDialog
{
	DECLARE_DYNAMIC(CDlgDeviceDetail)

public:
	CDlgDeviceDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDeviceDetail();

// 对话框数据
	enum { IDD = IDD_DLGDEVICEDETAIL };

public:
	// 设置UI数据
	void SetDeviceInfo(Device * pDevice);

	// 获取UI数据
	Device * GetDeviceInfo();

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// 初始话下拉列表信息
	void InitComboBoxInfo();

	// 更新UI数据
	void UpdateDeviceInfo(bool bGet);

	// 获取ComboBox里面的索引
	int SelectComboBox(CWnd * pComboBox, const CString & strText);

private:
// 数据
	Device *	m_pDevice;
};
