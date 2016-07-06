/* Polygon.h -- Polygon Math Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_MATHSTRUCTURE_POLYGON_H
#define INCLUDED_LL_MATHSTRUCTURE_POLYGON_H

#include "Point.h"
#include "LineSegment.h"
#include <vector>
#include <list>

namespace LL_MathStructure
{
    class Polygon
    {
        private:
            std::vector<Point<2>> _V_points;
        public:
            void add_point(Point<2> point)
            {
                _V_points.push_back(point);
            }
            bool remove_point(unsigned int index)
            {
                if(index>=_V_points.size())
                    return false;
                _V_points.erase(_V_points.begin()+index);
                return true;
            }
            unsigned int size()
            {
                return _V_points.size();
            }
            void clear()
            {
                _V_points.clear();
            }
            Point<2>& operator [] (unsigned int index)
            {
                return _V_points[index];
            }
            Polygon& operator = (Polygon another_polygon)
            {
                _V_points.clear();
                for(unsigned int i=0;i<another_polygon.size();++i)
                    add_point(another_polygon[i]);
                return (*this);
            }
    };

    bool point_into_polygon(Polygon polygon,Point<2> point)
    {
        if(polygon.size()>2)
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
                count_intersection+=intersection_of_line_segments_in_two_dimensions(
                                                            LineSegment<2>(point,create_point(max_pos_x+1,point[1])),
                                                            LineSegment<2>(polygon[i],polygon[j]));
            }
            return count_intersection%2;
        }
        return false;
    }

    bool collision_of_polygons(Polygon first_polygon,Polygon second_polygon,std::list<Point<2>>* points=nullptr)
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
                    if(intersection_of_line_segments_in_two_dimensions(
                                                            LineSegment<2>(first_polygon[i],first_polygon[j]),
                                                            LineSegment<2>(second_polygon[k],second_polygon[l]),
                                                            &intersection_x,&intersection_y))
                    {
                        if(points)
                        {
                            bool insertion=true;
                            for(std::list<Point<2>>::iterator m=points->begin();m!=points->end();++m)
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


#endif // INCLUDED_LL_MATHSTRUCTURE_POLYGON_H
