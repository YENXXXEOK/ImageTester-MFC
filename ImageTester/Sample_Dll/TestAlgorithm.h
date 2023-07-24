#pragma once
#include "SpecDlg.h"

class CTest
{
private:
	CSpecDlg*	m_pSpecDlg;

public:
	CTest();
	~CTest();

	void OnInit();
	CSpecDlg* GetSpecDlg();
};
extern CTest gTest;