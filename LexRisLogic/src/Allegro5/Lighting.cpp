/* Lighting.cpp -- Lighting Allegro 5 Source - LexRis Logic Headers

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

#include "../../include/Allegro5/Lighting.h"

namespace LL_AL5
{
    Lighting::Lighting()
    {
        al_get_blender(&_V_blend_mode,&_V_blend_source_value,&_V_blend_destination_value);
    }
    void Lighting::set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
    {
        _V_pos_x=new_pos_x;
        _V_pos_y=new_pos_y;
    }
    void Lighting::set_pos_x(Type_pos new_pos_x)
    {
        _V_pos_x=new_pos_x;
    }
    Type_pos Lighting::get_pos_x()
    {
        return _V_pos_x;
    }
    void Lighting::set_pos_y(Type_pos new_pos_y)
    {
        _V_pos_y=new_pos_y;
    }
    Type_pos Lighting::get_pos_y()
    {
        return _V_pos_y;
    }
    float Lighting::get_size_x()
    {
        return _V_size_x;
    }
    float Lighting::get_size_y()
    {
        return _V_size_y;
    }
    bool Lighting::create(int size_x,int size_y)
    {
        destroy();
        _V_lighting_buffer=al_create_bitmap(size_x,size_y);
        if(_V_lighting_buffer)
        {
            _V_size_x=size_x;
            _V_size_y=size_y;
            return true;
        }
        return false;
    }
    bool Lighting::destroy()
    {
        if(_V_lighting_buffer)
        {
            al_destroy_bitmap(_V_lighting_buffer);
            _V_lighting_buffer=nullptr;
            return true;
        }
        return false;
    }
    void Lighting::set_target()
    {
        if(_V_lighting_buffer)
            al_set_target_bitmap(_V_lighting_buffer);
    }
    void Lighting::clear(float intensity)
    {
        al_set_blender(ALLEGRO_SRC_MINUS_DEST, ALLEGRO_ONE, ALLEGRO_ZERO);
        al_set_blender(_V_blend_mode, _V_blend_source_value, _V_blend_destination_value);
    }
    float Lighting::get_pixel_intensity(Type_pos pos_x,Type_pos pos_y)
    {
        return al_get_pixel(_V_lighting_buffer,pos_x,pos_y).a;
    }
    void Lighting::draw()
    {
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ZERO, ALLEGRO_ALPHA);
        al_draw_scaled_bitmap(_V_lighting_buffer,0,0,_V_size_x,_V_size_y,_V_pos_x,_V_pos_y,
                              _V_size_x*bitmap_scale_x,_V_size_y*bitmap_scale_y,0);
        al_set_blender(_V_blend_mode, _V_blend_source_value, _V_blend_destination_value);
    }
    void Lighting::draw_in_another_target()
    {
        al_set_blender(ALLEGRO_ADD, ALLEGRO_ZERO, ALLEGRO_ALPHA);
        al_draw_bitmap(_V_lighting_buffer,_V_pos_x,_V_pos_y,0);
        al_set_blender(_V_blend_mode, _V_blend_source_value, _V_blend_destination_value);
    }
    Lighting::operator ALLEGRO_BITMAP* ()
    {
        return _V_lighting_buffer;
    }
    Lighting::~Lighting()
    {
        destroy();
    }
}
