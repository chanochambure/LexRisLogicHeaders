/* List.h -- List Data Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_DATASTRUCTURE_LIST_H
#define INCLUDED_LL_DATASTRUCTURE_LIST_H

#include "../LL_Shared.h"

namespace LL_DataStructure
{
    struct LL_SHARED __ListNodeBase__
    {
        bool enabled=false;
        __ListNodeBase__* prev=nullptr;
        __ListNodeBase__* next=nullptr;
        __ListNodeBase__* prev_enabled=nullptr;
        __ListNodeBase__* next_enabled=nullptr;
        void enable();
        virtual ~__ListNodeBase__();
    };

    class LL_SHARED __ListBase__;

    class LL_SHARED __ListIteratorBase__
    {
        friend __ListBase__;
        protected:
            __ListNodeBase__* _V_node=nullptr;
            __ListNodeBase__* _V_prev_node=nullptr;
            void _F_get_prev();
            void _F_get_next();
            void _F_get_prev_enabled();
            void _F_get_next_enabled();
    };

    class LL_SHARED __ListBase__
    {
        protected:
            __ListNodeBase__ _V_root;
            __ListNodeBase__* _V_head;
            unsigned int _V_size=0;
            void _F_clear();
            void _F_insert(__ListIteratorBase__& position,__ListNodeBase__* node);
            void _F_erase(__ListIteratorBase__& position);
            void _F_enable();
            void _F_disable(__ListIteratorBase__& position);
        public:
            __ListBase__();
    };

    template<typename T>
    class List:public __ListBase__
    {
        private:
            struct _S_Structure_Node:public __ListNodeBase__
            {
                T data;
            };
            void _F_init(const __ListNodeBase__* another_root)
            {
                if(another_root)
                {
                    _F_clear();
                    _S_Structure_Node* pointer=dynamic_cast<_S_Structure_Node*>
                                               (const_cast<__ListNodeBase__*>(another_root->next));
                    while(pointer)
                    {
                        insert(end(),pointer->data);
                        pointer=dynamic_cast<_S_Structure_Node*>(const_cast<__ListNodeBase__*>(pointer->next));
                    }
                }
            }
        public:
            List()
            {
                this->_F_init(nullptr);
            }
            List(const List<T>& another_list) : __ListBase__()
            {
                this->_F_init(&another_list._V_root);
            }
            class iterator:public __ListIteratorBase__
            {
                public:
                    iterator()
                    {
                    }
                    iterator(__ListNodeBase__* node,__ListNodeBase__* prev_node)
                    {
                        _V_node=node;
                        _V_prev_node=prev_node;
                    }
                    iterator operator -- (int)
                    {
                        iterator temp_iterator=(*this);
                        _F_get_prev();
                        return temp_iterator;
                    }
                    iterator operator -- ()
                    {
                        _F_get_prev();
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
                    T& operator * ()
                    {
                        _S_Structure_Node* pointer=static_cast<_S_Structure_Node*>(_V_node);
                        return pointer->data;
                    }
                    bool operator != (iterator another_iterator)
                    {
                        return (_V_node!=another_iterator._V_node);
                    }
            };
            class Class_EnabledIterator:public __ListIteratorBase__
            {
                public:
                    Class_EnabledIterator()
                    {
                    }
                    Class_EnabledIterator(__ListNodeBase__* node,__ListNodeBase__* prev_node)
                    {
                        _V_node=node;
                        _V_prev_node=prev_node;
                    }
                    T& get_data()
                    {
                        return static_cast<_S_Structure_Node*>(_V_node)->data;
                    }
                    bool is_valid()
                    {
                        return _V_node;
                    }
                    Class_EnabledIterator operator -- (int)
                    {
                        Class_EnabledIterator temp_iterator=(*this);
                        _F_get_prev_enabled();
                        return temp_iterator;
                    }
                    Class_EnabledIterator operator -- ()
                    {
                        _F_get_prev_enabled();
                        return (*this);
                    }
                    Class_EnabledIterator operator ++ (int)
                    {
                        Class_EnabledIterator temp_iterator=(*this);
                        _F_get_next_enabled();
                        return temp_iterator;
                    }
                    Class_EnabledIterator operator ++ ()
                    {
                        _F_get_next_enabled();
                        return (*this);
                    }
            };
            iterator begin()
            {
                return iterator(_V_root.next,&_V_root);
            }
            iterator end()
            {
                return iterator(nullptr,_V_head);
            }
            Class_EnabledIterator get_enabled_iterator()
            {
                return Class_EnabledIterator(_V_root.next_enabled,&_V_root);
            }
            unsigned int size()
            {
                return _V_size;
            }
            void clear()
            {
                _F_clear();
            }
            void push_front(const T& data)
            {
                insert(begin(),data);
            }
            void push_back(const T& data)
            {
                insert(end(),data);
            }
            iterator insert(iterator position,const T& data)
            {
                _S_Structure_Node* node=new _S_Structure_Node;
                node->data=data;
                _F_insert(position,node);
                return position;
            }
            bool remove(const T& data)
            {
                auto temp=begin();
                while(temp!=end())
                {
                    if((*temp)==data)
                    {
                        erase(temp);
                        return true;
                    }
                    ++temp;
                }
                return false;
            }
            iterator erase(iterator position)
            {
                _F_erase(position);
                return position;
            }
            void enable_list()
            {
                _F_enable();
            }
            Class_EnabledIterator disable(Class_EnabledIterator position)
            {
                _F_disable(position);
                return position;
            }
            List& operator = (const List<T>& another_list)
            {
                this->_F_init(&another_list._V_root);
                return (*this);
            }
    };
}

#endif // INCLUDED_LL_DATASTRUCTURE_LIST_H
