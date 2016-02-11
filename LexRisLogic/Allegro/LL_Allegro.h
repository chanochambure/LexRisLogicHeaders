#ifndef LL_ALLEGRO_H_INCLUDED
#define LL_ALLEGRO_H_INCLUDED

typedef float pos_t;
typedef unsigned int display_size_t;

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
bool primitives_addon(){return al_init_primitives_addon();}
bool image_addon(){return al_init_image_addon();}
bool text_addon(){return al_init_font_addon()and al_init_ttf_addon();}
bool audio_addon(){return (al_install_audio() and al_init_acodec_addon());}
void uninstall_audio(){al_uninstall_audio();}
void uninstall_primitives(){al_shutdown_primitives_addon();}

//Library
#include "LL_Path.h"
#include "LL_Display.h"
#include "LL_Native_Dialog.h"
#include "LL_Input.h"
#include "LL_Color.h"
#include "LL_Camera.h"
#include "LL_Primitives.h"
#include "LL_Bitmap.h"
#include "LL_Text.h"
#include "LL_Mixer.h"
#include "LL_Audio.h"
#include "LL_Video.h"

//Special Class
#include "Special/LL_Sprite.h"
#include "Special/LL_Interface.h"

#endif // LL_ALLEGRO_H_INCLUDED
