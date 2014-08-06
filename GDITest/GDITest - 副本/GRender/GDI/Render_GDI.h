#ifndef _464B97AB_A24F_4D34_9C8A_9C808CE0A608_H_
#define _464B97AB_A24F_4D34_9C8A_9C808CE0A608_H_

#include "../RenderDef.h"

#ifdef WIN32
HRESULT DrawImage(HDC _hDC, HBITMAP& _hBitmap, bool _bAlpha, const CRect& _rcDest, const CRect& _rcSrc);
HRESULT DrawOpaqueBitmap(HDC _hDC, HBITMAP& _hBitmap, const CRect& _rcDest, const CRect& _rcSrc);
HRESULT DrawAlphaBitmap(HDC _hDC, HBITMAP& _hBitmap, const CRect& _rcDest, const CRect& _rcSrc);

#endif

#endif // _464B97AB_A24F_4D34_9C8A_9C808CE0A608_H_
