#ifndef LL_POLYGON_H_INCLUDED
#define LL_POLYGON_H_INCLUDED

#include "LL_Point.h"
#include <vector>

using namespace std;

class LL_Polygon
{
    private:
        vector<LL_Point<2>> _points;
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

#endif // LL_POLYGON_H_INCLUDED
