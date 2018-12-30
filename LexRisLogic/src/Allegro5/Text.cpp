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
        return al_init_image_addon() && al_init_font_addon() && al_init_ttf_addon();
    }

    void FontConfiguration::add_range(int begin,int end)
    {
        _V_ranges.push_back(std::min(begin,end));
        _V_ranges.push_back(std::max(begin,end));
    }
    unsigned int FontConfiguration::size() const
    {
        return _V_ranges.size()/2;
    }
    void FontConfiguration::clear()
    {
        _V_ranges.clear();
    }
    void FontConfiguration::set_scale(float new_text_scale_x,float new_text_scale_y)
    {
        _V_text_scale_x=new_text_scale_x;
        _V_text_scale_y=new_text_scale_y;
    }
    void FontConfiguration::set_scale_x(float new_text_scale_x)
    {
        _V_text_scale_x=new_text_scale_x;
    }
    void FontConfiguration::set_scale_y(float new_text_scale_y)
    {
        _V_text_scale_y=new_text_scale_y;
    }
    float FontConfiguration::get_scale_x() const
    {
        return _V_text_scale_x;
    }
    float FontConfiguration::get_scale_y() const
    {
        return _V_text_scale_y;
    }

    bool Font::_F_load_bitmap_font(const FontConfiguration& configuration,float bmp_scale_x,float bmp_scale_y)
    {
        ALLEGRO_BITMAP* bitmap=al_load_bitmap(_V_font_path.c_str());
        if(bitmap)
        {
            ALLEGRO_BITMAP* resize_bitmap=_F_resize_bitmap(bitmap,bmp_scale_x,bmp_scale_y);
            if(resize_bitmap)
            {
                _V_font=al_grab_font_from_bitmap(resize_bitmap,configuration.size(),(&(configuration._V_ranges[0])));
                al_destroy_bitmap(resize_bitmap);
            }
            al_destroy_bitmap(bitmap);
        }
        return _V_font;
    }
    ALLEGRO_BITMAP* Font::_F_resize_bitmap(ALLEGRO_BITMAP* bitmap,float bmp_scale_x,float bmp_scale_y)
    {
        int w=al_get_bitmap_width(bitmap)*bmp_scale_x;
        int h=al_get_bitmap_height(bitmap)*bmp_scale_y;
        ALLEGRO_BITMAP* resized_bmp=al_create_bitmap(w,h);
        if(!resized_bmp)
            return nullptr;
        ALLEGRO_BITMAP* prev_target=al_get_target_bitmap();
        al_set_target_bitmap(resized_bmp);
        al_draw_scaled_bitmap(bitmap,0,0,al_get_bitmap_width(bitmap),al_get_bitmap_height(bitmap),0,0,w, h,0);
        al_set_target_bitmap(prev_target);
        return resized_bmp;
    }
    Font::Font()
    {
    }
    void Font::set_path(std::string new_font_path)
    {
        _V_font_path=new_font_path;
    }
    std::string Font::get_path()
    {
        return _V_font_path;
    }
    int Font::get_height()
    {
        if(_V_font)
            return al_get_font_line_height(_V_font);
        return 0;
    }
    int Font::get_width(std::string text)
    {
        if(_V_font)
            return al_get_text_width(_V_font,text.c_str());
        return 0;
    }
    bool Font::load_bitmap_font(const FontConfiguration& configuration)
    {
        if(configuration.size() && !_V_font)
            return _F_load_bitmap_font(configuration,
                                       configuration.get_scale_x()*bitmap_scale_x,
                                       configuration.get_scale_y()*bitmap_scale_y);
        return false;
    }
    bool Font::load_bitmap_font_for_another_target(const FontConfiguration& configuration)
    {
        if(configuration.size() && !_V_font)
            return _F_load_bitmap_font(configuration,configuration.get_scale_x(),configuration.get_scale_y());
        return false;
    }
    bool Font::load_ttf_font(float size)
    {
        if(size > 0.0 && !_V_font)
            return (_V_font=al_load_font(_V_font_path.c_str(),size*text_scale,0));
        return false;
    }
    bool Font::load_ttf_font_for_another_target(float size)
    {
        if(size > 0.0 && !_V_font)
            return (_V_font=al_load_font(_V_font_path.c_str(),size,0));
        return false;
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
