
// BlackJackDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "DigitalPanel.h"


// CBlackJackDlg ��ȭ ����
class CBlackJackDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CBlackJackDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLACKJACK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	int m_nWin, m_nManNum, m_nComputerNum, m_nManScore, m_nComputerScore, m_nSequence;
	int m_nManCard[10], m_nComputerCard[10];
	BOOL m_bReleased[52];

	CBitmap m_bmpCard;
	CBitmap m_bmpCardMask;
	CBitmap m_bmpBackground;
	CBitmap m_bmpLose;
	CBitmap m_bmpWin;

	CDigitalPanel m_ManPanel;	   // ���� (���)
	CDigitalPanel m_ComputerPanel; // ���� (��ǻ��)
	CDigitalPanel m_WinPanel;      // ���� ������ �ִ� �ݾ� 

	void DistributeCard();
	void GiveCard(BOOL bMan);
	void DrawCard(int nCard, int x, int y);
	void DoComputer();
	void LoseGame();
	void WinGame();
	void CalcScore(int *nCard, int &nNum, int &nScore);

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_Play;
	CButton m_Hit;
	CButton m_Stand;
	afx_msg void OnPlay();
	afx_msg void OnHit();
	afx_msg void OnStand();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
