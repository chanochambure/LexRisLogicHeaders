#ifndef LL_COLOR_H_INCLUDED
#define LL_COLOR_H_INCLUDED

struct Color
{
    unsigned char Red=0;
    unsigned char Green=0;
    unsigned char Blue=0;
    unsigned char Alpha=255;
    Color(unsigned char r=0,unsigned char g=0,unsigned char b=0,unsigned char a=255){Red=r;Green=g;Blue=b,Alpha=a;}
    operator ALLEGRO_COLOR(){return al_map_rgba(Red,Green,Blue,Alpha);}
    Color operator ! (){return Color(255-Red,255-Green,255-Blue,Alpha);}
    Color operator = (ALLEGRO_COLOR Ot){Red=(Ot.r*255);Green=(Ot.g*255);Blue=(Ot.b*255);Alpha=(Ot.a*255);return (*this);}
};

#endif // LL_COLOR_H_INCLUDED
