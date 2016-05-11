#ifndef INCLUDED_LL_AL5_PATH_H
#define INCLUDED_LL_AL5_PATH_H

#include <string>

namespace LL_AL5
{
    std::string get_current_absolute_directory()
    {
        char* _dir=al_get_current_directory();
        std::string dir;
        if(_dir)
        {
            dir=_dir;
            al_free(_dir);
        }
        return dir;
    }

    bool change_directory(std::string path)
    {
        return al_change_directory(path.c_str());
    }

    bool make_directory(std::string dir)
    {
        return al_make_directory(dir.c_str());
    }

    bool path_exists(std::string path)
    {
        return al_filename_exists(path.c_str());
    }

    bool remove_filename(std::string path)
    {
        return al_remove_filename(path.c_str());
    }
}

#endif // INCLUDED_LL_AL5_PATH_H
