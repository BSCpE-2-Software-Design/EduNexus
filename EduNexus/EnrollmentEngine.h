#ifndef ENGINE_H
#define ENGINE_H

#include "Student.h"
#include "Course.h"
#include <vector>

class EnrollmentEngine {
public:
    static bool passed(double grade);
    static std::vector<std::string> failedPrereqs(Student* s, Course c);
    static bool checkCoreq(Student* s, Course c);
    static bool isRegular(Student* s);
};

#endif
