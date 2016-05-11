#ifndef INCLUDED_LL_DATASTRUCTURE_RTREE_H
#define INCLUDED_LL_DATASTRUCTURE_RTREE_H

#include <algorithm>
#include <stack>
#include <vector>
#include <list>
#include "../MathStructures/Point.h"

namespace LL_DataStructure
{
    template<int DIMENSION>
    struct MBB
    {
        LL_MathStructure::Point<DIMENSION> first_point;
        LL_MathStructure::Point<DIMENSION> second_point;
        bool operator == (MBB<DIMENSION> other_mbb)
        {
            return ((first_point==other_mbb.first_point) and (second_point==other_mbb.second_point));
        }
    };

    template<int DIMENSION>
    double mbb_distance(MBB<DIMENSION> first_mbb,MBB<DIMENSION> second_mbb)
    {
        double acumulator=0;
        for(int i=0;i<DIMENSION;++i)
        {
            double min_distance=std::max(first_mbb.first_point[i],second_mbb.first_point[i])-
                                std::min(first_mbb.second_point[i],second_mbb.second_point[i]);
            if(min_distance>0)
                acumulator+=pow(min_distance,2);
        }
        return sqrt(acumulator);
    }

    template<typename T,int DIMENSION,unsigned int NODE_SIZE>
    class RTree
    {
        private:
            typedef std::pair<double,unsigned int> _T_Type_pair_dis_pos;
            const unsigned int _C_MIN_NODE_SIZE=(NODE_SIZE+1)/2;
            struct _S_Structure_DataNode
            {
                _S_Structure_DataNode(T new_data,MBB<DIMENSION> new_mbb)
                {
                    data=new_data;
                    mbb=new_mbb;
                }
                MBB<DIMENSION> mbb;
                T data;
            };
            struct _S_Structure_Node
            {
                _S_Structure_Node(bool node_type=false)
                {
                    type=node_type;
                    for(unsigned int i=0;i<(NODE_SIZE+1);++i)
                    {
                        data[i]=nullptr;
                        sons[i]=nullptr;
                    }
                    sons[NODE_SIZE+1]=nullptr;
                }
                MBB<DIMENSION> mbb;
                bool type=false;
                unsigned int size=0;
                unsigned int pos_in_parent=0;
                _S_Structure_Node* parent=nullptr;
                _S_Structure_Node* sons[NODE_SIZE+2];
                _S_Structure_DataNode* data[NODE_SIZE+1];
                void set_mbb()
                {
                    if(size)
                    {
                        if(type)
                        {
                            mbb=sons[0]->mbb;
                            for(unsigned int i=1;i<size;++i)
                            {
                                for(unsigned int j=0;j<DIMENSION;++j)
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
                                for(unsigned int j=0;j<DIMENSION;++j)
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
                void set_metadata()
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
                                for(unsigned int j=0;j<DIMENSION;++j)
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
                                for(unsigned int j=0;j<DIMENSION;++j)
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
                unsigned int farthest_node_position()
                {
                    unsigned int farthest_node=0;
                    if(type)
                    {
                        for(unsigned int i=1;i<size;++i)
                        {
                            for(unsigned int j=0;j<DIMENSION;++j)
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
                            for(unsigned int j=0;j<DIMENSION;++j)
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
                void clear()
                {
                    size=0;
                    for(unsigned int i=0;i<(NODE_SIZE+1);++i)
                    {
                        data[i]=nullptr;
                        sons[i]=nullptr;
                    }
                }
                ~_S_Structure_Node()
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
                }
            };
            _S_Structure_Node* _V_root=nullptr;
            unsigned int _V_size=0;
            MBB<DIMENSION> (*_P_Function_to_mbb)(T)=nullptr;
            void _F_target_node(MBB<DIMENSION> new_mbb,_S_Structure_Node**& target_node)
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
            bool _F_find_data(T data,MBB<DIMENSION> data_mbb,_S_Structure_Node**& node)
            {
                if(*node)
                {
                    if((*node)->type)
                    {
                        _S_Structure_Node** temp_node=node;
                        _S_Structure_Node** selected_node=node;
                        for(unsigned int i=0;i<(*node)->size;++i)
                        {
                            node=&((*node)->sons[i]);
                            if(mbb_distance((*node)->mbb,data_mbb)==0)
                            {
                                selected_node=node;
                                if(_F_find_data(data,data_mbb,node))
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
                            if(((*node)->data[i]->data)==data)
                                return true;
                        }
                    }
                }
                return false;
            }
            void _F_split_node(_S_Structure_Node* node)
            {
                _S_Structure_Node* new_node_1=new _S_Structure_Node(node->type);
                _S_Structure_Node* new_node_2=new _S_Structure_Node(node->type);
                if(node->type)
                {
                    std::vector<_T_Type_pair_dis_pos> sorted_data;
                    sorted_data.push_back(_T_Type_pair_dis_pos(0,node->farthest_node_position()));
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
                    sorted_data.push_back(_T_Type_pair_dis_pos(0,node->farthest_node_position()));
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
                    _S_Structure_Node* temp_node=node;
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
                    if(node->size==(NODE_SIZE+2))
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
            void _F_merge_node(_S_Structure_Node* node)
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
                        if(node->sons[i]->size>_C_MIN_NODE_SIZE)
                            sorted_data.push_back(_T_Type_pair_dis_pos(son_distance,i));
                        sorted_distance.push_back(_T_Type_pair_dis_pos(son_distance,i));
                    }
                }
                if(sorted_data.size())
                {
                    sorted_distance.clear();
                    std::sort(sorted_data.begin(),sorted_data.end());
                    _S_Structure_Node* donator_son=node->sons[sorted_data[0].second];
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
                    _S_Structure_Node* owner_son=node->sons[sorted_distance[0].second];
                    _S_Structure_Node* node_to_remove=node->sons[son_in_underflow];
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
                        if(node->size<_C_MIN_NODE_SIZE)
                            _F_merge_node(node);
                    }
                    else
                    {
                        if(node->size==1)
                        {
                            _S_Structure_Node* new_root=node->sons[0];
                            node->clear();
                            _V_root=new_root;
                            _V_root->parent=nullptr;
                            delete(node);
                            node=_V_root;
                        }
                    }
                }
            }
            void _F_range_query(std::list<T>* data_list,_S_Structure_Node* node,MBB<DIMENSION> mbb)
            {
                if(node->type)
                {
                    for(unsigned int i=0;i<node->size;++i)
                    {
                        if(mbb_distance(mbb,node->sons[i]->mbb)==0)
                            _F_range_query(data_list,node->sons[i],mbb);
                    }
                }
                else
                {
                    for(unsigned int i=0;i<node->size;++i)
                    {
                        if(mbb_distance(mbb,node->data[i]->mbb)==0)
                            data_list->push_back(node->data[i]->data);
                    }
                }
            }
        public:
            RTree(MBB<DIMENSION> (*Function_to_mbb)(T))
            {
                _P_Function_to_mbb=Function_to_mbb;
                _V_root=new _S_Structure_Node;
            }
            class iterator
            {
                private:
                    typedef std::pair<unsigned int,_S_Structure_Node*> _T_Type_stack_element;
                    std::stack<_T_Type_stack_element> _V_stack;
                    void _F_get_next()
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
                                _V_stack.push(_T_Type_stack_element(0,_V_stack.top().second->sons[_V_stack.top().first++]));
                            else
                                _V_stack.pop();
                        }
                    }
                public:
                    iterator(_S_Structure_Node* root_node=nullptr)
                    {
                        if(root_node)
                        {
                            if(root_node->size)
                                _V_stack.push(_T_Type_stack_element(0,root_node));
                            if(root_node->type)
                                _F_get_next();
                        }
                    }
                    iterator operator = (iterator another_iterator)
                    {
                        _V_stack=another_iterator._V_stack;
                        return (*this);
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
                    T operator * ()
                    {
                        return ((_V_stack.top().second)->data[_V_stack.top().first])->data;
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
                _V_root=new _S_Structure_Node;
                _V_size=0;
            }
            bool find(T data)
            {
                _S_Structure_Node** leaf=&(_V_root);
                return _F_find_data(data,_P_Function_to_mbb(data),leaf);
            }
            bool insert(T new_data)
            {
                MBB<DIMENSION> mbb=_P_Function_to_mbb(new_data);
                _S_Structure_Node** leaf=&(_V_root);
                if(_F_find_data(new_data,mbb,leaf))
                    return false;
                _F_target_node(mbb,leaf);
                (*leaf)->data[(*leaf)->size++]=new _S_Structure_DataNode(new_data,mbb);
                _V_root->set_metadata();
                if((*leaf)->size==(NODE_SIZE+1))
                {
                    _F_split_node(*leaf);
                    _V_root->set_metadata();
                }
                ++_V_size;
                return true;
            }
            bool remove(T data_to_remove)
            {
                MBB<DIMENSION> mbb=_P_Function_to_mbb(data_to_remove);
                _S_Structure_Node** leaf=&(_V_root);
                if(_F_find_data(data_to_remove,mbb,leaf))
                {
                    unsigned int i=0;
                    while(i<(*leaf)->size)
                    {
                        if(data_to_remove==((*leaf)->data[i]->data))
                            break;
                        ++i;
                    }
                    delete((*leaf)->data[i]);
                    (*leaf)->data[i]=(*leaf)->data[--((*leaf)->size)];
                    (*leaf)->data[(*leaf)->size]=nullptr;
                    _V_root->set_metadata();
                    if((*leaf)!=_V_root)
                    {
                        if((*leaf)->size==((NODE_SIZE-1)/2))
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
            std::list<T> range_query(MBB<DIMENSION> mbb)
            {
                std::list<T> data_list;
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
