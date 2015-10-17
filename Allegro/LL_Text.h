#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <string>

using namespace std;

class Font
{
    private:
        ALLEGRO_FONT* font=nullptr;
        string _D_F;
        float size;
    public:
        Font(){}
        void Refresh(){load();}
        void set_font(string Tfont){_D_F=Tfont;}
        void set_size(float Tsize){size=Tsize;}
        bool load();
        bool destroy(){if(font){al_destroy_font(font);font=nullptr;return 1;};return 0;}
        operator ALLEGRO_FONT*& (){return font;}
        ~Font(){destroy();}
};

bool Font::load()
{
    destroy();
    font=al_load_ttf_font(_D_F.c_str(),size*text_scale,0);
    return bool(font);
}

class Text
{
    private:
        //TEXT
        Font* font;
        int flag=0;
        string _m_gg;
        //COLOR AND SCALE
        ALLEGRO_COLOR TextColor;
        //POSITION
        pos_t x=0;
        pos_t y=0;
    public:
        //FUNCTIONS
        Text(){}
        Text(Font* f){font=f;}
        operator const char* () {return _m_gg.c_str();}
        operator string () {return _m_gg;}
        const char* operator = (const char* ot){_m_gg=ot;return ot;}
        string operator = (string ot){_m_gg=ot;return ot;}
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
        pos_t get_posx(){return x;}
        pos_t get_posy(){return y;}
        int get_flag(){return flag;}
        void set_flag(int _flag){flag=_flag;}
        void set_color(ALLEGRO_COLOR Other){TextColor=Other;}
        void set_font(Font* f){font=f;}
        void draw(){al_draw_text(*font,TextColor,x,y,flag,_m_gg.c_str());}
};

#endif // TEXT_H_INCLUDED
