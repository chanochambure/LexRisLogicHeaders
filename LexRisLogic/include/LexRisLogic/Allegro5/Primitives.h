/* Primitives.h -- Primitives Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_PRIMITIVES_H
#define INCLUDED_LL_AL5_PRIMITIVES_H

#include "../LL_Shared.h"

#include "Allegro5.h"

#include <allegro5/allegro_primitives.h>

namespace LL_AL5
{
    bool LL_SHARED primitives_addon();
    void LL_SHARED uninstall_primitives();

    class LL_SHARED Pixel
    {
        private:
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
            ALLEGRO_COLOR _V_color=al_map_rgb(0,0,0);
        public:
            Pixel();
            Pixel(Type_pos pos_x,Type_pos pos_y);
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y);
            void set_pos_x(Type_pos new_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_pos_y);
            Type_pos get_pos_y();
            void set_color(ALLEGRO_COLOR new_color);
            ALLEGRO_COLOR get_color();
            void draw();
            void draw_in_another_target();
    };

    class LL_SHARED Line
    {
        private:
            Type_pos _V_cam_pos_x=0.0;
            Type_pos _V_cam_pos_y=0.0;
            Type_pos _V_pos_x1=0.0;
            Type_pos _V_pos_y1=0.0;
            Type_pos _V_pos_x2=0.0;
            Type_pos _V_pos_y2=0.0;
            ALLEGRO_COLOR _V_color=al_map_rgb(0,0,0);
            float _V_thickness=1.0;
        public:
            Line();
            Line(Type_pos pos_x1,Type_pos pos_y1,Type_pos pos_x2,Type_pos pos_y2);
            void set_pos(Type_pos new_cam_pos_x,Type_pos new_cam_pos_y);
            void set_pos_x(Type_pos new_cam_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_cam_pos_y);
            Type_pos get_pos_y();
            void set_points(Type_pos new_pos_x1,Type_pos new_pos_y1,Type_pos new_pos_x2,Type_pos new_pos_y2);
            void set_pos_1(Type_pos new_pos_x1,Type_pos new_pos_y1);
            Type_pos get_pos_x1();
            Type_pos get_pos_y1();
            void set_pos_2(Type_pos new_pos_x2,Type_pos new_pos_y2);
            Type_pos get_pos_x2();
            Type_pos get_pos_y2();
            void set_color(ALLEGRO_COLOR new_color);
            ALLEGRO_COLOR get_color();
            void set_thickness(float new_thickness);
            float get_thickness();
            void draw();
            void draw_in_another_target();
    };

    class LL_SHARED Primitive
    {
        protected:
            bool _V_is_filled=false;
            float _V_thickness=1.0;
            ALLEGRO_COLOR _V_color=al_map_rgb(0,0,0);
        public:
            void set_thickness(float new_thickness);
            float get_thickness();
            void set_color(ALLEGRO_COLOR new_color);
            ALLEGRO_COLOR get_color();
            void set_filled_status(bool is_filled);
            bool get_filled_status();
    };

    class LL_SHARED Figure:public Primitive
    {
        protected:
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
        public:
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y);
            void set_pos_x(Type_pos new_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_pos_y);
            Type_pos get_pos_y();
    };

    class LL_SHARED Circle:public Figure
    {
        private:
            float _V_radius=1.0;
        public:
            Circle();
            Circle(Type_pos pos_x,Type_pos pos_y,float radius);
            void set_radius(float new_radius);
            float get_radius();
            void draw();
            void draw_in_another_target();
    };

    class LL_SHARED Ellipse:public Figure
    {
        private:
            float _V_radius_x=1.0;
            float _V_radius_y=1.0;
        public:
            Ellipse();
            Ellipse(Type_pos pos_x,Type_pos pos_y,float radius_x,float radius_y);
            void set_radius_x(float new_radius_x);
            float get_radius_x();
            void set_radius_y(float new_radius_y);
            float get_radius_y();
            void draw();
            void draw_in_another_target();
    };

    class LL_SHARED Rectangle:public Figure
    {
        private:
            float _V_size_x=0.0;
            float _V_size_y=0.0;
        public:
            Rectangle();
            Rectangle(Type_pos pos_x,Type_pos pos_y,float size_x,float size_y);
            void set_size_x(float new_size_x);
            float get_size_x();
            void set_size_y(float new_size_y);
            float get_size_y();
            void draw();
            void draw_in_another_target();
    };

    class LL_SHARED Triangle:public Primitive
    {
        private:
            Type_pos _V_cam_pos_x=0.0;
            Type_pos _V_cam_pos_y=0.0;
            Type_pos _V_pos_x1=0.0;
            Type_pos _V_pos_x2=0.0;
            Type_pos _V_pos_x3=0.0;
            Type_pos _V_pos_y1=0.0;
            Type_pos _V_pos_y2=0.0;
            Type_pos _V_pos_y3=0.0;
        public:
            Triangle();
            Triangle(Type_pos pos_x1,Type_pos pos_y1,Type_pos pos_x2,Type_pos pos_y2,Type_pos pos_x3,Type_pos pos_y3);
            void set_pos(Type_pos new_cam_pos_x,Type_pos new_cam_pos_y);
            void set_pos_x(Type_pos new_cam_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_cam_pos_y);
            Type_pos get_pos_y();
            void set_points(Type_pos new_pos_x1,Type_pos new_pos_y1,
                            Type_pos new_pos_x2,Type_pos new_pos_y2,
                            Type_pos new_pos_x3,Type_pos new_pos_y3);
            void set_pos_1(Type_pos new_pos_x1,Type_pos new_pos_y1);
            Type_pos get_pos_x1();
            Type_pos get_pos_y1();
            void set_pos_2(Type_pos new_pos_x2,Type_pos new_pos_y2);
            Type_pos get_pos_x2();
            Type_pos get_pos_y2();
            void set_pos_3(Type_pos new_pos_x3,Type_pos new_pos_y3);
            Type_pos get_pos_x3();
            Type_pos get_pos_y3();
            void draw();
            void draw_in_another_target();
    };

    class LL_SHARED Function
    {
        private:
            Type_pos _V_init_function=0.0;
            Type_pos _V_final_function=1.0;
            Type_pos _V_cam_pos_x=0.0;
            Type_pos _V_cam_pos_y=0.0;
            float _V_step_function=1.0;
            float _V_thickness=1.0;
            ALLEGRO_COLOR _V_color=al_map_rgb(0,0,0);
            Type_pos (*_P_Function_fx)(Type_pos)=nullptr;
        public:
            Function();
            Function(Type_pos (*Function_fx)(Type_pos));
            void set_pos(Type_pos new_cam_pos_x,Type_pos new_cam_pos_y);
            void set_pos_x(Type_pos new_cam_pos_x);
            Type_pos get_pos_x();
            void set_pos_y(Type_pos new_cam_pos_y);
            Type_pos get_pos_y();
            void set_thickness(float new_thickness);
            float get_thickness();
            void set_color(ALLEGRO_COLOR new_color);
            ALLEGRO_COLOR get_color();
            bool set_step(float new_step);
            float get_step();
            void set_initial_x(Type_pos new_init);
            Type_pos get_initial_x();
            void set_final_x(Type_pos new_final);
            Type_pos get_final_x();
            void set_function(Type_pos (*Function_fx)(Type_pos));
            void draw();
            void draw_in_another_target();
    };
}

#endif // INCLUDED_LL_AL5_PRIMITIVES_H
