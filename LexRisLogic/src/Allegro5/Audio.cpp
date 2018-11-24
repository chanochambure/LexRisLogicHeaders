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
    bool Audio::load()
    {
        if(_V_sample)
            return false;
        if(al_reserve_samples(1))
            _V_sample=al_load_sample(_V_audio_path.c_str());
        return _V_sample;
    }
    bool Audio::destroy()
    {
        if(_V_sample)
        {
            clear();
            al_destroy_sample(_V_sample);
            _V_sample=nullptr;
            return true;
        }
        return false;
    }
    unsigned int Audio::length()
    {
        if(_V_sample)
            return al_get_sample_length(_V_sample);
        return 0;
    }
    unsigned int Audio::size()
    {
        return _V_instances.size();
    }
    bool Audio::create_instance()
    {
        if(_V_sample)
        {
            _S_Structure_AudioInstance new_instance;
            new_instance.instance=al_create_sample_instance(_V_sample);
            if(new_instance.instance)
            {
                _V_instances.push_back(new_instance);
                return true;
            }
        }
        return false;
    }
    bool Audio::attach_instance_to_mixer(unsigned int index, ALLEGRO_MIXER* mixer)
    {
        return al_attach_sample_instance_to_mixer(_V_instances[index].instance,mixer);
    }
    bool Audio::destroy_instance(unsigned int index)
    {
        if(index<_V_instances.size())
        {
            auto iter=_V_instances.begin()+index;
            al_destroy_sample_instance(iter->instance);
            _V_instances.erase(iter);
            return true;
        }
        return false;
    }
    void Audio::clear()
    {
        for(_S_Structure_AudioInstance& iter:_V_instances)
            al_destroy_sample_instance(iter.instance);
        _V_instances.clear();
    }
    bool Audio::set_speed(unsigned int index,float new_speed)
    {
        return al_set_sample_instance_speed(_V_instances[index].instance,new_speed);
    }
    float Audio::get_speed(unsigned int index)
    {
        return al_get_sample_instance_speed(_V_instances[index].instance);
    }
    bool Audio::set_pan(unsigned int index,float new_pan)
    {
        return al_set_sample_instance_pan(_V_instances[index].instance,new_pan);
    }
    float Audio::get_pan(unsigned int index)
    {
        return al_get_sample_instance_pan(_V_instances[index].instance);
    }
    bool Audio::set_volume(unsigned int index,float new_volume)
    {
        return al_set_sample_instance_gain(_V_instances[index].instance,new_volume);
    }
    float Audio::get_volume(unsigned int index)
    {
        return al_get_sample_instance_gain(_V_instances[index].instance);
    }
    bool Audio::set_playmode(unsigned int index,ALLEGRO_PLAYMODE new_playmode)
    {
        return al_set_sample_instance_playmode(_V_instances[index].instance,new_playmode);
    }
    ALLEGRO_PLAYMODE Audio::get_playmode(unsigned int index)
    {
        return al_get_sample_instance_playmode(_V_instances[index].instance);
    }
    float Audio::get_time(unsigned int index)
    {
        return al_get_sample_instance_time(_V_instances[index].instance)*get_speed(index);
    }
    bool Audio::set_length(unsigned int index,unsigned int new_length)
    {
        return al_set_sample_instance_length(_V_instances[index].instance,new_length);
    }
    unsigned int Audio::get_length(unsigned int index)
    {
        if(is_playing(index))
            return al_get_sample_instance_length(_V_instances[index].instance);
        return _V_instances[index].position;
    }
    bool Audio::set_audio_position(unsigned int index,unsigned int new_position)
    {
        if(al_set_sample_instance_position(_V_instances[index].instance,new_position))
        {
            _V_instances[index].position=new_position;
            return true;
        }
        return false;
    }
    unsigned int Audio::get_audio_position(unsigned int index)
    {
        return al_get_sample_instance_position(_V_instances[index].instance);
    }
    bool Audio::is_playing(unsigned int index)
    {
        return al_get_sample_instance_playing(_V_instances[index].instance);
    }
    bool Audio::stop(unsigned int index)
    {
        if(al_stop_sample_instance(_V_instances[index].instance))
        {
            _V_instances[index].position=0;
            return true;
        }
        return false;
    }
    bool Audio::pause(unsigned int index)
    {
        if(is_playing(index))
        {
            _V_instances[index].position=get_audio_position(index);
            return al_set_sample_instance_playing(_V_instances[index].instance,false);
        }
        return false;
    }
    bool Audio::play(unsigned int index)
    {
        if(!is_playing(index) && set_audio_position(index,_V_instances[index].position))
            return al_set_sample_instance_playing(_V_instances[index].instance,true);
        return false;
    }
    Audio::operator ALLEGRO_SAMPLE* ()
    {
        return _V_sample;
    }
    Audio::~Audio()
    {
        destroy();
    }
}
