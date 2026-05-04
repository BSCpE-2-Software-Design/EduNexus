#include <iostream>
#include <windows.h>
#include "StudentRepository.h"
#include "Curriculum.h"
#include "ResultViewer.h"
#include <thread>
#include <chrono>



using namespace std;

void showHeader() {


    cout << "==========================================================================\n\n";

    cout << " ███████╗██████╗ ██╗   ██╗███╗   ██╗███████╗██╗  ██╗██╗   ██╗███████╗\n";
    cout << " ██╔════╝██╔══██╗██║   ██║████╗  ██║██╔════╝╚██╗██╔╝██║   ██║██╔════╝\n";
    cout << " █████╗  ██║  ██║██║   ██║██╔██╗ ██║█████╗   ╚███╔╝ ██║   ██║███████╗\n";
    cout << " ██╔══╝  ██║  ██║██║   ██║██║╚██╗██║██╔══╝   ██╔██╗ ██║   ██║╚════██║\n";
    cout << " ███████╗██████╔╝╚██████╔╝██║ ╚████║███████╗██╔╝ ██╗╚██████╔╝███████║\n";
    cout << " ╚══════╝╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n";

    cout << "           Academic Progress & Enrollment Planner System\n";
    cout << "==========================================================================\n";
}


int main() {

    SetConsoleOutputCP(CP_UTF8);

    showHeader();


    while (true) {
        string name;

        cout << "\n>> Search Student (type 'exit'): ";
        getline(cin, name);

        if (name == "exit")
            break;

        Student* student = StudentRepository::findStudent(name);

        if (!student) {
            cout << "\n[!] Student not found.\n";
            continue;
        }

        cout << "\nLoading data";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        cout << "\n";


        auto courses = Curriculum::getCourses(
            student->getProgram(),
            student->getYear(),
            student->getSemester()
        );


        int prevSem = student->getSemester() == 1 ? 2 : 1;
        int prevYear = student->getSemester() == 1 ? student->getYear() - 1 : student->getYear();

        auto prevCourses = Curriculum::getCourses(
            student->getProgram(),
            prevYear,
            prevSem
        );


        courses.insert(courses.end(), prevCourses.begin(), prevCourses.end());

        cout << "\n==================== RESULT ====================\n";
        ResultViewer::display(student, courses);
        cout << "================================================\n";

        delete student; 
    }

    cout << "\nThank you for using EDUNEXUS!\n";

    return 0;
}