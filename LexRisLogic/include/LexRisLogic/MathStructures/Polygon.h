/* Polygon.h -- Polygon Math Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_MATHSTRUCTURE_POLYGON_H
#define INCLUDED_LL_MATHSTRUCTURE_POLYGON_H

#include "../LL_Shared.h"

#include "Point.h"
#include "LineSegment.h"
#include <vector>
#include <list>

namespace LL_MathStructure
{
    class LL_SHARED Polygon
    {
        private:
            std::vector<Point> _V_points;
        public:
            bool add_point(Point point);
            bool remove_point(unsigned int index);
            unsigned int size();
            void clear();
            bool set_point(unsigned int index,Point new_point);
            const Point operator [] (unsigned int index);
    };

    bool LL_SHARED point_into_polygon(Polygon polygon,Point point);

    bool LL_SHARED collision_of_polygons(Polygon first_polygon,Polygon second_polygon,
                                         std::list<Point>* points=nullptr);
}

#endif // INCLUDED_LL_MATHSTRUCTURE_POLYGON_H
