/* Math.h -- Math Header - LexRis Logic Headers

    Copyright (c) 2017-2019 LexRisLogic

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

#ifndef INCLUDED_LL_MATH_H
#define INCLUDED_LL_MATH_H

#include "LL_Shared.h"

#include <math.h>
#include <time.h>
#include <random>

namespace LL
{
    static const double MATH_PI=3.14159265358979323846;

    int LL_SHARED mod(int dividend,int divisor);

    double LL_SHARED range_mod(double dividend,double divisor);

    float LL_SHARED sexagesimal_to_radian(float sexagesimal);

    float LL_SHARED radian_to_sexagesimal(float radian);

    void LL_SHARED random_generate_new_seed();

    int LL_SHARED random(int min_value,int max_value,bool include_max_value=false);

    bool LL_SHARED segment_collision(float ini_segment_1,float fin_segment_1,float ini_segment_2,float fin_segment_2);

    int LL_SHARED max_integer(float number);
}

#endif // INCLUDED_LL_MATH_H
