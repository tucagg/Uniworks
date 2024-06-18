#ifndef COURSE_H
#define COURSE_H
#include <string>

namespace PA3
{
    
    class Student;
    class Course
    {
    private:
        std::string name;
        std::string code;
        Student **students;
        int studentCount;

    public:
        Course();
        Course(const std::string &name, const std::string &code);
        ~Course();

        void setName(const std::string &name);
        std::string getName() const;

        void setCode(const std::string &code);
        std::string getCode() const;

        void addStudent(Student *student);
        void dropStudent(Student *student);

        void setStudentCount(int studentCount);
        int getStudentCount() const;

        Student *getStudent(int index) const;
    };
}

#endif // COURSE_H
