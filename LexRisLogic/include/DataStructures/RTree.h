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
        bool operator == (MBB another_mbb);
        bool operator != (MBB another_mbb);
    };

    double mbb_distance(MBB first_mbb,MBB second_mbb);

    struct __RTreeDataNodeBase__
    {
        MBB mbb;
        virtual ~__RTreeDataNodeBase__();
    };

    struct __RTreeNodeBase__
    {
        __RTreeNodeBase__(unsigned int new_dimension,unsigned int new_node_size,bool node_type=false);
        MBB mbb;
        bool type=false;
        unsigned int node_size;
        unsigned int dimension;
        unsigned int size=0;
        unsigned int pos_in_parent=0;
        __RTreeNodeBase__* parent=nullptr;
        __RTreeNodeBase__** sons=nullptr;
        __RTreeDataNodeBase__** data=nullptr;
        void set_mbb();
        void set_metadata();
        unsigned int farthest_node_position();
        void clear();
        virtual ~__RTreeNodeBase__();
    };

    class __RTreeIteratorBase__
    {
        protected:
            typedef std::pair<unsigned int,__RTreeNodeBase__*> _T_Type_item;
            std::stack<_T_Type_item> _V_stack;
            void _F_get_next();
            void _F_set_data(__RTreeNodeBase__* root_node);
    };

    class __RTreeBase__
    {
        protected:
            typedef std::pair<double,unsigned int> _T_Type_pair_dis_pos;
            unsigned int _V_dimension;
            unsigned int _V_node_size;
            unsigned int _V_min_node_size;
            __RTreeNodeBase__* _V_root=nullptr;
            unsigned int _V_size=0;
            void _F_target_node(MBB new_mbb,__RTreeNodeBase__**& target_node);
            bool _F_find_data(MBB data_mbb,__RTreeNodeBase__**& node);
            void _F_refresh_data(__RTreeNodeBase__** node);
            bool _F_remove_data(MBB mbb);
            void _F_split_node(__RTreeNodeBase__* node);
            void _F_merge_node(__RTreeNodeBase__* node);
    };

    template<typename T,unsigned int DIMENSION,unsigned int NODE_SIZE>
    class RTree:public __RTreeBase__
    {
        private:
            struct _S_Structure_DataNode:public __RTreeDataNodeBase__
            {
                _S_Structure_DataNode(T new_data,MBB new_mbb)
                {
                    data=new_data;
                    mbb=new_mbb;
                }
                T data;
            };
            MBB (*_P_Function_to_mbb)(T)=nullptr;
            void _F_range_query(std::list<T>* data_list,__RTreeNodeBase__* node,MBB mbb)
            {
                if(node->type)
                {
                    for(unsigned int i=0;i<node->size;++i)
                    {
                        if(mbb_distance(mbb,node->sons[i]->mbb)==0.0)
                            _F_range_query(data_list,node->sons[i],mbb);
                    }
                }
                else
                {
                    for(unsigned int i=0;i<node->size;++i)
                    {
                        _S_Structure_DataNode* pointer=static_cast<_S_Structure_DataNode*>(node->data[i]);
                        if(mbb_distance(mbb,node->data[i]->mbb)==0.0)
                            data_list->push_back(pointer->data);
                    }
                }
            }
        public:
            RTree(MBB (*Function_to_mbb)(T))
            {
                _V_dimension=DIMENSION;
                _V_node_size=NODE_SIZE;
                _V_min_node_size=(_V_node_size+1)/2;
                _P_Function_to_mbb=Function_to_mbb;
                _V_root=new __RTreeNodeBase__(_V_dimension,_V_node_size);
            }
            class iterator:public __RTreeIteratorBase__
            {
                public:
                    iterator(__RTreeNodeBase__* root_node=nullptr)
                    {
                        _F_set_data(root_node);
                    }
                    iterator operator ++ (int)
                    {
                        iterator temp_iterator=(*this);
                        _F_get_next();
                        return temp_iterator;
                    }
                    iterator operator ++ ()
                    {
                        _F_get_next();
                        return (*this);
                    }
                    const T operator * ()
                    {
                        _S_Structure_DataNode* pointer=static_cast<_S_Structure_DataNode*>
                                                        ((_V_stack.top().second)->data[_V_stack.top().first]);
                        return pointer->data;
                    }
                    bool operator != (iterator another_iterator)
                    {
                        return (_V_stack!=another_iterator._V_stack);
                    }
            };
            iterator begin()
            {
                return iterator(_V_root);
            }
            iterator end()
            {
                return iterator();
            }
            unsigned int size()
            {
                return _V_size;
            }
            void clear()
            {
                delete(_V_root);
                _V_root=new __RTreeNodeBase__(_V_dimension,_V_node_size);
                _V_size=0;
            }
            bool find(T data)
            {
                __RTreeNodeBase__** leaf=&(_V_root);
                MBB mbb=_P_Function_to_mbb(data);
                if(mbb.dimension==_V_dimension)
                    return _F_find_data(mbb,leaf);
                return false;
            }
            bool insert(T new_data)
            {
                MBB mbb=_P_Function_to_mbb(new_data);
                __RTreeNodeBase__** leaf=&(_V_root);
                if(_F_find_data(mbb,leaf) or (mbb.dimension!=_V_dimension))
                    return false;
                _F_target_node(mbb,leaf);
                (*leaf)->data[(*leaf)->size++]=new _S_Structure_DataNode(new_data,mbb);
                _F_refresh_data(leaf);
                return true;
            }
            bool remove(T data_to_remove)
            {
                MBB mbb=_P_Function_to_mbb(data_to_remove);
                if(mbb.dimension==_V_dimension)
                    return _F_remove_data(mbb);
                return false;
            }
            std::list<T> range_query(MBB mbb)
            {
                std::list<T> data_list;
                if(mbb.dimension==_V_dimension)
                    _F_range_query(&data_list,_V_root,mbb);
                return data_list;
            }
            ~RTree()
            {
                delete(_V_root);
            }
    };
}

#endif // INCLUDED_LL_DATASTRUCTURE_RTREE_H
