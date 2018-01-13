/* Time.h -- Time Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_TIME_H
#define INCLUDED_LL_TIME_H

#include "LL_Shared.h"

#include <chrono>

namespace LL
{
    class LL_SHARED Chronometer
    {
        private:
            typedef std::chrono::high_resolution_clock::time_point _T_Type_clock;
            typedef std::chrono::duration<double> _T_Type_duration;
            _T_Type_clock _V_point;
            double _V_time=0.0;
            bool _V_in_pause=true;
            bool _V_stopped=true;
            _T_Type_clock _F_get_clock();
        public:
            bool play();
            bool pause();
            bool stop();
            const double get_time();
            void clear();
    };
}

#endif // INCLUDED_LL_TIME_H
