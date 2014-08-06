#ifndef _AD7E36D9_C821_4AF4_A564_F2F4D0DE2960_H_
#define _AD7E36D9_C821_4AF4_A564_F2F4D0DE2960_H_

namespace glib
{
    class Canvas
    {
    public:
#ifdef WIN32
        Canvas(HDC _hDC, int _iWidth, int _iHeight) :
          m_hDC(_hDC), 
          m_iWidth(_iWidth),
          m_iHeight(_iHeight)
          {
          }

          virtual ~Canvas()
          {
          }

          operator HDC() const { return m_hDC; }

#endif
        int GetWidth() { return m_iWidth; }
        int GetHeight(){ return m_iHeight; }
    private:

#ifdef WIN32
        HWND m_hWnd;
        HDC m_hDC;
#endif

        int m_iWidth;
        int m_iHeight;
    };
}

#endif // _AD7E36D9_C821_4AF4_A564_F2F4D0DE2960_H_
