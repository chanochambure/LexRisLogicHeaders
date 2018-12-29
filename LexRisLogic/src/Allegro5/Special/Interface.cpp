/* Interface.cpp -- Interface Allegro 5 Special Source - LexRis Logic Headers

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

#include "../../../include/LexRisLogic/Allegro5/Special/Interface.h"

namespace LL_AL5
{
    int Interface::_F_get_mouse_x()
    {
        if(_V_input_pointer->get_mouse_controller())
            return _V_input_pointer->get_mouse_controller()->get_mouse_x();
        return 0;
    }
    int Interface::_F_get_mouse_y()
    {
        if(_V_input_pointer->get_mouse_controller())
            return _V_input_pointer->get_mouse_controller()->get_mouse_y();
        return 0;
    }
    bool Interface::_F_get_left_click()
    {
        if(_V_input_pointer->get_mouse_controller())
            return _V_input_pointer->get_mouse_controller()->left_click();
        return false;
    }
    bool Interface::_F_in_focus()
    {
        Type_pos mouse_x=_F_get_mouse_x();
        Type_pos mouse_y=_F_get_mouse_y();
        return ((_V_pos_x<=mouse_x && mouse_x<(_V_pos_x+(_V_size_x*bitmap_scale_x))) &&
                (_V_pos_y<=mouse_y && mouse_y<(_V_pos_y+(_V_size_y*bitmap_scale_y))));
    }
    Interface::Interface()
    {
    }
    void Interface::set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
    {
        _V_pos_x=new_pos_x;
        _V_pos_y=new_pos_y;
    }
    void Interface::set_pos_x(Type_pos new_pos_x)
    {
        _V_pos_x=new_pos_x;
    }
    Type_pos Interface::get_pos_x()
    {
        return _V_pos_x;
    }
    void Interface::set_pos_y(Type_pos new_pos_y)
    {
        _V_pos_y=new_pos_y;
    }
    Type_pos Interface::get_pos_y()
    {
        return _V_pos_y;
    }
    float Interface::get_size_x()
    {
        return _V_size_x;
    }
    float Interface::get_size_y()
    {
        return _V_size_y;
    }
    void Interface::set_unclick_line_color(ALLEGRO_COLOR new_unclick_line_color)
    {
        _V_unclick_line_color=new_unclick_line_color;
    }
    ALLEGRO_COLOR Interface::get_unclick_line_color()
    {
        return _V_unclick_line_color;
    }
    void Interface::set_unclick_fill_color(ALLEGRO_COLOR new_unclick_fill_color)
    {
        _V_unclick_fill_color=new_unclick_fill_color;
    }
    ALLEGRO_COLOR Interface::get_unclick_fill_color()
    {
        return _V_unclick_fill_color;
    }
    void Interface::set_click_line_color(ALLEGRO_COLOR new_click_line_color)
    {
        _V_click_line_color=new_click_line_color;
    }
    ALLEGRO_COLOR Interface::get_click_line_color()
    {
        return _V_click_line_color;
    }
    void Interface::set_click_fill_color(ALLEGRO_COLOR new_click_fill_color)
    {
        _V_click_fill_color=new_click_fill_color;
    }
    ALLEGRO_COLOR Interface::get_click_fill_color()
    {
        return _V_click_fill_color;
    }
    void Interface::set_thickness(float new_thickness)
    {
        _V_thickness=new_thickness;
    }
    float Interface::get_thickness()
    {
        return _V_thickness;
    }
    Font* Interface::get_font()
    {
        return _V_font;
    }
    void Interface::set_text_color(ALLEGRO_COLOR new_text_color)
    {
        _V_text_color=new_text_color;
    }
    ALLEGRO_COLOR Interface::get_text_color()
    {
        return _V_text_color;
    }

    void Button::_F_get_event()
    {
        if(!_V_locked && _V_interface_status && _F_get_left_click() && _F_in_focus())
        {
            _V_is_clicked=_V_locked=true;
            return;
        }
        if(!_F_get_left_click())
            _V_locked=false;
    }
    Button::Button(Input* input_pointer)
    {
        _V_input_pointer=input_pointer;
        _V_text_color=_V_unclick_line_color=_V_click_line_color=al_map_rgb(0,0,0);
        _V_unclick_fill_color=al_map_rgb(255,255,255);
        _V_click_fill_color=al_map_rgb(0,0,250);
    }
    void Button::set_button_text(std::string new_button_text)
    {
        _V_button_text=new_button_text;
        _V_size_x=_V_button_text.size();
        if(_V_font)
            _V_size_x=_V_font->get_width(_V_button_text+"--")/text_scale;
        _V_mid_x=(_V_size_x*bitmap_scale_x/2);
    }
    std::string Button::get_button_text()
    {
        return _V_button_text;
    }
    void Button::set_font(Font* new_font)
    {
        _V_font=new_font;
        _V_size_x=_V_button_text.size();
        _V_size_y=1;
        if(_V_font)
        {
            _V_size_x=_V_font->get_width(_V_button_text+"--")/text_scale;
            _V_size_y=_V_font->get_height()/text_scale;
        }
        _V_mid_x=(_V_size_x*bitmap_scale_x/2);
    }
    void Button::draw()
    {
        _F_get_event();
        if(_F_in_focus() && _F_get_left_click())
        {
            al_draw_filled_rectangle(_V_pos_x,_V_pos_y,
                                     _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                                     _V_click_fill_color);
            al_draw_rectangle(_V_pos_x,_V_pos_y,
                              _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                              _V_click_line_color,_V_thickness*primitives_scale);
        }
        else
        {
            al_draw_filled_rectangle(_V_pos_x,_V_pos_y,
                                     _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                                     _V_unclick_fill_color);
            al_draw_rectangle(_V_pos_x,_V_pos_y,
                              _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                              _V_unclick_line_color,_V_thickness*primitives_scale);
        }
        al_draw_text(*_V_font,_V_text_color,_V_pos_x+_V_mid_x,_V_pos_y,ALLEGRO_ALIGN_CENTER,_V_button_text.c_str());
    }
    bool Button::is_clicked()
    {
        if(_V_is_clicked)
        {
            _V_is_clicked=false;
            return true;
        }
        return false;
    }
    bool Button::button_on()
    {
        if(!_V_interface_status)
        {
            _V_interface_status=true;
            return true;
        }
        return false;
    }
    bool Button::button_off()
    {
        if(_V_interface_status)
        {
            _V_interface_status=false;
            return true;
        }
        return false;
    }

    void TextBox::_F_get_event()
    {
        if(_V_interface_status && _F_get_left_click() && _F_in_focus())
            _V_selected_status=true;
        else if(!_F_in_focus() && _F_get_left_click())
            _V_selected_status=false;
    }
    TextBox::TextBox(Input* input_pointer)
    {
        _V_input_pointer=input_pointer;
        _V_text_color=_V_unclick_line_color=_V_click_line_color=al_map_rgb(0,0,0);
        _V_unclick_fill_color=al_map_rgb(255,255,255);
        _V_click_fill_color=al_map_rgb(187,250,255);
    }
    void TextBox::set_hide_option(bool hide_option)
    {
        _V_hide_option=hide_option;
    }
    bool TextBox::get_hide_option()
    {
        return _V_hide_option;
    }
    void TextBox::set_text_length(unsigned int new_text_length)
    {
        clear();
        _V_text_length=new_text_length;
        _V_size_x=new_text_length;
        _V_space=1.0;
        if(_V_font)
        {
            _V_size_x=_V_font->get_width(std::string(_V_text_length+2,'m'))/text_scale;
            _V_space=_V_font->get_width(std::string(1,'m'));
        }
    }
    unsigned int TextBox::get_text_length()
    {
        return _V_text_length;
    }
    void TextBox::set_font(Font* new_font)
    {
        _V_font=new_font;
        _V_size_x=_V_text_length;
        _V_size_y=1.0;
        _V_space=1.0;
        if(_V_font)
        {
            _V_size_x=_V_font->get_width(std::string(_V_text_length+2,'m'))/text_scale;
            _V_size_y=_V_font->get_height()/text_scale;
            _V_space=_V_font->get_width(std::string(1,'m'));
        }
    }
    void TextBox::clear()
    {
        _V_value.clear();
    }
    bool TextBox::set_value(std::string new_value)
    {
        if(new_value.size()<=_V_text_length)
        {
            _V_value=new_value;
            return true;
        }
        return false;
    }
    std::string TextBox::get_value()
    {
        return _V_value;
    }
    void TextBox::draw()
    {
        _F_get_event();
        if(_V_selected_status)
        {
            if(!_V_loaded)
                _V_loaded=_V_input_pointer->input_on(&_V_value,_V_text_length,true);
            al_draw_filled_rectangle(_V_pos_x,_V_pos_y,
                                     _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                                     _V_click_fill_color);
            al_draw_rectangle(_V_pos_x,_V_pos_y,
                              _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                              _V_click_line_color,_V_thickness*primitives_scale);
        }
        else
        {
            if(_V_loaded)
                _V_loaded=!_V_input_pointer->input_off(&_V_value);
            al_draw_filled_rectangle(_V_pos_x,_V_pos_y,
                                     _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                                     _V_unclick_fill_color);
            al_draw_rectangle(_V_pos_x,_V_pos_y,
                              _V_pos_x+(_V_size_x*bitmap_scale_x),_V_pos_y+(_V_size_y*bitmap_scale_y),
                              _V_unclick_line_color,_V_thickness*primitives_scale);
        }
        if(_V_hide_option)
        {
            std::string hide_value(_V_value.size(),'*');
            al_draw_text(*_V_font,_V_text_color,_V_pos_x+_V_space,_V_pos_y,
                         ALLEGRO_ALIGN_LEFT,hide_value.c_str());
        }
        else
            al_draw_text(*_V_font,_V_text_color,_V_pos_x+_V_space,_V_pos_y,
                         ALLEGRO_ALIGN_LEFT,_V_value.c_str());
    }
    bool TextBox::is_clicked()
    {
        return _V_selected_status;
    }
    bool TextBox::textbox_on()
    {
        if(!_V_interface_status)
        {
            _V_interface_status=true;
            return true;
        }
        return false;
    }
    bool TextBox::textbox_off()
    {
        if(_V_interface_status)
        {
            _V_interface_status=false;
            _V_loaded=false;
            _V_input_pointer->input_off(&_V_value);
            return true;
        }
        return false;
    }
    TextBox::~TextBox()
    {
        textbox_off();
    }
}
