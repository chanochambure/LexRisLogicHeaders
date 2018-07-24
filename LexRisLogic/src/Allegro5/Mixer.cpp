/* Mixer.cpp -- Mixer Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/Mixer.h"

namespace LL_AL5
{
    bool LL_SHARED audio_addon()
    {
        return (al_install_audio() and al_init_acodec_addon());
    }
    void LL_SHARED uninstall_audio()
    {
        al_uninstall_audio();
    }
    bool LL_SHARED restore_default_mixer()
    {
        return al_restore_default_mixer();
    }

    bool Mixer::set_frequency(unsigned int new_frequency)
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
    unsigned int Mixer::get_frequency()
    {
        return _V_frequency;
    }
    bool Mixer::set_audio_depth(ALLEGRO_AUDIO_DEPTH new_audio_depth)
    {
        if(_V_mixer)
            return false;
        _V_audio_depth=new_audio_depth;
        return true;
    }
    ALLEGRO_AUDIO_DEPTH Mixer::get_audio_depth()
    {
        return _V_audio_depth;
    }
    bool Mixer::set_chanel_configuration(ALLEGRO_CHANNEL_CONF new_chanel_conf)
    {
        if(_V_voice or _V_mixer)
            return false;
        _V_chanel_conf=new_chanel_conf;
        return true;
    }
    ALLEGRO_CHANNEL_CONF Mixer::get_chanel_configuration()
    {
        return _V_chanel_conf;
    }
    bool Mixer::create()
    {
        destroy();
        _V_voice=al_create_voice(_V_frequency,ALLEGRO_AUDIO_DEPTH_INT16,_V_chanel_conf);
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
    bool Mixer::destroy()
    {
        if(_V_mixer and _V_voice)
        {
            al_detach_voice(_V_voice);
            al_detach_mixer(_V_mixer);
            al_destroy_mixer(_V_mixer);
            al_destroy_voice(_V_voice);
            _V_mixer=nullptr;
            _V_voice=nullptr;
            return true;
        }
        return false;
    }
    bool Mixer::set_quality(ALLEGRO_MIXER_QUALITY quality)
    {
        if(_V_mixer)
            return al_set_mixer_quality(_V_mixer,quality);
        return false;
    }
    ALLEGRO_MIXER_QUALITY Mixer::get_quality()
    {
        if(_V_mixer)
            return al_get_mixer_quality(_V_mixer);
        return ALLEGRO_MIXER_QUALITY_LINEAR;
    }
    bool Mixer::set_volume(float new_volume)
    {
        if(_V_mixer)
            return al_set_mixer_gain(_V_mixer,new_volume);
        return false;
    }
    float Mixer::get_volume()
    {
        if(_V_mixer)
            return al_get_mixer_gain(_V_mixer);
        return 0;
    }
    bool Mixer::set_default_mixer()
    {
        if(_V_mixer)
            return al_set_default_mixer(_V_mixer);
        return false;
    }
    Mixer::operator ALLEGRO_MIXER* ()
    {
        return _V_mixer;
    }
    Mixer::operator ALLEGRO_VOICE* ()
    {
        return _V_voice;
    }
    Mixer::~Mixer()
    {
        destroy();
    }
}
