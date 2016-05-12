#ifndef INCLUDED_LL_AL5_AUDIO_H
#define INCLUDED_LL_AL5_AUDIO_H

#include <string>

namespace LL_AL5
{
    class Audio
    {
        private:
            unsigned int _V_position=0;
            std::string _V_audio_path;
            ALLEGRO_PLAYMODE _V_playmode=ALLEGRO_PLAYMODE_ONCE;
            ALLEGRO_SAMPLE* _V_sample=nullptr;
            ALLEGRO_SAMPLE_INSTANCE* _V_instance=nullptr;
        public:
            void set_path(std::string new_audio_path)
            {
                _V_audio_path=new_audio_path;
            }
            std::string get_path()
            {
                return _V_audio_path;
            }
            bool set_speed(float new_speed)
            {
                if(_V_instance)
                    return al_set_sample_instance_speed(_V_instance,new_speed);
                return 0;
            }
            float get_speed()
            {
                if(_V_instance)
                    return al_get_sample_instance_speed(_V_instance);
                return 0;
            }
            bool set_pan(float new_pan)
            {
                if(_V_instance)
                    return al_set_sample_instance_pan(_V_instance,new_pan);
                return 0;
            }
            float get_pan()
            {
                if(_V_instance)
                    return al_get_sample_instance_pan(_V_instance);
                return 0;
            }
            bool set_volume(float new_volume)
            {
                if(_V_instance)
                    return al_set_sample_instance_gain(_V_instance,new_volume);
                return 0;
            }
            float get_volume()
            {
                if(_V_instance)
                    return al_get_sample_instance_gain(_V_instance);
                return 0;
            }
            bool set_playmode(ALLEGRO_PLAYMODE playmode)
            {
                if(_V_instance)
                    return al_set_sample_instance_playmode(_V_instance,playmode);
                return 0;
            }
            ALLEGRO_PLAYMODE get_playmode()
            {
                return _V_playmode;
            }
            bool load()
            {
                destroy();
                if(!al_reserve_samples(1))
                    return false;
                _V_sample=al_load_sample(_V_audio_path.c_str());
                if(_V_sample)
                    _V_instance=al_create_sample_instance(_V_sample);
                if(_V_instance)
                    al_attach_sample_instance_to_mixer(_V_instance,al_get_default_mixer());
                return (_V_sample and _V_instance);
            }
            unsigned int size()
            {
                if(_V_sample)
                    return al_get_sample_length(_V_sample);
                return 0;
            }
            float get_time()
            {
                if(_V_instance)
                    return al_get_sample_instance_time(_V_instance);
                return 0;
            }
            bool set_position(unsigned int new_position)
            {
                if(_V_instance and al_set_sample_instance_position(_V_instance,new_position))
                {
                    _V_position=new_position;
                    return true;
                }
                return false;
            }
            unsigned int get_position()
            {
                if(_V_instance)
                    return al_get_sample_instance_position(_V_instance);
                return 0;
            }
            bool is_playing()
            {
                if(_V_instance)
                    return al_get_sample_instance_playing(_V_instance);
                return false;
            }
            void stop()
            {
                if(_V_instance)
                {
                    al_stop_sample_instance(_V_instance);
                    _V_position=0;
                }
            }
            void pause()
            {
                if(is_playing())
                {
                    al_set_sample_instance_playing(_V_instance,false);
                    _V_position=get_position();
                }
            }
            void play()
            {
                if(!is_playing() and set_position(_V_position))
                    al_set_sample_instance_playing(_V_instance,true);
            }
            bool destroy()
            {
                if(_V_instance)
                {
                    al_destroy_sample_instance(_V_instance);
                    _V_instance=nullptr;
                    if(_V_sample)
                    {
                        al_destroy_sample(_V_sample);
                        _V_sample=nullptr;
                        return true;
                    }
                }
                return false;
            }
            operator ALLEGRO_SAMPLE* ()
            {
                return _V_sample;
            }
            operator ALLEGRO_SAMPLE_INSTANCE* ()
            {
                return _V_instance;
            }
            ~Audio()
            {
                destroy();
            }
    };
}

#endif // INCLUDED_LL_AL5_AUDIO_H
