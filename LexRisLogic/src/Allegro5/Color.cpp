/* Color.cpp -- Color Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/Color.h"

namespace LL_AL5
{
    Color::Color(unsigned char new_red,unsigned char new_green,unsigned char new_blue,unsigned char new_alpha)
    {
        red=new_red;
        green=new_green;
        blue=new_blue;
        alpha=new_alpha;
    }
    Color::Color(ALLEGRO_COLOR color)
    {
        red=(color.r*255);
        green=(color.g*255);
        blue=(color.b*255);
        alpha=(color.a*255);
    }
    Color Color::operator ! ()
    {
        return Color(255-red,255-green,255-blue,alpha);
    }
    Color Color::operator = (ALLEGRO_COLOR another_color)
    {
        red=(another_color.r*255);
        green=(another_color.g*255);
        blue=(another_color.b*255);
        alpha=(another_color.a*255);
        return (*this);
    }
    bool Color::operator == (Color another_color)
    {
        return (another_color.red==red && another_color.green==green &&
                another_color.blue==blue && another_color.alpha==alpha);
    }
    bool Color::operator != (Color another_color)
    {
        return (another_color.red!=red || another_color.green!=green ||
                another_color.blue!=blue || another_color.alpha!=alpha);
    }
    Color::operator ALLEGRO_COLOR()
    {
        return al_map_rgba(red,green,blue,alpha);
    }
}
