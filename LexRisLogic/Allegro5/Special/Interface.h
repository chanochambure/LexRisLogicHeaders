#ifndef INCLUDED_LL_AL5_INTERFACE_H
#define INCLUDED_LL_AL5_INTERFACE_H

#include <string>
#include "../Input.h"
#include "../Text.h"

namespace LL_AL5
{
    class LL_Interface
    {
        protected:
            Type_pos x=0;
            Type_pos y=0;
            float Xsize=0;
            float Ysize=0;
            LL_Font* _font=nullptr;
            ALLEGRO_COLOR TextColor;
            LL_Input* input=nullptr;
            float _size=1;
            ALLEGRO_COLOR U_LineColor;
            ALLEGRO_COLOR U_FilledColor;
            ALLEGRO_COLOR C_LineColor;
            ALLEGRO_COLOR C_FilledColor;
            bool _is_in(){Type_pos mx=input->get_mouse_x();Type_pos my=input->get_mouse_y();return ((x<=mx and mx<(x+(Xsize*bitmap_scale_x))) and (y<=my and my<(y+(Ysize*bitmap_scale_y))));}
            bool _block=0;
        public:
            Type_pos get_posx(){return x;}
            Type_pos get_posy(){return y;}
            float get_sizex(){return Xsize;}
            float get_sizey(){return Ysize;}
            //FIGURE CONFIGURATION
            void set_unclick_line_color(ALLEGRO_COLOR Other){U_LineColor=Other;}
            ALLEGRO_COLOR get_unclick_line_color(){return U_LineColor;}
            void set_unclick_filled_color(ALLEGRO_COLOR Other){U_FilledColor=Other;}
            ALLEGRO_COLOR get_unclick_filled_color(){return U_FilledColor;}
            void set_click_line_color(ALLEGRO_COLOR Other){C_LineColor=Other;}
            ALLEGRO_COLOR get_click_line_color(){return C_LineColor;}
            void set_click_filled_color(ALLEGRO_COLOR Other){C_FilledColor=Other;}
            ALLEGRO_COLOR get_click_filled_color(){return C_FilledColor;}
            void set_thickness(float ot){_size=ot;}
            float get_thickness(){return _size;}
            //TEXT CONFIGURATION
            LL_Font* get_font(){return _font;}
            void set_text_color(ALLEGRO_COLOR Other){TextColor=Other;}
            ALLEGRO_COLOR get_text_color(){return TextColor;}
            virtual ~LL_Interface(){}
    };

    class LL_Button:public LL_Interface
    {
        private:
            unsigned int _font_size=1;
            Type_pos middle_x=0;
            Type_pos middle_y=0;
            std::string _message;
            bool _lock=0;
            bool _bool_value=0;
            void _hear_event(){if(!_lock and _block and input->left_click() and _is_in()){_bool_value=_lock=1;return;}if(!input->left_click())_lock=0;_bool_value=0;}
        public:
            LL_Button(LL_Input* in)
            {
                input=in;
                TextColor=U_LineColor=C_LineColor=al_map_rgb(0,0,0);
                U_FilledColor=al_map_rgb(255,255,255);
                C_FilledColor=al_map_rgb(0,0,250);
            }
            //POSITION AND SIZE CONFIGURATION
            void set_pos(Type_pos px,Type_pos py){x=px;y=py;middle_x=(Xsize*bitmap_scale_x/2);middle_y=(Ysize*bitmap_scale_y/2);}
            void set_posx(Type_pos px){x=px;middle_x=(Xsize*bitmap_scale_x/2);}
            void set_posy(Type_pos py){y=py;middle_y=(Ysize*bitmap_scale_y/2);}
            //TEXT CONFIGURATION
            void set_message(std::string message){_message=message;Xsize=_message.size()*_font_size;middle_x=(Xsize*bitmap_scale_x/2);}
            std::string get_message(){return _message;}
            void set_font(LL_Font* font){_font=font;_font_size=_font->get_size();Xsize=_message.size()*_font_size;Ysize=(2*_font_size);middle_x=(Xsize*bitmap_scale_x/2);middle_y=(Ysize*bitmap_scale_y/2);}
            void draw()
            {
                _hear_event();
                if(_is_in() and input->left_click())
                {
                    al_draw_filled_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),C_FilledColor);
                    al_draw_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),C_LineColor,_size*primitives_scale);
                }
                else
                {
                    al_draw_filled_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),U_FilledColor);
                    al_draw_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),U_LineColor,_size*primitives_scale);
                }
                al_draw_text(*_font,TextColor,x+middle_x,y+middle_y-(_font->get_size()*text_scale/2),ALLEGRO_ALIGN_CENTER,_message.c_str());
            }
            operator bool(){return _bool_value;}
            void button_off(){_block=0;}
            void button_on(){_block=1;}
    };

    class LL_TextBox:public LL_Interface
    {
        private:
            unsigned int _text_size=100;
            std::string _data;
            bool _password_type=0;
            bool _active=0;
            bool _in_input=0;
            void _hear_event(){if(_block and input->left_click() and _is_in())_active=1;else if(!_is_in() and input->left_click())_active=0;}
        public:
            LL_TextBox(LL_Input* in)
            {
                input=in;
                TextColor=U_LineColor=C_LineColor=al_map_rgb(0,0,0);
                U_FilledColor=al_map_rgb(255,255,255);
                C_FilledColor=al_map_rgb(187,250,255);
            }
            //POSITION AND SIZE CONFIGURATION
            void set_pos(Type_pos px,Type_pos py){x=px;y=py;}
            void set_posx(Type_pos px){x=px;}
            void set_posy(Type_pos py){y=py;}
            void set_password_type(bool on){_password_type=on;}
            //TEXT CONFIGURATION
            std::string get_value(){return _data;}
            void set_max_text_size(unsigned int siz){clear();Xsize=((1+(_text_size=siz))*((_font->get_size())));}
            void set_font(LL_Font* font){_font=font;Ysize=(2*font->get_size());}
            void clear(){_data.clear();}
            bool set_value(std::string new_data){if(new_data.size()<=_text_size){_data=new_data;return 1;}return 0;}
            void draw()
            {
                _hear_event();
                if(_active)
                {
                    if(!_in_input)
                        _in_input=input->input_on(&_data,_text_size,1);
                    al_draw_filled_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),C_FilledColor);
                    al_draw_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),C_LineColor,_size*primitives_scale);
                }
                else
                {
                    if(_in_input)
                        _in_input=!input->input_off(&_data);
                    al_draw_filled_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),U_FilledColor);
                    al_draw_rectangle(x,y,x+(Xsize*bitmap_scale_x),y+(Ysize*bitmap_scale_y),U_LineColor,_size*primitives_scale);
                }
                if(_password_type)
                {
                    std::string _pass(_data.size(),'*');
                    al_draw_text(*_font,TextColor,x+(_font->get_size()*text_scale),y,ALLEGRO_ALIGN_LEFT,_pass.c_str());
                }
                else
                    al_draw_text(*_font,TextColor,x+(_font->get_size()*text_scale),y,ALLEGRO_ALIGN_LEFT,_data.c_str());
            }
            void textbox_off(){_block=0;input->input_off(&_data);_in_input=0;}
            void textbox_on(){_block=1;}
            operator bool (){return _active;}
            ~LL_TextBox(){if(_in_input)input->input_off(&_data);}
    };
}

#endif // INCLUDED_LL_AL5_INTERFACE_H
