#include "Curriculum.h"
#include "JSONLoader.h"

std::vector<Course> Curriculum::getCourses(std::string program, int year, int sem) {
    std::string file = "curriculum_" + program + ".json";
    json data = JSONLoader::load(file);

    std::vector<Course> courses;

    for (auto& c : data["courses"]) {
        if (c["year_level"] == year && c["semester"] == sem) {

            Course course;
            course.code = c["code"];
            course.name = c["name"];
            course.units = c["units"]; 
            course.year = c["year_level"];
            course.semester = c["semester"];

            for (auto& p : c["prerequisites"])
                course.prerequisites.push_back(p);

            for (auto& co : c["corequisites"])
                course.corequisites.push_back(co);

            courses.push_back(course);
        }
    }

    return courses;
}