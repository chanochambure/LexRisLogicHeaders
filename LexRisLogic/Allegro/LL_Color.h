#ifndef LL_COLOR_H_INCLUDED
#define LL_COLOR_H_INCLUDED

struct LL_Color
{
    unsigned char Red=0;
    unsigned char Green=0;
    unsigned char Blue=0;
    unsigned char Alpha=255;
    LL_Color(unsigned char r=0,unsigned char g=0,unsigned char b=0,unsigned char a=255){Red=r;Green=g;Blue=b,Alpha=a;}
    LL_Color(ALLEGRO_COLOR color){Red=(color.r*255);Green=(color.g*255);Blue=(color.b*255);Alpha=(color.a*255);}
    operator ALLEGRO_COLOR(){return al_map_rgba(Red,Green,Blue,Alpha);}
    LL_Color operator ! (){return LL_Color(255-Red,255-Green,255-Blue,Alpha);}
    LL_Color operator = (ALLEGRO_COLOR Ot){Red=(Ot.r*255);Green=(Ot.g*255);Blue=(Ot.b*255);Alpha=(Ot.a*255);return (*this);}
    bool operator == (LL_Color Ot){return (Ot.Red==Red and Ot.Green==Green and Ot.Blue==Blue and Ot.Alpha==Alpha);}
    bool operator != (LL_Color Ot){return (Ot.Red!=Red or Ot.Green!=Green or Ot.Blue!=Blue or Ot.Alpha!=Alpha);}
};

#endif // LL_COLOR_H_INCLUDED
