#include "Student.h"

Student::Student(std::string n, std::string p, int y, int s)
    : name(n), program(p), yearLevel(y), semester(s) {
}

void Student::addCourse(std::string code, double grade) {
    completedCourses[code] = grade;
}

std::string Student::getName() { return name; }
std::string Student::getProgram() { return program; }
int Student::getYear() { return yearLevel; }
int Student::getSemester() { return semester; }

double Student::getGrade(std::string code) {
    if (completedCourses.count(code))
        return completedCourses[code];
    return -1;
}

std::map<std::string, double> Student::getCompleted() {
    return completedCourses;
}