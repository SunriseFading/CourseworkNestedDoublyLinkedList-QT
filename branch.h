#ifndef BRANCH_H
#define BRANCH_H
#include "list1.h"

struct Address
{
    QString index;
    QString region;
    QString city;
    QString street;
};
class Branch : public List1
{
    QString name;
    struct Address address;
    QString number;
    List1 list;
    Branch *prev;
    Branch *next;

public:
    Branch();
    Branch(QString &name1, QString &index1, QString &region1, QString &city1, QString &street1, QString &number1)
    {
        name = name1;
        address.index = index1;
        address.region = region1;
        address.city = city1;
        address.street = street1;
        number = number1;
        List1();
    }
    void set_next(Branch *Obj) { next = Obj; }
    void set_prev(Branch *Obj) { prev = Obj; }
    Branch *get_next() { return next; }
    Branch *get_prev() { return prev; }
    QString get_name() { return name; }
    QString get_index() { return address.index; }
    QString get_region() { return address.region; }
    QString get_city() { return address.city; }
    QString get_street() { return address.street; }
    QString get_number() { return number; }

};

#endif // BRANCH_H
