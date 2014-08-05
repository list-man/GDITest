#include "stdafx.h"
#include "ImageHelper.h"
#include "BitmapHelper.h"

// 使用第三方图片绘制类库stbi
extern "C"
{
    extern unsigned char *stbi_load_from_memory( unsigned char const *buffer, int len, int *x, int *y,
        int *comp, int req_comp );
    extern void     stbi_image_free( void *retval_from_stbi_load );

};

namespace glib
{
    HRESULT CImageHelper::LoadImage(const wchar_t* _pFilePath, STImage& _stImage)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            FILE* pFile = NULL;
            if (0 != _wfopen_s(&pFile, _pFilePath, L"rb")) break;

            fseek(pFile, 0, SEEK_END);
            long lFileLen = ftell(pFile);
            fseek(pFile, 0, SEEK_SET);

            unsigned char* pBuffer = new unsigned char[lFileLen];
            if (!pBuffer)
            {
                fclose(pFile);
                break;
            };

            for (int i = 0; i < lFileLen; i++)
            {
                fread(pBuffer+i, 1, 1, pFile);
            }

            fclose(pFile);

            hResult = CImageHelper::LoadImage(pBuffer, lFileLen, _stImage);

            delete[] pBuffer;

        } while (false);

        return hResult;
    }

    HRESULT CImageHelper::LoadImage(unsigned char* _pData, int _iLen, STImage& _stImage)
    {
        HRESULT hResult = E_FAIL;

        do 
        {
            if (!_pData || _iLen <= 0)
            {
                hResult = S_FALSE;
                break;
            }

            int comp = 0;
            unsigned char* pImage = stbi_load_from_memory(_pData, 
                _iLen, 
                &_stImage.iWidth, 
                &_stImage.iHeight, 
                &comp, 
                4);

            if (!pImage) break;

            hResult = CBitmapHelper::CreateBitmap32(_stImage.iWidth, 
                _stImage.iHeight, 
                _stImage.hBitmap, 
                &_stImage.pData,
                true, 0xFF);

            int iPixelCnts = _stImage.iWidth * _stImage.iHeight;
            for (int i = 0; i < iPixelCnts; i++)
            {
                unsigned char* pAlpha = (BYTE*)pImage + i * 4 + 3;
                if (*pAlpha < 0xFF)
                {
                    _stImage.pData[i * 4] = pImage[i * 4 + 2] * (*pAlpha) / 255;
                    _stImage.pData[i * 4 + 1] = pImage[i * 4 + 1] * (*pAlpha) / 255;
                    _stImage.pData[i * 4 + 2] = pImage[i * 4] * (*pAlpha) / 255;
                    _stImage.bHasAlphaChannel = true;
                }
                else
                {
                    _stImage.pData[i * 4] = pImage[i * 4 + 2];
                    _stImage.pData[i * 4 + 1] = pImage[i * 4 + 1];
                    _stImage.pData[i * 4 + 2] = pImage[i * 4];
                }
            }

            stbi_image_free(pImage);

        } while (false);

        return hResult;
    }

    HRESULT CImageHelper::CreateImage(int _iWidth, int _iHeight, 
                                    bool _bAlpha, unsigned char _cAlpha,
                                    STImage& _stImage)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            hResult = CBitmapHelper::CreateBitmap32(_iWidth, _iHeight, _stImage.hBitmap,
                &_stImage.pData, _bAlpha, _cAlpha);

            if (SUCCEEDED(hResult))
            {
                _stImage.iWidth = _iWidth;
                _stImage.iHeight = _iHeight;
                _stImage.bHasAlphaChannel = _bAlpha;
            }
            else
            {
                _stImage.hBitmap = NULL;
                _stImage.pData = NULL;
            }

        } while (false);

        return hResult;
    }
}
