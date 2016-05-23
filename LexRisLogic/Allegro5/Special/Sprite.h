#ifndef INCLUDED_LL_AL5_SPRITE_H
#define INCLUDED_LL_AL5_SPRITE_H

#include <string>
#include "../Bitmap.h"
#include "../../Convert.h"

namespace LL_AL5
{
    class LL_Sprite:public BitmapBase
    {
        private:
            ALLEGRO_BITMAP** bmps=nullptr;
            unsigned int selection=0;
            unsigned int num_elements;
            float* Xsize=nullptr;
            float* Ysize=nullptr;
        public:
            LL_Sprite(unsigned int number_bmps)
            {
                num_elements=number_bmps;
                bmps=new ALLEGRO_BITMAP*[number_bmps];
                Xsize=new float[number_bmps];
                Ysize=new float[number_bmps];
                for(unsigned int i=0;i<num_elements;++i)
                {
                    Xsize[i]=0;
                    Ysize[i]=0;
                    bmps[i]=nullptr;
                }
            }
            float get_sizex(){return Xsize[selection];}
            float get_sizey(){return Ysize[selection];}
            void set_target(){if(bmps[selection])al_set_target_bitmap(bmps[selection]);}
            ALLEGRO_COLOR get_pixel(Type_pos x,Type_pos y){return al_get_pixel(bmps[selection],x,y);}
            bool lock(){return al_lock_bitmap(bmps[selection],ALLEGRO_LOCK_READWRITE,ALLEGRO_PIXEL_FORMAT_ANY);}
            void unlock(){al_unlock_bitmap(bmps[selection]);}
            bool create_selection(int s_X,int s_Y){destroy_selection();bmps[selection]=al_create_bitmap(s_X,s_Y);if(bmps[selection]){Xsize[selection]=s_X;Ysize[selection]=s_Y;return 1;}return 0;}
            bool destroy_selection()
            {
                if(bmps[selection])
                {
                    al_destroy_bitmap(bmps[selection]);
                    bmps[selection]=nullptr;
                    Xsize[selection]=0;
                    Ysize[selection]=0;
                    return 1;
                }
                return 0;
            }
            unsigned int create_from_directory(std::string sprites_dir,std::string format)
            {
                if(sprites_dir[sprites_dir.size()-1]!='/' or sprites_dir[sprites_dir.size()-1]!='\\')
                    sprites_dir=sprites_dir+'/';
                if(format[0]!='.')
                    format='.'+format;
                destroy();
                unsigned int return_value=0;
                for(unsigned int i=0;i<num_elements;++i)
                {
                    bmps[i]=al_load_bitmap((sprites_dir+LL::to_string(i+1)+format).c_str());
                    if(bmps[i])
                    {
                        Xsize[i]=al_get_bitmap_width(bmps[i]);
                        Ysize[i]=al_get_bitmap_height(bmps[i]);
                        ++return_value;
                    }
                }
                return return_value;
            }
            bool destroy()
            {
                bool return_value=0;
                for(unsigned int i=0;i<num_elements;++i)
                {
                    if(bmps[i])
                    {
                        return_value=1;
                        Xsize[i]=0;
                        Ysize[i]=0;
                        al_destroy_bitmap(bmps[i]);
                    }
                    bmps[i]=nullptr;
                }
                return return_value;
            }
            unsigned int size(){return num_elements;}
            bool set_selection(unsigned int new_selection){if(new_selection<num_elements){selection=new_selection;return 1;}return 0;}
            unsigned int get_selection(){return selection;}
            void draw()
            {
                const Type_pos size_in_axe_x=(Xsize[selection]*bitmap_scale_x*_V_scale_x);
                const Type_pos size_in_axe_y=(Ysize[selection]*bitmap_scale_y*_V_scale_y);
                al_draw_scaled_rotated_bitmap(bmps[selection],
                                              Xsize[selection]/2,
                                              Ysize[selection]/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              bitmap_scale_x*_V_scale_x,
                                              bitmap_scale_y*_V_scale_y,
                                              _V_angle,
                                              _V_flag);
            }
            void draw_in_another_target()
            {
                const Type_pos size_in_axe_x=(Xsize[selection]*_V_scale_x);
                const Type_pos size_in_axe_y=(Ysize[selection]*_V_scale_y);
                al_draw_scaled_rotated_bitmap(bmps[selection],
                                              Xsize[selection]/2,
                                              Ysize[selection]/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              _V_scale_x,
                                              _V_scale_x,
                                              _V_angle,
                                              _V_flag);
            }
            operator ALLEGRO_BITMAP* (){return bmps[selection];}
            ~LL_Sprite(){destroy();}
    };
}

#endif // INCLUDED_LL_AL5_SPRITE_H
