#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>

class Student {
private:
    std::string name;
    std::string program;
    int yearLevel;
    int semester;
    std::map<std::string, double> completedCourses;

public:
    Student(std::string n, std::string p, int y, int s);

    void addCourse(std::string code, double grade);

    std::string getName();
    std::string getProgram();
    int getYear();
    int getSemester();

    double getGrade(std::string code);
    std::map<std::string, double> getCompleted();
};

#endif
