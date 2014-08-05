#ifndef _24554786_499C_40CD_A683_417E169E1789_H_
#define _24554786_499C_40CD_A683_417E169E1789_H_

#include "ImageDef.h"

namespace glib
{
    class CImageHelper
    {
    public:
        static HRESULT LoadImage(const wchar_t* _pFilePath, STImage& _stImage);
        static HRESULT LoadImage(unsigned char* _pData, INT _iLen, STImage& _stImage);
        static HRESULT CreateImage(int _iWidth, int _iHeight, bool _bAlpha, unsigned char _cAlpha, STImage& _stImage);
    };
}

#endif // _24554786_499C_40CD_A683_417E169E1789_H_
