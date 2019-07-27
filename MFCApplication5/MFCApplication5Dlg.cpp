
// MFCApplication5Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5Dlg 대화 상자



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCApplication5Dlg 메시지 처리기

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_rect.SetRect(10, 10, 100, 100);

	POINT star_pos[11] = { {101, 0}, {77, 77}, {0, 77}, {62, 125},
	{39, 201}, {101, 153}, {163, 201}, {138, 125}, {201, 77}, {124, 77}, {101, 0} };

	m_star_rgn.CreatePolygonRgn(star_pos, 11, ALTERNATE);
	// ALTERNATE : 별모양 내부를 클릭해도 먹는다.

	m_fill_brush.CreateSolidBrush(RGB(0, 0, 0));
	// m_fill_brush : 별의 테두리를 그리는데 사용할 브러쉬

	m_Ellipse_rgn.CreateEllipticRgn(210, 10, 300, 100);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication5Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// 원 그리기
		dc.PaintRgn(&m_Ellipse_rgn);

		// 별모양 그리기
		dc.PaintRgn(&m_star_rgn);
		dc.FrameRgn(&m_star_rgn, &m_fill_brush, 1, 1);
		// FrameRgn : 도형의 테두리 색을 지정
		// (리즌지정, 브러쉬지정, 브러쉬의 사이즈 지정(x, y) 몇 필셀로 그릴지)

		// 사각형 그리기
		dc.Rectangle(m_rect);

		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication5Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//if (point.x >= m_rect.left && point.y >= m_rect.top && 
	//	point.x <= m_rect.right && point.y <= m_rect.bottom)
	if(m_rect.PtInRect(point))
	{
		m_is_clicked = 1;		// 사각형
	}
	else if (m_star_rgn.PtInRegion(point)) {
		m_is_clicked = 2;		// 별
	}
	else if (m_Ellipse_rgn.PtInRegion(point)) {
		m_is_clicked = 3;		// 원
	}

	if (m_is_clicked)
	{
		m_prev_pos = point;
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication5Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_is_clicked) {
		m_is_clicked = 0;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCApplication5Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_is_clicked) {
		CPoint move_pos;
		move_pos = point - m_prev_pos;
		if (m_is_clicked == 1) {
			m_rect = m_rect + move_pos;
			/*
			m_rect.left += move_pos.x;
			m_rect.top += move_pos.y;
			m_rect.right += move_pos.x;
			m_rect.bottom += move_pos.y;
			*/
		}
		else if (m_is_clicked == 2) {
			// 안됨 -> m_star_rgn = m_star_rgn + move_pos;
			m_star_rgn.OffsetRgn(move_pos);
		}
		else if (m_is_clicked == 3) {
			m_Ellipse_rgn.OffsetRgn(move_pos);
		}

		m_prev_pos = point;
		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
