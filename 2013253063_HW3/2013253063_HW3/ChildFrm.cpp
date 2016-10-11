
// ChildFrm.cpp : CChildFrame Ŭ������ ����
//

#include "stdafx.h"
#include "2013253063_HW3.h"
#include "2013253063_HW3Doc.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

// CChildFrame ����/�Ҹ�

CChildFrame::CChildFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ����

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame �޽��� ó����


void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CRect rect, rectC;
	GetWindowRect(&rect); GetClientRect(&rectC);

	CSize sizeImg;

	sizeImg.cx = ((CMy2013253063_HW3Doc*)GetActiveDocument())->width;
	sizeImg.cy = ((CMy2013253063_HW3Doc*)GetActiveDocument())->height;
	int cx = sizeImg.cx + rect.Width() - rectC.Width() + 4;
	int cy = sizeImg.cy + rect.Height() - rectC.Height() +4;
	width = cx;
	height = cy;
	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_SHOWWINDOW);

	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CChildFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	lpMMI->ptMinTrackSize.x = width;
	lpMMI->ptMaxTrackSize.x = width;
	lpMMI->ptMinTrackSize.y = height;
	lpMMI->ptMaxTrackSize.y = height;

	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);
}
