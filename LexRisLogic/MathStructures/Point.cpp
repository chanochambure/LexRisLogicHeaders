/* Point.cpp -- Point Math Structure Source - LexRis Logic Headers

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

#include "Point.h"

namespace LL_MathStructure
{
    void Point::_F_delete_coordinates()
    {
        if(_V_coordinates)
            delete(_V_coordinates);
        _V_coordinates=nullptr;
    }
    void Point::_F_create_coordinates()
    {
        _F_delete_coordinates();
        _V_coordinates=new float[_V_dimension];
        for(unsigned int i=0;i<_V_dimension;++i)
            _V_coordinates[i]=0.0;
    }
    void Point::_F_set_data(const Point& another_point)
    {
        for(unsigned int i=0;i<_V_dimension;++i)
            (*this)[i]=another_point[i];
    }
    Point::Point()
    {
    }
    Point::Point(unsigned int dimension)
    {
        set_dimension(dimension);
    }
    Point::Point(const Point& another_point)
    {
        set_dimension(another_point.get_dimension());
        _F_set_data(another_point);
    }
    bool Point::set_dimension(unsigned int new_dimension)
    {
        if(new_dimension)
        {
            _V_dimension=new_dimension;
            _F_create_coordinates();
            return true;
        }
        return false;
    }
    unsigned int Point::get_dimension() const
    {
        return _V_dimension;
    }
    float& Point::operator [](unsigned int index)
    {
        return _V_coordinates[index];
    }
    const float Point::operator [](unsigned int index) const
    {
        return _V_coordinates[index];
    }
    Point& Point::operator = (const Point& another_point)
    {
        this->set_dimension(another_point.get_dimension());
        this->_F_set_data(another_point);
        return (*this);
    }
    bool Point::operator == (const Point& another_point) const
    {
        if(_V_dimension!=another_point.get_dimension())
            return false;
        for(unsigned int i=0;i<_V_dimension;++i)
        {
            if((*this)[i]!=another_point[i])
                return false;
        }
        return true;
    }
    Point::~Point()
    {
        _F_delete_coordinates();
    }

    std::ostream& operator << (std::ostream& output_streamer,Point point)
    {
        output_streamer<<"[";
        for(unsigned int i=0;i<point.get_dimension()-1;++i)
            output_streamer<<point[i]<<" ";
        output_streamer<<point[point.get_dimension()-1]<<"]";
        return output_streamer;
    }

    double euclidean_distance(Point first_point,Point second_point)
    {
        if(first_point.get_dimension()==second_point.get_dimension())
        {
            double acumulator=0;;
            for(unsigned int i=0;i<first_point.get_dimension();++i)
                acumulator+=pow(first_point[i]-second_point[i],2);
            return sqrt(acumulator);
        }
        return 0.0;
    }

    Point create_point(float x,float y)
    {
        Point point(2);
        point[0]=x;
        point[1]=y;
        return point;
    }

    Point create_point(float x,float y,float z)
    {
        Point point(3);
        point[0]=x;
        point[1]=y;
        point[2]=z;
        return point;
    }
}
