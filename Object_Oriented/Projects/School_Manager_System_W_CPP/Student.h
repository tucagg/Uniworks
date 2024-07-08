#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include <string>

namespace PA3
{
    class Course;
    class Student
    {
    private:
        std::string name;
        int ID;
        Course **courses;
        int courseCount;

    public:
        Student();
        Student(const std::string &name, int ID);
        ~Student();

        void setName(const std::string &name);
        std::string getName() const;

        void setID(int ID);
        int getID() const;

        void addCourse(Course *course);
        void dropCourse(Course *course);
        void setCourseCapacity(int capacity); // Yeni eklendi
        int getCourseCapacity() const; // Yeni eklendi
        int getCourseCount() const;

        Course *getCourse(int index) const;
        
    };
}

#endif // STUDENT_H
