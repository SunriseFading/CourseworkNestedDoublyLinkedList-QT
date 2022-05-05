#ifndef LIST1_H
#define LIST1_H
#include "people.h"
#include "professor.h"
#include "student.h"
#include "worker.h"

class List1
{
    People *Head, *Tail;
    int count;

private:
    void add(People *P)
    {
        if (count != 0)
        {
            P->set_prev(Tail);
            P->set_next(Head);
            Head->set_prev(P);
            Tail->set_next(P);
            Head = P;
        }
        else
        {
            P->set_next(P);
            P->set_prev(P);
            Head = Tail = P;
        }
        count++;
    }

public:
    List1()
    {
        Head = Tail = NULL;
        count = 0;
    }
    void add_professor(QString &id1, QString &full_name1, QString &age1, QString &department1, QString &subject1, QString &salary1)
    {
        People *P = new Professor(id1, full_name1, age1, department1, subject1, salary1);
        add(P);
    }
    void add_student(QString &id1, QString &full_name1, QString &age1, QString &department1, QString &group1)
    {
        People *P = new Student(id1, full_name1, age1, department1, group1);
        add(P);
    }
    void add_worker(QString &id1, QString &full_name1, QString &age1, QString &position1, QString &salary1)
    {
        People *P = new Worker(id1, full_name1, age1, position1, salary1);
        add(P);
    }
    void del(int id)
    {
        People *P = Head;
        while ((P->get_id().toInt()) != id)
        {
            P = P->get_next();
        }
        if (count != 1)
        {
            P->get_next()->set_prev(P->get_prev());
            P->get_prev()->set_next(P->get_next());
            if (P == Head)
                Head = P->get_next();
            if (P == Tail)
                Tail = P->get_prev();
        }
        else
            Head = Tail = NULL;
        delete P;
        count--;
    }
    People *get_head() { return Head; }
    People *get_tail() { return Tail; }
    void set_head(People *Obj) { Head = Obj; }
    void set_tail(People *Obj) { Tail = Obj; }
    int get_count() { return count; }
    void set_count(int count1) { count = count1; }
};

#endif // LISTFORPEOPLE_H
