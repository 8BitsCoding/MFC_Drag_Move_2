
// MFCApplication5Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication5Dlg 대화 상자
class CMFCApplication5Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication5Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CRect m_rect;
	char m_is_clicked = 0;
	CPoint m_prev_pos;
	CRgn m_star_rgn, m_Ellipse_rgn;
	CBrush m_fill_brush;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
