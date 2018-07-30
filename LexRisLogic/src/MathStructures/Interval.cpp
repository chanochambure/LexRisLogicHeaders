/* Interval.cpp -- Interval Math Structure Source - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so.

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of
    the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "../../include/LexRisLogic/MathStructures/Interval.h"

namespace LL_MathStructure
{
    void Interval::_F_set_data(float left,float right)
    {
        _V_data[0]=left;
        _V_data[1]=right;
        if(left>right)
            std::swap(_V_data[0],_V_data[1]);
    }
    Interval::Interval()
    {
    }
    Interval::Interval(float left,float right)
    {
        _F_set_data(left,right);
    }
    bool Interval::set_left(float new_left)
    {
        if(new_left>_V_data[1])
            return false;
        _V_data[0]=new_left;
        return true;
    }
    bool Interval::set_right(float new_right)
    {
        if(new_right<_V_data[0])
            return false;
        _V_data[1]=new_right;
        return true;
    }
    void Interval::set_data(float new_left,float new_right)
    {
        _F_set_data(new_left,new_right);
    }
    float Interval::get_mid_point() const
    {
        return (_V_data[0]+_V_data[1])/2.0;
    }
	bool Interval::contains(float point) const
	{
	    return _V_data[0]<=point && point<=_V_data[1];
	}
	bool Interval::contains(const Interval& another_interval) const
	{
	    return _V_data[0]<=another_interval[0] && another_interval[1]<=_V_data[1];
	}
	bool Interval::intersects(const Interval& another_interval) const
	{
        float ini_point=std::max(_V_data[0],another_interval[0]);
        float end_point=std::min(_V_data[1],another_interval[1]);
        return ini_point<=end_point;
	}
	bool Interval::is_left_of(float point) const
	{
	    return _V_data[1]<point;
	}
	bool Interval::is_right_of(float point) const
	{
		return point<_V_data[0];
	}
	bool Interval::is_left_of(const Interval& another_interval) const
	{
		return is_left_of(another_interval[0]);
	}
	bool Interval::is_right_of(const Interval& another_interval) const
    {
		return is_right_of(another_interval[1]);
	}
    const float Interval::operator [](unsigned int index) const
    {
        return _V_data[index];
    }
    bool Interval::operator == (const Interval& another_interval) const
    {
        return _V_data[0]==another_interval[0] && _V_data[1]==another_interval[1];
    }
    bool Interval::operator < (const Interval& another_interval) const
    {
        if(_V_data[0]==another_interval[0])
            return _V_data[1]<another_interval[1];
        return _V_data[0]<another_interval[0];
    }
    bool Interval::operator != (const Interval& another_interval) const
    {
        return _V_data[0]!=another_interval[0] || _V_data[1]!=another_interval[1];
    }

    std::ostream& LL_SHARED operator << (std::ostream& output_stream,Interval interval)
    {
        output_stream<<"["<<interval[0]<<","<<interval[1]<<"]";
        return output_stream;
    }
}
