``` mermaid
classDiagram

class Program {
<<enumeration>>
CpE
ECE
EE
}

class YearLevel {
<<enumeration>>
Year1
Year2
Year3
Year4
}

class Course {
-code: string
-name: string
-units: int
-yearLevel: YearLevel
-prerequisites: vector<string>
+Course()
+Course(c: string, n: string, u: int, y: YearLevel)
+addPrerequisite(prereq: string)
+getCode() string
+getName() string
+getUnits() int
+getYearLevel() YearLevel
+getPrerequisites() vector<string>
}

class Student {
-name: string
-program: Program
-yearLevel: YearLevel
-grades: map<string, double>
+Student()
+Student(n: string, p: Program, y: YearLevel)
+addGrade(courseCode: string, grade: double)
+hasPassed(courseCode: string) bool
+getGrade(courseCode: string) double
+getName() string
+getProgram() Program
+getYearLevel() YearLevel
}

class Curriculum {
-courses: map<string, Course>
+addCourse(course: Course)
+getCourse(code: string) Course
+getAllCourses() map<string, Course>
}

class EnrollmentService {
+checkPrerequisites(student: Student, course: Course) bool
+getEligibleCourses(student: Student, curriculum: Curriculum) vector<string>
}

class InputHandler {
+inputGrade() double
}

Student --> Program : belongs to
Student --> YearLevel : current level
Course --> YearLevel : offered in
Curriculum "1" *-- "many" Course : contains
EnrollmentService ..> Student : evaluates
EnrollmentService ..> Course : checks prerequisites
EnrollmentService ..> Curriculum : retrieves courses
Student --> Course : has grades
InputHandler ..> Student : inputs grades

```
