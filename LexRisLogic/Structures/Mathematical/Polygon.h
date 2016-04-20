#ifndef LL_MATH_STRUCTURE_POLYGON_H_INCLUDED
#define LL_MATH_STRUCTURE_POLYGON_H_INCLUDED

#include "Point.h"
#include "LineSegment.h"
#include <vector>

namespace LL_MathStructure
{
    class LL_Polygon
    {
        private:
            std::vector<LL_Point<2>> _points;
        public:
            void add_point(unsigned int num_points=1){while(num_points){_points.push_back(LL_Point<2>());--num_points;}}
            void add_point(LL_Point<2> point){_points.push_back(point);}
            bool remove_point(unsigned int index)
            {
                if(index>=_points.size())
                    return 0;
                _points.erase(_points.begin()+index);
                return 1;
            }
            unsigned int size(){return _points.size();}
            void clear(){_points.clear();}
            LL_Point<2>& operator [] (unsigned int index){return _points[index];}
            LL_Polygon& operator = (LL_Polygon ot){clear();add_point(ot.size());for(unsigned int i=0;i<ot.size();++i)_points[i]=ot[i];return (*this);}
    };

    bool point_in_polygon(LL_Polygon polygon,LL_Point<2> point_2D)
    {
        if(polygon.size()>2)
        {
            float maxx=polygon[0][0];
            for(unsigned int i=1;i<polygon.size();++i)
            {
                if(polygon[i][0]>maxx)
                    maxx=polygon[i][0];
            }
            unsigned int cont=0;
            for(unsigned int i=0;i<polygon.size();++i)
            {
                unsigned int j=(i+1)%polygon.size();
                cont+=intersection_of_line_segments(LL_LineSegment(point_2D[0],point_2D[1],maxx+1,point_2D[1]),LL_LineSegment(polygon[i],polygon[j]));
            }
            return cont%2;
        }
        return 0;
    }

    bool collision_of_polygons(LL_Polygon p1,LL_Polygon p2)
    {
        if(p1.size()>2 and p2.size()>2)
        {
            for(unsigned int i=0;i<p1.size();++i)
            {
                unsigned int j=(i+1)%p1.size();
                for(unsigned int k=0;k<p2.size();++k)
                {
                    unsigned int l=(k+1)%p2.size();
                    if(intersection_of_line_segments(LL_LineSegment(p1[i],p1[j]),LL_LineSegment(p2[k],p2[l])))
                        return 1;
                }
            }
            return (point_in_polygon(p1,p2[0]) or point_in_polygon(p2,p1[0]));
        }
        return 0;
    }
}

#endif // LL_MATH_STRUCTURE_POLYGON_H_INCLUDED
