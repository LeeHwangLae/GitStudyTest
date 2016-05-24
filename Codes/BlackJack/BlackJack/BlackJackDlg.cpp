
// BlackJackDlg.cpp : 구?E파일
//

#include "stdafx.h"
#include "BlackJack.h"
#include "BlackJackDlg.h"
#include "afxdialogex.h"

#define IDT_DISTCARD 0
#define IDT_DOCOMPUT 1
#define IDT_LOSEGAME 2
#define IDT_WINGAME  3

#define CARDWIDTH 71
#define CARDHEIGHT 96
#define MARGIN  20
#define GAP  10
#define YPOSMAN 260
#define YPOSCOM 70

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응퓖E프로그램 정보에 사퓖E풔?CAboutDlg 큱E?상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 큱E?상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBlackJackDlg 큱E?상자



CBlackJackDlg::CBlackJackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BLACKJACK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nWin = 5000;
	m_nManNum = m_nComputerNum = m_nManScore = m_nComputerScore = 0;
	m_nSequence = 0;
	for (int i = 0; i<52; i++)
		m_bReleased[i] = FALSE;
}

void CBlackJackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAY, m_Play);
	DDX_Control(pDX, IDC_HIT, m_Hit);
	DDX_Control(pDX, IDC_STAND, m_Stand);
}

BEGIN_MESSAGE_MAP(CBlackJackDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, &CBlackJackDlg::OnPlay)
	ON_BN_CLICKED(IDC_HIT, &CBlackJackDlg::OnHit)
	ON_BN_CLICKED(IDC_STAND, &CBlackJackDlg::OnStand)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CBlackJackDlg 메시햨E처리콅E

BOOL CBlackJackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 뫄譚 퉩E㎰?있엉雹 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 큱E?상자의 아이콘을 설정합니다.  응퓖E프로그램의 주 창이 큱E?상자가 아닐 경퓖E〈?
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bmpCard.LoadBitmap(IDB_CARD);
	m_bmpBackground.LoadBitmap(IDB_BLACKJACK);
	m_bmpLose.LoadBitmap(IDB_LOSE);
	m_bmpWin.LoadBitmap(IDB_WIN);
	m_bmpCardMask.LoadBitmap(IDB_CARDMASK);

	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);

	// 숫자 판넬 생성
	m_ManPanel.Create(120, 206, 2, this, 1);
	m_ComputerPanel.Create(120, 22, 2, this, 1);
	m_WinPanel.Create(540, 30, 6, this, 1);
	m_WinPanel.SetValue(m_nWin);
	m_ComputerPanel.SetValue(m_nComputerScore);
	m_ManPanel.SetValue(m_nManScore);
	return TRUE;  // 포커스를 컨트롤에 설정하햨E않으툈ETRUE를 반환합니다.
}

void CBlackJackDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 큱E?상자에 최소화 단추를 추가할 경퓖E아이콘을 그리려툈E
//  아래 코드가 필요합니다.  문서/틒E모델을 사퓖E求?MFC 응퓖E프로그램의 경퓖E〈?
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBlackJackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각?E【?아이콘을 가웝棄에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

		int i;
		CDC MemDC;

		// 배컖E비트맵 그리콅E
		MemDC.CreateCompatibleDC(&dc);
		CBitmap *pOld = (CBitmap *)MemDC.SelectObject(&m_bmpBackground);
		dc.BitBlt(0, 0, 640, 460, &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(pOld);

		// 카탛E다시 그리콅E
		for (i = 0; i<m_nManNum; i++)
			DrawCard(m_nManCard[i], MARGIN + i*(CARDWIDTH + GAP), YPOSMAN);
		for (i = 0; i<m_nComputerNum; i++)
			DrawCard(m_nComputerCard[i], MARGIN + i*(CARDWIDTH + GAP), YPOSCOM);
	}
	else
	{
		CPaintDC dc(this);

		CDialogEx::OnPaint();
	}
}

// 사퓖E微?최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBlackJackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBlackJackDlg::OnPlay()
{
	m_Play.ShowWindow(SW_HIDE);
	InvalidateRect(NULL); //오톩E때문에 잠콅E닫아놓음

	m_nManNum = m_nComputerNum = m_nManScore = m_nComputerScore = 0;
	m_nSequence = 0;
	for (int i = 0; i<52; i++)
		m_bReleased[i] = FALSE;
	SetTimer(IDT_DISTCARD, 500, NULL);
}


void CBlackJackDlg::OnHit()
{
	if (m_nManNum > 4) return; //카탛E계속 생성 막음
	GiveCard(TRUE);

	if (m_nManScore == 21) OnStand();
	else if (m_nManScore > 21)
	{ 
		m_Hit.ShowWindow(SW_HIDE);
		m_Stand.ShowWindow(SW_HIDE);
		SetTimer(IDT_DOCOMPUT, 500, NULL);
	}
}

void CBlackJackDlg::OnStand()
{
	m_Hit.ShowWindow(SW_HIDE);
	m_Stand.ShowWindow(SW_HIDE);
	SetTimer(IDT_DOCOMPUT, 500, NULL);
}

void CBlackJackDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	switch (nIDEvent)
	{
		case IDT_DISTCARD: DistributeCard();
			break;
		case IDT_DOCOMPUT: DoComputer();
			break;
		case IDT_LOSEGAME: LoseGame();
			break;
		case IDT_WINGAME: WinGame();
			break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CBlackJackDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pbmpOld = MemDC.SelectObject(&m_bmpBackground);
	pDC->BitBlt(0, 0, rc.right, rc.bottom, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pbmpOld);

	ReleaseDC(pDC);
	return CDialogEx::OnEraseBkgnd(pDC);
}

void CBlackJackDlg::DistributeCard()
{
	// 카드를 차례로 나누푳E줌
	switch(m_nSequence)
	{
		case 0: GiveCard(TRUE);
			break;
		case 1: GiveCard(FALSE);
			break;
		case 2: KillTimer(IDT_DISTCARD);
			m_Hit.ShowWindow(SW_SHOW);
			m_Stand.ShowWindow(SW_SHOW);
			break;
	}
	m_nSequence++;
}

void CBlackJackDlg::GiveCard(BOOL bMan)
{
	int nCard;
	// 아햨E나누푳E주햨E않은 카드를 무작위로 선택
	srand(GetCurrentTime());
	do
	{
		nCard = rand() * 51 / (RAND_MAX + 1);
	}
	while (m_bReleased[nCard] != FALSE);
	m_bReleased[nCard] = TRUE;

	if (bMan) 
	{   
		// 사람에게 나누푳E줄 때
		m_nManCard[m_nManNum] = nCard;
		// 받은 카드를 그려줌
		DrawCard(nCard, MARGIN+m_nManNum*(CARDWIDTH+GAP), YPOSMAN);
		m_nManNum++;
		// 점펯E계퍊E
		CalcScore(m_nManCard, m_nManNum, m_nManScore);
		m_ManPanel.SetValue(m_nManScore);
	}

	else
	{
		// 컴퓨터에게 나누푳E줄 때
		m_nComputerCard[m_nComputerNum] = nCard;
		// 받은 카드를 그려줌
		DrawCard(nCard, MARGIN + m_nComputerNum*(CARDWIDTH + GAP), YPOSCOM);
		m_nComputerNum++;
		// 점펯E계퍊E
		CalcScore(m_nComputerCard, m_nComputerNum, m_nComputerScore);
		m_ComputerPanel.SetValue(m_nComputerScore);
	}
}

void CBlackJackDlg::DrawCard(int nCard, int x, int y)
{
	int nX, nY;

	//nX, nY 값 지정해 보자.
	nX = nCard / 13;
	nY = nCard % 13;

	CClientDC dc(this);
	CDC MemDC;

	MemDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&m_bmpCardMask);
	dc.BitBlt(x, y, CARDWIDTH, CARDHEIGHT, &MemDC, 0, 0, SRCAND);
	MemDC.SelectObject(&m_bmpCard);
	dc.BitBlt(x, y, CARDWIDTH, CARDHEIGHT, &MemDC, nX*CARDWIDTH, nY*CARDHEIGHT, SRCPAINT);
	MemDC.SelectObject(pOldBitmap);
}

void CBlackJackDlg::DoComputer()
{
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	if (m_nManScore > 21)
	{
		KillTimer(IDT_DOCOMPUT);
		MemDC.SelectObject(&m_bmpLose);
		dc.BitBlt(200, 200, 200, 50, &MemDC, 0, 0, SRCCOPY);
		SetTimer(IDT_LOSEGAME,2000,NULL);
		m_Hit.ShowWindow(SW_HIDE);
		m_Stand.ShowWindow(SW_HIDE);
	}
	else if (m_nComputerScore<21 && m_nComputerScore-m_nManScore<=0)
	{//컴퓨터에게 카드를 한픸E큱E배분
		GiveCard(FALSE);
	}
	else
	{
		KillTimer(IDT_DOCOMPUT);
		m_Hit.ShowWindow(SW_HIDE);
		m_Stand.ShowWindow(SW_HIDE);

		if (m_nComputerScore > 21)
		{//유저승리
			MemDC.SelectObject(&m_bmpWin);
			dc.BitBlt(200, 200, 200, 50, &MemDC, 0, 0, SRCCOPY);
			SetTimer(IDT_WINGAME, 2000, NULL);
		}
		else if ((m_nComputerScore) < (m_nManScore))
		{//유저승리
			MemDC.SelectObject(&m_bmpWin);
			dc.BitBlt(200, 200, 200, 50, &MemDC, 0, 0, SRCCOPY);
			SetTimer(IDT_WINGAME, 2000, NULL);
		}
		else if (m_nComputerScore == m_nManScore)
		{
			OnPlay();
		}
		else
		{
			MemDC.SelectObject(&m_bmpLose);
			dc.BitBlt(200, 200, 200, 50, &MemDC, 0, 0, SRCCOPY);
			SetTimer(IDT_LOSEGAME, 2000, NULL);
		}
	}
}

void CBlackJackDlg::LoseGame()
{
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	KillTimer(IDT_LOSEGAME);
	MemDC.SelectObject(m_bmpBackground);
	dc.BitBlt(200, 200, 200, 50, &MemDC, 200, 200, SRCCOPY);
	this->m_nWin = m_nWin - 1000; // 지면 1000원 내리기
	m_WinPanel.SetValue(m_nWin); // 그것을 저장
	if (m_nWin <= 0) // 돈이 0원이하면 끝
	{
		AfxMessageBox(_T("You Lose..."));
		SendMessage(WM_CLOSE, 0, 0);
	}

	m_Play.ShowWindow(SW_SHOW);
}

void CBlackJackDlg::WinGame()
{
	CClientDC dc(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	KillTimer(IDT_WINGAME);
	MemDC.SelectObject(m_bmpBackground);
	dc.BitBlt(200, 200, 200, 50, &MemDC, 200, 200, SRCCOPY);
	this->m_nWin = m_nWin + 1000; // 이기면 1000원 올리기
	m_WinPanel.SetValue(m_nWin); // 그것을 저장
	if (m_nWin >= 10000) // 돈이 10000원 이상이면 끝
	{
		AfxMessageBox(_T("You Win!"));
		SendMessage(WM_CLOSE, 0, 0);
	}

	m_Play.ShowWindow(SW_SHOW);
}

void CBlackJackDlg::CalcScore(int *nCard, int &nNum, int &nScore)
{
	int nS;
	int aceNum = 0;

	nScore = 0;
	for (int i = 0; i < nNum; i++)
	{
		nS = nCard[i] % 13 + 1;
		if (nS == 1)
		{
			aceNum++;
			nS = 11;
		}
		else
		{
			nS = nS > 10 ? 10 : nS;
		}
		nScore += nS;


	}
	while (aceNum > 0)
	{
		nScore -= nScore > 22 ? 10 : 1;
		--aceNum;
	}
}