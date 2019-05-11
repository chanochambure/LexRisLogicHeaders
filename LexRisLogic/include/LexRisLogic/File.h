/* File.h -- File Header - LexRis Logic Headers

    Copyright (c) 2017-2019 LexRisLogic

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

#ifndef INCLUDED_LL_FILE_H
#define INCLUDED_LL_FILE_H

#include "LL_Shared.h"

#include <string>
#include <vector>
#include <fstream>

namespace LL
{
    class LL_SHARED FileStream
    {
        private:
            std::string _V_file_path;
            std::ifstream _V_input_stream;
            std::ofstream _V_output_stream;
            bool _V_binary_option=false;
            bool _V_append_option=false;
        public:
            FileStream();
            FileStream(const FileStream&) = delete;
            void set_path(std::string new_path);
            std::string get_path();
            bool set_binary_option(bool new_binary_option);
            bool get_binary_option();
            bool set_append_option(bool new_append_option);
            bool get_append_option();
            bool open(bool mode);
            bool write(const char* data,unsigned int bytes);
            unsigned int read(char* data,unsigned int bytes);
            bool close();
            bool is_open();
            const FileStream& operator = (const FileStream&) = delete;
            ~FileStream();
    };

    class LL_SHARED TextFile
    {
        private:
            std::string _V_file_path;
            std::vector<std::string> _V_data;
        public:
            void set_path(std::string new_path);
            std::string get_path();
            bool load();
            bool save();
            void clear();
            bool insert_line(unsigned int insert_position,unsigned int total_of_new_lines);
            bool remove_line(unsigned int remove_position);
            unsigned int size();
            std::string& operator [] (unsigned int line_position);
            ~TextFile();
    };
}

#endif // INCLUDED_LL_FILE_H
