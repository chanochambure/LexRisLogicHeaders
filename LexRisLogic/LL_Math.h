#ifndef LL_MATH_H_INCLUDED
#define LL_MATH_H_INCLUDED

#include <math.h>
#include <random>

//Operations

template<typename T>
T mod(T a,T b){return ((a%b)+b)%b;}

template<typename T>
T range_mod(T a,T b){return fmod(fmod(a,b)+b,b);}

//Angle Conversion

#define MATH_PI 3.14159265358979323846

float sexagesimal_to_radian(float sexagesimal){return (sexagesimal*MATH_PI)/180;}
float radian_to_sexagesimal(float radian){return (radian*180)/MATH_PI;}

//Random

uint64_t rdtsc(){uint32_t a,b;__asm__ __volatile__("rdtsc":"=a"(a),"=d"(b));return ((uint64_t)a|((uint64_t)b)<<32);}

void set_new_seed(){srand(rdtsc());}

int random(int mini, int maxi){return mod(int(rand()),(maxi-mini))+mini;}

//Intersection

bool intersection_of_segments(float a1,float b1,float a2,float b2)
{
    int a=max(a1,a2);
    int b=min(b1,b2);
    return (a<=b);
}

#endif // LL_MATH_H_INCLUDED
