/* Mixer.h -- Mixer Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_MIXER_H
#define INCLUDED_LL_AL5_MIXER_H

#include "../LL_Shared.h"

#include "Allegro5.h"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

namespace LL_AL5
{
    bool LL_SHARED audio_addon();
    void LL_SHARED uninstall_audio();
    bool LL_SHARED restore_default_mixer();

    class LL_SHARED Mixer
    {
        private:
            ALLEGRO_VOICE* _V_voice=nullptr;
            ALLEGRO_MIXER* _V_mixer=nullptr;
            ALLEGRO_AUDIO_DEPTH _V_audio_depth=ALLEGRO_AUDIO_DEPTH_FLOAT32;
            ALLEGRO_CHANNEL_CONF _V_chanel_conf=ALLEGRO_CHANNEL_CONF_2;
            unsigned int _V_frequency=44100;
        public:
            bool set_frequency(unsigned int new_frequency);
            unsigned int get_frequency();
            bool set_audio_depth(ALLEGRO_AUDIO_DEPTH new_audio_depth);
            ALLEGRO_AUDIO_DEPTH get_audio_depth();
            bool set_chanel_configuration(ALLEGRO_CHANNEL_CONF new_chanel_conf);
            ALLEGRO_CHANNEL_CONF get_chanel_configuration();
            bool create();
            bool destroy();
            bool set_quality(ALLEGRO_MIXER_QUALITY quality);
            ALLEGRO_MIXER_QUALITY get_quality();
            bool set_volume(float new_volume);
            float get_volume();
            bool set_default_mixer();
            operator ALLEGRO_MIXER* ();
            operator ALLEGRO_VOICE* ();
            ~Mixer();
    };
}

#endif // INCLUDED_LL_AL5_MIXER_H
