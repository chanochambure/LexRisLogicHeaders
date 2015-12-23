#ifndef LL_COLOR_H_INCLUDED
#define LL_COLOR_H_INCLUDED

struct LL_Color
{
    unsigned char Red=0;
    unsigned char Green=0;
    unsigned char Blue=0;
    unsigned char Alpha=255;
    LL_Color(unsigned char r=0,unsigned char g=0,unsigned char b=0,unsigned char a=255){Red=r;Green=g;Blue=b,Alpha=a;}
    operator ALLEGRO_COLOR(){return al_map_rgba(Red,Green,Blue,Alpha);}
    LL_Color operator ! (){return LL_Color(255-Red,255-Green,255-Blue,Alpha);}
    LL_Color operator = (ALLEGRO_COLOR Ot){Red=(Ot.r*255);Green=(Ot.g*255);Blue=(Ot.b*255);Alpha=(Ot.a*255);return (*this);}
    bool operator == (ALLEGRO_COLOR Ot){return (Red==(Ot.r*255) and Green==(Ot.g*255) and Blue==(Ot.b*255) and Alpha==(Ot.a*255));}
    bool operator != (ALLEGRO_COLOR Ot){return (Red!=(Ot.r*255) or Green!=(Ot.g*255) or Blue!=(Ot.b*255) or Alpha!=(Ot.a*255));}
};

#endif // LL_COLOR_H_INCLUDED
