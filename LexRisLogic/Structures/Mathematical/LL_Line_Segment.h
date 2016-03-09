#ifndef LL_MATH_STRUCTURE_LINE_SEGMENT_H_INCLUDED
#define LL_MATH_STRUCTURE_LINE_SEGMENT_H_INCLUDED

#include "LL_Point.h"

namespace LL_MathStructure
{
    class LL_LineSegment
    {
        private:
            LL_Point<2> p1;
            LL_Point<2> p2;
        public:
            LL_LineSegment(){}
            LL_LineSegment(LL_Point<2> point1,LL_Point<2> point2){p1=point1;p2=point2;}
            LL_LineSegment(float posx1,float posy1,float posx2,float posy2){p1[0]=posx1;p1[1]=posy1;p2[0]=posx2;p2[1]=posy2;}
            void set_points(float posx1,float posy1,float posx2,float posy2){p1[0]=posx1;p1[1]=posy1;p2[0]=posx2;p2[1]=posy2;}
            void set_point_1(float xx,float yy){p1[0]=xx;p1[1]=yy;}
            void set_point_1(LL_Point<2> point){p1=point;}
            float get_posx_point1(){return p1[0];}
            float get_posy_point1(){return p1[1];}
            LL_Point<2> get_point1(){return p1;}
            void set_point_2(float xx,float yy){p2[0]=xx;p2[1]=yy;}
            void set_point_2(LL_Point<2> point){p2=point;}
            float get_posx_point2(){return p2[0];}
            float get_posy_point2(){return p2[1];}
            LL_Point<2> get_point2(){return p2;}
            bool num_in_interval_x(float num){return (std::min(p1[0],p2[0])<=num and num<=std::max(p1[0],p2[0]));}
            bool num_in_interval_y(float num){return (std::min(p1[1],p2[1])<=num and num<=std::max(p1[1],p2[1]));}
    };

    bool intersection_of_lines(LL_LineSegment seg1,LL_LineSegment seg2,float* x=nullptr,float* y=nullptr)
    {
        if((seg1.get_posx_point1()==seg1.get_posx_point2() and seg1.get_posy_point1()==seg1.get_posy_point2()) or (seg2.get_posx_point1()==seg2.get_posx_point2() and seg2.get_posy_point1()==seg2.get_posy_point2()))
            return 0;
        if(((seg1.get_posx_point2()-seg1.get_posx_point1())*(seg2.get_posy_point2()-seg2.get_posy_point1()))!=((seg1.get_posy_point2()-seg1.get_posy_point1())*(seg2.get_posx_point2()-seg2.get_posx_point1())))
        {
            float x3,y3;
            if(seg1.get_posx_point2()==seg1.get_posx_point1())
            {
                float m2=((seg2.get_posy_point2()-seg2.get_posy_point1())/(seg2.get_posx_point2()-seg2.get_posx_point1()));
                float b2=seg2.get_posy_point1()-m2*seg2.get_posx_point1();
                x3=seg1.get_posx_point1();
                y3=m2*x3+b2;
            }
            else if(seg2.get_posx_point2()==seg2.get_posx_point1())
            {
                float m1=((seg1.get_posy_point2()-seg1.get_posy_point1())/(seg1.get_posx_point2()-seg1.get_posx_point1()));
                float b1=seg1.get_posy_point1()-m1*seg1.get_posx_point1();
                x3=seg2.get_posx_point1();
                y3=m1*x3+b1;
            }
            else
            {
                float m1=((seg1.get_posy_point2()-seg1.get_posy_point1())/(seg1.get_posx_point2()-seg1.get_posx_point1()));
                float b1=seg1.get_posy_point1()-m1*seg1.get_posx_point1();
                float m2=((seg2.get_posy_point2()-seg2.get_posy_point1())/(seg2.get_posx_point2()-seg2.get_posx_point1()));
                float b2=seg2.get_posy_point1()-m2*seg2.get_posx_point1();
                x3=(b2-b1)/(m1-m2);
                y3=m1*x3+b1;
            }
            if(x and y)
            {
                *x=x3;
                *y=y3;
            }
            return 1;
        }
        return 0;
    }

    bool intersection_of_line_segments(LL_LineSegment seg1,LL_LineSegment seg2)
    {
        float x3,y3;
        if(intersection_of_lines(seg1,seg2,&x3,&y3))
            return (seg1.num_in_interval_x(x3) and seg1.num_in_interval_y(y3)) and (seg2.num_in_interval_x(x3) and seg2.num_in_interval_y(y3));
        return 0;
    }
}

#endif // LL_MATH_STRUCTURE_LINE_SEGMENT_H_INCLUDED
