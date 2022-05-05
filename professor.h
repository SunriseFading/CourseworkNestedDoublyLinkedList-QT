#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "people.h"

class Professor : public People
{
    QString department;
    QString subject;
    QString salary;

public:
    Professor() : People() {}
    Professor(QString &id1, QString &full_name1, QString &age1, QString &department1, QString &subject1, QString &salary1) : People(id1, full_name1, age1), department(department1), subject(subject1), salary(salary1) {}
    QString get_type() { return "Professor"; }
    QString get_department() { return department; }
    QString get_subject() { return subject; }
    QString get_salary() { return salary; }
};

#endif // PROFESSOR_H
