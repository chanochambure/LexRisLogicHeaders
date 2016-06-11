/* irrKlang.h -- irrKlang Header - LexRis Logic Headers

    Copyright (c) 2016 LexRisLogic

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

#include <irrKlang.h>

namespace LL_irrKlang
{
    class SoundEngine;

    SoundEngine* default_engine=nullptr;

    class SoundEngine
    {
        private:
            float _V_volume=1.0;
            irrklang::ISoundEngine* _V_engine=nullptr;
        public:
            bool create()
            {
                destroy();
                return (_V_engine=irrklang::createIrrKlangDevice());
            }
            void set_default_engine()
            {
                default_engine=this;
            }
            void set_volume(float new_volume)
            {
                _V_volume=new_volume;
            }
            float get_volume()
            {
                return _V_volume;
            }
            bool destroy()
            {
                if(!_V_engine)
                    return false;
                _V_engine->drop();
                _V_engine=nullptr;
                return true;
            }
            operator irrklang::ISoundEngine* ()
            {
                return _V_engine;
            }
            ~SoundEngine()
            {
                destroy();
            }
    };
}

//Headers
#include "Audio.h"

#endif // INCLUDED_LL_IRRKLANG_H
