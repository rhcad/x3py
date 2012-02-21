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
    AFX_MANAGE_STATE_EX;
    CWnd* pParent = CWnd::FromHandle(reinterpret_cast<HWND>(hparent));

    if (m_pwnd->Create(NULL, L"Test", 
        WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), pParent, 
        id ? id : AFX_IDW_PANE_FIRST))
    {
        CRect rect;
        pParent->GetClientRect(&rect);
        m_pwnd->MoveWindow(&rect);

        return true;
    }

    return false;
}

size_t CSimple::getHandle() const
{
    return reinterpret_cast<size_t>(m_pwnd->GetSafeHwnd());
}

void CSimple::showMessage()
{
    ::MessageBox(m_pwnd->GetSafeHwnd(), L"Hello World MFC.", L"mfcwnd", MB_ICONINFORMATION);
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
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_FILE_UPDATE, OnTestRespond)
END_MESSAGE_MAP()

BOOL CSimpleWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

    cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

BOOL CSimpleWnd::OnEraseBkgnd(CDC*)
{
    return TRUE;
}

void CSimpleWnd::OnPaint() 
{
	CPaintDC dc(this);
    CRect rect;

    GetClientRect(rect);

    dc.FillSolidRect(rect, GetSysColor(COLOR_WINDOW));

    dc.MoveTo(0, 0);
    dc.LineTo(rect.BottomRight());
    dc.MoveTo(0, rect.bottom);
    dc.LineTo(rect.right, 0);

    dc.DrawText(L"Hello World MFC.", rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void CSimpleWnd::OnTestRespond()
{
    AfxMessageBox(L"Responded by the mfcwnd plugin.");
}
