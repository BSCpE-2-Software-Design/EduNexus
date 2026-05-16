#ifndef UI_H
#define UI_H

#include "Student.h"
#include "Course.h"
#include <vector>

class UI {
public:
    static void showThreeColumns(Student* s, std::vector<Course> courses);
};

#endif

