#ifndef LL_MIXER_H_INCLUDED
#define LL_MIXER_H_INCLUDED

class LL_Mixer
{
    private:
        ALLEGRO_VOICE* _voice=nullptr;
        ALLEGRO_MIXER* _mixer=nullptr;
        ALLEGRO_AUDIO_DEPTH _depth=ALLEGRO_AUDIO_DEPTH_FLOAT32;
        ALLEGRO_CHANNEL_CONF _chanel_conf=ALLEGRO_CHANNEL_CONF_2;
        unsigned int _frequency=44100;
    public:
        void set_frequency(unsigned int freq){bool state=1;if(_mixer){state=al_set_mixer_frequency(_mixer,freq);}if(state)_frequency=freq;}
        unsigned int get_frequency(){return _frequency;}
        void set_audio_depth(ALLEGRO_AUDIO_DEPTH depth){_depth=depth;}
        ALLEGRO_AUDIO_DEPTH get_audio_depth(){return _depth;}
        void set_chanel_configuration(ALLEGRO_CHANNEL_CONF chanel_conf){_chanel_conf=chanel_conf;}
        ALLEGRO_CHANNEL_CONF get_chanel_configuration(){return _chanel_conf;}
        bool create();
        bool destroy();
        bool set_quality(ALLEGRO_MIXER_QUALITY quality){if(_mixer)return al_set_mixer_quality(_mixer,quality);return false;}
        ALLEGRO_MIXER_QUALITY get_quality(){return al_get_mixer_quality(_mixer);}
        bool set_volume(float vol){if(_mixer)return al_set_mixer_gain(_mixer,vol);return false;}
        float get_volume(){if(_mixer)return al_get_mixer_gain(_mixer);return 0;}
        bool set_default_mixer(){return al_set_default_mixer(_mixer);}
        operator ALLEGRO_MIXER* (){return _mixer;}
        operator ALLEGRO_VOICE* (){return _voice;}
        ~LL_Mixer(){destroy();}
};

bool LL_Mixer::create()
{
    destroy();
    _voice=al_create_voice(_frequency, ALLEGRO_AUDIO_DEPTH_INT16,_chanel_conf);
    if(!_voice)
        return 0;
    _mixer=al_create_mixer(_frequency,_depth,_chanel_conf);
    if(!_mixer)
    {
        al_destroy_voice(_voice);
        return 0;
    }
    if(al_attach_mixer_to_voice(_mixer,_voice))
        return 1;
    al_destroy_voice(_voice);
    al_destroy_mixer(_mixer);
    return false;
}

bool LL_Mixer::destroy()
{
    if(_mixer and _voice)
    {
        al_detach_voice(_voice);
        al_destroy_mixer(_mixer);
        _mixer=nullptr;
        al_destroy_voice(_voice);
        _voice=nullptr;
        return 1;
    }
    return 0;
}

#endif // LL_MIXER_H_INCLUDED
