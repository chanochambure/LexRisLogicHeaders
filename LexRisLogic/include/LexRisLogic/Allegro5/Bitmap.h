/* Bitmap.h -- Bitmap Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_BITMAP_H
#define INCLUDED_LL_AL5_BITMAP_H

#include "../LL_Shared.h"

#include "Allegro5.h"

#include <allegro5/allegro_image.h>
#include <string>

namespace LL_AL5
{
    bool LL_SHARED image_addon();
    bool LL_SHARED save_bitmap(std::string bitmap_file_name,ALLEGRO_BITMAP* bitmap);
    void LL_SHARED disable_premultiplied_alpha();

    class LL_SHARED BitmapBase
    {
        protected:
            int _V_flag=0;
            float _V_angle=0.0;
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
            float _V_scale_x=1.0;
            float _V_scale_y=1.0;
            Type_pos _V_anchor_x=0;
            Type_pos _V_anchor_y=0;
            ALLEGRO_COLOR _V_tint_color;
        public:
            BitmapBase();
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y);
            void set_pos_x(Type_pos new_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_pos_y);
            Type_pos get_pos_y();
            void set_angle(float new_angle);
            float get_angle();
            void set_flag(int new_flag);
            void set_scale_x(float new_scale_x);
            float get_scale_x();
            void set_scale_y(float new_scale_y);
            float get_scale_y();
            void set_anchor(float new_anchor_x,float new_anchor_y);
            float get_anchor_x();
            float get_anchor_y();
            void set_tint_color(ALLEGRO_COLOR new_color);
            ALLEGRO_COLOR get_tint_color();
    };

    class LL_SHARED Bitmap:public BitmapBase
    {
        protected:
            ALLEGRO_BITMAP* _V_bitmap=nullptr;
            float _V_size_x=0.0;
            float _V_size_y=0.0;
        public:
            Bitmap();
            Bitmap(const Bitmap&) = delete;
            float get_size_x();
            float get_size_y();
            bool create(int size_x,int size_y);
            bool clone(ALLEGRO_BITMAP* base_bitmap);
            bool destroy();
            void set_target();
            bool lock();
            void unlock();
            ALLEGRO_COLOR get_pixel_color(Type_pos pos_x,Type_pos pos_y);
            void draw();
            void draw_in_another_target();
            const Bitmap& operator = (const Bitmap&) = delete;
            operator ALLEGRO_BITMAP* ();
            ~Bitmap();
    };

    class LL_SHARED SubBitmap:public BitmapBase
    {
        private:
            ALLEGRO_BITMAP* _V_parent_bitmap=nullptr;
            ALLEGRO_BITMAP* _V_bitmap=nullptr;
            int _V_sub_x=0.0;
            int _V_sub_y=0.0;
            float _V_size_x=0.0;
            float _V_size_y=0.0;
        public:
            SubBitmap();
            SubBitmap(const SubBitmap&) = delete;
            void set_parent_bitmap(ALLEGRO_BITMAP* new_parent_bitmap);
            ALLEGRO_BITMAP* get_parent_bitmap();
            void set_sub_x(int new_sub_x);
            int get_sub_x();
            void set_sub_y(int new_sub_y);
            int get_sub_y();
            void set_size_x(float new_size_x);
            float get_size_x();
            void set_size_y(float new_size_y);
            float get_size_y();
            bool create();
            bool destroy();
            void set_target();
            bool lock();
            void unlock();
            ALLEGRO_COLOR get_pixel_color(Type_pos pos_x,Type_pos pos_y);
            void draw();
            void draw_in_another_target();
            const SubBitmap& operator = (const SubBitmap&) = delete;
            operator ALLEGRO_BITMAP* ();
            ~SubBitmap();
    };

    class LL_SHARED Image:public BitmapBase
    {
        private:
            ALLEGRO_BITMAP* _V_bitmap=nullptr;
            std::string _V_image_path;
            float _V_size_x=0.0;
            float _V_size_y=0.0;
        public:
            Image();
            Image(const Image&) = delete;
            void set_path(std::string new_image_path);
            std::string get_path();
            float get_size_x();
            float get_size_y();
            bool load();
            bool save();
            bool destroy();
            void set_target();
            bool lock();
            void unlock();
            ALLEGRO_COLOR get_pixel_color(Type_pos pos_x,Type_pos pos_y);
            void draw();
            void draw_in_another_target();
            const Image& operator = (const Image&) = delete;
            operator ALLEGRO_BITMAP* ();
            ~Image();
    };
}

#endif // INCLUDED_LL_AL5_BITMAP_H
