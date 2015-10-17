#ifndef LL_PRIMITIVES_H_INCLUDED
#define LL_PRIMITIVES_H_INCLUDED

class __Figure__
{
    private:
        bool _filled=0;
        pos_t x=0;
        pos_t y=0;
        float _size=1;
        ALLEGRO_COLOR _Color=al_map_rgb(0,0,0);
    public:
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
        pos_t get_posx(){return x;}
        pos_t get_posy(){return y;}
        void set_thickness(float ot){_size=ot;}
        float get_thickness(){return _size;}
        void set_color(ALLEGRO_COLOR Other){_Color=Other;}
        ALLEGRO_COLOR& get_color(){return _Color;}
        void set_is_filled(bool op){_filled=op;}
        bool is_filled(){return _filled;}
};

class point
{
    private:
        pos_t x=0;
        pos_t y=0;
        ALLEGRO_COLOR _Color=al_map_rgb(0,0,0);
    public:
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
        pos_t get_posx(){return x;}
        pos_t get_posy(){return y;}
        void set_color(ALLEGRO_COLOR Other){_Color=Other;}
        ALLEGRO_COLOR& get_color(){return _Color;}
        point(){}
        point(float a,float b){set_pos(a,b);}
        point operator = (point ot){set_pos(ot.get_posx(),ot.get_posy());return (*this);}
        void draw(){al_draw_filled_rectangle(get_posx(),get_posy(),get_posx()+scale_x,get_posy()+scale_y,get_color());}
};

class circle:public __Figure__
{
    private:
        float _ratio=1;
    public:
        circle(){}
        circle(float a,float b,float r){set_pos(a,b);_ratio=r;}
        void set_ratio(float ot){_ratio=ot;}
        float get_ratio(){return _ratio;}
        void draw(){if(is_filled())al_draw_filled_ellipse(get_posx(),get_posy(),_ratio*scale_x,_ratio*scale_y,get_color());al_draw_ellipse(get_posx(),get_posy(),_ratio*scale_x,_ratio*scale_y,get_color(),get_thickness()*primitives_scale);}
};

class ellipse:public __Figure__
{
    private:
        float _ratiox=1;
        float _ratioy=1;
    public:
        ellipse(){}
        ellipse(pos_t a,pos_t b,float rx,float ry){set_pos(a,b);_ratiox=rx;_ratioy=ry;}
        void set_ratiox(float ot){_ratiox=ot;}
        float get_ratiox(){return _ratiox;}
        void set_ratioy(float ot){_ratioy=ot;}
        float get_ratioy(){return _ratioy;}
        void draw(){if(is_filled())al_draw_filled_ellipse(get_posx(),get_posy(),_ratiox*scale_x,_ratioy*scale_y,get_color());al_draw_ellipse(get_posx(),get_posy(),_ratiox*scale_x,_ratioy*scale_y,get_color(),get_thickness()*primitives_scale);}
};

class rectangle:public __Figure__
{
    private:
        pos_t _tamx=0;
        pos_t _tamy=0;
    public:
        rectangle(){}
        rectangle(pos_t posx,pos_t posy,pos_t tamx,pos_t tamy){set_pos(posx,posy);_tamx=tamx;_tamy=tamy;}
        void set_tamx(pos_t ot){_tamx=ot;}
        float get_tamx(){return _tamx;}
        void set_tamy(pos_t ot){_tamy=ot;}
        float get_tamy(){return _tamy;}
        void draw(){if(is_filled())al_draw_filled_rectangle(get_posx(),get_posy(),get_posx()+(_tamx*scale_x),get_posy()+(_tamy*scale_y),get_color());al_draw_rectangle(get_posx(),get_posy(),get_posx()+(_tamx*scale_x),get_posy()+(_tamy*scale_y),get_color(),get_thickness()*primitives_scale);}
};

class function
{
    private:
        pos_t _init_=0;
        pos_t _final_=1;
        pos_t camx=0;
        pos_t camy=0;
        float pass=0;
        float _size=1;
        ALLEGRO_COLOR FunctionColor=al_map_rgb(0,0,0);
        float (*_fx)(float);
    public:
        function(float (*ofx)(float)){_fx=ofx;}
        void set_pos(pos_t xx,pos_t yy){camx=xx;camy=yy;}
        pos_t get_posx(){return 0;}
        pos_t get_posy(){return 0;}
        void set_pass(float _p){pass=_p;}
        float get_pass(){return pass;}
        void set_init(pos_t x){_init_=x;}
        void set_final(pos_t x){_final_=x;}
        pos_t get_init(){return _init_;}
        pos_t get_final(){return _final_;}
        void set_color(ALLEGRO_COLOR Other){FunctionColor=Other;}
        void set_thickness(float ot){_size=ot;}
        float get_size(){return _size;}
        void draw();
};

void function::draw()
{
    pos_t i=_init_;
    if(i<=_final_)
    {
        if(pass>0)
        {
            pos_t j=_init_+pass;
            while(j<_final_)
            {
                al_draw_line((i*scale_x)+camx,(_fx(i)*scale_y)+camy,(j*scale_x)+camx,(_fx(j)*scale_y)+camy,FunctionColor,_size*primitives_scale);
                i+=pass;
                j+=pass;
            }
        }
        al_draw_line((i*scale_x)+camx,(_fx(i)*scale_y)+camy,(_final_*scale_x)+camx,(_fx(_final_)*scale_y)+camy,FunctionColor,_size*primitives_scale);
    }
}


#endif // LL_PRIMITIVES_H_INCLUDED
