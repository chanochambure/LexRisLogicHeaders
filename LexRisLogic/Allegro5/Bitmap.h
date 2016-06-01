#ifndef INCLUDED_LL_AL5_BITMAP_H
#define INCLUDED_LL_AL5_BITMAP_H

#include <string>

namespace LL_AL5
{
    bool save_bitmap(std::string bitmap_file_name,ALLEGRO_BITMAP* bitmap)
    {
        return al_save_bitmap(bitmap_file_name.c_str(),bitmap);
    }

    class BitmapBase
    {
        protected:
            int _V_flag=0;
            float _V_angle=0;
            Type_pos _V_pos_x=0;
            Type_pos _V_pos_y=0;
            float _V_scale_x=1;
            float _V_scale_y=1;
            bool _V_centering_option_x=false;
            bool _V_centering_option_y=false;
        public:
            void set_pos(Type_pos new_pos_x,Type_pos new_pos_y)
            {
                _V_pos_x=new_pos_x;
                _V_pos_y=new_pos_y;
            }
            void set_pos_x(Type_pos new_pos_x)
            {
                _V_pos_x=new_pos_x;
            }
            Type_pos get_pos_x()
            {
                return _V_pos_x;
            }
            void set_pos_y(Type_pos new_pos_y)
            {
                _V_pos_y=new_pos_y;
            }
            Type_pos get_pos_y()
            {
                return _V_pos_y;
            }
            void set_angle(float new_angle)
            {
                _V_angle=new_angle;
            }
            float get_angle()
            {
                return _V_angle;
            }
            void set_flag(int new_flag)
            {
                _V_flag=new_flag;
            }
            void set_scale_x(float new_scale_x)
            {
                _V_scale_x=new_scale_x;
            }
            float get_scale_x()
            {
                return _V_scale_x;
            }
            void set_scale_y(float new_scale_y)
            {
                _V_scale_y=new_scale_y;
            }
            float get_scale_y()
            {
                return _V_scale_y;
            }
            void set_centering_option(bool new_centering_option_x,bool new_centering_option_y)
            {
                _V_centering_option_x=new_centering_option_x;
                _V_centering_option_y=new_centering_option_y;
            }
            bool get_centering_option_x()
            {
                return _V_centering_option_x;
            }
            bool get_centering_option_y()
            {
                return _V_centering_option_y;
            }
    };

    class Bitmap:public BitmapBase
    {
        protected:
            ALLEGRO_BITMAP* _V_bitmap=nullptr;
            float _V_size_x=0;
            float _V_size_y=0;
        public:
            float get_size_x()
            {
                return _V_size_x;
            }
            float get_size_y()
            {
                return _V_size_y;
            }
            bool create(int size_x,int size_y)
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
            bool destroy()
            {
                if(_V_bitmap)
                {
                    al_destroy_bitmap(_V_bitmap);
                    _V_bitmap=nullptr;
                    return true;
                }
                return false;
            }
            void set_target()
            {
                if(_V_bitmap)
                    al_set_target_bitmap(_V_bitmap);
            }
            bool lock()
            {
                return al_lock_bitmap(_V_bitmap,ALLEGRO_LOCK_READWRITE,ALLEGRO_PIXEL_FORMAT_ANY);
            }
            void unlock()
            {
                al_unlock_bitmap(_V_bitmap);
            }
            ALLEGRO_COLOR get_pixel_color(Type_pos pos_x,Type_pos pos_y)
            {
                return al_get_pixel(_V_bitmap,pos_x,pos_y);
            }
            void draw()
            {
                const Type_pos size_in_axe_x=(_V_size_x*bitmap_scale_x*_V_scale_x);
                const Type_pos size_in_axe_y=(_V_size_y*bitmap_scale_y*_V_scale_y);
                al_draw_scaled_rotated_bitmap(_V_bitmap,_V_size_x/2,_V_size_y/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,_V_angle,_V_flag);
            }
            void draw_in_another_target()
            {
                const Type_pos size_in_axe_x=(_V_size_x*_V_scale_x);
                const Type_pos size_in_axe_y=(_V_size_y*_V_scale_y);
                al_draw_scaled_rotated_bitmap(_V_bitmap,_V_size_x/2,_V_size_y/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              _V_scale_x,_V_scale_y,_V_angle,_V_flag);
            }
            operator ALLEGRO_BITMAP* ()
            {
                return _V_bitmap;
            }
            ~Bitmap()
            {
                destroy();
            }
    };

    class SubBitmap:public BitmapBase
    {
        private:
            ALLEGRO_BITMAP* _V_parent_bitmap=nullptr;
            ALLEGRO_BITMAP* _V_bitmap=nullptr;
            Type_pos _V_sub_x=0;
            Type_pos _V_sub_y=0;
            float _V_size_x=0;
            float _V_size_y=0;
        public:
            void set_parent_bitmap(ALLEGRO_BITMAP* new_parent_bitmap)
            {
                destroy();
                _V_parent_bitmap=new_parent_bitmap;
            }
            ALLEGRO_BITMAP* get_parent_bitmap()
            {
                return _V_parent_bitmap;
            }
            void set_sub_x(Type_pos new_sub_x)
            {
                _V_sub_x=new_sub_x;
            }
            Type_pos get_sub_x()
            {
                return _V_sub_x;
            }
            void set_sub_y(Type_pos new_sub_y)
            {
                _V_sub_y=new_sub_y;
            }
            Type_pos get_sub_y()
            {
                return _V_sub_y;
            }
            void set_size_x(int new_size_x)
            {
                _V_size_x=new_size_x;
            }
            float get_size_x()
            {
                return _V_size_x;
            }
            void set_size_y(int new_size_y)
            {
                _V_size_y=new_size_y;
            }
            float get_size_y()
            {
                return _V_size_y;
            }
            bool create()
            {
                destroy();
                if(_V_parent_bitmap)
                {
                    _V_bitmap=al_create_sub_bitmap(_V_parent_bitmap,_V_sub_x,_V_sub_y,_V_size_x,_V_size_y);
                    return _V_bitmap;
                }
                return false;
            }
            bool destroy()
            {
                if(_V_bitmap)
                {
                    al_destroy_bitmap(_V_bitmap);
                    _V_bitmap=nullptr;
                    return true;
                }
                return false;
            }
            void set_target()
            {
                if(_V_bitmap)
                    al_set_target_bitmap(_V_bitmap);
            }
            bool lock()
            {
                return al_lock_bitmap(_V_bitmap,ALLEGRO_LOCK_READWRITE,ALLEGRO_PIXEL_FORMAT_ANY);
            }
            void unlock()
            {
                al_unlock_bitmap(_V_bitmap);
            }
            ALLEGRO_COLOR get_pixel_color(Type_pos pos_x,Type_pos pos_y)
            {
                return al_get_pixel(_V_bitmap,pos_x,pos_y);
            }
            void draw()
            {
                const Type_pos size_in_axe_x=(_V_size_x*bitmap_scale_x*_V_scale_x);
                const Type_pos size_in_axe_y=(_V_size_y*bitmap_scale_y*_V_scale_y);
                al_draw_scaled_rotated_bitmap(_V_bitmap,_V_size_x/2,_V_size_y/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,_V_angle,_V_flag);
            }
            void draw_in_another_target()
            {
                const Type_pos size_in_axe_x=(_V_size_x*_V_scale_x);
                const Type_pos size_in_axe_y=(_V_size_y*_V_scale_y);
                al_draw_scaled_rotated_bitmap(_V_bitmap,_V_size_x/2,_V_size_y/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              _V_scale_x,_V_scale_y,_V_angle,_V_flag);
            }
            operator ALLEGRO_BITMAP* ()
            {
                return _V_bitmap;
            }
            ~SubBitmap()
            {
                destroy();
            }
    };

    class Image:public BitmapBase
    {
        private:
            ALLEGRO_BITMAP* _V_bitmap=nullptr;
            std::string _V_image_path;
            float _V_size_x=0;
            float _V_size_y=0;
        public:
            void set_path(std::string new_image_path)
            {
                _V_image_path=new_image_path;
            }
            std::string get_path()
            {
                return _V_image_path;
            }
            float get_size_x()
            {
                return _V_size_x;
            }
            float get_size_y()
            {
                return _V_size_y;
            }
            bool load()
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
            bool save()
            {
                if(_V_bitmap)
                    return save_bitmap(_V_image_path,_V_bitmap);
                return false;
            }
            bool destroy()
            {
                if(_V_bitmap)
                {
                    al_destroy_bitmap(_V_bitmap);
                    _V_bitmap=nullptr;
                    return true;
                }
                return false;
            }
            void set_target()
            {
                if(_V_bitmap)
                    al_set_target_bitmap(_V_bitmap);
            }
            bool lock()
            {
                return al_lock_bitmap(_V_bitmap,ALLEGRO_LOCK_READWRITE,ALLEGRO_PIXEL_FORMAT_ANY);
            }
            void unlock()
            {
                al_unlock_bitmap(_V_bitmap);
            }
            ALLEGRO_COLOR get_pixel_color(Type_pos pos_x,Type_pos pos_y)
            {
                return al_get_pixel(_V_bitmap,pos_x,pos_y);
            }
            void draw()
            {
                const Type_pos size_in_axe_x=(_V_size_x*bitmap_scale_x*_V_scale_x);
                const Type_pos size_in_axe_y=(_V_size_y*bitmap_scale_y*_V_scale_y);
                al_draw_scaled_rotated_bitmap(_V_bitmap,_V_size_x/2,_V_size_y/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,_V_angle,_V_flag);
            }
            void draw_in_another_target()
            {
                const Type_pos size_in_axe_x=(_V_size_x*_V_scale_x);
                const Type_pos size_in_axe_y=(_V_size_y*_V_scale_y);
                al_draw_scaled_rotated_bitmap(_V_bitmap,_V_size_x/2,_V_size_y/2,
                                              _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                              _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                              _V_scale_x,_V_scale_y,_V_angle,_V_flag);
            }
            operator ALLEGRO_BITMAP* ()
            {
                return _V_bitmap;
            }
            ~Image()
            {
                destroy();
            }
    };
}

#endif // INCLUDED_LL_AL5_BITMAP_H
