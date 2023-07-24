
// ImageTester.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ImageTester.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ImageTesterDoc.h"
#include "ImageTesterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageTesterApp

BEGIN_MESSAGE_MAP(CImageTesterApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CImageTesterApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CImageTesterApp::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CImageTesterApp 생성

CImageTesterApp::CImageTesterApp() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 애플리케이션을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 애플리케이션 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ImageTester.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CImageTesterApp 개체입니다.

CImageTesterApp theApp;


// CImageTesterApp 초기화

BOOL CImageTesterApp::InitInstance()
{
	// 애플리케이션 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 애플리케이션의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_ImageTesterTYPE,
		RUNTIME_CLASS(CImageTesterDoc),
		RUNTIME_CLASS(CChildFrame), // 사용자 지정 MDI 자식 프레임입니다.
		RUNTIME_CLASS(CImageTesterView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 주 MDI 프레임 창을 만듭니다.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 주 창이 초기화되었으므로 이를 표시하고 업데이트합니다.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CImageTesterApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CImageTesterApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CImageTesterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CImageTesterApp 사용자 지정 로드/저장 방법

void CImageTesterApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CImageTesterApp::LoadCustomState()
{
}

void CImageTesterApp::SaveCustomState()
{
}

// CImageTesterApp 메시지 처리기
void CImageTesterApp::OnFileOpen()
{
	CString strFilter = _T("All Files(*.*)|*.*|jpeg (*.jpg)|*.jpg|bmp (*.bmp)|*.bmp|raw (*.raw)|*.raw|");
	CFileDialog file(TRUE, _T("*"), _T("*.bmp"), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, strFilter, NULL);
	if (file.DoModal() == IDOK)
	{
		CString strPath = file.GetPathName();

		SetImage(strPath);
	}

	Load_LibItem(0, _T("Dll"), _T("Sample_Dll.dll"));
	Load_LibItem(1, _T("Dll"), _T("Sample_Dll.dll"));
}

void CImageTesterApp::SetImage(CString strPath)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CImageTesterView* pView = (CImageTesterView*)pMain->GetActiveFrame()->GetActiveView();

	pView->SetImage(strPath);
}

void CImageTesterApp::Load_LibItem(UINT nItem, CString strFolder, CString strFileName)
{
	TCHAR szPath[MAX_PATH];
	CString str;

	fp_OnCreateItem				OnCreateItem	=		NULL;
	fp_OnSpecDlg				OnSpecDlg		=		NULL;
	fp_OnTest					OnTest			=		NULL;
	fp_OnDeleteItem				OnDeleteItem	=		NULL;

	TCHAR exePath[256] = { 0, };
	GetModuleFileName(NULL, exePath, 256);   // 현재 경로 가져오기

	CString folderPath = exePath;
	folderPath = folderPath.Left(folderPath.ReverseFind('\\')); // 실행파일을 뺀 경로 가져오기


	wsprintf(szPath, _T("%s\\%s\\%s"), folderPath, strFolder, strFileName);
	m_hInstance = ::LoadLibrary(szPath);

	if (m_hInstance)
	{
		OnCreateItem	=		(fp_OnCreateItem)		GetProcAddress		(m_hInstance, "OnCreateItem");
		OnSpecDlg		=		(fp_OnSpecDlg)			GetProcAddress		(m_hInstance, "OnSpecDlg");
		OnTest			=		(fp_OnTest)				GetProcAddress		(m_hInstance, "OnTest");
		OnDeleteItem	=		(fp_OnDeleteItem)		GetProcAddress		(m_hInstance, "OnDeleteItem");

		if (
			OnCreateItem &&
			OnSpecDlg// &&
			//OnTest &&
			//OnDeleteItem
			)
		{
			str.Format(_T("%s Pass to get function pointer.\n"), strFileName);
			TRACE(str);
		}
		else
		{
			str.Format(_T("%s Failed to get function pointer.\n"), strFileName);
			AfxMessageBox(str);
		}
	}
	switch (nItem)
	{
	case 0:
		OnCreateItem();
		break;
	case 1:
		OnSpecDlg();
		break;
	case 2:
		OnTest();
		break;
	case 3:
		OnDeleteItem();
		break;
	}

}
