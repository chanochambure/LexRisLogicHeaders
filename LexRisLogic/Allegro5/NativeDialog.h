/* NativeDialog.h -- Native Dialog Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_NATIVEDIALOG_H
#define INCLUDED_LL_AL5_NATIVEDIALOG_H

#include <string>

namespace LL_AL5
{
    bool show_native_message(ALLEGRO_DISPLAY* display,std::string title,std::string header,std::string message,int flag)
    {
        return (al_show_native_message_box(display,title.c_str(),header.c_str(),message.c_str(),nullptr,flag)==1);
    }

    class FileChooser
    {
        private:
            int _V_mode=0;
            std::string _V_initial_path;
            std::string _V_title;
            std::string _V_patterns="*.*";
            unsigned int _V_number_of_selected_files=0;
            bool _V_file_exists=false;
            ALLEGRO_FILECHOOSER* _V_filechooser=nullptr;
            ALLEGRO_DISPLAY* _V_display=nullptr;
        public:
            void set_display(ALLEGRO_DISPLAY* display)
            {
                _V_display=display;
            }
            ALLEGRO_DISPLAY* get_display()
            {
                return _V_display;
            }
            void set_initial_path(std::string new_search_path)
            {
                _V_initial_path=new_search_path;
                _V_file_exists=false;
            }
            std::string get_initial_path()
            {
                return _V_initial_path;
            }
            void set_title(std::string new_title)
            {
                _V_title=new_title;
                _V_file_exists=false;
            }
            std::string get_title()
            {
                return _V_title;
            }
            void set_patterns(std::string new_patterns)
            {
                _V_patterns=new_patterns;
                _V_file_exists=false;
            }
            std::string get_patterns()
            {
                return _V_patterns;
            }
            void set_mode(int new_mode)
            {
                _V_mode=new_mode;
                _V_file_exists=false;
            }
            bool start_filechooser()
            {
                if(!_V_file_exists)
                {
                    if(_V_filechooser)
                        al_destroy_native_file_dialog(_V_filechooser);
                    _V_filechooser=al_create_native_file_dialog(_V_initial_path.c_str(),_V_title.c_str(),
                                                                _V_patterns.c_str(),_V_mode);
                    if(!_V_filechooser)
                        return false;
                    _V_file_exists=true;
                }
                al_show_native_file_dialog(_V_display,_V_filechooser);
                _V_number_of_selected_files=al_get_native_file_dialog_count(_V_filechooser);
                return _V_number_of_selected_files;
            }
            unsigned int get_number_of_selected_files()
            {
                return _V_number_of_selected_files;
            }
            std::string operator [] (unsigned int index)
            {
                const char* file_path=al_get_native_file_dialog_path(_V_filechooser,index);
                if(file_path)
                    return file_path;
                return std::string();
            }
            ~FileChooser()
            {
                if(_V_filechooser)
                    al_destroy_native_file_dialog(_V_filechooser);
            }
    };

    class TextLog
    {
        private:
            int _V_mode=0;
            std::string _V_title;
            ALLEGRO_TEXTLOG* _V_textlog=nullptr;
        public:
            void set_title(std::string new_title)
            {
                _V_title=new_title;
            }
            std::string get_title()
            {
                return _V_title;
            }
            void set_mode(int new_mode)
            {
                _V_mode=new_mode;
            }
            bool open_textlog()
            {
                if(!_V_textlog)
                {
                    _V_textlog=al_open_native_text_log(_V_title.c_str(),_V_mode);
                    return _V_textlog;
                }
                return false;
            }
            bool write_text(std::string text)
            {
                if(_V_textlog)
                {
                    al_append_native_text_log(_V_textlog,text.c_str());
                    return true;
                }
                return false;
            }
            bool write_endl()
            {
                return write_text("\n");
            }
            bool close_textlog()
            {
                if(_V_textlog)
                {
                    al_close_native_text_log(_V_textlog);
                    _V_textlog=nullptr;
                    return true;
                }
                return false;
            }
            bool is_open()
            {
                return _V_textlog;
            }
            operator ALLEGRO_TEXTLOG* ()
            {
                return _V_textlog;
            }
            ~TextLog()
            {
                close_textlog();
            }
    };
}

#endif // INCLUDED_LL_AL5_NATIVEDIALOG_H
