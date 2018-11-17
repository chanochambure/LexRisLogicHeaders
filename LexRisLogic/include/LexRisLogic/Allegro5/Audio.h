/* Audio.h -- Audio Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_AUDIO_H
#define INCLUDED_LL_AL5_AUDIO_H

#include "../LL_Shared.h"

#include "Allegro5.h"
#include "Mixer.h"

#include <string>
#include <vector>

namespace LL_AL5
{
    class LL_SHARED Audio
    {
        private:
            struct _S_Structure_AudioInstance
            {
                unsigned int position=0;
                ALLEGRO_SAMPLE_INSTANCE* instance=nullptr;
            };
            std::string _V_audio_path;
            ALLEGRO_SAMPLE* _V_sample=nullptr;
            std::vector<_S_Structure_AudioInstance> _V_instances;
        public:
            Audio();
            Audio(const Audio&) = delete;
            void set_path(std::string new_audio_path);
            std::string get_path();
            bool load();
            bool destroy();
            unsigned int length();
            unsigned int size();
            bool create_instance();
            bool attack_instance_to_mixer(unsigned int index, ALLEGRO_MIXER* mixer);
            bool destroy_instance(unsigned int index);
            void clear();
            bool set_speed(unsigned int index,float new_speed);
            float get_speed(unsigned int index);
            bool set_pan(unsigned int index,float new_pan);
            float get_pan(unsigned int index);
            bool set_volume(unsigned int index,float new_volume);
            float get_volume(unsigned int index);
            bool set_playmode(unsigned int index,ALLEGRO_PLAYMODE playmode);
            ALLEGRO_PLAYMODE get_playmode(unsigned int index);
            float get_time(unsigned int index);
            bool set_length(unsigned int index,unsigned int new_length);
            unsigned int get_length(unsigned int index);
            bool set_audio_position(unsigned int index,unsigned int new_position);
            unsigned int get_audio_position(unsigned int index);
            bool is_playing(unsigned int index);
            bool stop(unsigned int index);
            bool pause(unsigned int index);
            bool play(unsigned int index);
            const Audio& operator = (const Audio&) = delete;
            operator ALLEGRO_SAMPLE* ();
            ~Audio();
    };
}

#endif // INCLUDED_LL_AL5_AUDIO_H
