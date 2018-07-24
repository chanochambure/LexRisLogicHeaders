/* Text.cpp -- Text Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/Text.h"

namespace LL_AL5
{
    bool LL_SHARED text_addon()
    {
        return al_init_font_addon()and al_init_ttf_addon();
    }

    void Font::set_path(std::string new_font_path)
    {
        _V_font_path=new_font_path;
    }
    std::string Font::get_path()
    {
        return _V_font_path;
    }
    bool Font::set_size(float new_size)
    {
        if(new_size>0.0 and !_V_font)
        {
            _V_size=new_size;
            return true;
        }
        return false;
    }
    float Font::get_size()
    {
        return _V_size;
    }
    bool Font::load_ttf_font()
    {
        destroy();
        _V_font=al_load_ttf_font(_V_font_path.c_str(),_V_size*text_scale,0);
        return bool(_V_font);
    }
    bool Font::load_ttf_font_for_another_target()
    {
        destroy();
        _V_font=al_load_ttf_font(_V_font_path.c_str(),_V_size,0);
        return bool(_V_font);
    }
    bool Font::destroy()
    {
        if(_V_font)
        {
            al_destroy_font(_V_font);
            _V_font=nullptr;
            return true;
        }
        return false;
    }
    Font::operator ALLEGRO_FONT* ()
    {
        return _V_font;
    }
    Font::~Font()
    {
        destroy();
    }

    void Text::set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
    {
        _V_pos_x=new_pos_x;
        _V_pos_y=new_pos_y;
    }
    void Text::set_pos_x(Type_pos new_pos_x)
    {
        _V_pos_x=new_pos_x;
    }
    Type_pos Text::get_pos_x()
    {
        return _V_pos_x;
    }
    void Text::set_pos_y(Type_pos new_pos_y)
    {
        _V_pos_y=new_pos_y;
    }
    Type_pos Text::get_pos_y()
    {
        return _V_pos_y;
    }
    void Text::set_flag(int new_flag)
    {
        _V_flag=new_flag;
    }
    void Text::set_color(ALLEGRO_COLOR new_color)
    {
        _V_color=new_color;
    }
    ALLEGRO_COLOR Text::get_color()
    {
        return _V_color;
    }
    void Text::set_font(Font* new_font)
    {
        _V_font=new_font;
    }
    Font* Text::get_font()
    {
        return _V_font;
    }
    void Text::draw()
    {
        al_draw_text(*_V_font,_V_color,_V_pos_x,_V_pos_y,_V_flag,_V_text.c_str());
    }
    const char* Text::operator = (const char* new_text)
    {
        _V_text=new_text;
        return new_text;
    }
    std::string Text::operator = (std::string new_text)
    {
        _V_text=new_text;
        return new_text;
    }
    Text::operator const char* ()
    {
        return _V_text.c_str();
    }
    Text::operator std::string ()
    {
        return _V_text;
    }
}
