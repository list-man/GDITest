#ifndef _3F92644F_69AA_49D7_90C4_F6265B399C75_H_
#define _3F92644F_69AA_49D7_90C4_F6265B399C75_H_

/*
Author: JayGuo.
Date:   2014/07/31
File:   ImageCacher.h
Desc:   image cacher.
*/

#include <memory>
#include <map>
#include "ImageDef.h"

namespace glib
{
    class CImageCacher
    {
    public:
        static CImageCacher* _Instance();
        virtual ~CImageCacher();

        std::shared_ptr<STImage> GetImage(const std::wstring& _strImage, bool _bLoadIfNotExist);
        std::shared_ptr<STImage> LoadImage(const std::wstring& _strImage, bool _bCache);
        HRESULT Add(const std::wstring& _strImage, std::shared_ptr<STImage> _spImage);
        HRESULT Remove(const std::wstring& _strImage);
    protected:
        CImageCacher(){}
        static CImageCacher* m_pImageCache;
    private:
        typedef std::map<std::wstring, std::shared_ptr<STImage>> MAP_IMAGE;
        MAP_IMAGE m_imageCache;
    };
}

#endif // _3F92644F_69AA_49D7_90C4_F6265B399C75_H_
