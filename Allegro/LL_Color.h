#ifndef LL_COLOR_H_INCLUDED
#define LL_COLOR_H_INCLUDED

struct Color
{
    char Red=0;
    char Green=0;
    char Blue=0;
    char Alpha=255;
    Color(char r=0,char g=0,char b=0,char a=255){Red=r;Green=g;Blue=b,Alpha=a;}
    operator ALLEGRO_COLOR(){return al_map_rgba(Red,Green,Blue,Alpha);}
    Color operator ! (){return Color(255-Red,255-Green,255-Blue,Alpha);}
    Color operator = (ALLEGRO_COLOR Ot){Red=Ot.r;Green=Ot.g;Blue=Ot.b;Alpha=Ot.a;return (*this);}
};

#endif // LL_COLOR_H_INCLUDED
