#ifndef _5C4810B8_B9ED_41C8_87BF_8059E55BC0A3_H_
#define _5C4810B8_B9ED_41C8_87BF_8059E55BC0A3_H_

#include <WinDef.h>
#include "../GRender/RenderDef.h"

class STImage
{
public:
    STImage()
    {
        hBitmap = NULL;
        pData = NULL;
        iWidth = iHeight = 0;
        bHasAlphaChannel = false;
    }

    virtual ~STImage()
    {
        if (hBitmap)
        {
            ::DeleteObject(hBitmap);
            hBitmap = NULL;
        }
    }

public:
    HBITMAP hBitmap;
    unsigned char* pData;
    int iWidth;
    int iHeight;
    bool bHasAlphaChannel;
};

#endif // _5C4810B8_B9ED_41C8_87BF_8059E55BC0A3_H_
