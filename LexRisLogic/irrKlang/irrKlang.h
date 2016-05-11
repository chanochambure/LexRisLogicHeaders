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
            float _V_volume=1;
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
