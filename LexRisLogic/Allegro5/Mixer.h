#ifndef INCLUDED_LL_AL5_MIXER_H
#define INCLUDED_LL_AL5_MIXER_H

namespace LL_AL5
{
    class LL_Mixer
    {
        private:
            ALLEGRO_VOICE* _V_voice=nullptr;
            ALLEGRO_MIXER* _V_mixer=nullptr;
            ALLEGRO_AUDIO_DEPTH _V_audio_depth=ALLEGRO_AUDIO_DEPTH_FLOAT32;
            ALLEGRO_CHANNEL_CONF _V_chanel_conf=ALLEGRO_CHANNEL_CONF_2;
            unsigned int _V_frequency=44100;
        public:
            bool set_frequency(unsigned int new_frequency)
            {
                if(_V_mixer)
                {
                    if(al_set_mixer_frequency(_V_mixer,new_frequency))
                    {
                        _V_frequency=new_frequency;
                        return true;
                    }
                }
                return false;
            }
            unsigned int get_frequency()
            {
                return _V_frequency;
            }
            bool set_audio_depth(ALLEGRO_AUDIO_DEPTH new_audio_depth)
            {
                if(_V_mixer)
                    return false;
                _V_audio_depth=new_audio_depth;
                return true;
            }
            ALLEGRO_AUDIO_DEPTH get_audio_depth()
            {
                return _V_audio_depth;
            }
            bool set_chanel_configuration(ALLEGRO_CHANNEL_CONF new_chanel_conf)
            {
                if(_V_voice or _V_mixer)
                    return false;
                _V_chanel_conf=new_chanel_conf;
                return true;
            }
            ALLEGRO_CHANNEL_CONF get_chanel_configuration()
            {
                return _V_chanel_conf;
            }
            bool create()
            {
                destroy();
                _V_voice=al_create_voice(_V_frequency,_V_audio_depth,_V_chanel_conf);
                if(_V_voice)
                {
                    _V_mixer=al_create_mixer(_V_frequency,_V_audio_depth,_V_chanel_conf);
                    if(_V_mixer)
                    {
                        if(al_attach_mixer_to_voice(_V_mixer,_V_voice))
                            return true;
                        al_destroy_mixer(_V_mixer);
                        _V_mixer=nullptr;
                    }
                    al_destroy_voice(_V_voice);
                    _V_voice=nullptr;
                }
                return false;
            }
            bool destroy()
            {
                if(_V_mixer and _V_voice)
                {
                    al_detach_voice(_V_voice);
                    al_destroy_mixer(_V_mixer);
                    al_destroy_voice(_V_voice);
                    _V_mixer=nullptr;
                    _V_voice=nullptr;
                    return true;
                }
                return false;
            }
            bool set_quality(ALLEGRO_MIXER_QUALITY quality)
            {
                if(_V_mixer)
                    return al_set_mixer_quality(_V_mixer,quality);
                return false;
            }
            ALLEGRO_MIXER_QUALITY get_quality()
            {
                return al_get_mixer_quality(_V_mixer);
            }
            bool set_volume(float new_volume)
            {
                if(_V_mixer)
                    return al_set_mixer_gain(_V_mixer,new_volume);
                return false;
            }
            float get_volume()
            {
                if(_V_mixer)
                    return al_get_mixer_gain(_V_mixer);
                return 0;
            }
            bool set_default_mixer()
            {
                return al_set_default_mixer(_V_mixer);
            }
            operator ALLEGRO_MIXER* ()
            {
                return _V_mixer;
            }
            operator ALLEGRO_VOICE* ()
            {
                return _V_voice;
            }
            ~LL_Mixer()
            {
                destroy();
            }
    };
}

#endif // INCLUDED_LL_AL5_MIXER_H
