// DigitalPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BlackJack.h"
#include "DigitalPanel.h"

#define DIGIT_PANEL_MARGIN 0
#define DIGIT_PANEL_X 15
#define DIGIT_PANEL_Y 20 

// CDigitalPanel

IMPLEMENT_DYNAMIC(CDigitalPanel, CWnd)

CDigitalPanel::CDigitalPanel()
{

}

CDigitalPanel::~CDigitalPanel()
{
}


BEGIN_MESSAGE_MAP(CDigitalPanel, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CDigitalPanel �޽��� ó�����Դϴ�.




int CDigitalPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	if (m_nType == 0) 
		m_Bitmap.LoadBitmap(IDB_DIGIT1);
	else  
		m_Bitmap.LoadBitmap(IDB_DIGIT2);

	return 0;
}


void CDigitalPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CWnd::OnPaint()��(��) ȣ������ ���ʽÿ�.

	int nValue = m_nValue;
	int i, nDigit, nRadix = 1;
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(&m_Bitmap);
	for (i = 0; i<m_nRange - 1; i++)
		nRadix *= 10;
	for (i = 0; i<m_nRange; i++)
	{
		nDigit = nValue / nRadix;   
		dc.BitBlt(DIGIT_PANEL_MARGIN + i*DIGIT_PANEL_X, DIGIT_PANEL_MARGIN, DIGIT_PANEL_X, DIGIT_PANEL_Y, &MemDC, DIGIT_PANEL_X*nDigit, 0, SRCCOPY);   
		nValue -= nDigit*nRadix;   
		nRadix /= 10; 
	}
}


BOOL CDigitalPanel::Create(int x, int y, int nRange, CWnd* pParentWnd, int nType)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_nRange = nRange;
	m_nType = nType;

	CRect rect = CRect(x, y, x + nRange*DIGIT_PANEL_X + 2 * DIGIT_PANEL_MARGIN + 2, y + DIGIT_PANEL_Y + 2 * DIGIT_PANEL_MARGIN);

	return CWnd::Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParentWnd, 0);
}

void CDigitalPanel::SetValue(int nValue)
{
	m_nValue = nValue;
	int i, nDigit, nRadix = 1;
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	if (nValue < 0)   
		nValue = -nValue;  
	else     
		MemDC.SelectObject(&m_Bitmap);

	for (i = 0; i<m_nRange - 1; i++) 
		nRadix *= 10;
	for (i = 0; i<m_nRange; i++) 
	{ 
		nDigit = nValue / nRadix;   
		dc.BitBlt(DIGIT_PANEL_MARGIN + i*DIGIT_PANEL_X, DIGIT_PANEL_MARGIN, DIGIT_PANEL_X, DIGIT_PANEL_Y, &MemDC, DIGIT_PANEL_X*nDigit, 0, SRCCOPY);      
		nValue -= nDigit*nRadix;   
		nRadix /= 10; 
	}
}