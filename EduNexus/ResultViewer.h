#ifndef VIEWER_H
#define VIEWER_H

#include "Student.h"
#include "Course.h"
#include <vector>

class ResultViewer {
public:
    static void display(Student* s, std::vector<Course> courses);
};

#endif