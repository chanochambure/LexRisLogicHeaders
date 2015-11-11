#ifndef LL_MATH_H_INCLUDED
#define LL_MATH_H_INCLUDED

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

template<int N>
class Dot
{
    private:
        vector<float> dots;
    public:
        Dot(){for(int i=0;i<N;++i)dots.push_back(0);}
        int get_dimension(){return N;}
        float& operator [](unsigned int i){return dots[i];}
        Dot<N>& operator = (Dot<N> ot){for(int i=0;i<N;++i)(*this)[i]=ot[i];return (*this);}
        bool operator == (Dot<N> ot){for(int i=0;i<N;++i){if((*this)[i]!=ot[i])return 0;}return 1;}
        ~Dot(){dots.clear();}
};

template<int N>
ostream& operator << (ostream& os,Dot<N> dot)
{
    os<<"[";
    for(unsigned int i=0;i<N-1;++i)
        os<<dot[i]<<" ";
    os<<dot[N-1]<<"]";
    return os;
}

template<int N>
double euclidean_distance(Dot<N> one,Dot<N> two)
{
    double acum=0;;
    for(int i=0;i<N;++i)
        acum+=pow(one[i]-two[i],2);
    return sqrt(acum);
}

#endif // LL_MATH_H_INCLUDED
