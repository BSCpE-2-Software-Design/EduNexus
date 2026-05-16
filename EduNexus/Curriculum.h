#ifndef CURRICULUM_H
#define CURRICULUM_H

#include "Course.h"
#include <vector>

class Curriculum {
public:
    static std::vector<Course> getCourses(std::string program, int year, int sem);
};

#endif
