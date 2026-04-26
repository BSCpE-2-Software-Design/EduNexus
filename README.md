CLASS DIAGRAM (not final)
``` mermaid
classDiagram

class Student {
  -string name
  -string program
  -int yearLevel
  -int semester
  -map<string, double> completedCourses
  +getName()
  +getProgram()
  +getYearLevel()
  +getSemester()
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
  +getCourseCode()
  +getCourseName()
}

class Curriculum {
  -vector<Course> courses
  +loadFromJSON(filePath)
  +getCoursesByProgram(program)
}

class JSONLoader {
  +loadStudents(filePath)
  +loadCourses(filePath)
}

class EnrollmentEngine {
  +evaluateEligibility(Student, vector<Course>)
  +checkPrerequisites(Student, Course)
  +checkCorequisites(Student, Course)
}

class EligibilityResult {
  -vector<Course> eligibleCourses
  -vector<Course> blockedCourses
  +addEligible(course)
  +addBlocked(course)
}

Student --> Course : completed
Curriculum --> Course : contains
JSONLoader --> Student : creates
JSONLoader --> Course : creates
EnrollmentEngine --> Student
EnrollmentEngine --> Course
EnrollmentEngine --> EligibilityResult
```

SEQUENCE DIAGRAM (not final)
``` mermaid
sequenceDiagram

participant User
participant Main
participant JSONLoader
participant Curriculum
participant Student
participant Engine
participant Result

User ->> Main: Enter student info

Main ->> JSONLoader: loadStudents file
JSONLoader -->> Main: return student data

Main ->> JSONLoader: loadCourses file
JSONLoader -->> Main: return course list

Main ->> Student: create student object

Main ->> Curriculum: filter courses
Curriculum -->> Main: return filtered courses

Main ->> Engine: evaluate eligibility

Engine ->> Student: get completed courses
Engine ->> Curriculum: check prerequisites
Engine ->> Curriculum: check corequisites

Engine ->> Result: store eligible and blocked
Result -->> Main: return results

Main ->> User: display eligible courses
Main ->> User: display blocked courses
```
