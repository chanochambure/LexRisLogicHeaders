#ifndef LL_CAMERA_H_INCLUDED
#define LL_CAMERA_H_INCLUDED

class Camera
{
    private:
        display_size_t RealSizeX;
        display_size_t RealSizeY;
        ALLEGRO_DISPLAY* _dd=nullptr;
        pos_t camx=0;
        pos_t camy=0;
        float _x_l=1;
        float _y_l=1;
        void __set_scale(float dx,float dy,display_size_t rx,display_size_t ry){_x_l=dx;_y_l=dy;scale_x=dx/rx;scale_y=dy/ry;text_scale=((scale_x-scale_y)/2)+scale_y;if(text_scale<1)primitives_scale=1;else{primitives_scale=text_scale;}}
    public:
        Camera(ALLEGRO_DISPLAY* display,display_size_t rsx,display_size_t rsy){_dd=display;RealSizeX=rsx;RealSizeY=rsy;refresh();}
        void set_display(ALLEGRO_DISPLAY* display){_dd=display;refresh();}
        ALLEGRO_DISPLAY* get_display(){return _dd;}
		void set_realsize(display_size_t rsx,display_size_t rsy){RealSizeX=rsx;RealSizeY=rsy;refresh();}
		display_size_t get_realsizex(){return RealSizeX;}
		display_size_t get_realsizey(){return RealSizeY;}
        void set_cam(pos_t x,pos_t y){camx=(x*scale_x);camy=(y*scale_y);}
        void set_camx(pos_t x){camx=(x*scale_x);}
        void set_camy(pos_t y){camy=(y*scale_y);}
		pos_t get_camx(){return camx/scale_x;}
		pos_t get_camy(){return camy/scale_y;}
        void plus_x(pos_t v){camx+=(v*scale_x);}
        void plus_y(pos_t v){camy+=(v*scale_y);}
        void refresh(){camx=((camx*al_get_display_width(_dd))/(_x_l));camy=((camy*al_get_display_height(_dd))/(_y_l));__set_scale(al_get_display_width(_dd),al_get_display_height(_dd),RealSizeX,RealSizeY);}
        template<typename T>
        void draw(T* data,bool in=1){pos_t xx=data->get_posx();pos_t yy=data->get_posy();data->set_pos(((xx)*(scale_x)-(camx*in)),((yy)*(scale_y)-(camy*in)));data->draw();data->set_pos(xx,yy);}
};

#endif // LL_CAMERA_H_INCLUDED
