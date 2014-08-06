#ifndef _002BCF46_432F_4C28_B8B4_A9C6D0D43FFB_H_
#define _002BCF46_432F_4C28_B8B4_A9C6D0D43FFB_H_

class CMainFrame : 
            public CWindowImpl<CMainFrame>
{
public:
    CMainFrame();
    virtual ~CMainFrame();

    DECLARE_WND_CLASS(L"MainFrame")
    BEGIN_MSG_MAP(CMainFrame)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
};

#endif // _002BCF46_432F_4C28_B8B4_A9C6D0D43FFB_H_
