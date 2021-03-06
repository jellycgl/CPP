#include "stdafx.h"
#include "DeviceManageSystem.h"
#include "DlgDeviceDetail.h"
#include "afxdialogex.h"

// CDlgDeviceDetail 对话框

IMPLEMENT_DYNAMIC(CDlgDeviceDetail, CDialog)

CDlgDeviceDetail::CDlgDeviceDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceDetail::IDD, pParent)
	, m_pDevice(NULL)
{

}

CDlgDeviceDetail::~CDlgDeviceDetail()
{
}

void CDlgDeviceDetail::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgDeviceDetail, CDialog)
END_MESSAGE_MAP()

BOOL CDlgDeviceDetail::OnInitDialog()
{
	__super::OnInitDialog();

	InitComboBoxInfo();

	if (NULL != m_pDevice)
	{
		UpdateDeviceInfo(false);
	}
	else
	{
		m_pDevice = new Device();
	}

	return TRUE;
}

void CDlgDeviceDetail::InitComboBoxInfo()
{
	CComboBox * pCB = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICE_INPORTANCE);
	if (NULL != pCB)
	{
		pCB->InsertString(0, "A");
		pCB->InsertString(1, "B");
		pCB->InsertString(2, "C");

		pCB->SetCurSel(0);
	}

	pCB = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICE_TYPE);
	if (NULL != pCB)
	{
		pCB->InsertString(0, "机械");
		pCB->InsertString(1, "电气");
		pCB->InsertString(2, "仪表");

		pCB->SetCurSel(0);
	}

	pCB = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICE_STATUE);
	if (NULL != pCB)
	{
		pCB->InsertString(0, "停机");
		pCB->InsertString(1, "运行");
		pCB->InsertString(2, "停(运)机");

		pCB->SetCurSel(0);
	}

	pCB = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICE_CHECK_CYCLE);
	if (NULL != pCB)
	{
		pCB->InsertString(0, "H:小时");
		pCB->InsertString(1, "S:班");
		pCB->InsertString(2, "D:天");
		pCB->InsertString(3, "W:周");
		pCB->InsertString(4, "M:月");
		pCB->InsertString(5, "Y:年");

		pCB->SetCurSel(0);
	}

	pCB = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICE_CHECK_METHOD);
	if (NULL != pCB)
	{
		pCB->InsertString(0, "观察");
		pCB->InsertString(1, "测定");
		pCB->InsertString(2, "触摸");
		pCB->InsertString(3, "打诊");
		pCB->InsertString(4, "耳听");
		pCB->InsertString(5, "红外");
		pCB->InsertString(6, "超声波");
		pCB->InsertString(7, "其他");

		pCB->SetCurSel(0);
	}

	pCB = (CComboBox*)GetDlgItem(IDC_COMB_DEVICE_WORKORDER_TYPE);
	if (NULL != pCB)
	{
		pCB->InsertString(0, "立即维修");
		pCB->InsertString(1, "当天解决");
		pCB->InsertString(2, "保养计划");

		pCB->SetCurSel(0);
	}

}

void CDlgDeviceDetail::SetDeviceInfo(Device * pDevice)
{
	if (NULL == pDevice)
	{
		return;
	}

	m_pDevice = pDevice;
}

void CDlgDeviceDetail::UpdateDeviceInfo(bool bGet)
{
	if (bGet)
	{
		GetDlgItem(IDC_EDIT_DEVICE_NAME)->GetWindowText(m_pDevice->csDeviceName);
		GetDlgItem(IDC_EDIT_DEVICE_PARTS)->GetWindowText(m_pDevice->csAffiliatedParts);
		GetDlgItem(IDC_EDIT_DEVICE_DEPARTMENT)->GetWindowText(m_pDevice->csUseDepartment);
		GetDlgItem(IDC_EDIT_DEVICE_MODEL)->GetWindowText(m_pDevice->csDeviceModel);
		GetDlgItem(IDC_EDIT_APPEARANCE_DATE)->GetWindowText(m_pDevice->csAppearanceDate);
		GetDlgItem(IDC_EDIT_APPEARANCE_NUM)->GetWindowText(m_pDevice->csAppearanceNumber);
		GetDlgItem(IDC_COMBO_DEVICE_TYPE)->GetWindowText(m_pDevice->csDeviceType);
		GetDlgItem(IDC_COMBO_DEVICE_INPORTANCE)->GetWindowText(m_pDevice->csImportance);
		GetDlgItem(IDC_EDIT_DEVICE_OPERATOR)->GetWindowText(m_pDevice->csOperator);
		GetDlgItem(IDC_EDIT_DEVICE_ENABLE_DATE)->GetWindowText(m_pDevice->csEnableData);
		GetDlgItem(IDC_COMBO_DEVICE_STATUE)->GetWindowText(m_pDevice->csDeviceStatue);
		GetDlgItem(IDC_EDIT_DEVICE_INSTALL_LOCATION)->GetWindowText(m_pDevice->csInstallLocation);
		GetDlgItem(IDC_EDIT_DEVICE_CHECK_ITEM)->GetWindowText(m_pDevice->csCheckItem);
		GetDlgItem(IDC_COMBO_DEVICE_CHECK_CYCLE)->GetWindowText(m_pDevice->csCheckCycle);
		GetDlgItem(IDC_COMBO_DEVICE_CHECK_METHOD)->GetWindowText(m_pDevice->csCheckMethod);
		GetDlgItem(IDC_EDIT_DEVICE_CHECK_POINT)->GetWindowText(m_pDevice->csCheckPoint);
		GetDlgItem(IDC_EDIT_DEVICE_CHECK_TOOL)->GetWindowText(m_pDevice->csCheckTool);
		GetDlgItem(IDC_COMB_DEVICE_WORKORDER_TYPE)->GetWindowText(m_pDevice->csWorkOrderType);
		GetDlgItem(IDC_EDIT_DEVICE_STANDER_NUMBER)->GetWindowText(m_pDevice->csStandardNumber);
		GetDlgItem(IDC_EDIT_DEVICE_APPORVER)->GetWindowText(m_pDevice->csApporver);
		GetDlgItem(IDC_EDIT_DEVICE_AUDITOR)->GetWindowText(m_pDevice->csAuditor);
		GetDlgItem(IDC_EDIT_DEVICE_EDITOR)->GetWindowText(m_pDevice->strEditor);
		GetDlgItem(IDC_EDIT_DEVICE_REMARK)->GetWindowText(m_pDevice->csRemarks);
	}
	else
	{
		GetDlgItem(IDC_EDIT_DEVICE_NAME)->SetWindowText(m_pDevice->csDeviceName);
		GetDlgItem(IDC_EDIT_DEVICE_PARTS)->SetWindowText(m_pDevice->csAffiliatedParts);
		GetDlgItem(IDC_EDIT_DEVICE_DEPARTMENT)->SetWindowText(m_pDevice->csUseDepartment);
		GetDlgItem(IDC_EDIT_DEVICE_MODEL)->SetWindowText(m_pDevice->csDeviceModel);
		GetDlgItem(IDC_EDIT_APPEARANCE_DATE)->SetWindowText(m_pDevice->csAppearanceDate);
		GetDlgItem(IDC_EDIT_APPEARANCE_NUM)->SetWindowText(m_pDevice->csAppearanceNumber);
		SelectComboBox(GetDlgItem(IDC_COMBO_DEVICE_TYPE), m_pDevice->csDeviceType);
		SelectComboBox(GetDlgItem(IDC_COMBO_DEVICE_INPORTANCE), m_pDevice->csImportance);
		GetDlgItem(IDC_EDIT_DEVICE_OPERATOR)->SetWindowText(m_pDevice->csOperator);
		GetDlgItem(IDC_EDIT_DEVICE_ENABLE_DATE)->SetWindowText(m_pDevice->csEnableData);
		SelectComboBox(GetDlgItem(IDC_COMBO_DEVICE_STATUE), m_pDevice->csDeviceStatue);
		GetDlgItem(IDC_EDIT_DEVICE_INSTALL_LOCATION)->SetWindowText(m_pDevice->csInstallLocation);
		GetDlgItem(IDC_EDIT_DEVICE_CHECK_ITEM)->SetWindowText(m_pDevice->csCheckItem);
		SelectComboBox(GetDlgItem(IDC_COMBO_DEVICE_CHECK_CYCLE), m_pDevice->csCheckCycle);
		SelectComboBox(GetDlgItem(IDC_COMBO_DEVICE_CHECK_METHOD), m_pDevice->csCheckMethod);
		GetDlgItem(IDC_EDIT_DEVICE_CHECK_POINT)->SetWindowText(m_pDevice->csCheckPoint);
		GetDlgItem(IDC_EDIT_DEVICE_CHECK_TOOL)->SetWindowText(m_pDevice->csCheckTool);
		SelectComboBox(GetDlgItem(IDC_COMB_DEVICE_WORKORDER_TYPE), m_pDevice->csWorkOrderType);
		GetDlgItem(IDC_EDIT_DEVICE_STANDER_NUMBER)->SetWindowText(m_pDevice->csStandardNumber);
		GetDlgItem(IDC_EDIT_DEVICE_APPORVER)->SetWindowText(m_pDevice->csApporver);
		GetDlgItem(IDC_EDIT_DEVICE_AUDITOR)->SetWindowText(m_pDevice->csAuditor);
		GetDlgItem(IDC_EDIT_DEVICE_EDITOR)->SetWindowText(m_pDevice->strEditor);
		GetDlgItem(IDC_EDIT_DEVICE_REMARK)->SetWindowText(m_pDevice->csRemarks);
	}
}

Device * CDlgDeviceDetail::GetDeviceInfo()
{
	return m_pDevice;
}

void CDlgDeviceDetail::OnOK()
{
	UpdateDeviceInfo(true);
	__super::OnOK();
}

int CDlgDeviceDetail::SelectComboBox(CWnd * pComboBoxWnd, const CString & strText)
{
	if (NULL == pComboBoxWnd)
	{
		return -1;
	}

	CComboBox * pComboBox = (CComboBox *)pComboBoxWnd;
	if (NULL == pComboBox)
	{
		return -1;
	}

	int nCount = pComboBox->GetCount();
	for (int n = 0; n < nCount; ++n)
	{
		CString csText;
		pComboBox->GetLBText(n, csText);
		if (csText == strText)
		{
			pComboBox->SetCurSel(n);
			return 0;
		}
	}

	return 0;
}
