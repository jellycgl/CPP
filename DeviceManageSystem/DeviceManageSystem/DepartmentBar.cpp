
#include "stdafx.h"
#include "mainfrm.h"
#include "Resource.h"
#include "DepartmentBar.h"
#include "DeviceManageSystem.h"
#include "MsgId.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CDepartmentBar::CDepartmentBar()
{
}

CDepartmentBar::~CDepartmentBar()
{
}

BEGIN_MESSAGE_MAP(CDepartmentBar, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_MESSAGE(WM_TREE_CLICK, OnClickTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CDepartmentBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		return -1;
	}

	// 加载视图图像: 
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	m_wndToolBar.SetWindowText("部门");
	SetWindowText("部门");

	InitDepartmentData();
	AdjustLayout();

	return 0;
}

void CDepartmentBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CDepartmentBar::InitDepartmentData()
{
	HTREEITEM hWorkshop1 = m_wndFileView.InsertItem(_T("加工一车间"), 0, 0, NULL);

	m_wndFileView.InsertItem(_T("9#结晶器搅拌"), 1, 1, hWorkshop1);
	m_wndFileView.InsertItem(_T("12#离心机"), 1, 1, hWorkshop1);

	HTREEITEM hWorkshop2 = m_wndFileView.InsertItem(_T("加工二车间"), 0, 0, NULL);

	m_wndFileView.InsertItem(_T("振动筛"), 2, 2, hWorkshop2);
	m_wndFileView.InsertItem(_T("B系列水平带机"), 2, 2, hWorkshop2);

	HTREEITEM hWorkshop3 = m_wndFileView.InsertItem(_T("加工三车间"), 0, 0, NULL);

	m_wndFileView.InsertItem(_T("粗选浮选机"), 2, 2, hWorkshop3);
	m_wndFileView.InsertItem(_T("搅拌槽"), 2, 2, hWorkshop3);

	HTREEITEM hPosition1 = m_wndFileView.InsertItem(_T("采收车间"), 0, 0);
	m_wndFileView.SetItemState(hPosition1, TVIS_BOLD, TVIS_BOLD);
	m_wndFileView.InsertItem(_T("9#履带式浮动采收机"), 2, 2, hPosition1);
	m_wndFileView.InsertItem(_T("11#履带式浮动采收机岸基增压泵"), 2, 2, hPosition1);

	HTREEITEM hPosition2 = m_wndFileView.InsertItem(_T("干包车间"), 0, 0);
	m_wndFileView.SetItemState(hPosition2, TVIS_BOLD, TVIS_BOLD);
	m_wndFileView.InsertItem(_T("5#包装线"), 2, 2, hPosition2);
	m_wndFileView.InsertItem(_T("1#空压机"), 2, 2, hPosition2);

	HTREEITEM hPosition3 = m_wndFileView.InsertItem(_T("动力车间"), 0, 0);
	m_wndFileView.SetItemState(hPosition3, TVIS_BOLD, TVIS_BOLD);
	m_wndFileView.InsertItem(_T("清水泵"), 2, 2, hPosition3);
	m_wndFileView.InsertItem(_T("智能自吸泵"), 2, 2, hPosition3);

	HTREEITEM hPosition4 = m_wndFileView.InsertItem(_T("盐田管理部"), 0, 0);
	m_wndFileView.SetItemState(hPosition3, TVIS_BOLD, TVIS_BOLD);
	m_wndFileView.InsertItem(_T("混流泵500"), 2, 2, hPosition4);
	m_wndFileView.InsertItem(_T("混流泵700点"), 2, 2, hPosition4);

	m_wndFileView.Expand(hWorkshop1, TVE_EXPAND);
	m_wndFileView.Expand(hWorkshop2, TVE_EXPAND);
	m_wndFileView.Expand(hWorkshop3, TVE_EXPAND);
	m_wndFileView.Expand(hPosition1, TVE_EXPAND);
	m_wndFileView.Expand(hPosition2, TVE_EXPAND);
	m_wndFileView.Expand(hPosition3, TVE_EXPAND);
	m_wndFileView.Expand(hPosition4, TVE_EXPAND);
}

void CDepartmentBar::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CDepartmentBar::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDepartmentBar::OnProperties()
{
	AfxMessageBox(_T("属性...."));

}

void CDepartmentBar::OnFileOpen()
{
	// TODO:  在此处添加命令处理程序代码
}

void CDepartmentBar::OnFileOpenWith()
{
	// TODO:  在此处添加命令处理程序代码
}

void CDepartmentBar::OnDummyCompile()
{
	// TODO:  在此处添加命令处理程序代码
}

void CDepartmentBar::OnEditCut()
{
	// TODO:  在此处添加命令处理程序代码
}

void CDepartmentBar::OnEditCopy()
{
	// TODO:  在此处添加命令处理程序代码
}

void CDepartmentBar::OnEditClear()
{
	// TODO:  在此处添加命令处理程序代码
}

void CDepartmentBar::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CDepartmentBar::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CDepartmentBar::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定*/);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图:  %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

LRESULT CDepartmentBar::OnClickTree(WPARAM wParam, LPARAM lParam)
{
	if (NULL == m_wndFileView.GetSafeHwnd())
	{
		return -1;
	}

	HTREEITEM hSelItem = m_wndFileView.GetCurrentTreeItem();
	if (NULL == -1)
	{
		return -1;
	}

	CString csName = m_wndFileView.GetItemText(hSelItem);

	CMainFrame * pMainFrame = (CMainFrame *)AfxGetMainWnd();
	if (NULL == pMainFrame)
	{
		return -1;
	}
	CView * pView = pMainFrame->GetActiveView();
	if (NULL == pView)
	{
		return -1;
	}

	::SendMessage(pView->GetSafeHwnd(), WM_TREE_CLICK, (WPARAM)&csName, NULL);

	return 0;
}


