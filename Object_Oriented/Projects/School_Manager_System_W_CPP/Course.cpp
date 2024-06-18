// Course.cpp
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>

namespace PA3
{
    //default constructor
    Course::Course()
    {
        name = "";
        code = "";
        students = new Student *[0];
        studentCount = 0;
    }

    //constructor
    Course::Course(const std::string &name, const std::string &code)
    {
        this->name = name;
        this->code = code;
        students = new Student *[0];
        studentCount = 0;
    }

    //destructor
    Course::~Course()
    {
        for (int i = 0; i < studentCount; ++i)
        {
            students[i]->dropCourse(this); // delete course from student
        }
        delete[] students; // delete students array (not students)
    }

    //setters and getters
    void Course::setName(const std::string &name)
    {
        this->name = name;
    }

    std::string Course::getName() const
    {
        return name;
    }

    void Course::setCode(const std::string &code)
    {
        this->code = code;
    }

    std::string Course::getCode() const
    {
        return code;
    }

    //add student to course
    void Course::addStudent(Student *student)
    {
        Student **temp = new Student *[studentCount + 1];
        for (int i = 0; i < studentCount; i++)
        {
            temp[i] = students[i];
        }
        temp[studentCount] = student;
        //we need to delete the old array
        delete[] students;
        students = temp;
        studentCount++;
    }

    //drop student from course
    void Course::dropStudent(Student *student)
    {
        int index = -1;
        // fins student in the array
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i] == student)
            {
                index = i;
                //std::cout << "Student " << student->getName() << " dropped from " << name << " (" << code << ")" << std::endl;
                break;
            }
        }
        // terminate if student not found   
        if (index == -1)
        {
            return;
        }
        // make a new array with one less element
        Student **temp = new Student *[studentCount - 1];
        // copy all elements except the one to be deleted
        for (int i = 0, j = 0; i < studentCount; i++)
        {
            if (i != index)
            {
                temp[j++] = students[i];
            }
        }
        // delete the old array and assign the new array
        delete[] students;
        students = temp;
        studentCount--;
    }

    int Course::getStudentCount() const
    {
        return studentCount;
    }

    Student *Course::getStudent(int index) const
    {
        return students[index];
    }

    void Course::setStudentCount(int studentCount)
    {
        Student **temp = new Student *[studentCount];
        for (int i = 0; i < this->studentCount; i++)
        {
            temp[i] = students[i];
        }
        delete[] students;
        students = temp;
    }

}
// Course.cpp