#ifndef LL_MATH_STRUCTURE_POINT_H_INCLUDED
#define LL_MATH_STRUCTURE_POINT_H_INCLUDED

#include <math.h>
#include <iostream>

namespace LL_MathStructure
{
    template<int D>
    class LL_Point
    {
        private:
            float dots[D];
        public:
            LL_Point(){for(int i=0;i<D;++i)dots[i]=0;}
            int get_dimension(){return D;}
            float& operator [](unsigned int i){return dots[i];}
            LL_Point<D>& operator = (LL_Point<D> ot){for(int i=0;i<D;++i)(*this)[i]=ot[i];return (*this);}
            bool operator == (LL_Point<D> ot){for(int i=0;i<D;++i){if((*this)[i]!=ot[i])return 0;}return 1;}
    };

    template<int D>
    std::ostream& operator << (std::ostream& os,LL_Point<D> dot)
    {
        os<<"[";
        for(unsigned int i=0;i<D-1;++i)
            os<<dot[i]<<" ";
        os<<dot[D-1]<<"]";
        return os;
    }

    template<int D>
    double euclidean_distance(LL_Point<D> one,LL_Point<D> two)
    {
        double acum=0;;
        for(int i=0;i<D;++i)
            acum+=pow(one[i]-two[i],2);
        return sqrt(acum);
    }

    LL_Point<2> create_point(float x,float y){LL_Point<2> point;point[0]=x;point[1]=y;return point;}
    LL_Point<3> create_point(float x,float y,float z){LL_Point<3> point;point[0]=x;point[1]=y;point[2]=z;return point;}
}

#endif // LL_MATH_STRUCTURE_POINT_H_INCLUDED
