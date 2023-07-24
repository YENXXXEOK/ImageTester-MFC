#include "pch.h"
#include "TestAlgorithm.h"

CTest gTest;
CTest::CTest()
{
	m_pSpecDlg = NULL;
}

CTest::~CTest()
{

}

void CTest::OnInit()
{
	if (m_pSpecDlg == NULL)
	{
		m_pSpecDlg = new CSpecDlg();
		m_pSpecDlg->Create(CSpecDlg::IDD);
	}
}

CSpecDlg* CTest::GetSpecDlg()
{
	return m_pSpecDlg;
}