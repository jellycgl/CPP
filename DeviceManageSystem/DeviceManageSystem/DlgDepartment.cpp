#include "stdafx.h"
#include "DeviceManageSystem.h"
#include "DlgDepartment.h"
#include "afxdialogex.h"
#include "DlgDeviceDetail.h"
#include "DeviceManager.h"

IMPLEMENT_DYNAMIC(CDlgDepartment, CDialogEx)

CDlgDepartment::CDlgDepartment(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDepartment::IDD, pParent)
	, m_csFile("")
{
}

CDlgDepartment::~CDlgDepartment()
{
}

void CDlgDepartment::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_listInfo);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnNew);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
}

BEGIN_MESSAGE_MAP(CDlgDepartment, CDialogEx)
	//ON_WM_PAINT()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CDlgDepartment::OnNMDblclkList)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CDlgDepartment::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CDlgDepartment::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgDepartment::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDlgDepartment::OnBnClickedButtonSave)
END_MESSAGE_MAP()

void CDlgDepartment::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	MoveControl();
}

void CDlgDepartment::OnPaint()
{
	//CPaintDC dc(this);

	//CRect rectClient;
	//GetClientRect(&rectClient);

	//CBrush br(RGB(255, 0, 0));
	//dc.FillRect(rectClient, &br);
}

void CDlgDepartment::InsertInfo(Device * pDevice)
{
	if (NULL == pDevice || NULL == m_listInfo.GetSafeHwnd())
	{
		return;
	}

	int nIndex = m_listInfo.GetItemCount();
	m_listInfo.InsertItem(nIndex, "");

	CString strNum;
	strNum.Format(_T("%d"), nIndex + 1);
	m_listInfo.SetItemText(nIndex, 0, strNum);
	m_listInfo.SetItemText(nIndex, 1, pDevice->csDeviceName);
	m_listInfo.SetItemText(nIndex, 2, pDevice->csAffiliatedParts);
	m_listInfo.SetItemText(nIndex, 3, pDevice->csUseDepartment);
	m_listInfo.SetItemText(nIndex, 4, pDevice->csDeviceModel);
	m_listInfo.SetItemText(nIndex, 5, pDevice->csDeviceType);
	m_listInfo.SetItemText(nIndex, 6, pDevice->csDeviceStatue);
	m_listInfo.SetItemText(nIndex, 7, pDevice->csInstallLocation);
	m_listInfo.SetItemText(nIndex, 8, pDevice->csCheckItem);
	m_listInfo.SetItemData(nIndex, (DWORD_PTR)pDevice);
}

void CDlgDepartment::RefreshData()
{
	m_listInfo.DeleteAllItems();

	list<Device*> lsDevs;
	CDeviceManager::Instance()->GetDeviceByFile(m_csFile, lsDevs);
	if (0 == lsDevs.size())
	{
		return;
	}

	Device * pDevice = NULL;
	list<Device*>::iterator iterBegin = lsDevs.begin();
	list<Device*>::iterator iterEnd = lsDevs.end();
	for (; iterBegin != iterEnd; ++iterBegin)
	{
		pDevice = *iterBegin;
		if (NULL == pDevice)
		{
			continue;
		}
		InsertInfo(pDevice);
	}
}

void CDlgDepartment::InitControl()
{
	if (NULL != m_listInfo.GetSafeHwnd())
	{
		DWORD dwStyle = m_listInfo.GetExtendedStyle();
		dwStyle |= LVS_EX_GRIDLINES;
		dwStyle |= LVS_EX_FULLROWSELECT;
		m_listInfo.SetExtendedStyle(dwStyle);

		m_listInfo.InsertColumn(0, "序号", LVCFMT_CENTER, 50);
		m_listInfo.InsertColumn(1, "零件名称", LVCFMT_CENTER, 100);
		m_listInfo.InsertColumn(2, "所属部件", LVCFMT_CENTER, 100);
		m_listInfo.InsertColumn(3, "使用单位", LVCFMT_CENTER, 100);
		m_listInfo.InsertColumn(4, "型号规格", LVCFMT_CENTER, 100);
		m_listInfo.InsertColumn(5, "零件类别", LVCFMT_CENTER, 100);
		m_listInfo.InsertColumn(6, "设备状态", LVCFMT_CENTER, 100);
		m_listInfo.InsertColumn(7, "安装地点", LVCFMT_CENTER, 100);
		m_listInfo.InsertColumn(8, "点检项目", LVCFMT_CENTER, 100);

		RefreshData();
	}
}

void CDlgDepartment::MoveControl()
{
	if (NULL == GetSafeHwnd()||
		NULL == m_listInfo.GetSafeHwnd())
	{
		return;
	}

	CRect rectClient;
	GetClientRect(&rectClient);

	CRect rectButton;
	rectButton.right = rectClient.right - 25;
	rectButton.bottom = rectClient.bottom - 15;
	rectButton.left = rectButton.right - 75;
	rectButton.top = rectButton.bottom - 20;
	m_btnSave.MoveWindow(rectButton);

	rectButton.right = rectButton.left - 10;
	rectButton.left = rectButton.right - 75;
	m_btnDelete.MoveWindow(rectButton);

	rectButton.right = rectButton.left - 10;
	rectButton.left = rectButton.right - 75;
	m_btnOpen.MoveWindow(rectButton);

	rectButton.right = rectButton.left - 10;
	rectButton.left = rectButton.right - 75;
	m_btnNew.MoveWindow(rectButton);

	CRect rectList;
	rectList.left = rectClient.left + 25;;
	rectList.top = rectClient.top + 25;
	rectList.right = rectClient.right - 25;
	rectList.bottom = rectButton.top - 10;
	m_listInfo.MoveWindow(rectList);
}



void CDlgDepartment::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (-1 == pNMItemActivate->iItem)
	{
		*pResult = 0;
		return;
	}

	OnBnClickedButtonOpen();

	*pResult = 0;
}


void CDlgDepartment::OnBnClickedButtonNew()
{
	CDlgDeviceDetail ddd;
	if (IDOK != ddd.DoModal())
	{
		return;
	}

	Device * pDevice = ddd.GetDeviceInfo();
	if ( NULL == pDevice )
	{
		return;
	}

	CDeviceManager::Instance()->AddOneDevice(m_csFile, pDevice);
	
	RefreshData();
}


void CDlgDepartment::OnBnClickedButtonOpen()
{
	if (NULL == m_listInfo.GetSafeHwnd())
	{
		return;
	}

	int nSel = m_listInfo.GetSelectionMark();
	if (-1 == nSel)
	{
		MessageBox("您未选中任何信息");
		return;
	}

	Device * pDevice = (Device *)m_listInfo.GetItemData(nSel);
	if (NULL == pDevice)
	{
		return;
	}

	CDlgDeviceDetail ddd;
	ddd.SetDeviceInfo(pDevice);
	if (IDOK != ddd.DoModal())
	{
		return;
	}
	
	Device * pDev = ddd.GetDeviceInfo();
	if (NULL == pDev)
	{
		return;
	}

	CDeviceManager::Instance()->UpdateOnDevice(m_csFile, pDev);

	RefreshData();
}


void CDlgDepartment::OnBnClickedButtonDelete()
{
	if (NULL == m_listInfo.GetSafeHwnd())
	{
		return;
	}

	int nSel = m_listInfo.GetSelectionMark();
	if (-1 == nSel )
	{
		MessageBox("您未选中任何信息");
		return;
	}

	if (IDOK != MessageBox("您确定要删除这条信息？", "确认提示", MB_OKCANCEL))
	{
		return;
	}

	Device * pDevice = (Device *)m_listInfo.GetItemData(nSel);
	if (NULL == pDevice)
	{
		return;
	}

	CDeviceManager::Instance()->DeleteOneDevice(m_csFile, pDevice);

	RefreshData();
}


void CDlgDepartment::OnBnClickedButtonSave()
{
	CDeviceManager::Instance()->SaveAllDevice();
}
