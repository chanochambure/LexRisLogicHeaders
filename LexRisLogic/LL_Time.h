#ifndef LL_TIME_H_INCLUDED
#define LL_TIME_H_INCLUDED
#include <time.h>

class Chronometer
{
    private:
        clock_t point;
        double _time_=0;
        bool in_pause=1;
        bool stoped=1;
    public:
        bool play(){if(stoped){_time_=0;stoped=0;}if(in_pause){point=clock();in_pause=0;return 1;}return 0;}
        bool pause(){if(!in_pause){_time_+=(((double)(clock()-point))/CLOCKS_PER_SEC);in_pause=1;return 1;}return 0;}
        bool stop(){if(!stoped){stoped=1;pause();return 1;}return 0;}
        double get_time(){if(!in_pause)return _time_+(((double)(clock()-point))/CLOCKS_PER_SEC);return _time_;}
        void clear(){_time_=0;point=clock();}
};

#endif // LL_TIME_H_INCLUDED
