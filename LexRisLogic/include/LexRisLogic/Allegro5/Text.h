/* Text.h -- Text Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_TEXT_H
#define INCLUDED_LL_AL5_TEXT_H

#include "../LL_Shared.h"

#include "Allegro5.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

namespace LL_AL5
{
    bool LL_SHARED text_addon();

    class LL_SHARED Font
    {
        private:
            ALLEGRO_FONT* _V_font=nullptr;
            std::string _V_font_path;
            float _V_size=12.0;
        public:
            void set_path(std::string new_font_path);
            std::string get_path();
            bool set_size(float new_size);
            float get_size();
            bool load_ttf_font();
            bool load_ttf_font_for_another_target();
            bool destroy();
            operator ALLEGRO_FONT* ();
            ~Font();
    };

    class LL_SHARED Text
    {
        private:
            Font* _V_font=nullptr;
            int _V_flag=0;
            std::string _V_text;
            ALLEGRO_COLOR _V_color;
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
        public:
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y);
            void set_pos_x(Type_pos new_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_pos_y);
            Type_pos get_pos_y();
            void set_flag(int new_flag);
            void set_color(ALLEGRO_COLOR new_color);
            ALLEGRO_COLOR get_color();
            void set_font(Font* new_font);
            Font* get_font();
            void draw();
            const char* operator = (const char* new_text);
            std::string operator = (std::string new_text);
            operator const char* ();
            operator std::string ();
    };
}

#endif // INCLUDED_LL_AL5_TEXT_H
