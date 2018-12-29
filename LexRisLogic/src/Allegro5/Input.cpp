/* Input.cpp -- Input Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/Input.h"

namespace LL_AL5
{
    bool LL_SHARED input_addon()
    {
        return al_install_keyboard() && al_install_mouse() && al_install_joystick();
    }
    void LL_SHARED uninstall_input()
    {
        al_uninstall_joystick();
        al_uninstall_keyboard();
        al_uninstall_mouse();
    }
    std::string LL_SHARED get_keycode_name(int keycode)
    {
        return al_keycode_to_name(keycode);
    }

    KeyController::_S_Structure_Key::_S_Structure_Key()
    {
    }
    KeyController::_S_Structure_Key::_S_Structure_Key(int new_keycode)
    {
        keycode=new_keycode;
    }
    bool KeyController::add_key(std::string key_name,int keycode)
    {
        if(find_key(key_name) || find_key(keycode))
            return false;
        _V_keys.insert(std::pair<std::string,_S_Structure_Key>(key_name,_S_Structure_Key(keycode)));
        return true;
    }
    bool KeyController::find_key(std::string key_name)
    {
        return _V_keys.find(key_name)!=_V_keys.end();
    }
    bool KeyController::find_key(int keycode,std::string* key_name)
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
    bool KeyController::mod_key(std::string last_key_name,std::string new_key_name)
    {
        if(find_key(last_key_name) && !find_key(new_key_name))
        {
            _V_keys[new_key_name]=_V_keys[last_key_name];
            _V_keys.erase(last_key_name);
            return true;
        }
        return false;
    }
    bool KeyController::mod_key(std::string key_name,int new_keycode)
    {
        if(find_key(key_name) && !find_key(new_keycode))
        {
            _V_keys[key_name].keycode=new_keycode;
            return true;
        }
        return false;
    }
    bool KeyController::remove_key(std::string key_name)
    {
        if(find_key(key_name))
        {
            _V_keys.erase(key_name);
            return true;
        }
        return false;
    }
    bool KeyController::remove_key(int keycode)
    {
        std::string key_name;
        if(find_key(keycode,&key_name))
        {
            _V_keys.erase(key_name);
            return true;
        }
        return false;
    }
    unsigned int KeyController::size()
    {
        return _V_keys.size();
    }
    void KeyController::clear()
    {
        _V_keys.clear();
    }
    bool& KeyController::get_key_status(std::string key_name)
    {
        _V_auxiliar_key=false;
        if(find_key(key_name))
            return _V_keys[key_name].key_down;
        return _V_auxiliar_key;
    }
    int KeyController::get_keycode(std::string key_name)
    {
        if(find_key(key_name))
            return _V_keys[key_name].keycode;
        return -1;
    }
    void KeyController::update()
    {
        ALLEGRO_KEYBOARD_STATE keyboard_state;
        al_get_keyboard_state(&keyboard_state);
        for(auto i=_V_keys.begin();i!=_V_keys.end();++i)
            i->second.key_down=al_key_down(&keyboard_state,i->second.keycode);
    }
    void KeyController::clear_key_status()
    {
        for(auto i=_V_keys.begin();i!=_V_keys.end();++i)
            i->second.key_down=false;
    }
    KeyController::~KeyController()
    {
        _V_keys.clear();
    }

    bool MouseController::set_mouse_xy(ALLEGRO_DISPLAY* display,int new_mouse_x,int new_mouse_y)
    {
        if(al_set_mouse_xy(display,new_mouse_x,new_mouse_y))
        {
            _V_mouse_x=new_mouse_x;
            _V_mouse_y=new_mouse_y;
            return true;
        }
        return false;
    }
    int MouseController::get_mouse_x()
    {
        return _V_mouse_x;
    }
    int MouseController::get_mouse_y()
    {
        return _V_mouse_y;
    }
    bool MouseController::set_mouse_z(int new_mouse_z)
    {
        if(al_set_mouse_z(new_mouse_z))
        {
            _V_mouse_z=new_mouse_z;
            return true;
        }
        return false;
    }
    int MouseController::get_mouse_z()
    {
        return _V_mouse_z;
    }
    bool& MouseController::left_click()
    {
        return (_V_mouse_buttons[0]);
    }
    bool& MouseController::right_click()
    {
        return (_V_mouse_buttons[1]);
    }
    bool& MouseController::middle_click()
    {
        return (_V_mouse_buttons[2]);
    }
    void MouseController::clear_mouse_status()
    {
        _V_mouse_x=0;
        _V_mouse_y=0;
        _V_mouse_z=0;
        _V_mouse_buttons[0]=_V_mouse_buttons[1]=_V_mouse_buttons[2]=false;
        _V_mouse_buttons_auxiliar[0]=_V_mouse_buttons_auxiliar[1]=_V_mouse_buttons_auxiliar[2]=false;
    }
    void MouseController::update()
    {
        ALLEGRO_MOUSE_STATE mouse_state;
        al_get_mouse_state(&mouse_state);
        for(unsigned int i=0;i<3;++i)
        {
            bool current_state=(mouse_state.buttons & 1<<i);
            if(_V_mouse_buttons_auxiliar[i]==_V_mouse_buttons[i])
                _V_mouse_buttons_auxiliar[i]=_V_mouse_buttons[i]=current_state;
            else
            {
                if(_V_mouse_buttons[i]==current_state)
                    _V_mouse_buttons_auxiliar[i]=current_state;
            }
        }
        _V_mouse_x=mouse_state.x;
        _V_mouse_y=mouse_state.y;
        _V_mouse_z=mouse_state.z;
    }

    void JoyStickController::_F_init()
    {
        std::map<ALLEGRO_JOYSTICK*,float> last_configuration;
        for(unsigned int i=0;i<_V_joystick_data.size();++i)
            last_configuration[_V_joystick_data[i].joystick]=_V_joystick_data[i].axis_min_value;
        _V_joysticks.clear();
        _V_joystick_data.clear();
        int joysticks=al_get_num_joysticks();
        for(int i=0;i<joysticks;++i)
        {
            _S_Structure_JoyStick new_joystick;
            new_joystick.joystick=al_get_joystick(i);
            new_joystick.name=al_get_joystick_name(new_joystick.joystick);
            new_joystick.axis_min_value=_V_default_axis_min_value;
            int sticks=al_get_joystick_num_sticks(new_joystick.joystick);
            for(int j=0;j<sticks;++j)
            {
                _S_Structure_Stick new_stick;
                new_stick.name=al_get_joystick_stick_name(new_joystick.joystick,j);
                new_stick.flag=al_get_joystick_stick_flags(new_joystick.joystick,j);
                int axes=al_get_joystick_num_axes(new_joystick.joystick,j);
                for(int k=0;k<axes;++k)
                {
                    _S_Structure_Axis new_axis;
                    new_axis.name=al_get_joystick_axis_name(new_joystick.joystick,j,k);
                    new_stick.axes.push_back(new_axis);
                }
                new_joystick.sticks.push_back(new_stick);
            }
            int buttons=al_get_joystick_num_buttons(new_joystick.joystick);
            for(int j=0;j<buttons;++j)
            {
                _S_Structure_Button new_button;
                new_button.name=al_get_joystick_button_name(new_joystick.joystick,j);
                new_joystick.buttons.push_back(new_button);
            }
            auto iter=last_configuration.find(new_joystick.joystick);
            if(iter!=last_configuration.end())
                new_joystick.axis_min_value=iter->second;
            _V_joystick_data.push_back(new_joystick);
            _V_joysticks[new_joystick.joystick]=i;
        }
    }
    JoyStickController::JoyStickController()
    {
        _F_init();
    }
    bool JoyStickController::reconfigure_joysticks()
    {
        if(al_reconfigure_joysticks())
        {
            _F_init();
            return true;
        }
        return false;
    }
    bool JoyStickController::set_default_axis_min_value(float new_default_axis_min_value)
    {
        if(new_default_axis_min_value>=0.0 && new_default_axis_min_value<=1.0)
        {
            _V_default_axis_min_value=new_default_axis_min_value;
            return true;
        }
        return false;
    }
    float JoyStickController::get_default_axis_min_value()
    {
        return _V_default_axis_min_value;
    }
    unsigned int JoyStickController::size()
    {
        return _V_joystick_data.size();
    }
    bool JoyStickController::set_axis_min_value(unsigned int joystick_id,float new_axis_min_value)
    {
        if(joystick_id<_V_joystick_data.size() && new_axis_min_value>=0.0 && new_axis_min_value<=1.0)
        {
            _V_joystick_data[joystick_id].axis_min_value=new_axis_min_value;
            return true;
        }
        return false;
    }
    float JoyStickController::get_axis_min_value(unsigned int joystick_id)
    {
        if(joystick_id<_V_joystick_data.size())
            return _V_joystick_data[joystick_id].axis_min_value;
        return 0.0;
    }
    std::string JoyStickController::get_name(unsigned int joystick_id)
    {
        if(joystick_id<_V_joystick_data.size())
            return _V_joystick_data[joystick_id].name;
        return "";
    }
    unsigned int JoyStickController::get_num_buttons(unsigned int joystick_id)
    {
        if(joystick_id<_V_joystick_data.size())
            return _V_joystick_data[joystick_id].buttons.size();
        return 0;
    }
    bool& JoyStickController::get_button_value(unsigned int joystick_id,unsigned int button_id)
    {
        _V_auxiliar_button=false;
        if(button_id<get_num_buttons(joystick_id))
            return _V_joystick_data[joystick_id].buttons[button_id].value;
        return _V_auxiliar_button;
    }
    std::string JoyStickController::get_button_name(unsigned int joystick_id,unsigned int button_id)
    {
        if(button_id<get_num_buttons(joystick_id))
            return _V_joystick_data[joystick_id].buttons[button_id].name;
        return "";
    }
    unsigned int JoyStickController::get_num_sticks(unsigned int joystick_id)
    {
        if(joystick_id<_V_joystick_data.size())
            return _V_joystick_data[joystick_id].sticks.size();
        return 0;
    }
    int JoyStickController::get_stick_flag(unsigned int joystick_id,unsigned int stick_id)
    {
        if(stick_id<get_num_sticks(joystick_id))
            return _V_joystick_data[joystick_id].sticks[stick_id].flag;
        return 0;
    }
    std::string JoyStickController::get_stick_name(unsigned int joystick_id,unsigned int stick_id)
    {
        if(stick_id<get_num_sticks(joystick_id))
            return _V_joystick_data[joystick_id].sticks[stick_id].name;
        return 0;
    }
    unsigned int JoyStickController::get_num_axes(unsigned int joystick_id,unsigned int stick_id)
    {
        if(stick_id<get_num_sticks(joystick_id))
            return _V_joystick_data[joystick_id].sticks[stick_id].axes.size();
        return 0;
    }
    float& JoyStickController::get_axis_value(unsigned int joystick_id,unsigned int stick_id,unsigned int axis_id)
    {
        _V_auxiliar_axis=false;
        if(axis_id<get_num_axes(joystick_id,stick_id))
        {
            float& return_value=_V_joystick_data[joystick_id].sticks[stick_id].axes[axis_id].value;
            if((return_value<0 && -return_value<_V_joystick_data[joystick_id].axis_min_value) ||
               (return_value>0 && return_value<_V_joystick_data[joystick_id].axis_min_value))
                return_value=0.0;
            return return_value;
        }
        return _V_auxiliar_axis;
    }
    std::string JoyStickController::get_axis_name(unsigned int joystick_id,unsigned int stick_id,unsigned int axis_id)
    {
        if(axis_id<get_num_axes(joystick_id,stick_id))
            return _V_joystick_data[joystick_id].sticks[stick_id].axes[axis_id].name;
        return "";
    }
    void JoyStickController::clear_joystick_status()
    {
        for(unsigned int id=0;id<_V_joystick_data.size();++id)
        {
            for(unsigned int i=0;i<_V_joystick_data[id].sticks.size();++i)
            {
                for(unsigned int j=0;j<_V_joystick_data[id].sticks[i].axes.size();++j)
                    _V_joystick_data[id].sticks[i].axes[j].value=0.0;
            }
            for(unsigned int i=0;i<_V_joystick_data[id].buttons.size();++i)
                _V_joystick_data[id].buttons[i].value=false;
        }
    }
    void JoyStickController::update(unsigned int joystick_id)
    {
        if(joystick_id<_V_joystick_data.size())
        {
            ALLEGRO_JOYSTICK_STATE joystick_state;
            al_get_joystick_state(_V_joystick_data[joystick_id].joystick,&joystick_state);
            for(unsigned int i=0;i<_V_joystick_data[joystick_id].sticks.size();++i)
            {
                for(unsigned int j=0;j<_V_joystick_data[joystick_id].sticks[i].axes.size();++j)
                    _V_joystick_data[joystick_id].sticks[i].axes[j].value=joystick_state.stick[i].axis[j];
            }
            for(unsigned int i=0;i<_V_joystick_data[joystick_id].buttons.size();++i)
                _V_joystick_data[joystick_id].buttons[i].value=joystick_state.button[i];
        }
    }

    InputEvent::InputEvent()
    {
    }
    const InputEventType& InputEvent::get_type()
    {
        return _V_type;
    }
    InputEvent::operator bool ()
    {
        return _V_type!=InputEventType::INPUT_EVENT_NONE;
    }
    const ALLEGRO_EVENT& InputEvent::get()
    {
        return _V_event;
    }

    bool Input::_F_find_key(std::string key_name)
    {
        if(_V_key_controller)
            return _V_key_controller->find_key(key_name);
        return false;
    }
    bool Input::_F_find_key(int keycode,std::string* key_name)
    {
        if(_V_key_controller)
            return _V_key_controller->find_key(keycode,key_name);
        return false;
    }
    Input::Input()
    {
    }
    bool Input::create()
    {
        if(!_V_event_queue)
            return (_V_event_queue=al_create_event_queue());
        return false;
    }
    bool Input::destroy()
    {
        if(_V_event_queue)
        {
            unregister_timer();
            unregister_display();
            unregister_textlog();
            joystick_off();
            keyboard_off();
            mouse_off();
            al_destroy_event_queue(_V_event_queue);
            _V_event_queue=nullptr;
        }
        return false;
    }
    bool Input::unregister_timer()
    {
        if(_V_event_queue && _V_timer_registered)
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
        if(_V_event_queue && !_V_timer_registered)
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
        if(_V_event_queue && _V_display_registered)
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
        if(_V_event_queue && !_V_display_registered)
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
        if(_V_event_queue && _V_textlog_registered)
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
        if(_V_event_queue && !_V_textlog_registered)
        {
            _V_textlog=new_textlog;
            al_register_event_source(_V_event_queue,al_get_native_text_log_event_source(_V_textlog));
            _V_textlog_registered=true;
            return true;
        }
        return false;
    }
    void Input::set_key_controller(KeyController* new_key_controller)
    {
        _V_key_controller=new_key_controller;
    }
    KeyController* Input::get_key_controller()
    {
        return _V_key_controller;
    }
    void Input::set_mouse_controller(MouseController* new_mouse_controller)
    {
        _V_mouse_controller=new_mouse_controller;
    }
    MouseController* Input::get_mouse_controller()
    {
        return _V_mouse_controller;
    }
    void Input::set_joystick_controller(JoyStickController* new_joystick_controller)
    {
        _V_joystick_controller=new_joystick_controller;
        new_joystick_controller->_F_init();
    }
    JoyStickController* Input::get_joystick_controller()
    {
        return _V_joystick_controller;
    }
    void Input::clear_events()
    {
        if(_V_event_queue)
            al_flush_event_queue(_V_event_queue);
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
        if(_V_event_queue && !_V_keyboard_status)
        {
            al_register_event_source(_V_event_queue,al_get_keyboard_event_source());
            _V_keyboard_status=true;
            return true;
        }
        return false;
    }
    bool Input::keyboard_off()
    {
        if(_V_event_queue && _V_keyboard_status)
        {
            input_off(_V_target_input);
            al_unregister_event_source(_V_event_queue,al_get_keyboard_event_source());
            _V_keyboard_status=false;
            return true;
        }
        return false;
    }
    bool Input::input_on(std::string* target_input,unsigned int max_input_size,bool special_is_blocked)
    {
        if(_V_keyboard_status && !_V_input_activated && target_input && max_input_size>0)
        {
            _V_char_lock=special_is_blocked;
            _V_target_input=target_input;
            _V_max_input_size=max_input_size;
            if(_V_target_input->size()>_V_max_input_size)
                (*_V_target_input)=_V_target_input->substr(0,_V_max_input_size);
            _V_input_activated=true;
            return true;
        }
        return false;
    }
    bool Input::input_off(std::string* target_input)
    {
        if(_V_input_activated && _V_target_input && target_input==_V_target_input)
        {
            _V_input_activated=false;
            _V_target_input=nullptr;
            return true;
        }
        return false;
    }
    bool Input::mouse_on()
    {
        if(_V_event_queue && !_V_mouse_status)
        {
            al_register_event_source(_V_event_queue,al_get_mouse_event_source());
            _V_mouse_status=true;
            return true;
        }
        return false;
    }
    bool Input::mouse_off()
    {
        if(_V_event_queue && _V_mouse_status)
        {
            al_unregister_event_source(_V_event_queue,al_get_mouse_event_source());
            _V_mouse_status=false;
            return true;
        }
        return false;
    }
    bool Input::joystick_on()
    {
        if(_V_event_queue && !_V_joystick_status)
        {
            al_register_event_source(_V_event_queue,al_get_joystick_event_source());
            _V_joystick_status=true;
            return true;
        }
        return false;
    }
    bool Input::joystick_off()
    {
        if(_V_event_queue && _V_joystick_status)
        {
            al_unregister_event_source(_V_event_queue,al_get_joystick_event_source());
            _V_joystick_status=false;
            return true;
        }
        return false;
    }
    bool& Input::get_display_status()
    {
        return _V_display_exit_status;
    }
    bool& Input::get_textlog_status()
    {
        return _V_textlog_exit_status;
    }
    InputEvent Input::get_event()
    {
        InputEvent event;
        if(_V_event_queue)
        {
            if(al_wait_for_event_timed(_V_event_queue,&event._V_event,_V_time))
            {
                switch(event._V_event.type)
                {
                    case ALLEGRO_EVENT_TIMER:
                    {
                        if(_V_timer_registered)
                            event._V_type=InputEventType::INPUT_EVENT_TIMER;
                        break;
                    }
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    {
                        if(_V_display_registered)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_DISPLAY_CLOSE;
                            _V_display_exit_status=true;
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE:
                    {
                        if(_V_textlog_registered)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_TEXTLOG_CLOSE;
                            _V_textlog_exit_status=true;
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_KEY_CHAR:
                    {
                        if(_V_input_activated)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_KEY_CHAR;
                            if(event._V_event.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
                                (*_V_target_input)=_V_target_input->substr(0,_V_target_input->size()-1);
                            else if(_V_target_input->size()<_V_max_input_size)
                            {
                                if(event._V_event.keyboard.keycode==ALLEGRO_KEY_ENTER)
                                {
                                    if(!_V_char_lock)
                                        (*_V_target_input)=(*_V_target_input)+'\n';
                                }
                                else if(event._V_event.keyboard.keycode==ALLEGRO_KEY_TAB)
                                {
                                    if(!_V_char_lock)
                                        (*_V_target_input)=(*_V_target_input)+'\t';
                                }
                                else if(event._V_event.keyboard.unichar>=32 && event._V_event.keyboard.keycode!=77)
                                    (*_V_target_input)=(*_V_target_input)+char(event._V_event.keyboard.unichar);
                            }
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_KEY_DOWN:
                    {
                        if(_V_keyboard_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_KEY_DOWN;
                            if(_V_key_controller)
                            {
                                std::string key_name;
                                if(_F_find_key(event._V_event.keyboard.keycode,&key_name))
                                    _V_key_controller->get_key_status(key_name)=true;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_KEY_UP:
                    {
                        if(_V_keyboard_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_KEY_UP;
                            if(_V_key_controller)
                            {
                                std::string key_name;
                                if(_F_find_key(event._V_event.keyboard.keycode,&key_name))
                                    _V_key_controller->get_key_status(key_name)=false;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_MOUSE_AXES:
                    {
                        if(_V_mouse_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_MOUSE_AXES;
                            if(_V_mouse_controller)
                            {
                                _V_mouse_controller->_V_mouse_x=event._V_event.mouse.x;
                                _V_mouse_controller->_V_mouse_y=event._V_event.mouse.y;
                                _V_mouse_controller->_V_mouse_z=event._V_event.mouse.z;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    {
                        if(_V_mouse_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_MOUSE_BUTTON_DOWN;
                            if(_V_mouse_controller)
                                _V_mouse_controller->_V_mouse_buttons[event._V_event.mouse.button-1]=true;
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                    {
                        if(_V_mouse_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_MOUSE_BUTTON_UP;
                            if(_V_mouse_controller)
                                _V_mouse_controller->_V_mouse_buttons[event._V_event.mouse.button-1]=false;
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
                    {
                        if(_V_joystick_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_JOYSTICK_CONF;
                            if(_V_joystick_controller)
                                _V_joystick_controller->reconfigure_joysticks();
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_JOYSTICK_AXIS:
                    {
                        if(_V_joystick_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_JOYSTICK_AXIS;
                            if(_V_joystick_controller)
                            {
                                auto iter=_V_joystick_controller->_V_joysticks.find(event._V_event.joystick.id);
                                if(iter!=_V_joystick_controller->_V_joysticks.end())
                                {
                                    _T_Type_joystick& joystick=_V_joystick_controller->_V_joystick_data[iter->second];
                                    joystick.sticks[event._V_event.joystick.stick].axes[event._V_event.joystick.axis].value=event._V_event.joystick.pos;
                                }
                            }
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
                    {
                        if(_V_joystick_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_JOYSTICK_BUTTON_DOWN;
                            if(_V_joystick_controller)
                            {
                                auto iter=_V_joystick_controller->_V_joysticks.find(event._V_event.joystick.id);
                                if(iter!=_V_joystick_controller->_V_joysticks.end())
                                {
                                    _T_Type_joystick& joystick=_V_joystick_controller->_V_joystick_data[iter->second];
                                    joystick.buttons[event._V_event.joystick.button].value=true;
                                }
                            }
                        }
                        break;
                    }
                    case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
                    {
                        if(_V_joystick_status)
                        {
                            event._V_type=InputEventType::INPUT_EVENT_JOYSTICK_BUTTON_UP;
                            if(_V_joystick_controller)
                            {
                                auto iter=_V_joystick_controller->_V_joysticks.find(event._V_event.joystick.id);
                                if(iter!=_V_joystick_controller->_V_joysticks.end())
                                {
                                    _T_Type_joystick& joystick=_V_joystick_controller->_V_joystick_data[iter->second];
                                    joystick.buttons[event._V_event.joystick.button].value=false;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        return event;
    }
    Input::operator ALLEGRO_EVENT_QUEUE* ()
    {
        return _V_event_queue;
    }
    Input::~Input()
    {
        destroy();
    }
}
