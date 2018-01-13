/* Input.h -- Input Allegro 5 Header - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so.

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of
    the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef INCLUDED_LL_AL5_INPUT_H
#define INCLUDED_LL_AL5_INPUT_H

#include "../LL_Shared.h"

#include "Allegro5.h"

#include <allegro5/allegro_native_dialog.h>
#include <map>
#include <string>

namespace LL_AL5
{
    class LL_SHARED KeyControl
    {
        private:
            struct _S_Structure_Key
            {
                int keycode=-1;
                bool key_down=false;
                _S_Structure_Key();
                _S_Structure_Key(int new_keycode);
            };
            bool _V_auxiliar_key=false;
            std::map<std::string,_S_Structure_Key> _V_keys;
        public:
            bool add_key(std::string key_name,int keycode);
            bool find_key(std::string key_name);
            bool find_key(int keycode,std::string* key_name=nullptr);
            bool mod_key(std::string last_key_name,std::string new_key_name);
            bool mod_key(std::string key_name,int new_keycode);
            bool remove_key(std::string key_name);
            bool remove_key(int keycode);
            unsigned int size();
            void clear_key_status();
            void clear();
            bool& get_key_down_status(std::string key_name);
            int get_keycode(std::string key_name);
            ~KeyControl();
    };

    class LL_SHARED Input
    {
        private:
            bool _V_keyboard_status=false;
            bool _V_mouse_status=false;
            bool _V_mouse_event_type=false;
            std::string* _V_input_objetive=nullptr;
            unsigned int _V_max_input_size;
            ALLEGRO_EVENT_QUEUE* _V_event_queue;
            KeyControl* _V_key_control=nullptr;
            bool _V_auxiliar_key=false;
            bool _V_display_exit_status=false;
            bool _V_textlog_exit_status=false;
            float _V_time=0.0;
            bool _V_timer_event=false;
            int _V_mouse_x=0;
            int _V_mouse_y=0;
            int _V_mouse_z=0;
            bool _V_mouse_buttons[3]={false,false,false};
            bool _V_mouse_buttons_auxiliar[3]={false,false,false};
            bool _V_input_activated=false;
            ALLEGRO_DISPLAY* _V_display=nullptr;
            ALLEGRO_TEXTLOG* _V_textlog=nullptr;
            ALLEGRO_TIMER* _V_timer=nullptr;
            bool _V_timer_registered=false;
            bool _V_display_registered=false;
            bool _V_textlog_registered=false;
            bool _V_char_lock=false;
            bool _F_find_key(std::string key_name);
            bool _F_find_key(int keycode,std::string* key_name=nullptr);
        public:
            Input();
            bool unregister_timer();
            bool register_timer(ALLEGRO_TIMER* new_timer);
            bool unregister_display();
            bool register_display(ALLEGRO_DISPLAY* new_display);
            bool unregister_textlog();
            bool register_textlog(ALLEGRO_TEXTLOG* new_textlog);
            void set_key_control(KeyControl* new_key_control);
            KeyControl* get_key_control();
            void clear_events();
            void clear_key_status();
            bool set_wait_time(float wait_time);
            float get_wait_time();
            bool keyboard_on();
            bool keyboard_off();
            bool input_on(std::string* input_objetive,unsigned int max_input_size,bool special_is_blocked=false);
            bool input_off(std::string* input_objetive);
            bool mouse_on(bool event_type=false);
            bool mouse_off();
            bool set_mouse_xy(int new_mouse_x,int new_mouse_y);
            int get_mouse_x();
            int get_mouse_y();
            bool set_mouse_z(int new_mouse_z);
            int get_mouse_z();
            bool& left_click();
            bool& right_click();
            bool& middle_click();
            bool get_timer_event();
            bool& get_display_status();
            bool& get_textlog_status();
            bool get_event();
            int get_keycode();
            bool& operator [](std::string key_name);
            operator ALLEGRO_EVENT_QUEUE* ();
            ~Input();
    };
}

#endif // INCLUDED_LL_AL5_INPUT_H
