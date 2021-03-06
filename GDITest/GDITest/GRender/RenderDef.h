#ifndef _F0B50B92_E7F8_4E1F_8269_9DA76E58655D_H_
#define _F0B50B92_E7F8_4E1F_8269_9DA76E58655D_H_

typedef enum tagENStretchMode
{
    kGSMNil,
    kGSMStretch,        //whole stretch 
    kGSMTile,           // tile mode.
    kGSMNineGrid,       // nine-grid stretch mode.
}ENStretchMode;

#define RGB(r, g, b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define ARGB(a, r, g, b) (RGB(r, g, b) | (DWORD)(a << 24 & 0xFF000000))

#endif // _F0B50B92_E7F8_4E1F_8269_9DA76E58655D_H_
