#ifndef INCLUDED_LL_AL5_TIMER_H
#define INCLUDED_LL_AL5_TIMER_H

namespace LL_AL5
{
    class Timer
    {
        private:
            ALLEGRO_TIMER* _V_timer=nullptr;
            double _V_speed_seconds=1;
        public:
            bool set_speed_seconds(double new_speed_seconds)
            {
                if(!_V_timer and new_speed_seconds>0)
                {
                    _V_speed_seconds=new_speed_seconds;
                    return true;
                }
                return false;
            }
            double get_speed_seconds()
            {
                return _V_speed_seconds;
            }
            bool create()
            {
                if(!_V_timer)
                {
                    _V_timer=al_create_timer(_V_speed_seconds);
                    return _V_timer;
                }
                return false;
            }
            bool destroy()
            {
                if(_V_timer)
                {
                    al_destroy_timer(_V_timer);
                    _V_timer=nullptr;
                    return true;
                }
                return false;
            }
            bool start()
            {
                if(_V_timer)
                {
                    al_start_timer(_V_timer);
                    return true;
                }
                return false;
            }
            bool resume()
            {
                if(_V_timer)
                {
                    al_resume_timer(_V_timer);
                    return true;
                }
                return false;
            }
            bool stop()
            {
                if(_V_timer)
                {
                    al_stop_timer(_V_timer);
                    return true;
                }
                return false;
            }
            operator ALLEGRO_TIMER* ()
            {
                return _V_timer;
            }
            ~Timer()
            {
                destroy();
            }
    };
}

#endif // INCLUDED_LL_AL5_TIMER_H
