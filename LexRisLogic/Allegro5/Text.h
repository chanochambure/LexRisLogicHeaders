#ifndef INCLUDED_LL_AL5_TEXT_H
#define INCLUDED_LL_AL5_TEXT_H

#include <string>

namespace LL_AL5
{
    class LL_Font
    {
        private:
            ALLEGRO_FONT* font=nullptr;
            std::string font_path;
            float size;
        public:
            void set_path(std::string new_path){font_path=new_path;}
            std::string get_path(){return font_path;}
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
            std::string _message;
            ALLEGRO_COLOR TextColor;
            Type_pos x=0;
            Type_pos y=0;
        public:
            void set_pos(Type_pos xx,Type_pos yy){x=xx;y=yy;}
            void set_posx(Type_pos xx){x=xx;}
            void set_posy(Type_pos yy){y=yy;}
            Type_pos get_posx(){return x;}
            Type_pos get_posy(){return y;}
            void set_flag(int _flag){flag=_flag;}
            void set_color(ALLEGRO_COLOR Other){TextColor=Other;}
            ALLEGRO_COLOR get_color(){return TextColor;}
            void set_font(LL_Font* f){font=f;}
            LL_Font* get_font(){return font;}
            void draw(){al_draw_text(*font,TextColor,x,y,flag,_message.c_str());}
            operator const char* () {return _message.c_str();}
            operator std::string () {return _message;}
            const char* operator = (const char* ot){_message=ot;return ot;}
            std::string operator = (std::string ot){_message=ot;return ot;}
    };
}

#endif // INCLUDED_LL_AL5_TEXT_H
