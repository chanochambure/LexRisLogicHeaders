/* IntervalTree.h -- Interval-Tree Data Structure Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_DATASTRUCTURE_INTERVALTREE_H
#define INCLUDED_LL_DATASTRUCTURE_INTERVALTREE_H

#include "../LL_Shared.h"

#include <algorithm>
#include <set>
#include <list>
#include <stack>
#include "../MathStructures/Interval.h"

namespace LL_DataStructure
{
    class LL_SHARED IntervalTree
    {
        private:
            struct _S_Structure_SweepLeftToRight
            {
                bool operator() (const LL_MathStructure::Interval& a, const LL_MathStructure::Interval& b) const;
            };
            struct _S_Structure_SweepRightToLeft
            {
                bool operator() (const LL_MathStructure::Interval& a, const LL_MathStructure::Interval& b) const;
            };
            struct _S_Structure_Node
            {
                std::set<LL_MathStructure::Interval,_S_Structure_SweepLeftToRight> increasing;
                std::set<LL_MathStructure::Interval,_S_Structure_SweepRightToLeft> decreasing;
                _S_Structure_Node* left=nullptr;
                _S_Structure_Node* right=nullptr;
                float mid_point=0.0;
                int height=0;
                _S_Structure_Node();
                _S_Structure_Node(LL_MathStructure::Interval interval);
                int get_left_height();
                int get_right_height();
                void update_height();
                ~_S_Structure_Node();
            };
            _S_Structure_Node* _V_root=nullptr;
            unsigned int _V_size=0;
            void _F_clear();
            void _F_copy(_S_Structure_Node** to,const _S_Structure_Node* from);
            void _F_init(const _S_Structure_Node* another_root,unsigned int new_size);
            _S_Structure_Node* _F_balance(_S_Structure_Node* node);
            _S_Structure_Node* _F_left_rotate(_S_Structure_Node* node);
            _S_Structure_Node* _F_right_rotate(_S_Structure_Node* node);
            _S_Structure_Node* _F_get_overlaps(_S_Structure_Node* to,_S_Structure_Node* from);
            _S_Structure_Node* _F_delete_empty_node(_S_Structure_Node* target);
            bool _F_find(_S_Structure_Node* node,const LL_MathStructure::Interval& interval);
            _S_Structure_Node* _F_insert(_S_Structure_Node* node,const LL_MathStructure::Interval& interval);
            _S_Structure_Node* _F_remove(_S_Structure_Node* node,const LL_MathStructure::Interval& interval);
            void _F_range_query(std::list<LL_MathStructure::Interval>* data,_S_Structure_Node* node,
                                const LL_MathStructure::Interval& query);
        public:
            IntervalTree();
            IntervalTree(const IntervalTree& another_interval_tree);
            class iterator
            {
                private:
                    typedef std::set<LL_MathStructure::Interval,_S_Structure_SweepLeftToRight>::iterator _T_Type_iter;
                    typedef std::pair<unsigned int,_T_Type_iter> _T_Type_data;
                    typedef std::pair<_S_Structure_Node*,_T_Type_data> _T_Type_item;
                    std::stack<_T_Type_item> _V_stack;
                    void _F_get_next();
                    void _F_set_data(_S_Structure_Node* root_node);
                public:
                    iterator(_S_Structure_Node* root_node=nullptr);
                    iterator operator ++ (int);
                    iterator operator ++ ();
                    const LL_MathStructure::Interval operator * ();
                    bool operator != (iterator another_iterator);
            };
            iterator begin();
            iterator end();
            unsigned int size();
            void clear();
            bool find(const LL_MathStructure::Interval& interval);
            bool insert(const LL_MathStructure::Interval& interval);
            bool remove(const LL_MathStructure::Interval& interval);
            std::list<LL_MathStructure::Interval> range_query(const LL_MathStructure::Interval& query);
            IntervalTree& operator = (const IntervalTree& another_interval_tree);
            ~IntervalTree();
    };
}

#endif // INCLUDED_LL_DATASTRUCTURE_INTERVALTREE_H
