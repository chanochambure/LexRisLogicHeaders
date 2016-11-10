/* Lighting.h -- Lighting Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_LIGHTING_H
#define INCLUDED_LL_AL5_LIGHTING_H

#include "Allegro5.h"

namespace LL_AL5
{
    class Lighting
    {
        private:
            int _V_blend_mode;
            int _V_blend_source_value;
            int _V_blend_destination_value;
            ALLEGRO_BITMAP* _V_lighting_buffer=nullptr;
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
            float _V_size_x=0.0;
            float _V_size_y=0.0;
        public:
            Lighting();
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y);
            void set_pos_x(Type_pos new_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_pos_y);
            Type_pos get_pos_y();
            float get_size_x();
            float get_size_y();
            bool create(int size_x,int size_y);
            bool destroy();
            void set_target();
            void clear();
            template<typename T>
            void add(T* object_shape,float intensity)
            {
                al_set_blender(ALLEGRO_SRC_MINUS_DEST, ALLEGRO_ONE, ALLEGRO_ZERO);
                ALLEGRO_COLOR data_color=object_shape->get_color();
                object_shape->set_color(al_map_rgba_f(0,0,0,intensity));
                object_shape->draw_in_another_target();
                al_set_blender(_V_blend_mode, _V_blend_source_value, _V_blend_destination_value);
                object_shape->set_color(data_color);
            }
            float get_pixel_intensity(Type_pos pos_x,Type_pos pos_y);
            void draw();
            void draw_in_another_target();
            operator ALLEGRO_BITMAP* ();
            ~Lighting();
    };
}

#endif // INCLUDED_LL_AL5_LIGHTING_H
