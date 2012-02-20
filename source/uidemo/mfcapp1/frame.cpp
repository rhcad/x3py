#include <module/plugininc.h> // or stdafx.h
#include "resource.h"
#include "frame.h"
#include <mfcwnd/isimple.h>

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
    ON_COMMAND(ID_CALL_VIEWPLUGIN, OnDemoInView)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_NUM,
	ID_INDICATOR_XY,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    x3::Object<ISimpleWnd> wnd(clsidSimple);

    m_view = wnd;
    if (!wnd || !wnd->createWnd((size_t)GetSafeHwnd(), AFX_IDW_PANE_FIRST))
	{
        TRACE0("Fail to create sub-window.\n");
		return -1;
	}

	if (!m_statusBar.Create(this) ||
		!m_statusBar.SetIndicators(indicators, _countof(indicators)))
	{
		return -1;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

HWND CMainFrame::GetChildWnd() const
{
    x3::Object<ISimpleWnd> wnd(m_view);
    return wnd ? (HWND)wnd->getHandle() : NULL;
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
    ::SetFocus(GetChildWnd());

    CFrameWnd::OnSetFocus(pOldWnd);
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    CWnd* wnd = CWnd::FromHandle(GetChildWnd());
	if (wnd && wnd->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnDemoInView()
{
    x3::Object<ISimpleWnd> wnd(m_view);
    wnd->showMessage();
}
