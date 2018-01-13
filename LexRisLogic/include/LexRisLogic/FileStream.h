/* FileStream.h -- File Stream Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_FILESTREAM_H
#define INCLUDED_LL_FILESTREAM_H

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
            std::vector<std::string> _V_data;
        public:
            void set_path(std::string new_path);
            std::string get_path();
            bool load();
            bool save();
            void clear_file();
            bool insert_line(unsigned int insert_position,unsigned int total_of_new_lines);
            bool remove_line(unsigned int remove_position);
            unsigned int size();
            std::string& operator [] (unsigned int line_position);
            ~FileStream();
    };
}

#endif // INCLUDED_LL_FILESTREAM_H
