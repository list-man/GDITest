#include "stdafx.h"
#include "MainFrame.h"
#include "./wtl81/atlapp.h"
#include "./GRender/GRender.h"
#include "./ImageLoader/BitmapHelper.h"

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{

}

LRESULT CMainFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    ::PostQuitMessage(0);
    return 0;
}

LRESULT CMainFrame::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    {
        CPaintDC dc(m_hWnd);
    }

    CClientDC dc(m_hWnd);
    CRect rcClient;
    GetClientRect(&rcClient);
    CMemoryDC dcMem(dc, rcClient);

    HBITMAP hBitmap = NULL;
    unsigned char* pData = NULL;
    glib::CBitmapHelper::CreateBitmap32(rcClient.Width(), rcClient.Height(), hBitmap,
        &pData, true, 0xFF);
    dcMem.SelectBitmap(hBitmap);
/*
    {
        HBITMAP hBitmap1 = NULL;
        unsigned char* pData1 = NULL;
        glib::CBitmapHelper::CreateBitmap32(rcClient.Width(), rcClient.Height(), hBitmap1,
            &pData1, true, 0xFF);

        CDC dc1;
        dc1.CreateCompatibleDC(dcMem);
        dc1.SelectBitmap(hBitmap1);
        dc1.FillSolidRect(rcClient, RGB(0xFF, 0, 0));

        ::BitBlt(dcMem, 0, 0, rcClient.Width(), rcClient.Height(), dc1, 0, 0, SRCCOPY);
        ::DeleteObject(hBitmap1);
    }
*/
    // BitBlt不会把像素拷贝到选中的位图中去？上面的实验证明不是的，那是为什么呢？
    //dcMem.FillSolidRect(rcClient, RGB(0xFF, 0, 0xFF));
    glib::Canvas canvas(dcMem, rcClient.Width(), rcClient.Height());
    glib::GRender::FillRect(canvas, rcClient, RGB(0xFF, 0x00, 0xFF));
    //glib::GRender::RenderImage(, rcClient, L"file=bkgnd.png");

    ::DeleteObject(hBitmap);

    return 0;
}
