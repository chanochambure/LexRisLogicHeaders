/* Sprite.cpp -- Sprite Allegro 5 Special Source - LexRis Logic Headers

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

#include "../../../include/LexRisLogic/Allegro5/Special/Sprite.h"

namespace LL_AL5
{
    std::string Sprite::_F_int_to_string(unsigned int value)
    {
        std::stringstream string_stream;
        string_stream<<value;
        return string_stream.str();
    }
    float Sprite::get_size_x()
    {
        return _V_size_x[_V_index];
    }
    float Sprite::get_size_y()
    {
        return _V_size_y[_V_index];
    }
    unsigned int Sprite::get_size()
    {
        return _V_size;
    }
    bool Sprite::set_size(unsigned int new_size)
    {
        if(_V_initialised or !new_size)
            return false;
        _V_size=new_size;
        if(_V_index>=_V_size)
            _V_index=0;
        return true;
    }
    bool Sprite::set_selection(unsigned int new_selection)
    {
        if(new_selection<_V_size)
        {
            _V_index=new_selection;
            return true;
        }
        return false;
    }
    unsigned int Sprite::get_selection()
    {
        return _V_index;
    }
    bool Sprite::create()
    {
        if(_V_initialised)
            return false;
        _V_bitmap_set=new ALLEGRO_BITMAP*[_V_size];
        if(!_V_bitmap_set)
            return false;
        _V_size_x=new float[_V_size];
        if(!_V_size_x)
        {
            delete(_V_bitmap_set);
            _V_bitmap_set=nullptr;
            return false;
        }
        _V_size_y=new float[_V_size];
        if(!_V_size_y)
        {
            delete(_V_size_x);
            delete(_V_bitmap_set);
            _V_size_x=nullptr;
            _V_bitmap_set=nullptr;
            return false;
        }
        for(unsigned int i=0;i<_V_size;++i)
        {
            _V_size_x[i]=0.0;
            _V_size_y[i]=0.0;
            _V_bitmap_set[i]=nullptr;
        }
        _V_initialised=true;
        return true;
    }
    bool Sprite::create_selection(int size_x,int size_y)
    {
        if(_V_initialised)
        {
            destroy_selection();
            _V_bitmap_set[_V_index]=al_create_bitmap(size_x,size_y);
            if(_V_bitmap_set[_V_index])
            {
                _V_size_x[_V_index]=size_x;
                _V_size_y[_V_index]=size_y;
                return true;
            }
        }
        return false;
    }
    bool Sprite::destroy_selection()
    {
        if(_V_initialised and _V_bitmap_set[_V_index])
        {
            al_destroy_bitmap(_V_bitmap_set[_V_index]);
            _V_bitmap_set[_V_index]=nullptr;
            _V_size_x[_V_index]=0.0;
            _V_size_y[_V_index]=0.0;
            return true;
        }
        return false;
    }
    bool Sprite::create_data_from_directory(std::string sprites_path,std::string bitmap_format)
    {
        if(_V_initialised)
        {
            destroy_data();
            for(unsigned int i=0;i<_V_size;++i)
            {
                _V_bitmap_set[i]=al_load_bitmap((sprites_path+_F_int_to_string(i+1)+bitmap_format).c_str());
                if(!_V_bitmap_set[i])
                {
                    destroy_data();
                    return false;
                }
                _V_size_x[i]=al_get_bitmap_width(_V_bitmap_set[i]);
                _V_size_y[i]=al_get_bitmap_height(_V_bitmap_set[i]);
            }
            return true;
        }
        return false;
    }
    bool Sprite::destroy_data()
    {
        if(_V_initialised)
        {
            bool return_value=false;
            for(unsigned int i=0;i<_V_size;++i)
            {
                if(_V_bitmap_set[i])
                {
                    return_value=true;
                    _V_size_x[i]=0.0;
                    _V_size_y[i]=0.0;
                    al_destroy_bitmap(_V_bitmap_set[i]);
                    _V_bitmap_set[i]=nullptr;
                }
            }
            return return_value;
        }
        return false;
    }
    bool Sprite::destroy()
    {
        if(_V_initialised)
        {
            destroy_data();
            delete(_V_size_x);
            delete(_V_size_y);
            delete(_V_bitmap_set);
            _V_size_x=nullptr;
            _V_size_y=nullptr;
            _V_bitmap_set=nullptr;
            _V_initialised=false;
            return true;
        }
        return false;
    }
    void Sprite::set_target()
    {
        if(_V_bitmap_set[_V_index])
            al_set_target_bitmap(_V_bitmap_set[_V_index]);
    }
    bool Sprite::lock()
    {
        return al_lock_bitmap(_V_bitmap_set[_V_index],ALLEGRO_LOCK_READWRITE,ALLEGRO_PIXEL_FORMAT_ANY);
    }
    void Sprite::unlock()
    {
        al_unlock_bitmap(_V_bitmap_set[_V_index]);
    }
    ALLEGRO_COLOR Sprite::get_pixel_color(Type_pos pos_x,Type_pos pos_y)
    {
        return al_get_pixel(_V_bitmap_set[_V_index],pos_x,pos_y);
    }
    void Sprite::draw()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x[_V_index]*bitmap_scale_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y[_V_index]*bitmap_scale_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap_set[_V_index],_V_tint_color,
                                             _V_size_x[_V_index]/2,_V_size_y[_V_index]/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,_V_angle,_V_flag);
    }
    void Sprite::draw_in_another_target()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x[_V_index]*bitmap_scale_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y[_V_index]*bitmap_scale_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap_set[_V_index],_V_tint_color,
                                             _V_size_x[_V_index]/2,_V_size_y[_V_index]/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             _V_scale_x,_V_scale_y,_V_angle,_V_flag);
    }
    Sprite::operator ALLEGRO_BITMAP* ()
    {
        return _V_bitmap_set[_V_index];
    }
    Sprite::~Sprite()
    {
        destroy();
    }
}
