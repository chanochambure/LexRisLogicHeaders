/* RTree.cpp -- R-Tree Data Structure Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/DataStructures/RTree.h"

namespace LL_DataStructure
{
    __RTreeDataNodeBase__::~__RTreeDataNodeBase__()
    {
    }

    __RTreeNodeBase__::__RTreeNodeBase__(unsigned int new_dimension,unsigned int new_node_size,bool node_type)
    {
        dimension=new_dimension;
        node_size=new_node_size;
        mbb.set_dimension(dimension);
        type=node_type;
        data=new __RTreeDataNodeBase__*[new_node_size+1];
        sons=new __RTreeNodeBase__*[new_node_size+2];
        for(unsigned int i=0;i<(new_node_size+1);++i)
        {
            data[i]=nullptr;
            sons[i]=nullptr;
        }
        sons[new_node_size+1]=nullptr;
    }
    void __RTreeNodeBase__::set_mbb()
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
    void __RTreeNodeBase__::set_metadata()
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
    unsigned int __RTreeNodeBase__::farthest_node_position()
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
    void __RTreeNodeBase__::clear()
    {
        size=0;
        for(unsigned int i=0;i<(node_size+1);++i)
        {
            data[i]=nullptr;
            sons[i]=nullptr;
        }
    }
    __RTreeNodeBase__::~__RTreeNodeBase__()
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

    void __RTreeIteratorBase__::_F_get_next()
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
    void __RTreeIteratorBase__::_F_set_data(__RTreeNodeBase__* root_node)
    {
        if(root_node)
        {
            if(root_node->size)
                _V_stack.push(_T_Type_item(0,root_node));
            if(root_node->type)
                _F_get_next();
        }
    }

    void __RTreeBase__::_F_target_node(LL_MathStructure::MBB new_mbb,__RTreeNodeBase__**& target_node)
    {
        while((*target_node)->type)
        {
            unsigned int target_son=0;
            double actual_distance=LL_MathStructure::mbb_distance(new_mbb,(*target_node)->sons[0]->mbb);
            for(unsigned int i=1;i<(*target_node)->size;++i)
            {
                double new_distance=LL_MathStructure::mbb_distance(new_mbb,(*target_node)->sons[i]->mbb);
                if(new_distance<actual_distance)
                {
                    actual_distance=new_distance;
                    target_son=i;
                }
            }
            target_node=&((*target_node)->sons[target_son]);
        }
    }
    bool __RTreeBase__::_F_find_data(LL_MathStructure::MBB data_mbb,__RTreeNodeBase__**& node)
    {
        if(*node)
        {
            if((*node)->type)
            {
                __RTreeNodeBase__** temp_node=node;
                __RTreeNodeBase__** selected_node=node;
                for(unsigned int i=0;i<(*node)->size;++i)
                {
                    node=&((*node)->sons[i]);
                    if(LL_MathStructure::mbb_collision((*node)->mbb,data_mbb))
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
                    if((((*node)->data[i])->mbb)==data_mbb)
                        return true;
                }
            }
        }
        return false;
    }
    void __RTreeBase__::_F_refresh_data(__RTreeNodeBase__** node)
    {
        _V_root->set_metadata();
        if((*node)->size==(_V_node_size+1))
        {
            _F_split_node(*node);
            _V_root->set_metadata();
        }
        ++_V_size;
    }
    bool __RTreeBase__::_F_remove_data(LL_MathStructure::MBB mbb)
    {
        __RTreeNodeBase__** leaf=&(_V_root);
        if(_F_find_data(mbb,leaf))
        {
            unsigned int i=0;
            while(i<(*leaf)->size)
            {
                if(mbb==(((*leaf)->data[i])->mbb))
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
    void __RTreeBase__::_F_split_node(__RTreeNodeBase__* node)
    {
        __RTreeNodeBase__* new_node_1=new __RTreeNodeBase__(_V_dimension,_V_node_size,node->type);
        __RTreeNodeBase__* new_node_2=new __RTreeNodeBase__(_V_dimension,_V_node_size,node->type);
        if(node->type)
        {
            std::vector<_T_Type_pair_dis_pos> sorted_data;
            sorted_data.push_back(_T_Type_pair_dis_pos(0.0,node->farthest_node_position()));
            for(unsigned int i=0;i<node->size;++i)
            {
                if(i!=sorted_data[0].second)
                {
                    _T_Type_pair_dis_pos new_data(
                        LL_MathStructure::mbb_distance(node->sons[sorted_data[0].second]->mbb,node->sons[i]->mbb),i);
                    sorted_data.push_back(new_data);
                }
            }
            std::sort(sorted_data.begin(),sorted_data.end());
            unsigned int MID=(node->size)>>1;
            for(unsigned int i=0;i<MID;++i)
            {
                new_node_1->sons[new_node_1->size]=node->sons[sorted_data[i].second];
                new_node_1->sons[new_node_1->size]->parent=new_node_1;
                new_node_1->sons[new_node_1->size]->pos_in_parent=new_node_1->size;
                ++(new_node_1->size);
            }
            for(unsigned int i=MID;i<node->size;++i)
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
                        LL_MathStructure::mbb_distance(node->data[sorted_data[0].second]->mbb,node->data[i]->mbb),i);
                    sorted_data.push_back(new_data);
                }
            }
            std::sort(sorted_data.begin(),sorted_data.end());
            unsigned int MID=(node->size)>>1;
            for(unsigned int i=0;i<MID;++i)
                new_node_1->data[new_node_1->size++]=node->data[sorted_data[i].second];
            for(unsigned int i=MID;i<node->size;++i)
                new_node_2->data[new_node_2->size++]=node->data[sorted_data[i].second];
        }
        new_node_1->set_mbb();
        new_node_2->set_mbb();
        node->clear();
        if(node->parent)
        {
            __RTreeNodeBase__* temp_node=node;
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
    void __RTreeBase__::_F_merge_node(__RTreeNodeBase__* node)
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
                double distance=LL_MathStructure::mbb_distance(node->sons[son_in_underflow]->mbb,node->sons[i]->mbb);
                if(node->sons[i]->size>_V_min_node_size)
                    sorted_data.push_back(_T_Type_pair_dis_pos(distance,i));
                sorted_distance.push_back(_T_Type_pair_dis_pos(distance,i));
            }
        }
        if(sorted_data.size())
        {
            sorted_distance.clear();
            std::sort(sorted_data.begin(),sorted_data.end());
            __RTreeNodeBase__* donator_son=node->sons[sorted_data[0].second];
            sorted_data.clear();
            if(node_type)
            {
                for(unsigned int i=0;i<donator_son->size;++i)
                {
                    _T_Type_pair_dis_pos new_data(
                        LL_MathStructure::mbb_distance(donator_son->sons[i]->mbb,node->sons[son_in_underflow]->mbb),i);
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
                        LL_MathStructure::mbb_distance(donator_son->data[i]->mbb,node->sons[son_in_underflow]->mbb),i);
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
            __RTreeNodeBase__* owner_son=node->sons[sorted_distance[0].second];
            __RTreeNodeBase__* node_to_remove=node->sons[son_in_underflow];
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
                    __RTreeNodeBase__* new_root=node->sons[0];
                    node->clear();
                    _V_root=new_root;
                    _V_root->parent=nullptr;
                    delete(node);
                    node=_V_root;
                }
            }
        }
    }
}
