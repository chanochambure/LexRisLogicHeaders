#ifndef LR_MATH_H_INCLUDED
#define LR_MATH_H_INCLUDED

#include <vector>
#include <math.h>
#include <random>

using namespace std;

//Operations

template<typename T>
T mod(T a,T b){return ((a%b)+b)%b;}

template<typename T>
T range_mod(T a,T b){return fmod(fmod(a,b)+b,b);}

//Angle Conversion

#define PI 3.14159265358979323846

float sexadecimal_to_radian(float sexadecimal){return (sexadecimal*PI)/180;}
float radian_to_sexadecimal(float radian){return (radian*180)/PI;}

//Random

uint64_t rdtsc(){uint32_t a,b;__asm__ __volatile__("rdtsc":"=a"(a),"=d"(b));return ((uint64_t)a|((uint64_t)b)<<32);}

void set_new_seed(){srand(rdtsc());}

int random(int mini, int maxi){return mod(int(rand()),(maxi-mini))+mini;}

//Intersection

bool intersection_1D(float a1,float b1,float a2,float b2)
{
    int a=max(a1,a2);
    int b=min(b1,b2);
    return (a<=b);
}

//class
template<int N>
struct dot
{
    vector<int> dots;
    dot(){for(int i=0;i<N;++i)dots.push_back(0);}
    int& operator [](unsigned int p){return dots[p];}
    ~dot(){dots.clear();}
    dot<N>& operator = (dot<N> ot)
    {
        for(int i=0;i<N;++i)
            (*this)[i]=ot[i];
        return (*this);
    }
    bool operator == (dot<N> ot)
    {
        for(int i=0;i<N;++i)
        {
            if((*this)[i]!=ot[i])
                return 0;
        }
        return 1;
    }
};

template<int N>
double euclidean_distance(dot<N> one,dot<N> two)
{
    double acum=0;;
    for(int i=0;i<N;++i)
        acum+=pow(one[i]-two[i],2);
    return sqrt(acum);
}

#endif // LR_MATH_H_INCLUDED
