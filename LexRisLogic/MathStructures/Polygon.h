#ifndef LL_MATH_STRUCTURE_POLYGON_H_INCLUDED
#define LL_MATH_STRUCTURE_POLYGON_H_INCLUDED

#include "Point.h"
#include "LineSegment.h"
#include <vector>

namespace LL_MathStructure
{
    class Polygon
    {
        public:
            typedef Point<2> Type_point;
        private:
            std::vector<Type_point> _V_points;
        public:
            void add_point(Type_point point)
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
            Type_point& operator [] (unsigned int index)
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

    bool point_into_polygon(Polygon polygon,Polygon::Type_point point)
    {
        if(polygon.size()>2)
        {
            float max_posx=polygon[0][0];
            for(unsigned int i=1;i<polygon.size();++i)
            {
                if(polygon[i][0]>max_posx)
                    max_posx=polygon[i][0];
            }
            unsigned int count_intersection=0;
            for(unsigned int i=0;i<polygon.size();++i)
            {
                unsigned int j=(i+1)%polygon.size();
                count_intersection+=intersection_of_line_segments(LineSegment(point,create_point(max_posx+1,point[1])),
                                                    LineSegment(polygon[i],polygon[j]));
            }
            return count_intersection%2;
        }
        return false;
    }

    bool collision_of_polygons(Polygon first_polygon,Polygon second_polygon)
    {
        if(first_polygon.size()>2 and second_polygon.size()>2)
        {
            for(unsigned int i=0;i<first_polygon.size();++i)
            {
                unsigned int j=(i+1)%first_polygon.size();
                for(unsigned int k=0;k<second_polygon.size();++k)
                {
                    unsigned int l=(k+1)%second_polygon.size();
                    if(intersection_of_line_segments(LineSegment(first_polygon[i],first_polygon[j]),
                                                     LineSegment(second_polygon[k],second_polygon[l])))
                        return true;
                }
            }
            return (point_into_polygon(first_polygon,second_polygon[0]) or point_into_polygon(second_polygon,first_polygon[0]));
        }
        return false;
    }
}

#endif // LL_MATH_STRUCTURE_POLYGON_H_INCLUDED