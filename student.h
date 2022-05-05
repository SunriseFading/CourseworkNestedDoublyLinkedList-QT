#ifndef STUDENT_H
#define STUDENT_H
#include "people.h"

class Student : public People
{
    QString department;
    QString group;

public:
    Student() : People() {}
    Student(QString &id1, QString &full_name1, QString &age1, QString &department1, QString &group1) : People(id1, full_name1, age1), department(department1), group(group1) {}
    QString get_type() { return "Student"; }
    QString get_department() { return department; }
    QString get_group() { return group; }
};

#endif // STUDENT_H
