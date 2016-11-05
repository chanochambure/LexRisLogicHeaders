/* RTree.cpp -- R-Tree Data Structure Source - LexRis Logic Headers

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

#include "../../include/DataStructures/RTree.h"

namespace LL_DataStructure
{
    MBB::MBB()
    {
    }
    MBB::MBB(unsigned int new_dimension)
    {
        set_dimension(new_dimension);
    }
    bool MBB::set_dimension(unsigned int new_dimension)
    {
        if(new_dimension)
        {
            dimension=new_dimension;
            first_point.set_dimension(dimension);
            second_point.set_dimension(dimension);
            return true;
        }
        return false;
    }
    bool MBB::operator == (MBB another_mbb)
    {
        return ((first_point==another_mbb.first_point) and (second_point==another_mbb.second_point));
    }

    double mbb_distance(MBB first_mbb,MBB second_mbb)
    {
        if(first_mbb.dimension==second_mbb.dimension)
        {
            double acumulator=0.0;
            for(unsigned int i=0;i<first_mbb.dimension;++i)
            {
                double min_distance=std::max(first_mbb.first_point[i],second_mbb.first_point[i])-
                                    std::min(first_mbb.second_point[i],second_mbb.second_point[i]);
                if(min_distance>0)
                    acumulator+=pow(min_distance,2);
            }
            return sqrt(acumulator);
        }
        return 0.0;
    }

    __RTreeDataNode__::__RTreeDataNode__(void* new_data,MBB new_mbb)
    {
        data=new_data;
        mbb=new_mbb;
    }

    __RTreeNode__::__RTreeNode__(unsigned int new_dimension,unsigned int new_node_size,bool node_type)
    {
        node_size=new_node_size;
        sons=new __RTreeNode__*[node_size+2];
        data=new __RTreeDataNode__*[node_size+1];
        dimension=new_dimension;
        mbb.set_dimension(dimension);
        type=node_type;
        for(unsigned int i=0;i<(node_size+1);++i)
        {
            data[i]=nullptr;
            sons[i]=nullptr;
        }
        sons[node_size+1]=nullptr;
    }
    void __RTreeNode__::set_mbb()
    {
        if(size)
        {
            if(type)
            {
                mbb=sons[0]->mbb;
                for(unsigned int i=1;i<size;++i)
                {
                    for(unsigned int j=0;j<dimension;++j)
                    {
                        if(sons[i]->mbb.first_point[j]<mbb.first_point[j])
                            mbb.first_point[j]=sons[i]->mbb.first_point[j];
                        if(sons[i]->mbb.second_point[j]>mbb.second_point[j])
                            mbb.second_point[j]=sons[i]->mbb.second_point[j];
                    }
                }
            }
            else
            {
                mbb=data[0]->mbb;
                for(unsigned int i=1;i<size;++i)
                {
                    for(unsigned int j=0;j<dimension;++j)
                    {
                        if(data[i]->mbb.first_point[j]<mbb.first_point[j])
                            mbb.first_point[j]=data[i]->mbb.first_point[j];
                        if(data[i]->mbb.second_point[j]>mbb.second_point[j])
                            mbb.second_point[j]=data[i]->mbb.second_point[j];
                    }
                }
            }
        }
    }
    void __RTreeNode__::set_metadata()
    {
        if(size)
        {
            if(type)
            {
                sons[0]->pos_in_parent=0;
                sons[0]->set_metadata();
                mbb=sons[0]->mbb;
                for(unsigned int i=1;i<size;++i)
                {
                    sons[i]->pos_in_parent=i;
                    sons[i]->set_metadata();
                    for(unsigned int j=0;j<dimension;++j)
                    {
                        if(sons[i]->mbb.first_point[j]<mbb.first_point[j])
                            mbb.first_point[j]=sons[i]->mbb.first_point[j];
                        if(sons[i]->mbb.second_point[j]>mbb.second_point[j])
                            mbb.second_point[j]=sons[i]->mbb.second_point[j];
                    }
                }
            }
            else
            {
                mbb=data[0]->mbb;
                for(unsigned int i=1;i<size;++i)
                {
                    for(unsigned int j=0;j<dimension;++j)
                    {
                        if(data[i]->mbb.first_point[j]<mbb.first_point[j])
                            mbb.first_point[j]=data[i]->mbb.first_point[j];
                        if(data[i]->mbb.second_point[j]>mbb.second_point[j])
                            mbb.second_point[j]=data[i]->mbb.second_point[j];
                    }
                }
            }
        }
    }
    unsigned int __RTreeNode__::farthest_node_position()
    {
        unsigned int farthest_node=0;
        if(type)
        {
            for(unsigned int i=1;i<size;++i)
            {
                for(unsigned int j=0;j<dimension;++j)
                {
                    if(sons[farthest_node]->mbb.first_point[j]>sons[i]->mbb.first_point[j])
                    {
                        farthest_node=i;
                        break;
                    }
                }
            }
        }
        else
        {
            for(unsigned int i=1;i<size;++i)
            {
                for(unsigned int j=0;j<dimension;++j)
                {
                    if(data[farthest_node]->mbb.first_point[j]>data[i]->mbb.first_point[j])
                    {
                        farthest_node=i;
                        break;
                    }
                }
            }
        }
        return farthest_node;
    }
    void __RTreeNode__::clear()
    {
        size=0;
        for(unsigned int i=0;i<(node_size+1);++i)
        {
            data[i]=nullptr;
            sons[i]=nullptr;
        }
    }
    __RTreeNode__::~__RTreeNode__()
    {
        if(type)
        {
            for(unsigned int i=0;i<size;++i)
                delete(sons[i]);
        }
        else
        {
            for(unsigned int i=0;i<size;++i)
                delete(data[i]);
        }
        delete(sons);
        delete(data);
    }

    __RTreeIterator__::__RTreeIterator__(__RTreeNode__* root_node)
    {
        if(root_node)
        {
            if(root_node->size)
                _V_stack.push(_T_Type_item(0,root_node));
            if(root_node->type)
                get_next_element();
        }
    }
    void*& __RTreeIterator__::get_value()
    {
        return ((_V_stack.top().second)->data[_V_stack.top().first])->data;
    }
    void __RTreeIterator__::get_next_element()
    {
        if(_V_stack.empty())
            return;
        if(!(_V_stack.top().second->type))
        {
            if((_V_stack.top().first++)<(_V_stack.top().second->size-1))
                return;
            else
                _V_stack.pop();
        }
        while((!_V_stack.empty()) and _V_stack.top().second->type)
        {
            if(_V_stack.top().first<(_V_stack.top().second->size))
                _V_stack.push(_T_Type_item(0,_V_stack.top().second->sons[_V_stack.top().first++]));
            else
                _V_stack.pop();
        }
    }
    bool __RTreeIterator__::compare_iterator(const __RTreeIterator__& another_iterator)
    {
        return (_V_stack!=another_iterator._V_stack);
    }

    void __RTree__::_F_target_node(MBB new_mbb,__RTreeNode__**& target_node)
    {
        while((*target_node)->type)
        {
            unsigned int target_son=0;
            double actual_distance=mbb_distance(new_mbb,(*target_node)->sons[0]->mbb);
            for(unsigned int i=1;i<(*target_node)->size;++i)
            {
                double new_distance=mbb_distance(new_mbb,(*target_node)->sons[i]->mbb);
                if(new_distance<actual_distance)
                {
                    actual_distance=new_distance;
                    target_son=i;
                }
            }
            target_node=&((*target_node)->sons[target_son]);
        }
    }
    bool __RTree__::_F_find_data(MBB data_mbb,__RTreeNode__**& node)
    {
        if(*node)
        {
            if((*node)->type)
            {
                __RTreeNode__** temp_node=node;
                __RTreeNode__** selected_node=node;
                for(unsigned int i=0;i<(*node)->size;++i)
                {
                    node=&((*node)->sons[i]);
                    if(mbb_distance((*node)->mbb,data_mbb)==0.0)
                    {
                        selected_node=node;
                        if(_F_find_data(data_mbb,node))
                            return true;
                        selected_node=node;
                    }
                    node=temp_node;
                }
                node=selected_node;
            }
            else
            {
                for(unsigned int i=0;i<(*node)->size;++i)
                {
                    if(((*node)->data[i]->mbb)==data_mbb)
                        return true;
                }
            }
        }
        return false;
    }
    void __RTree__::_F_split_node(__RTreeNode__* node)
    {
        __RTreeNode__* new_node_1=new __RTreeNode__(_V_dimension,_V_node_size,node->type);
        __RTreeNode__* new_node_2=new __RTreeNode__(_V_dimension,_V_node_size,node->type);
        if(node->type)
        {
            std::vector<_T_Type_pair_dis_pos> sorted_data;
            sorted_data.push_back(_T_Type_pair_dis_pos(0.0,node->farthest_node_position()));
            for(unsigned int i=0;i<node->size;++i)
            {
                if(i!=sorted_data[0].second)
                {
                    _T_Type_pair_dis_pos new_data(
                                mbb_distance(node->sons[sorted_data[0].second]->mbb,node->sons[i]->mbb),i);
                    sorted_data.push_back(new_data);
                }
            }
            std::sort(sorted_data.begin(),sorted_data.end());
            unsigned int middle_position=(node->size)>>1;
            for(unsigned int i=0;i<middle_position;++i)
            {
                new_node_1->sons[new_node_1->size]=node->sons[sorted_data[i].second];
                new_node_1->sons[new_node_1->size]->parent=new_node_1;
                new_node_1->sons[new_node_1->size]->pos_in_parent=new_node_1->size;
                ++(new_node_1->size);
            }
            for(unsigned int i=middle_position;i<node->size;++i)
            {
                new_node_2->sons[new_node_2->size]=node->sons[sorted_data[i].second];
                new_node_2->sons[new_node_2->size]->parent=new_node_2;
                new_node_2->sons[new_node_2->size]->pos_in_parent=new_node_2->size;
                ++(new_node_2->size);
            }
        }
        else
        {
            std::vector<_T_Type_pair_dis_pos> sorted_data;
            sorted_data.push_back(_T_Type_pair_dis_pos(0.0,node->farthest_node_position()));
            for(unsigned int i=0;i<node->size;++i)
            {
                if(i!=sorted_data[0].second)
                {
                    _T_Type_pair_dis_pos new_data(
                                mbb_distance(node->data[sorted_data[0].second]->mbb,node->data[i]->mbb),i);
                    sorted_data.push_back(new_data);
                }
            }
            std::sort(sorted_data.begin(),sorted_data.end());
            unsigned int middle_position=(node->size)>>1;
            for(unsigned int i=0;i<middle_position;++i)
                new_node_1->data[new_node_1->size++]=node->data[sorted_data[i].second];
            for(unsigned int i=middle_position;i<node->size;++i)
                new_node_2->data[new_node_2->size++]=node->data[sorted_data[i].second];
        }
        new_node_1->set_mbb();
        new_node_2->set_mbb();
        node->clear();
        if(node->parent)
        {
            __RTreeNode__* temp_node=node;
            unsigned int split_pos=temp_node->pos_in_parent;
            node=node->parent;
            new_node_1->parent=node;
            new_node_2->parent=node;
            node->sons[split_pos]=new_node_1;
            node->sons[node->size]=new_node_2;
            new_node_1->pos_in_parent=split_pos;
            new_node_2->pos_in_parent=node->size;
            ++(node->size);
            delete(temp_node);
            if(node->size==(_V_node_size+2))
                _F_split_node(node);
        }
        else
        {
            node->type=1;
            new_node_1->parent=node;
            new_node_2->parent=node;
            new_node_1->pos_in_parent=0;
            new_node_2->pos_in_parent=1;
            node->sons[0]=new_node_1;
            node->sons[1]=new_node_2;
            node->size=2;
        }
    }
    void __RTree__::_F_merge_node(__RTreeNode__* node)
    {
        bool node_type=node->type;
        unsigned int son_in_underflow=node->pos_in_parent;
        node=node->parent;
        std::vector<_T_Type_pair_dis_pos> sorted_data;
        std::vector<_T_Type_pair_dis_pos> sorted_distance;
        for(unsigned int i=0;i<node->size;++i)
        {
            if(i!=son_in_underflow)
            {
                double son_distance=mbb_distance(node->sons[son_in_underflow]->mbb,node->sons[i]->mbb);
                if(node->sons[i]->size>_V_min_node_size)
                    sorted_data.push_back(_T_Type_pair_dis_pos(son_distance,i));
                sorted_distance.push_back(_T_Type_pair_dis_pos(son_distance,i));
            }
        }
        if(sorted_data.size())
        {
            sorted_distance.clear();
            std::sort(sorted_data.begin(),sorted_data.end());
            __RTreeNode__* donator_son=node->sons[sorted_data[0].second];
            sorted_data.clear();
            if(node_type)
            {
                for(unsigned int i=0;i<donator_son->size;++i)
                {
                    _T_Type_pair_dis_pos new_data(
                                mbb_distance(donator_son->sons[i]->mbb,node->sons[son_in_underflow]->mbb),i);
                    sorted_data.push_back(new_data);
                }
                std::sort(sorted_data.begin(),sorted_data.end());
                unsigned int new_owner=sorted_data[0].second;
                sorted_data.clear();
                donator_son->sons[new_owner]->pos_in_parent=node->sons[son_in_underflow]->size;
                donator_son->sons[new_owner]->parent=node->sons[son_in_underflow];
                unsigned int temp_size=node->sons[son_in_underflow]->size++;
                node->sons[son_in_underflow]->sons[temp_size]=donator_son->sons[new_owner];
                donator_son->sons[--(donator_son->size)]->pos_in_parent=new_owner;
                donator_son->sons[new_owner]=donator_son->sons[donator_son->size];
                donator_son->sons[donator_son->size]=nullptr;
            }
            else
            {
                for(unsigned int i=0;i<donator_son->size;++i)
                {
                    _T_Type_pair_dis_pos new_data(
                                mbb_distance(donator_son->data[i]->mbb,node->sons[son_in_underflow]->mbb),i);
                    sorted_data.push_back(new_data);
                }
                std::sort(sorted_data.begin(),sorted_data.end());
                unsigned int new_owner=sorted_data[0].second;
                sorted_data.clear();
                unsigned int temp_size=node->sons[son_in_underflow]->size++;
                node->sons[son_in_underflow]->data[temp_size]=donator_son->data[new_owner];
                donator_son->data[new_owner]=donator_son->data[--(donator_son->size)];
                donator_son->data[donator_son->size]=nullptr;
            }
        }
        else
        {
            sorted_data.clear();
            sort(sorted_distance.begin(),sorted_distance.end());
            __RTreeNode__* owner_son=node->sons[sorted_distance[0].second];
            __RTreeNode__* node_to_remove=node->sons[son_in_underflow];
            sorted_distance.clear();
            --(node->size);
            node->sons[son_in_underflow]=node->sons[node->size];
            node->sons[son_in_underflow]->pos_in_parent=son_in_underflow;
            node->sons[node->size]=nullptr;
            if(node_type)
            {
                for(unsigned int k=0;k<node_to_remove->size;++k)
                {
                    owner_son->sons[owner_son->size]=node_to_remove->sons[k];
                    owner_son->sons[owner_son->size]->pos_in_parent=owner_son->size;
                    owner_son->sons[owner_son->size++]->parent=owner_son;
                }
            }
            else
            {
                for(unsigned int k=0;k<node_to_remove->size;++k)
                    owner_son->data[owner_son->size++]=node_to_remove->data[k];
            }
            node_to_remove->clear();
            delete(node_to_remove);
            if(node->parent)
            {
                if(node->size<_V_min_node_size)
                    _F_merge_node(node);
            }
            else
            {
                if(node->size==1)
                {
                    __RTreeNode__* new_root=node->sons[0];
                    node->clear();
                    _V_root=new_root;
                    _V_root->parent=nullptr;
                    delete(node);
                    node=_V_root;
                }
            }
        }
    }
    void __RTree__::_F_range_query(std::list<void*>* data_list,__RTreeNode__* node,MBB mbb)
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
                if(mbb_distance(mbb,node->data[i]->mbb)==0.0)
                    data_list->push_back(node->data[i]->data);
            }
        }
    }
    __RTree__::__RTree__(unsigned int dimension,unsigned int node_size)
    {
        _V_dimension=dimension;
        _V_node_size=node_size;
        _V_min_node_size=(_V_node_size+1)/2;
        _V_root=new __RTreeNode__(_V_dimension,_V_node_size);
    }
    unsigned int __RTree__::size()
    {
        return _V_size;
    }
    void __RTree__::clear()
    {
        delete(_V_root);
        _V_root=new __RTreeNode__(_V_dimension,_V_node_size);
        _V_size=0;
    }
    bool __RTree__::find(MBB data_mbb)
    {
        if(data_mbb.dimension==_V_dimension)
        {
            __RTreeNode__** leaf=&(_V_root);
            return _F_find_data(data_mbb,leaf);
        }
        return false;
    }
    bool __RTree__::insert(void* new_data,MBB data_mbb)
    {
        if(data_mbb.dimension!=_V_dimension)
            return false;
        __RTreeNode__** leaf=&(_V_root);
        if(_F_find_data(data_mbb,leaf))
            return false;
        _F_target_node(data_mbb,leaf);
        (*leaf)->data[(*leaf)->size++]=new __RTreeDataNode__(new_data,data_mbb);
        _V_root->set_metadata();
        if((*leaf)->size==(_V_node_size+1))
        {
            _F_split_node(*leaf);
            _V_root->set_metadata();
        }
        ++_V_size;
        return true;
    }
    bool __RTree__::remove(MBB data_mbb)
    {
        if(data_mbb.dimension!=_V_dimension)
            return false;
        __RTreeNode__** leaf=&(_V_root);
        if(_F_find_data(data_mbb,leaf))
        {
            unsigned int i=0;
            while(i<(*leaf)->size)
            {
                if(data_mbb==((*leaf)->data[i]->mbb))
                    break;
                ++i;
            }
            delete((*leaf)->data[i]);
            (*leaf)->data[i]=(*leaf)->data[--((*leaf)->size)];
            (*leaf)->data[(*leaf)->size]=nullptr;
            _V_root->set_metadata();
            if((*leaf)!=_V_root)
            {
                if((*leaf)->size==((_V_node_size-1)/2))
                {
                    _F_merge_node(*leaf);
                    _V_root->set_metadata();
                }
            }
            --_V_size;
            return true;
        }
        return false;
    }
    std::list<void*> __RTree__::range_query(MBB mbb)
    {
        std::list<void*> data_list;
        if(mbb.dimension==_V_dimension)
            _F_range_query(&data_list,_V_root,mbb);
        return data_list;
    }
    __RTreeNode__* __RTree__::get_root_node()
    {
        return _V_root;
    }
    __RTree__::~__RTree__()
    {
        delete(_V_root);
    }
}
