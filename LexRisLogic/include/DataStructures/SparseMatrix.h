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
    struct __SparseMatrixNode__
    {
        __SparseMatrixNode__(unsigned int new_pos_x,unsigned int new_pos_y,void* new_data);
        unsigned int pos_x;
        unsigned int pos_y;
        void* data;
        __SparseMatrixNode__* next_x=nullptr;
        __SparseMatrixNode__* next_y=nullptr;
        void delete_y_node();
        ~__SparseMatrixNode__();
    };

    class __SparseMatrixController__
    {
        private:
            void* _V_null_value;
            __SparseMatrixNode__** _V_pointer_x=nullptr;
            __SparseMatrixNode__** _V_pointer_y=nullptr;
            unsigned int _V_pos_x;
            unsigned int _V_pos_y;
            void _F_create_node(void* new_data);
            void _F_remove_node();
        public:
            __SparseMatrixController__();
            __SparseMatrixController__(__SparseMatrixNode__** pointer_x,__SparseMatrixNode__** pointer_y,
                            unsigned int pos_x,unsigned int pos_y,void* null_value);
            void construct(__SparseMatrixNode__** pointer_x,__SparseMatrixNode__** pointer_y,
                            unsigned int pos_x,unsigned int pos_y,void* null_value);
            void* get_value();
            void* get_null_value();
            void set_value(void* new_data,bool difference_null_value);
    };

    class __SparseMatrix__
    {
        private:
            unsigned int _V_size_x;
            unsigned int _V_size_y;
            void* _V_null_value;
            __SparseMatrixNode__** _V_vector_x=nullptr;
            __SparseMatrixNode__** _V_vector_y=nullptr;
        public:
            __SparseMatrix__(unsigned int size_x,unsigned int size_y,void* null_value);
            unsigned int get_size_x();
            unsigned int get_size_y();
            void* get_null_value();
            void clear();
            void get_data_to_create_controller(unsigned int pos_x,unsigned int pos_y,
                                               __SparseMatrixNode__**& root_x,__SparseMatrixNode__**& root_y);
            ~__SparseMatrix__();
    };

    template<typename T>
    class SparseMatrix
    {
        private:
            __SparseMatrix__* _V_void_sparse_matrix=nullptr;
        public:
            SparseMatrix(unsigned int size_x,unsigned int size_y,T null_value)
            {
                _V_void_sparse_matrix=new __SparseMatrix__(size_x,size_y,(void*)null_value);
            }
            class Class_Controller
            {
                private:
                     __SparseMatrixController__ _V_void_class_controller;
                public:
                    Class_Controller(__SparseMatrixNode__** pointer_x,__SparseMatrixNode__** pointer_y,
                                     unsigned int pos_x,unsigned int pos_y,void* null_value)
                    {
                        _V_void_class_controller.construct(pointer_x,pointer_y,pos_x,pos_y,null_value);
                    }
                    T get_value()
                    {
                        return (T)(_V_void_class_controller.get_value());
                    }
                    T operator = (T new_data)
                    {
                        _V_void_class_controller.set_value((void*)new_data,
                                                            new_data!=(T)(_V_void_class_controller.get_null_value()));
                        return new_data;
                    }
                    operator T()
                    {
                        return get_value();
                    }
            };
            unsigned int get_size_x()
            {
                return _V_void_sparse_matrix->get_size_x();
            }
            unsigned int get_size_y()
            {
                return _V_void_sparse_matrix->get_size_y();
            }
            T get_null_value()
            {
                return (T)(_V_void_sparse_matrix->get_null_value());
            }
            void clear()
            {
                _V_void_sparse_matrix->clear();
            }
            Class_Controller operator () (unsigned int pos_x,unsigned int pos_y)
            {
                __SparseMatrixNode__** root_x;
                __SparseMatrixNode__** root_y;
                _V_void_sparse_matrix->get_data_to_create_controller(pos_x,pos_y,root_x,root_y);
                return Class_Controller(root_x,root_y,pos_x,pos_y,_V_void_sparse_matrix->get_null_value());
            }
            ~SparseMatrix()
            {
                delete(_V_void_sparse_matrix);
                _V_void_sparse_matrix=nullptr;
            }
    };
}

#endif // INCLUDED_LL_DATASTRUCTURE_SPARSEMATRIX_H
