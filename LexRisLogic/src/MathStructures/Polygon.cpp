/* Polygon.cpp -- Polygon Math Structure Source - LexRis Logic Headers

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


#include "../../include/MathStructures/Polygon.h"

namespace LL_MathStructure
{
    bool Polygon::add_point(Point point)
    {
        if(point.get_dimension()==2)
        {
            _V_points.push_back(point);
            return true;
        }
        return false;
    }
    bool Polygon::remove_point(unsigned int index)
    {
        if(index>=_V_points.size())
            return false;
        _V_points.erase(_V_points.begin()+index);
        return true;
    }
    unsigned int Polygon::size()
    {
        return _V_points.size();
    }
    void Polygon::clear()
    {
        _V_points.clear();
    }
    bool Polygon::set_point(unsigned int index,Point new_point)
    {
        if(new_point.get_dimension()==2 and index<_V_points.size())
        {
            _V_points[index]=new_point;
            return true;
        }
        return false;
    }
    const Point Polygon::operator [] (unsigned int index)
    {
        return _V_points[index];
    }

    bool point_into_polygon(Polygon polygon,Point point)
    {
        if(point.get_dimension()==2 and polygon.size()>2)
        {
            float max_pos_x=polygon[0][0];
            for(unsigned int i=1;i<polygon.size();++i)
            {
                if(polygon[i][0]>max_pos_x)
                    max_pos_x=polygon[i][0];
            }
            unsigned int count_intersection=0;
            for(unsigned int i=0;i<polygon.size();++i)
            {
                unsigned int j=(i+1)%polygon.size();
                LineSegment first_segment(2);
                first_segment.set_ini_point(point);
                first_segment.set_end_point(create_point(max_pos_x+1,point[1]));
                LineSegment second_segment(2);
                second_segment.set_ini_point(polygon[i]);
                second_segment.set_end_point(polygon[j]);
                count_intersection+=intersection_of_line_segments_in_two_dimensions(first_segment,second_segment);
            }
            return count_intersection%2;
        }
        return false;
    }

    bool collision_of_polygons(Polygon first_polygon,Polygon second_polygon,std::list<Point>* points)
    {
        if(first_polygon.size()>2 and second_polygon.size()>2)
        {
            for(unsigned int i=0;i<first_polygon.size();++i)
            {
                unsigned int j=(i+1)%first_polygon.size();
                for(unsigned int k=0;k<second_polygon.size();++k)
                {
                    unsigned int l=(k+1)%second_polygon.size();
                    float intersection_x;
                    float intersection_y;
                    LineSegment first_segment(2);
                    first_segment.set_ini_point(first_polygon[i]);
                    first_segment.set_end_point(first_polygon[j]);
                    LineSegment second_segment(2);
                    second_segment.set_ini_point(second_polygon[k]);
                    second_segment.set_end_point(second_polygon[l]);
                    if(intersection_of_line_segments_in_two_dimensions(first_segment,second_segment,
                                                                       &intersection_x,&intersection_y))
                    {
                        if(points)
                        {
                            bool insertion=true;
                            for(std::list<Point>::iterator m=points->begin();m!=points->end();++m)
                            {
                                if((*m)[0]==intersection_x and (*m)[1]==intersection_y)
                                {
                                    insertion=false;
                                    break;
                                }
                            }
                            if(insertion)
                                points->push_back(create_point(intersection_x,intersection_y));
                        }
                        else
                            return true;
                    }
                }
            }
            if(points and points->size())
                return true;
            return (point_into_polygon(first_polygon,second_polygon[0]) or
                    point_into_polygon(second_polygon,first_polygon[0]));
        }
        return false;
    }
}
