/* Audio.cpp -- Audio Allegro 5 Source - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

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

#include "../../include/LexRisLogic/Allegro5/Audio.h"

namespace LL_AL5
{
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
        if(_V_instance)
            return al_set_sample_instance_speed(_V_instance,new_speed);
        return false;
    }
    float Audio::get_speed()
    {
        if(_V_instance)
            return al_get_sample_instance_speed(_V_instance);
        return 0.0;
    }
    bool Audio::set_pan(float new_pan)
    {
        if(_V_instance)
            return al_set_sample_instance_pan(_V_instance,new_pan);
        return false;
    }
    float Audio::get_pan()
    {
        if(_V_instance)
            return al_get_sample_instance_pan(_V_instance);
        return 0.0;
    }
    bool Audio::set_volume(float new_volume)
    {
        if(_V_instance)
            return al_set_sample_instance_gain(_V_instance,new_volume);
        return false;
    }
    float Audio::get_volume()
    {
        if(_V_instance)
            return al_get_sample_instance_gain(_V_instance);
        return 0.0;
    }
    bool Audio::set_playmode(ALLEGRO_PLAYMODE playmode)
    {
        if(_V_instance)
            return al_set_sample_instance_playmode(_V_instance,_V_playmode=playmode);
        return false;
    }
    ALLEGRO_PLAYMODE Audio::get_playmode()
    {
        return _V_playmode;
    }
    bool Audio::load()
    {
        destroy();
        if(!al_reserve_samples(1))
            return false;
        _V_sample=al_load_sample(_V_audio_path.c_str());
        if(_V_sample)
        {
            _V_instance=al_create_sample_instance(_V_sample);
            if(_V_instance)
            {
                al_attach_sample_instance_to_mixer(_V_instance,al_get_default_mixer());
                return true;
            }
            al_destroy_sample(_V_sample);
            _V_sample=nullptr;
        }
        return false;
    }
    bool Audio::destroy()
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
    unsigned int Audio::size()
    {
        if(_V_sample)
            return al_get_sample_length(_V_sample);
        return 0;
    }
    float Audio::get_time()
    {
        if(_V_instance)
            return al_get_sample_instance_time(_V_instance);
        return 0.0;
    }
    bool Audio::set_audio_position(unsigned int new_position)
    {
        if(_V_instance and al_set_sample_instance_position(_V_instance,new_position))
        {
            _V_position=new_position;
            return true;
        }
        return false;
    }
    unsigned int Audio::get_audio_position()
    {
        if(_V_instance)
            return al_get_sample_instance_position(_V_instance);
        return 0;
    }
    bool Audio::is_playing()
    {
        if(_V_instance)
            return al_get_sample_instance_playing(_V_instance);
        return false;
    }
    void Audio::stop()
    {
        if(_V_instance)
        {
            al_stop_sample_instance(_V_instance);
            _V_position=0;
        }
    }
    void Audio::pause()
    {
        if(is_playing())
        {
            al_set_sample_instance_playing(_V_instance,false);
            _V_position=get_audio_position();
        }
    }
    void Audio::play()
    {
        if(!is_playing() and set_audio_position(_V_position))
            al_set_sample_instance_playing(_V_instance,true);
    }
    Audio::operator ALLEGRO_SAMPLE* ()
    {
        return _V_sample;
    }
    Audio::operator ALLEGRO_SAMPLE_INSTANCE* ()
    {
        return _V_instance;
    }
    Audio::~Audio()
    {
        destroy();
    }
}
