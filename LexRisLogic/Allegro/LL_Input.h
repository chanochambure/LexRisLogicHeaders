#ifndef LL_INPUT_H_INCLUDED
#define LL_INPUT_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

struct LL_Key
{
    string name;
    int keycode;
    bool active=0;
    LL_Key(string n,int k){name=n;keycode=k;}
};

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

class LL_KeyControl
{
    private:
        vector<LL_Key> key;
    public:
        LL_Key& operator [] (unsigned int index){return key[index];}
        int find_key(string Name){for(unsigned int i=0;i<key.size();++i){if(key[i].name==Name)return i;}return -1;}
        int find_key(int keycode){for(unsigned int i=0;i<key.size();++i){if(key[i].keycode==keycode)return i;}return -1;}
        bool add_key(string Name,int keycode){if((find_key(Name)!=-1) or (find_key(keycode)!=-1))return 0;key.push_back(LL_Key(Name,keycode));return 1;}
        bool mod_key(unsigned int index,string new_Name){if((index<key.size()) and (find_key(new_Name)==-1)){key[index].name=new_Name;return 1;}return 0;}
        bool mod_key(unsigned int index,int new_keycode){if((index<key.size()) and (find_key(new_keycode)==-1)){key[index].keycode=new_keycode;return 1;}return 0;}
        bool remove_key(string Name){int lol=find_key(Name);if(lol==-1)return 0;key.erase((key.begin())+lol);return 1;}
        bool remove_key(int keycode){int lol=find_key(keycode);if(lol==-1)return 0;key.erase((key.begin())+lol);return 1;}
        void clear_key_values(){for(unsigned int i=0;i<key.size();++i)key[i].active=0;}
        unsigned int size(){return key.size();}
        ~LL_KeyControl(){key.clear();}
};

class LL_Input
{
    private:
        bool k_on=0;
        bool m_on=0;
        string* _word;
        unsigned int _c_limits;
        ALLEGRO_EVENT_QUEUE* EQ;
        ALLEGRO_TIMER* T;
        LL_KeyControl* key=nullptr;
        int _KeySearchName(string Name){if(key)return key->find_key(Name);return -1;}
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
        LL_Input(float fps);
        bool unregister_display(){if(_re_D){al_unregister_event_source(EQ,al_get_display_event_source(*DS));_re_D=0;return 1;}return 0;}
        bool register_display(ALLEGRO_DISPLAY*& New_Display){if(!_re_D){DS=&New_Display;al_register_event_source(EQ,al_get_display_event_source(*DS));_re_D=1;return 1;}return 0;}
        bool unregister_textlog(){if(_re_TL){al_unregister_event_source(EQ,al_get_native_text_log_event_source(*TL));_re_TL=0;return 1;}return 0;}
        bool register_textlog(ALLEGRO_TEXTLOG*& New_TextLog){if(!_re_TL){TL=&New_TextLog;al_register_event_source(EQ,al_get_native_text_log_event_source(*TL));_re_TL=1;return 1;}return 0;}
        void change_fps(float fps){al_unregister_event_source(EQ, al_get_timer_event_source(T));al_destroy_timer(T);T=al_create_timer(fps);al_register_event_source(EQ, al_get_timer_event_source(T));}
        void set_key_control(LL_KeyControl* k){key=k;}
        LL_KeyControl* get_key_control(){return key;}
        void clear_events(){al_flush_event_queue(EQ);}
        void clear_key_values(){if(key)key->clear_key_values();}
        bool& operator [] (string Name){_ff=0;int lol=_KeySearchName(Name);if(lol==-1)return _ff;return ((*key)[lol]).active;}
        void operator()();
        void get_exit();
        void keyboard_on(){if(!k_on)al_register_event_source(EQ,al_get_keyboard_event_source());k_on=1;}
        void keyboard_off(){if(k_on)al_unregister_event_source(EQ,al_get_keyboard_event_source());k_on=0;}
        void mouse_on(){m_on=1;}
        void mouse_off(){m_on=0;}
        bool input_on(string* X,unsigned int c,bool special_is_blocked=0){keyboard_on();if(c>0 and !input){special_block=special_is_blocked;_word=X;input=1;_c_limits=c;if(_word->size()>_c_limits)(*_word)=_word->substr(0,_c_limits);return 1;}return 0;}
        bool input_off(string *X){if(input and X==_word){input=0;return 1;}return 0;}
        bool set_mouse_xy(pos_t x,pos_t y){if(al_set_mouse_xy(*DS,x,y)){axe_x=x;axe_y=y;return 1;}return 0;}
        bool set_mouse_z(int z){if(al_set_mouse_z(z)){axe_z=z;return 1;}return 0;}
        pos_t get_mouse_x(){return axe_x;}
        pos_t get_mouse_y(){return axe_y;}
        int get_mouse_z(){return axe_z;}
        bool& right_click(){return (mouse_button[1]);}
        bool& left_click(){return (mouse_button[0]);}
        bool& mid_click(){return (mouse_button[2]);}
        bool get_timer_event(){return timer_event;}
        bool& get_display_status(){return close;}
        ALLEGRO_TIMER* get_timer(){return T;}
        operator ALLEGRO_EVENT_QUEUE* (){return EQ;}
        ~LL_Input();
};

LL_Input::LL_Input(float fps)
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

void LL_Input::operator()()
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
    if(k_on)
    {
        if(input and event.type==ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode==63)
                (*_word)=_word->substr(0,_word->size()-1);
            else if(_word->size()<_c_limits)
            {
                if(event.keyboard.keycode==67)
                {
                    if(!special_block)
                        (*_word)=(*_word)+'\n';
                }
                else if(event.keyboard.keycode==64)
                {
                    if(!special_block)
                        (*_word)=(*_word)+'\t';
                }
                else if(event.keyboard.unichar>=32 and event.keyboard.keycode!=77)
                    (*_word)=(*_word)+char(event.keyboard.unichar);
            }
        }
        if(event.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            int lol=_KeySearchKeycode(event.keyboard.keycode);
            if(lol!=-1)
                ((*key)[lol]).active=1;
        }
        if(event.type==ALLEGRO_EVENT_KEY_UP)
        {
            int lol=_KeySearchKeycode(event.keyboard.keycode);
            if(lol!=-1)
                ((*key)[lol]).active=0;
        }
    }
    if(m_on)
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
    timer_event=(event.type==ALLEGRO_EVENT_TIMER);
}

void LL_Input::get_exit()
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

LL_Input::~LL_Input()
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

#endif // LL_INPUT_H_INCLUDED
