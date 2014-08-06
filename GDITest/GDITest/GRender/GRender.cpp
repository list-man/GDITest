#include "stdafx.h"
#include "GRender.h"
#include "../wtl81/atlapp.h"
#include "../ImageLoader/ImageCacher.h"
#include "./ImageFilterParser.h"
#include "../ImageLoader/ImageHelper.h"
#include "../ImageLoader/BitmapHelper.h"

#ifdef WIN32
#include "./GDI/Render_GDI.h"
#endif

namespace glib
{
    HRESULT GRender::RenderImage(Canvas _canvas, const CRect& _rcDest, const std::wstring& _strImage)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            std::wstring strImage = _strImage;
            CImageFilter filter(strImage);

            wchar_t* pFile = NULL;
            if (FAILED(filter.GetValue(L"file", &pFile))
                || !pFile)
            {
                break;
            }

            std::shared_ptr<STImage> spImage = 
                CImageCacher::_Instance()->GetImage(pFile, true);

            hResult = GRender::RenderImage(_canvas, _rcDest, spImage, filter);

        } while (false);

        return hResult;
    }

    HRESULT GRender::RenderImage(Canvas _canvas, const CRect& _rcDest, std::shared_ptr<STImage> _spImage, 
        CImageFilter& _filter)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            if (!_spImage) break;

#ifdef WIN32

            CRect rcSource(0, 0, _spImage->iWidth, _spImage->iHeight);
            CRect rcDest = _rcDest;
            _filter.GetValue(L"source", rcSource);
            _filter.GetValue(L"dest", rcDest);
            ENStretchMode eStretchMode =  kGSMTile;
            _filter.GetValue(L"stretch", eStretchMode);
            MARGINS margins = {0};
            RenderImageStretch(_canvas, _spImage, _rcDest, rcSource,
                eStretchMode, margins);


#endif
        } while (false);

        return hResult;
    }

    HRESULT GRender::RenderImageStretch(Canvas _canvas, std::shared_ptr<STImage> _spImage, 
        const CRect& _rcDest, const CRect& _rcSrc,
        ENStretchMode _eStretchMode, const MARGINS& _margins)
    {
        HRESULT hResult = S_OK;

        if (kGSMTile == _eStretchMode)
        {
            for (int h = 0; h < _rcDest.Width(); h += _rcSrc.Width())
            {
                for (int v = 0; v < _rcDest.Height(); v += _rcSrc.Height())
                {
                    DrawImage((HDC)_canvas, _spImage->hBitmap, _spImage->bHasAlphaChannel,
                        CRect(h, v, h + _rcSrc.Width(), v + _rcSrc.Height()),
                        _rcSrc);
                }
            }
        }
        else if (kGSMStretch == _eStretchMode)
        {
            DrawImage((HDC)_canvas, _spImage->hBitmap, _spImage->bHasAlphaChannel,
                        _rcDest, _rcSrc);
        }
        else if (kGSMNineGrid == _eStretchMode)
        {
            MARGINS margins = {0};
            //left-top.
            RenderImageStretch(_canvas, _spImage, 
                        CRect(_rcDest.left, _rcDest.top, _rcDest.left + _margins.cxLeftWidth, _rcDest.top + _margins.cyTopHeight),
                        CRect(0, 0, _margins.cxLeftWidth, _margins.cyTopHeight),
                        kGSMNil, margins);

            // right-top.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.right - _margins.cxRightWidth, _rcDest.top, _rcDest.right, _rcDest.top + _margins.cyTopHeight),
                CRect(_rcSrc.right - _margins.cxRightWidth, 0, _rcSrc.right, _margins.cyTopHeight),
                kGSMNil, margins);

            // left-bottom.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.left, _rcDest.bottom - _margins.cyBottomHeight, _rcDest.left + _margins.cxLeftWidth, _rcDest.bottom),
                CRect(0, _rcSrc.bottom - _margins.cyBottomHeight, _margins.cxLeftWidth, _rcSrc.bottom),
                kGSMNil, margins);

            // right-bottom.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.right - _margins.cxRightWidth, _rcDest.bottom - _margins.cyBottomHeight, _rcDest.right, _rcDest.bottom),
                CRect(_rcSrc.right - _margins.cxRightWidth, _rcSrc.bottom - _margins.cyBottomHeight, _rcSrc.right, _rcSrc.bottom),
                kGSMNil, margins);

            // left-side.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.left, _rcDest.top + _margins.cyTopHeight, _margins.cxLeftWidth, _rcDest.bottom - _margins.cyBottomHeight),
                CRect(_rcSrc.left, _rcSrc.top + _margins.cyTopHeight, _margins.cxLeftWidth, _rcSrc.bottom - _margins.cyBottomHeight),
                kGSMStretch, margins);

            // top-side.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.left + _margins.cxLeftWidth, _rcDest.top, _rcDest.right - _margins.cxRightWidth, _rcDest.top + _margins.cyTopHeight),
                CRect(_rcSrc.left + _margins.cxLeftWidth, _rcSrc.top, _rcSrc.right - _margins.cxRightWidth, _rcSrc.top + _margins.cyTopHeight),
                kGSMStretch, margins);

            // right-side.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.right - _margins.cxRightWidth, _rcDest.top + _margins.cyTopHeight, _rcDest.right, _rcDest.bottom - _margins.cyBottomHeight),
                CRect(_rcSrc.right - _margins.cxRightWidth, _rcSrc.top + _margins.cyTopHeight, _rcSrc.right, _rcSrc.bottom - _margins.cyBottomHeight),
                kGSMStretch, margins);

            // bottom-side.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.left + _margins.cxLeftWidth, _rcDest.bottom - _margins.cyBottomHeight, _rcDest.right - _margins.cxRightWidth, _rcDest.bottom),
                CRect(_rcSrc.left + _margins.cxLeftWidth, _rcSrc.bottom - _margins.cyBottomHeight, _rcSrc.right - _margins.cxRightWidth, _rcSrc.bottom),
                kGSMStretch, margins);

            // center.
            RenderImageStretch(_canvas, _spImage, 
                CRect(_rcDest.left + _margins.cxLeftWidth, _rcDest.top + _margins.cyTopHeight, _rcDest.right - _margins.cxRightWidth, _rcDest.bottom - _margins.cyBottomHeight),
                CRect(_rcSrc.left + _margins.cxLeftWidth, _rcSrc.top + _margins.cyTopHeight, _rcSrc.right - _margins.cxRightWidth, _rcSrc.bottom - _margins.cyBottomHeight),
                kGSMStretch, margins);
        }
        else if (kGSMNil == _eStretchMode)
        {
            DrawImage((HDC)_canvas, _spImage->hBitmap, _spImage->bHasAlphaChannel,
                CRect(_rcDest.left, _rcDest.top, _rcDest.left + _rcSrc.Width(), _rcDest.top + _rcSrc.Height()),
                _rcSrc);
        }

        return hResult;
    }

    HRESULT GRender::FillRect(Canvas _canvas, const CRect& _rcDest, DWORD _dwClr)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            HBITMAP hBitmap = NULL;
            unsigned char* pData = NULL;
            CBitmapHelper::CreateBitmap32(_rcDest.Width(), _rcDest.Height(),
                hBitmap, &pData, true, ((_dwClr >> 24) & 0xFF));

            if (!hBitmap) break;

            CDC dc;
            dc.CreateCompatibleDC(_canvas);
            HBITMAP hBmpOld = dc.SelectBitmap(hBitmap);

            HBRUSH hBrush = ::CreateSolidBrush(_dwClr);
            ::FillRect(dc, &_rcDest, hBrush);
            ::DeleteObject(hBrush);

            BYTE cAlphaValue = (_dwClr >> 24) & 0xFF;
            if (cAlphaValue != 0)
            {
                for (int i = 0; i < _rcDest.Width() * _rcDest.Height(); i++)
                {
                    BYTE* pPixel = (BYTE*)((DWORD*)pData) + i;
                    pPixel[3] = cAlphaValue;
                    pPixel[0] = pPixel[0] * cAlphaValue / 255;
                    pPixel[1] = pPixel[1] * cAlphaValue / 255;
                    pPixel[2] = pPixel[2] * cAlphaValue / 255;
                }
            }

            //dc.SelectBitmap(hBmpOld);

            BITMAP bi = {0};
            GetObject(hBitmap, sizeof(bi), &bi);
            DrawImage(_canvas, hBitmap, cAlphaValue!=0, _rcDest, _rcDest);
            ::DeleteObject(hBitmap);
        } while (false);

        return hResult;
    }

}
