
// 2013253063_HW3Doc.cpp : CMy2013253063_HW3Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "2013253063_HW3.h"
#endif

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#include <math.h>
#include "2013253063_HW3Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2013253063_HW3Doc

IMPLEMENT_DYNCREATE(CMy2013253063_HW3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy2013253063_HW3Doc, CDocument)
END_MESSAGE_MAP()


// CMy2013253063_HW3Doc 생성/소멸

CMy2013253063_HW3Doc::CMy2013253063_HW3Doc()
: m_InImg(NULL)
, m_OutImg(NULL)
, height(0)
, width(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_InImg = NULL; // 영상버퍼 초기화
	m_OutImg = NULL; // 영상버퍼 초기화g

	for (int i = 0; i<256; i++) //  흑백영상을 위한 팔레트
	{
		palRGB[i].rgbRed = palRGB[i].rgbGreen = palRGB[i].rgbBlue = i;
		palRGB[i].rgbReserved = 0;
	}
}

CMy2013253063_HW3Doc::~CMy2013253063_HW3Doc()
{
	if (m_InImg) delete []m_InImg;  // 영상버퍼가 할당되었다면 종료 전 해제
	if (m_OutImg) delete []m_OutImg;// 영상버퍼가 할당되었다면 종료 전 해제
}

/* 새문서 열기. 영상처리된 영상을 새창에 띄워줄 때 이용한다. */
BOOL CMy2013253063_HW3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다..
	::OpenClipboard(NULL);
	if (!IsClipboardFormatAvailable(CF_DIB)) return FALSE;
	HGLOBAL m_hImage = ::GetClipboardData(CF_DIB);
	::CloseClipboard();
	LPSTR pDIB = (LPSTR)::GlobalLock((HGLOBAL)m_hImage);

	BITMAPINFOHEADER dibHi;
	memcpy(&dibHi, pDIB, sizeof(BITMAPINFOHEADER));
	height = dibHi.biHeight; width = dibHi.biWidth;
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* 256 + rwsize*height * sizeof(char);

	m_InImg = new unsigned char[dibHi.biSizeImage];
	m_OutImg = new unsigned char[dibHi.biSizeImage];

	if (dibHi.biBitCount == 8)
	{
		memcpy(palRGB, pDIB + sizeof(BITMAPINFOHEADER), sizeof(RGBQUAD)* 256);
		memcpy(m_InImg, pDIB + dwBitsSize - dibHi.biSizeImage, dibHi.biSizeImage);
	}
	else memcpy(m_InImg, pDIB + sizeof(BITMAPINFOHEADER), dibHi.biSizeImage);

	return TRUE;
}




// CMy2013253063_HW3Doc serialization
void CMy2013253063_HW3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		CFile* infile = ar.GetFile(); // 입력한 파일의 포인트를 가져옴

		/* 확장자를 찾기 위함 */
		extension = (infile->GetFileName()).Right(3);

		/* 영상 이미지일때 == 0, 히스토그램 이미지일때 == 1*/
		mode_flag = 0;

		/* raw파일일 때 */
		if (!extension.CompareNoCase(_T("raw"))){
			int ImgSize = infile->GetLength();

			if (ImgSize == 256 * 256){
				height = 256;
				width = 256;
			}
			else if (ImgSize == 512 * 512){
				height = 512;
				width = 512;
			}
			else{
				AfxMessageBox(_T("지원하지 않는 파일 크기입니다.\n(256*256 또는512*512로 한정되어있습니다)"));
				return;
			}

			unsigned char* tmp = new unsigned char[ImgSize];
			m_InImg = new unsigned char[ImgSize];
			ar.Read(tmp,ImgSize);
			
			for (int i = 0; i < height;i++){
				for (int j = 0; j < width; j++) m_InImg[i*width + j] = tmp[((width-1)-i)*width+j];
			}

			delete []tmp;
	
		}
		else{
			AfxMessageBox(_T("Not RAW file!!"));
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy2013253063_HW3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMy2013253063_HW3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy2013253063_HW3Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy2013253063_HW3Doc 진단

#ifdef _DEBUG
void CMy2013253063_HW3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2013253063_HW3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2013253063_HW3Doc 명령


/* 영상처리된 이미지를 새창에 띄우기 전에 클립보드에 복사해넣는 과정이다. */
void CMy2013253063_HW3Doc::CopyClipboard(unsigned char* m_CpyImg, int height, int width, int biBitCount)
{
	// 클립보드에 복사하기 위한 파일의 길이를 구함
	int rwsize = WIDTHBYTES(biBitCount*width);
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* 256 + rwsize*height * sizeof(char);

	// 메모리 할당(파일헤드만 제외시킨 길이)
	HGLOBAL m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
	LPSTR pDIB = (LPSTR)::GlobalLock((HGLOBAL)m_hImage);

	// 데이터 복사
	BITMAPINFOHEADER dibCpyHi;
	dibCpyHi.biBitCount = biBitCount;
	dibCpyHi.biClrUsed = 256;
	dibCpyHi.biCompression = 0;
	dibCpyHi.biHeight = height;
	dibCpyHi.biPlanes = 1;
	dibCpyHi.biSize = 40;
	dibCpyHi.biWidth = width;
	dibCpyHi.biXPelsPerMeter = 0;
	dibCpyHi.biYPelsPerMeter = 0;
	dibCpyHi.biSizeImage = height*rwsize;
	if (biBitCount == 8) dibCpyHi.biClrUsed = dibCpyHi.biClrImportant = 256;

	memcpy(pDIB, &dibCpyHi, sizeof(BITMAPINFOHEADER));
	if (biBitCount == 8)
	{
		memcpy(pDIB + sizeof(BITMAPINFOHEADER), palRGB, sizeof(RGBQUAD)* 256);
		memcpy(pDIB + dwBitsSize - dibCpyHi.biSizeImage, m_CpyImg, dibCpyHi.biSizeImage);
	}
	else memcpy(pDIB + sizeof(BITMAPINFOHEADER), m_CpyImg, dibCpyHi.biSizeImage);

	// 클립보드 복사
	::OpenClipboard(NULL);
	::SetClipboardData(CF_DIB, m_hImage);
	::CloseClipboard();

	::GlobalUnlock((HGLOBAL)m_hImage);
	GlobalFree(m_hImage);
}

/* 원본 영상 히스토그램 */
void CMy2013253063_HW3Doc::m_ImgHisto(int height, int width)
{
	m_OutImg = new unsigned char[300*300];
	
	int i, j, gv, vmax, vmin;
	double p[256]; // 엔트로피 구할 때 Probability
	entropy = 0;   // 엔트로피 값 0으로 초기화

	for (i = 0; i < 256; i++){
		m_HistoArr[i] = 0; // 히스토그램 배열 초기화
	}

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
		    gv = (int)m_InImg[i*width+j];
			m_HistoArr[gv]++; // 밝기값에 따른 히스토그램 voting
		}
	}

	// 엔트로피 계산 (히스토그램을 계산할 때 같이 계산하도록 하였다)
	for (i = 0; i < 256; i++){
		if (m_HistoArr[i] != 0){
			p[i] = (double)m_HistoArr[i] / (double)(height*width);
			entropy += p[i] * (log(1 / p[i]) / log(2.0));
		}
	}

	// 히스토그램 크기 정규화(화면 출력을 위해)
	vmin = 1000000; vmax = 0;
	for (i = 0; i<256; i++)
	{
		if (m_HistoArr[i] <= vmin) vmin = m_HistoArr[i];
		if (m_HistoArr[i] >= vmax) vmax = m_HistoArr[i];
	}
	if (vmax == vmin) return;

	histo_max_value_y = vmax;
	
	vmax = ((2*vmax)/1000)*1000;
	histo_axis_y = vmax;

	float vd = (float)(vmax - vmin);
	for (i = 0; i<256; i++)
	{
		m_HistoArr[i] = (int)(((float)m_HistoArr[i] - vmin)*255.0 / vd);
	}

	// 히스토그램의 화면출력(히스토그램 화면출력을 위해 m_OutImg를 사용)
	for (i = 0; i < 300; i++)
		for (j = 0; j < 300; j++) m_OutImg[i * 300 + j] = 255;

	for (j = 0; j<256; j++)
	{
		for (i = 35; i<m_HistoArr[j]+35; i++) m_OutImg[i*300 + (j+20)] = 0;
	}
}

void CMy2013253063_HW3Doc::m_errorHisto(int height, int width){
	m_OutImg = new unsigned char[300 * 556];

	int i, j, gv, vmax, vmin;
	double p[511]; // 엔트로피 구할 때 Probability
	entropy = 0;   // 엔트로피 값 0으로 초기화

	for (i = 0; i < 511; i++){
		m_errorHistoArr[i] = 0; // 히스토그램 배열 초기화
	}


	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			gv = (int)m_error[i*width + j];
			m_errorHistoArr[gv + 255]++; // 밝기값에 따른 히스토그램 voting
		}
	}
	

	
	// 엔트로피 계산 (히스토그램을 계산할 때 같이 계산하도록 하였다)
	for (i = 0; i < 511; i++){
		if (m_errorHistoArr[i] != 0){
			p[i] = (double)m_errorHistoArr[i] / (double)(height*width);
			entropy += p[i] * (log(1 / p[i]) / log(2.0));
		}
	}

	// 히스토그램 크기 정규화(화면 출력을 위해)
	vmin = 1000000; vmax = 0;
	for (i = 0; i<511; i++)
	{
		if (m_errorHistoArr[i] <= vmin) vmin = m_errorHistoArr[i];
		if (m_errorHistoArr[i] >= vmax) vmax = m_errorHistoArr[i];
	}
	if (vmax == vmin) return;

	histo_max_value_y = vmax;

	vmax = ((2 * vmax) / 1000) * 1000;
	histo_axis_y = vmax;

	float vd = (float)(vmax - vmin);
	for (i = 0; i<511; i++)
	{
		m_errorHistoArr[i] = (int)(((float)m_errorHistoArr[i] - vmin)*255.0 / vd);
	}

	// 히스토그램의 화면출력(히스토그램 화면출력을 위해 m_OutImg를 사용)
	for (i = 0; i < 300; i++)
	for (j = 0; j < 556; j++) m_OutImg[i * 556 + j] = 255;

	for (j = 0; j<511; j++)
	{
		for (i = 35; i<m_errorHistoArr[j]+35; i++) m_OutImg[i * 556 + (j + 20)] = 0;
	}
}

// 1. X = A
void CMy2013253063_HW3Doc::m_ImgPrediction1(int height, int width){
	m_OutImg = new unsigned char[height * width];
	m_error = new int[height*width];

	unsigned char* predict_Img = new unsigned char[height*width];

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){

			// 첫 번째 열의 경우에는 Prediction된 이미지에 첫 번째 열을 복사해서 넣어준다.
			if (j == 0){
				predict_Img[i*width + j] = m_InImg[i*width + j];
			}
			// 그 외에는 이전 열에서 값을 예측한다.
			else{
				predict_Img[i*width + j] = m_InImg[i*width + (j-1)];
			}
		}
	}

	for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++) {
		    
		    // error = 원본 영상- 예측된 영상
		    // error 히스토그램을 위한 에러를 unsigned char형이 아닌 int로 따로 계산한다. 계산시에 나오는 음수 값을 위해서이다.
			m_error[i*width + j] = (int)m_InImg[i*width + j] - (int)predict_Img[i*width + j];

			// error 출력용 영상이다. 출력 영상은 unsigned char형으로 음수 표현이 불가능하다. 따라서 0보다 작은 값은 모두 0으로 만들어주었다.
			m_OutImg[i*width + j] = (m_InImg[i*width + j] - predict_Img[i*width + j])<0 ? 0 : (m_InImg[i*width + j] - predict_Img[i*width + j]);

	}

	delete[]predict_Img;

}

// 2. X = (1/2)*A + (1/2)*B
void CMy2013253063_HW3Doc::m_ImgPrediction2(int height, int width){
	m_OutImg = new unsigned char[height * width];
	m_error = new int[height*width];

	unsigned char* predict_Img = new unsigned char[height*width];

	/* 경계 처리시 값을 복사한 값을 사용하기 위해서 임시로 너비와 높이가 큰 이미지를 만들어준다.*/
	unsigned char* tmp = new unsigned char[(height+2)*(width*2)];
	for (int i = 0; i < height+2; i++){
		for (int j = 0; j < width+2; j++){
			
			/* 경계 */
			//1. 모서리
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j-2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i-2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j-2)];
			// 2. 변
			else if (i == 0){
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 1)];
			}
			else if (j == 0){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + j];
			}
			else if (i == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 1)];
			}
			else if (j == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 2)];
			}
			else{
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 1)];
			}
		}
	}

	
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			predict_Img[i*width + j] = (int)(0.5 * (double)tmp[i*(width + 2) + j] + 0.5 * (double)tmp[(i+1)*(width + 2) + j]+0.5);
		}
	}

	for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++) {
		m_error[i*width + j] = (int)m_InImg[i*width + j] - (int)predict_Img[i*width + j];
		m_OutImg[i*width + j] = (m_InImg[i*width + j] - predict_Img[i*width + j])<0 ? 0 : (m_InImg[i*width + j] - predict_Img[i*width + j]);
	}

	delete[]predict_Img;

}

// 3. X = A - B + C
void CMy2013253063_HW3Doc::m_ImgPrediction3(int height, int width){
	m_OutImg = new unsigned char[height * width];
	m_error = new int[height*width];

	unsigned char* predict_Img = new unsigned char[height*width];

	/* 경계 처리시 값을 복사한 값을 사용하기 위해서 임시로 너비와 높이가 큰 이미지를 만들어준다.*/
	unsigned char* tmp = new unsigned char[(height + 2)*(width * 2)];
	for (int i = 0; i < height + 2; i++){
		for (int j = 0; j < width + 2; j++){

			/* 경계 */
			// 1. 모서리
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 2)];
			// 2. 변
			else if (i == 0){
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 1)];
			}
			else if (j == 0){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + j];
			}
			else if (i == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 1)];
			}
			else if (j == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 2)];
			}
			else{
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 1)];
			}
		}
	}


	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			predict_Img[i*width + j] = tmp[i*(width + 2) + j] - tmp[(i + 1)*(width + 2) + j] + tmp[(i + 1)*(width + 2) + (j+1)];
		}
	}

	for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++) {
		m_error[i*width + j] = (int)m_InImg[i*width + j] - (int)predict_Img[i*width + j];
		m_OutImg[i*width + j] = (m_InImg[i*width + j] - predict_Img[i*width + j])<0 ? 0 : (m_InImg[i*width + j] - predict_Img[i*width + j]);
	}

	delete[]predict_Img;

}

// 4. X = 0.75*A - 0.5*B + 0.75*C
void CMy2013253063_HW3Doc::m_ImgPrediction4(int height, int width){
	m_OutImg = new unsigned char[height * width];
	m_error = new int[height*width];

	unsigned char* predict_Img = new unsigned char[height*width];

	/* 경계 처리시 값을 복사한 값을 사용하기 위해서 임시로 너비와 높이가 큰 이미지를 만들어준다.*/
	unsigned char* tmp = new unsigned char[(height + 2)*(width * 2)];
	for (int i = 0; i < height + 2; i++){
		for (int j = 0; j < width + 2; j++){

			/* 경계 */
			// 1. 모서리
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 2)];
			// 2. 변
			else if (i == 0){
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 1)];
			}
			else if (j == 0){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + j];
			}
			else if (i == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 1)];
			}
			else if (j == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 2)];
			}
			else{
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 1)];
			}
		}
	}


	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			predict_Img[i*width + j] = (int)(0.75*(double)tmp[i*(width + 2) + j] - 0.5*(double)tmp[(i + 1)*(width + 2) + j] + 0.75*(double)tmp[(i + 1)*(width + 2) + (j + 1)]+0.5);
		}
	}

	for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++) {
		m_error[i*width + j] = (int)m_InImg[i*width + j] - (int)predict_Img[i*width + j];
		m_OutImg[i*width + j] = (m_InImg[i*width + j] - predict_Img[i*width + j])<0 ? 0 : (m_InImg[i*width + j] - predict_Img[i*width + j]);
	}

	delete[]predict_Img;

}

// 5. Adaptive Prediction
void CMy2013253063_HW3Doc::m_ImgAdaptPrediction(int height, int width){
	m_OutImg = new unsigned char[height * width];
	m_error = new int[height*width];

	unsigned char* predict_Img = new unsigned char[height*width];

	/* 경계 처리시 값을 복사한 값을 사용하기 위해서 임시로 너비와 높이가 큰 이미지를 만들어준다.*/
	unsigned char* tmp = new unsigned char[(height + 2)*(width * 2)];
	for (int i = 0; i < height + 2; i++){
		for (int j = 0; j < width + 2; j++){

			/* 경계 */
			// 1. 모서리
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 2)];
			// 2. 변
			else if (i == 0){
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 1)];
			}
			else if (j == 0){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + j];
			}
			else if (i == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 1)];
			}
			else if (j == 513){
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 2)];
			}
			else{
				tmp[i*(width + 2) + j] = m_InImg[(i - 1)*width + (j - 1)];
			}
		}
	}


	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (tmp[(i + 1)*(width + 2) + j] >= MAX(tmp[i*(width + 2) + j], tmp[(i + 1)*(width + 2) + (j + 1)])){
				predict_Img[i*width + j] = MIN(tmp[i*(width + 2) + j], tmp[(i + 1)*(width + 2) + (j + 1)]);
			}
			else if (tmp[(i + 1)*(width + 2) + j] <= MIN(tmp[i*(width + 2) + j], tmp[(i + 1)*(width + 2) + (j + 1)])){
				predict_Img[i*width + j] = MAX(tmp[i*(width + 2) + j], tmp[(i + 1)*(width + 2) + (j + 1)]);
			}
			else{
				predict_Img[i*width + j] = tmp[i*(width + 2) + j] - tmp[(i + 1)*(width + 2) + j] + tmp[(i + 1)*(width + 2) + (j + 1)];
			}	
		}
	}

	for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++) {
		m_error[i*width + j] = (int)m_InImg[i*width + j] - (int)predict_Img[i*width + j];
		m_OutImg[i*width + j] = (m_InImg[i*width + j] - predict_Img[i*width + j])<0 ? 0 : (m_InImg[i*width + j] - predict_Img[i*width + j]);
	}

	delete[]predict_Img;
}