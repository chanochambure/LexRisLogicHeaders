/* Display.cpp -- Display Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/Display.h"

namespace LL_AL5
{
    void Display::_F_set_global_scale()
    {
        _V_cam_pos_x=((_V_cam_pos_x*_V_size_x)/(_V_last_size_x));
        _V_cam_pos_y=((_V_cam_pos_y*_V_size_y)/(_V_last_size_y));
        _V_last_size_x=_V_size_x;
        _V_last_size_y=_V_size_y;
        bitmap_scale_x=float(_V_size_x)/_V_real_size_x;
        bitmap_scale_y=float(_V_size_y)/_V_real_size_y;
        text_scale=((bitmap_scale_x-bitmap_scale_y)/2)+bitmap_scale_y;
        if(text_scale<1.0)
            primitives_scale=1.0;
        else
            primitives_scale=text_scale;
    }
    Display::Display()
    {
    }
    Display::Display(Type_display_size size_x,Type_display_size size_y)
    {
        _V_real_size_x=_V_size_x=size_x;
        _V_real_size_y=_V_size_y=size_y;
        _F_set_global_scale();
    }
    Display::Display(Type_display_size size_x,Type_display_size size_y,
                     Type_display_size real_size_x,Type_display_size real_size_y)
    {
        _V_size_x=size_x;
        _V_size_y=size_y;
        _V_real_size_x=real_size_x;
        _V_real_size_y=real_size_y;
        _F_set_global_scale();
    }
    bool Display::create()
    {
        if(_V_display)
            return false;
        al_set_new_display_flags(_V_display_mode);
        _V_display=al_create_display(_V_size_x,_V_size_y);
        if(_V_display)
        {
            set_target();
            al_flip_display();
        }
        return _V_display;
    }
    bool Display::destroy()
    {
        if(!_V_display)
            return false;
        al_destroy_display(_V_display);
        _V_display=nullptr;
        return true;
    }
    bool Display::set_title(std::string new_title)
    {
        if(!_V_display)
            return false;
        al_set_window_title(_V_display,new_title.c_str());
        return true;
    }
    bool Display::set_size(Type_display_size size_x,Type_display_size size_y)
    {
        if(_V_display && !al_resize_display(_V_display,size_x,size_y))
            return false;
        _V_size_x=size_x;
        _V_size_y=size_y;
        _F_set_global_scale();
        return true;
    }
    Type_display_size Display::get_size_x()
    {
        return _V_size_x;
    }
    Type_display_size Display::get_size_y()
    {
        return _V_size_y;
    }
    void Display::set_real_size(Type_display_size real_size_x,Type_display_size real_size_y)
    {
        _V_real_size_x=real_size_x;
        _V_real_size_y=real_size_y;
        _F_set_global_scale();
    }
    Type_display_size Display::get_real_size_x()
    {
        return _V_real_size_x;
    }
    Type_display_size Display::get_real_size_y()
    {
        return _V_real_size_y;
    }
    bool Display::set_display_mode(int new_flag)
    {
        if(_V_display)
            return false;
        _V_display_mode=new_flag;
        return true;
    }
    int Display::get_display_mode()
    {
        return _V_display_mode;
    }
    void Display::set_cam(Type_pos new_pos_x,Type_pos new_pos_y)
    {
        _V_cam_pos_x=(new_pos_x*bitmap_scale_x);
        _V_cam_pos_y=(new_pos_y*bitmap_scale_y);
    }
    void Display::set_cam_x(Type_pos new_pos_x)
    {
        _V_cam_pos_x=(new_pos_x*bitmap_scale_x);
    }
    Type_pos Display::get_cam_x()
    {
        return _V_cam_pos_x/bitmap_scale_x;
    }
    void Display::set_cam_y(Type_pos new_pos_y)
    {
        _V_cam_pos_y=(new_pos_y*bitmap_scale_y);
    }
    Type_pos Display::get_cam_y()
    {
        return _V_cam_pos_y/bitmap_scale_y;
    }
    void Display::plus_cam_x(Type_pos plus_x)
    {
        _V_cam_pos_x+=(plus_x*bitmap_scale_x);
    }
    void Display::plus_cam_y(Type_pos plus_y)
    {
        _V_cam_pos_y+=(plus_y*bitmap_scale_y);
    }
    Type_pos Display::display_to_real_pos_x(Type_pos pos_x,bool references_axes)
    {
        return (pos_x+(_V_cam_pos_x*references_axes))/bitmap_scale_x;
    }
    Type_pos Display::display_to_real_pos_y(Type_pos pos_y,bool references_axes)
    {
        return (pos_y+(_V_cam_pos_y*references_axes))/bitmap_scale_y;
    }
    bool Display::show_cursor()
    {
        return al_show_mouse_cursor(_V_display);
    }
    bool Display::hide_cursor()
    {
        return al_hide_mouse_cursor(_V_display);
    }
    bool Display::set_cursor(ALLEGRO_BITMAP* bitmap_cursor,int focus_x,int focus_y)
    {
        destroy_cursor();
        if((_V_cursor=al_create_mouse_cursor(bitmap_cursor,focus_x,focus_y)))
            return al_set_mouse_cursor(_V_display,_V_cursor);
        return false;
    }
    bool Display::destroy_cursor()
    {
        if(_V_cursor)
        {
            al_destroy_mouse_cursor(_V_cursor);
            _V_cursor=nullptr;
            return true;
        }
        return false;
    }
    void Display::clear()
    {
        al_clear_to_color(al_map_rgb(255,255,255));
    }
    void Display::clear_to_color(ALLEGRO_COLOR color)
    {
        al_clear_to_color(color);
    }
    void Display::refresh()
    {
        al_flip_display();
    }
    bool Display::set_target()
    {
        if(!_V_display)
            return false;
        al_set_target_backbuffer(_V_display);
        _F_set_global_scale();
        return true;
    }
    Display::operator ALLEGRO_DISPLAY* ()
    {
        return _V_display;
    }
    Display::operator ALLEGRO_BITMAP* ()
    {
        return al_get_backbuffer(_V_display);
    }
    Display::operator ALLEGRO_MOUSE_CURSOR* ()
    {
        return _V_cursor;
    }
    Display::~Display()
    {
        destroy_cursor();
        destroy();
    }
}
