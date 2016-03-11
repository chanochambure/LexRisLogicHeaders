#ifndef LL_IRRKLANG_AUDIO_H_INCLUDED
#define LL_IRRKLANG_AUDIO_H_INCLUDED

#include <string>

namespace LL_irrKlang
{
    class LL_Audio
    {
        private:
            unsigned int _ps=0;
            float vl=1;
            std::string audio_path;
            irrklang::ISound* sound=nullptr;
            bool loop=false;
        public:
            void set_path(std::string new_path){audio_path=new_path;}
            std::string get_path(){return audio_path;}
            bool set_speed(float speed){if(sound)return sound->setPlaybackSpeed(speed);return 0;}
            float get_speed(){if(sound)return sound->getPlaybackSpeed();return 0;}
            bool set_pan(float pn){if(sound)sound->setPan(pn);return sound;}
            float get_pan(){if(sound)return sound->getPan();return 0;}
            void set_volume(float vol){if(sound)sound->setVolume(vol*default_engine->get_volume());vl=vol;}
            float get_volume(){return vl;}
            void set_mode(bool looped){loop=looped;if(sound)sound->setIsLooped(loop);}
            bool load();
            unsigned int get_size(){if(sound)return sound->getPlayLength();return 0;}
            void set_position(unsigned int pos){if(sound)sound->setPlayPosition(_ps=pos);}
            unsigned int get_position(){if(sound)return sound->getPlayPosition();return 0;}
            bool is_playing(){return (sound and !(sound->getIsPaused() or sound->isFinished()));}
            void stop(){if(sound){sound->stop();_ps=0;}}
            void pause(){if(is_playing()){_ps=get_position();sound->setIsPaused(true);}}
            void play(){if(sound and !is_playing()){set_position(_ps);sound->setIsPaused(false);}}
            bool destroy(){stop();if(!sound)return 0;sound->drop();sound=nullptr;return 1;}
            operator irrklang::ISound* (){return sound;}
            ~LL_Audio(){destroy();}
    };

    bool LL_Audio::load()
    {
        destroy();
        if(!default_engine)
            return 0;
        sound=((irrklang::ISoundEngine*)(*default_engine))->play2D(audio_path.c_str(),loop,true);
        set_volume(vl);
        return sound;
    }
}

#endif // LL_IRRKLANG_AUDIO_H_INCLUDED
