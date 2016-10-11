
// 2013253063_HW3View.cpp : CMy2013253063_HW3View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "2013253063_HW3.h"
#endif

#include "MainFrm.h"
#include "ChildFrm.h"
#include "2013253063_HW3Doc.h"
#include "2013253063_HW3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2013253063_HW3View

IMPLEMENT_DYNCREATE(CMy2013253063_HW3View, CView)

BEGIN_MESSAGE_MAP(CMy2013253063_HW3View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_COPY, &CMy2013253063_HW3View::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CMy2013253063_HW3View::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CMy2013253063_HW3View::OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_HISTOGRAM, &CMy2013253063_HW3View::OnUpdateHistogram)
	ON_COMMAND(ID_HISTOGRAM, &CMy2013253063_HW3View::OnHistogram)
	ON_COMMAND(ID_PREDICTION_X, &CMy2013253063_HW3View::OnPrediction1)
	ON_COMMAND(ID_PREDICTION_X32776, &CMy2013253063_HW3View::OnPrediction2)
	ON_COMMAND(ID_PREDICTION_X32777, &CMy2013253063_HW3View::OnPrediction3)
	ON_COMMAND(ID_PREDICTION_X32778, &CMy2013253063_HW3View::OnPrediction4)
	ON_COMMAND(ID_PREDICTION_ADAPTIVEPREDICTION, &CMy2013253063_HW3View::OnAdaptiveprediction)
	ON_UPDATE_COMMAND_UI(ID_PREDICTION_X, &CMy2013253063_HW3View::OnUpdatePrediction1)
	ON_UPDATE_COMMAND_UI(ID_PREDICTION_X32776, &CMy2013253063_HW3View::OnUpdatePrediction2)
	ON_UPDATE_COMMAND_UI(ID_PREDICTION_X32777, &CMy2013253063_HW3View::OnUpdatePrediction3)
	ON_UPDATE_COMMAND_UI(ID_PREDICTION_X32778, &CMy2013253063_HW3View::OnUpdatePrediction4)
	ON_UPDATE_COMMAND_UI(ID_PREDICTION_ADAPTIVEPREDICTION, &CMy2013253063_HW3View::OnUpdateAdaptiveprediction)
END_MESSAGE_MAP()

// CMy2013253063_HW3View 생성/소멸

CMy2013253063_HW3View::CMy2013253063_HW3View()
: BmInfo(NULL)
, height(0)
, width(0)
, rwsize(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy2013253063_HW3View::~CMy2013253063_HW3View()
{
}

BOOL CMy2013253063_HW3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy2013253063_HW3View 그리기

void CMy2013253063_HW3View::OnDraw(CDC* pDC)
{
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (pDoc->m_InImg == NULL) return;

	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height, 0, 0, 0, height, pDoc->m_InImg, BmInfo, DIB_RGB_COLORS);
	
	if (pDoc->mode_flag == 1){
		CPen pen(PS_SOLID, 1, RGB(200, 0, 200));
		pDC->SelectObject(&pen);
		pDC->MoveTo(20, 280);
		pDC->LineTo(20, 8);
		pDC->MoveTo(5, 264);
		pDC->LineTo(275, 264);
		pDC->MoveTo(275, 258);
		pDC->LineTo(275, 270);

		pDC->SetTextColor(RGB(200, 0, 200));

		CString str;
		str.Format(_T("0"));
		pDC->TextOutW(5, 255, str);
		pDC->TextOutW(17, 270, str);
		str.Format(_T("255"));
		pDC->TextOutW(266, 268, str);
		str.Format(_T("%d"), pDoc->histo_axis_y);
		pDC->TextOutW(0, 0, str);
		pDC->SetTextColor(RGB(255, 0, 0));
		str.Format(_T("Entropy = %.2lf"), (pDoc->entropy));
		pDC->TextOutW(200, 15, str);
		str.Format(_T("MAX = %d"), pDoc->histo_max_value_y);
		pDC->TextOutW(200, 0, str);
	}
	else if(pDoc->mode_flag == 3){
		CPen pen(PS_SOLID, 1, RGB(200, 0, 200));
		pDC->SelectObject(&pen);
		pDC->MoveTo(20, 280);
		pDC->LineTo(20, 8);
		pDC->MoveTo(5, 264);
		pDC->LineTo(530, 264);
		pDC->MoveTo(275, 258);
		pDC->LineTo(275, 270);
		pDC->MoveTo(530, 258);
		pDC->LineTo(530, 270);

		pDC->SetTextColor(RGB(200, 0, 200));

		CString str;
		str.Format(_T("0"));
		pDC->TextOutW(5, 255, str);
		str.Format(_T("-255"));
		pDC->TextOutW(12, 270, str);
		str.Format(_T("0"));
		pDC->TextOutW(271, 268, str);
		str.Format(_T("255"));
		pDC->TextOutW(520, 268, str);
		str.Format(_T("%d"), pDoc->histo_axis_y);
		pDC->TextOutW(0, 0, str);
		pDC->SetTextColor(RGB(255, 0, 0));
		str.Format(_T("Entropy = %.2lf"), (pDoc->entropy));
		pDC->TextOutW(456, 15, str);
		str.Format(_T("MAX = %d"), pDoc->histo_max_value_y);
		pDC->TextOutW(456, 0, str);
	}
}


// CMy2013253063_HW3View 인쇄

BOOL CMy2013253063_HW3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy2013253063_HW3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy2013253063_HW3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy2013253063_HW3View 진단

#ifdef _DEBUG
void CMy2013253063_HW3View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2013253063_HW3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2013253063_HW3Doc* CMy2013253063_HW3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2013253063_HW3Doc)));
	return (CMy2013253063_HW3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2013253063_HW3View 메시지 처리기


void CMy2013253063_HW3View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	height = pDoc->height;
	width = pDoc->width;

	// 창크기를 영상의 크기에 맞추기 위함
	GetParentFrame()->ActivateFrame();

	// bmp 헤더 정보 입력
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+256 * sizeof(RGBQUAD));
	BmInfo->bmiHeader.biBitCount = 8;
	rwsize = WIDTHBYTES(BmInfo->bmiHeader.biBitCount * width);
	BmInfo->bmiHeader.biClrImportant = 256;
	BmInfo->bmiHeader.biClrUsed = 256;
	BmInfo->bmiHeader.biCompression = 0;
	BmInfo->bmiHeader.biHeight = height;
	BmInfo->bmiHeader.biPlanes = 1;
	BmInfo->bmiHeader.biSize = 40;
	BmInfo->bmiHeader.biSizeImage = rwsize*height;
	BmInfo->bmiHeader.biWidth = width;
	BmInfo->bmiHeader.biXPelsPerMeter = 0;
	BmInfo->bmiHeader.biYPelsPerMeter = 0;


	for (int i = 0; i<256; i++){
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}
}


void CMy2013253063_HW3View::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->CopyClipboard(pDoc->m_InImg, height, width, 8);
}


void CMy2013253063_HW3View::OnEditPaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

	CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 

	CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
	pDoc2->mode_flag = pDoc->mode_flag;
	pDoc2->histo_axis_y = pDoc->histo_axis_y;
	pDoc2->histo_max_value_y = pDoc->histo_max_value_y;
	pDoc2->entropy = pDoc->entropy;
}


void CMy2013253063_HW3View::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_DIB));
}

void CMy2013253063_HW3View::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->mode_flag == 0){
		pDoc->m_ImgHisto(height, width);
		pDoc->CopyClipboard(pDoc->m_OutImg, 300, 300, 8);
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

		CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

		CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 

		CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
		pDoc2->mode_flag = 1;
		pDoc2->histo_axis_y = pDoc->histo_axis_y;
		pDoc2->histo_max_value_y = pDoc->histo_max_value_y;
		pDoc2->entropy = pDoc->entropy;
	}

	else if (pDoc->mode_flag == 2){
		pDoc->m_errorHisto(height, width);
		pDoc->CopyClipboard(pDoc->m_OutImg, 300, 556, 8);
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

		CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

		CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 
		                                                                                   
		CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
		pDoc2->mode_flag = 3;
		pDoc2->histo_axis_y = pDoc->histo_axis_y;
		pDoc2->histo_max_value_y = pDoc->histo_max_value_y;
		pDoc2->entropy = pDoc->entropy;
	}
	
}

// 1. X = A
void CMy2013253063_HW3View::OnPrediction1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_ImgPrediction1(height, width);
	pDoc->CopyClipboard(pDoc->m_OutImg, height, width, 8);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

	CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 
	                                                                                   
	CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
	pDoc2->mode_flag = 2;
	pDoc2->m_error = pDoc->m_error;
}


// 2. X = (1/2)*A + (1/2)*B
void CMy2013253063_HW3View::OnPrediction2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_ImgPrediction2(height, width);
	pDoc->CopyClipboard(pDoc->m_OutImg, height, width, 8);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

	CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 

	CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
	pDoc2->mode_flag = 2;
	pDoc2->m_error = pDoc->m_error;
}


// 3. X = A - B + C
void CMy2013253063_HW3View::OnPrediction3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_ImgPrediction3(height, width);
	pDoc->CopyClipboard(pDoc->m_OutImg, height, width, 8);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

	CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 

	CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
	pDoc2->mode_flag = 2;
	pDoc2->m_error = pDoc->m_error;
}


// 4. X = 0.75*A - 0.5*B + 0.75*C
void CMy2013253063_HW3View::OnPrediction4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_ImgPrediction4(height, width);
	pDoc->CopyClipboard(pDoc->m_OutImg, height, width, 8);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

	CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 

	CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
	pDoc2->mode_flag = 2;
	pDoc2->m_error = pDoc->m_error;
}

// 5. Adaptive Prediction
void CMy2013253063_HW3View::OnAdaptiveprediction()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_ImgAdaptPrediction(height, width);
	pDoc->CopyClipboard(pDoc->m_OutImg, height, width, 8);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd);                      // MainFrame구함 (AfxGetApp()라는 전역함수를 이용하였다.)

	CChildFrame *pChildFrm = (CChildFrame*)pMainFrm->MDIGetActive();                    // Active된 ChildFrame 구함. 

	CMy2013253063_HW3Doc *pDoc2 = (CMy2013253063_HW3Doc *)(pChildFrm->GetActiveDocument());
	pDoc2->mode_flag = 2;
	pDoc2->m_error = pDoc->m_error;
}

void CMy2013253063_HW3View::OnUpdateHistogram(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->mode_flag == 1 || pDoc->mode_flag == 3){
		pCmdUI->Enable(FALSE);
	}
}

void CMy2013253063_HW3View::OnUpdatePrediction1(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->mode_flag == 1 || pDoc->mode_flag == 3){
		pCmdUI->Enable(FALSE);
	}
}


void CMy2013253063_HW3View::OnUpdatePrediction2(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->mode_flag == 1 || pDoc->mode_flag == 3){
		pCmdUI->Enable(FALSE);
	}
}


void CMy2013253063_HW3View::OnUpdatePrediction3(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->mode_flag == 1 || pDoc->mode_flag == 3){
		pCmdUI->Enable(FALSE);
	}
}


void CMy2013253063_HW3View::OnUpdatePrediction4(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->mode_flag == 1 || pDoc->mode_flag == 3){
		pCmdUI->Enable(FALSE);
	}
}


void CMy2013253063_HW3View::OnUpdateAdaptiveprediction(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CMy2013253063_HW3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->mode_flag == 1 || pDoc->mode_flag == 3){
		pCmdUI->Enable(FALSE);
	}
}
