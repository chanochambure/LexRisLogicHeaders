/* Sprite.h -- Sprite Allegro 5 Special Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_SPRITE_H
#define INCLUDED_LL_AL5_SPRITE_H

#include "../Allegro5.h"
#include "../Bitmap.h"

#include "../../LL_Shared.h"

#include <string>
#include <sstream>

namespace LL_AL5
{
    class LL_SHARED Sprite:public BitmapBase
    {
        private:
            ALLEGRO_BITMAP** _V_bitmap_set=nullptr;
            float* _V_size_x=nullptr;
            float* _V_size_y=nullptr;
            unsigned int _V_index=0;
            unsigned int _V_size=1;
            bool _V_initialised=false;
            std::string _F_int_to_string(unsigned int value);
        public:
            float get_size_x();
            float get_size_y();
            unsigned int get_size();
            bool set_size(unsigned int new_size);
            bool set_selection(unsigned int new_selection);
            unsigned int get_selection();
            bool create();
            bool create_selection(int size_x,int size_y);
            bool destroy_selection();
            bool create_data_from_directory(std::string sprites_path,std::string bitmap_format);
            bool destroy_data();
            bool destroy();
            void set_target();
            bool lock();
            void unlock();
            ALLEGRO_COLOR get_pixel_color(Type_pos pos_x,Type_pos pos_y);
            void draw();
            void draw_in_another_target();
            operator ALLEGRO_BITMAP* ();
            ~Sprite();
    };
}

#endif // INCLUDED_LL_AL5_SPRITE_H
