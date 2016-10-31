/* RTree.h -- R-Tree Data Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_DATASTRUCTURE_RTREE_H
#define INCLUDED_LL_DATASTRUCTURE_RTREE_H

#include <algorithm>
#include <stack>
#include <vector>
#include <list>
#include "../MathStructures/Point.h"

namespace LL_DataStructure
{
    struct MBB
    {
        MBB();
        MBB(unsigned int new_dimension);
        unsigned int dimension=0;
        LL_MathStructure::Point first_point;
        LL_MathStructure::Point second_point;
        bool set_dimension(unsigned int new_dimension);
        bool operator == (MBB other_mbb);
    };

    double mbb_distance(MBB first_mbb,MBB second_mbb);

    struct __RTreeDataNode__
    {
        __RTreeDataNode__(void* new_data,MBB new_mbb);
        MBB mbb;
        void* data;
    };

    struct __RTreeNode__
    {
        __RTreeNode__(unsigned int new_dimension,unsigned int new_node_size,bool node_type=false);
        MBB mbb;
        unsigned int node_size;
        unsigned int dimension;
        bool type=false;
        unsigned int size=0;
        unsigned int pos_in_parent=0;
        __RTreeNode__* parent=nullptr;
        __RTreeNode__** sons=nullptr;
        __RTreeDataNode__** data=nullptr;
        void set_mbb();
        void set_metadata();
        unsigned int farthest_node_position();
        void clear();
        ~__RTreeNode__();
    };

    class __RTreeIterator__
    {
        private:
            typedef std::pair<unsigned int,__RTreeNode__*> _T_Type_item;
            std::stack<_T_Type_item> _V_stack;
        public:
            __RTreeIterator__(__RTreeNode__* root_node=nullptr);
            void*& get_value();
            void get_next_element();
            bool compare_iterator(const __RTreeIterator__& another_iterator);
    };

    class __RTree__
    {
        private:
            typedef std::pair<double,unsigned int> _T_Type_pair_dis_pos;
            unsigned int _V_min_node_size=0;
            __RTreeNode__* _V_root=nullptr;
            unsigned int _V_size=0;
            unsigned int _V_dimension=0;
            unsigned int _V_node_size=0;
            void _F_target_node(MBB new_mbb,__RTreeNode__**& target_node);
            bool _F_find_data(MBB data_mbb,__RTreeNode__**& node);
            void _F_split_node(__RTreeNode__* node);
            void _F_merge_node(__RTreeNode__* node);
            void _F_range_query(std::list<void*>* data_list,__RTreeNode__* node,MBB mbb);
        public:
            __RTree__(unsigned int dimension,unsigned int node_size);
            unsigned int size();
            void clear();
            bool find(MBB data_mbb);
            bool insert(void* new_data,MBB data_mbb);
            bool remove(MBB data_mbb);
            std::list<void*> range_query(MBB mbb);
            __RTreeNode__* get_root_node();
            ~__RTree__();
    };

    template<typename T,int DIMENSION,unsigned int NODE_SIZE>
    class RTree
    {
        private:
            __RTree__* _V_void_rtree=nullptr;
            MBB (*_P_Function_to_mbb)(T)=nullptr;
        public:
            RTree(MBB (*Function_to_mbb)(T))
            {
                _P_Function_to_mbb=Function_to_mbb;
                _V_void_rtree=new __RTree__(DIMENSION,NODE_SIZE);
            }
            class iterator
            {
                private:
                    __RTreeIterator__ _V_void_iterator;
                public:
                    iterator(__RTreeNode__* root_node=nullptr)
                    {
                        _V_void_iterator=__RTreeIterator__(root_node);
                    }
                    iterator operator ++ (int)
                    {
                        iterator temp_iterator=(*this);
                        _V_void_iterator.get_next_element();
                        return temp_iterator;
                    }
                    iterator operator ++ ()
                    {
                        _V_void_iterator.get_next_element();
                        return (*this);
                    }
                    T operator * ()
                    {
                        return (T&)(_V_void_iterator.get_value());
                    }
                    bool operator != (const iterator& another_iterator)
                    {
                        return (_V_void_iterator.compare_iterator(another_iterator._V_void_iterator));
                    }
            };
            iterator begin()
            {
                return iterator(_V_void_rtree->get_root_node());
            }
            iterator end()
            {
                return iterator();
            }
            unsigned int size()
            {
                return _V_void_rtree->size();
            }
            void clear()
            {
                _V_void_rtree->clear();
            }
            bool find(T data)
            {
                return _V_void_rtree->find(_P_Function_to_mbb(data));
            }
            bool insert(T new_data)
            {
                return _V_void_rtree->insert((void*&)new_data,_P_Function_to_mbb(new_data));
            }
            bool remove(T data_to_remove)
            {
                return _V_void_rtree->remove(_P_Function_to_mbb(data_to_remove));
            }
            std::list<T> range_query(MBB mbb)
            {
                std::list<void*> void_data_list=_V_void_rtree->range_query(mbb);
                std::list<T> data_list;
                for(std::list<void*>::iterator i=void_data_list.begin();i!=void_data_list.end();++i)
                    data_list.push_back((T&)(*i));
                return data_list;
            }
            ~RTree()
            {
                delete(_V_void_rtree);
                _V_void_rtree=nullptr;
            }
    };
}

#endif // INCLUDED_LL_DATASTRUCTURE_RTREE_H
