#pragma once


// CDigitalPanel

class CDigitalPanel : public CWnd
{
	DECLARE_DYNAMIC(CDigitalPanel)

public:
	CDigitalPanel();
	virtual ~CDigitalPanel();

protected:
	DECLARE_MESSAGE_MAP()

	int m_nValue;
	int m_nRange;
	int m_nType;
	CBitmap m_Bitmap;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	BOOL Create(int x, int y, int nRange, CWnd* pParentWnd, int nType);
	void CDigitalPanel::SetValue(int nValue);
};