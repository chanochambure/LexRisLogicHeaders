/* Time.cpp -- Time Source - LexRis Logic Headers

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

#include "../include/LexRisLogic/Time.h"

namespace LL
{
    Chronometer::_T_Type_clock Chronometer::_F_get_clock()
    {
        return std::chrono::high_resolution_clock::now();
    }
    bool Chronometer::play()
    {
        if(_V_stopped)
        {
            _V_time=0.0;
            _V_stopped=false;
        }
        if(_V_in_pause)
        {
            _V_point=_F_get_clock();
            _V_in_pause=false;
            return true;
        }
        return false;
    }
    bool Chronometer::pause()
    {
        if(!_V_in_pause)
        {
            _V_time+=std::chrono::duration_cast<_T_Type_duration>(_F_get_clock()-_V_point).count();
            _V_in_pause=true;
            return true;
        }
        return false;
    }
    bool Chronometer::stop()
    {
        if(!_V_stopped)
        {
            _V_stopped=true;
            pause();
            return true;
        }
        return false;
    }
    const double Chronometer::get_time()
    {
        if(!_V_in_pause)
            return _V_time+std::chrono::duration_cast<_T_Type_duration>(_F_get_clock()-_V_point).count();
        return _V_time;
    }
    void Chronometer::clear()
    {
        _V_time=0.0;
        _V_point=_F_get_clock();
    }
}
