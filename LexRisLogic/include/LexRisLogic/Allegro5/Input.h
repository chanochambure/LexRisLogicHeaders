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
#include <vector>

namespace LL_AL5
{
    bool LL_SHARED input_addon();
    void LL_SHARED uninstall_input();
    std::string LL_SHARED get_keycode_name(int keycode);

    class LL_SHARED Input;

    class LL_SHARED KeyController
    {
        friend class Input;
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
            bool& get_key_status(std::string key_name);
            int get_keycode(std::string key_name);
            void update();
            ~KeyController();
    };

    class LL_SHARED MouseController
    {
        friend class Input;
        private:
            int _V_mouse_x=0;
            int _V_mouse_y=0;
            int _V_mouse_z=0;
            bool _V_mouse_buttons[3]={false,false,false};
            bool _V_mouse_buttons_auxiliar[3]={false,false,false};
        public:
            bool set_mouse_xy(ALLEGRO_DISPLAY* display,int new_mouse_x,int new_mouse_y);
            int get_mouse_x();
            int get_mouse_y();
            bool set_mouse_z(int new_mouse_z);
            int get_mouse_z();
            bool& left_click();
            bool& right_click();
            bool& middle_click();
            void update();
    };

    class LL_SHARED JoyStickController
    {
        friend class Input;
        private:
            struct _S_Structure_Axis
            {
                std::string name;
                float value=0;
            };
            struct _S_Structure_Stick
            {
                std::string name;
                int flag;
                std::vector<_S_Structure_Axis> axes;
            };
            struct _S_Structure_Button
            {
                bool value=false;
                std::string name;
            };
            struct _S_Structure_JoyStick
            {
                ALLEGRO_JOYSTICK* joystick=nullptr;
                float axis_min_value=0.0;
                std::string name;
                std::vector<_S_Structure_Stick> sticks;
                std::vector<_S_Structure_Button> buttons;
            };
            bool _V_auxiliar_button=false;
            float _V_auxiliar_axis=0.0;
            float _V_default_axis_min_value=0.0;
            std::vector<_S_Structure_JoyStick> _V_joystick_data;
            std::map<ALLEGRO_JOYSTICK*,unsigned int> _V_joysticks;
            void _F_init();
        public:
            JoyStickController();
            JoyStickController(const JoyStickController&) = delete;
            bool reconfigure_joysticks();
            bool set_default_axis_min_value(float new_default_axis_min_value);
            float get_default_axis_min_value();
            unsigned int size();
            bool set_axis_min_value(unsigned int joystick_id,float new_axis_min_value);
            float get_axis_min_value(unsigned int joystick_id);
            std::string get_name(unsigned int joystick_id);
            unsigned int get_num_buttons(unsigned int joystick_id);
            bool& get_button_value(unsigned int joystick_id,unsigned int button_id);
            std::string get_button_name(unsigned int joystick_id,unsigned int button_id);
            unsigned int get_num_sticks(unsigned int joystick_id);
            int get_stick_flag(unsigned int joystick_id,unsigned int stick_id);
            std::string get_stick_name(unsigned int joystick_id,unsigned int stick_id);
            unsigned int get_num_axes(unsigned int joystick_id,unsigned int stick_id);
            float& get_axis_value(unsigned int joystick_id,unsigned int stick_id,unsigned int axis_id);
            std::string get_axis_name(unsigned int joystick_id,unsigned int stick_id,unsigned int axis_id);
            void update(unsigned int joystick_id);
            const JoyStickController& operator = (const JoyStickController&) = delete;
    };

    enum InputEventType
    {
        INPUT_EVENT_NONE                    = 0,

        INPUT_EVENT_TIMER                   = 1,

        INPUT_EVENT_DISPLAY_CLOSE           = 11,

        INPUT_EVENT_TEXTLOG_CLOSE           = 21,

        INPUT_EVENT_KEY_CHAR                = 31,
        INPUT_EVENT_KEY_DOWN                = 32,
        INPUT_EVENT_KEY_UP                  = 33,

        INPUT_EVENT_MOUSE_AXES              = 41,
        INPUT_EVENT_MOUSE_BUTTON_DOWN       = 42,
        INPUT_EVENT_MOUSE_BUTTON_UP         = 43,

        INPUT_EVENT_JOYSTICK_CONF           = 51,
        INPUT_EVENT_JOYSTICK_AXIS           = 52,
        INPUT_EVENT_JOYSTICK_BUTTON_DOWN    = 53,
        INPUT_EVENT_JOYSTICK_BUTTON_UP      = 54
    };

    class LL_SHARED InputEvent
    {
        friend class Input;
        private:
            ALLEGRO_EVENT _V_event;
            InputEventType _V_type=INPUT_EVENT_NONE;
        public:
            InputEvent();
            const InputEventType& get_type();
            const ALLEGRO_EVENT& get();
            operator bool ();
    };

    class LL_SHARED Input
    {
        private:
            typedef JoyStickController::_S_Structure_JoyStick _T_Type_joystick;
            bool _V_keyboard_status=false;
            bool _V_mouse_status=false;
            bool _V_joystick_status=false;
            std::string* _V_target_input=nullptr;
            unsigned int _V_max_input_size;
            ALLEGRO_EVENT_QUEUE* _V_event_queue=nullptr;
            KeyController* _V_key_controller=nullptr;
            MouseController* _V_mouse_controller=nullptr;
            JoyStickController* _V_joystick_controller=nullptr;
            bool _V_auxiliar_data=false;
            bool _V_display_exit_status=false;
            bool _V_textlog_exit_status=false;
            float _V_time=0.0;
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
            Input(const Input&) = delete;
            bool create();
            bool destroy();
            bool unregister_timer();
            bool register_timer(ALLEGRO_TIMER* new_timer);
            bool unregister_display();
            bool register_display(ALLEGRO_DISPLAY* new_display);
            bool unregister_textlog();
            bool register_textlog(ALLEGRO_TEXTLOG* new_textlog);
            void set_key_controller(KeyController* new_key_controller);
            KeyController* get_key_controller();
            void set_mouse_controller(MouseController* new_mouse_controller);
            MouseController* get_mouse_controller();
            void set_joystick_controller(JoyStickController* new_mouse_controller);
            JoyStickController* get_joystick_controller();
            void clear_events();
            bool set_wait_time(float wait_time);
            float get_wait_time();
            bool keyboard_on();
            bool keyboard_off();
            bool mouse_on();
            bool mouse_off();
            bool joystick_on();
            bool joystick_off();
            bool input_on(std::string* target_input,unsigned int max_input_size,bool special_is_blocked=false);
            bool input_off(std::string* target_input);
            bool& get_display_status();
            bool& get_textlog_status();
            InputEvent get_event();
            const Input& operator = (const Input&) = delete;
            operator ALLEGRO_EVENT_QUEUE* ();
            ~Input();
    };
}

#endif // INCLUDED_LL_AL5_INPUT_H
