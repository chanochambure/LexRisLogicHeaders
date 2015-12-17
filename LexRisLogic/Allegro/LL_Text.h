#ifndef LL_TEXT_H_INCLUDED
#define LL_TEXT_H_INCLUDED

#include <string>

using namespace std;

class LL_Font
{
    private:
        ALLEGRO_FONT* font=nullptr;
        string font_path;
        float size;
    public:
        void set_path(string new_path){font_path=new_path;}
        string get_path(){return font_path;}
        void set_size(float Tsize){size=Tsize;}
        float get_size(){return size;}
        bool load();
        bool load_for_another_target();
        void refresh(){load();}
        bool destroy(){if(font){al_destroy_font(font);font=nullptr;return 1;};return 0;}
        operator ALLEGRO_FONT*& (){return font;}
        ~LL_Font(){destroy();}
};

bool LL_Font::load()
{
    destroy();
    font=al_load_ttf_font(font_path.c_str(),size*text_scale,0);
    return bool(font);
}

bool LL_Font::load_for_another_target()
{
    destroy();
    font=al_load_ttf_font(font_path.c_str(),size,0);
    return bool(font);
}

class LL_Text
{
    private:
        LL_Font* font=nullptr;
        int flag=0;
        string _m_gg;
        ALLEGRO_COLOR TextColor;
        pos_t x=0;
        pos_t y=0;
    public:
        void set_pos(pos_t xx,pos_t yy){x=xx;y=yy;}
        void set_posx(pos_t xx){x=xx;}
        void set_posy(pos_t yy){y=yy;}
        pos_t get_posx(){return x;}
        pos_t get_posy(){return y;}
        void set_flag(int _flag){flag=_flag;}
        void set_color(ALLEGRO_COLOR Other){TextColor=Other;}
        ALLEGRO_COLOR get_color(){return TextColor;}
        void set_font(LL_Font* f){font=f;}
        LL_Font* get_font(){return font;}
        void draw(){al_draw_text(*font,TextColor,x,y,flag,_m_gg.c_str());}
        operator const char* () {return _m_gg.c_str();}
        operator string () {return _m_gg;}
        const char* operator = (const char* ot){_m_gg=ot;return ot;}
        string operator = (string ot){_m_gg=ot;return ot;}
};

#endif // LL_TEXT_H_INCLUDED
