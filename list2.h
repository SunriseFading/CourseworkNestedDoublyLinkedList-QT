#ifndef LIST2_H
#define LIST2_H
#include "branch.h"

class List2
{
    Branch *Head, *Tail;
    int count;

private:
    void add(Branch *B)
    {
        if (count != 0)
        {
            B->set_prev(Tail);
            B->set_next(Head);
            Head->set_prev(B);
            Tail->set_next(B);
            Head = B;
        }
        else
        {
            B->set_next(B);
            B->set_prev(B);
            Head = Tail = B;
        }
        count++;
    }

public:
    List2()
    {
        Head = Tail = NULL;
        count = 0;
    }
    void add_branch(QString &name1, QString &index1, QString &region1, QString &city1, QString &street1, QString &number1)
    {
        Branch *B = new Branch(name1, index1, region1, city1, street1, number1);
        add(B);
    }
    void del(int n)
    {
        int i = 0;
        Branch *B = Tail;
        while (i < n)
        {
            B = B->get_prev();
            i++;
        }
        if (count != 1)
        {
            B->get_next()->set_prev(B->get_prev());
            B->get_prev()->set_next(B->get_next());
            if (B == Head)
                Head = B->get_next();
            if (B == Tail)
                Tail = B->get_prev();
        }
        else
            Head = Tail = NULL;
        delete B;
        count--;
    }
    Branch *get_head() { return Head; }
    Branch *get_tail() { return Tail; }
    void set_head(Branch *Obj) { Head = Obj; }
    void set_tail(Branch *Obj) { Tail = Obj; }
    int get_count() { return count; }
    void set_count(int count1) { count = count1; }
};

#endif // LIST2_H
