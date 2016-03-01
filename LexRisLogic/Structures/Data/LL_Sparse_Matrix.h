#ifndef LL_SPARSE_MATRIX_H_INCLUDED
#define LL_SPARSE_MATRIX_H_INCLUDED

template<typename T>
class LL_SparseMatrix
{
    private:
        unsigned int size_x;
        unsigned int size_y;
        T null_value;
        typedef unsigned int smp_t;
        struct node
        {
            smp_t pos_x;
            smp_t pos_y;
            T data;
            node* next_x=nullptr;
            node* next_y=nullptr;
            node(smp_t x,smp_t y,T dat){pos_x=x;pos_y=y;data=dat;}
            void delete_y_node(){if(next_y){next_y->delete_y_node();delete(next_y);}next_y=nullptr;}
            ~node(){delete_y_node();if(next_x)delete(next_x);next_x=nullptr;}
        };
        class controller
        {
            private:
                T null_value;
                node** X=nullptr;
                node** Y=nullptr;
                smp_t pos_x;
                smp_t pos_y;
                void create_node(T data)
                {
                    node* the_node=new node(pos_x,pos_y,data);
                    the_node->next_x=*X;
                    the_node->next_y=*Y;
                    *X=the_node;
                    *Y=the_node;
                }
                void remove_node()
                {
                    node* the_node=*X;
                    *X=the_node->next_x;
                    *Y=the_node->next_y;
                    the_node->next_x=nullptr;
                    the_node->next_y=nullptr;
                    delete(the_node);
                }
            public:
                controller(node** a,node** b,smp_t px,smp_t py,T t_null){X=a;Y=b;pos_x=px;pos_y=py;null_value=t_null;}
                T get_value()
                {
                    if(((*X) and (*Y)) and ((*X)==(*Y)))
                        return (*((*this).X))->data;
                    return null_value;
                }
                operator T(){return get_value();}
                T operator = (T dat)
                {
                    if(((*X) and (*Y)) and ((*X)==(*Y)))
                    {
                        if(dat!=null_value)
                            (*X)->data=dat;
                        else
                            remove_node();
                    }
                    else if(dat!=null_value)
                        create_node(dat);
                    return dat;
                }
        };
        node** vector_x=nullptr;
        node** vector_y=nullptr;
    public:
        LL_SparseMatrix(smp_t size_in_x,smp_t size_in_y,T t_null)
        {
            size_x=size_in_x;
            size_y=size_in_y;
            null_value=t_null;
            vector_x=new node*[size_x];
            for(unsigned int i=0;i<size_x;i++)
                vector_x[i]=nullptr;
            vector_y=new node*[size_y];
            for(unsigned int i=0;i<size_y;i++)
                vector_y[i]=nullptr;
        }
        controller operator () (smp_t X,smp_t Y)
        {
            node** rootx=&vector_y[Y];
            for(;*rootx and ((*rootx)->pos_x)<X;rootx=&((*rootx)->next_x));
            node** rooty=&vector_x[X];
            for(;*rooty and ((*rooty)->pos_y)<Y;rooty=&((*rooty)->next_y));
            return controller(rootx,rooty,X,Y,null_value);
        }
        smp_t get_size_x(){return size_x;}
        smp_t get_size_y(){return size_y;}
        T get_null_value(){return null_value;}
        void clear()
        {
            if(vector_x[0])
                delete(vector_x[0]);
            delete(vector_x);
            delete(vector_y);
            vector_x=new node*[size_x];
            for(unsigned int i=0;i<size_x;i++)
                vector_x[i]=nullptr;
            vector_y=new node*[size_y];
            for(unsigned int i=0;i<size_y;i++)
                vector_y[i]=nullptr;
        }
        ~LL_SparseMatrix()
        {
            clear();
            delete(vector_x);
            delete(vector_y);
        }
};

#endif // LL_SPARSE_MATRIX_H_INCLUDED
