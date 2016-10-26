/* Math.cpp -- Math Source - LexRis Logic Headers

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

#include "Math.h"

namespace LL
{
    int mod(int dividend,int divisor)
    {
        return ((dividend%divisor)+divisor)%divisor;
    }

    double range_mod(double dividend,double divisor)
    {
        return fmod(fmod(dividend,divisor)+divisor,divisor);
    }

    float sexagesimal_to_radian(float sexagesimal)
    {
        return (sexagesimal*MATH_PI)/180;
    }

    float radian_to_sexagesimal(float radian)
    {
        return (radian*180)/MATH_PI;
    }

    void random_generate_new_seed()
    {
        srand(time(nullptr));
    }

    int random(int min_value,int max_value,bool include_max_value)
    {
        return mod(rand(),(max_value-min_value+include_max_value))+min_value;
    }

    bool segment_collision(float ini_segment_1,float fin_segment_1,float ini_segment_2,float fin_segment_2)
    {
        int ini_segment=std::max(ini_segment_1,ini_segment_2);
        int fin_segment=std::min(fin_segment_1,fin_segment_2);
        return (ini_segment<=fin_segment);
    }

    int max_integer(float number)
    {
        return (int(number)-(number<0.0));
    }
}
