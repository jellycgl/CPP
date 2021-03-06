
// DeviceManageSystemView.cpp : CDeviceManageSystemView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DeviceManageSystem.h"
#endif

#include "DeviceManageSystemDoc.h"
#include "DeviceManageSystemView.h"
#include "MsgId.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDeviceManageSystemView

IMPLEMENT_DYNCREATE(CDeviceManageSystemView, CView)

BEGIN_MESSAGE_MAP(CDeviceManageSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDeviceManageSystemView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_MESSAGE(WM_TREE_CLICK, OnUpdateDepartment)
END_MESSAGE_MAP()

// CDeviceManageSystemView 构造/析构

CDeviceManageSystemView::CDeviceManageSystemView()
	: m_pDepartView(NULL)
{
}

CDeviceManageSystemView::~CDeviceManageSystemView()
{
	DestroyDepartmentView();
}

BOOL CDeviceManageSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

void CDeviceManageSystemView::OnInitialUpdate()
{
	__super::OnInitialUpdate();

	InitDepartmentView();
}

// CDeviceManageSystemView 绘制

void CDeviceManageSystemView::OnDraw(CDC* /*pDC*/)
{
}


// CDeviceManageSystemView 打印


void CDeviceManageSystemView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDeviceManageSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDeviceManageSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CDeviceManageSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CDeviceManageSystemView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDeviceManageSystemView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDeviceManageSystemView 诊断

#ifdef _DEBUG
void CDeviceManageSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CDeviceManageSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG


// CDeviceManageSystemView 消息处理程序


void CDeviceManageSystemView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	MoveDepartmentView();
}

bool CDeviceManageSystemView::CreateDepartmentView()
{
	if (NULL == m_pDepartView)
	{
		m_pDepartView = new CDlgDepartment(this);
	}

	bool bSuccess = m_pDepartView->Create(IDD_DIALOG_DEPARTMENT, this) ? true : false;
	if (bSuccess)
	{
		m_pDepartView->ShowWindow(SW_SHOW);
	}

	return bSuccess;
}

void CDeviceManageSystemView::InitDepartmentView()
{
	if (NULL == m_pDepartView || NULL == m_pDepartView->GetSafeHwnd())
	{
		return;
	}

	m_pDepartView->InitControl();
}

void CDeviceManageSystemView::MoveDepartmentView()
{
	if (NULL == m_pDepartView ||
		NULL == m_pDepartView->GetSafeHwnd())
	{
		return;
	}

	CRect rectClient;
	GetClientRect(&rectClient);

	m_pDepartView->MoveWindow(&rectClient);
}

void CDeviceManageSystemView::DestroyDepartmentView()
{
	if (NULL != m_pDepartView)
	{
		if (NULL != m_pDepartView->GetSafeHwnd())
		{
			m_pDepartView->DestroyWindow();
		}

		delete m_pDepartView;
		m_pDepartView = NULL;
	}
}


int CDeviceManageSystemView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (!CreateDepartmentView())
	{
		return -1;
	}

	return 0;
}

LRESULT CDeviceManageSystemView::OnUpdateDepartment(WPARAM wParam, LPARAM lParam)
{
	CString * pFileName = (CString *)wParam;
	if (NULL == pFileName)
	{
		return -1;
	}

	if (NULL == m_pDepartView)
	{
		CreateDepartmentView();
	}

	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);

	CString strFullPath;
	strFullPath.Format("%s\\Data\\%s.dvi", path, *pFileName);
	m_pDepartView->SetFile(strFullPath);
	m_pDepartView->RefreshData();

	return 0;
}
