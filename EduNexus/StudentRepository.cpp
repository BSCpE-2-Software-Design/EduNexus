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

    bool newWord = true;

    for (char c : name) {

        if (c == ' ') {
            newWord = true;
            continue;
        }

        if (!isalpha(c))
            return false;


        if (!newWord && isupper(c))
            return false;

        newWord = false;
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