/* MBB.h -- Minimal Bounding Box Math Structure Header - LexRis Logic Headers

    Copyright (c) 2017-2019 LexRisLogic

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

#ifndef INCLUDED_LL_MATHSTRUCTURE_MBB_H
#define INCLUDED_LL_MATHSTRUCTURE_MBB_H

#include "../LL_Shared.h"

#include "../MathStructures/Point.h"

namespace LL_MathStructure
{
    struct LL_SHARED MBB
    {
        MBB();
        MBB(unsigned int new_dimension);
        unsigned int dimension=0;
        Point first_point;
        Point second_point;
        bool set_dimension(unsigned int new_dimension);
        bool operator == (MBB another_mbb);
        bool operator != (MBB another_mbb);
    };

    double LL_SHARED mbb_distance(MBB first_mbb,MBB second_mbb);
    bool LL_SHARED mbb_collision(MBB first_mbb,MBB second_mbb);
}

#endif // INCLUDED_LL_MATHSTRUCTURE_MBB_H
