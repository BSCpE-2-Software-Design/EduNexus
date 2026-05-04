#ifndef STUDENTREPO_H
#define STUDENTREPO_H

#include "Student.h"

class StudentRepository {
public:
    static Student* findStudent(std::string name);
};

#endif