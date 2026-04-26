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
