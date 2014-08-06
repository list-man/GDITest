#include "stdafx.h"
#include "BitmapHelper.h"
#include "../wtl81/atlapp.h"

namespace glib
{
    HRESULT CBitmapHelper::CreateBitmap32(int _iWidth, int _iHeight,
                                    HBITMAP& _hBitmap, unsigned char** _pData,
                                    bool _bAlpha, unsigned char _cAlpha)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            int iSize = _iWidth * _iHeight * 4;
            if (iSize <= 0) break;

            BITMAPINFO bi;
            memset(&bi, 0, sizeof(bi));
            bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
            bi.bmiHeader.biWidth = _iWidth;
            bi.bmiHeader.biHeight = -_iHeight;
            bi.bmiHeader.biPlanes = 1;
            bi.bmiHeader.biBitCount = 32;
            bi.bmiHeader.biCompression = BI_RGB;
            bi.bmiHeader.biSizeImage = iSize;

            WTL::CClientDC dc(NULL);
            void* pBits = NULL;
            _hBitmap = ::CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &pBits,
                NULL, 0);

            if (!_hBitmap) break;

            if (pBits && _bAlpha)
            {
                int iPixels = _iWidth * _iHeight;
                for (int i = 0; i < iPixels; i++)
                {
                    DWORD* pPixel = (DWORD*)pBits + i;
                    *pPixel = (_cAlpha << 24);
                }
            }

            hResult = S_OK;

            if (_pData)
            {
                *_pData = (unsigned char*)pBits;
            }

        } while (false);

        return hResult;
    }

}
