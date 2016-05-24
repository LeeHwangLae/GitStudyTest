
// BlackJackDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "DigitalPanel.h"


// CBlackJackDlg 대화 상자
class CBlackJackDlg : public CDialogEx
{
// 생성입니다.
public:
	CBlackJackDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLACKJACK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
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

	CDigitalPanel m_ManPanel;	   // 점수 (사람)
	CDigitalPanel m_ComputerPanel; // 점수 (컴퓨터)
	CDigitalPanel m_WinPanel;      // 현재 가지고 있는 금액 

	void DistributeCard();
	void GiveCard(BOOL bMan);
	void DrawCard(int nCard, int x, int y);
	void DoComputer();
	void LoseGame();
	void WinGame();
	void CalcScore(int *nCard, int &nNum, int &nScore);

	// 생성된 메시지 맵 함수
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
