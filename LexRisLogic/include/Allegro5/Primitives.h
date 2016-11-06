/* Primitives.h -- Primitives Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_PRIMITIVES_H
#define INCLUDED_LL_AL5_PRIMITIVES_H

#include "Allegro5.h"

#include <allegro5/allegro_primitives.h>

namespace LL_AL5
{
    bool primitives_addon()
    {
        return al_init_primitives_addon();
    }
    void uninstall_primitives()
    {
        al_shutdown_primitives_addon();
    }

    class Pixel
    {
        private:
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
            ALLEGRO_COLOR _V_color=al_map_rgb(0,0,0);
        public:
            Pixel(){}
            Pixel(Type_pos pos_x,Type_pos pos_y)
            {
                _V_pos_x=pos_x;
                _V_pos_y=pos_y;
            }
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
            {
                _V_pos_x=new_pos_x;
                _V_pos_y=new_pos_y;
            }
            void set_pos_x(Type_pos new_pos_x)
            {
                _V_pos_x=new_pos_x;
            }
            Type_pos get_pos_x()
            {
                return _V_pos_x;
            }
            void set_pos_y(Type_pos new_pos_y)
            {
                _V_pos_y=new_pos_y;
            }
            Type_pos get_pos_y()
            {
                return _V_pos_y;
            }
            void set_color(ALLEGRO_COLOR new_color)
            {
                _V_color=new_color;
            }
            ALLEGRO_COLOR get_color()
            {
                return _V_color;
            }
            void draw()
            {
                al_draw_filled_rectangle(_V_pos_x,_V_pos_y,_V_pos_x+bitmap_scale_x,_V_pos_y+bitmap_scale_y,_V_color);
            }
            void draw_in_another_target()
            {
                al_put_pixel(_V_pos_x,_V_pos_y,_V_color);
            }
    };

    class Line
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
            Line(){}
            Line(Type_pos pos_x1,Type_pos pos_y1,Type_pos pos_x2,Type_pos pos_y2)
            {
                _V_pos_x1=pos_x1;
                _V_pos_y1=pos_y1;
                _V_pos_x2=pos_x2;
                _V_pos_y2=pos_y2;
            }
            void set_pos(Type_pos new_cam_pos_x,Type_pos new_cam_pos_y)
            {
                _V_cam_pos_x=new_cam_pos_x;
                _V_cam_pos_y=new_cam_pos_y;
            }
            void set_pos_x(Type_pos new_cam_pos_x)
            {
                _V_cam_pos_x=new_cam_pos_x;
            }
            Type_pos get_pos_x()
            {
                return _V_cam_pos_x;
            }
            void set_pos_y(Type_pos new_cam_pos_y)
            {
                _V_cam_pos_y=new_cam_pos_y;
            }
            Type_pos get_pos_y()
            {
                return _V_cam_pos_y;
            }
            void set_points(Type_pos new_pos_x1,Type_pos new_pos_y1,Type_pos new_pos_x2,Type_pos new_pos_y2)
            {
                _V_pos_x1=new_pos_x1;
                _V_pos_y1=new_pos_y1;
                _V_pos_x2=new_pos_x2;
                _V_pos_y2=new_pos_y2;
            }
            void set_pos_1(Type_pos new_pos_x1,Type_pos new_pos_y1)
            {
                _V_pos_x1=new_pos_x1;
                _V_pos_y1=new_pos_y1;
            }
            Type_pos get_pos_x1()
            {
                return _V_pos_x1;
            }
            Type_pos get_pos_y1()
            {
                return _V_pos_y1;
            }
            void set_pos_2(Type_pos new_pos_x2,Type_pos new_pos_y2)
            {
                _V_pos_x2=new_pos_x2;
                _V_pos_y2=new_pos_y2;
            }
            Type_pos get_pos_x2()
            {
                return _V_pos_x2;
            }
            Type_pos get_pos_y2()
            {
                return _V_pos_y2;
            }
            void set_color(ALLEGRO_COLOR new_color)
            {
                _V_color=new_color;
            }
            ALLEGRO_COLOR get_color()
            {
                return _V_color;
            }
            void set_thickness(float new_thickness)
            {
                _V_thickness=new_thickness;
            }
            float get_thickness()
            {
                return _V_thickness;
            }
            void draw()
            {
                al_draw_line((_V_pos_x1*bitmap_scale_x)+_V_cam_pos_x,(_V_pos_y1*bitmap_scale_y)+_V_cam_pos_y,
                             (_V_pos_x2*bitmap_scale_x)+_V_cam_pos_x,(_V_pos_y2*bitmap_scale_y)+_V_cam_pos_y,
                             _V_color,_V_thickness*primitives_scale);
            }
            void draw_in_another_target()
            {
                al_draw_line(_V_pos_x1+_V_cam_pos_x,_V_pos_y1+_V_cam_pos_y,
                             _V_pos_x2+_V_cam_pos_x,_V_pos_y2+_V_cam_pos_y,
                             _V_color,_V_thickness);
            }
    };

    class Primitive
    {
        protected:
            bool _V_is_filled=false;
            float _V_thickness=1.0;
            ALLEGRO_COLOR _V_color=al_map_rgb(0,0,0);
        public:
            void set_thickness(float new_thickness)
            {
                _V_thickness=new_thickness;
            }
            float get_thickness()
            {
                return _V_thickness;
            }
            void set_color(ALLEGRO_COLOR new_color)
            {
                _V_color=new_color;
            }
            ALLEGRO_COLOR get_color()
            {
                return _V_color;
            }
            void set_filled_status(bool is_filled)
            {
                _V_is_filled=is_filled;
            }
            bool get_filled_status()
            {
                return _V_is_filled;
            }
    };

    class Figure:public Primitive
    {
        protected:
            Type_pos _V_pos_x=0.0;
            Type_pos _V_pos_y=0.0;
        public:
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
            {
                _V_pos_x=new_pos_x;
                _V_pos_y=new_pos_y;
            }
            void set_pos_x(Type_pos new_pos_x)
            {
                _V_pos_x=new_pos_x;
            }
            Type_pos get_pos_x()
            {
                return _V_pos_x;
            }
            void set_pos_y(Type_pos new_pos_y)
            {
                _V_pos_y=new_pos_y;
            }
            Type_pos get_pos_y()
            {
                return _V_pos_y;
            }
    };

    class Circle:public Figure
    {
        private:
            float _V_radius=1.0;
        public:
            Circle(){}
            Circle(Type_pos pos_x,Type_pos pos_y,float radius)
            {
                set_pos(pos_x,pos_y);
                _V_radius=radius;
            }
            void set_radius(float new_radius)
            {
                _V_radius=new_radius;
            }
            float get_radius()
            {
                return _V_radius;
            }
            void draw()
            {
                if(get_filled_status())
                    al_draw_filled_ellipse(_V_pos_x,_V_pos_y,_V_radius*bitmap_scale_x,_V_radius*bitmap_scale_y,
                                           _V_color);
                al_draw_ellipse(_V_pos_x,_V_pos_y,_V_radius*bitmap_scale_x,_V_radius*bitmap_scale_y,_V_color,
                                _V_thickness*primitives_scale);
            }
            void draw_in_another_target()
            {
                if(get_filled_status())
                    al_draw_filled_circle(_V_pos_x,_V_pos_y,_V_radius,_V_color);
                al_draw_circle(_V_pos_x,_V_pos_y,_V_radius,_V_color,_V_thickness);
            }
    };

    class Ellipse:public Figure
    {
        private:
            float _V_radius_x=1.0;
            float _V_radius_y=1.0;
        public:
            Ellipse(){}
            Ellipse(Type_pos pos_x,Type_pos pos_y,float radius_x,float radius_y)
            {
                set_pos(pos_x,pos_y);
                _V_radius_x=radius_x;
                _V_radius_y=radius_y;
            }
            void set_radius_x(float new_radius_x)
            {
                _V_radius_x=new_radius_x;
            }
            float get_radius_x()
            {
                return _V_radius_x;
            }
            void set_radius_y(float new_radius_y)
            {
                _V_radius_y=new_radius_y;
            }
            float get_radius_y()
            {
                return _V_radius_y;
            }
            void draw()
            {
                if(get_filled_status())
                    al_draw_filled_ellipse(_V_pos_x,_V_pos_y,_V_radius_x*bitmap_scale_x,_V_radius_y*bitmap_scale_y,
                                           _V_color);
                al_draw_ellipse(_V_pos_x,_V_pos_y,_V_radius_x*bitmap_scale_x,_V_radius_y*bitmap_scale_y,_V_color,
                                _V_thickness*primitives_scale);
            }
            void draw_in_another_target()
            {
                if(get_filled_status())
                    al_draw_filled_ellipse(_V_pos_x,_V_pos_y,_V_radius_x,_V_radius_y,_V_color);
                al_draw_ellipse(_V_pos_x,_V_pos_y,_V_radius_x,_V_radius_y,_V_color,_V_thickness);
            }
    };

    class Rectangle:public Figure
    {
        private:
            float _V_size_x=0.0;
            float _V_size_y=0.0;
        public:
            Rectangle(){}
            Rectangle(Type_pos pos_x,Type_pos pos_y,float size_x,float size_y)
            {
                set_pos(pos_x,pos_y);
                _V_size_x=size_x;
                _V_size_y=size_y;
            }
            void set_size_x(float new_size_x)
            {
                _V_size_x=new_size_x;
            }
            float get_size_x()
            {
                return _V_size_x;
            }
            void set_size_y(float new_size_y)
            {
                _V_size_y=new_size_y;
            }
            float get_size_y()
            {
                return _V_size_y;
            }
            void draw()
            {
                if(get_filled_status())
                    al_draw_filled_rectangle(_V_pos_x,_V_pos_y,_V_pos_x+(_V_size_x*bitmap_scale_x),
                                             _V_pos_y+(_V_size_y*bitmap_scale_y),_V_color);
                al_draw_rectangle(_V_pos_x,_V_pos_y,_V_pos_x+(_V_size_x*bitmap_scale_x),
                                  _V_pos_y+(_V_size_y*bitmap_scale_y),_V_color,_V_thickness*primitives_scale);
            }
            void draw_in_another_target()
            {
                if(get_filled_status())
                    al_draw_filled_rectangle(_V_pos_x,_V_pos_y,_V_pos_x+(_V_size_x),_V_pos_y+(_V_size_y),_V_color);
                al_draw_rectangle(_V_pos_x,_V_pos_y,_V_pos_x+(_V_size_x),_V_pos_y+(_V_size_y),_V_color,_V_thickness);
            }
    };

    class Triangle:public Primitive
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
            Triangle(){}
            Triangle(Type_pos pos_x1,Type_pos pos_y1,Type_pos pos_x2,Type_pos pos_y2,Type_pos pos_x3,Type_pos pos_y3)
            {
                _V_pos_x1=pos_x1;
                _V_pos_y1=pos_y1;
                _V_pos_x2=pos_x2;
                _V_pos_y2=pos_y2;
                _V_pos_x3=pos_x3;
                _V_pos_y3=pos_y3;
            }
            void set_pos(Type_pos new_cam_pos_x,Type_pos new_cam_pos_y)
            {
                _V_cam_pos_x=new_cam_pos_x;
                _V_cam_pos_y=new_cam_pos_y;
            }
            void set_pos_x(Type_pos new_cam_pos_x)
            {
                _V_cam_pos_x=new_cam_pos_x;
            }
            Type_pos get_pos_x()
            {
                return _V_cam_pos_x;
            }
            void set_pos_y(Type_pos new_cam_pos_y)
            {
                _V_cam_pos_y=new_cam_pos_y;
            }
            Type_pos get_pos_y()
            {
                return _V_cam_pos_y;
            }
            void set_points(Type_pos new_pos_x1,Type_pos new_pos_y1,
                            Type_pos new_pos_x2,Type_pos new_pos_y2,
                            Type_pos new_pos_x3,Type_pos new_pos_y3)
            {
                _V_pos_x1=new_pos_x1;
                _V_pos_y1=new_pos_y1;
                _V_pos_x2=new_pos_x2;
                _V_pos_y2=new_pos_y2;
                _V_pos_x3=new_pos_x3;
                _V_pos_y3=new_pos_y3;
            }
            void set_pos_1(Type_pos new_pos_x1,Type_pos new_pos_y1)
            {
                _V_pos_x1=new_pos_x1;
                _V_pos_y1=new_pos_y1;
            }
            Type_pos get_pos_x1()
            {
                return _V_pos_x1;
            }
            Type_pos get_pos_y1()
            {
                return _V_pos_y1;
            }
            void set_pos_2(Type_pos new_pos_x2,Type_pos new_pos_y2)
            {
                _V_pos_x2=new_pos_x2;
                _V_pos_y2=new_pos_y2;
            }
            Type_pos get_pos_x2()
            {
                return _V_pos_x2;
            }
            Type_pos get_pos_y2()
            {
                return _V_pos_y2;
            }
            void set_pos_3(Type_pos new_pos_x3,Type_pos new_pos_y3)
            {
                _V_pos_x3=new_pos_x3;
                _V_pos_y3=new_pos_y3;
            }
            Type_pos get_pos_x3()
            {
                return _V_pos_x3;
            }
            Type_pos get_pos_y3()
            {
                return _V_pos_y3;
            }
            void draw()
            {
                if(get_filled_status())
                    al_draw_filled_triangle(_V_pos_x1*bitmap_scale_x+_V_cam_pos_x,
                                            _V_pos_y1*bitmap_scale_y+_V_cam_pos_y,
                                            _V_pos_x2*bitmap_scale_x+_V_cam_pos_x,
                                            _V_pos_y2*bitmap_scale_y+_V_cam_pos_y,
                                            _V_pos_x3*bitmap_scale_x+_V_cam_pos_x,
                                            _V_pos_y3*bitmap_scale_y+_V_cam_pos_y,_V_color);
                al_draw_triangle(_V_pos_x1*bitmap_scale_x+_V_cam_pos_x,_V_pos_y1*bitmap_scale_y+_V_cam_pos_y,
                                 _V_pos_x2*bitmap_scale_x+_V_cam_pos_x,_V_pos_y2*bitmap_scale_y+_V_cam_pos_y,
                                 _V_pos_x3*bitmap_scale_x+_V_cam_pos_x,_V_pos_y3*bitmap_scale_y+_V_cam_pos_y,
                                 _V_color,_V_thickness*primitives_scale);
            }
            void draw_in_another_target()
            {
                if(get_filled_status())
                    al_draw_filled_triangle(_V_pos_x1+_V_cam_pos_x,_V_pos_y1+_V_cam_pos_y,
                                            _V_pos_x2+_V_cam_pos_x,_V_pos_y2+_V_cam_pos_y,
                                            _V_pos_x3+_V_cam_pos_x,_V_pos_y3+_V_cam_pos_y,_V_color);
                al_draw_triangle(_V_pos_x1+_V_cam_pos_x,_V_pos_y1+_V_cam_pos_y,_V_pos_x2+_V_cam_pos_x,
                                 _V_pos_y2+_V_cam_pos_y,_V_pos_x3+_V_cam_pos_x,_V_pos_y3+_V_cam_pos_y,
                                 _V_color,_V_thickness);
            }
    };

    class Function
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
            Function(Type_pos (*Function_fx)(Type_pos))
            {
                _P_Function_fx=Function_fx;
            }
            void set_pos(Type_pos new_cam_pos_x,Type_pos new_cam_pos_y)
            {
                _V_cam_pos_x=new_cam_pos_x;
                _V_cam_pos_y=new_cam_pos_y;
            }
            void set_pos_x(Type_pos new_cam_pos_x)
            {
                _V_cam_pos_x=new_cam_pos_x;
            }
            Type_pos get_pos_x()
            {
                return _V_cam_pos_x;
            }
            void set_pos_y(Type_pos new_cam_pos_y)
            {
                _V_cam_pos_y=new_cam_pos_y;
            }
            Type_pos get_pos_y()
            {
                return _V_cam_pos_y;
            }
            void set_thickness(float new_thickness)
            {
                _V_thickness=new_thickness;
            }
            float get_thickness()
            {
                return _V_thickness;
            }
            void set_color(ALLEGRO_COLOR new_color)
            {
                _V_color=new_color;
            }
            ALLEGRO_COLOR get_color()
            {
                return _V_color;
            }
            bool set_step(float new_step)
            {
                if(new_step>0)
                {
                    _V_step_function=new_step;
                    return true;
                }
                return false;
            }
            float get_step()
            {
                return _V_step_function;
            }
            void set_initial_x(Type_pos new_init)
            {
                _V_init_function=new_init;
            }
            Type_pos get_initial_x()
            {
                return _V_init_function;
            }
            void set_final_x(Type_pos new_final)
            {
                _V_final_function=new_final;
            }
            Type_pos get_final_x()
            {
                return _V_final_function;
            }
            void set_function(Type_pos (*Function_fx)(Type_pos))
            {
                _P_Function_fx=Function_fx;
            }
            void draw()
            {
                if(_V_init_function<=_V_final_function)
                {
                    Type_pos i=_V_init_function;
                    Type_pos j=_V_init_function+_V_step_function;
                    while(j<_V_final_function)
                    {
                        al_draw_line((i*bitmap_scale_x)+_V_cam_pos_x,(_P_Function_fx(i)*bitmap_scale_y)+_V_cam_pos_y,
                                     (j*bitmap_scale_x)+_V_cam_pos_x,(_P_Function_fx(j)*bitmap_scale_y)+_V_cam_pos_y,
                                     _V_color,_V_thickness*primitives_scale);
                        i+=_V_step_function;
                        j+=_V_step_function;
                    }
                    al_draw_line((i*bitmap_scale_x)+_V_cam_pos_x,
                                 (_P_Function_fx(i)*bitmap_scale_y)+_V_cam_pos_y,
                                 (_V_final_function*bitmap_scale_x)+_V_cam_pos_x,
                                 (_P_Function_fx(_V_final_function)*bitmap_scale_y)+_V_cam_pos_y,
                                 _V_color,_V_thickness*primitives_scale);
                }
            }
            void draw_in_another_target()
            {
                if(_V_init_function<=_V_final_function)
                {
                    Type_pos i=_V_init_function;
                    Type_pos j=_V_init_function+_V_step_function;
                    while(j<_V_final_function)
                    {
                        al_draw_line((i)+_V_cam_pos_x,(_P_Function_fx(i))+_V_cam_pos_y,
                                     (j)+_V_cam_pos_x,(_P_Function_fx(j))+_V_cam_pos_y,
                                     _V_color,_V_thickness);
                        i+=_V_step_function;
                        j+=_V_step_function;
                    }
                    al_draw_line((i)+_V_cam_pos_x,(_P_Function_fx(i))+_V_cam_pos_y,
                                 (_V_final_function)+_V_cam_pos_x,(_P_Function_fx(_V_final_function))+_V_cam_pos_y,
                                 _V_color,_V_thickness);
                }
            }
    };
}

#endif // INCLUDED_LL_AL5_PRIMITIVES_H
