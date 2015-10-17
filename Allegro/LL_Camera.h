#ifndef LL_CAMERA_H_INCLUDED
#define LL_CAMERA_H_INCLUDED

float _x_l=1;
float _y_l=1;

void set_scale(float dx,float dy,int rx,int ry)
{
    _x_l=dx;
    _y_l=dy;
    scale_x=dx/rx;
    scale_y=dy/ry;
    text_scale=((scale_x-scale_y)/2)+scale_y;
    if(text_scale<1)
        primitives_scale=1;
    else
        primitives_scale=text_scale;
}

class Camera
{
    private:
        double RealSizeX;
        double RealSizeY;
        ALLEGRO_DISPLAY* _dd=nullptr;
        pos_t camx=0;
        pos_t camy=0;
    public:
        void Refresh(){camx=((camx*al_get_display_width(_dd))/(_x_l));camy=((camy*al_get_display_height(_dd))/(_y_l));set_scale(al_get_display_width(_dd),al_get_display_height(_dd),RealSizeX,RealSizeY);}
        Camera(ALLEGRO_DISPLAY* display,int realsizex,int realiszey){_dd=display;RealSizeX=realsizex;RealSizeY=realiszey;Refresh();}
        void ChangeDisplay(ALLEGRO_DISPLAY* display){_dd=display;Refresh();}
        template<typename T>
        void draw(T* data,bool in){pos_t xx=data->get_posx();pos_t yy=data->get_posy();data->set_pos(((xx)*(scale_x)-(camx*in)),((yy)*(scale_y)-(camy*in)));data->draw();data->set_pos(xx,yy);}
        void set_cam(pos_t x,pos_t y){camx=(x*scale_x);camy=(y*scale_y);}
		pos_t get_camx(){return camx/scale_x;}
		pos_t get_camy(){return camy/scale_y;}
		void set_realsize(int realsizex,int realiszey){RealSizeX=realsizex;RealSizeY=realiszey;Refresh();}
		double get_realsizex(){return RealSizeX;}
		double get_realsizey(){return RealSizeY;}
        void plus_x(pos_t v){camx+=(v*scale_x);}
        void plus_y(pos_t v){camy+=(v*scale_y);}
};

#endif // LL_CAMERA_H_INCLUDED
