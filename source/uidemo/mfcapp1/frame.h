#pragma once

#include <objptr.h>

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
    virtual ~CMainFrame();

    HWND GetChildWnd() const;

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
    afx_msg void OnDemoInView();
    DECLARE_MESSAGE_MAP()

private:
	CStatusBar      m_statusBar;
    x3::AnyObject   m_view;
};
