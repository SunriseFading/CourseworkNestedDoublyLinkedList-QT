#ifndef WORKER_H
#define WORKER_H
#include "people.h"

class Worker : public People
{
    QString position;
    QString salary;

public:
    Worker() : People() {}
    Worker(QString &id1, QString &full_name1, QString &age1, QString &position1, QString &salary1) : People(id1, full_name1, age1), position(position1), salary(salary1) {}
    QString get_type() { return "Worker"; }
    QString get_position() { return position; }
    QString get_salary() { return salary; }
};

#endif // WORKER_H
