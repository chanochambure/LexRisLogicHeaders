#ifndef INCLUDED_LL_AL5_H
#define INCLUDED_LL_AL5_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_native_dialog.h>

namespace LL_AL5
{
    typedef float Type_pos;
    typedef unsigned int Type_display_size;

    float bitmap_scale_x=1;
    float bitmap_scale_y=1;
    float text_scale=1;
    float primitives_scale=1;
    Type_display_size desktop_size_x=0;
    Type_display_size desktop_size_y=0;

    void init_allegro()
    {
        al_init();
        ALLEGRO_MONITOR_INFO monitor_info;
        if(al_get_monitor_info(0,&monitor_info))
        {
            desktop_size_x=monitor_info.x2-monitor_info.x1;
            desktop_size_y=monitor_info.y2-monitor_info.y1;
        }
    }
    void sleep(float sleep_time)
    {
        al_rest(sleep_time);
    }
    bool native_dialog_addon()
    {
        return al_init_native_dialog_addon();
    }
    bool primitives_addon()
    {
        return al_init_primitives_addon();
    }
    bool image_addon()
    {
        return al_init_image_addon();
    }
    bool text_addon()
    {
        return al_init_font_addon()and al_init_ttf_addon();
    }
    bool audio_addon()
    {
        return (al_install_audio() and al_init_acodec_addon());
    }
    bool video_addon()
    {
        return al_init_video_addon();
    }
    void uninstall_audio()
    {
        al_uninstall_audio();
    }
    void uninstall_primitives()
    {
        al_shutdown_primitives_addon();
    }
}

#include "Path.h"
#include "Display.h"
#include "NativeDialog.h"
#include "Input.h"
#include "Color.h"
#include "Primitives.h"
#include "Bitmap.h"
#include "Text.h"
#include "Mixer.h"
#include "Audio.h"
#include "Video.h"

#include "Special/Lighting.h"
#include "Special/Sprite.h"
#include "Special/Interface.h"

#endif // INCLUDED_LL_AL5_H
