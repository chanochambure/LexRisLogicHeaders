#ifndef LL_LIGHTING_H_INCLUDED
#define LL_LIGHTING_H_INCLUDED

template<typename LL_Figure_Derivative>
class LL_Lighting
{
    protected:
        LL_Figure_Derivative figure;
    public:
        void set_pos(pos_t x,pos_t y){figure.set_pos(x,y);}
        void set_posx(pos_t x){figure.set_posx(x);}
        void set_posy(pos_t y){figure.set_posy(y);}
        pos_t get_posx(){return figure.get_posx();}
        pos_t get_posy(){return figure.get_posy();}
        void draw(){figure.draw();}
        void draw_in_another_target(){figure.draw_in_another_target();}
        LL_Figure_Derivative& get_figure(){return figure;}
};

template<typename LL_Figure_Derivative>
class LL_Light:public LL_Lighting<LL_Figure_Derivative>
{
    private:
        LL_Color color;
        LL_Color figure_color;
        float intensity=0;
    public:
        LL_Light()
        {
            this->figure.set_thickness(0);
            this->figure.set_is_filled(1);
            color.Alpha=figure_color.Alpha=0;
        }
        bool set_intensity(float new_intensity)
        {
            if(new_intensity>1 or new_intensity<0)
                return 0;
            intensity=new_intensity;
            figure_color.Red=color.Red*intensity;
            figure_color.Green=color.Green*intensity;
            figure_color.Blue=color.Blue*intensity;
            figure_color.Alpha=0;
            this->figure.set_color(figure_color);
            return 1;
        }
        float get_intensity(){return intensity;}
        void set_color(LL_Color new_color)
        {
            color=new_color;
            figure_color.Red=color.Red*intensity;
            figure_color.Green=color.Green*intensity;
            figure_color.Blue=color.Blue*intensity;
            color.Alpha=figure_color.Alpha=0;
            this->figure.set_color(figure_color);
        }
        LL_Color get_color(){return color;}
};

template<typename LL_Figure_Derivative>
class LL_Shade:public LL_Lighting<LL_Figure_Derivative>
{
    private:
        LL_Color shadow;
        float intensity=0;
    public:
        LL_Shade()
        {
            this->figure.set_thickness(0);
            this->figure.set_is_filled(1);
            shadow.Alpha=0;
            this->figure.set_color(shadow);
        }
        bool set_intensity(float new_intensity)
        {
            if(new_intensity>1 or new_intensity<0)
                return 0;
            intensity=new_intensity;
            shadow.Alpha=255*intensity;
            this->figure.set_color(shadow);
            return 1;
        }
        float get_intensity(){return intensity;}
};

#endif // LL_LIGHTING_H_INCLUDED
