#ifndef LL_AL5_ALLEGRO_H_INCLUDED
#define LL_AL5_ALLEGRO_H_INCLUDED

//Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_native_dialog.h>

namespace LL_Allegro5
{
    //Definición de Tipos
    typedef float pos_t;
    typedef unsigned int display_size_t;

    //Variables Importantes
    float scale_x=1;
    float scale_y=1;
    float text_scale=1;
    float primitives_scale=1;
    bool exit_program=0;
    display_size_t desktop_size_x;
    display_size_t desktop_size_y;

    //Functions
    void init_allegro(){al_init();ALLEGRO_MONITOR_INFO info;al_get_monitor_info(0, &info);desktop_size_x=info.x2 -info.x1;desktop_size_y=info.y2-info.y1;}
    void rest(float _time){al_rest(_time);}
    bool native_dialog_addon(){return al_init_native_dialog_addon();}
    bool primitives_addon(){return al_init_primitives_addon();}
    bool image_addon(){return al_init_image_addon();}
    bool text_addon(){return al_init_font_addon()and al_init_ttf_addon();}
    bool audio_addon(){return (al_install_audio() and al_init_acodec_addon());}
    bool video_addon(){return al_init_video_addon();}
    void uninstall_audio(){al_uninstall_audio();}
    void uninstall_primitives(){al_shutdown_primitives_addon();}
}

//Headers
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

//Special Class
#include "Special/Lighting.h"
#include "Special/Sprite.h"
#include "Special/Interface.h"

#endif // LL_AL5_ALLEGRO_H_INCLUDED
