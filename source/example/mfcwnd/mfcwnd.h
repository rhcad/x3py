#ifndef X3_EXAMPLE_SIMPLE_IMPL_H
#define X3_EXAMPLE_SIMPLE_IMPL_H

#include <module/classmacro.h>
#include <mfcwnd/isimple.h>

class CSimpleWnd : public CWnd
{
public:
	CSimpleWnd();
    virtual ~CSimpleWnd();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

class CSimple : public ISimple
{
    X3BEGIN_CLASS_DECLARE(CSimple, clsidSimple)
        X3DEFINE_INTERFACE_ENTRY(ISimple)
    X3END_CLASS_DECLARE()
protected:
    CSimple();
    virtual ~CSimple();

private:
    virtual bool createWnd(size_t hparent, int id);
    virtual size_t getHandle() const;
    virtual void showMessage();

private:
    CSimpleWnd*     m_pwnd;
};

#endif