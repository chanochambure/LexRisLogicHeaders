/* Video.h -- Video Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_VIDEO_H
#define INCLUDED_LL_AL5_VIDEO_H

#include "../LL_Shared.h"

#include "Allegro5.h"
#include "Bitmap.h"
#include "Mixer.h"

#include <allegro5/allegro_video.h>
#include <string>

namespace LL_AL5
{
    bool LL_SHARED video_addon();

    class LL_SHARED Video:public BitmapBase
    {
        private:
            ALLEGRO_VIDEO* _V_video=nullptr;
            float _V_size_x=0.0;
            float _V_size_y=0.0;
            std::string _V_video_path;
        public:
            void set_path(std::string new_video_path);
            std::string get_path();
            float get_size_x();
            float get_size_y();
            bool load();
            bool destroy();
            double get_video_position(ALLEGRO_VIDEO_POSITION_TYPE reference_position=ALLEGRO_VIDEO_POSITION_ACTUAL);
            bool start();
            bool is_playing();
            void stop();
            void pause();
            void play();
            void draw();
            operator ALLEGRO_VIDEO* ();
            ~Video();
    };
}

#endif // INCLUDED_LL_AL5_VIDEO_H
