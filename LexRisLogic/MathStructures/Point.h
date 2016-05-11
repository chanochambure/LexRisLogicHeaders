#ifndef INCLUDED_LL_MATHSTRUCTURE_POINT_H
#define INCLUDED_LL_MATHSTRUCTURE_POINT_H

#include <math.h>
#include <iostream>

namespace LL_MathStructure
{
    template<unsigned int DIMENSION>
    class Point
    {
        private:
            float _V_coordinates[DIMENSION];
        public:
            Point()
            {
                for(unsigned int i=0;i<DIMENSION;++i)
                    _V_coordinates[i]=0;
            }
            unsigned int get_dimension()
            {
                return DIMENSION;
            }
            float& operator [](unsigned int index)
            {
                return _V_coordinates[index];
            }
            Point<DIMENSION>& operator = (Point<DIMENSION> another_point)
            {
                for(unsigned int i=0;i<DIMENSION;++i)
                    (*this)[i]=another_point[i];
                return (*this);
            }
            bool operator == (Point<DIMENSION> another_point)
            {
                for(unsigned int i=0;i<DIMENSION;++i)
                {
                    if((*this)[i]!=another_point[i])
                        return false;
                }
                return true;
            }
    };

    template<unsigned int DIMENSION>
    std::ostream& operator << (std::ostream& output_streamer,Point<DIMENSION> point)
    {
        output_streamer<<"[";
        for(unsigned int i=0;i<DIMENSION-1;++i)
            output_streamer<<point[i]<<" ";
        output_streamer<<point[DIMENSION-1]<<"]";
        return output_streamer;
    }

    template<unsigned int DIMENSION>
    double euclidean_distance(Point<DIMENSION> first_point,Point<DIMENSION> second_point)
    {
        double acumulator=0;;
        for(unsigned int i=0;i<DIMENSION;++i)
            acumulator+=pow(first_point[i]-second_point[i],2);
        return sqrt(acumulator);
    }

    Point<2> create_point(float x,float y)
    {
        Point<2> point;
        point[0]=x;
        point[1]=y;
        return point;
    }

    Point<3> create_point(float x,float y,float z)
    {
        Point<3> point;
        point[0]=x;
        point[1]=y;
        point[2]=z;
        return point;
    }
}

#endif // INCLUDED_LL_MATHSTRUCTURE_POINT_H
