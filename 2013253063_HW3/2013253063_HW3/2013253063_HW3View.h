
// 2013253063_HW3View.h : CMy2013253063_HW3View 클래스의 인터페이스
//

#pragma once


class CMy2013253063_HW3View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy2013253063_HW3View();
	DECLARE_DYNCREATE(CMy2013253063_HW3View)

// 특성입니다.
public:
	CMy2013253063_HW3Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy2013253063_HW3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:

	BITMAPINFO* BmInfo;
	int height;
	int width;
	int rwsize;
	virtual void OnInitialUpdate();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHistogram(CCmdUI *pCmdUI);
	afx_msg void OnHistogram();
	afx_msg void OnPrediction1();
	afx_msg void OnPrediction2();
	afx_msg void OnPrediction3();
	afx_msg void OnPrediction4();
	afx_msg void OnAdaptiveprediction();
	afx_msg void OnUpdatePrediction1(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrediction2(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrediction3(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrediction4(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAdaptiveprediction(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // 2013253063_HW3View.cpp의 디버그 버전
inline CMy2013253063_HW3Doc* CMy2013253063_HW3View::GetDocument() const
   { return reinterpret_cast<CMy2013253063_HW3Doc*>(m_pDocument); }
#endif

