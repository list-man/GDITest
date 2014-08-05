#ifndef _CA3819AE_1495_47FE_A935_01BB00F5653A_H_
#define _CA3819AE_1495_47FE_A935_01BB00F5653A_H_

namespace glib
{
    class CBitmapHelper
    {
    public:
        static HRESULT CreateBitmap32(int _iWidth, int _iHeight, 
                                HBITMAP& _hBitmap, unsigned char** _pData,
                                bool _bAlpha, unsigned char _cAlpha);
    };
}

#endif // _CA3819AE_1495_47FE_A935_01BB00F5653A_H_
