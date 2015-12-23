#ifndef LL_AUDIO_H_INCLUDED
#define LL_AUDIO_H_INCLUDED

class LL_Audio
{
    private:
        unsigned int _ps=0;
        bool _play_status=0;
        ALLEGRO_PLAYMODE _mode=ALLEGRO_PLAYMODE_ONCE;
        ALLEGRO_SAMPLE* sample=nullptr;
        ALLEGRO_SAMPLE_INSTANCE* instance=nullptr;
        string audio_path;
    public:
        void set_path(string new_path){audio_path=new_path;}
        string get_path(){return audio_path;}
        bool set_speed(float sp){if(instance)return al_set_sample_instance_speed(instance,sp);return 0;}
        float get_speed(){if(instance)return al_get_sample_instance_speed(instance);return 0;}
        bool set_pan(float pn){if(instance)return al_set_sample_instance_pan(instance,pn);return 0;}
        float get_pan(){if(instance)return al_get_sample_instance_pan(instance);return 0;}
        bool set_volume(float vl){if(instance)return al_set_sample_instance_gain(instance,vl);return 0;}
        float get_volume(){if(instance)return al_get_sample_instance_gain(instance);return 0;}
        void set_mode(ALLEGRO_PLAYMODE flag){if(instance)al_set_sample_instance_playmode(instance,flag);}
        bool load();
        unsigned int get_size(){return al_get_sample_length(sample);}
        void set_position(unsigned int pos){al_set_sample_instance_position(instance,pos);}
        unsigned int get_position(){if(!al_get_sample_instance_playing(instance))return _ps;return al_get_sample_instance_position(instance);}
        bool is_playing(){return _play_status;}
        void stop(){_play_status=0;al_stop_sample_instance(instance);(_ps=0);}
        void pause(){if(al_get_sample_instance_playing(instance)){_ps=get_position();al_set_sample_instance_playing(instance,false);_play_status=false;}}
        void play(){if(!al_get_sample_instance_playing(instance)){set_position(_ps);al_set_sample_instance_playing(instance,true);_play_status=true;}}
        bool destroy(){if(instance){al_destroy_sample_instance(instance);instance=nullptr;}if(sample){al_destroy_sample(sample);sample=nullptr;return 1;}return 0;}
        operator ALLEGRO_SAMPLE* (){return sample;}
        operator ALLEGRO_SAMPLE_INSTANCE* (){return instance;}
        ~LL_Audio(){destroy();}
};

bool LL_Audio::load()
{
    destroy();
    if(!al_reserve_samples(1))
        return false;
    sample=al_load_sample(audio_path.c_str());
    if(sample)instance=al_create_sample_instance(sample);
    if(instance)al_attach_sample_instance_to_mixer(instance,al_get_default_mixer());
    return ((bool)sample and (bool)instance);
}

#endif // LL_AUDIO_H_INCLUDED
