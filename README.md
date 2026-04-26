CLASS DIAGRAM (not final)
``` mermaid
classDiagram

class Student {
  -string name
  -string program
  -int yearLevel
  -int semester
  -map<string, double> completedCourses
  -string studentStatus
  +getName()
  +getProgram()
  +getStatus()
  +getGrade(courseCode)
}

class Course {
  -string courseCode
  -string courseName
  -int units
  -int yearLevel
  -int semester
  -vector<string> preRequisites
  -vector<string> coRequisites
}

class StudentRepository {
  +findStudentByName(name)
  +loadFromJSON(file)
}

class Curriculum {
  +getCourses(program, year, semester)
  +loadFromJSON(file)
}

class JSONLoader {
  +readFile(file)
}

class EnrollmentEngine {
  +evaluateEligibility(Student, vector<Course>)
  +checkPrerequisites(Student, Course)
  +checkCorequisites(Student, Course)
  +determineStudentStatus(Student)
}

class ResultViewer {
  +displayStudentInfo(Student)
  +displayCourses()
  +displayEligibility()
}

StudentRepository --> Student
JSONLoader --> StudentRepository
JSONLoader --> Curriculum

Curriculum --> Course
Student --> Course

EnrollmentEngine --> Student
EnrollmentEngine --> Course
EnrollmentEngine --> ResultViewer
```

SEQUENCE DIAGRAM (not final)
``` mermaid
sequenceDiagram

participant 👤User
participant Main
participant JSONLoader
participant StudentRepository
participant Student
participant Curriculum
participant Engine
participant ResultViewer

%% SEARCH STUDENT
User ->> Main: Enter student name

Main ->> JSONLoader: loadStudents JSON
JSONLoader -->> Main: student dataset

Main ->> StudentRepository: findStudentByName(name)
StudentRepository -->> Main: student profile

alt Student found

    Main ->> Student: create student object

    %% SHOW INFO
    Main ->> ResultViewer: display student info

    %% LOAD CURRICULUM
    Main ->> Curriculum: getCourses(program, year, semester)
    Curriculum -->> Main: course list

    %% SHOW COURSES + GRADES
    Main ->> ResultViewer: display completed courses (PASSED/FAILED)

    %% EVALUATION PROCESS
    Main ->> Engine: evaluateEligibility(student, courses)

    loop for each course
        Engine ->> Student: check grade
        Engine ->> Curriculum: check prerequisites
        Engine ->> Curriculum: check co-requisites

        alt prerequisites met
            Engine ->> ResultViewer: mark eligible course
        else not met
            Engine ->> ResultViewer: mark blocked course
        end
    end

    %% DETERMINE STATUS
    Engine ->> Student: determine REGULAR or IRREGULAR

    %% FINAL OUTPUT
    ResultViewer -->> Main: compiled results
    Main ->> User: display eligibility + status

else Student not found
    Main ->> User: display "Student not found"
end
```
