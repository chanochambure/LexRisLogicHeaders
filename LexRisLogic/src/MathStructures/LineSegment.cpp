/* LineSegment.cpp -- Line Segment Math Structure Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/MathStructures/LineSegment.h"

namespace LL_MathStructure
{
    LineSegment::LineSegment()
    {
    }
    LineSegment::LineSegment(unsigned int dimension)
    {
        set_dimension(dimension);
    }
    bool LineSegment::set_dimension(unsigned int new_dimension)
    {
        if(new_dimension)
        {
            _V_dimension=new_dimension;
            _V_ini_point.set_dimension(_V_dimension);
            _V_end_point.set_dimension(_V_dimension);
            return true;
        }
        return false;
    }
    unsigned int LineSegment::get_dimension()
    {
        return _V_dimension;
    }
    bool LineSegment::set_ini_point(Point new_ini_point)
    {
        if(new_ini_point.get_dimension()==_V_dimension)
        {
            _V_ini_point=new_ini_point;
            return true;
        }
        return false;
    }
    const Point LineSegment::get_ini_point()
    {
        return _V_ini_point;
    }
    bool LineSegment::set_end_point(Point new_end_point)
    {
        if(new_end_point.get_dimension()==_V_dimension)
        {
            _V_end_point=new_end_point;
            return true;
        }
        return false;
    }
    const Point LineSegment::get_end_point()
    {
        return _V_end_point;
    }
    bool LineSegment::in_range(unsigned int dimension,float number)
    {
        return ((std::min(_V_ini_point[dimension],_V_end_point[dimension])<=number)
                and (number<=std::max(_V_ini_point[dimension],_V_end_point[dimension])));
    }

    bool intersection_of_lines_in_two_dimensions(LineSegment first_line,LineSegment second_line,float* x,float* y)
    {
        if(first_line.get_dimension()!=second_line.get_dimension() or first_line.get_dimension()!=2)
            return false;
        if((first_line.get_ini_point()==first_line.get_end_point())
           or (second_line.get_ini_point()==second_line.get_end_point()))
            return false;
        if(((first_line.get_end_point()[0]-first_line.get_ini_point()[0])
                *(second_line.get_end_point()[1]-second_line.get_ini_point()[1]))
           !=((first_line.get_end_point()[1]-first_line.get_ini_point()[1])
                *(second_line.get_end_point()[0]-second_line.get_ini_point()[0])))
        {
            float intersection_point_x,intersection_point_y;
            if(first_line.get_end_point()[0]==first_line.get_ini_point()[0])
            {
                float m2=((second_line.get_end_point()[1]-second_line.get_ini_point()[1])/
                          (second_line.get_end_point()[0]-second_line.get_ini_point()[0]));
                float b2=second_line.get_ini_point()[1]-m2*second_line.get_ini_point()[0];
                intersection_point_x=first_line.get_ini_point()[0];
                intersection_point_y=m2*intersection_point_x+b2;
            }
            else if(second_line.get_end_point()[0]==second_line.get_ini_point()[0])
            {
                float m1=((first_line.get_end_point()[1]-first_line.get_ini_point()[1])/
                          (first_line.get_end_point()[0]-first_line.get_ini_point()[0]));
                float b1=first_line.get_ini_point()[1]-m1*first_line.get_ini_point()[0];
                intersection_point_x=second_line.get_ini_point()[0];
                intersection_point_y=m1*intersection_point_x+b1;
            }
            else
            {
                float m1=((first_line.get_end_point()[1]-first_line.get_ini_point()[1])/
                          (first_line.get_end_point()[0]-first_line.get_ini_point()[0]));
                float b1=first_line.get_ini_point()[1]-m1*first_line.get_ini_point()[0];
                float m2=((second_line.get_end_point()[1]-second_line.get_ini_point()[1])/
                          (second_line.get_end_point()[0]-second_line.get_ini_point()[0]));
                float b2=second_line.get_ini_point()[1]-m2*second_line.get_ini_point()[0];
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

    bool intersection_of_line_segments_in_two_dimensions(LineSegment first_segment,LineSegment second_segment,
                                                         float* x,float* y)
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
