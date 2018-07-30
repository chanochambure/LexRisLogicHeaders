/* IntervalTree.cpp -- Interval-Tree Data Structure Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/DataStructures/IntervalTree.h"

namespace LL_DataStructure
{
    bool IntervalTree::_S_Structure_SweepLeftToRight::operator() (const LL_MathStructure::Interval& a,
                                                                  const LL_MathStructure::Interval& b) const
    {
        if(a[0]==b[0])
            return a[1]<b[1];
        return a[0]<b[0];
    }

    bool IntervalTree::_S_Structure_SweepRightToLeft::operator() (const LL_MathStructure::Interval& a,
                                                                  const LL_MathStructure::Interval& b) const
    {
        if(a[1]==b[1])
            return a[0]>b[0];
        return a[1]>b[1];
    }
    IntervalTree::_S_Structure_Node::_S_Structure_Node()
    {
    }

    IntervalTree::_S_Structure_Node::_S_Structure_Node(LL_MathStructure::Interval interval)
    {
        decreasing.insert(interval);
        increasing.insert(interval);
        mid_point=interval.get_mid_point();
        height=1;
    }
    int IntervalTree::_S_Structure_Node::get_left_height()
    {
        if(left)
            return left->height;
        return 0;
    }
    int IntervalTree::_S_Structure_Node::get_right_height()
    {
        if(right)
            return right->height;
        return 0;
    }
    void IntervalTree::_S_Structure_Node::update_height()
    {
        height=std::max(get_left_height(),get_right_height())+1;
    }
    IntervalTree::_S_Structure_Node::~_S_Structure_Node()
    {
        if(left)
            delete(left);
        if(right)
            delete(right);
        left=nullptr;
        right=nullptr;
    }

    void IntervalTree::_F_clear()
    {
        if(_V_root)
            delete(_V_root);
        _V_root=nullptr;
        _V_size=0;
    }
    void IntervalTree::_F_copy(_S_Structure_Node** to,const _S_Structure_Node* from)
    {
        if(from)
        {
            (*to)=new _S_Structure_Node();
            (*to)->decreasing=from->decreasing;
            (*to)->increasing=from->increasing;
            (*to)->height=from->height;
            (*to)->mid_point=from->mid_point;
            _F_copy(&((*to)->left),from->left);
            _F_copy(&((*to)->right),from->right);
        }
    }
    void IntervalTree::_F_init(const _S_Structure_Node* another_root,unsigned int new_size)
    {
        if(another_root)
        {
            _F_clear();
            _F_copy(&_V_root,another_root);
        }
        _V_size=new_size;
    }
    IntervalTree::_S_Structure_Node* IntervalTree::_F_balance(_S_Structure_Node* node)
    {
        int status=node->get_left_height()-node->get_right_height();
        if(status<-1)
        {
            if(node->right->get_left_height()>node->right->get_right_height())
                node->right=_F_right_rotate(node->right);
            return _F_left_rotate(node);
        }
        else if(status>1)
        {
            if(node->left->get_right_height()>node->left->get_left_height())
                node->left=_F_left_rotate(node->left);
            return _F_right_rotate(node);
        }
        return node;
    }
    IntervalTree::_S_Structure_Node* IntervalTree::_F_left_rotate(_S_Structure_Node* node)
    {
        _S_Structure_Node* head=node->right;
        node->right=head->left;
        head->left=node;
        node->update_height();
        head->left=_F_get_overlaps(head,node);
        return head;
    }
    IntervalTree::_S_Structure_Node* IntervalTree::_F_right_rotate(_S_Structure_Node* node)
    {
        _S_Structure_Node* head=node->left;
        node->left=head->right;
        head->right=node;
        node->update_height();
        head->right=_F_get_overlaps(head,node);
        return head;
    }
    IntervalTree::_S_Structure_Node* IntervalTree::_F_get_overlaps(_S_Structure_Node* to,_S_Structure_Node* from)
    {
        std::list<LL_MathStructure::Interval> temp_list;
        if(to->mid_point<from->mid_point)
        {
            for(auto i=from->increasing.begin();i!=from->increasing.end();++i)
            {
                LL_MathStructure::Interval next=*i;
                if(next.is_right_of(to->mid_point))
                    break;
                temp_list.push_back(next);
            }
        }
        else
        {
            for(auto i=from->decreasing.begin();i!=from->decreasing.end();++i)
            {
                LL_MathStructure::Interval next=*i;
                if(next.is_left_of(to->mid_point))
                    break;
                temp_list.push_back(next);
            }
        }
        for(auto i=temp_list.begin();i!=temp_list.end();++i)
        {
            LL_MathStructure::Interval next=*i;
            auto inc=from->increasing.find(next);
            if(inc != from->increasing.end())
                from->increasing.erase(inc);
            auto dec=from->decreasing.find(next);
            if(dec != from->decreasing.end())
                from->decreasing.erase(dec);
        }
        to->increasing.insert(temp_list.begin(),temp_list.end());
        to->decreasing.insert(temp_list.begin(),temp_list.end());
        if(!from->increasing.size())
            return _F_delete_empty_node(from);
        return from;
    }
    IntervalTree::_S_Structure_Node* IntervalTree::_F_delete_empty_node(_S_Structure_Node* target)
    {
        if(!(target->left) && !(target->right))
        {
            delete(target);
            return nullptr;
        }
        if(!(target->left))
        {
            _S_Structure_Node* new_root=target->right;
            target->right=nullptr;
            delete(target);
            return new_root;
        }
        _S_Structure_Node* node=target->left;
        std::stack<_S_Structure_Node*> new_stack;
        while(node->right)
        {
            new_stack.push(node);
            node=node->right;
        }
        if(!new_stack.empty())
        {
            new_stack.top()->right=node->left;
            node->left=target->left;
        }
        node->right=target->right;
        _S_Structure_Node* new_root=node;
        while(!new_stack.empty())
        {
            node=new_stack.top();
            new_stack.pop();
            if(!new_stack.empty())
                new_stack.top()->right = _F_get_overlaps(new_root,node);
            else
                new_root->left=_F_get_overlaps(new_root,node);
        }
        target->left=nullptr;
        target->right=nullptr;
        delete(target);
        return _F_balance(new_root);
    }
    bool IntervalTree::_F_find(_S_Structure_Node* node,const LL_MathStructure::Interval& interval)
    {
        if(node)
        {
            if(interval.contains(node->mid_point))
            {
                auto result=node->increasing.find(interval);
                if(result!=node->increasing.end())
                    return true;
            }
            else if(interval.is_left_of(node->mid_point))
                return _F_find(node->left,interval);
            else
                return _F_find(node->right,interval);
        }
        return false;
    }
    IntervalTree::_S_Structure_Node* IntervalTree::_F_insert(_S_Structure_Node* node,
                                                             const LL_MathStructure::Interval& interval)
    {
        if(node==nullptr)
        {
            ++_V_size;
            return new _S_Structure_Node(interval);
        }
        if(interval.contains(node->mid_point))
        {
            auto result=node->decreasing.insert(interval);
            if(result.second)
            {
                ++_V_size;
                node->increasing.insert(interval);
            }
            return node;
        }
        else if(interval.is_left_of(node->mid_point))
            node->left=_F_insert(node->left,interval);
        else
            node->right=_F_insert(node->right,interval);
        node->update_height();
        return _F_balance(node);
    }
    IntervalTree::_S_Structure_Node* IntervalTree::_F_remove(_S_Structure_Node* node,
                                                             const LL_MathStructure::Interval& interval)
    {
        if(!node)
            return nullptr;
        if(interval.contains(node->mid_point))
        {
            if(node->decreasing.erase(interval))
            {
                node->increasing.erase(interval);
                --_V_size;
                if(!node->increasing.size())
                    return _F_delete_empty_node(node);
            }
        }
        else if(interval.is_left_of(node->mid_point))
            node->left=_F_remove(node->left,interval);
        else
            node->right=_F_remove(node->right,interval);
        node->update_height();
        return _F_balance(node);
    }
    void IntervalTree::_F_range_query(std::list<LL_MathStructure::Interval>* data,_S_Structure_Node* node,
                                      const LL_MathStructure::Interval& query)
    {
        while(node)
        {
            if(query.contains(node->mid_point))
            {
                data->insert(data->end(),node->increasing.begin(),node->increasing.end());
                _F_range_query(data,node->left,query);
                _F_range_query(data,node->right,query);
                break;
            }
            else if(query.is_left_of(node->mid_point))
            {
                for(auto i=node->increasing.begin();i!=node->increasing.end();++i)
                {
                    LL_MathStructure::Interval interval=*i;
                    if (!query.intersects(interval))
                        break;
                    data->push_back(interval);
                }
                node=node->left;
            }
            else if(query.is_right_of(node->mid_point))
            {
                for(auto i=node->decreasing.begin();i!=node->decreasing.end();++i)
                {
                    LL_MathStructure::Interval interval=*i;
                    if (!query.intersects(interval))
                        break;
                    data->push_back(interval);
                }
                node=node->right;
            }
        }
    }
    IntervalTree::IntervalTree()
    {
        this->_F_init(nullptr,0);
    }
    IntervalTree::IntervalTree(const IntervalTree& another_interval_tree)
    {
        this->_F_init(another_interval_tree._V_root,another_interval_tree._V_size);
    }
    void IntervalTree::iterator::_F_get_next()
    {
        while(true)
        {
            if(_V_stack.empty())
                return;
            _S_Structure_Node* node=_V_stack.top().first;
            switch(_V_stack.top().second.first)
            {
                case 0:
                {
                    if(node->left)
                        _V_stack.push(_T_Type_item(node->left,_T_Type_data(0,node->left->increasing.begin())));
                    else
                        ++_V_stack.top().second.first;
                    break;
                }
                case 1:
                {
                    ++_V_stack.top().second.first;
                    return;
                }
                case 2:
                {
                    ++_V_stack.top().second.second;
                    if(_V_stack.top().second.second!=node->increasing.end())
                        return;
                    ++_V_stack.top().second.first;
                    break;
                }
                case 3:
                {
                    if(node->right)
                        _V_stack.push(_T_Type_item(node->right,_T_Type_data(0,node->right->increasing.begin())));
                    else
                        ++_V_stack.top().second.first;
                    break;
                }
                case 4:
                {
                    _V_stack.pop();
                    if(!_V_stack.empty())
                        ++_V_stack.top().second.first;
                    break;
                }
            }
        }
    }
    void IntervalTree::iterator::_F_set_data(_S_Structure_Node* root_node)
    {
        if(root_node)
        {
            _V_stack.push(_T_Type_item(root_node,_T_Type_data(0,root_node->increasing.begin())));
            _F_get_next();
        }
    }
    IntervalTree::iterator::iterator(_S_Structure_Node* root_node)
    {
        _F_set_data(root_node);
    }
    IntervalTree::iterator IntervalTree::iterator::operator ++ (int)
    {
        iterator temp_iterator=(*this);
        _F_get_next();
        return temp_iterator;
    }
    IntervalTree::iterator IntervalTree::iterator::operator ++ ()
    {
        _F_get_next();
        return (*this);
    }
    const LL_MathStructure::Interval IntervalTree::iterator::operator * ()
    {
        return *(_V_stack.top().second.second);
    }
    bool IntervalTree::iterator::operator != (iterator another_iterator)
    {
        return (_V_stack!=another_iterator._V_stack);
    }
    IntervalTree::iterator IntervalTree::begin()
    {
        return iterator(_V_root);
    }
    IntervalTree::iterator IntervalTree::end()
    {
        return iterator();
    }
    unsigned int IntervalTree::size()
    {
        return _V_size;
    }
    void IntervalTree::clear()
    {
        _F_clear();
    }
    bool IntervalTree::find(const LL_MathStructure::Interval& interval)
    {
        return _F_find(_V_root,interval);
    }
    bool IntervalTree::insert(const LL_MathStructure::Interval& interval)
    {
        unsigned int last_size=_V_size;
        _V_root=_F_insert(_V_root,interval);
        return _V_size!=last_size;
    }
    bool IntervalTree::remove(const LL_MathStructure::Interval& interval)
    {
        if(_V_root)
        {
            unsigned int last_size=_V_size;
            _V_root=_F_remove(_V_root,interval);
            return _V_size!=last_size;
        }
        return false;
    }
    std::list<LL_MathStructure::Interval> IntervalTree::range_query(const LL_MathStructure::Interval& query)
    {
        std::list<LL_MathStructure::Interval> data;
        _F_range_query(&data,_V_root,query);
        return data;
    }
    IntervalTree& IntervalTree::operator = (const IntervalTree& another_interval_tree)
    {
        this->_F_init(another_interval_tree._V_root,another_interval_tree._V_size);
        return (*this);
    }
    IntervalTree::~IntervalTree()
    {
        _F_clear();
    }
}
