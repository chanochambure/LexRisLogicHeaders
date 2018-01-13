/* NativeDialog.h -- Native Dialog Allegro 5 Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_AL5_NATIVEDIALOG_H
#define INCLUDED_LL_AL5_NATIVEDIALOG_H

#include "../LL_Shared.h"

#include "Allegro5.h"

#include <allegro5/allegro_native_dialog.h>
#include <string>

namespace LL_AL5
{
    bool LL_SHARED native_dialog_addon();
    bool LL_SHARED show_native_message(ALLEGRO_DISPLAY* display,std::string title,
                                       std::string header,std::string message,int flag);

    class LL_SHARED FileChooser
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
            void set_display(ALLEGRO_DISPLAY* display);
            ALLEGRO_DISPLAY* get_display();
            void set_initial_path(std::string new_search_path);
            std::string get_initial_path();
            void set_title(std::string new_title);
            std::string get_title();
            void set_patterns(std::string new_patterns);
            std::string get_patterns();
            void set_mode(int new_mode);
            bool start_filechooser();
            unsigned int get_number_of_selected_files();
            std::string operator [] (unsigned int index);
            ~FileChooser();
    };

    class LL_SHARED TextLog
    {
        private:
            int _V_mode=0;
            std::string _V_title;
            ALLEGRO_TEXTLOG* _V_textlog=nullptr;
        public:
            void set_title(std::string new_title);
            std::string get_title();
            void set_mode(int new_mode);
            bool open_textlog();
            bool write_text(std::string text);
            bool write_endl();
            bool close_textlog();
            bool is_open();
            operator ALLEGRO_TEXTLOG* ();
            ~TextLog();
    };
}

#endif // INCLUDED_LL_AL5_NATIVEDIALOG_H
