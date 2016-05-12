#ifndef INCLUDED_LL_AL5_PATH_H
#define INCLUDED_LL_AL5_PATH_H

#include <string>

namespace LL_AL5
{
    std::string get_current_directory()
    {
        char* actual_dir=al_get_current_directory();
        std::string return_dir;
        if(actual_dir)
        {
            return_dir=actual_dir;
            al_free(actual_dir);
        }
        return return_dir;
    }

    bool change_directory(std::string new_path)
    {
        return al_change_directory(new_path.c_str());
    }

    bool make_directory(std::string new_dir)
    {
        return al_make_directory(new_dir.c_str());
    }

    bool path_exists(std::string path)
    {
        return al_filename_exists(path.c_str());
    }

    bool remove_path(std::string path)
    {
        return al_remove_filename(path.c_str());
    }
}

#endif // INCLUDED_LL_AL5_PATH_H
