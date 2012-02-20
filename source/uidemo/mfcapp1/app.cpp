#include <module/plugininc.h> // or stdafx.h
#include "resource.h"
#include "frame.h"
#include <nonplugin/useplugins.h>
#include <nonplugin/scanplugins.h>

class CHelloApp : public CWinApp
{
public:
    CHelloApp() {}

protected:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
};

CHelloApp theApp;

BOOL CHelloApp::InitInstance()
{
	INITCOMMONCONTROLSEX initctls;
	initctls.dwSize = sizeof(initctls);
	initctls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&initctls);

	CWinApp::InitInstance();

    const char* plugins[] = { "x3manager.pln", "mfcwnd.pln", NULL };
    x3::loadPlugins(plugins, "plugins");
    x3::loadScanPlugins("plugins");

	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame || !pFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
    m_pMainWnd = pFrame;
    pFrame->SetIcon(LoadIcon(IDR_MAINFRAME), FALSE);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

int CHelloApp::ExitInstance()
{
    x3::unloadScanPlugins();
    x3::unloadPlugins();

    return CWinApp::ExitInstance();
}


#if defined(_UNICODE) && _MSC_VER >= 1400
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
