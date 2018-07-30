/* Interval.h -- Interval Math Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_MATHSTRUCTURE_INTERVAL_H
#define INCLUDED_LL_MATHSTRUCTURE_INTERVAL_H

#include "../LL_Shared.h"

#include <iostream>
#include <algorithm>

namespace LL_MathStructure
{
    class LL_SHARED Interval
    {
        private:
            float _V_data[2]={0.0, 0.0};
            void _F_set_data(float left,float right);
        public:
            Interval();
            Interval(float left,float right);
            bool set_left(float new_left);
            bool set_right(float new_right);
            void set_data(float new_left,float new_right);
            float get_mid_point() const;
            bool contains(float point) const;
            bool contains(const Interval& another_interval) const;
            bool intersects(const Interval& another_interval) const;
            bool is_left_of(float point) const;
            bool is_right_of(float point) const;
            bool is_left_of(const Interval& another_interval) const;
            bool is_right_of(const Interval& another_interval) const;
            const float operator [](unsigned int index) const;
            bool operator == (const Interval& another_interval) const;
            bool operator != (const Interval& another_interval) const;
            bool operator < (const Interval& another_interval) const;
    };

    std::ostream& LL_SHARED operator << (std::ostream& output_stream,Interval interval);
}

#endif // INCLUDED_LL_MATHSTRUCTURE_INTERVAL_H
