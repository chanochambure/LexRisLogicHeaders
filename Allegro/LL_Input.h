#ifndef LL_INPUT_H_INCLUDED
#define LL_INPUT_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

struct Key
{
    string name;
    int keycode;
    bool active=0;
    Key(string n,int k){name=n;keycode=k;}
};
class KeyControl
{
    private:
        vector<Key> key;
        ALLEGRO_EVENT_QUEUE* EQ=nullptr;
    public:
        KeyControl(ALLEGRO_EVENT_QUEUE* NEQ){EQ=NEQ;}
        Key& operator [] (unsigned int index){return key[index];}
        int FindKey(string Name){for(unsigned int i=0;i<key.size();++i){if(key[i].name==Name)return i;}return -1;}
        int FindKey(int keycode){for(unsigned int i=0;i<key.size();++i){if(key[i].keycode==keycode)return i;}return -1;}
        bool AddKey(string Name){if(FindKey(Name)!=-1)return 0;int lol=getkeycode();if(FindKey(lol)!=-1)return 0;key.push_back(Key(Name,lol));return 1;}
        bool AddKey(string Name,int keycode){if((FindKey(Name)!=-1) or (FindKey(keycode)!=-1))return 0;key.push_back(Key(Name,keycode));return 1;}
        bool ModeKey(int index,string new_Name){if((0<=index) and (index<key.size()) and (!FindKey(new_Name))){key[index].name=new_Name;return 1;}return 0;}
        bool ModeKey(int index,int new_keycode){if((0<=index) and (index<key.size()) and (!FindKey(new_keycode))){key[index].keycode=new_keycode;return 1;}return 0;}
        bool RemoveKey(string Name){int lol=FindKey(Name);if(lol==-1)return 0;key.erase((key.begin())+lol);return 1;}
        bool RemoveKey(int keycode){int lol=FindKey(keycode);if(lol==-1)return 0;key.erase((key.begin())+lol);return 1;}
        int getkeycode();
        void set_event_queue(ALLEGRO_EVENT_QUEUE* NEQ){EQ=NEQ;}
        ~KeyControl(){key.clear();}
};

int KeyControl::getkeycode()
{
    al_flush_event_queue(EQ);
    while(1)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(EQ,&event);
        if(event.type==ALLEGRO_EVENT_KEY_DOWN)
            return event.keyboard.keycode;
    }
}

class Input
{
    private:
        bool k_on=0;
        bool m_on=0;
        string* _word;
        unsigned int _c_limits;
        ALLEGRO_EVENT_QUEUE* EQ;
        ALLEGRO_TIMER* T;
        KeyControl* key=nullptr;
        int _KeySearchName(string Name){if(key)return key->FindKey(Name);return -1;}
        int _KeySearchKeycode(int keycode){if(key)return key->FindKey(keycode);return -1;}
        bool close=0;
        bool _d_ff=0;
        bool _ff=0;
        float _x_m=0;
        float _y_m=0;
        int _z_m=0;
        bool _c_[3];
        bool input=0;
        ALLEGRO_DISPLAY** DS=nullptr;
        ALLEGRO_TEXTLOG** TL=nullptr;
        bool _re_D=0;
        bool _re_TL=0;
        bool timer_event=0;
    public:
        Input(float fps);
        //Changes
        bool UnregisterDisplay(){if(_re_D){al_unregister_event_source(EQ,al_get_display_event_source(*DS));_re_D=0;return 1;}return 0;}
        bool RegisterDisplay(ALLEGRO_DISPLAY*& New_Display){if(!_re_D){DS=&New_Display;al_register_event_source(EQ,al_get_display_event_source(*DS));_re_D=1;return 1;}return 0;}
        bool UnregisterTextLog(){if(_re_TL){al_unregister_event_source(EQ,al_get_native_text_log_event_source(*TL));_re_TL=0;return 1;}return 0;}
        bool RegisterTextLog(ALLEGRO_TEXTLOG*& New_TextLog){if(!_re_TL){TL=&New_TextLog;al_register_event_source(EQ,al_get_native_text_log_event_source(*TL));_re_TL=1;return 1;}return 0;}
        void ChangeFpS(float fps){al_unregister_event_source(EQ, al_get_timer_event_source(T));al_destroy_timer(T);T=al_create_timer(fps);al_register_event_source(EQ, al_get_timer_event_source(T));}
        void SetKeyControl(KeyControl* k){key=k;}
        KeyControl* GetKeyControl(){return key;}
        void clear_events(){al_flush_event_queue(EQ);}
        //ADD,REMOVE,MODIFY
        bool& operator [] (string Name){_ff=0;int lol=_KeySearchName(Name);if(lol==-1)return _ff;return ((*key)[lol]).active;}
        void operator()();
        void getexit();
        //INPUT
        void KeyboardON(){if(!k_on)al_register_event_source(EQ,al_get_keyboard_event_source());k_on=1;}
        void KeyboardOFF(){if(k_on)al_unregister_event_source(EQ,al_get_keyboard_event_source());k_on=0;}
        void MouseON(){if(!m_on)al_register_event_source(EQ,al_get_mouse_event_source());m_on=1;}
        void MouseOFF(){if(m_on){al_unregister_event_source(EQ,al_get_mouse_event_source());for(int i=0;i<3;++i)_c_[i]=0;}m_on=0;}
        bool inputON(string* X,unsigned int c){KeyboardON();if(c>0 and !input){_word=X;input=1;_c_limits=c;if(_word->size()>_c_limits)(*_word)=_word->substr(0,_c_limits);return 1;}return 0;}
        bool inputOFF(string *X){if(input and X==_word){input=0;return 1;}return 0;}
        //MOUSE
        bool SetMouseXY(float x,float y){if(al_set_mouse_xy(*DS,x,y)){_x_m=x;_y_m=y;return 1;}return 0;}
        bool SetMouseZ(float z){if(al_set_mouse_z(z)){_z_m=z;return 1;}return 0;}
        float MouseX(){return _x_m;}
        float MouseY(){return _y_m;}
        int MouseZ(){return _z_m;}
        bool& rightclick(){return (_c_[1]);}
        bool& leftclick(){return (_c_[0]);}
        bool& midclick(){return (_c_[2]);}
        bool ShowCursor(){return al_show_mouse_cursor(*DS);}
        bool HideCursor(){return al_hide_mouse_cursor(*DS);}
        //OTHER
        bool get_timer_event(){return timer_event;}
        bool& get_display_status(){return close;}
        ALLEGRO_TIMER* get_timer(){return T;}
        operator ALLEGRO_EVENT_QUEUE* (){return EQ;}
        ~Input();
};

Input::Input(float fps)
{
    for(int i=0;i<3;++i)
        _c_[i]=0;
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
    if(k_on)
    {
        if(input and event.type==ALLEGRO_EVENT_KEY_CHAR)
        {
            if(event.keyboard.keycode==63)
                (*_word)=_word->substr(0,_word->size()-1);
            else if(_word->size()<_c_limits)
            {
                if(event.keyboard.keycode==67)
                    (*_word)=(*_word)+'\n';
                else if(event.keyboard.keycode==64)
                    (*_word)=(*_word)+'\t';
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
        if(event.type==ALLEGRO_EVENT_MOUSE_AXES)
        {
            _x_m=event.mouse.x;
            _y_m=event.mouse.y;
            _z_m=event.mouse.z;
        }
        if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            _c_[event.mouse.button-1]=1;
        if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            _c_[event.mouse.button-1]=0;
    }
    timer_event=(event.type==ALLEGRO_EVENT_TIMER);
}

void Input::getexit()
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
    UnregisterDisplay();
    UnregisterTextLog();
    KeyboardOFF();
    MouseOFF();
    if(EQ)
        al_destroy_event_queue(EQ);
    if(T)
        al_destroy_timer(T);
    al_uninstall_keyboard();
    al_uninstall_mouse();
}

#endif // LL_INPUT_H_INCLUDED
