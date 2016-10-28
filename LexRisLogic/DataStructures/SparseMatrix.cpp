/* SparseMatrix.cpp -- Sparse Matrix Data Structure Source - LexRis Logic Headers

    Copyright (c) 2016 LexRisLogic

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

#include "SparseMatrix.h"

namespace LL_DataStructure
{
    __SparseMatrixNode__::__SparseMatrixNode__(unsigned int new_pos_x,unsigned int new_pos_y,void* new_data)
    {
        pos_x=new_pos_x;
        pos_y=new_pos_y;
        data=new_data;
    }
    void __SparseMatrixNode__::delete_y_node()
    {
        if(next_y)
        {
            next_y->delete_y_node();
            delete(next_y);
        }
        next_y=nullptr;
    }
    __SparseMatrixNode__::~__SparseMatrixNode__()
    {
        delete_y_node();
        if(next_x)
            delete(next_x);
        next_x=nullptr;
    }

    void __SparseMatrixController__::_F_create_node(void* new_data)
    {
        __SparseMatrixNode__* new_node=new __SparseMatrixNode__(_V_pos_x,_V_pos_y,new_data);
        new_node->next_x=*_V_pointer_x;
        new_node->next_y=*_V_pointer_y;
        *_V_pointer_x=new_node;
        *_V_pointer_y=new_node;
    }
    void __SparseMatrixController__::_F_remove_node()
    {
        __SparseMatrixNode__* node_to_remove=*_V_pointer_x;
        *_V_pointer_x=node_to_remove->next_x;
        *_V_pointer_y=node_to_remove->next_y;
        node_to_remove->next_x=nullptr;
        node_to_remove->next_y=nullptr;
        delete(node_to_remove);
    }
    __SparseMatrixController__::__SparseMatrixController__()
    {
    }
    __SparseMatrixController__::__SparseMatrixController__(__SparseMatrixNode__** pointer_x,
                                                           __SparseMatrixNode__** pointer_y,
                                                            unsigned int pos_x,unsigned int pos_y,void* null_value)
    {
        construct(pointer_x,pointer_y,pos_x,pos_y,null_value);
    }
    void __SparseMatrixController__::construct(__SparseMatrixNode__** pointer_x,__SparseMatrixNode__** pointer_y,
                                                unsigned int pos_x,unsigned int pos_y,void* null_value)
    {
        _V_pointer_x=pointer_x;
        _V_pointer_y=pointer_y;
        _V_pos_x=pos_x;
        _V_pos_y=pos_y;
        _V_null_value=null_value;
    }
    void* __SparseMatrixController__::get_value()
    {
        if(((*_V_pointer_x) and (*_V_pointer_y)) and ((*_V_pointer_x)==(*_V_pointer_y)))
            return (*((*this)._V_pointer_x))->data;
        return _V_null_value;
    }
    void* __SparseMatrixController__::get_null_value()
    {
        return _V_null_value;
    }
    void __SparseMatrixController__::set_value(void* new_data,bool difference_null_value)
    {
        if(((*_V_pointer_x) and (*_V_pointer_y)) and ((*_V_pointer_x)==(*_V_pointer_y)))
        {
            if(difference_null_value)
                (*_V_pointer_x)->data=new_data;
            else
                _F_remove_node();
        }
        else if(difference_null_value)
            _F_create_node(new_data);
    }

    __SparseMatrix__::__SparseMatrix__(unsigned int size_x,unsigned int size_y,void* null_value)
    {
        _V_size_x=size_x;
        _V_size_y=size_y;
        _V_null_value=null_value;
        _V_vector_x=new __SparseMatrixNode__*[_V_size_x];
        for(unsigned int i=0;i<_V_size_x;++i)
            _V_vector_x[i]=nullptr;
        _V_vector_y=new __SparseMatrixNode__*[_V_size_y];
        for(unsigned int i=0;i<_V_size_y;++i)
            _V_vector_y[i]=nullptr;
    }
    unsigned int __SparseMatrix__::get_size_x()
    {
        return _V_size_x;
    }
    unsigned int __SparseMatrix__::get_size_y()
    {
        return _V_size_y;
    }
    void* __SparseMatrix__::get_null_value()
    {
        return _V_null_value;
    }
    void __SparseMatrix__::clear()
    {
        unsigned int ini_x=0;
        unsigned int ini_y=0;
        unsigned int fin_x=_V_size_x;
        unsigned int fin_y=_V_size_y;
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
            __SparseMatrixNode__** root_x;
            __SparseMatrixNode__** root_y;
            for(unsigned int i=ini_x;i<fin_x;++i)
            {
                for(unsigned int j=ini_y;j<fin_y;++j)
                {
                    get_data_to_create_controller(i,j,root_x,root_y);
                    __SparseMatrixController__ temp_controller(root_x,root_y,i,j,_V_null_value);
                    temp_controller.set_value(_V_null_value,false);
                }
            }
        }
    }
    void __SparseMatrix__::get_data_to_create_controller(unsigned int pos_x,unsigned int pos_y,
                                                        __SparseMatrixNode__**& root_x,__SparseMatrixNode__**& root_y)
    {
        root_x=&_V_vector_y[pos_y];
        for(;(*root_x) and ((*root_x)->pos_x)<pos_x;root_x=&((*root_x)->next_x));
        root_y=&_V_vector_x[pos_x];
        for(;(*root_y) and ((*root_y)->pos_y)<pos_y;root_y=&((*root_y)->next_y));
    }
    __SparseMatrix__::~__SparseMatrix__()
    {
        clear();
        delete(_V_vector_x);
        delete(_V_vector_y);
    }
}
