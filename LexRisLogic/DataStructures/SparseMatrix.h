/* SparseMatrix.h -- Sparse Matrix Data Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_DATASTRUCTURE_SPARSEMATRIX_H
#define INCLUDED_LL_DATASTRUCTURE_SPARSEMATRIX_H

namespace LL_DataStructure
{
    template<typename T>
    class SparseMatrix
    {
        private:
            struct _S_Structure_Node
            {
                _S_Structure_Node(unsigned int new_pos_x,unsigned int new_pos_y,T new_data)
                {
                    pos_x=new_pos_x;
                    pos_y=new_pos_y;
                    data=new_data;
                }
                unsigned int pos_x;
                unsigned int pos_y;
                T data;
                _S_Structure_Node* next_x=nullptr;
                _S_Structure_Node* next_y=nullptr;
                void delete_y_node()
                {
                    if(next_y)
                    {
                        next_y->delete_y_node();
                        delete(next_y);
                    }
                    next_y=nullptr;
                }
                ~_S_Structure_Node()
                {
                    delete_y_node();
                    if(next_x)
                        delete(next_x);
                    next_x=nullptr;
                }
            };
            unsigned int _V_size_x;
            unsigned int _V_size_y;
            T _V_null_value;
            _S_Structure_Node** _V_vector_x=nullptr;
            _S_Structure_Node** _V_vector_y=nullptr;
        public:
            SparseMatrix(unsigned int size_x,unsigned int size_y,T null_value)
            {
                _V_size_x=size_x;
                _V_size_y=size_y;
                _V_null_value=null_value;
                _V_vector_x=new _S_Structure_Node*[_V_size_x];
                for(unsigned int i=0;i<_V_size_x;++i)
                    _V_vector_x[i]=nullptr;
                _V_vector_y=new _S_Structure_Node*[_V_size_y];
                for(unsigned int i=0;i<_V_size_y;++i)
                    _V_vector_y[i]=nullptr;
            }
            class Class_Controller
            {
                private:
                    T _V_null_value;
                    _S_Structure_Node** _V_pointer_x=nullptr;
                    _S_Structure_Node** _V_pointer_y=nullptr;
                    unsigned int _V_pos_x;
                    unsigned int _V_pos_y;
                    void _F_create_node(T new_data)
                    {
                        _S_Structure_Node* new_node=new _S_Structure_Node(_V_pos_x,_V_pos_y,new_data);
                        new_node->next_x=*_V_pointer_x;
                        new_node->next_y=*_V_pointer_y;
                        *_V_pointer_x=new_node;
                        *_V_pointer_y=new_node;
                    }
                    void _F_remove_node()
                    {
                        _S_Structure_Node* node_to_remove=*_V_pointer_x;
                        *_V_pointer_x=node_to_remove->next_x;
                        *_V_pointer_y=node_to_remove->next_y;
                        node_to_remove->next_x=nullptr;
                        node_to_remove->next_y=nullptr;
                        delete(node_to_remove);
                    }
                public:
                    Class_Controller(_S_Structure_Node** pointer_x,_S_Structure_Node** pointer_y,
                                     unsigned int pos_x,unsigned int pos_y,T null_value)
                    {
                        _V_pointer_x=pointer_x;
                        _V_pointer_y=pointer_y;
                        _V_pos_x=pos_x;
                        _V_pos_y=pos_y;
                        _V_null_value=null_value;
                    }
                    T get_value()
                    {
                        if(((*_V_pointer_x) and (*_V_pointer_y)) and ((*_V_pointer_x)==(*_V_pointer_y)))
                            return (*((*this)._V_pointer_x))->data;
                        return _V_null_value;
                    }
                    T operator = (T new_data)
                    {
                        if(((*_V_pointer_x) and (*_V_pointer_y)) and ((*_V_pointer_x)==(*_V_pointer_y)))
                        {
                            if(new_data!=_V_null_value)
                                (*_V_pointer_x)->data=new_data;
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
                    for(unsigned int i=ini_x;i<fin_x;++i)
                    {
                        for(unsigned int j=ini_y;j<fin_y;++j)
                            (*this)(i,j)=_V_null_value;
                    }
                }
            }
            Class_Controller operator () (unsigned int pos_x,unsigned int pos_y)
            {
                _S_Structure_Node** root_x=&_V_vector_y[pos_y];
                for(;(*root_x) and ((*root_x)->pos_x)<pos_x;root_x=&((*root_x)->next_x));
                _S_Structure_Node** root_y=&_V_vector_x[pos_x];
                for(;(*root_y) and ((*root_y)->pos_y)<pos_y;root_y=&((*root_y)->next_y));
                return Class_Controller(root_x,root_y,pos_x,pos_y,_V_null_value);
            }
            ~SparseMatrix()
            {
                clear();
                delete(_V_vector_x);
                delete(_V_vector_y);
            }
    };
}

#endif // INCLUDED_LL_DATASTRUCTURE_SPARSEMATRIX_H
