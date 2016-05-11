#ifndef INCLUDED_LL_AL5_LIGHTING_H
#define INCLUDED_LL_AL5_LIGHTING_H

#include "../Primitives.h"

namespace LL_AL5
{
    template<typename LL_Figure_Derivative>
    class Lighting
    {
        protected:
            LL_Figure_Derivative figure;
        public:
            void set_pos(Type_pos x,Type_pos y){figure.set_pos(x,y);}
            void set_posx(Type_pos x){figure.set_posx(x);}
            void set_posy(Type_pos y){figure.set_posy(y);}
            Type_pos get_posx(){return figure.get_posx();}
            Type_pos get_posy(){return figure.get_posy();}
            void draw(){figure.draw();}
            void draw_in_another_target(){figure.draw_in_another_target();}
            LL_Figure_Derivative& get_figure(){return figure;}
    };

    template<typename LL_Figure_Derivative>
    class LL_Light:public Lighting<LL_Figure_Derivative>
    {
        private:
            Color color;
            Color figure_color;
            float intensity=0;
        public:
            LL_Light()
            {
                this->figure.set_thickness(0);
                this->figure.set_is_filled(1);
                color.alpha=figure_color.alpha=0;
            }
            bool set_intensity(float new_intensity)
            {
                if(new_intensity>1 or new_intensity<0)
                    return 0;
                intensity=new_intensity;
                figure_color.red=color.red*intensity;
                figure_color.green=color.green*intensity;
                figure_color.blue=color.blue*intensity;
                figure_color.alpha=0;
                this->figure.set_color(figure_color);
                return 1;
            }
            float get_intensity(){return intensity;}
            void set_color(Color new_color)
            {
                color=new_color;
                figure_color.red=color.red*intensity;
                figure_color.green=color.green*intensity;
                figure_color.blue=color.blue*intensity;
                color.alpha=figure_color.alpha=0;
                this->figure.set_color(figure_color);
            }
            Color get_color(){return color;}
    };

    template<typename LL_Figure_Derivative>
    class LL_Shade:public Lighting<LL_Figure_Derivative>
    {
        private:
            Color shadow;
            float intensity=0;
        public:
            LL_Shade()
            {
                this->figure.set_thickness(0);
                this->figure.set_is_filled(1);
                shadow.alpha=0;
                this->figure.set_color(shadow);
            }
            bool set_intensity(float new_intensity)
            {
                if(new_intensity>1 or new_intensity<0)
                    return 0;
                intensity=new_intensity;
                shadow.alpha=255*intensity;
                this->figure.set_color(shadow);
                return 1;
            }
            float get_intensity(){return intensity;}
    };
}

#endif // INCLUDED_LL_AL5_LIGHTING_H
