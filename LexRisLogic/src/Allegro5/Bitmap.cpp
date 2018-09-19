/* Bitmap.cpp -- Bitmap Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/Allegro5/Bitmap.h"

namespace LL_AL5
{
    bool LL_SHARED image_addon()
    {
        return al_init_image_addon();
    }
    bool LL_SHARED save_bitmap(std::string bitmap_file_name,ALLEGRO_BITMAP* bitmap)
    {
        return al_save_bitmap(bitmap_file_name.c_str(),bitmap);
    }
    void LL_SHARED disable_premultiplied_alpha()
    {
        al_set_new_bitmap_flags(ALLEGRO_NO_PREMULTIPLIED_ALPHA);
    }

    BitmapBase::BitmapBase()
    {
        _V_tint_color=al_map_rgb(255,255,255);
    }
    void BitmapBase::set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
    {
        _V_pos_x=new_pos_x;
        _V_pos_y=new_pos_y;
    }
    void BitmapBase::set_pos_x(Type_pos new_pos_x)
    {
        _V_pos_x=new_pos_x;
    }
    Type_pos BitmapBase::get_pos_x()
    {
        return _V_pos_x;
    }
    void BitmapBase::set_pos_y(Type_pos new_pos_y)
    {
        _V_pos_y=new_pos_y;
    }
    Type_pos BitmapBase::get_pos_y()
    {
        return _V_pos_y;
    }
    void BitmapBase::set_angle(float new_angle)
    {
        _V_angle=new_angle;
    }
    float BitmapBase::get_angle()
    {
        return _V_angle;
    }
    void BitmapBase::set_flag(int new_flag)
    {
        _V_flag=new_flag;
    }
    void BitmapBase::set_scale_x(float new_scale_x)
    {
        _V_scale_x=new_scale_x;
    }
    float BitmapBase::get_scale_x()
    {
        return _V_scale_x;
    }
    void BitmapBase::set_scale_y(float new_scale_y)
    {
        _V_scale_y=new_scale_y;
    }
    float BitmapBase::get_scale_y()
    {
        return _V_scale_y;
    }
    void BitmapBase::set_anchor(float new_anchor_x,float new_anchor_y)
    {
        _V_anchor_x=new_anchor_x;
        _V_anchor_y=new_anchor_y;
    }
    float BitmapBase::get_anchor_x()
    {
        return _V_anchor_x;
    }
    float BitmapBase::get_anchor_y()
    {
        return _V_anchor_y;
    }
    void BitmapBase::set_tint_color(ALLEGRO_COLOR new_color)
    {
        _V_tint_color=new_color;
    }
    ALLEGRO_COLOR BitmapBase::get_tint_color()
    {
        return _V_tint_color;
    }

    Bitmap::Bitmap()
    {
    }
    float Bitmap::get_size_x()
    {
        return _V_size_x;
    }
    float Bitmap::get_size_y()
    {
        return _V_size_y;
    }
    bool Bitmap::create(int size_x,int size_y)
    {
        destroy();
        _V_bitmap=al_create_bitmap(size_x,size_y);
        if(_V_bitmap)
        {
            _V_size_x=size_x;
            _V_size_y=size_y;
            return true;
        }
        return false;
    }
    bool Bitmap::clone(ALLEGRO_BITMAP* base_bitmap)
    {
        if(base_bitmap)
        {
            destroy();
            _V_bitmap=al_clone_bitmap(base_bitmap);
            if(_V_bitmap)
            {
                _V_size_x=al_get_bitmap_width(_V_bitmap);
                _V_size_y=al_get_bitmap_height(_V_bitmap);
                return true;
            }
        }
        return false;
    }
    bool Bitmap::destroy()
    {
        if(_V_bitmap)
        {
            al_destroy_bitmap(_V_bitmap);
            _V_bitmap=nullptr;
            return true;
        }
        return false;
    }
    void Bitmap::set_target()
    {
        if(_V_bitmap)
            al_set_target_bitmap(_V_bitmap);
    }
    bool Bitmap::lock()
    {
        return al_lock_bitmap(_V_bitmap,ALLEGRO_PIXEL_FORMAT_ANY,ALLEGRO_LOCK_READWRITE);
    }
    void Bitmap::unlock()
    {
        al_unlock_bitmap(_V_bitmap);
    }
    ALLEGRO_COLOR Bitmap::get_pixel_color(Type_pos pos_x,Type_pos pos_y)
    {
        return al_get_pixel(_V_bitmap,pos_x,pos_y);
    }
    void Bitmap::draw()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x*bitmap_scale_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y*bitmap_scale_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap,_V_tint_color,_V_size_x/2,_V_size_y/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,_V_angle,_V_flag);
    }
    void Bitmap::draw_in_another_target()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap,_V_tint_color,_V_size_x/2,_V_size_y/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             _V_scale_x,_V_scale_y,_V_angle,_V_flag);
    }
    Bitmap::operator ALLEGRO_BITMAP* ()
    {
        return _V_bitmap;
    }
    Bitmap::~Bitmap()
    {
        destroy();
    }

    SubBitmap::SubBitmap()
    {
    }
    void SubBitmap::set_parent_bitmap(ALLEGRO_BITMAP* new_parent_bitmap)
    {
        destroy();
        _V_parent_bitmap=new_parent_bitmap;
    }
    ALLEGRO_BITMAP* SubBitmap::get_parent_bitmap()
    {
        return _V_parent_bitmap;
    }
    void SubBitmap::set_sub_x(int new_sub_x)
    {
        _V_sub_x=new_sub_x;
    }
    int SubBitmap::get_sub_x()
    {
        return _V_sub_x;
    }
    void SubBitmap::set_sub_y(int new_sub_y)
    {
        _V_sub_y=new_sub_y;
    }
    int SubBitmap::get_sub_y()
    {
        return _V_sub_y;
    }
    void SubBitmap::set_size_x(float new_size_x)
    {
        _V_size_x=new_size_x;
    }
    float SubBitmap::get_size_x()
    {
        return _V_size_x;
    }
    void SubBitmap::set_size_y(float new_size_y)
    {
        _V_size_y=new_size_y;
    }
    float SubBitmap::get_size_y()
    {
        return _V_size_y;
    }
    bool SubBitmap::create()
    {
        destroy();
        if(_V_parent_bitmap)
        {
            _V_bitmap=al_create_sub_bitmap(_V_parent_bitmap,_V_sub_x,_V_sub_y,_V_size_x,_V_size_y);
            return _V_bitmap;
        }
        return false;
    }
    bool SubBitmap::destroy()
    {
        if(_V_bitmap)
        {
            al_destroy_bitmap(_V_bitmap);
            _V_bitmap=nullptr;
            return true;
        }
        return false;
    }
    void SubBitmap::set_target()
    {
        if(_V_bitmap)
            al_set_target_bitmap(_V_bitmap);
    }
    bool SubBitmap::lock()
    {
        return al_lock_bitmap(_V_bitmap,ALLEGRO_PIXEL_FORMAT_ANY,ALLEGRO_LOCK_READWRITE);
    }
    void SubBitmap::unlock()
    {
        al_unlock_bitmap(_V_bitmap);
    }
    ALLEGRO_COLOR SubBitmap::get_pixel_color(Type_pos pos_x,Type_pos pos_y)
    {
        return al_get_pixel(_V_bitmap,pos_x,pos_y);
    }
    void SubBitmap::draw()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x*bitmap_scale_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y*bitmap_scale_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap,_V_tint_color,_V_size_x/2,_V_size_y/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,_V_angle,_V_flag);
    }
    void SubBitmap::draw_in_another_target()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap,_V_tint_color,_V_size_x/2,_V_size_y/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             _V_scale_x,_V_scale_y,_V_angle,_V_flag);
    }
    SubBitmap::operator ALLEGRO_BITMAP* ()
    {
        return _V_bitmap;
    }
    SubBitmap::~SubBitmap()
    {
        destroy();
    }

    Image::Image()
    {
    }
    void Image::set_path(std::string new_image_path)
    {
        _V_image_path=new_image_path;
    }
    std::string Image::get_path()
    {
        return _V_image_path;
    }
    float Image::get_size_x()
    {
        return _V_size_x;
    }
    float Image::get_size_y()
    {
        return _V_size_y;
    }
    bool Image::load()
    {
        destroy();
        _V_bitmap=al_load_bitmap(_V_image_path.c_str());
        if(_V_bitmap)
        {
            _V_size_x=al_get_bitmap_width(_V_bitmap);
            _V_size_y=al_get_bitmap_height(_V_bitmap);
            return true;
        }
        return false;
    }
    bool Image::save()
    {
        if(_V_bitmap)
            return save_bitmap(_V_image_path,_V_bitmap);
        return false;
    }
    bool Image::destroy()
    {
        if(_V_bitmap)
        {
            al_destroy_bitmap(_V_bitmap);
            _V_bitmap=nullptr;
            return true;
        }
        return false;
    }
    void Image::set_target()
    {
        if(_V_bitmap)
            al_set_target_bitmap(_V_bitmap);
    }
    bool Image::lock()
    {
        return al_lock_bitmap(_V_bitmap,ALLEGRO_PIXEL_FORMAT_ANY,ALLEGRO_LOCK_READWRITE);
    }
    void Image::unlock()
    {
        al_unlock_bitmap(_V_bitmap);
    }
    ALLEGRO_COLOR Image::get_pixel_color(Type_pos pos_x,Type_pos pos_y)
    {
        return al_get_pixel(_V_bitmap,pos_x,pos_y);
    }
    void Image::draw()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x*bitmap_scale_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y*bitmap_scale_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap,_V_tint_color,_V_size_x/2,_V_size_y/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,_V_angle,_V_flag);
    }
    void Image::draw_in_another_target()
    {
        const Type_pos size_in_axe_x=((_V_anchor_x-0.5)*_V_size_x*_V_scale_x);
        const Type_pos size_in_axe_y=((_V_anchor_y-0.5)*_V_size_y*_V_scale_y);
        al_draw_tinted_scaled_rotated_bitmap(_V_bitmap,_V_tint_color,_V_size_x/2,_V_size_y/2,
                                             _V_pos_x-size_in_axe_x,_V_pos_y-size_in_axe_y,
                                             _V_scale_x,_V_scale_y,_V_angle,_V_flag);
    }
    Image::operator ALLEGRO_BITMAP* ()
    {
        return _V_bitmap;
    }
    Image::~Image()
    {
        destroy();
    }
}
