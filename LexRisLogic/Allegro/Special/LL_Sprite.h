#ifndef LL_SPRITE_H_INCLUDED
#define LL_SPRITE_H_INCLUDED

#include "../../LL_Convert.h"

class LL_Sprite:public LL_Bitmap_Base
{
    private:
        ALLEGRO_BITMAP** bmps=nullptr;
        unsigned int selection=0;
        unsigned int num_elements;
        float* Xsize=nullptr;
        float* Ysize=nullptr;
        bool special_X_pos=0;
        bool special_Y_pos=0;
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
        unsigned int create_from_directory(string sprites_dir,string format)
        {
            if(sprites_dir[sprites_dir.size()-1]!='/' or sprites_dir[sprites_dir.size()-1]!='\\')
                sprites_dir=sprites_dir+'/';
            if(format[0]!='.')
                format='.'+format;
            destroy();
            unsigned int return_value=0;
            for(unsigned int i=0;i<num_elements;++i)
            {
                bmps[i]=al_load_bitmap((sprites_dir+to_string(i+1)+format).c_str());
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
        void set_position_to_draw(bool pos_x,bool pos_y)
        {
            special_X_pos=pos_x;
            special_Y_pos=pos_y;
        }
        bool set_selection(unsigned int new_selection){if(new_selection<num_elements){selection=new_selection;return 1;}return 0;}
        unsigned int get_selection(){return selection;}
        void draw()
        {
            const int size_in_axe_x=(Xsize[selection]*scale_x*bmp_scalex);
            const int size_in_axe_y=(Ysize[selection]*scale_y*bmp_scaley);
            al_draw_scaled_rotated_bitmap(bmps[selection],
                                          Xsize[selection]/2,
                                          Ysize[selection]/2,
                                          x-(special_X_pos*size_in_axe_x)+(size_in_axe_x/2),
                                          y-(special_Y_pos*size_in_axe_y)+(size_in_axe_y/2),
                                          scale_x*bmp_scalex,
                                          scale_y*bmp_scaley,
                                          angle,
                                          flag);
        }
        void draw_in_another_target()
        {
            const int size_in_axe_x=(Xsize[selection]*bmp_scalex);
            const int size_in_axe_y=(Ysize[selection]*bmp_scaley);
            al_draw_scaled_rotated_bitmap(bmps[selection],
                                          Xsize[selection]/2,
                                          Ysize[selection]/2,
                                          x-(special_X_pos*size_in_axe_x)+(size_in_axe_x/2),
                                          y-(special_Y_pos*size_in_axe_y)+(size_in_axe_y/2),
                                          bmp_scalex,
                                          bmp_scaley,
                                          angle,
                                          flag);
        }
        operator ALLEGRO_BITMAP* (){return bmps[selection];}
        ~LL_Sprite(){destroy();}
};

#endif // LL_SPRITE_H_INCLUDED
