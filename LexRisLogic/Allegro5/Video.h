#ifndef INCLUDED_LL_AL5_VIDEO_H
#define INCLUDED_LL_AL5_VIDEO_H

#include <string>

namespace LL_AL5
{
    class LL_Video
    {
        private:
            ALLEGRO_VIDEO* video=nullptr;
            int flag=0;
            float angle=0;
            Type_pos x=0;
            Type_pos y=0;
            float Xsize=0;
            float Ysize=0;
            float video_scalex=1;
            float video_scaley=1;
            std::string video_path;
        public:
            void set_pos(Type_pos xx,Type_pos yy){x=xx;y=yy;}
            void set_posx(Type_pos xx){x=xx;}
            void set_posy(Type_pos yy){y=yy;}
            Type_pos get_posx(){return x;}
            Type_pos get_posy(){return y;}
            float get_sizex(){return Xsize;}
            float get_sizey(){return Ysize;}
            void set_angle(float an){angle=an;}
            float get_angle(){return angle;}
            void set_flag(int f){flag=f;}
            void set_scale_x(float sx){video_scalex=sx;}
            void set_scale_y(float sy){video_scaley=sy;}
            float get_scale_x(){return video_scalex;}
            float get_scale_y(){return video_scaley;}
            void set_path(std::string new_path){video_path=new_path;}
            std::string get_path(){return video_path;}
            bool load();
            bool set_position(double ss){return al_seek_video(video,ss);}
            double get_position(ALLEGRO_VIDEO_POSITION_TYPE sw=ALLEGRO_VIDEO_POSITION_ACTUAL){return al_get_video_position(video,sw);}
            void draw(){ALLEGRO_BITMAP* bmp=al_get_video_frame(video);if(bmp)al_draw_scaled_rotated_bitmap(bmp,Xsize/2,Ysize/2,x+((Xsize*bitmap_scale_x*video_scalex)/2),y+((Ysize*bitmap_scale_y*video_scaley)/2),bitmap_scale_x*video_scalex,bitmap_scale_y*video_scaley,angle,flag);}
            void start(){al_start_video(video,al_get_default_mixer());}
            bool is_playing(){return al_is_video_playing(video);}
            void stop(){pause();al_seek_video(video,0);}
            void pause(){if(is_playing())al_set_video_playing(video,0);}
            void play(){if(!is_playing())al_set_video_playing(video,1);}
            bool destroy(){if(video){al_close_video(video);video=nullptr;return 1;}return 0;}
            operator ALLEGRO_VIDEO* (){return video;}
            ~LL_Video(){destroy();}
    };

    bool LL_Video::load()
    {
        destroy();
        if(!al_reserve_samples(1))
            return false;
        video=al_open_video(video_path.c_str());
        if(video)
        {
            Xsize=al_get_video_scaled_width(video);
            Ysize=al_get_video_scaled_height(video);
        }
        return video;
    }
}

#endif // INCLUDED_LL_AL5_VIDEO_H
