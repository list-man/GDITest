#ifndef _9EF9A3E0_BC09_4C49_B835_BE8419EB1CCD_H_
#define _9EF9A3E0_BC09_4C49_B835_BE8419EB1CCD_H_

#include <map>
#include <atltypes.h>
#include "../ImageLoader/ImageDef.h"

class CRect;

namespace glib
{
    class CImageFilter
    {
        typedef enum tabENValueType
        {
            kVTNil,
            kVTRect,
            kVTInt,
            kVTBoolean,
            kVTString,
        }ENValueType;

        typedef struct tagSTFilterValue
        {
            ENValueType enType;
            union FilterValue
            {
                RECT rcValue;
                int iInt;
                bool bYes;
                wchar_t* pStr;
            }unValue;

            struct tagSTFilterValue()
            {
                enType = kVTNil;
            };

            tagSTFilterValue operator=(const tagSTFilterValue& _val)
            {
                this->enType = _val.enType;
                switch (this->enType)
                {
                case kVTString:
                    if (_val.unValue.pStr)
                    {
                        this->unValue.pStr = _wcsdup(_val.unValue.pStr);
                    }
                    break;
                case kVTBoolean:
                    this->unValue.bYes = _val.unValue.bYes;
                    break;
                case kVTInt:
                    this->unValue.iInt = _val.unValue.iInt;
                    break;
                case kVTRect:
                    ::CopyRect(&this->unValue.rcValue, &_val.unValue.rcValue);
                    break;
                default:
                    break;
                }
            }

        }STFilterValue;

    public:
        explicit CImageFilter(std::wstring& _strFilter);
        virtual ~CImageFilter();

        HRESULT GetValue(const std::wstring& _strKey, RECT& _rcValue);
        HRESULT GetValue(const std::wstring& _strKey, int& _iValue);
        HRESULT GetValue(const std::wstring& _strKey, bool& _bValue);
        HRESULT GetValue(const std::wstring& _strKey, wchar_t** _ppValue);
        HRESULT GetValue(const std::wstring& _strKey, ENStretchMode& _enStretchMode);
    protected:
        HRESULT _Parser(std::wstring& _strFilter);
        HRESULT _ParseItem(std::wstring& _strPair);
        HRESULT _MakeStrPair(const std::wstring& _strKey, const std::wstring& _strValue);
    private:

        typedef std::map<std::wstring, STFilterValue> MAP_FILTERS;
        MAP_FILTERS m_filters;

        std::wstring m_strRawString;
    };
}

#endif // _9EF9A3E0_BC09_4C49_B835_BE8419EB1CCD_H_
