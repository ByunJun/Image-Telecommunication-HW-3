
// 2013253063_HW3Doc.cpp : CMy2013253063_HW3Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CMy2013253063_HW3Doc ����/�Ҹ�

CMy2013253063_HW3Doc::CMy2013253063_HW3Doc()
: m_InImg(NULL)
, m_OutImg(NULL)
, height(0)
, width(0)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_InImg = NULL; // ������� �ʱ�ȭ
	m_OutImg = NULL; // ������� �ʱ�ȭg

	for (int i = 0; i<256; i++) //  ��鿵���� ���� �ȷ�Ʈ
	{
		palRGB[i].rgbRed = palRGB[i].rgbGreen = palRGB[i].rgbBlue = i;
		palRGB[i].rgbReserved = 0;
	}
}

CMy2013253063_HW3Doc::~CMy2013253063_HW3Doc()
{
	if (m_InImg) delete []m_InImg;  // ������۰� �Ҵ�Ǿ��ٸ� ���� �� ����
	if (m_OutImg) delete []m_OutImg;// ������۰� �Ҵ�Ǿ��ٸ� ���� �� ����
}

/* ������ ����. ����ó���� ������ ��â�� ����� �� �̿��Ѵ�. */
BOOL CMy2013253063_HW3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�..
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
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		CFile* infile = ar.GetFile(); // �Է��� ������ ����Ʈ�� ������

		/* Ȯ���ڸ� ã�� ���� */
		extension = (infile->GetFileName()).Right(3);

		/* ���� �̹����϶� == 0, ������׷� �̹����϶� == 1*/
		mode_flag = 0;

		/* raw������ �� */
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
				AfxMessageBox(_T("�������� �ʴ� ���� ũ���Դϴ�.\n(256*256 �Ǵ�512*512�� �����Ǿ��ֽ��ϴ�)"));
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

// ����� �׸��� �����մϴ�.
void CMy2013253063_HW3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CMy2013253063_HW3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CMy2013253063_HW3Doc ����

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


// CMy2013253063_HW3Doc ���


/* ����ó���� �̹����� ��â�� ���� ���� Ŭ�����忡 �����سִ� �����̴�. */
void CMy2013253063_HW3Doc::CopyClipboard(unsigned char* m_CpyImg, int height, int width, int biBitCount)
{
	// Ŭ�����忡 �����ϱ� ���� ������ ���̸� ����
	int rwsize = WIDTHBYTES(biBitCount*width);
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* 256 + rwsize*height * sizeof(char);

	// �޸� �Ҵ�(������常 ���ܽ�Ų ����)
	HGLOBAL m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
	LPSTR pDIB = (LPSTR)::GlobalLock((HGLOBAL)m_hImage);

	// ������ ����
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

	// Ŭ������ ����
	::OpenClipboard(NULL);
	::SetClipboardData(CF_DIB, m_hImage);
	::CloseClipboard();

	::GlobalUnlock((HGLOBAL)m_hImage);
	GlobalFree(m_hImage);
}

/* ���� ���� ������׷� */
void CMy2013253063_HW3Doc::m_ImgHisto(int height, int width)
{
	m_OutImg = new unsigned char[300*300];
	
	int i, j, gv, vmax, vmin;
	double p[256]; // ��Ʈ���� ���� �� Probability
	entropy = 0;   // ��Ʈ���� �� 0���� �ʱ�ȭ

	for (i = 0; i < 256; i++){
		m_HistoArr[i] = 0; // ������׷� �迭 �ʱ�ȭ
	}

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
		    gv = (int)m_InImg[i*width+j];
			m_HistoArr[gv]++; // ��Ⱚ�� ���� ������׷� voting
		}
	}

	// ��Ʈ���� ��� (������׷��� ����� �� ���� ����ϵ��� �Ͽ���)
	for (i = 0; i < 256; i++){
		if (m_HistoArr[i] != 0){
			p[i] = (double)m_HistoArr[i] / (double)(height*width);
			entropy += p[i] * (log(1 / p[i]) / log(2.0));
		}
	}

	// ������׷� ũ�� ����ȭ(ȭ�� ����� ����)
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

	// ������׷��� ȭ�����(������׷� ȭ������� ���� m_OutImg�� ���)
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
	double p[511]; // ��Ʈ���� ���� �� Probability
	entropy = 0;   // ��Ʈ���� �� 0���� �ʱ�ȭ

	for (i = 0; i < 511; i++){
		m_errorHistoArr[i] = 0; // ������׷� �迭 �ʱ�ȭ
	}


	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			gv = (int)m_error[i*width + j];
			m_errorHistoArr[gv + 255]++; // ��Ⱚ�� ���� ������׷� voting
		}
	}
	

	
	// ��Ʈ���� ��� (������׷��� ����� �� ���� ����ϵ��� �Ͽ���)
	for (i = 0; i < 511; i++){
		if (m_errorHistoArr[i] != 0){
			p[i] = (double)m_errorHistoArr[i] / (double)(height*width);
			entropy += p[i] * (log(1 / p[i]) / log(2.0));
		}
	}

	// ������׷� ũ�� ����ȭ(ȭ�� ����� ����)
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

	// ������׷��� ȭ�����(������׷� ȭ������� ���� m_OutImg�� ���)
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

			// ù ��° ���� ��쿡�� Prediction�� �̹����� ù ��° ���� �����ؼ� �־��ش�.
			if (j == 0){
				predict_Img[i*width + j] = m_InImg[i*width + j];
			}
			// �� �ܿ��� ���� ������ ���� �����Ѵ�.
			else{
				predict_Img[i*width + j] = m_InImg[i*width + (j-1)];
			}
		}
	}

	for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++) {
		    
		    // error = ���� ����- ������ ����
		    // error ������׷��� ���� ������ unsigned char���� �ƴ� int�� ���� ����Ѵ�. ���ÿ� ������ ���� ���� ���ؼ��̴�.
			m_error[i*width + j] = (int)m_InImg[i*width + j] - (int)predict_Img[i*width + j];

			// error ��¿� �����̴�. ��� ������ unsigned char������ ���� ǥ���� �Ұ����ϴ�. ���� 0���� ���� ���� ��� 0���� ������־���.
			m_OutImg[i*width + j] = (m_InImg[i*width + j] - predict_Img[i*width + j])<0 ? 0 : (m_InImg[i*width + j] - predict_Img[i*width + j]);

	}

	delete[]predict_Img;

}

// 2. X = (1/2)*A + (1/2)*B
void CMy2013253063_HW3Doc::m_ImgPrediction2(int height, int width){
	m_OutImg = new unsigned char[height * width];
	m_error = new int[height*width];

	unsigned char* predict_Img = new unsigned char[height*width];

	/* ��� ó���� ���� ������ ���� ����ϱ� ���ؼ� �ӽ÷� �ʺ�� ���̰� ū �̹����� ������ش�.*/
	unsigned char* tmp = new unsigned char[(height+2)*(width*2)];
	for (int i = 0; i < height+2; i++){
		for (int j = 0; j < width+2; j++){
			
			/* ��� */
			//1. �𼭸�
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j-2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i-2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j-2)];
			// 2. ��
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

	/* ��� ó���� ���� ������ ���� ����ϱ� ���ؼ� �ӽ÷� �ʺ�� ���̰� ū �̹����� ������ش�.*/
	unsigned char* tmp = new unsigned char[(height + 2)*(width * 2)];
	for (int i = 0; i < height + 2; i++){
		for (int j = 0; j < width + 2; j++){

			/* ��� */
			// 1. �𼭸�
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 2)];
			// 2. ��
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

	/* ��� ó���� ���� ������ ���� ����ϱ� ���ؼ� �ӽ÷� �ʺ�� ���̰� ū �̹����� ������ش�.*/
	unsigned char* tmp = new unsigned char[(height + 2)*(width * 2)];
	for (int i = 0; i < height + 2; i++){
		for (int j = 0; j < width + 2; j++){

			/* ��� */
			// 1. �𼭸�
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 2)];
			// 2. ��
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

	/* ��� ó���� ���� ������ ���� ����ϱ� ���ؼ� �ӽ÷� �ʺ�� ���̰� ū �̹����� ������ش�.*/
	unsigned char* tmp = new unsigned char[(height + 2)*(width * 2)];
	for (int i = 0; i < height + 2; i++){
		for (int j = 0; j < width + 2; j++){

			/* ��� */
			// 1. �𼭸�
			if (i == 0 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[i*width + j];
			else if (i == 0 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[i*width + (j - 2)];
			else if (i == 513 && j == 0)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + j];
			else if (i == 513 && j == 513)
				tmp[i*(width + 2) + j] = m_InImg[(i - 2)*width + (j - 2)];
			// 2. ��
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