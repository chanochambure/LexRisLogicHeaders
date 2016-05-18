#ifndef INCLUDED_LL_AL5_INPUT_H
#define INCLUDED_LL_AL5_INPUT_H

#include <vector>
#include <string>

namespace LL_AL5
{
    struct Key
    {
        std::string key_name;
        int keycode;
        bool key_down=false;
        Key(std::string new_key_name,int new_keycode)
        {
            key_name=new_key_name;
            keycode=new_keycode;
        }
    };

    class KeyControl
    {
        private:
            std::vector<Key> _V_keys;
        public:
            bool add_key(std::string key_name,int keycode)
            {
                if((find_key(key_name)!=-1) or (find_key(keycode)!=-1))
                    return false;
                _V_keys.push_back(Key(key_name,keycode));
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
            void clear()
            {
                for(unsigned int i=0;i<_V_keys.size();++i)
                    _V_keys[i].key_down=false;
            }
            Key& operator [] (unsigned int index)
            {
                return _V_keys[index];
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
            std::string* _V_input_objetive;
            unsigned int _c_limits;
            ALLEGRO_EVENT_QUEUE* EQ;
            ALLEGRO_TIMER* T;
            KeyControl* key=nullptr;
            int _KeySearchName(std::string Name){if(key)return key->find_key(Name);return -1;}
            int _KeySearchKeycode(int keycode){if(key)return key->find_key(keycode);return -1;}
            bool close=0;
            bool _ff=0;
            float axe_x=0;
            float axe_y=0;
            int axe_z=0;
            bool mouse_button[3];
            bool mouse_button_status[3];
            bool input=0;
            ALLEGRO_DISPLAY** DS=nullptr;
            ALLEGRO_TEXTLOG** TL=nullptr;
            bool _re_D=0;
            bool _re_TL=0;
            bool timer_event=0;
            bool special_block=0;
        public:
            Input(float fps);
            bool unregister_display(){if(_re_D){al_unregister_event_source(EQ,al_get_display_event_source(*DS));_re_D=0;return 1;}return 0;}
            bool register_display(ALLEGRO_DISPLAY*& New_Display){if(!_re_D){DS=&New_Display;al_register_event_source(EQ,al_get_display_event_source(*DS));_re_D=1;return 1;}return 0;}
            bool unregister_textlog(){if(_re_TL){al_unregister_event_source(EQ,al_get_native_text_log_event_source(*TL));_re_TL=0;return 1;}return 0;}
            bool register_textlog(ALLEGRO_TEXTLOG*& New_TextLog){if(!_re_TL){TL=&New_TextLog;al_register_event_source(EQ,al_get_native_text_log_event_source(*TL));_re_TL=1;return 1;}return 0;}
            void change_fps(float fps){al_unregister_event_source(EQ, al_get_timer_event_source(T));al_destroy_timer(T);T=al_create_timer(fps);al_register_event_source(EQ, al_get_timer_event_source(T));}
            void set_key_control(KeyControl* k){key=k;}
            KeyControl* get_key_control(){return key;}
            void clear_events(){al_flush_event_queue(EQ);}
            void clear(){if(key)key->clear();}
            bool& operator [] (std::string Name){_ff=0;int lol=_KeySearchName(Name);if(lol==-1)return _ff;return ((*key)[lol]).key_down;}
            void operator()();
            void get_exit();
            void keyboard_on(){if(!_V_keyboard_status)al_register_event_source(EQ,al_get_keyboard_event_source());_V_keyboard_status=1;}
            void keyboard_off(){if(_V_keyboard_status)al_unregister_event_source(EQ,al_get_keyboard_event_source());_V_keyboard_status=0;}
            bool mouse_on(bool event_type=false)
            {
                if(_V_mouse_status)
                    return false;
                _V_mouse_status=1;
                _V_mouse_event_type=event_type;
                if(_V_mouse_event_type)
                    al_register_event_source(EQ,al_get_mouse_event_source());
                return true;
            }
            bool mouse_off()
            {
                if(_V_mouse_status)
                {
                    _V_mouse_status=false;
                    if(_V_mouse_event_type)
                    {
                        al_unregister_event_source(EQ,al_get_mouse_event_source());
                        _V_mouse_event_type=false;
                    }
                    return true;
                }
                return false;
            }
            bool input_on(std::string* X,unsigned int c,bool special_is_blocked=0){keyboard_on();if(c>0 and !input){special_block=special_is_blocked;_V_input_objetive=X;input=1;_c_limits=c;if(_V_input_objetive->size()>_c_limits)(*_V_input_objetive)=_V_input_objetive->substr(0,_c_limits);return 1;}return 0;}
            bool input_off(std::string *X){if(input and X==_V_input_objetive){input=0;return 1;}return 0;}
            bool set_mouse_xy(Type_pos x,Type_pos y){if(al_set_mouse_xy(*DS,x,y)){axe_x=x;axe_y=y;return 1;}return 0;}
            bool set_mouse_z(int z){if(al_set_mouse_z(z)){axe_z=z;return 1;}return 0;}
            Type_pos get_mouse_x(){return axe_x;}
            Type_pos get_mouse_y(){return axe_y;}
            int get_mouse_z(){return axe_z;}
            bool& right_click(){return (mouse_button[1]);}
            bool& left_click(){return (mouse_button[0]);}
            bool& mid_click(){return (mouse_button[2]);}
            bool get_timer_event(){return timer_event;}
            bool& get_display_status(){return close;}
            ALLEGRO_TIMER* get_timer(){return T;}
            operator ALLEGRO_EVENT_QUEUE* (){return EQ;}
            ~Input();
    };

    Input::Input(float fps)
    {
        for(int i=0;i<3;++i)
            mouse_button[i]=mouse_button_status[i]=0;
        al_install_keyboard();
        al_install_mouse();
        EQ=al_create_event_queue();
        T=al_create_timer(fps);
        al_register_event_source(EQ, al_get_timer_event_source(T));
        al_start_timer(T);
    }

    void Input::operator()()
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(EQ,&event);
        if(_re_D)
        {
            if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
                close=1;
        }
        if(_re_TL)
        {
            if(event.type==ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE)
            {
                al_close_native_text_log(*TL);
                (*TL)=nullptr;
            }
        }
        if(_V_keyboard_status)
        {
            if(input and event.type==ALLEGRO_EVENT_KEY_CHAR)
            {
                if(event.keyboard.keycode==ALLEGRO_KEY_BACKSPACE)
                    (*_V_input_objetive)=_V_input_objetive->substr(0,_V_input_objetive->size()-1);
                else if(_V_input_objetive->size()<_c_limits)
                {
                    if(event.keyboard.keycode==ALLEGRO_KEY_ENTER)
                    {
                        if(!special_block)
                            (*_V_input_objetive)=(*_V_input_objetive)+'\n';
                    }
                    else if(event.keyboard.keycode==ALLEGRO_KEY_TAB)
                    {
                        if(!special_block)
                            (*_V_input_objetive)=(*_V_input_objetive)+'\t';
                    }
                    else if(event.keyboard.unichar>=32 and event.keyboard.keycode!=77)
                        (*_V_input_objetive)=(*_V_input_objetive)+char(event.keyboard.unichar);
                }
            }
            if(event.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                int lol=_KeySearchKeycode(event.keyboard.keycode);
                if(lol!=-1)
                    ((*key)[lol]).key_down=1;
            }
            if(event.type==ALLEGRO_EVENT_KEY_UP)
            {
                int lol=_KeySearchKeycode(event.keyboard.keycode);
                if(lol!=-1)
                    ((*key)[lol]).key_down=0;
            }
        }
        if(_V_mouse_status)
        {
            if(_V_mouse_event_type)
            {
                if(event.type==ALLEGRO_EVENT_MOUSE_AXES)
                {
                    axe_x=event.mouse.x;
                    axe_y=event.mouse.y;
                    axe_z=event.mouse.z;
                }
                else if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    mouse_button[event.mouse.button-1]=1;
                else if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                    mouse_button[event.mouse.button-1]=0;
            }
            else
            {
                ALLEGRO_MOUSE_STATE state;
                al_get_mouse_state(&state);
                for(unsigned int i=0;i<3;++i)
                {
                    bool actual=(state.buttons & 1<<i);
                    if(mouse_button_status[i]==mouse_button[i])
                        mouse_button_status[i]=mouse_button[i]=actual;
                    else
                    {
                        if(mouse_button[i]==actual)
                            mouse_button_status[i]=actual;
                    }
                }
                axe_x=state.x;
                axe_y=state.y;
                axe_z=state.z;
            }
        }
        timer_event=(event.type==ALLEGRO_EVENT_TIMER);
    }

    void Input::get_exit()
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(EQ,&event);
        if(_re_D)
        {
            if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
                close=1;
        }
        if(_re_TL)
        {
            if(event.type==ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE)
            {
                al_close_native_text_log(*TL);
                (*TL)=nullptr;
            }
        }
    }

    Input::~Input()
    {
        unregister_display();
        unregister_textlog();
        keyboard_off();
        mouse_off();
        if(EQ)
        {
            al_destroy_event_queue(EQ);
            EQ=nullptr;
        }
        if(T)
        {
            al_destroy_timer(T);
            T=nullptr;
        }
        al_uninstall_keyboard();
        al_uninstall_mouse();
    }

    int get_keycode(ALLEGRO_EVENT_QUEUE* EQ)
    {
        if(EQ==nullptr)
            return -1;
        al_flush_event_queue(EQ);
        while(1)
        {
            ALLEGRO_EVENT event;
            al_wait_for_event(EQ,&event);
            if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
                return -1;
            if(event.type==ALLEGRO_EVENT_KEY_DOWN)
                return event.keyboard.keycode;
        }
    }
}

#endif // INCLUDED_LL_AL5_INPUT_H
