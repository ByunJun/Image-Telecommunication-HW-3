
// 2013253063_HW3Doc.h : CMy2013253063_HW3Doc 클래스의 인터페이스
//


#pragma once
#define WIDTHBYTES(bits) (((bits)+31)/32*4) // 4바이트의 배수여야 함

class CMy2013253063_HW3Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMy2013253063_HW3Doc();
	DECLARE_DYNCREATE(CMy2013253063_HW3Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMy2013253063_HW3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	CString extension;
	RGBQUAD palRGB[256];
	unsigned char*m_InImg;
	unsigned char*m_OutImg;
	int*m_error;
	int height;
	int width;
	int m_HistoArr[256];
	int m_errorHistoArr[512];
	int histo_max_value_y;
	int histo_axis_y;
	double entropy;
	int mode_flag;
	void CopyClipboard(unsigned char* m_CpyImg, int height, int width, int biBitCount);
	void m_ImgHisto(int height, int width);
	void m_errorHisto(int height, int width);
	void m_ImgPrediction1(int height,int width);
	void m_ImgPrediction2(int height, int width);
	void m_ImgPrediction3(int height, int width);
	void m_ImgPrediction4(int height, int width);
	void m_ImgAdaptPrediction(int height, int width);
};
