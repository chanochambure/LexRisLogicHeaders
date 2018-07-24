/* NativeDialog.cpp -- Native Dialog Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/NativeDialog.h"

namespace LL_AL5
{
    bool LL_SHARED native_dialog_addon()
    {
        return al_init_native_dialog_addon();
    }
    bool LL_SHARED show_native_message(ALLEGRO_DISPLAY* display,std::string title,
                                       std::string header,std::string message,int flag)
    {
        return (al_show_native_message_box(display,title.c_str(),header.c_str(),message.c_str(),nullptr,flag)==1);
    }

    void FileChooser::set_display(ALLEGRO_DISPLAY* display)
    {
        _V_display=display;
    }
    ALLEGRO_DISPLAY* FileChooser::get_display()
    {
        return _V_display;
    }
    void FileChooser::set_initial_path(std::string new_search_path)
    {
        _V_initial_path=new_search_path;
        _V_file_exists=false;
    }
    std::string FileChooser::get_initial_path()
    {
        return _V_initial_path;
    }
    void FileChooser::set_title(std::string new_title)
    {
        _V_title=new_title;
        _V_file_exists=false;
    }
    std::string FileChooser::get_title()
    {
        return _V_title;
    }
    void FileChooser::set_patterns(std::string new_patterns)
    {
        _V_patterns=new_patterns;
        _V_file_exists=false;
    }
    std::string FileChooser::get_patterns()
    {
        return _V_patterns;
    }
    void FileChooser::set_mode(int new_mode)
    {
        _V_mode=new_mode;
        _V_file_exists=false;
    }
    bool FileChooser::start_filechooser()
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
    unsigned int FileChooser::get_number_of_selected_files()
    {
        return _V_number_of_selected_files;
    }
    std::string FileChooser::operator [] (unsigned int index)
    {
        const char* file_path=al_get_native_file_dialog_path(_V_filechooser,index);
        if(file_path)
            return file_path;
        return std::string();
    }
    FileChooser::~FileChooser()
    {
        if(_V_filechooser)
            al_destroy_native_file_dialog(_V_filechooser);
    }

    void TextLog::set_title(std::string new_title)
    {
        _V_title=new_title;
    }
    std::string TextLog::get_title()
    {
        return _V_title;
    }
    void TextLog::set_mode(int new_mode)
    {
        _V_mode=new_mode;
    }
    bool TextLog::open_textlog()
    {
        if(!_V_textlog)
        {
            _V_textlog=al_open_native_text_log(_V_title.c_str(),_V_mode);
            return _V_textlog;
        }
        return false;
    }
    bool TextLog::write_text(std::string text)
    {
        if(_V_textlog)
        {
            al_append_native_text_log(_V_textlog,text.c_str());
            return true;
        }
        return false;
    }
    bool TextLog::write_endl()
    {
        return write_text("\n");
    }
    bool TextLog::close_textlog()
    {
        if(_V_textlog)
        {
            al_close_native_text_log(_V_textlog);
            _V_textlog=nullptr;
            return true;
        }
        return false;
    }
    bool TextLog::is_open()
    {
        return _V_textlog;
    }
    TextLog::operator ALLEGRO_TEXTLOG* ()
    {
        return _V_textlog;
    }
    TextLog::~TextLog()
    {
        close_textlog();
    }
}
