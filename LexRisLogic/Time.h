/* Time.h -- Time Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_TIME_H
#define INCLUDED_LL_TIME_H

#include <time.h>

namespace LL
{
    class Chronometer
    {
        private:
            clock_t _V_point;
            double _V_time=0;
            bool _V_in_pause=true;
            bool _V_stopped=true;
        public:
            bool play()
            {
                if(_V_stopped)
                {
                    _V_time=0;
                    _V_stopped=false;
                }
                if(_V_in_pause)
                {
                    _V_point=clock();
                    _V_in_pause=false;
                    return true;
                }
                return false;
            }
            bool pause()
            {
                if(!_V_in_pause)
                {
                    _V_time+=((double(clock()-_V_point))/CLOCKS_PER_SEC);
                    _V_in_pause=true;
                    return true;
                }
                return false;
            }
            bool stop()
            {
                if(!_V_stopped)
                {
                    _V_stopped=true;
                    pause();
                    return true;
                }
                return false;
            }
            double get_time()
            {
                if(!_V_in_pause)
                    return _V_time+((double(clock()-_V_point))/CLOCKS_PER_SEC);
                return _V_time;
            }
            void clear()
            {
                _V_time=0;
                _V_point=clock();
            }
};
}

#endif // INCLUDED_LL_TIME_H
