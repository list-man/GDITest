#include "stdafx.h"
#include "ImageCacher.h"
#include "./ImageHelper.h"

namespace glib
{
    CImageCacher* CImageCacher::m_pImageCache = NULL;

    CImageCacher* CImageCacher::_Instance()
    {
        if (!m_pImageCache)
        {
            m_pImageCache = new CImageCacher();
        }

        return m_pImageCache;
    }

    CImageCacher::~CImageCacher()
    {

    }

    std::shared_ptr<STImage> CImageCacher::GetImage(const std::wstring& _strImage,
                                                    bool _bLoadIfNotExist)
    {
        std::shared_ptr<STImage> spResult;

        wchar_t szPath[_MAX_PATH] = {0};
        GetModuleFileName(NULL, szPath, _MAX_PATH);
        PathRemoveFileSpec(szPath);
        PathAppend(szPath, _strImage.c_str());

        do 
        {
            MAP_IMAGE::const_iterator itrFind = m_imageCache.find(_strImage);
            if (itrFind != m_imageCache.end())
            {
                spResult = itrFind->second;
            }
            else
            {
                if (!_bLoadIfNotExist) break;

                spResult = LoadImage(szPath, true);
            }

        } while (false);

        return spResult;
    }

    std::shared_ptr<STImage> CImageCacher::LoadImage(const std::wstring& _strImage,
        bool _bCache)
    {
        std::shared_ptr<STImage> spResult;

        do 
        {
            std::shared_ptr<STImage> spImage = std::make_shared<STImage>();
            if (FAILED(CImageHelper::LoadImage(_strImage.c_str(), *spImage.get())))
            {
                break;
            }

            spResult = spImage;

            if (_bCache)
            {
                Add(_strImage, spImage);
            }

        } while (false);

        return spResult;
    }

    HRESULT CImageCacher::Add(const std::wstring& _strImage, 
        std::shared_ptr<STImage> _spImage)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            if (_strImage.size() <= 0) break;

            m_imageCache[_strImage] = _spImage;
            hResult = S_OK;

        } while (false);

        return hResult;
    }

    HRESULT CImageCacher::Remove(const std::wstring& _strImage)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            MAP_IMAGE::const_iterator itrFind = m_imageCache.find(_strImage);
            if (itrFind == m_imageCache.end()) break;

            m_imageCache.erase(itrFind);
            hResult = S_OK;

        } while (false);

        return hResult;
    }
}
