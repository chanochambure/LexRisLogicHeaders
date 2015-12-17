#ifndef LL_VIDEO_H_INCLUDED
#define LL_VIDEO_H_INCLUDED

class LL_Video
{
    private:
        ALLEGRO_VIDEO* video=nullptr;
        int flag=0;
        float angle=0;
        bool _pause=0;
        pos_t x=0;
        pos_t y=0;
        float Xsize=0;
        float Ysize=0;
        float video_scalex=1;
        float video_scaley=1;
        string video_path;
    public:
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
        void set_posx(pos_t xx){x=xx;}
        void set_posy(pos_t yy){y=yy;}
		pos_t get_posx(){return x;}
		pos_t get_posy(){return y;}
		float get_sizex(){return Xsize;}
		float get_sizey(){return Ysize;}
        void set_angle(float an){angle=an;}
        float get_angle(){return angle;}
        void set_flag(int f){flag=f;}
        void set_scale_x(float sx){video_scalex=sx;}
        void set_scale_y(float sy){video_scaley=sy;}
        float get_scale_x(){return video_scalex;}
        float get_scale_y(){return video_scaley;}
        void set_path(string new_path){video_path=new_path;}
        string get_path(){return video_path;}
        bool load();
        bool set_position(double ss){return al_seek_video(video,ss);}
        double get_position(int sw=0){return al_get_video_position(video,sw);}
        void draw(){ALLEGRO_BITMAP* bmp=al_get_video_frame(video);if(bmp)al_draw_scaled_rotated_bitmap(bmp,Xsize/2,Ysize/2,x+((Xsize*scale_x*video_scalex)/2),y+((Ysize*scale_y*video_scaley)/2),scale_x*video_scalex,scale_y*video_scaley,angle,flag);}
        void start(){al_start_video(video,al_get_default_mixer());}
        void stop(){pause();al_seek_video(video,0);}
        void pause(){if(!_pause)al_pause_video(video,(_pause=1));}
        void play(){if(_pause)al_pause_video(video,(_pause=0));}
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
        Xsize=al_get_video_width(video);
        Ysize=al_get_video_height(video);
    }
    return video;
}

#endif // LL_VIDEO_H_INCLUDED
