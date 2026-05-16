#include "StudentRepository.h"
#include "JSONLoader.h"
#include <algorithm>
#include <cctype>

using json = nlohmann::json;

std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


bool isValidNameFormat(const std::string& name) {

    for (char c : name) {

        // allow spaces
        if (c == ' ')
            continue;

        // must be alphabet only
        if (!isalpha(static_cast<unsigned char>(c)))
            return false;
    }

    return true;
}

Student* StudentRepository::findStudent(std::string name) {

    if (!isValidNameFormat(name))
        return nullptr;

    json data = JSONLoader::load("students.json");

    std::string inputLower = toLower(name);

    for (auto& s : data["students"]) {

        std::string storedName = s["name"];
        std::string storedLower = toLower(storedName);

        if (storedLower == inputLower) {

            Student* student = new Student(
                s["name"],
                s["program"],
                s["enrolling_year"],
                s["enrolling_semester"]
            );

            for (auto& c : s["completed_courses"]) {
                student->addCourse(c["code"], c["grade"]);
            }

            return student;
        }
    }

    return nullptr;
}
