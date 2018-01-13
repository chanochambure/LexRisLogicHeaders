/* Display.h -- Display Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_DISPLAY_H
#define INCLUDED_LL_AL5_DISPLAY_H

#include "../LL_Shared.h"

#include "Allegro5.h"

#include <string>

namespace LL_AL5
{
    class LL_SHARED Display
    {
        private:
            ALLEGRO_DISPLAY* _V_display=nullptr;
            ALLEGRO_MOUSE_CURSOR* _V_cursor=nullptr;
            Type_display_size _V_size_x;
            Type_display_size _V_size_y;
            Type_display_size _V_real_size_x;
            Type_display_size _V_real_size_y;
            Type_display_size _V_last_size_x=1;
            Type_display_size _V_last_size_y=1;
            Type_pos _V_cam_pos_x=0.0;
            Type_pos _V_cam_pos_y=0.0;
            int _V_display_mode=ALLEGRO_WINDOWED;
            void _F_set_global_scale();
        public:
            Display();
            Display(Type_display_size size_x,Type_display_size size_y);
            Display(Type_display_size size_x,Type_display_size size_y,
                    Type_display_size real_size_x,Type_display_size real_size_y);
            bool create();
            bool destroy();
            bool set_title(std::string new_title);
            bool set_size(Type_display_size size_x,Type_display_size size_y);
            Type_display_size get_size_x();
            Type_display_size get_size_y();
            void set_real_size(Type_display_size real_size_x,Type_display_size real_size_y);
            Type_display_size get_real_size_x();
            Type_display_size get_real_size_y();
            bool set_display_mode(int new_flag);
            int get_display_mode();
            void set_cam(Type_pos new_pos_x,Type_pos new_pos_y);
            void set_cam_x(Type_pos new_pos_x);
            Type_pos get_cam_x();
            void set_cam_y(Type_pos new_pos_y);
            Type_pos get_cam_y();
            void plus_cam_x(Type_pos plus_x);
            void plus_cam_y(Type_pos plus_y);
            Type_pos display_to_real_pos_x(Type_pos pos_x,bool references_axes=true);
            Type_pos display_to_real_pos_y(Type_pos pos_y,bool references_axes=true);
            bool show_cursor();
            bool hide_cursor();
            bool set_cursor(ALLEGRO_BITMAP* bitmap_cursor,int focus_x,int focus_y);
            bool destroy_cursor();
            void clear();
            void clear_to_color(ALLEGRO_COLOR color);
            template<typename T>
            void draw(T* object,bool references_axes=true)
            {
                Type_pos data_pos_x=object->get_pos_x();
                Type_pos data_pos_y=object->get_pos_y();
                object->set_pos(((data_pos_x)*(bitmap_scale_x)-(_V_cam_pos_x*references_axes)),
                              ((data_pos_y)*(bitmap_scale_y)-(_V_cam_pos_y*references_axes)));
                object->draw();
                object->set_pos(data_pos_x,data_pos_y);
            }
            void refresh();
            bool set_target();
            operator ALLEGRO_DISPLAY* ();
            operator ALLEGRO_BITMAP* ();
            operator ALLEGRO_MOUSE_CURSOR* ();
            ~Display();
    };
}

#endif // INCLUDED_LL_AL5_DISPLAY_H
