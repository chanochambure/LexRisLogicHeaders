#ifndef INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H
#define INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H

#include "Point.h"

namespace LL_MathStructure
{
    class LineSegment
    {
        public:
            typedef Point<2> Type_point;
        private:
            Type_point _V_ini_point;
            Type_point _V_end_point;
        public:
            LineSegment(){}
            LineSegment(Type_point ini_point,Type_point end_point)
            {
                _V_ini_point=ini_point;
                _V_end_point=end_point;
            }
            Type_point get_ini_point()
            {
                return _V_ini_point;
            }
            Type_point get_end_point()
            {
                return _V_end_point;
            }
            void set_ini_point(Type_point point)
            {
                _V_ini_point=point;
            }
            void set_end_point(Type_point point)
            {
                _V_end_point=point;
            }
            float get_posx_ini_point()
            {
                return _V_ini_point[0];
            }
            float get_posy_ini_point()
            {
                return _V_ini_point[1];
            }
            float get_posx_end_point()
            {
                return _V_end_point[0];
            }
            float get_posy_end_point()
            {
                return _V_end_point[1];
            }
            bool in_range_x(float number_x)
            {
                return ((std::min(_V_ini_point[0],_V_end_point[0])<=number_x)
                        and (number_x<=std::max(_V_ini_point[0],_V_end_point[0])));
            }
            bool in_range_y(float number_y)
            {
                return ((std::min(_V_ini_point[1],_V_end_point[1])<=number_y)
                        and number_y<=std::max(_V_ini_point[1],_V_end_point[1]));
            }
    };

    bool intersection_of_lines(LineSegment first_segment,LineSegment second_segment,float* x=nullptr,float* y=nullptr)
    {
        if((first_segment.get_posx_ini_point()==first_segment.get_posx_end_point()
                and first_segment.get_posy_ini_point()==first_segment.get_posy_end_point())
                or (second_segment.get_posx_ini_point()==second_segment.get_posx_end_point()
                and second_segment.get_posy_ini_point()==second_segment.get_posy_end_point()))
            return false;
        if(((first_segment.get_posx_end_point()-first_segment.get_posx_ini_point())
                *(second_segment.get_posy_end_point()-second_segment.get_posy_ini_point()))
                !=((first_segment.get_posy_end_point()-first_segment.get_posy_ini_point())
                *(second_segment.get_posx_end_point()-second_segment.get_posx_ini_point())))
        {
            float intersection_point_x,intersection_point_y;
            if(first_segment.get_posx_end_point()==first_segment.get_posx_ini_point())
            {
                float m2=((second_segment.get_posy_end_point()-second_segment.get_posy_ini_point())/
                          (second_segment.get_posx_end_point()-second_segment.get_posx_ini_point()));
                float b2=second_segment.get_posy_ini_point()-m2*second_segment.get_posx_ini_point();
                intersection_point_x=first_segment.get_posx_ini_point();
                intersection_point_y=m2*intersection_point_x+b2;
            }
            else if(second_segment.get_posx_end_point()==second_segment.get_posx_ini_point())
            {
                float m1=((first_segment.get_posy_end_point()-first_segment.get_posy_ini_point())/
                          (first_segment.get_posx_end_point()-first_segment.get_posx_ini_point()));
                float b1=first_segment.get_posy_ini_point()-m1*first_segment.get_posx_ini_point();
                intersection_point_x=second_segment.get_posx_ini_point();
                intersection_point_y=m1*intersection_point_x+b1;
            }
            else
            {
                float m1=((first_segment.get_posy_end_point()-first_segment.get_posy_ini_point())/
                          (first_segment.get_posx_end_point()-first_segment.get_posx_ini_point()));
                float b1=first_segment.get_posy_ini_point()-m1*first_segment.get_posx_ini_point();
                float m2=((second_segment.get_posy_end_point()-second_segment.get_posy_ini_point())/
                          (second_segment.get_posx_end_point()-second_segment.get_posx_ini_point()));
                float b2=second_segment.get_posy_ini_point()-m2*second_segment.get_posx_ini_point();
                intersection_point_x=(b2-b1)/(m1-m2);
                intersection_point_y=m1*intersection_point_x+b1;
            }
            if(x and y)
            {
                *x=intersection_point_x;
                *y=intersection_point_y;
            }
            return true;
        }
        return false;
    }

    bool intersection_of_line_segments(LineSegment first_segment,LineSegment second_segment)
    {
        float intersection_point_x,intersection_point_y;
        if(intersection_of_lines(first_segment,second_segment,&intersection_point_x,&intersection_point_y))
            return ((first_segment.in_range_x(intersection_point_x)
                    and first_segment.in_range_y(intersection_point_y))
                    and (second_segment.in_range_x(intersection_point_x)
                    and second_segment.in_range_y(intersection_point_y)));
        return false;
    }
}

#endif // INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H
