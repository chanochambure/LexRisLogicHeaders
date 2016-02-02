#ifndef LL_RTREE_H_INCLUDED
#define LL_RTREE_H_INCLUDED

#include <algorithm>
#include <stack>
#include <vector>
#include <list>
#include "../Mathematical/LL_Point.h"

using namespace std;

template<int D>
struct LL_MBB
{
    LL_Point<D> first_point;
    LL_Point<D> second_point;
    bool operator == (LL_MBB<D> Ot){return ((first_point==Ot.first_point) and (second_point==Ot.second_point));}
};

template<int D>
double mbb_distance(LL_MBB<D> one,LL_MBB<D> two)
{
    double acum=0;;
    for(int i=0;i<D;++i)
    {
        double min_distance=max(one.first_point[i],two.first_point[i])-min(one.second_point[i],two.second_point[i]);
        if(min_distance>0)
            acum+=pow(min_distance,2);
    }
    return sqrt(acum);
}

template<typename T,int D,unsigned int S>
class LL_RTree
{
    private:
        unsigned int _min_size=(S+1)/2;
        typedef pair<double,unsigned int> dis_pos_t;
        struct data_t
        {
            LL_MBB<D> mbb;
            T data;
            data_t(T d,LL_MBB<D> m){data=d;mbb=m;}
        };
        struct node
        {
            LL_MBB<D> mbb;
            bool type=0;
            unsigned int size=0;
            unsigned int pos_in_parent=0;
            node* parent=nullptr;
            node* sons[S+2];
            data_t* data[S+1];
            node(bool t=0)
            {
                type=t;
                for(unsigned int i=0;i<(S+1);++i)
                {
                    data[i]=nullptr;
                    sons[i]=nullptr;
                }
                sons[S+1]=nullptr;
            }
            void set_space()
            {
                if(size==0)
                    return;
                if(type)
                {
                    mbb=sons[0]->mbb;
                    for(unsigned int i=1;i<size;++i)
                    {
                        for(unsigned int j=0;j<D;++j)
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
                        for(unsigned int j=0;j<D;++j)
                        {
                            if(data[i]->mbb.first_point[j]<mbb.first_point[j])
                                mbb.first_point[j]=data[i]->mbb.first_point[j];
                            if(data[i]->mbb.second_point[j]>mbb.second_point[j])
                                mbb.second_point[j]=data[i]->mbb.second_point[j];
                        }
                    }
                }
            }
            unsigned int far_node_position()
            {
                unsigned int minus=0;
                if(type)
                {
                    for(unsigned int i=1;i<size;++i)
                    {
                        for(unsigned int j=0;j<D;++j)
                        {
                            if(sons[minus]->mbb.first_point[j]>sons[i]->mbb.first_point[j])
                            {
                                minus=i;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for(unsigned int i=1;i<size;++i)
                    {
                        for(unsigned int j=0;j<D;++j)
                        {
                            if(data[minus]->mbb.first_point[j]>data[i]->mbb.first_point[j])
                            {
                                minus=i;
                                break;
                            }
                        }
                    }
                }
                return minus;
            }
            void all_data_to_null()
            {
                size=0;
                for(unsigned int i=0;i<(S+1);++i)
                {
                    data[i]=nullptr;
                    sons[i]=nullptr;
                }
            }
            ~node()
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
        node* root=nullptr;
        LL_MBB<D> (*data_to_mbb)(T)=nullptr;
        unsigned int num_elements=0;
        void _choose_leaf_node(LL_MBB<D> mbb,node**& _node)
        {
            while((*_node)->type)
            {
                unsigned int pos=0;
                double new_distance;
                double actual_distance=mbb_distance(mbb,(*_node)->sons[0]->mbb);
                for(unsigned int i=1;i<(*_node)->size;++i)
                {
                    new_distance=mbb_distance(mbb,(*_node)->sons[i]->mbb);
                    if(new_distance<actual_distance)
                    {
                        actual_distance=new_distance;
                        pos=i;
                    }
                }
                _node=&((*_node)->sons[pos]);
            }
        }
        bool _find(T data,LL_MBB<D> mbb,node**& _node)
        {
            if(*_node)
            {
                if((*_node)->type)
                {
                    node** megatemp=_node;
                    node** realtemp=_node;
                    for(unsigned int i=0;i<(*_node)->size;++i)
                    {
                        _node=&((*_node)->sons[i]);
                        if(mbb_distance((*_node)->mbb,mbb)==0)
                        {
                            realtemp=_node;
                            if(_find(data,mbb,_node))
                                return 1;
                        }
                        _node=megatemp;
                    }
                    _node=realtemp;
                }
                else
                {
                    for(unsigned int i=0;i<(*_node)->size;++i)
                    {
                        if(data==(*_node)->data[i]->data)
                            return 1;
                    }
                }
            }
            return 0;
        }
        void _split_node(node* _node)
        {
            node* new_node_1=new node(_node->type);
            node* new_node_2=new node(_node->type);
            if(_node->type)
            {
                vector<dis_pos_t> data_order;
                data_order.push_back(dis_pos_t(0,_node->far_node_position()));
                for(unsigned int i=0;i<_node->size;++i)
                {
                    if(i!=data_order[0].second)
                        data_order.push_back(dis_pos_t(mbb_distance(_node->sons[data_order[0].second]->mbb,_node->sons[i]->mbb),i));
                }
                sort(data_order.begin(),data_order.end());
                unsigned int MID=(_node->size)>>1;
                for(unsigned int i=0;i<MID;++i)
                {
                    _node->sons[data_order[i].second]->parent=new_node_1;
                    _node->sons[data_order[i].second]->pos_in_parent=new_node_1->size;
                    new_node_1->sons[new_node_1->size++]=_node->sons[data_order[i].second];
                }
                for(unsigned int i=MID;i<_node->size;++i)
                {
                    _node->sons[data_order[i].second]->parent=new_node_2;
                    _node->sons[data_order[i].second]->pos_in_parent=new_node_2->size;
                    new_node_2->sons[new_node_2->size++]=_node->sons[data_order[i].second];
                }
            }
            else
            {
                vector<dis_pos_t> data_order;
                data_order.push_back(dis_pos_t(0,_node->far_node_position()));
                for(unsigned int i=0;i<_node->size;++i)
                {
                    if(i!=data_order[0].second)
                        data_order.push_back(dis_pos_t(mbb_distance(_node->data[data_order[0].second]->mbb,_node->data[i]->mbb),i));
                }
                sort(data_order.begin(),data_order.end());
                unsigned int MID=(_node->size)>>1;
                for(unsigned int i=0;i<MID;++i)
                    new_node_1->data[new_node_1->size++]=_node->data[data_order[i].second];
                for(unsigned int i=MID;i<_node->size;++i)
                    new_node_2->data[new_node_2->size++]=_node->data[data_order[i].second];
            }
            new_node_1->set_space();
            new_node_2->set_space();
            _node->all_data_to_null();
            if(_node->parent)
            {
                node* temp=_node;
                unsigned int split_pos=temp->pos_in_parent;
                _node=_node->parent;
                new_node_1->parent=_node;
                new_node_2->parent=_node;
                _node->sons[split_pos]=new_node_1;
                _node->sons[_node->size]=new_node_2;
                new_node_1->pos_in_parent=split_pos;
                new_node_2->pos_in_parent=_node->size++;
                delete(temp);
                if(_node->size==(S+2))
                    _split_node(_node);
                else
                {
                    while(_node)
                    {
                        _node->set_space();
                        _node=(_node->parent);
                    }
                }
            }
            else
            {
                _node->type=1;
                new_node_1->parent=_node;
                new_node_2->parent=_node;
                new_node_1->pos_in_parent=0;
                new_node_2->pos_in_parent=1;
                _node->sons[0]=new_node_1;
                _node->sons[1]=new_node_2;
                _node->size=2;
                _node->set_space();
            }
        }
        void _merge_node(node* _node)
        {
            bool node_type=_node->type;
            unsigned int son_underflow=_node->pos_in_parent;
            _node=_node->parent;
            vector<dis_pos_t> data_order;
            vector<dis_pos_t> data_distance;
            for(unsigned int i=0;i<_node->size;++i)
            {
                if(i!=son_underflow)
                {
                    double dis=mbb_distance(_node->sons[son_underflow]->mbb,_node->sons[i]->mbb);
                    if(_node->sons[i]->size>_min_size)
                        data_order.push_back(dis_pos_t(dis,i));
                    data_distance.push_back(dis_pos_t(dis,i));
                }
            }
            if(data_order.size())
            {
                data_distance.clear();
                sort(data_order.begin(),data_order.end());
                node* donater=_node->sons[data_order[0].second];
                data_order.clear();
                if(node_type)
                {
                    for(unsigned int i=0;i<donater->size;++i)
                        data_order.push_back(dis_pos_t(mbb_distance(donater->sons[i]->mbb,_node->sons[son_underflow]->mbb),i));
                    sort(data_order.begin(),data_order.end());
                    unsigned int change=data_order[0].second;
                    data_order.clear();
                    donater->sons[change]->pos_in_parent=_node->sons[son_underflow]->size;
                    donater->sons[change]->parent=_node->sons[son_underflow];
                    _node->sons[son_underflow]->sons[_node->sons[son_underflow]->size++]=donater->sons[change];
                    donater->sons[change]=donater->sons[--(donater->size)];
                    donater->sons[change]->pos_in_parent=change;
                    donater->sons[donater->size]=nullptr;
                }
                else
                {
                    for(unsigned int i=0;i<donater->size;++i)
                        data_order.push_back(dis_pos_t(mbb_distance(donater->data[i]->mbb,_node->sons[son_underflow]->mbb),i));
                    sort(data_order.begin(),data_order.end());
                    unsigned int change=data_order[0].second;
                    data_order.clear();
                    _node->sons[son_underflow]->data[_node->sons[son_underflow]->size++]=donater->data[change];
                    donater->data[change]=donater->data[--(donater->size)];
                    donater->data[donater->size]=nullptr;
                }
                donater->set_space();
                _node->sons[son_underflow]->set_space();
                _node->set_space();
            }
            else
            {
                data_order.clear();
                sort(data_distance.begin(),data_distance.end());
                node* owner=_node->sons[data_distance[0].second];
                node* removed=_node->sons[son_underflow];
                data_distance.clear();
                _node->sons[son_underflow]=_node->sons[--(_node->size)];
                _node->sons[son_underflow]->pos_in_parent=removed->pos_in_parent;
                _node->sons[_node->size]=nullptr;
                if(node_type)
                {
                    for(unsigned int k=0;k<removed->size;++k)
                    {
                        removed->sons[k]->pos_in_parent=owner->size;
                        removed->sons[k]->parent=owner;
                        owner->sons[owner->size++]=removed->sons[k];
                    }
                }
                else
                {
                    for(unsigned int k=0;k<removed->size;++k)
                        owner->data[owner->size++]=removed->data[k];
                }
                removed->all_data_to_null();
                delete(removed);
                owner->set_space();
                _node->set_space();
                if(_node->parent)
                {
                    if(_node->size<_min_size)
                        _merge_node(_node);
                    else
                    {
                        while(_node)
                        {
                            _node->set_space();
                            _node=(_node->parent);
                        }
                    }
                }
                else
                {
                    if(_node->size==1)
                    {
                        node* new_root=_node->sons[0];
                        _node->all_data_to_null();
                        _node->type=new_root->type;
                        if(_node->type)
                        {
                            for(unsigned int k=0;k<new_root->size;++k)
                            {
                                new_root->sons[k]->parent=_node;
                                new_root->pos_in_parent=_node->size;
                                _node->sons[_node->size++]=new_root->sons[k];
                            }
                        }
                        else
                        {
                            for(unsigned int k=0;k<new_root->size;++k)
                                _node->data[_node->size++]=new_root->data[k];
                        }
                        new_root->all_data_to_null();
                        delete(new_root);
                    }
                }
            }
        }
        void _range_query(list<T>* data,node* _node,LL_MBB<D> mbb)
        {
            if(_node->type)
            {
                for(unsigned int i=0;i<_node->size;++i)
                {
                    if(mbb_distance(mbb,_node->sons[i]->mbb)==0)
                        _range_query(data,_node->sons[i],mbb);
                }
            }
            else
            {
                for(unsigned int i=0;i<_node->size;++i)
                {
                    if(mbb_distance(mbb,_node->data[i]->mbb)==0)
                        data->push_back(_node->data[i]->data);
                }
            }
        }
    public:
        class iterator
        {
            private:
                typedef pair<unsigned int,node*> element_node;
                stack<element_node> iterator_stack;
                void get_next_element()
                {
                    if(iterator_stack.empty())
                        return;
                    if(!(iterator_stack.top().second->type))
                    {
                        if((iterator_stack.top().first++)<(iterator_stack.top().second->size-1))
                            return;
                        else
                            iterator_stack.pop();
                    }
                    while((!iterator_stack.empty()) and iterator_stack.top().second->type)
                    {
                        if(iterator_stack.top().first<(iterator_stack.top().second->size))
                            iterator_stack.push(element_node(0,iterator_stack.top().second->sons[iterator_stack.top().first++]));
                        else
                            iterator_stack.pop();
                    }
                }
            public:
                iterator(node* r=nullptr)
                {
                    if(r)
                    {
                        if(r->size)
                            iterator_stack.push(element_node(0,r));
                        if(r->type)
                            get_next_element();
                    }
                }
                iterator operator=(iterator ot){iterator_stack=ot.iterator_stack;return (*this);}
                iterator operator ++(int)
                {
                    iterator temp=(*this);
                    get_next_element();
                    return temp;
                }
                iterator operator ++()
                {
                    get_next_element();
                    return (*this);
                }
                T operator *(){return ((iterator_stack.top().second)->data[iterator_stack.top().first])->data;}
                bool operator !=(iterator ot){return (iterator_stack!=ot.iterator_stack);}
        };
        LL_RTree(LL_MBB<D> (*to_mbb)(T)){data_to_mbb=to_mbb;root=new node;}
        iterator begin(){return iterator(root);}
        iterator end(){return iterator();}
        unsigned int size(){return num_elements;}
        void clear(){delete(root);root=new node;}
        bool find(T data)
        {
            node** leaf=&(root);
            return _find(data,data_to_mbb(data),leaf);
        }
        bool insert(T data)
        {
            LL_MBB<D> mbb=data_to_mbb(data);
            node** leaf=&(root);
            if(_find(data,mbb,leaf))
                return 0;
            if((*leaf)->type)
                _choose_leaf_node(mbb,leaf);
            (*leaf)->data[(*leaf)->size++]=new data_t(data,mbb);
            node* _node=(*leaf);
            while(_node)
            {
                _node->set_space();
                _node=(_node->parent);
            }
            if((*leaf)->size==(S+1))
                _split_node(*leaf);
            ++num_elements;
            return 1;
        }
        bool remove(T data)
        {
            LL_MBB<D> mbb=data_to_mbb(data);
            node** leaf=&(root);
            if(_find(data,mbb,leaf))
            {
                unsigned int i=0;
                while(i<(*leaf)->size)
                {
                    if(data==(*leaf)->data[i]->data)
                        break;
                    ++i;
                }
                delete((*leaf)->data[i]);
                (*leaf)->data[i]=(*leaf)->data[--(*leaf)->size];
                (*leaf)->data[(*leaf)->size]=nullptr;
                node* _node=(*leaf);
                while(_node)
                {
                    _node->set_space();
                    _node=(_node->parent);
                }
                if((*leaf)!=root)
                {
                    if((*leaf)->size==((S-1)/2))
                        _merge_node(*leaf);
                }
                --num_elements;
                return 1;
            }
            return 0;
        }
        list<T> range_query(LL_MBB<D> mbb)
        {
            list<T> rng_qry;
            _range_query(&rng_qry,root,mbb);
            return rng_qry;
        }
        ~LL_RTree(){delete(root);}
};

#endif // LL_RTREE_H_INCLUDED
