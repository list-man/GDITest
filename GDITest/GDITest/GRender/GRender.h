#ifndef _FCAECFAF_0C85_4E2B_A5AA_60538433FD88_H_
#define _FCAECFAF_0C85_4E2B_A5AA_60538433FD88_H_

#include <Uxtheme.h>
#include <memory>
#include "./Canvas.h"
#include "../ImageLoader/ImageDef.h"

namespace glib
{
    class CImageFilter;

    class GRender
    {
    public:
        /*
        * @brief: draw image.
        * @_strImage: contains many filters.
                    @file:      image to be loaded.
                    @source:    source rectangle.
                    @dest:      destination rectangle.
                    @stretch:   the stretch mode to use: stretch, tile, nine-grid
                    @mask:      to do.
                    @hole:      keep hole or not.
                    @nineGrid:  the nine-grid rectangle.
        */
        static HRESULT RenderImage(Canvas _canvas, const CRect& _rcDest, const std::wstring& _strImage);
        static HRESULT RenderImage(Canvas _canvas, const CRect& _rcDest, 
                            std::shared_ptr<STImage> _spImage, 
                            CImageFilter& _filter);
        static HRESULT RenderImageStretch(Canvas _canvas, std::shared_ptr<STImage> _spImage, 
                            const CRect& _rcDest, const CRect& _rcSrc,
                            ENStretchMode _eStretchMode, const MARGINS& _margins);
    };
}

#endif // _FCAECFAF_0C85_4E2B_A5AA_60538433FD88_H_
