/* LineSegment.h -- Line Segment Math Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H
#define INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H

#include "Point.h"

namespace LL_MathStructure
{
    class LineSegment
    {
        private:
            Point _V_ini_point;
            Point _V_end_point;
            unsigned int _V_dimension=0;
        public:
            LineSegment();
            LineSegment(unsigned int dimension);
            bool set_dimension(unsigned int new_dimension);
            unsigned int get_dimension();
            bool set_ini_point(Point new_ini_point);
            const Point get_ini_point();
            bool set_end_point(Point new_end_point);
            const Point get_end_point();
            bool in_range(unsigned int dimension,float number);
    };

    bool intersection_of_lines_in_two_dimensions(LineSegment first_line,LineSegment second_line,
                                                 float* x=nullptr,float* y=nullptr);

    bool intersection_of_line_segments_in_two_dimensions(LineSegment first_segment,LineSegment second_segment,
                                                         float* x=nullptr,float* y=nullptr);
}

#endif // INCLUDED_LL_MATHSTRUCTURE_LINESEGMENT_H
