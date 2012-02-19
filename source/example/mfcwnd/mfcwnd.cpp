#include <module/plugininc.h>
#include "mfcwnd.h"

CSimple::CSimple()
{
    m_pwnd = new CSimpleWnd();
}

CSimple::~CSimple()
{
    delete m_pwnd;
}

bool CSimple::createWnd(size_t hparent, int id)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CWnd* pParent = CWnd::FromHandle(reinterpret_cast<HWND>(hparent));

    return !!m_pwnd->CreateEx(WS_EX_STATICEDGE, NULL, L"Test", 
        WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), pParent, 
        id ? id : AFX_IDW_PANE_FIRST);
}

size_t CSimple::getHandle() const
{
    return reinterpret_cast<size_t>(m_pwnd->GetSafeHwnd());
}

void CSimple::showMessage()
{
    ::MessageBox(m_pwnd->GetSafeHwnd(), L"Hello World MFC.", L"Test", MB_ICONINFORMATION);
}

//------------------------------------------------

CSimpleWnd::CSimpleWnd()
{
}

CSimpleWnd::~CSimpleWnd()
{
}

BEGIN_MESSAGE_MAP(CSimpleWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CSimpleWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CSimpleWnd::OnPaint() 
{
	CPaintDC dc(this);

    dc.TextOut(10, 10, L"Hello World MFC.");
}
