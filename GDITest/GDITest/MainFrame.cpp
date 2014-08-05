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

    dcMem.FillSolidRect(rcClient, RGB(0xFF, 0xFF, 0xFF));
    glib::GRender::RenderImage(glib::CanvasT<false>(m_hWnd, dcMem), rcClient, L"file=bkgnd.png");

    ::DeleteObject(hBitmap);

    return 0;
}
