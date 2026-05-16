#include <iostream>
#include <windows.h>
#include "StudentRepository.h"
#include "Curriculum.h"

#include <thread>
#include <chrono>
#include "ui.h"
#include <limits>
#include <cctype>



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

    while (true) {

        system("cls");
        showHeader();

        string name;

        cout << "\n>> Search Student (type 'exit'): ";
        getline(cin, name);

        if (name == "exit")
            break;

        Student* student = StudentRepository::findStudent(name);

        if (!student) {
            cout << "\n! Student not found.\n";

            cout << "\nPress any ENTER to continue...";
            cin.get();

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
        int prevYear = student->getSemester() == 1
            ? student->getYear() - 1
            : student->getYear();

        auto prevCourses = Curriculum::getCourses(
            student->getProgram(),
            prevYear,
            prevSem
        );

        courses.insert(courses.end(), prevCourses.begin(), prevCourses.end());

        cout << "\n==================== RESULT ====================\n";

        UI::showThreeColumns(student, courses);


        char choice;

        while (true) {

            cout << "\nWould you like to search another student?\n";
            cout << "Enter [Y] for Yes to proceed and [N] to exit: ";

            cin >> choice;

            choice = toupper(choice);

            cin.ignore(10000, '\n');

            if (choice == 'Y') {

                delete student;

                system("cls");

                break;
            }
            else if (choice == 'N') {

                delete student;

                cout << "\nThank you for using EDUNEXUS!\n";

                return 0;
            }
            else {

                cout << "\nInvalid input. Please press Y or N only.\n";
            }
        }
    }

    cout << "\nThank you for using EDUNEXUS!\n";

    return 0;
}
