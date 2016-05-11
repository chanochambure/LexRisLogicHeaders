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
