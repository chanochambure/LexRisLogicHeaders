#ifndef LL_BITMAP_H_INCLUDED
#define LL_BITMAP_H_INCLUDED

#include <string>

using namespace std;

bool save_bitmap(string name,ALLEGRO_BITMAP* bmp)
{
    return al_save_bitmap(name.c_str(),bmp);
}

class LL_Bitmap_Base
{
    protected:
        int flag=0;
        float angle=0;
        pos_t x=0;
        pos_t y=0;
        float bmp_scalex=1;
        float bmp_scaley=1;
        bool special_X_pos=0;
        bool special_Y_pos=0;
    public:
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
        void set_posx(pos_t xx){x=xx;}
        void set_posy(pos_t yy){y=yy;}
		pos_t get_posx(){return x;}
		pos_t get_posy(){return y;}
        void set_angle(float an){angle=an;}
        float get_angle(){return angle;}
        void set_flag(int f){flag=f;}
        void set_scale_x(float sx){bmp_scalex=sx;}
        void set_scale_y(float sy){bmp_scaley=sy;}
        float get_scale_x(){return bmp_scalex;}
        float get_scale_y(){return bmp_scaley;}
        void set_position_to_draw(bool pos_x,bool pos_y){special_X_pos=pos_x;special_Y_pos=pos_y;}
};

class LL_Bitmap:public LL_Bitmap_Base
{
    protected:
        ALLEGRO_BITMAP* bmp=nullptr;
        float Xsize=0;
        float Ysize=0;
    public:
		float get_sizex(){return Xsize;}
		float get_sizey(){return Ysize;}
        void set_target(){if(bmp)al_set_target_bitmap(bmp);}
        bool create(int s_X,int s_Y){destroy();bmp=al_create_bitmap(s_X,s_Y);if(bmp){Xsize=s_X;Ysize=s_Y;return 1;}return 0;}
        bool destroy(){if(bmp){al_destroy_bitmap(bmp);bmp=nullptr;return 1;}return 0;}
        void draw()
        {
            const int size_in_axe_x=(Xsize*scale_x*bmp_scalex);
            const int size_in_axe_y=(Ysize*scale_y*bmp_scaley);
            al_draw_scaled_rotated_bitmap(bmp,
                                          Xsize/2,
                                          Ysize/2,
                                          x-(!special_X_pos*(size_in_axe_x/2)),
                                          y-(!special_Y_pos*(size_in_axe_y/2)),
                                          scale_x*bmp_scalex,
                                          scale_y*bmp_scaley,
                                          angle,flag);
        }
        void draw_in_another_target()
        {
            const int size_in_axe_x=(Xsize*bmp_scalex);
            const int size_in_axe_y=(Ysize*bmp_scaley);
            al_draw_scaled_rotated_bitmap(bmp,
                                          Xsize/2,
                                          Ysize/2,
                                          x-(!special_X_pos*(size_in_axe_x/2)),
                                          y-(!special_Y_pos*(size_in_axe_y/2)),
                                          bmp_scalex,
                                          bmp_scaley,
                                          angle,
                                          flag);
        }
        operator ALLEGRO_BITMAP* (){return bmp;}
        ~LL_Bitmap(){destroy();}
};

class LL_SubBitmap:public LL_Bitmap
{
    private:
        ALLEGRO_BITMAP* parent=nullptr;
        pos_t sub_x=0;
        pos_t sub_y=0;
    public:
        void set_bitmap_parent(ALLEGRO_BITMAP* ft){parent=ft;}
        ALLEGRO_BITMAP* get_bitmap_parent(){return parent;}
        void set_sub_x(pos_t nx){sub_x=nx;}
        void set_sub_y(pos_t ny){sub_y=ny;}
        pos_t get_sub_x(){return sub_x;}
        pos_t get_sub_y(){return sub_y;}
        void set_sizex(int s_x){Xsize=s_x;}
        void set_sizey(int s_y){Ysize=s_y;}
        bool create_sub_bitmap(){destroy();bmp=al_create_sub_bitmap(parent,sub_x,sub_y,Xsize,Ysize);return bmp;}
};

class LL_Image:public LL_Bitmap
{
    private:
        string image_path;
    public:
        void set_path(string new_path){image_path=new_path;}
        string get_path(){return image_path;}
        bool load(){destroy();bmp=al_load_bitmap(image_path.c_str());if(bmp){Xsize=al_get_bitmap_width(bmp);Ysize=al_get_bitmap_height(bmp);}return bmp;}
        bool save(){return save_bitmap(image_path,bmp);}
};

#endif // LL_BITMAP_H_INCLUDED
