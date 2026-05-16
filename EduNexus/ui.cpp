#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include "ui.h"
#include "EnrollmentEngine.h"

using namespace std;



vector<string> wrapText(string text, int width) {

    vector<string> lines;

    stringstream ss(text);

    string word, line;

    while (ss >> word) {

        if (line.length() + word.length() + 1 > width) {

            lines.push_back(line);

            line = word;
        }
        else {

            if (!line.empty())
                line += " ";

            line += word;
        }
    }

    if (!line.empty())
        lines.push_back(line);

    return lines;
}



void UI::showThreeColumns(Student* s, vector<Course> courses) {

    int col1 = 30;
    int col2 = 60;
    int col3 = 60;

    cout << "\n\n";

    cout << string(col1 + col2 + col3 + 4, '=') << "\n";

    cout << left
        << "|"
        << setw(col1) << " STUDENT INFORMATION"
        << "|"
        << setw(col2) << " COMPLETED COURSES"
        << "|"
        << setw(col3) << " COURSES FOR ENROLLMENT"
        << "|\n";

    cout << string(col1 + col2 + col3 + 4, '=') << "\n";



    vector<string> col1Lines;
    vector<string> col2Lines;
    vector<string> col3Lines;



    col1Lines.push_back("Name: " + s->getName());
    col1Lines.push_back("Program: " + s->getProgram());
    col1Lines.push_back("Enrolling Year: " + to_string(s->getYear()));
    col1Lines.push_back("Enrolling Semester: " + to_string(s->getSemester()));



    col2Lines.push_back("CODE | COURSE | UNITS | GRADE | REMARKS");
    col2Lines.push_back(string(58, '-'));

    for (auto& c : s->getCompleted()) {

        string code = c.first;
        double grade = c.second;

        int units = 0;
        string name = "Unknown";

        for (auto& course : courses) {
            if (course.code == code) {
                units = course.units;
                name = course.name;
                break;
            }
        }

        string remark = EnrollmentEngine::passed(grade) ? "PASSED" : "FAILED";


        ostringstream gradeStream;
        gradeStream << fixed << setprecision(2) << grade;
        string gradeStr = gradeStream.str();

        string mainLine =
            code + " | " +
            name + " | " +
            to_string(units) + " units | " +
            gradeStr + " | " +
            remark;

        auto wrappedMain = wrapText(mainLine, col2 - 2);

        for (auto& line : wrappedMain)
            col2Lines.push_back(line);

        // prerequisite remarks

        for (auto& course : courses) {

            for (auto& pre : course.prerequisites) {

                if (pre == code) {

                    string prereqLine =
                        "-> This course is a prerequisite of: " +
                        course.code + " - " +
                        course.name +
                        " (" + to_string(course.units) + " units)";

                    auto wrapped = wrapText(prereqLine, col2 - 4);

                    for (auto& line : wrapped)
                        col2Lines.push_back("  " + line);
                }
            }
        }

        col2Lines.push_back("");
    }



    col3Lines.push_back("CODE | COURSE | UNITS | STATUS");
    col3Lines.push_back(string(58, '-'));

    for (auto& c : courses) {

        auto failed = EnrollmentEngine::failedPrereqs(s, c);
        bool coreqOK = EnrollmentEngine::checkCoreq(s, c);

        string line =
            c.code + " | " +
            c.name + " | " +
            to_string(c.units) + " units | ";

        if (failed.empty()) {

            if (c.corequisites.empty() || coreqOK) {

                line += "[ELIGIBLE]";
            }
            else {

                line += "[ELIGIBLE WITH COREQUISITE] Must enroll together with: ";

                for (auto& co : c.corequisites)
                    line += co + " ";
            }
        }
        else {

            line += "[NOT ELIGIBLE] ";

            line += "Missing Prereq: ";

            for (auto& f : failed)
                line += f + " ";
        }

        auto wrapped = wrapText(line, col3 - 2);

        for (auto& w : wrapped)
            col3Lines.push_back(w);

        col3Lines.push_back("");
    }

    // STATUS

    col3Lines.push_back("");

    col3Lines.push_back(
        string("STATUS: ") +
        (EnrollmentEngine::isRegular(s) ? "REGULAR" : "IRREGULAR")
    );



    int maxRows = (int)col1Lines.size();
    if ((int)col2Lines.size() > maxRows) maxRows = (int)col2Lines.size();
    if ((int)col3Lines.size() > maxRows) maxRows = (int)col3Lines.size();


    for (int i = 0; i < maxRows; i++) {

        cout << "|";

        if (i < col1Lines.size())
            cout << setw(col1) << col1Lines[i];
        else
            cout << setw(col1) << "";

        cout << "|";

        if (i < col2Lines.size())
            cout << setw(col2) << col2Lines[i];
        else
            cout << setw(col2) << "";

        cout << "|";

        if (i < col3Lines.size())
            cout << setw(col3) << col3Lines[i];
        else
            cout << setw(col3) << "";

        cout << "|\n";
    }

    cout << string(col1 + col2 + col3 + 4, '=') << "\n";
}

