/* LineSegment.h -- Line Segment Math Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H
#define INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H

#include "Point.h"

namespace LL_MathStructure
{
    template<unsigned int DIMENSION>
    class LineSegment
    {
        private:
            Point _V_ini_point;
            Point _V_end_point;
        public:
            LineSegment()
            {
                _V_ini_point.set_dimension(DIMENSION);
                _V_end_point.set_dimension(DIMENSION);
            }
            LineSegment(Point ini_point,Point end_point)
            {
                _V_ini_point.set_dimension(DIMENSION);
                _V_end_point.set_dimension(DIMENSION);
                _V_ini_point=ini_point;
                _V_end_point=end_point;
            }
            unsigned int get_dimension()
            {
                return DIMENSION;
            }
            Point& ini_point()
            {
                return _V_ini_point;
            }
            Point& end_point()
            {
                return _V_end_point;
            }
            bool in_range(unsigned int dimension,float number)
            {
                return ((std::min(_V_ini_point[dimension],_V_end_point[dimension])<=number)
                        and (number<=std::max(_V_ini_point[dimension],_V_end_point[dimension])));
            }
    };

    bool intersection_of_lines_in_two_dimensions(LineSegment<2> first_line,LineSegment<2> second_line,
                                                 float* x=nullptr,float* y=nullptr)
    {
        if((first_line.ini_point()==first_line.end_point())
           or (second_line.ini_point()==second_line.end_point()))
            return false;
        if(((first_line.end_point()[0]-first_line.ini_point()[0])
                *(second_line.end_point()[1]-second_line.ini_point()[1]))
           !=((first_line.end_point()[1]-first_line.ini_point()[1])
                *(second_line.end_point()[0]-second_line.ini_point()[0])))
        {
            float intersection_point_x,intersection_point_y;
            if(first_line.end_point()[0]==first_line.ini_point()[0])
            {
                float m2=((second_line.end_point()[1]-second_line.ini_point()[1])/
                          (second_line.end_point()[0]-second_line.ini_point()[0]));
                float b2=second_line.ini_point()[1]-m2*second_line.ini_point()[0];
                intersection_point_x=first_line.ini_point()[0];
                intersection_point_y=m2*intersection_point_x+b2;
            }
            else if(second_line.end_point()[0]==second_line.ini_point()[0])
            {
                float m1=((first_line.end_point()[1]-first_line.ini_point()[1])/
                          (first_line.end_point()[0]-first_line.ini_point()[0]));
                float b1=first_line.ini_point()[1]-m1*first_line.ini_point()[0];
                intersection_point_x=second_line.ini_point()[0];
                intersection_point_y=m1*intersection_point_x+b1;
            }
            else
            {
                float m1=((first_line.end_point()[1]-first_line.ini_point()[1])/
                          (first_line.end_point()[0]-first_line.ini_point()[0]));
                float b1=first_line.ini_point()[1]-m1*first_line.ini_point()[0];
                float m2=((second_line.end_point()[1]-second_line.ini_point()[1])/
                          (second_line.end_point()[0]-second_line.ini_point()[0]));
                float b2=second_line.ini_point()[1]-m2*second_line.ini_point()[0];
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

    bool intersection_of_line_segments_in_two_dimensions(LineSegment<2> first_segment,LineSegment<2> second_segment,
                                                         float* x=nullptr,float* y=nullptr)
    {
        float intersection_point_x,intersection_point_y;
        if(intersection_of_lines_in_two_dimensions(first_segment,second_segment,
                                                   &intersection_point_x,&intersection_point_y))
        {
            if(x and y)
            {
                *x=intersection_point_x;
                *y=intersection_point_y;
            }
            return ((first_segment.in_range(0,intersection_point_x)
                    and first_segment.in_range(1,intersection_point_y))
                    and (second_segment.in_range(0,intersection_point_x)
                    and second_segment.in_range(1,intersection_point_y)));
        }
        return false;
    }
}

#endif // INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H
