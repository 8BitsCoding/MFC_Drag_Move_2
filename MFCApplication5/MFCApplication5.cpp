
// MFCApplication5.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5App

BEGIN_MESSAGE_MAP(CMFCApplication5App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplication5App 생성

CMFCApplication5App::CMFCApplication5App()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCApplication5App 개체입니다.

CMFCApplication5App theApp;


// CMFCApplication5App 초기화

BOOL CMFCApplication5App::InitInstance()
{
	CWinApp::InitInstance();

	CMFCApplication5Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}

