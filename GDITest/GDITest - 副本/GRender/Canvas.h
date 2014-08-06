#ifndef _AD7E36D9_C821_4AF4_A564_F2F4D0DE2960_H_
#define _AD7E36D9_C821_4AF4_A564_F2F4D0DE2960_H_

namespace glib
{
    template <bool t_bManaged>
    class CanvasT
    {
    public:
#ifdef WIN32
        CanvasT(HWND _hWnd, HDC _hDC) :
          m_hWnd(_hWnd), m_hDC(_hDC), 
          m_iWidth(0), m_iHeight(0)
          {
          }

          virtual ~CanvasT()
          {
              if (t_bManaged)
              {
                  ::ReleaseDC(m_hWnd, m_hDC);
              }
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

    //typedef CanvasT<false> CanvasHandle;
    typedef CanvasT<false>  Canvas;
}

#endif // _AD7E36D9_C821_4AF4_A564_F2F4D0DE2960_H_
