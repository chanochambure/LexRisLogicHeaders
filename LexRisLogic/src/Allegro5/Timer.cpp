/* Timer.cpp -- Timer Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/Timer.h"

namespace LL_AL5
{
    Timer::Timer()
    {
    }
    bool Timer::set_speed_seconds(double new_speed_seconds)
    {
        if(!_V_timer && new_speed_seconds>0.0)
        {
            _V_speed_seconds=new_speed_seconds;
            return true;
        }
        return false;
    }
    double Timer::get_speed_seconds()
    {
        return _V_speed_seconds;
    }
    bool Timer::create()
    {
        if(!_V_timer)
        {
            _V_timer=al_create_timer(_V_speed_seconds);
            return _V_timer;
        }
        return false;
    }
    bool Timer::destroy()
    {
        if(_V_timer)
        {
            al_destroy_timer(_V_timer);
            _V_timer=nullptr;
            return true;
        }
        return false;
    }
    bool Timer::start()
    {
        if(_V_timer)
        {
            al_start_timer(_V_timer);
            return true;
        }
        return false;
    }
    bool Timer::resume()
    {
        if(_V_timer)
        {
            al_resume_timer(_V_timer);
            return true;
        }
        return false;
    }
    bool Timer::stop()
    {
        if(_V_timer)
        {
            al_stop_timer(_V_timer);
            return true;
        }
        return false;
    }
    Timer::operator ALLEGRO_TIMER* ()
    {
        return _V_timer;
    }
    Timer::~Timer()
    {
        destroy();
    }
}
