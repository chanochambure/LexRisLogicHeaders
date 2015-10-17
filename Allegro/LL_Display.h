#ifndef LL_DISPLAY_H_INCLUDED
#define LL_DISPLAY_H_INCLUDED

#include <string>

using namespace std;

class Display
{
    private:
        ALLEGRO_DISPLAY* display=nullptr;
        int X;
        int Y;
        int FT=ALLEGRO_WINDOWED;
        bool _destroy(){if(display){al_destroy_display(display);display=nullptr;return 1;}return 0;}
        void _create(){_destroy();al_set_new_display_flags(FT);display=al_create_display(X,Y);al_flip_display();}
    public:
        void set_title(string T){al_set_window_title(display,T.c_str());}
        void resize(int SizeX,int SizeY){X=SizeX;Y=SizeY;al_resize_display(display,X,Y);}
        int get_sizex(){return X;}
        int get_sizey(){return Y;}
        void set_flag(int F){FT=F;_create();}
        void refresh(){al_flip_display();}
        void clear(){al_clear_to_color(al_map_rgb(255,255,255));}
        Display(int SizeX,int SizeY){X=SizeX;Y=SizeY;_create();}
        ~Display(){_destroy();}
        operator ALLEGRO_DISPLAY*& (){return display;}
        operator ALLEGRO_BITMAP* (){return al_get_backbuffer(display);}
};

#endif // LL_DISPLAY_H_INCLUDED
