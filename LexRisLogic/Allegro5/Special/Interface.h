/* Interface.h -- Interface Allegro 5 Special Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_INTERFACE_H
#define INCLUDED_LL_AL5_INTERFACE_H

#include <string>
#include "../Input.h"
#include "../Text.h"

namespace LL_AL5
{
    class Interface
    {
        protected:
            const float _C_CONSTANT_SCALE_FONT_X=0.53125;
            const float _C_CONSTANT_SCALE_FONT_Y=1.25;
            unsigned int _V_font_size=1;
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
            float _V_size_x=0.0;
            float _V_size_y=0.0;
            Font* _V_font=nullptr;
            ALLEGRO_COLOR _V_text_color;
            ALLEGRO_COLOR _V_unclick_line_color;
            ALLEGRO_COLOR _V_unclick_fill_color;
            ALLEGRO_COLOR _V_click_line_color;
            ALLEGRO_COLOR _V_click_fill_color;
            float _V_thickness=1.0;
            bool _V_interface_status=false;
            Input* _V_input_pointer=nullptr;
            bool _F_in_focus()
            {
                Type_pos mouse_x=_V_input_pointer->get_mouse_x();
                Type_pos mouse_y=_V_input_pointer->get_mouse_y();
                return ((_V_pos_x<=mouse_x and mouse_x<(_V_pos_x+(_V_size_x*bitmap_scale_x))) and
                        (_V_pos_y<=mouse_y and mouse_y<(_V_pos_y+(_V_size_y*bitmap_scale_y))));
            }
        public:
            Interface(){}
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
            {
                _V_pos_x=new_pos_x;
                _V_pos_y=new_pos_y;
            }
            Type_pos get_pos_x()
            {
                return _V_pos_x;
            }
            void set_pos_x(Type_pos new_pos_x)
            {
                _V_pos_x=new_pos_x;
            }
            void set_pos_y(Type_pos new_pos_y)
            {
                _V_pos_y=new_pos_y;
            }
            Type_pos get_pos_y()
            {
                return _V_pos_y;
            }
            float get_size_x()
            {
                return _V_size_x;
            }
            float get_size_y()
            {
                return _V_size_y;
            }
            void set_unclick_line_color(ALLEGRO_COLOR new_unclick_line_color)
            {
                _V_unclick_line_color=new_unclick_line_color;
            }
            ALLEGRO_COLOR get_unclick_line_color()
            {
                return _V_unclick_line_color;
            }
            void set_unclick_fill_color(ALLEGRO_COLOR new_unclick_fill_color)
            {
                _V_unclick_fill_color=new_unclick_fill_color;
            }
            ALLEGRO_COLOR get_unclick_fill_color()
            {
                return _V_unclick_fill_color;
            }
            void set_click_line_color(ALLEGRO_COLOR new_click_line_color)
            {
                _V_click_line_color=new_click_line_color;
            }
            ALLEGRO_COLOR get_click_line_color()
            {
                return _V_click_line_color;
            }
            void set_click_fill_color(ALLEGRO_COLOR new_click_fill_color)
            {
                _V_click_fill_color=new_click_fill_color;
            }
            ALLEGRO_COLOR get_click_fill_color()
            {
                return _V_click_fill_color;
            }
            void set_thickness(float new_thickness)
            {
                _V_thickness=new_thickness;
            }
            float get_thickness()
            {
                return _V_thickness;
            }
            Font* get_font()
            {
                return _V_font;
            }
            void set_text_color(ALLEGRO_COLOR new_text_color)
            {
                _V_text_color=new_text_color;
            }
            ALLEGRO_COLOR get_text_color()
            {
                return _V_text_color;
            }
            virtual ~Interface(){}
    };

    class Button:public Interface
    {
        private:
            Type_pos _V_mid_x=0.0;
            std::string _V_button_text;
            bool _V_locked=false;
            bool _V_is_clicked=false;
            void _F_get_event()
            {
                if(!_V_locked and _V_interface_status and _V_input_pointer->left_click() and _F_in_focus())
                {
                    _V_is_clicked=_V_locked=true;
                    return;
                }
                if(!_V_input_pointer->left_click())
                    _V_locked=false;
            }
        public:
            Button(Input* input_pointer)
            {
                _V_input_pointer=input_pointer;
                _V_text_color=_V_unclick_line_color=_V_click_line_color=al_map_rgb(0,0,0);
                _V_unclick_fill_color=al_map_rgb(255,255,255);
                _V_click_fill_color=al_map_rgb(0,0,250);
            }
            void set_button_text(std::string new_button_text)
            {
                _V_button_text=new_button_text;
                _V_size_x=_V_button_text.size()*_V_font_size*_C_CONSTANT_SCALE_FONT_X;
                _V_mid_x=(_V_size_x*bitmap_scale_x/2);
            }
            std::string get_button_text()
            {
                return _V_button_text;
            }
            void set_font(Font* new_font)
            {
                _V_font=new_font;
                _V_font_size=_V_font->get_size();
                _V_size_x=_V_button_text.size()*_V_font_size*_C_CONSTANT_SCALE_FONT_X;
                _V_size_y=(_V_font_size*_C_CONSTANT_SCALE_FONT_Y);
                _V_mid_x=(_V_size_x*bitmap_scale_x/2);
            }
            void draw()
            {
                _F_get_event();
                if(_F_in_focus() and _V_input_pointer->left_click())
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
                al_draw_text(*_V_font,_V_text_color,
                             _V_pos_x+_V_mid_x,_V_pos_y,
                             ALLEGRO_ALIGN_CENTER,_V_button_text.c_str());
            }
            bool is_clicked()
            {
                if(_V_is_clicked)
                {
                    _V_is_clicked=false;
                    return true;
                }
                return false;
            }
            bool button_on()
            {
                if(!_V_interface_status)
                {
                    _V_interface_status=true;
                    return true;
                }
                return false;
            }
            bool button_off()
            {
                if(_V_interface_status)
                {
                    _V_interface_status=false;
                    return true;
                }
                return false;
            }
    };

    class TextBox:public Interface
    {
        private:
            unsigned int _V_text_length=100;
            std::string _V_value;
            bool _V_hide_option=false;
            bool _V_selected_status=false;
            bool _V_loaded=false;
            void _F_get_event()
            {
                if(_V_interface_status and _V_input_pointer->left_click() and _F_in_focus())
                    _V_selected_status=true;
                else if(!_F_in_focus() and _V_input_pointer->left_click())
                    _V_selected_status=false;
            }
        public:
            TextBox(Input* input_pointer)
            {
                _V_input_pointer=input_pointer;
                _V_text_color=_V_unclick_line_color=_V_click_line_color=al_map_rgb(0,0,0);
                _V_unclick_fill_color=al_map_rgb(255,255,255);
                _V_click_fill_color=al_map_rgb(187,250,255);
            }
            void set_hide_option(bool hide_option)
            {
                _V_hide_option=hide_option;
            }
            bool get_hide_option()
            {
                return _V_hide_option;
            }
            void set_text_length(unsigned int new_text_length)
            {
                clear();
                _V_text_length=new_text_length;
                _V_size_x=(_V_text_length+1)*_V_font_size*_C_CONSTANT_SCALE_FONT_X;
            }
            void set_font(Font* new_font)
            {
                _V_font=new_font;
                _V_font_size=_V_font->get_size();
                _V_size_x=(_V_text_length+1)*_V_font_size*_C_CONSTANT_SCALE_FONT_X;
                _V_size_y=_V_font->get_size()*_C_CONSTANT_SCALE_FONT_Y;
            }
            void clear()
            {
                _V_value.clear();
            }
            bool set_value(std::string new_value)
            {
                if(new_value.size()<=_V_text_length)
                {
                    _V_value=new_value;
                    return true;
                }
                return false;
            }
            std::string get_value()
            {
                return _V_value;
            }
            void draw()
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
                    al_draw_text(*_V_font,_V_text_color,
                                 _V_pos_x+(_V_font->get_size()*text_scale),_V_pos_y,
                                 ALLEGRO_ALIGN_LEFT,hide_value.c_str());
                }
                else
                    al_draw_text(*_V_font,_V_text_color,
                                 _V_pos_x+(_V_font->get_size()*text_scale),_V_pos_y,
                                 ALLEGRO_ALIGN_LEFT,_V_value.c_str());
            }
            bool is_selected()
            {
                return _V_selected_status;
            }
            bool textbox_on()
            {
                if(!_V_interface_status)
                {
                    _V_interface_status=true;
                    return true;
                }
                return false;
            }
            bool textbox_off()
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
            ~TextBox()
            {
                textbox_off();
            }
    };
}

#endif // INCLUDED_LL_AL5_INTERFACE_H
