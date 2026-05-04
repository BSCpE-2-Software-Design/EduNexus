#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

class Course {
public:
    std::string code;
    std::string name;
    int units;
    int year;
    int semester;
    std::vector<std::string> prerequisites;
    std::vector<std::string> corequisites;
};

#endif