#include <iostream>
#include "ResultViewer.h"
#include "EnrollmentEngine.h"

void ResultViewer::display(Student* s, std::vector<Course> courses) {

    std::cout << "\nSTUDENT: " << s->getName() << "\n";
    std::cout << "Program: " << s->getProgram() << "\n";
    std::cout << "Enrolling Year: " << s->getYear() << "\n";
    std::cout << "Enrolling Semester: " << s->getSemester() << "\n";

    std::cout << "\nCOMPLETED COURSES:\n";

    for (auto& c : s->getCompleted()) {

        std::string code = c.first;
        double grade = c.second;

        int units = 0;
        std::string name = "Unknown";


        for (auto& course : courses) {
            if (course.code == code) {
                units = course.units;
                name = course.name;
                break;
            }
        }

        std::cout << code
            << " - " << name
            << " (" << units << " units)"
            << " - Grade: " << grade;

        if (EnrollmentEngine::passed(grade))
            std::cout << " (PASSED)\n";
        else
            std::cout << " (FAILED)\n";

 
        for (auto& course : courses) {
            for (auto& pre : course.prerequisites) {
                if (pre == code) {
                    std::cout << "   → This course is a prerequisite of: "
                        << course.code << " - " << course.name
                        << " (" << course.units << " units)\n";
                }
            }
        }
    }

    std::cout << "\nCOURSES FOR ENROLLMENT:\n";

    for (auto& c : courses) {

        auto failed = EnrollmentEngine::failedPrereqs(s, c);
        bool coreqOK = EnrollmentEngine::checkCoreq(s, c);

        std::cout << c.code
            << " - " << c.name
            << " (" << c.units << " units)";

        if (failed.empty() && coreqOK) {
            std::cout << " [ELIGIBLE]\n";
        }
        else {
            std::cout << " [NOT ELIGIBLE]";

            if (!failed.empty()) {
                std::cout << " Missing Prereq: ";
                for (auto& f : failed)
                    std::cout << f << " ";
            }

            if (!coreqOK)
                std::cout << " Corequisite not satisfied";

            std::cout << "\n";
        }
    }

    std::cout << "\nSTATUS: ";
    if (EnrollmentEngine::isRegular(s))
        std::cout << "REGULAR\n";
    else
        std::cout << "IRREGULAR\n";
}