#ifndef LL_VIDEO_H_INCLUDED
#define LL_VIDEO_H_INCLUDED

class Video
{
    private:
        //IMAGE
        ALLEGRO_VIDEO* video=nullptr;
        int flag=0;
        float angle=0;
        bool _pause=0;
        //POSITION
        pos_t x=0;
        pos_t y=0;
        //SIZE
        float Xsize=0;
        float Ysize=0;
    public:
        //FUNCTIONS
        Video(){}
        bool load(string Dirbmp);
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
		pos_t get_posx(){return x;}
		pos_t get_posy(){return y;}
		float get_sizex(){return Xsize;}
		float get_sizey(){return Ysize;}
        void set_angle(float an){angle=an;}
        float get_angle(){return angle;}
        void set_flag(int f){flag=f;}
        void draw();
        void play(){al_start_video(video, al_get_default_mixer());}
        void pause(){if(!_pause)al_pause_video(video,(_pause=1));}
        void unpause(){if(_pause)al_pause_video(video,(_pause=0));}
        double get_video_position(int sw){return al_get_video_position(video,sw);}
        bool set_video_position(double ss){return al_seek_video(video,ss);}
        void restart(){set_video_position(0);}
        bool destroy(){if(video){al_close_video(video);video=nullptr;return 1;}return 0;}
        ~Video(){destroy();}
};

void Video::draw()
{
    ALLEGRO_BITMAP* bmp=al_get_video_frame(video);
    if(bmp)al_draw_scaled_rotated_bitmap(bmp,Xsize/2,Ysize/2,x+((Xsize*scale_x)/2),y+((Ysize*scale_y)/2),scale_x,scale_y,angle,flag);
}

bool Video::load(string Dirvideo)
{
    destroy();
    video=al_open_video(Dirvideo.c_str());
    if(video)
    {
        Xsize=al_get_video_width(video);
        Ysize=al_get_video_height(video);
    }
    return video;
}

#endif // LL_VIDEO_H_INCLUDED
