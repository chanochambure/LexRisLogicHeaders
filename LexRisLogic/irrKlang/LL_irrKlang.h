#ifndef LL_IRRKLANG_H_INCLUDED
#define LL_IRRKLANG_H_INCLUDED

#include <irrKlang.h>

namespace LL_irrKlang
{
    class LL_SoundEngine
    {
        private:
            float volume=1;
            irrklang::ISoundEngine* engine=nullptr;
        public:
            bool create(){return (engine=irrklang::createIrrKlangDevice());}
            void set_volume(float vl){volume=vl;}
            float get_volume(){return volume;}
            bool destroy(){if(!engine)return 0;engine->drop();engine=nullptr;return 1;}
            operator irrklang::ISoundEngine* (){return engine;}
            void set_default_engine();
            ~LL_SoundEngine(){destroy();}
    };

    LL_SoundEngine* default_engine=nullptr;

    void LL_SoundEngine::set_default_engine(){default_engine=this;}
}

//Headers
#include "LL_Audio.h"

#endif // LL_IRRKLANG_H_INCLUDED
