#ifndef LL_AL5_PRIMITIVES_H_INCLUDED
#define LL_AL5_PRIMITIVES_H_INCLUDED

namespace LL_Allegro5
{
    class LL_Pixel
    {
        private:
            pos_t x=0;
            pos_t y=0;
            ALLEGRO_COLOR _Color=al_map_rgb(0,0,0);
        public:
            LL_Pixel(){}
            LL_Pixel(pos_t a,pos_t b){set_pos(a,b);}
            void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
            void set_posx(pos_t xx){x=xx;}
            void set_posy(pos_t yy){y=yy;}
            pos_t get_posx(){return x;}
            pos_t get_posy(){return y;}
            void set_color(ALLEGRO_COLOR Other){_Color=Other;}
            ALLEGRO_COLOR get_color(){return _Color;}
            void draw(){al_draw_filled_rectangle(x,y,x+scale_x,y+scale_y,_Color);}
            void draw_in_another_target(){al_put_pixel(x,y,_Color);}
    };

    class LL_Line
    {
        private:
            pos_t camx=0;
            pos_t camy=0;
            pos_t x1=0;
            pos_t y1=0;
            pos_t x2=0;
            pos_t y2=0;
            ALLEGRO_COLOR _Color=al_map_rgb(0,0,0);
            float _size=1;
        public:
            LL_Line(){}
            LL_Line(pos_t posx1,pos_t posy1,pos_t posx2,pos_t posy2){x1=posx1;y1=posy1;x2=posx2;y2=posy2;}
            void set_pos(pos_t xx,pos_t yy){camx=xx;camy=yy;}
            void set_posx(pos_t x){camx=x;}
            void set_posy(pos_t y){camy=y;}
            pos_t get_posx(){return camx;}
            pos_t get_posy(){return camy;}
            void set_points(float posx1,float posy1,float posx2,float posy2){x1=posx1;y1=posy1;x2=posx2;y2=posy2;}
            void set_point_1(pos_t xx,pos_t yy){x1=xx;y1=yy;}
            pos_t get_posx_point1(){return x1;}
            pos_t get_posy_point1(){return y1;}
            void set_point_2(pos_t xx,pos_t yy){x2=xx;y2=yy;}
            pos_t get_posx_point2(){return x2;}
            pos_t get_posy_point2(){return y2;}
            void set_color(ALLEGRO_COLOR Other){_Color=Other;}
            ALLEGRO_COLOR get_color(){return _Color;}
            void set_thickness(float ot){_size=ot;}
            float get_thickness(){return _size;}
            void draw(){al_draw_line((x1*scale_x)+camx,(y1*scale_y)+camy,(x2*scale_x)+camx,(y2*scale_y)+camy,_Color,_size*primitives_scale);}
            void draw_in_another_target(){al_draw_line(x1+camx,y1+camy,x2+camx,y2+camy,_Color,_size);}
    };

    class LL_Primitive
    {
        protected:
            bool _filled=0;
            float _size=1;
            ALLEGRO_COLOR _Color=al_map_rgb(0,0,0);
        public:
            void set_thickness(float ot){_size=ot;}
            float get_thickness(){return _size;}
            void set_color(ALLEGRO_COLOR Other){_Color=Other;}
            ALLEGRO_COLOR get_color(){return _Color;}
            void set_is_filled(bool op){_filled=op;}
            bool is_filled(){return _filled;}
    };

    class LL_Figure:public LL_Primitive
    {
        protected:
            pos_t x=0;
            pos_t y=0;
        public:
            void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
            void set_posx(pos_t xx){x=xx;}
            void set_posy(pos_t yy){y=yy;}
            pos_t get_posx(){return x;}
            pos_t get_posy(){return y;}
    };

    class LL_Circle:public LL_Figure
    {
        private:
            float _ratio=1;
        public:
            LL_Circle(){}
            LL_Circle(pos_t a,pos_t b,float r){set_pos(a,b);_ratio=r;}
            void set_ratio(float ot){_ratio=ot;}
            float get_ratio(){return _ratio;}
            void draw(){if(is_filled())al_draw_filled_ellipse(x,y,_ratio*scale_x,_ratio*scale_y,_Color);al_draw_ellipse(x,y,_ratio*scale_x,_ratio*scale_y,_Color,_size*primitives_scale);}
            void draw_in_another_target(){if(is_filled())al_draw_filled_circle(x,y,_ratio,_Color);al_draw_circle(x,y,_ratio,_Color,_size);}
    };

    class LL_Ellipse:public LL_Figure
    {
        private:
            float _ratiox=1;
            float _ratioy=1;
        public:
            LL_Ellipse(){}
            LL_Ellipse(pos_t a,pos_t b,float rx,float ry){set_pos(a,b);_ratiox=rx;_ratioy=ry;}
            void set_ratiox(float ot){_ratiox=ot;}
            float get_ratiox(){return _ratiox;}
            void set_ratioy(float ot){_ratioy=ot;}
            float get_ratioy(){return _ratioy;}
            void draw(){if(is_filled())al_draw_filled_ellipse(x,y,_ratiox*scale_x,_ratioy*scale_y,_Color);al_draw_ellipse(x,y,_ratiox*scale_x,_ratioy*scale_y,_Color,_size*primitives_scale);}
            void draw_in_another_target(){if(is_filled())al_draw_filled_ellipse(x,y,_ratiox,_ratioy,_Color);al_draw_ellipse(x,y,_ratiox,_ratioy,_Color,_size);}
    };

    class LL_Rectangle:public LL_Figure
    {
        private:
            float _tamx=0;
            float _tamy=0;
        public:
            LL_Rectangle(){}
            LL_Rectangle(pos_t posx,pos_t posy,float tamx,float tamy){set_pos(posx,posy);_tamx=tamx;_tamy=tamy;}
            void set_sizex(float ot){_tamx=ot;}
            float get_sizex(){return _tamx;}
            void set_sizey(float ot){_tamy=ot;}
            float get_sizey(){return _tamy;}
            void draw(){if(is_filled())al_draw_filled_rectangle(x,y,x+(_tamx*scale_x),y+(_tamy*scale_y),_Color);al_draw_rectangle(x,y,x+(_tamx*scale_x),y+(_tamy*scale_y),_Color,_size*primitives_scale);}
            void draw_in_another_target(){if(is_filled())al_draw_filled_rectangle(x,y,x+(_tamx),y+(_tamy),_Color);al_draw_rectangle(x,y,x+(_tamx),y+(_tamy),_Color,_size);}
    };

    class LL_Triangle:public LL_Primitive
    {
        private:
            pos_t camx=0;
            pos_t camy=0;
            pos_t x1=0;
            pos_t x2=0;
            pos_t x3=0;
            pos_t y1=0;
            pos_t y2=0;
            pos_t y3=0;
        public:
            LL_Triangle(){}
            LL_Triangle(float posx1,float posy1,float posx2,float posy2,float posx3,float posy3){x1=posx1;y1=posy1;x2=posx2;y2=posy2;x3=posx3;y3=posy3;}
            void set_pos(pos_t xx,pos_t yy){camx=xx;camy=yy;}
            void set_posx(pos_t x){camx=x;}
            void set_posy(pos_t y){camy=y;}
            pos_t get_posx(){return camx;}
            pos_t get_posy(){return camy;}
            void set_points(float posx1,float posy1,float posx2,float posy2,float posx3,float posy3){x1=posx1;y1=posy1;x2=posx2;y2=posy2;x3=posx3;y3=posy3;}
            void set_point_1(pos_t xx,pos_t yy){x1=xx;y1=yy;}
            pos_t get_posx_point1(){return x1;}
            pos_t get_posy_point1(){return y1;}
            void set_point_2(pos_t xx,pos_t yy){x2=xx;y2=yy;}
            pos_t get_posx_point2(){return x2;}
            pos_t get_posy_point2(){return y2;}
            void set_point_3(pos_t xx,pos_t yy){x3=xx;y3=yy;}
            pos_t get_posx_point3(){return x3;}
            pos_t get_posy_point3(){return y3;}
            void draw()
            {
                if(is_filled())
                    al_draw_filled_triangle(x1*scale_x+camx,y1*scale_y+camy,x2*scale_x+camx,y2*scale_y+camy,x3*scale_x+camx,y3*scale_y+camy,_Color);
                al_draw_triangle(x1*scale_x+camx,y1*scale_y+camy,x2*scale_x+camx,y2*scale_y+camy,x3*scale_x+camx,y3*scale_y+camy,_Color,_size*primitives_scale);
            }
            void draw_in_another_target()
            {
                if(is_filled())
                    al_draw_filled_triangle(x1+camx,y1+camy,x2+camx,y2+camy,x3+camx,y3+camy,_Color);
                al_draw_triangle(x1+camx,y1+camy,x2+camx,y2+camy,x3+camx,y3+camy,_Color,_size);
            }
    };

    class LL_Function
    {
        private:
            pos_t _init_=0;
            pos_t _final_=1;
            pos_t camx=0;
            pos_t camy=0;
            float pass=0;
            float _size=1;
            ALLEGRO_COLOR FunctionColor=al_map_rgb(0,0,0);
            pos_t (*_fx)(pos_t)=nullptr;
        public:
            LL_Function(pos_t (*ofx)(pos_t)){_fx=ofx;}
            void set_pos(pos_t xx,pos_t yy){camx=xx;camy=yy;}
            void set_posx(pos_t xx){camx=xx;}
            void set_posy(pos_t yy){camy=yy;}
            pos_t get_posx(){return camx;}
            pos_t get_posy(){return camy;}
            void set_thickness(float ot){_size=ot;}
            float get_thickness(){return _size;}
            void set_color(ALLEGRO_COLOR Other){FunctionColor=Other;}
            ALLEGRO_COLOR get_color(){return FunctionColor;}
            void set_pass(float _p){pass=_p;}
            float get_pass(){return pass;}
            void set_init(pos_t x){_init_=x;}
            pos_t get_init(){return _init_;}
            void set_final(pos_t x){_final_=x;}
            pos_t get_final(){return _final_;}
            void set_function(pos_t (*ofx)(pos_t)){_fx=ofx;}
            void draw();
            void draw_in_another_target();
    };

    void LL_Function::draw()
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

    void LL_Function::draw_in_another_target()
    {
        pos_t i=_init_;
        if(i<=_final_)
        {
            if(pass>0)
            {
                pos_t j=_init_+pass;
                while(j<_final_)
                {
                    al_draw_line((i)+camx,(_fx(i))+camy,(j)+camx,(_fx(j))+camy,FunctionColor,_size);
                    i+=pass;
                    j+=pass;
                }
            }
            al_draw_line((i)+camx,(_fx(i))+camy,(_final_)+camx,(_fx(_final_))+camy,FunctionColor,_size);
        }
    }
}

#endif // LL_AL5_PRIMITIVES_H_INCLUDED
