#ifndef INCLUDED_LL_AL5_DISPLAY_H
#define INCLUDED_LL_AL5_DISPLAY_H

#include <string>

namespace LL_AL5
{
    class Display
    {
        private:
            ALLEGRO_DISPLAY* _V_display=nullptr;
            ALLEGRO_MOUSE_CURSOR* _V_cursor=nullptr;
            Type_display_size _V_size_x;
            Type_display_size _V_size_y;
            Type_display_size _V_real_size_x;
            Type_display_size _V_real_size_y;
            Type_display_size _V_last_size_x=1;
            Type_display_size _V_last_size_y=1;
            Type_pos _V_cam_pos_x=0;
            Type_pos _V_cam_pos_y=0;
            int _V_display_mode=ALLEGRO_WINDOWED;
            void _F_destroy()
            {
                if(_V_display)
                {
                    al_destroy_display(_V_display);
                    _V_display=nullptr;
                }
            }
            void _F_create()
            {
                _F_destroy();
                al_set_new_display_flags(_V_display_mode);
                _V_display=al_create_display(_V_size_x,_V_size_y);
                al_flip_display();
            }
            void _F_set_global_scale()
            {
                _V_cam_pos_x=((_V_cam_pos_x*_V_size_x)/(_V_last_size_x));
                _V_cam_pos_y=((_V_cam_pos_y*_V_size_y)/(_V_last_size_y));
                _V_last_size_x=_V_size_x;
                _V_last_size_y=_V_size_y;
                bitmap_scale_x=float(_V_size_x)/_V_real_size_x;
                bitmap_scale_y=float(_V_size_y)/_V_real_size_y;
                text_scale=((bitmap_scale_x-bitmap_scale_y)/2)+bitmap_scale_y;
                if(text_scale<1)
                    primitives_scale=1;
                else
                    primitives_scale=text_scale;
            }
        public:
            Display(Type_display_size size_x,Type_display_size size_y)
            {
                _V_real_size_x=_V_size_x=size_x;
                _V_real_size_y=_V_size_y=size_y;
                _F_create();
                _F_set_global_scale();
            }
            Display(Type_display_size size_x,Type_display_size size_y,
                    Type_display_size real_size_x,Type_display_size real_size_y)
            {
                _V_size_x=size_x;
                _V_size_y=size_y;
                _V_real_size_x=real_size_x;
                _V_real_size_y=real_size_y;
                _F_create();
                _F_set_global_scale();
            }
            void set_title(std::string new_title)
            {
                al_set_window_title(_V_display,new_title.c_str());
            }
            Type_display_size get_size_x()
            {
                return _V_size_x;
            }
            Type_display_size get_size_y()
            {
                return _V_size_y;
            }
            void set_real_size(Type_display_size real_size_x,Type_display_size real_size_y)
            {
                _V_real_size_x=real_size_x;
                _V_real_size_y=real_size_y;
                _F_set_global_scale();
            }
            Type_display_size get_real_size_x()
            {
                return _V_real_size_x;
            }
            Type_display_size get_real_size_y()
            {
                return _V_real_size_y;
            }
            void set_flag(int new_flag)
            {
                _V_display_mode=new_flag;
                _F_create();
            }
            void resize(Type_display_size size_x,Type_display_size size_y)
            {
                _V_size_x=size_x;
                _V_size_y=size_y;
                al_resize_display(_V_display,_V_size_x,_V_size_y);
                _F_set_global_scale();
            }
            void set_cam(Type_pos new_pos_x,Type_pos new_pos_y)
            {
                _V_cam_pos_x=(new_pos_x*bitmap_scale_x);
                _V_cam_pos_y=(new_pos_y*bitmap_scale_y);
            }
            void set_cam_x(Type_pos new_pos_x)
            {
                _V_cam_pos_x=(new_pos_x*bitmap_scale_x);
            }
            Type_pos get_cam_x()
            {
                return _V_cam_pos_x/bitmap_scale_x;
            }
            void set_cam_y(Type_pos new_pos_y)
            {
                _V_cam_pos_y=(new_pos_y*bitmap_scale_y);
            }
            Type_pos get_cam_y()
            {
                return _V_cam_pos_y/bitmap_scale_y;
            }
            void plus_cam_x(Type_pos plus_x)
            {
                _V_cam_pos_x+=(plus_x*bitmap_scale_x);
            }
            void plus_cam_y(Type_pos plus_y)
            {
                _V_cam_pos_y+=(plus_y*bitmap_scale_y);
            }
            Type_pos display_to_real_pos_x(Type_pos pos_x,bool references_axes=true)
            {
                return (pos_x+(_V_cam_pos_x*references_axes))/bitmap_scale_x;
            }
            Type_pos display_to_real_pos_y(Type_pos pos_y,bool references_axes=true)
            {
                return (pos_y+(_V_cam_pos_y*references_axes))/bitmap_scale_y;
            }
            bool show_cursor()
            {
                return al_show_mouse_cursor(_V_display);
            }
            bool hide_cursor()
            {
                return al_hide_mouse_cursor(_V_display);
            }
            bool set_cursor(ALLEGRO_BITMAP* bitmap_cursor,int focus_x,int focus_y)
            {
                destroy_cursor();
                if((_V_cursor=al_create_mouse_cursor(bitmap_cursor,focus_x,focus_y)))
                    return al_set_mouse_cursor(_V_display,_V_cursor);
                return false;
            }
            bool destroy_cursor()
            {
                if(_V_cursor)
                {
                    al_destroy_mouse_cursor(_V_cursor);
                    _V_cursor=nullptr;
                    return true;
                }
                return false;
            }
            void clear()
            {
                al_clear_to_color(al_map_rgb(255,255,255));
            }
            void clear_to_color(ALLEGRO_COLOR color)
            {
                al_clear_to_color(color);
            }
            template<typename T>
            void draw(T* object,bool references_axes=true)
            {
                Type_pos data_pos_x=object->get_pos_x();
                Type_pos data_pos_y=object->get_pos_y();
                object->set_pos(((data_pos_x)*(bitmap_scale_x)-(_V_cam_pos_x*references_axes)),
                              ((data_pos_y)*(bitmap_scale_y)-(_V_cam_pos_y*references_axes)));
                object->draw();
                object->set_pos(data_pos_x,data_pos_y);
            }
            void refresh()
            {
                al_flip_display();
            }
            void set_target()
            {
                al_set_target_backbuffer(_V_display);
                _F_set_global_scale();
            }
            operator ALLEGRO_DISPLAY*& ()
            {
                return _V_display;
            }
            operator ALLEGRO_BITMAP* ()
            {
                return al_get_backbuffer(_V_display);
            }
            operator ALLEGRO_MOUSE_CURSOR* ()
            {
                return _V_cursor;
            }
            ~Display()
            {
                destroy_cursor();
                _F_destroy();
            }
    };
}

#endif // INCLUDED_LL_AL5_DISPLAY_H
