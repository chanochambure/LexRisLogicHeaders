/* irrKlang.h -- irrKlang Header - LexRis Logic Headers

    Copyright (c) 2017 LexRisLogic

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

#ifndef INCLUDED_LL_IRRKLANG_H
#define INCLUDED_LL_IRRKLANG_H

#include "../LL_Shared.h"

#include <irrKlang.h>

namespace LL_irrKlang
{
    class LL_SHARED SoundEngine;

    extern SoundEngine* LL_SHARED default_engine;

    class LL_SHARED SoundEngine
    {
        private:
            float _V_volume=1.0;
            irrklang::ISoundEngine* _V_engine=nullptr;
        public:
            bool create();
            void set_default_engine();
            void set_volume(float new_volume);
            float get_volume();
            bool destroy();
            operator irrklang::ISoundEngine* ();
            ~SoundEngine();
    };
}

#endif // INCLUDED_LL_IRRKLANG_H
