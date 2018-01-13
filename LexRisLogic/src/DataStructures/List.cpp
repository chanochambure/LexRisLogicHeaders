/* List.cpp -- List Data Structure Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/DataStructures/List.h"

namespace LL_DataStructure
{
    __ListNodeBase__::~__ListNodeBase__()
    {
        if(next)
            delete(next);
    }

    void __ListIteratorBase__::_F_get_next()
    {
        if(_V_node)
        {
            _V_prev_node=_V_node;
            _V_node=_V_node->next;
        }
    }

    void __ListBase__::_F_clear()
    {
        _V_size=0;
        if(_V_root.next)
            delete(_V_root.next);
        _V_root.next=nullptr;
        _V_head=&_V_root;
    }
    void __ListBase__::_F_insert(__ListIteratorBase__& position,__ListNodeBase__* node)
    {
        node->next=position._V_node;
        node->prev=position._V_prev_node;
        position._V_prev_node->next=node;
        position._V_node=node;
        if(position._V_node)
            position._V_node->prev=node;
        while(_V_head->next)
            _V_head=_V_head->next;
        ++_V_size;
    }
    void __ListBase__::_F_erase(__ListIteratorBase__& position)
    {
        __ListNodeBase__* to_erase=position._V_node;
        if(to_erase)
        {
            position._V_node=to_erase->next;
            position._V_prev_node->next=position._V_node;
            if(position._V_node)
                position._V_node->prev=position._V_prev_node;
            else
                _V_head=position._V_prev_node;
            to_erase->prev=nullptr;
            to_erase->next=nullptr;
            delete(to_erase);
            --_V_size;
        }
    }
}
