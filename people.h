#ifndef PEOPLE_H
#define PEOPLE_H
#include <QString>

class People
{
    QString type;
    QString id;
    QString full_name;
    QString age;
    People *next, *prev;

public:
    People();
    People(QString &id1, QString &full_name1, QString &age1) : id(id1), full_name(full_name1), age(age1) {}
    virtual ~People() {}
    People *get_next() { return next; }
    People *get_prev() { return prev; }
    void set_next(People *Obj) { next = Obj; }
    void set_prev(People *Obj) { prev = Obj; }
    virtual QString get_type() { return type; }
    QString get_id() { return id; }
    QString get_full_name() { return full_name; }
    QString get_age() { return age; }
};

#endif // PEOPLE_H
