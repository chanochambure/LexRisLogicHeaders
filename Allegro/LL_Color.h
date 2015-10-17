#ifndef LL_COLOR_H_INCLUDED
#define LL_COLOR_H_INCLUDED

class Color
{
    private:
        char r=0;
        char g=0;
        char b=0;
        char a=255;
        void generatecolor(){C=al_map_rgba(r,g,b,a);}
        ALLEGRO_COLOR C;
    public:
        Color(){}
        Color(char Red,char Green,char Blue){r=Red;g=Green;b=Blue;generatecolor();}
        Color(char Red,char Green,char Blue,char Alpha){r=Red;g=Green;b=Blue;a=Alpha;generatecolor();}
        operator ALLEGRO_COLOR&(){return C;}
        Color operator ! (){Color TEMP(255-r,255-g,255-b,a);TEMP.generatecolor();return TEMP;}
        Color operator = (Color Ot){r=Ot.r;g=Ot.g;b=Ot.b;a=Ot.a;generatecolor();return (*this);}
        Color operator = (ALLEGRO_COLOR Ot){r=Ot.r;g=Ot.g;b=Ot.b;a=Ot.a;C=Ot;return (*this);}
        void set_color_rgb(char Red,char Green,char Blue){r=Red;g=Green;b=Blue;generatecolor();}
        void set_color_rgba(char Red,char Green,char Blue,char Alpha){r=Red;g=Green;b=Blue;a=Alpha,generatecolor();}
};

void ClearToColor(Color R){al_clear_to_color(R);}

#endif // LL_COLOR_H_INCLUDED
