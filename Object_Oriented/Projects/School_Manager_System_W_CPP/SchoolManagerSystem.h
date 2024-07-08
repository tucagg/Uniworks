#ifndef SCHOOLMANAGERSYSTEM_H
#define SCHOOLMANAGERSYSTEM_H

#include <string>    // <string> başlık dosyasını dahil et
#include "Course.h"  // Course.h başlık dosyasını dahil et
#include "Student.h" // Student.h başlık dosyasını dahil et

namespace PA3 // PA3 ad alanını kullan
{

    class SchoolManagerSystem
    {
    private:
        Course **courses;
        Student **students;
        int courseCount;
        int studentCount;

    public:
        SchoolManagerSystem();
        ~SchoolManagerSystem();

        void addStudent(Student *student);
        void selectStudent(std::string &name, int &ID);
        void deleteStudent(Student *student);
        void addSelectedStudentToACourse(Student *student);
        void dropSelectedStudentFromACourse(Student *student);
        void addCourse(Course *course);
        void selectCourse(std::string &name, std::string &code);
        void deleteCourse(Course *course);
        int listStudentsRegisteredToTheSelectedCourse(Course *course);
        int listCoursesTakenByTheSelectedStudent(Student *student);
        int listCouresesNotTakenByTheSelectedStudent(Student *student);
        int listAllStudents() const;
        int listAllCourses() const;

        void mainMenu();
        void studentMenu();
        void courseMenu();
        void selectedStudentMenu(Student *student);
        void selectedCourseMenu(Course *course);

        void printStudents() const;
        void printCourses() const;

        void takeStudentInfo(std::string &name, int &ID);
        void takeCourseInfo(std::string &name, std::string &code);
    };
}

#endif // SCHOOLMANAGERSYSTEM_H
