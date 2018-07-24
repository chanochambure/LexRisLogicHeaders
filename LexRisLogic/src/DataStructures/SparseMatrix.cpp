/* SparseMatrix.cpp -- Sparse Matrix Data Structure Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/DataStructures/SparseMatrix.h"

namespace LL_DataStructure
{
    void __SparseMatrixNodeBase__::set_data(unsigned int new_pos_x,unsigned int new_pos_y)
    {
        pos_x=new_pos_x;
        pos_y=new_pos_y;
    }
    void __SparseMatrixNodeBase__::delete_y_node()
    {
        if(next_y)
        {
            next_y->delete_y_node();
            delete(next_y);
        }
        next_y=nullptr;
    }
    __SparseMatrixNodeBase__::~__SparseMatrixNodeBase__()
    {
        delete_y_node();
        if(next_x)
            delete(next_x);
        next_x=nullptr;
    }

    void __SparseMatrixControllerBase__::_F_remove_node()
    {
        __SparseMatrixNodeBase__* node_to_remove=*_V_pointer_x;
        *_V_pointer_x=node_to_remove->next_x;
        *_V_pointer_y=node_to_remove->next_y;
        node_to_remove->next_x=nullptr;
        node_to_remove->next_y=nullptr;
        delete(node_to_remove);
    }
    void __SparseMatrixControllerBase__::_F_set_data(__SparseMatrixNodeBase__** pointer_x,
                                                     __SparseMatrixNodeBase__** pointer_y,
                                                     unsigned int pos_x,unsigned int pos_y)
    {
        _V_pointer_x=pointer_x;
        _V_pointer_y=pointer_y;
        _V_pos_x=pos_x;
        _V_pos_y=pos_y;
    }

    void __SparseMatrixBase__::_F_construct_matrix(unsigned int size_x,unsigned int size_y)
    {
        _V_size_x=size_x;
        _V_size_y=size_y;
        _V_vector_x=new __SparseMatrixNodeBase__*[_V_size_x];
        for(unsigned int i=0;i<_V_size_x;++i)
            _V_vector_x[i]=nullptr;
        _V_vector_y=new __SparseMatrixNodeBase__*[_V_size_y];
        for(unsigned int i=0;i<_V_size_y;++i)
            _V_vector_y[i]=nullptr;
    }
    void __SparseMatrixBase__::_F_get_nodes_to_position(unsigned int pos_x,unsigned int pos_y,
                                                        __SparseMatrixNodeBase__**& root_x,
                                                        __SparseMatrixNodeBase__**& root_y)
    {
        root_x=&_V_vector_y[pos_y];
        for(;(*root_x) and ((*root_x)->pos_x)<pos_x;root_x=&((*root_x)->next_x));
        root_y=&_V_vector_x[pos_x];
        for(;(*root_y) and ((*root_y)->pos_y)<pos_y;root_y=&((*root_y)->next_y));
    }
    bool __SparseMatrixBase__::_F_can_clear(unsigned int& ini_x,unsigned int& ini_y,
                                            unsigned int& fin_x,unsigned int& fin_y)
    {
        ini_x=0;
        ini_y=0;
        fin_x=_V_size_x;
        fin_y=_V_size_y;
        bool have_data=false;
        for(unsigned int i=0;i<_V_size_x;++i)
        {
            if(_V_vector_x[i])
            {
                have_data=true;
                ini_x=i;
                break;
            }
        }
        for(unsigned int i=0;i<_V_size_y;++i)
        {
            if(_V_vector_y[i])
            {
                have_data=true;
                ini_y=i;
                break;
            }
        }
        if(have_data)
        {
            for(unsigned int i=_V_size_x-1;i>=0;--i)
            {
                if(_V_vector_x[i])
                {
                    fin_x=i+1;
                    break;
                }
            }
            for(unsigned int i=_V_size_y-1;i>=0;--i)
            {
                if(_V_vector_y[i])
                {
                    fin_y=i+1;
                    break;
                }
            }
        }
        return have_data;
    }
    void __SparseMatrixBase__::_F_delete_matrix()
    {
        delete(_V_vector_x);
        delete(_V_vector_y);
    }
}
