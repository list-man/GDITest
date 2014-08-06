#include "stdafx.h"
#include "ImageFilterParser.h"

namespace glib
{
    CImageFilter::CImageFilter(std::wstring& _strFilter)
    {
        _Parser(_strFilter);
    }

    CImageFilter::~CImageFilter()
    {

    }

    HRESULT CImageFilter::GetValue(const std::wstring& _strKey, RECT& _rcValue)
    {
        HRESULT hResult = E_FAIL;

        do 
        {
            MAP_FILTERS::const_iterator itr = m_filters.find(_strKey);
            if (itr == m_filters.end()) break;

            if (itr->second.enType != kVTRect) break;

            ::CopyRect(&_rcValue, &itr->second.unValue.rcValue);
            hResult = S_OK;

        } while (false);

        return hResult;
    }

    HRESULT CImageFilter::GetValue(const std::wstring& _strKey, int& _iValue)
    {
        HRESULT hResult = E_FAIL;

        do 
        {
            MAP_FILTERS::const_iterator itr = m_filters.find(_strKey);
            if (itr == m_filters.end()) break;

            if (itr->second.enType != kVTInt) break;

            _iValue = itr->second.unValue.iInt;
            hResult = S_OK;

        } while (false);

        return hResult;
    }

    HRESULT CImageFilter::GetValue(const std::wstring& _strKey, bool& _bValue)
    {
        HRESULT hResult = E_FAIL;

        do 
        {
            MAP_FILTERS::const_iterator itr = m_filters.find(_strKey);
            if (itr == m_filters.end()) break;

            if (itr->second.enType != kVTBoolean) break;

            _bValue = itr->second.unValue.bYes;
            hResult = S_OK;

        } while (false);

        return hResult;
    }

    HRESULT CImageFilter::GetValue(const std::wstring& _strKey, wchar_t** _ppValue)
    {
        HRESULT hResult = E_FAIL;

        do 
        {
            if (!_ppValue)
            {
                hResult = E_INVALIDARG;
                break;
            }

            MAP_FILTERS::const_iterator itr = m_filters.find(_strKey);
            if (itr == m_filters.end()) break;

            if (itr->second.enType != kVTString) break;

            *_ppValue = itr->second.unValue.pStr;
            hResult = S_OK;

        } while (false);

        return hResult;
    }

    HRESULT CImageFilter::GetValue(const std::wstring& _strKey, 
                        ENStretchMode& _enStretchMode)
    {
        HRESULT hResult = E_FAIL;

        do 
        {
            MAP_FILTERS::const_iterator itr = m_filters.find(_strKey);
            if (itr == m_filters.end()) break;

            if (itr->second.enType != kVTInt) break;

            _enStretchMode = (ENStretchMode)itr->second.unValue.iInt;
            hResult = S_OK;

        } while (false);

        return hResult;
    }

    //////////////////////////////////////////////////////////////////////////
    // protected.
    HRESULT CImageFilter::_Parser(std::wstring& _strFilter)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            m_strRawString = _strFilter;
            m_filters.clear();

            wchar_t* pSrcContext = (wchar_t*)_strFilter.c_str();
            wchar_t* pDelimiter = L" ;";
            wchar_t* pContext = NULL;
            wchar_t* pToken = wcstok_s(pSrcContext, pDelimiter, &pContext);
            while (pToken)
            {
                hResult = _ParseItem(std::wstring(pToken));
                pToken = wcstok_s(NULL, pDelimiter, &pContext);
            }

        } while (false);

        return hResult;
    }

    HRESULT CImageFilter::_ParseItem(std::wstring& _strPair)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            wchar_t* pSrcContext = (wchar_t*)_strPair.c_str();
            wchar_t* pDelimieter = L"=";
            wchar_t* pNextToken = NULL;
            wchar_t* pToken = wcstok_s(pSrcContext, pDelimieter, &pNextToken);
            if (!pToken || !pNextToken) break;

            if (0 == wcscmp(pToken, L"file"))
            {
                _MakeStrPair(pToken, pNextToken);
            }
            else if (0 == wcscmp(pToken, L"source"))
            {

            }
            else if (0 == wcscmp(pToken, L"dest"))
            {

            }
            else if (0 == wcscmp(pToken, L"hole"))
            {

            }
            else if (0 == wcscmp(pToken, L"stretch"))
            {

            }
            else if (0 == wcscmp(pToken, L"nineGrid"))
            {

            }
            else if (0 == wcscmp(pToken, L"mask"))
            {

            }

        } while (false);

        return hResult;
    }

    HRESULT CImageFilter::_MakeStrPair(const std::wstring& _strKey, 
        const std::wstring& _strValue)
    {
        HRESULT hResult = S_FALSE;

        do 
        {
            if (_strKey.size() <= 0) break;

            wchar_t* pValue = new wchar_t[_strValue.size() + 1];
            if (!pValue)
            {
                hResult = E_FAIL;
                break;
            }

            wcscpy_s(pValue, _strValue.size() + 1, (wchar_t*)_strValue.c_str());
            *(pValue + _strValue.size()) = L'\x0';

            STFilterValue stFV;
            stFV.enType = kVTString;
            stFV.unValue.pStr = pValue;
            m_filters.insert(std::make_pair(_strKey, stFV));

        } while (false);

        return hResult;
    }
}
