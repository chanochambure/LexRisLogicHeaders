#ifndef LL_NATIVE_DIALOG_H_INCLUDED
#define LL_NATIVE_DIALOG_H_INCLUDED

#include <LexRisLogic/Allegro/LL_Allegro.h>
#include <sstream>

bool show_native_message(ALLEGRO_DISPLAY* display,string title,string header,string text,int flags)
{
    return (1==al_show_native_message_box(display,title.c_str(),header.c_str(),text.c_str(),nullptr,flags));
}

class FileChooser
{
    private:
        bool _no_exist=1;
        ALLEGRO_FILECHOOSER* _chooser=nullptr;
        ALLEGRO_DISPLAY* _display=nullptr;
        string _path;
        string _title;
        string _format=".*.";
        int _mode=0;
        unsigned int _selected_files=0;
    public:
        FileChooser(){}
        void set_display(ALLEGRO_DISPLAY* d){_display=d;}
        ALLEGRO_DISPLAY* get_display(){return _display;}
        void set_path(string path){_path=path;_no_exist=1;}
        string get_path(){return _path;}
        void set_title(string title){_title=title;_no_exist=1;}
        string get_title(){return _title;}
        void set_mode(int mode){_mode=mode;_no_exist=1;}
        unsigned int get_count_selected_files(){return _selected_files;}
        void set_format(string format){_format=format;_no_exist=1;}
        void operator () ()
        {
            if(_no_exist)
            {
                if(_chooser)
                    al_destroy_native_file_dialog(_chooser);
                _chooser=al_create_native_file_dialog(_path.c_str(),_title.c_str(),_format.c_str(),_mode);
                _no_exist=0;
            }
            al_show_native_file_dialog(_display,_chooser);
            _selected_files=al_get_native_file_dialog_count(_chooser);
        }
        string operator [] (unsigned int pos)
        {
            return al_get_native_file_dialog_path(_chooser,pos);
        }
        ~FileChooser(){if(_chooser)al_destroy_native_file_dialog(_chooser);}
};

class TextLog
{
    private:
        string _title;
        int _mode=0;
        ALLEGRO_TEXTLOG* _tex=nullptr;
    public:
        TextLog(){}
        void set_title(string title){_title=title;}
        string get_title(){return _title;}
        void set_mode(int mode){_mode=mode;}
        operator ALLEGRO_TEXTLOG*& (){return _tex;}
        bool is_open(){return _tex;}
        bool open(){if(!_tex){_tex=al_open_native_text_log(_title.c_str(),_mode);return _tex;}return 0;}
        void write(string str){al_append_native_text_log(_tex,str.c_str());}
        void close(){if(_tex){al_close_native_text_log(_tex);_tex=nullptr;}}
        ~TextLog(){close();}
};

#endif // LL_NATIVE_DIALOG_H_INCLUDED
