#ifndef INCLUDED_LL_AL5_VIDEO_H
#define INCLUDED_LL_AL5_VIDEO_H

#include <string>
#include "Bitmap.h"

namespace LL_AL5
{
    class Video:public BitmapBase
    {
        private:
            ALLEGRO_VIDEO* _V_video=nullptr;
            float _V_size_x=0;
            float _V_size_y=0;
            std::string _V_video_path;
        public:
            void set_path(std::string new_video_path)
            {
                _V_video_path=new_video_path;
            }
            std::string get_path()
            {
                return _V_video_path;
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
                if(!al_reserve_samples(1))
                    return false;
                _V_video=al_open_video(_V_video_path.c_str());
                if(_V_video)
                {
                    _V_size_x=al_get_video_scaled_width(_V_video);
                    _V_size_y=al_get_video_scaled_height(_V_video);
                    return true;
                }
                return false;
            }
            bool destroy()
            {
                if(_V_video)
                {
                    al_close_video(_V_video);
                    _V_video=nullptr;
                    return true;
                }
                return false;
            }
            double get_video_position(ALLEGRO_VIDEO_POSITION_TYPE reference_position=ALLEGRO_VIDEO_POSITION_ACTUAL)
            {
                return al_get_video_position(_V_video,reference_position);
            }
            void start()
            {
                al_start_video(_V_video,al_get_default_mixer());
            }
            bool is_playing()
            {
                return al_is_video_playing(_V_video);
            }
            void stop()
            {
                pause();
                al_seek_video(_V_video,0);
            }
            void pause()
            {
                if(is_playing())
                    al_set_video_playing(_V_video,false);
            }
            void play()
            {
                if(!is_playing())
                    al_set_video_playing(_V_video,true);
            }
            void draw()
            {
                ALLEGRO_BITMAP* bitmap=al_get_video_frame(_V_video);
                if(bitmap)
                {
                    const Type_pos size_in_axe_x=(_V_size_x*bitmap_scale_x*_V_scale_x);
                    const Type_pos size_in_axe_y=(_V_size_y*bitmap_scale_y*_V_scale_y);
                    al_draw_scaled_rotated_bitmap(bitmap,_V_size_x/2,_V_size_y/2,
                                                  _V_pos_x+(!_V_centering_option_x*(size_in_axe_x/2)),
                                                  _V_pos_y+(!_V_centering_option_y*(size_in_axe_y/2)),
                                                  bitmap_scale_x*_V_scale_x,bitmap_scale_y*_V_scale_y,
                                                  _V_angle,_V_flag);
                }
            }
            operator ALLEGRO_VIDEO* ()
            {
                return _V_video;
            }
            ~Video()
            {
                destroy();
            }
    };
}

#endif // INCLUDED_LL_AL5_VIDEO_H
