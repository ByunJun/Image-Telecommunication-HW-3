
// 2013253063_HW3View.h : CMy2013253063_HW3View Ŭ������ �������̽�
//

#pragma once


class CMy2013253063_HW3View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy2013253063_HW3View();
	DECLARE_DYNCREATE(CMy2013253063_HW3View)

// Ư���Դϴ�.
public:
	CMy2013253063_HW3Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy2013253063_HW3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // 2013253063_HW3View.cpp�� ����� ����
inline CMy2013253063_HW3Doc* CMy2013253063_HW3View::GetDocument() const
   { return reinterpret_cast<CMy2013253063_HW3Doc*>(m_pDocument); }
#endif

