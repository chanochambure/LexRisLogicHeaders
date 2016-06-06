#ifndef INCLUDED_LL_MATH_H
#define INCLUDED_LL_MATH_H

#include <math.h>
#include <random>

namespace LL
{
    const double MATH_PI=3.14159265358979323846;

    int mod(int dividend,int divisor)
    {
        return ((dividend%divisor)+divisor)%divisor;
    }

    double range_mod(double dividend,double divisor)
    {
        return fmod(fmod(dividend,divisor)+divisor,divisor);
    }

    float sexagesimal_to_radian(float sexagesimal)
    {
        return (sexagesimal*MATH_PI)/180;
    }

    float radian_to_sexagesimal(float radian)
    {
        return (radian*180)/MATH_PI;
    }

    void random_generate_new_seed()
    {
        uint32_t asm_a,asm_d;
        __asm__ __volatile__("rdtsc":"=a"(asm_a),"=d"(asm_d));
        srand(((uint64_t)asm_a | ((uint64_t)asm_d)<<32));
    }

    int random(int min_value,int max_value,bool include_max_value=false)
    {
        return mod(rand(),(max_value-min_value+include_max_value))+min_value;
    }

    bool segment_collision(float ini_segment_1,float fin_segment_1,float ini_segment_2,float fin_segment_2)
    {
        int ini_segment=std::max(ini_segment_1,ini_segment_2);
        int fin_segment=std::min(fin_segment_1,fin_segment_2);
        return (ini_segment<=fin_segment);
    }

    int max_integer(float number)
    {
        return (int(number)-(number<0));
    }
}

#endif // INCLUDED_LL_MATH_H
