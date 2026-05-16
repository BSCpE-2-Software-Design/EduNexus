#include "EnrollmentEngine.h"

bool EnrollmentEngine::passed(double grade) {
    return grade >= 1.0 && grade <= 3.0;
}

std::vector<std::string> EnrollmentEngine::failedPrereqs(Student* s, Course c) {
    std::vector<std::string> failed;

    for (auto& pre : c.prerequisites) {
        double grade = s->getGrade(pre);

        if (!(grade >= 1.0 && grade <= 3.0)) {
            failed.push_back(pre);
        }
    }

    return failed;
}

bool EnrollmentEngine::checkCoreq(Student* s, Course c) {
    for (auto& co : c.corequisites) {
        double grade = s->getGrade(co);

        if (grade == -1)
            return false;
    }
    return true;
}

bool EnrollmentEngine::isRegular(Student* s) {
    for (auto& c : s->getCompleted()) {
        if (!passed(c.second))
            return false;
    }
    return true;
}