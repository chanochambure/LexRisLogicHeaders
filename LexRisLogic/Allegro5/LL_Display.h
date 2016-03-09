#ifndef LL_AL5_DISPLAY_H_INCLUDED
#define LL_AL5_DISPLAY_H_INCLUDED

#include <string>

namespace LL_Allegro5
{
    class LL_Display
    {
        private:
            //Display
            ALLEGRO_DISPLAY* display=nullptr;
            ALLEGRO_MOUSE_CURSOR* cursor=nullptr;
            display_size_t X;
            display_size_t Y;
            int FT=ALLEGRO_WINDOWED;
            bool _destroy(){if(display){al_destroy_display(display);display=nullptr;return 1;}return 0;}
            void _create(){_destroy();al_set_new_display_flags(FT);display=al_create_display(X,Y);al_flip_display();}
            //Camera
            display_size_t RealSizeX;
            display_size_t RealSizeY;
            display_size_t LastDisplayX=1;
            display_size_t LastDisplayY=1;
            pos_t camx=0;
            pos_t camy=0;
            void _refresh_scale()
            {
                camx=((camx*X)/(LastDisplayX));
                camy=((camy*Y)/(LastDisplayY));
                LastDisplayX=X;
                LastDisplayY=Y;
                scale_x=float(X)/RealSizeX;
                scale_y=float(Y)/RealSizeY;
                text_scale=((scale_x-scale_y)/2)+scale_y;
                if(text_scale<1)
                    primitives_scale=1;
                else
                    primitives_scale=text_scale;
            }
        public:
            LL_Display(display_size_t SizeX,display_size_t SizeY){RealSizeX=X=SizeX;RealSizeY=Y=SizeY;_create();_refresh_scale();}
            LL_Display(display_size_t SizeX,display_size_t SizeY,display_size_t RealX,display_size_t RealY){X=SizeX;Y=SizeY;RealSizeX=RealX;RealSizeY=RealY;_create();_refresh_scale();}
            void set_title(std::string T){al_set_window_title(display,T.c_str());}
            void resize(display_size_t SizeX,display_size_t SizeY){X=SizeX;Y=SizeY;al_resize_display(display,X,Y);_refresh_scale();}
            display_size_t get_sizex(){return X;}
            display_size_t get_sizey(){return Y;}
            void set_realsize(display_size_t rsx,display_size_t rsy){RealSizeX=rsx;RealSizeY=rsy;_refresh_scale();}
            display_size_t get_realsizex(){return RealSizeX;}
            display_size_t get_realsizey(){return RealSizeY;}
            void set_target(){al_set_target_backbuffer(display);}
            void set_flag(int F){FT=F;_create();}
            void refresh(){al_flip_display();}
            void clear(){al_clear_to_color(al_map_rgb(255,255,255));}
            void clear_to_color(ALLEGRO_COLOR color){al_clear_to_color(color);}
            void set_cam(pos_t x,pos_t y){camx=(x*scale_x);camy=(y*scale_y);}
            void set_camx(pos_t x){camx=(x*scale_x);}
            void set_camy(pos_t y){camy=(y*scale_y);}
            pos_t get_camx(){return camx/scale_x;}
            pos_t get_camy(){return camy/scale_y;}
            void plus_x(pos_t px){camx+=(px*scale_x);}
            void plus_y(pos_t py){camy+=(py*scale_y);}
            pos_t convert_display_posx_to_cam_posx(pos_t x,bool in=1){return (x-(camx*in))/scale_x;}
            pos_t convert_display_posy_to_cam_posy(pos_t y,bool in=1){return (y-(camy*in))/scale_y;}
            bool show_cursor(){return al_show_mouse_cursor(display);}
            bool hide_cursor(){return al_hide_mouse_cursor(display);}
            bool set_cursor(ALLEGRO_BITMAP* bitmap,int x_focus,int y_focus)
            {
                destroy_cursor();
                if((cursor=al_create_mouse_cursor(bitmap,x_focus,y_focus)))
                    return al_set_mouse_cursor(display,cursor);
                return 0;
            }
            void destroy_cursor(){if(cursor)al_destroy_mouse_cursor(cursor);cursor=nullptr;}
            template<typename T>
            void draw(T* data,bool in=1)
            {
                pos_t xx=data->get_posx();
                pos_t yy=data->get_posy();
                data->set_pos(((xx)*(scale_x)-(camx*in)),((yy)*(scale_y)-(camy*in)));
                data->draw();
                data->set_pos(xx,yy);
            }
            operator ALLEGRO_DISPLAY*& (){return display;}
            operator ALLEGRO_BITMAP* (){return al_get_backbuffer(display);}
            operator ALLEGRO_MOUSE_CURSOR* (){return cursor;}
            ~LL_Display(){_destroy();destroy_cursor();}
    };
}

#endif // LL_AL5_DISPLAY_H_INCLUDED
