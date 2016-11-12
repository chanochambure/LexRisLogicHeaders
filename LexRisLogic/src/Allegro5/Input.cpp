/* Input.cpp -- Input Allegro 5 Source - LexRis Logic Headers

    Copyright (c) 2016 LexRisLogic

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

#include "../../include/LexRisLogic/Allegro5/Input.h"

namespace LL_AL5
{
    KeyControl::_S_Structure_Key::_S_Structure_Key()
    {
    }
    KeyControl::_S_Structure_Key::_S_Structure_Key(int new_keycode)
    {
        keycode=new_keycode;
    }
    bool KeyControl::add_key(std::string key_name,int keycode)
    {
        if(find_key(key_name) or find_key(keycode))
            return false;
        _V_keys.insert(std::pair<std::string,_S_Structure_Key>(key_name,_S_Structure_Key(keycode)));
        return true;
    }
    bool KeyControl::find_key(std::string key_name)
    {
        return _V_keys.find(key_name)!=_V_keys.end();
    }
    bool KeyControl::find_key(int keycode,std::string* key_name)
    {
        for(std::map<std::string,_S_Structure_Key>::iterator i=_V_keys.begin();i!=_V_keys.end();++i)
        {
            if((*i).second.keycode==keycode)
            {
                if(key_name)
                    (*key_name)=(*i).first;
                return true;
            }
        }
        return false;
    }
    bool KeyControl::mod_key(std::string last_key_name,std::string new_key_name)
    {
        if(find_key(last_key_name) and !find_key(new_key_name))
        {
            _V_keys[new_key_name]=_V_keys[last_key_name];
            _V_keys.erase(last_key_name);
            return true;
        }
        return false;
    }
    bool KeyControl::mod_key(std::string key_name,int new_keycode)
    {
        if(find_key(key_name) and !find_key(new_keycode))
        {
            _V_keys[key_name].keycode=new_keycode;
            return true;
        }
        return false;
    }
    bool KeyControl::remove_key(std::string key_name)
    {
        if(find_key(key_name))
        {
            _V_keys.erase(key_name);
            return true;
        }
        return false;
    }
    bool KeyControl::remove_key(int keycode)
    {
        std::string key_name;
        if(find_key(keycode,&key_name))
        {
            _V_keys.erase(key_name);
            return true;
        }
        return false;
    }
    unsigned int KeyControl::size()
    {
        return _V_keys.size();
    }
    void KeyControl::clear_key_status()
    {
        for(std::map<std::string,_S_Structure_Key>::iterator i=_V_keys.begin();i!=_V_keys.end();++i)
            (*i).second.key_down=false;
    }
    void KeyControl::clear()
    {
        _V_keys.clear();
    }
    bool& KeyControl::get_key_down_status(std::string key_name)
    {
        _V_auxiliar_key=false;
        if(find_key(key_name))
            return _V_keys[key_name].key_down;
        return _V_auxiliar_key;
    }
    int KeyControl::get_keycode(std::string key_name)
    {
        if(find_key(key_name))
            return _V_keys[key_name].keycode;
        return -1;
    }
    KeyControl::~KeyControl()
    {
        _V_keys.clear();
    }

    bool Input::_F_find_key(std::string key_name)
    {
        if(_V_key_control)
            return _V_key_control->find_key(key_name);
        return false;
    }
    bool Input::_F_find_key(int keycode,std::string* key_name)
    {
        if(_V_key_control)
            return _V_key_control->find_key(keycode,key_name);
        return false;
    }
    Input::Input()
    {
        al_install_keyboard();
        al_install_mouse();
        _V_event_queue=al_create_event_queue();
    }
    bool Input::unregister_timer()
    {
        if(_V_timer_registered)
        {
            al_unregister_event_source(_V_event_queue,al_get_timer_event_source(_V_timer));
            _V_timer_registered=false;
            _V_timer=nullptr;
            return true;
        }
        return false;
    }
    bool Input::register_timer(ALLEGRO_TIMER* new_timer)
    {
        if(!_V_timer_registered)
        {
            _V_timer=new_timer;
            al_register_event_source(_V_event_queue,al_get_timer_event_source(_V_timer));
            _V_timer_registered=true;
            return true;
        }
        return false;
    }
    bool Input::unregister_display()
    {
        if(_V_display_registered)
        {
            al_unregister_event_source(_V_event_queue,al_get_display_event_source(_V_display));
            _V_display_registered=false;
            _V_display=nullptr;
            return true;
        }
        return false;
    }
    bool Input::register_display(ALLEGRO_DISPLAY* new_display)
    {
        if(!_V_display_registered)
        {
            _V_display=new_display;
            al_register_event_source(_V_event_queue,al_get_display_event_source(_V_display));
            _V_display_registered=true;
            return true;
        }
        return false;
    }
    bool Input::unregister_textlog()
    {
        if(_V_textlog_registered)
        {
            al_unregister_event_source(_V_event_queue,al_get_native_text_log_event_source(_V_textlog));
            _V_textlog_registered=false;
            _V_textlog=nullptr;
            return true;
        }
        return false;
    }
    bool Input::register_textlog(ALLEGRO_TEXTLOG* new_textlog)
    {
        if(!_V_textlog_registered)
        {
            _V_textlog=new_textlog;
            al_register_event_source(_V_event_queue,al_get_native_text_log_event_source(_V_textlog));
            _V_textlog_registered=true;
            return true;
        }
        return false;
    }
    void Input::set_key_control(KeyControl* new_key_control)
    {
        _V_key_control=new_key_control;
    }
    KeyControl* Input::get_key_control()
    {
        return _V_key_control;
    }
    void Input::clear_events()
    {
        al_flush_event_queue(_V_event_queue);
    }
    void Input::clear_key_status()
    {
        if(_V_key_control)
            _V_key_control->clear_key_status();
    }
    bool Input::set_wait_time(float wait_time)
    {
        if(wait_time<0)
            return false;
        _V_time=wait_time;
        return true;
    }
    float Input::get_wait_time()
    {
        return _V_time;
    }
    bool Input::keyboard_on()
    {
        if(!_V_keyboard_status)
        {
            al_register_event_source(_V_event_queue,al_get_keyboard_event_source());
            _V_keyboard_status=true;
            return true;
        }
        return false;
    }
    bool Input::keyboard_off()
    {
        if(_V_keyboard_status)
        {
            al_unregister_event_source(_V_event_queue,al_get_keyboard_event_source());
            _V_keyboard_status=false;
            return true;
        }
        return false;
    }
    bool Input::input_on(std::string* input_objetive,unsigned int max_input_size,bool special_is_blocked)
    {
        if(_V_keyboard_status and !_V_input_activated and max_input_size>0)
        {
            _V_char_lock=special_is_blocked;
            _V_input_objetive=input_objetive;
            _V_max_input_size=max_input_size;
            if(_V_input_objetive->size()>_V_max_input_size)
                (*_V_input_objetive)=_V_input_objetive->substr(0,_V_max_input_size);
            _V_input_activated=true;
            return true;
        }
        return false;
    }
    bool Input::input_off(std::string* input_objetive)
    {
        if(_V_input_activated and _V_input_objetive and input_objetive==_V_input_objetive)
        {
            _V_input_activated=false;
            _V_input_objetive=nullptr;
            return true;
        }
        return false;
    }
    bool Input::mouse_on(bool event_type)
    {
        if(!_V_mouse_status)
        {
            _V_mouse_event_type=event_type;
            if(_V_mouse_event_type)
                al_register_event_source(_V_event_queue,al_get_mouse_event_source());
            _V_mouse_status=true;
            return true;
        }
        return false;
    }
    bool Input::mouse_off()
    {
        if(_V_mouse_status)
        {
            if(_V_mouse_event_type)
            {
                al_unregister_event_source(_V_event_queue,al_get_mouse_event_source());
                _V_mouse_event_type=false;
            }
            _V_mouse_status=false;
            return true;
        }
        return false;
    }
    bool Input::set_mouse_xy(int new_mouse_x,int new_mouse_y)
    {
        if(_V_display_registered and al_set_mouse_xy(_V_display,new_mouse_x,new_mouse_y))
        {
            _V_mouse_x=new_mouse_x;
            _V_mouse_y=new_mouse_y;
            return true;
        }
        return false;
    }
    int Input::get_mouse_x()
    {
        return _V_mouse_x;
    }
    int Input::get_mouse_y()
    {
        return _V_mouse_y;
    }
    bool Input::set_mouse_z(int new_mouse_z)
    {
        if(al_set_mouse_z(new_mouse_z))
        {
            _V_mouse_z=new_mouse_z;
            return true;
        }
        return false;
    }
    int Input::get_mouse_z()
    {
        return _V_mouse_z;
    }
    bool& Input::left_click()
    {
        return (_V_mouse_buttons[0]);
    }
    bool& Input::right_click()
    {
        return (_V_mouse_buttons[1]);
    }
    bool& Input::middle_click()
    {
        return (_V_mouse_buttons[2]);
    }
    bool Input::get_timer_event()
    {
        return _V_timer_event;
    }
    bool& Input::get_display_status()
    {
        return _V_display_exit_status;
    }
    bool& Input::get_textlog_status()
    {
        return _V_textlog_exit_status;
    }
    bool Input::get_event()
    {
        ALLEGRO_EVENT event;
        if(al_wait_for_event_timed(_V_event_queue,&event,_V_time))
        {
            if(_V_timer_registered)
            {
                if(event.type==ALLEGRO_EVENT_TIMER)
                {
                    _V_timer_event=true;
                    return true;
                }
                else
                    _V_timer_event=false;
            }
            if(_V_display_registered)
            {
                if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
                {
                    _V_display_exit_status=true;
                    return true;
                }
            }
            if(_V_textlog_registered)
            {
                if(event.type==ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE)
                {
                    _V_textlog_exit_status=true;
                    return true;
                }
            }
            if(_V_keyboard_status)
            {
                if(_V_input_activated and event.type==ALLEGRO_EVENT_KEY_CHAR)
                {
                    if(event.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
                        (*_V_input_objetive)=_V_input_objetive->substr(0,_V_input_objetive->size()-1);
                    else if(_V_input_objetive->size()<_V_max_input_size)
                    {
                        if(event.keyboard.keycode==ALLEGRO_KEY_ENTER)
                        {
                            if(!_V_char_lock)
                                (*_V_input_objetive)=(*_V_input_objetive)+'\n';
                        }
                        else if(event.keyboard.keycode==ALLEGRO_KEY_TAB)
                        {
                            if(!_V_char_lock)
                                (*_V_input_objetive)=(*_V_input_objetive)+'\t';
                        }
                        else if(event.keyboard.unichar>=32 and event.keyboard.keycode!=77)
                            (*_V_input_objetive)=(*_V_input_objetive)+char(event.keyboard.unichar);
                    }
                }
                else if(event.type==ALLEGRO_EVENT_KEY_DOWN)
                {
                    std::string key_name;
                    if(_F_find_key(event.keyboard.keycode,&key_name))
                        _V_key_control->get_key_down_status(key_name)=true;
                    return true;
                }
                else if(event.type==ALLEGRO_EVENT_KEY_UP)
                {
                    std::string key_name;
                    if(_F_find_key(event.keyboard.keycode,&key_name))
                        _V_key_control->get_key_down_status(key_name)=false;
                    return true;
                }
            }
            if(_V_mouse_status)
            {
                if(_V_mouse_event_type)
                {
                    if(event.type==ALLEGRO_EVENT_MOUSE_AXES)
                    {
                        _V_mouse_x=event.mouse.x;
                        _V_mouse_y=event.mouse.y;
                        _V_mouse_z=event.mouse.z;
                        return true;
                    }
                    else if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    {
                        _V_mouse_buttons[event.mouse.button-1]=true;
                        return true;
                    }
                    else if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    {
                        _V_mouse_buttons[event.mouse.button-1]=false;
                        return true;
                    }
                }
                else
                {
                    ALLEGRO_MOUSE_STATE mouse_state;
                    al_get_mouse_state(&mouse_state);
                    for(unsigned int i=0;i<3;++i)
                    {
                        bool actual_state=(mouse_state.buttons & 1<<i);
                        if(_V_mouse_buttons_auxiliar[i]==_V_mouse_buttons[i])
                            _V_mouse_buttons_auxiliar[i]=_V_mouse_buttons[i]=actual_state;
                        else
                        {
                            if(_V_mouse_buttons[i]==actual_state)
                                _V_mouse_buttons_auxiliar[i]=actual_state;
                        }
                    }
                    _V_mouse_x=mouse_state.x;
                    _V_mouse_y=mouse_state.y;
                    _V_mouse_z=mouse_state.z;
                }
            }
            return true;
        }
        _V_timer_event=false;
        return false;
    }
    int Input::get_keycode()
    {
        if(_V_event_queue and _V_display_registered and _V_keyboard_status)
        {
            clear_events();
            while(true)
            {
                ALLEGRO_EVENT event;
                al_wait_for_event(_V_event_queue,&event);
                if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
                {
                    _V_display_exit_status=true;
                    break;
                }
                if(event.type==ALLEGRO_EVENT_KEY_DOWN)
                    return event.keyboard.keycode;
            }
        }
        return -1;
    }
    bool& Input::operator [](std::string key_name)
    {
        _V_auxiliar_key=false;
        if(_V_key_control)
            return _V_key_control->get_key_down_status(key_name);
        return _V_auxiliar_key;
    }
    Input::operator ALLEGRO_EVENT_QUEUE* ()
    {
        return _V_event_queue;
    }
    Input::~Input()
    {
        unregister_timer();
        unregister_display();
        unregister_textlog();
        keyboard_off();
        mouse_off();
        if(_V_event_queue)
        {
            al_destroy_event_queue(_V_event_queue);
            _V_event_queue=nullptr;
        }
        al_uninstall_keyboard();
        al_uninstall_mouse();
    }
}
