#ifndef LL_PATH_H_INCLUDED
#define LL_PATH_H_INCLUDED

#include <string>

using namespace std;

string get_current_absolute_directory()
{
    char* _dir=al_get_current_directory();
    string dir;
    if(_dir)
    {
        dir=_dir;
        al_free(_dir);
    }
    return dir;
}

bool change_directory(string path)
{
    return al_change_directory(path.c_str());
}

bool make_directory(string dir)
{
    return al_make_directory(dir.c_str());
}

bool path_exists(string path)
{
    return al_filename_exists(path.c_str());
}

bool remove_filename(string path)
{
    return al_remove_filename(path.c_str());
}

#endif // LL_PATH_H_INCLUDED
