/* Audio.h -- Audio irrKlang Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_IRRKLANG_AUDIO_H
#define INCLUDED_LL_IRRKLANG_AUDIO_H

#include "../LL_Shared.h"

#include "irrKlang.h"
#include <string>

namespace LL_irrKlang
{
    class LL_SHARED Audio
    {
        private:
            unsigned int _V_position=0;
            float _V_volume=1.0;
            std::string _V_audio_path;
            irrklang::ISound* _V_isound=nullptr;
            bool _V_loop_mode=false;
        public:
            void set_path(std::string new_audio_path);
            std::string get_path();
            bool set_speed(float new_speed);
            float get_speed();
            bool set_pan(float new_pan);
            float get_pan();
            void set_volume(float new_volume);
            float get_volume();
            bool set_loop_mode(bool loop_mode_on);
            bool get_loop_mode();
            bool load();
            unsigned int size();
            bool set_position(unsigned int new_position);
            unsigned int get_position();
            bool is_playing();
            void stop();
            void pause();
            void play();
            bool destroy();
            operator irrklang::ISound* ();
            ~Audio();
    };
}

#endif // INCLUDED_LL_IRRKLANG_AUDIO_H
