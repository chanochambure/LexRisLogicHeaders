/* Allegro5.h -- Allegro 5 Header - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so.

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of
    the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef INCLUDED_LL_AL5_H
#define INCLUDED_LL_AL5_H

#include "../LL_Shared.h"

#include <allegro5/allegro5.h>

namespace LL_AL5
{
    typedef float Type_pos;
    typedef unsigned int Type_display_size;

    extern LL_SHARED float bitmap_scale_x;
    extern LL_SHARED float bitmap_scale_y;
    extern LL_SHARED float text_scale;
    extern LL_SHARED float primitives_scale;
    extern LL_SHARED Type_display_size desktop_size_x;
    extern LL_SHARED Type_display_size desktop_size_y;

    void LL_SHARED init_allegro();
    void LL_SHARED sleep(float sleep_time);
}

#endif // INCLUDED_LL_AL5_H
