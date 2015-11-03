#ifndef LL_AUDIO_H_INCLUDED
#define LL_AUDIO_H_INCLUDED

class Audio
{
    private:
        unsigned int _ps=0;
        ALLEGRO_PLAYMODE _mode=ALLEGRO_PLAYMODE_ONCE;
        float _speed=1;
        float _pan=0;
        float _vol=1;
        ALLEGRO_SAMPLE* sample=nullptr;
        ALLEGRO_SAMPLE_INSTANCE* instance=nullptr;
        string audio_path;
    public:
        void set_path(string new_path){audio_path=new_path;}
        string get_path(){return audio_path;}
        void set_speed(float sp){_speed=sp;if(instance)al_set_sample_instance_speed(instance,_speed);}
        float get_speed(){return _speed;}
        void set_pan(float pn){_pan=pn;if(instance)al_set_sample_instance_pan(instance,_pan);}
        float get_pan(){return _pan;}
        void set_volume(float vl){_vol=vl;if(instance)al_set_sample_instance_gain(instance,_vol);}
        float get_volume(){return _vol;}
        void set_mode(ALLEGRO_PLAYMODE flag){_mode=flag;if(instance)al_set_sample_instance_playmode(instance,_mode);}
        bool load();
        void set_position(unsigned int pos){al_set_sample_instance_position(instance,pos);}
        unsigned int get_position(){if(!al_get_sample_instance_playing(instance))return _ps;return al_get_sample_instance_position(instance);}
        void stop(){al_stop_sample_instance(instance);(_ps=0);}
        void pause(){if(al_get_sample_instance_playing(instance)){_ps=get_position();al_set_sample_instance_playing(instance,false);}}
        void play(){if(!al_get_sample_instance_playing(instance)){set_position(_ps);al_set_sample_instance_playing(instance,true);}}
        bool destroy(){if(instance){al_destroy_sample_instance(instance);instance=nullptr;}if(sample){al_destroy_sample(sample);sample=nullptr;return 1;}return 0;}
        operator ALLEGRO_SAMPLE* (){return sample;}
        operator ALLEGRO_SAMPLE_INSTANCE* (){return instance;}
        ~Audio(){destroy();}
};

bool Audio::load()
{
    destroy();
    if(!al_reserve_samples(1))
        return false;
    sample=al_load_sample(audio_path.c_str());
    if(sample)instance=al_create_sample_instance(sample);
    if(instance)al_attach_sample_instance_to_mixer(instance,al_get_default_mixer());
    al_set_sample_instance_playmode(instance,_mode);
    al_set_sample_instance_speed(instance,_speed);
    al_set_sample_instance_pan(instance,_pan);
    al_set_sample_instance_gain(instance,_vol);
    return ((bool)sample and (bool)instance);
}

#endif // LL_AUDIO_H_INCLUDED
