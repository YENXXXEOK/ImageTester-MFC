// SpecDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Sample_Dll.h"
#include "afxdialogex.h"
#include "SpecDlg.h"


// CSpecDlg 대화 상자

IMPLEMENT_DYNAMIC(CSpecDlg, CDialogEx)

CSpecDlg::CSpecDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPEC_DLG, pParent)
{

}

CSpecDlg::~CSpecDlg()
{
}

void CSpecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSpecDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpecDlg 메시지 처리기
