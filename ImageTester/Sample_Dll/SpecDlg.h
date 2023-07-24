#pragma once
#include "afxdialogex.h"
#include "resource.h"

// CSpecDlg 대화 상자

class CSpecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSpecDlg)

public:
	CSpecDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSpecDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SPEC_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
