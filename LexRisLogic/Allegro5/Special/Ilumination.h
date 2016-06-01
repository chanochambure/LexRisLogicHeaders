#ifndef INCLUDED_LL_AL5_ILUMINATION_H
#define INCLUDED_LL_AL5_ILUMINATION_H

#include "../Primitives.h"

namespace LL_AL5
{
    template<typename FIGURE>
    class Ilumination
    {
        protected:
            FIGURE _V_figure;
        public:
            void set_pos(Type_pos pos_x,Type_pos pos_y)
            {
                _V_figure.set_pos(pos_x,pos_y);
            }
            void set_pos_x(Type_pos pos_x)
            {
                _V_figure.set_pos_x(pos_x);
            }
            void set_pos_y(Type_pos pos_y)
            {
                _V_figure.set_pos_y(pos_y);
            }
            Type_pos get_pos_x()
            {
                return _V_figure.get_pos_x();
            }
            Type_pos get_pos_y()
            {
                return _V_figure.get_pos_y();
            }
            void draw()
            {
                _V_figure.draw();
            }
            void draw_in_another_target()
            {
                _V_figure.draw_in_another_target();
            }
            FIGURE& get_figure()
            {
                return _V_figure;
            }
    };

    template<typename FIGURE>
    class Light:public Ilumination<FIGURE>
    {
        private:
            Color color;
            Color _V_figure_color;
            float intensity=0;
        public:
            Light()
            {
                this->_V_figure.set_filled_status(true);
                this->_V_figure.set_thickness(0);
                color.alpha=_V_figure_color.alpha=0;
            }
            bool set_intensity(float new_intensity)
            {
                if(new_intensity>1 or new_intensity<0)
                    return false;
                intensity=new_intensity;
                _V_figure_color.red=color.red*intensity;
                _V_figure_color.green=color.green*intensity;
                _V_figure_color.blue=color.blue*intensity;
                _V_figure_color.alpha=0;
                this->_V_figure.set_color(_V_figure_color);
                return true;
            }
            float get_intensity(){return intensity;}
            void set_color(Color new_color)
            {
                color=new_color;
                _V_figure_color.red=color.red*intensity;
                _V_figure_color.green=color.green*intensity;
                _V_figure_color.blue=color.blue*intensity;
                color.alpha=_V_figure_color.alpha=0;
                this->_V_figure.set_color(_V_figure_color);
            }
            Color get_color(){return color;}
    };

    template<typename FIGURE>
    class Shade:public Ilumination<FIGURE>
    {
        private:
            Color shadow;
            float intensity=0;
        public:
            Shade()
            {
                this->_V_figure.set_filled_status(true);
                this->_V_figure.set_thickness(0);
                shadow.alpha=0;
                this->_V_figure.set_color(shadow);
            }
            bool set_intensity(float new_intensity)
            {
                if(new_intensity>1 or new_intensity<0)
                    return false;
                intensity=new_intensity;
                shadow.alpha=255*intensity;
                this->_V_figure.set_color(shadow);
                return true;
            }
            float get_intensity(){return intensity;}
    };
}

#endif // INCLUDED_LL_AL5_ILUMINATION_H
