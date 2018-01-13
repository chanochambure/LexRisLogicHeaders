/* Point.h -- Point Math Structure Header - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

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

#ifndef INCLUDED_LL_MATHSTRUCTURE_POINT_H
#define INCLUDED_LL_MATHSTRUCTURE_POINT_H

#include "../LL_Shared.h"

#include <math.h>
#include <iostream>

namespace LL_MathStructure
{
    class LL_SHARED Point
    {
        private:
            unsigned int _V_dimension=0;
            float* _V_coordinates=nullptr;
            void _F_delete_coordinates();
            void _F_create_coordinates();
            void _F_set_data(const Point& another_point);
        public:
            Point();
            Point(unsigned int dimension);
            Point(const Point& another_point);
            bool set_dimension(unsigned int new_dimension);
            unsigned int get_dimension() const;
            float& operator [](unsigned int index);
            const float operator [](unsigned int index) const;
            Point& operator = (const Point& another_point);
            bool operator == (const Point& another_point) const;
            bool operator != (const Point& another_point) const;
            ~Point();
    };

    std::ostream& LL_SHARED operator << (std::ostream& output_stream,Point point);

    double LL_SHARED euclidean_distance(Point first_point,Point second_point);

    Point LL_SHARED create_point(float x,float y);

    Point LL_SHARED create_point(float x,float y,float z);
}

#endif // INCLUDED_LL_MATHSTRUCTURE_POINT_H
