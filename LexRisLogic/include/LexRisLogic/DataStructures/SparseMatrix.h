/* SparseMatrix.h -- Sparse Matrix Data Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_DATASTRUCTURE_SPARSEMATRIX_H
#define INCLUDED_LL_DATASTRUCTURE_SPARSEMATRIX_H

#include "../LL_Shared.h"

namespace LL_DataStructure
{
    struct LL_SHARED __SparseMatrixNodeBase__
    {
        unsigned int pos_x;
        unsigned int pos_y;
        __SparseMatrixNodeBase__* next_x=nullptr;
        __SparseMatrixNodeBase__* next_y=nullptr;
        void set_data(unsigned int new_pos_x,unsigned int new_pos_y);
        void delete_y_node();
        virtual ~__SparseMatrixNodeBase__();
    };

    class LL_SHARED __SparseMatrixControllerBase__
    {
        protected:
            __SparseMatrixNodeBase__** _V_pointer_x=nullptr;
            __SparseMatrixNodeBase__** _V_pointer_y=nullptr;
            unsigned int _V_pos_x;
            unsigned int _V_pos_y;
            void _F_remove_node();
            void _F_set_data(__SparseMatrixNodeBase__** pointer_x,
                             __SparseMatrixNodeBase__** pointer_y,
                             unsigned int pos_x,unsigned int pos_y);
    };

    class LL_SHARED __SparseMatrixBase__
    {
        protected:
            __SparseMatrixNodeBase__** _V_vector_x=nullptr;
            __SparseMatrixNodeBase__** _V_vector_y=nullptr;
            unsigned int _V_size_x;
            unsigned int _V_size_y;
            void _F_construct_matrix(unsigned int size_x,unsigned int size_y);
            void _F_get_nodes_to_position(unsigned int pos_x,unsigned int pos_y,
                                          __SparseMatrixNodeBase__**& root_x,
                                          __SparseMatrixNodeBase__**& root_y);
            bool _F_can_clear(unsigned int& ini_x,unsigned int& ini_y,unsigned int& fin_x,unsigned int& fin_y);
            void _F_delete_matrix();
    };

    template<typename T>
    class SparseMatrix:public __SparseMatrixBase__
    {
        private:
            struct _S_Structure_Node:public __SparseMatrixNodeBase__
            {
                _S_Structure_Node(unsigned int new_pos_x,unsigned int new_pos_y,T new_data)
                {
                    data=new_data;
                    set_data(new_pos_x,new_pos_y);
                }
                T data;
            };
            T _V_null_value;
        public:
            SparseMatrix(unsigned int size_x,unsigned int size_y,T null_value)
            {
                _V_null_value=null_value;
                _F_construct_matrix(size_x,size_y);
            }
            class Class_Controller:public __SparseMatrixControllerBase__
            {
                private:
                    T _V_null_value;
                    void _F_create_node(T new_data)
                    {
                        _S_Structure_Node* new_node=new _S_Structure_Node(_V_pos_x,_V_pos_y,new_data);
                        new_node->next_x=*_V_pointer_x;
                        new_node->next_y=*_V_pointer_y;
                        *_V_pointer_x=new_node;
                        *_V_pointer_y=new_node;
                    }
                public:
                    Class_Controller(__SparseMatrixNodeBase__** pointer_x,__SparseMatrixNodeBase__** pointer_y,
                                     unsigned int pos_x,unsigned int pos_y,T null_value)
                    {
                        _V_null_value=null_value;
                        _F_set_data(pointer_x,pointer_y,pos_x,pos_y);
                    }
                    T get_value()
                    {
                        _S_Structure_Node* pointer=static_cast<_S_Structure_Node*>(*_V_pointer_x);
                        if(((*_V_pointer_x) and (*_V_pointer_y)) and ((*_V_pointer_x)==(*_V_pointer_y)))
                            return pointer->data;
                        return _V_null_value;
                    }
                    T operator = (T new_data)
                    {
                        if(((*_V_pointer_x) and (*_V_pointer_y)) and ((*_V_pointer_x)==(*_V_pointer_y)))
                        {
                            _S_Structure_Node* pointer=static_cast<_S_Structure_Node*>(*_V_pointer_x);
                            if(new_data!=_V_null_value)
                                pointer->data=new_data;
                            else
                                _F_remove_node();
                        }
                        else if(new_data!=_V_null_value)
                            _F_create_node(new_data);
                        return new_data;
                    }
                    operator T()
                    {
                        return get_value();
                    }
            };
            unsigned int get_size_x()
            {
                return _V_size_x;
            }
            unsigned int get_size_y()
            {
                return _V_size_y;
            }
            T get_null_value()
            {
                return _V_null_value;
            }
            void clear()
            {
                unsigned int ini_x;
                unsigned int ini_y;
                unsigned int fin_x;
                unsigned int fin_y;
                if(_F_can_clear(ini_x,ini_y,fin_x,fin_y))
                {
                    for(unsigned int i=ini_x;i<fin_x;++i)
                    {
                        for(unsigned int j=ini_y;j<fin_y;++j)
                            (*this)(i,j)=_V_null_value;
                    }
                }
            }
            Class_Controller operator () (unsigned int pos_x,unsigned int pos_y)
            {
                __SparseMatrixNodeBase__** root_x;
                __SparseMatrixNodeBase__** root_y;
                _F_get_nodes_to_position(pos_x,pos_y,root_x,root_y);
                return Class_Controller(root_x,root_y,pos_x,pos_y,_V_null_value);
            }
            ~SparseMatrix()
            {
                clear();
                _F_delete_matrix();
            }
    };
}

#endif // INCLUDED_LL_DATASTRUCTURE_SPARSEMATRIX_H
