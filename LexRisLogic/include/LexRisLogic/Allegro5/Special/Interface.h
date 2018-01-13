/* Interface.h -- Interface Allegro 5 Special Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_INTERFACE_H
#define INCLUDED_LL_AL5_INTERFACE_H

#include "../../LL_Shared.h"

#include "../Allegro5.h"
#include "../Primitives.h"
#include "../Input.h"
#include "../Text.h"

#include <string>

namespace LL_AL5
{
    class LL_SHARED Interface
    {
        protected:
            const float _C_CONSTANT_SCALE_FONT_X=0.75;
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
            bool _F_in_focus();
        public:
            Interface();
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y);
            void set_pos_x(Type_pos new_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_pos_y);
            Type_pos get_pos_y();
            float get_size_x();
            float get_size_y();
            void set_unclick_line_color(ALLEGRO_COLOR new_unclick_line_color);
            ALLEGRO_COLOR get_unclick_line_color();
            void set_unclick_fill_color(ALLEGRO_COLOR new_unclick_fill_color);
            ALLEGRO_COLOR get_unclick_fill_color();
            void set_click_line_color(ALLEGRO_COLOR new_click_line_color);
            ALLEGRO_COLOR get_click_line_color();
            void set_click_fill_color(ALLEGRO_COLOR new_click_fill_color);
            ALLEGRO_COLOR get_click_fill_color();
            void set_thickness(float new_thickness);
            float get_thickness();
            Font* get_font();
            void set_text_color(ALLEGRO_COLOR new_text_color);
            ALLEGRO_COLOR get_text_color();
    };

    class LL_SHARED Button:public Interface
    {
        private:
            Type_pos _V_mid_x=0.0;
            std::string _V_button_text;
            bool _V_locked=false;
            bool _V_is_clicked=false;
            void _F_get_event();
        public:
            Button(Input* input_pointer);
            void set_button_text(std::string new_button_text);
            std::string get_button_text();
            void set_font(Font* new_font);
            void draw();
            bool is_clicked();
            bool button_on();
            bool button_off();
    };

    class LL_SHARED TextBox:public Interface
    {
        private:
            unsigned int _V_text_length=100;
            std::string _V_value;
            bool _V_hide_option=false;
            bool _V_selected_status=false;
            bool _V_loaded=false;
            void _F_get_event();
        public:
            TextBox(Input* input_pointer);
            void set_hide_option(bool hide_option);
            bool get_hide_option();
            void set_text_length(unsigned int new_text_length);
            unsigned int get_text_length();
            void set_font(Font* new_font);
            void clear();
            bool set_value(std::string new_value);
            std::string get_value();
            void draw();
            bool is_clicked();
            bool textbox_on();
            bool textbox_off();
            ~TextBox();
    };
}

#endif // INCLUDED_LL_AL5_INTERFACE_H
