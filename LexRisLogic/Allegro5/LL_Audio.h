#ifndef LL_AL5_AUDIO_H_INCLUDED
#define LL_AL5_AUDIO_H_INCLUDED

#include <string>

namespace LL_Allegro5
{
    class LL_Audio
    {
        private:
            unsigned int _ps=0;
            ALLEGRO_PLAYMODE _mode=ALLEGRO_PLAYMODE_ONCE;
            ALLEGRO_SAMPLE* sample=nullptr;
            ALLEGRO_SAMPLE_INSTANCE* instance=nullptr;
            std::string audio_path;
        public:
            void set_path(std::string new_path){audio_path=new_path;}
            std::string get_path(){return audio_path;}
            bool set_speed(float sp){if(instance)return al_set_sample_instance_speed(instance,sp);return 0;}
            float get_speed(){if(instance)return al_get_sample_instance_speed(instance);return 0;}
            bool set_pan(float pn){if(instance)return al_set_sample_instance_pan(instance,pn);return 0;}
            float get_pan(){if(instance)return al_get_sample_instance_pan(instance);return 0;}
            bool set_volume(float vl){if(instance)return al_set_sample_instance_gain(instance,vl);return 0;}
            float get_volume(){if(instance)return al_get_sample_instance_gain(instance);return 0;}
            void set_mode(ALLEGRO_PLAYMODE flag){if(instance)al_set_sample_instance_playmode(instance,flag);}
            bool load();
            unsigned int get_size(){return al_get_sample_length(sample);}
            void set_position(unsigned int pos){al_set_sample_instance_position(instance,_ps=pos);}
            unsigned int get_position(){if(instance)return al_get_sample_instance_position(instance);return 0;}
            bool is_playing(){return al_get_sample_instance_playing(instance);}
            void stop(){al_stop_sample_instance(instance);_ps=0;}
            void pause(){if(is_playing()){_ps=get_position();al_set_sample_instance_playing(instance,false);}}
            void play(){if(!is_playing()){set_position(_ps);al_set_sample_instance_playing(instance,true);}}
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
        return (sample and instance);
    }
}

#endif // LL_AL5_AUDIO_H_INCLUDED
