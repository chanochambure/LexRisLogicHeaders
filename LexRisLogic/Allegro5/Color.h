/* Color.h -- Color Allegro 5 Header - LexRis Logic Headers

    Copyright (c) 2016 LexRisLogic

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

#ifndef INCLUDED_LL_AL5_COLOR_H
#define INCLUDED_LL_AL5_COLOR_H

namespace LL_AL5
{
    struct Color
    {
        Color(unsigned char new_red=0,unsigned char new_green=0,unsigned char new_blue=0,unsigned char new_alpha=255)
        {
            red=new_red;
            green=new_green;
            blue=new_blue;
            alpha=new_alpha;
        }
        Color(ALLEGRO_COLOR color)
        {
            red=(color.r*255);
            green=(color.g*255);
            blue=(color.b*255);
            alpha=(color.a*255);
        }
        unsigned char red=0;
        unsigned char green=0;
        unsigned char blue=0;
        unsigned char alpha=255;
        Color operator ! ()
        {
            return Color(255-red,255-green,255-blue,alpha);
        }
        Color operator = (ALLEGRO_COLOR another_color)
        {
            red=(another_color.r*255);
            green=(another_color.g*255);
            blue=(another_color.b*255);
            alpha=(another_color.a*255);
            return (*this);
        }
        bool operator == (Color another_color)
        {
            return (another_color.red==red and another_color.green==green and
                    another_color.blue==blue and another_color.alpha==alpha);
        }
        bool operator != (Color another_color)
        {
            return (another_color.red!=red or another_color.green!=green or
                    another_color.blue!=blue or another_color.alpha!=alpha);
        }
        operator ALLEGRO_COLOR()
        {
            return al_map_rgba(red,green,blue,alpha);
        }
    };
}

#endif // INCLUDED_LL_AL5_COLOR_H
