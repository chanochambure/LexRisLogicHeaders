#ifndef INCLUDED_LL_AL5_INPUT_H
#define INCLUDED_LL_AL5_INPUT_H

#include <vector>
#include <string>

namespace LL_AL5
{
    class KeyControl
    {
        private:
            struct _S_Structure_Key
            {
                std::string key_name;
                int keycode;
                bool key_down=false;
                _S_Structure_Key(std::string new_key_name,int new_keycode)
                {
                    key_name=new_key_name;
                    keycode=new_keycode;
                }
            };
            std::vector<_S_Structure_Key> _V_keys;
        public:
            bool add_key(std::string key_name,int keycode)
            {
                if((find_key(key_name)!=-1) or (find_key(keycode)!=-1))
                    return false;
                _V_keys.push_back(_S_Structure_Key(key_name,keycode));
                return true;
            }
            int find_key(std::string key_name)
            {
                for(unsigned int i=0;i<_V_keys.size();++i)
                {
                    if(_V_keys[i].key_name==key_name)
                        return i;
                }
                return -1;
            }
            int find_key(int keycode)
            {
                for(unsigned int i=0;i<_V_keys.size();++i)
                {
                    if(_V_keys[i].keycode==keycode)
                        return i;
                }
                return -1;
            }
            bool mod_key(unsigned int index,std::string new_key_name)
            {
                if((index<_V_keys.size()) and (find_key(new_key_name)==-1))
                {
                    _V_keys[index].key_name=new_key_name;
                    return true;
                }
                return false;
            }
            bool mod_key(unsigned int index,int new_keycode)
            {
                if((index<_V_keys.size()) and (find_key(new_keycode)==-1))
                {
                    _V_keys[index].keycode=new_keycode;
                    return true;
                }
                return false;
            }
            bool remove_key(std::string key_name)
            {
                int key_index=find_key(key_name);
                if(key_index==-1)
                    return false;
                _V_keys.erase((_V_keys.begin())+key_index);
                return true;
            }
            bool remove_key(int keycode)
            {
                int key_index=find_key(keycode);
                if(key_index==-1)
                    return false;
                _V_keys.erase((_V_keys.begin())+key_index);
                return true;
            }
            unsigned int size()
            {
                return _V_keys.size();
            }
            void clear_key_status()
            {
                for(unsigned int i=0;i<_V_keys.size();++i)
                    _V_keys[i].key_down=false;
            }
            void clear()
            {
                _V_keys.clear();
            }
            bool& get_key_down_status(unsigned int index)
            {
                return _V_keys[index].key_down;
            }
            std::string get_key_name(unsigned int index)
            {
                return _V_keys[index].key_name;
            }
            int get_keycode(unsigned int index)
            {
                return _V_keys[index].keycode;
            }
            ~KeyControl()
            {
                _V_keys.clear();
            }
    };

    class Input
    {
        private:
            bool _V_keyboard_status=false;
            bool _V_mouse_status=false;
            bool _V_mouse_event_type=false;
            std::string* _V_input_objetive=nullptr;
            unsigned int _V_max_input_size;
            ALLEGRO_EVENT_QUEUE* _V_event_queue;
            KeyControl* _V_key_control=nullptr;
            bool _V_display_exit_status=false;
            bool _V_textlog_exit_status=false;
            float _V_time=0;
            bool _V_timer_event=false;
            bool _V_auxiliar_key=false;
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
            int _F_find_key(std::string key_name)
            {
                if(_V_key_control)
                    return _V_key_control->find_key(key_name);
                return -1;
            }
            int _F_find_key(int keycode)
            {
                if(_V_key_control)
                    return _V_key_control->find_key(keycode);
                return -1;
            }
        public:
            Input()
            {
                al_install_keyboard();
                al_install_mouse();
                _V_event_queue=al_create_event_queue();
            }
            bool unregister_timer()
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
            bool register_timer(ALLEGRO_TIMER* new_timer)
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
            bool unregister_display()
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
            bool register_display(ALLEGRO_DISPLAY* new_display)
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
            bool unregister_textlog()
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
            bool register_textlog(ALLEGRO_TEXTLOG* new_textlog)
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
            void set_key_control(KeyControl* new_key_control)
            {
                _V_key_control=new_key_control;
            }
            KeyControl* get_key_control()
            {
                return _V_key_control;
            }
            void clear_events()
            {
                al_flush_event_queue(_V_event_queue);
            }
            void clear_key_status()
            {
                if(_V_key_control)
                    _V_key_control->clear_key_status();
            }
            bool set_wait_time(float wait_time)
            {
                if(wait_time<0)
                    return false;
                _V_time=wait_time;
                return true;
            }
            unsigned int get_wait_time()
            {
                return _V_time;
            }
            bool keyboard_on()
            {
                if(!_V_keyboard_status)
                {
                    al_register_event_source(_V_event_queue,al_get_keyboard_event_source());
                    _V_keyboard_status=true;
                    return true;
                }
                return false;
            }
            bool keyboard_off()
            {
                if(_V_keyboard_status)
                {
                    al_unregister_event_source(_V_event_queue,al_get_keyboard_event_source());
                    _V_keyboard_status=false;
                    return true;
                }
                return false;
            }
            bool input_on(std::string* input_objetive,unsigned int max_input_size,bool special_is_blocked=false)
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
            bool input_off(std::string* input_objetive)
            {
                if(_V_input_activated and _V_input_objetive and input_objetive==_V_input_objetive)
                {
                    _V_input_activated=false;
                    _V_input_objetive=nullptr;
                    return true;
                }
                return false;
            }
            bool mouse_on(bool event_type=false)
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
            bool mouse_off()
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
            bool set_mouse_xy(int new_mouse_x,int new_mouse_y)
            {
                if(al_set_mouse_xy(_V_display,new_mouse_x,new_mouse_y))
                {
                    _V_mouse_x=new_mouse_x;
                    _V_mouse_y=new_mouse_y;
                    return true;
                }
                return false;
            }
            int get_mouse_x()
            {
                return _V_mouse_x;
            }
            int get_mouse_y()
            {
                return _V_mouse_y;
            }
            bool set_mouse_z(int new_mouse_z)
            {
                if(al_set_mouse_z(new_mouse_z))
                {
                    _V_mouse_z=new_mouse_z;
                    return true;
                }
                return false;
            }
            int get_mouse_z()
            {
                return _V_mouse_z;
            }
            bool& left_click()
            {
                return (_V_mouse_buttons[0]);
            }
            bool& right_click()
            {
                return (_V_mouse_buttons[1]);
            }
            bool& middle_click()
            {
                return (_V_mouse_buttons[2]);
            }
            bool get_timer_event()
            {
                return _V_timer_event;
            }
            bool& get_display_status()
            {
                return _V_display_exit_status;
            }
            bool& get_textlog_status()
            {
                return _V_textlog_exit_status;
            }
            bool get_event()
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
                            int key_index=_F_find_key(event.keyboard.keycode);
                            if(key_index!=-1)
                                _V_key_control->get_key_down_status(key_index)=true;
                            return true;
                        }
                        else if(event.type==ALLEGRO_EVENT_KEY_UP)
                        {
                            int key_index=_F_find_key(event.keyboard.keycode);
                            if(key_index!=-1)
                                _V_key_control->get_key_down_status(key_index)=false;
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
            int get_keycode()
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
            bool& operator [](std::string key_name)
            {
                _V_auxiliar_key=false;
                int key_index=_F_find_key(key_name);
                if(key_index==-1)
                    return _V_auxiliar_key;
                return _V_key_control->get_key_down_status(key_index);
            }
            operator ALLEGRO_EVENT_QUEUE* ()
            {
                return _V_event_queue;
            }
            ~Input()
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
    };
}

#endif // INCLUDED_LL_AL5_INPUT_H
