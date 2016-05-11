#ifndef INCLUDED_LL_AL5_DISPLAY_H
#define INCLUDED_LL_AL5_DISPLAY_H

#include <string>

namespace LL_AL5
{
    class Display
    {
        private:
            ALLEGRO_DISPLAY* _V_display=nullptr;
            ALLEGRO_MOUSE_CURSOR* _V_cursor=nullptr;
            Type_display_size X;
            Type_display_size Y;
            Type_display_size RealSizeX;
            Type_display_size RealSizeY;
            Type_display_size LastDisplayX=1;
            Type_display_size LastDisplayY=1;
            Type_pos camx=0;
            Type_pos camy=0;
            int _V_display_mode=ALLEGRO_WINDOWED;
            bool _F_destroy(){if(_V_display){al_destroy_display(_V_display);_V_display=nullptr;return 1;}return 0;}
            void _F_create(){_F_destroy();al_set_new_display_flags(_V_display_mode);_V_display=al_create_display(X,Y);al_flip_display();}
            void _refresh_scale()
            {
                camx=((camx*X)/(LastDisplayX));
                camy=((camy*Y)/(LastDisplayY));
                LastDisplayX=X;
                LastDisplayY=Y;
                bitmap_scale_x=float(X)/RealSizeX;
                bitmap_scale_y=float(Y)/RealSizeY;
                text_scale=((bitmap_scale_x-bitmap_scale_y)/2)+bitmap_scale_y;
                if(text_scale<1)
                    primitives_scale=1;
                else
                    primitives_scale=text_scale;
            }
        public:
            Display(Type_display_size SizeX,Type_display_size SizeY){RealSizeX=X=SizeX;RealSizeY=Y=SizeY;_F_create();_refresh_scale();}
            Display(Type_display_size SizeX,Type_display_size SizeY,Type_display_size RealX,Type_display_size RealY){X=SizeX;Y=SizeY;RealSizeX=RealX;RealSizeY=RealY;_F_create();_refresh_scale();}
            void set_title(std::string T){al_set_window_title(_V_display,T.c_str());}
            void resize(Type_display_size SizeX,Type_display_size SizeY){X=SizeX;Y=SizeY;al_resize_display(_V_display,X,Y);_refresh_scale();}
            Type_display_size get_sizex(){return X;}
            Type_display_size get_sizey(){return Y;}
            void set_realsize(Type_display_size rsx,Type_display_size rsy){RealSizeX=rsx;RealSizeY=rsy;_refresh_scale();}
            Type_display_size get_realsizex(){return RealSizeX;}
            Type_display_size get_realsizey(){return RealSizeY;}
            void set_target(){al_set_target_backbuffer(_V_display);}
            void set_flag(int F){_V_display_mode=F;_F_create();}
            void refresh(){al_flip_display();}
            void clear(){al_clear_to_color(al_map_rgb(255,255,255));}
            void clear_to_color(ALLEGRO_COLOR color){al_clear_to_color(color);}
            void set_cam(Type_pos x,Type_pos y){camx=(x*bitmap_scale_x);camy=(y*bitmap_scale_y);}
            void set_camx(Type_pos x){camx=(x*bitmap_scale_x);}
            void set_camy(Type_pos y){camy=(y*bitmap_scale_y);}
            Type_pos get_camx(){return camx/bitmap_scale_x;}
            Type_pos get_camy(){return camy/bitmap_scale_y;}
            void plus_x(Type_pos px){camx+=(px*bitmap_scale_x);}
            void plus_y(Type_pos py){camy+=(py*bitmap_scale_y);}
            Type_pos convert_display_posx_to_cam_posx(Type_pos x,bool in=1){return (x+(camx*in))/bitmap_scale_x;}
            Type_pos convert_display_posy_to_cam_posy(Type_pos y,bool in=1){return (y+(camy*in))/bitmap_scale_y;}
            bool show_cursor(){return al_show_mouse_cursor(_V_display);}
            bool hide_cursor(){return al_hide_mouse_cursor(_V_display);}
            bool set_cursor(ALLEGRO_BITMAP* bitmap,int x_focus,int y_focus)
            {
                destroy_cursor();
                if((_V_cursor=al_create_mouse_cursor(bitmap,x_focus,y_focus)))
                    return al_set_mouse_cursor(_V_display,_V_cursor);
                return 0;
            }
            void destroy_cursor(){if(_V_cursor)al_destroy_mouse_cursor(_V_cursor);_V_cursor=nullptr;}
            template<typename T>
            void draw(T* data,bool in=1)
            {
                Type_pos xx=data->get_posx();
                Type_pos yy=data->get_posy();
                data->set_pos(((xx)*(bitmap_scale_x)-(camx*in)),((yy)*(bitmap_scale_y)-(camy*in)));
                data->draw();
                data->set_pos(xx,yy);
            }
            operator ALLEGRO_DISPLAY*& (){return _V_display;}
            operator ALLEGRO_BITMAP* (){return al_get_backbuffer(_V_display);}
            operator ALLEGRO_MOUSE_CURSOR* (){return _V_cursor;}
            ~Display(){_F_destroy();destroy_cursor();}
    };
}

#endif // INCLUDED_LL_AL5_DISPLAY_H
