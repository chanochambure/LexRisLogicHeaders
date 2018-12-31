/* Audio.cpp -- Audio irrKlang Source - LexRis Logic Headers

    Copyright (c) 2017-2019 LexRisLogic

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so.

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of
    the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "../../include/LexRisLogic/irrKlang/Audio.h"

namespace LL_irrKlang
{
    Audio::Audio()
    {
    }
    void Audio::set_path(std::string new_audio_path)
    {
        _V_audio_path=new_audio_path;
    }
    std::string Audio::get_path()
    {
        return _V_audio_path;
    }
    bool Audio::set_speed(float new_speed)
    {
        if(_V_isound)
            return _V_isound->setPlaybackSpeed(new_speed);
        return false;
    }
    float Audio::get_speed()
    {
        if(_V_isound)
            return _V_isound->getPlaybackSpeed();
        return 0.0;
    }
    bool Audio::set_pan(float new_pan)
    {
        if(_V_isound)
            _V_isound->setPan(new_pan*-1);
        return false;
    }
    float Audio::get_pan()
    {
        if(_V_isound)
            return (_V_isound->getPan()*-1);
        return 0.0;
    }
    void Audio::set_volume(float new_volume)
    {
        if(_V_isound)
            _V_isound->setVolume(new_volume*default_engine->get_volume());
        _V_volume=new_volume;
    }
    float Audio::get_volume()
    {
        return _V_volume;
    }
    bool Audio::set_loop_mode(bool loop_mode_on)
    {
        if(_V_isound && loop_mode_on!=_V_loop_mode)
        {
            _V_loop_mode=loop_mode_on;
            _V_isound->setIsLooped(_V_loop_mode);
            return true;
        }
        return false;
    }
    bool Audio::get_loop_mode()
    {
        return _V_loop_mode;
    }
    bool Audio::load()
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
    unsigned int Audio::size()
    {
        if(_V_isound)
            return _V_isound->getPlayLength();
        return 0;
    }
    bool Audio::set_position(unsigned int new_position)
    {
        if(_V_isound && _V_isound->setPlayPosition(new_position))
        {
            _V_position=new_position;
            return true;
        }
        return false;
    }
    unsigned int Audio::get_position()
    {
        if(_V_isound)
            return _V_isound->getPlayPosition();
        return 0;
    }
    bool Audio::is_playing()
    {
        if(_V_isound && _V_isound->isFinished())
        {
            _V_position=0;
            return false;
        }
        return (_V_isound && !_V_isound->getIsPaused());
    }
    void Audio::stop()
    {
        if(_V_isound)
        {
            _V_isound->stop();
            _V_position=0;
        }
    }
    void Audio::pause()
    {
        if(is_playing())
        {
            _V_position=get_position();
            _V_isound->setIsPaused(true);
        }
    }
    void Audio::play()
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
    bool Audio::destroy()
    {
        if(!_V_isound)
            return false;
        stop();
        _V_isound->drop();
        _V_isound=nullptr;
        return true;
    }
    Audio::operator irrklang::ISound* ()
    {
        return _V_isound;
    }
    Audio::~Audio()
    {
        destroy();
    }
}
