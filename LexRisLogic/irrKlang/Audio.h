#ifndef INCLUDED_LL_IRRKLANG_AUDIO_H
#define INCLUDED_LL_IRRKLANG_AUDIO_H

#include <string>

namespace LL_irrKlang
{
    class Audio
    {
        private:
            unsigned int _V_position=0;
            float _V_volume=1;
            std::string _V_audio_path;
            irrklang::ISound* _V_isound=nullptr;
            bool _V_loop_mode=false;
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
                if(_V_isound)
                    return _V_isound->setPlaybackSpeed(new_speed);
                return false;
            }
            float get_speed()
            {
                if(_V_isound)
                    return _V_isound->getPlaybackSpeed();
                return 0;
            }
            bool set_pan(float new_pan)
            {
                if(_V_isound)
                    _V_isound->setPan(new_pan*-1);
                return _V_isound;
            }
            float get_pan()
            {
                if(_V_isound)
                    return (_V_isound->getPan()*-1);
                return 0;
            }
            void set_volume(float new_volume)
            {
                if(_V_isound)
                    _V_isound->setVolume(new_volume*default_engine->get_volume());
                _V_volume=new_volume;
            }
            float get_volume()
            {
                return _V_volume;
            }
            bool set_loop_mode(bool loop_mode_on)
            {
                if(_V_isound and loop_mode_on!=_V_loop_mode)
                {
                    _V_loop_mode=loop_mode_on;
                    _V_isound->setIsLooped(_V_loop_mode);
                    return true;
                }
                return false;
            }
            bool get_loop_mode()
            {
                return _V_loop_mode;
            }
            bool load()
            {
                destroy();
                if(!default_engine)
                    return false;
                _V_isound=((irrklang::ISoundEngine*)(*default_engine))->play2D(_V_audio_path.c_str(),
                                                                               _V_loop_mode,true);
                _V_position=0;
                set_volume(_V_volume);
                return _V_isound;
            }
            unsigned int size()
            {
                if(_V_isound)
                    return _V_isound->getPlayLength();
                return 0;
            }
            bool set_position(unsigned int new_position)
            {
                if(_V_isound and _V_isound->setPlayPosition(new_position))
                {
                    _V_position=new_position;
                    return true;
                }
                return false;
            }
            unsigned int get_position()
            {
                if(_V_isound)
                    return _V_isound->getPlayPosition();
                return 0;
            }
            bool is_playing()
            {
                if(_V_isound and _V_isound->isFinished())
                {
                    _V_position=0;
                    return false;
                }
                return (_V_isound and !_V_isound->getIsPaused());
            }
            void stop()
            {
                if(_V_isound)
                {
                    _V_isound->stop();
                    _V_position=0;
                }
            }
            void pause()
            {
                if(is_playing())
                {
                    _V_position=get_position();
                    _V_isound->setIsPaused(true);
                }
            }
            void play()
            {
                if(_V_isound)
                {
                    if(!_V_isound->isFinished())
                    {
                        if(_V_isound->getIsPaused())
                        {
                            set_position(_V_position);
                            _V_isound->setIsPaused(false);
                        }
                    }
                    else
                    {
                        float temp_speed=get_speed();
                        float temp_pan=get_pan();
                        load();
                        _V_isound->setIsPaused(false);
                        set_loop_mode(_V_loop_mode);
                        set_speed(temp_speed);
                        set_pan(temp_pan);
                    }
                }
            }
            bool destroy()
            {
                if(!_V_isound)
                    return false;
                stop();
                _V_isound->drop();
                _V_isound=nullptr;
                return true;
            }
            operator irrklang::ISound* ()
            {
                return _V_isound;
            }
            ~Audio()
            {
                destroy();
            }
    };
}

#endif // INCLUDED_LL_IRRKLANG_AUDIO_H
