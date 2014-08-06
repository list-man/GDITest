#include "stdafx.h"
#include "Render_GDI.h"
#include "../../wtl81/atlapp.h"

#ifdef WIN32

HRESULT DrawImage(HDC _hDC, HBITMAP& _hBitmap, bool _bAlpha, 
                    const CRect& _rcDest, const CRect& _rcSrc)
{
    HRESULT hResult = S_FALSE;

    do 
    {
        if (_bAlpha)
        {
            hResult = DrawAlphaBitmap(_hDC, _hBitmap, _rcDest, _rcSrc);
        }
        else
        {
            hResult = DrawOpaqueBitmap(_hDC, _hBitmap, _rcDest, _rcSrc);
        }

    } while (false);

    return hResult;
}

HRESULT DrawOpaqueBitmap(HDC _hDC, HBITMAP& _hBitmap, 
                        const CRect& _rcDest, const CRect& _rcSrc)
{
    HRESULT hResult = S_FALSE;

    do 
    {
        CDC dcMem;
        dcMem.CreateCompatibleDC(_hDC);
        dcMem.SelectBitmap(_hBitmap);
        BOOL bResult = ::BitBlt(_hDC, 
                            _rcDest.left, _rcDest.top, _rcDest.Width(), _rcDest.Height(),
                            dcMem,
                            _rcSrc.left, _rcSrc.top, 
                            SRCCOPY);

        hResult = TRUE == bResult 
                    ? S_OK:E_FAIL;

    } while (false);

    return hResult;
}

HRESULT DrawAlphaBitmap(HDC _hDC, HBITMAP& _hBitmap, 
                        const CRect& _rcDest, const CRect& _rcSrc)
{
    HRESULT hResult = S_FALSE;

    do 
    {
        BLENDFUNCTION bf = {0};
        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.SourceConstantAlpha = 0xFF;
        bf.AlphaFormat = AC_SRC_ALPHA;

        CDC dcMem;
        dcMem.CreateCompatibleDC(_hDC);
        dcMem.SelectBitmap(_hBitmap);

        BOOL bResult = AlphaBlend(_hDC,
            _rcDest.left, _rcDest.top, _rcDest.Width(), _rcDest.Height(),
            dcMem, 
            _rcSrc.left, _rcSrc.top, _rcSrc.Width(), _rcSrc.Height(),
            bf);

        hResult = TRUE == bResult 
                    ? S_OK:E_FAIL;

    } while (false);

    return hResult;
}

#endif
