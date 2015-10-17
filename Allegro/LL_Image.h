#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <string>

using namespace std;

bool SaveImage(string name,ALLEGRO_BITMAP* bmp)
{
    return al_save_bitmap(name.c_str(),bmp);
}

class Image
{
    private:
        //IMAGE
        ALLEGRO_BITMAP* bmp=nullptr;
        int flag=0;
        float angle=0;
        //POSITION
        pos_t x=0;
        pos_t y=0;
        //SIZE
        float Xsize=0;
        float Ysize=0;
        //Region
        bool a_region=0;
        pos_t sub_X_ini=0;
        pos_t sub_Y_ini=0;
        pos_t sub_width=0;
        pos_t sub_height=0;
        //Scale
        float bmp_scalex=1;
        float bmp_scaley=1;
    public:
        //FUNCTIONS
        Image(){}
        bool load(string Dirbmp);
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
		pos_t get_posx(){return x;}
		pos_t get_posy(){return y;}
		float get_sizex(){return Xsize;}
		float get_sizey(){return Ysize;}
        void set_angle(float an){angle=an;}
        float get_angle(){return angle;}
        void set_flag(int f){flag=f;}
		bool get_draw_a_region(){return a_region;}
        void set_draw_a_region(bool d){a_region=d;}
		pos_t get_region_posx(){return sub_X_ini;}
		pos_t get_region_posy(){return sub_Y_ini;}
        void set_region_pos(pos_t xx,pos_t yy){sub_X_ini=xx;sub_Y_ini=yy;}
		pos_t get_region_width(){return sub_width;}
		pos_t get_region_height(){return sub_height;}
        void set_region_width(pos_t w){sub_width=w;}
        void set_region_height(pos_t h){sub_height=h;}
        float get_scale_x(){return bmp_scalex;}
        float get_scale_y(){return bmp_scaley;}
        void set_scale_x(float sx){bmp_scalex=sx;}
        void set_scale_y(float sy){bmp_scaley=sy;}
        void draw();
        bool destroy(){if(bmp){al_destroy_bitmap(bmp);bmp=nullptr;return 1;}return 0;}
        operator ALLEGRO_BITMAP* (){return bmp;}
        ~Image(){destroy();}
};

void Image::draw()
{
    if(a_region)
    {
        ALLEGRO_BITMAP* EXTRAbmp=al_create_sub_bitmap(bmp,sub_X_ini,sub_Y_ini,sub_width,sub_height);
        al_draw_scaled_rotated_bitmap(EXTRAbmp,sub_width/2,sub_height/2,x+((sub_width*scale_x)/2),y+((sub_height*scale_y)/2),scale_x,scale_y,angle,flag);
        al_destroy_bitmap(EXTRAbmp);
    }
    else
        al_draw_scaled_rotated_bitmap(bmp,Xsize/2,Ysize/2,x+((Xsize*scale_x)/2),y+((Ysize*scale_y)/2),scale_x,scale_y,angle,flag);
}

bool Image::load(string Dirbmp)
{
    destroy();
    bmp=al_load_bitmap(Dirbmp.c_str());
    if(bmp)
    {
        Xsize=al_get_bitmap_width(bmp);
        Ysize=al_get_bitmap_height(bmp);
    }
    return bmp;
}

#endif // IMAGE_H_INCLUDED
