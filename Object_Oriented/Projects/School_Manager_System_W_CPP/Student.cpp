// Student.cpp
#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>

namespace PA3
{
    Student::Student()
    {
        name = "";
        ID = 0;
        courses = new Course *[0];
        courseCount = 0;
    }

    Student::Student(const std::string &name, int ID)
    {
        this->name = name;
        this->ID = ID;
        courses = new Course *[5];
        courseCount = 0;
    }

    Student::~Student()
    {
        for (int i = 0; i < courseCount; ++i)
        {
            this->getCourse(i)->dropStudent(this);
            this->dropCourse(this->getCourse(i));
            // drop the student from the course
            // drop the course from the student
        }
        delete[] courses; // delete courses array (not courses)
    }

    //setters and getters
    void Student::setName(const std::string &name)
    {
        this->name = name;
    }

    std::string Student::getName() const
    {
        return name;
    }

    void Student::setID(int ID)
    {
        this->ID = ID;
    }

    int Student::getID() const
    {
        return ID;
    }

    void Student::addCourse(Course *course)
    {
        // we are going to add a course to the student
        Course **temp = new Course *[courseCount + 1];
        for (int i = 0; i < courseCount; i++)
        {
            // copy the courses to the new array
            temp[i] = courses[i];
        }
        temp[courseCount] = course;
        delete[] courses;
        courses = temp;
        courseCount++;
    }

    void Student::dropCourse(Course *course)
    {
        int index = -1;
        // search for the course in the courses array
        for (int i = 0; i < courseCount; i++)
        {
            if (courses[i] == course)
            {
                index = i;
                break;
            }
        }
        // if the course is not found return
        if (index == -1)
        {
            return;
        }
        // create a new array with one less element
        Course **tempCourses = new Course *[courseCount - 1];
        // copy the courses to the new array
        for (int i = 0, j = 0; i < courseCount; i++)
        {
            if (i != index)
            {
                tempCourses[j++] = courses[i];
            }
        }
        // delete the old array
        delete[] courses;
        courses = tempCourses;
        courseCount--;

        // drop the student from the course
        course->dropStudent(this);
    }

    void Student::setCourseCapacity(int capacity)
    {
        Course **temp = new Course *[capacity];
        for (int i = 0; i < courseCount; i++)
        {
            temp[i] = courses[i];
        }
        delete[] courses;
        courses = temp;
    }

    int Student::getCourseCapacity() const
    {
        return sizeof(courses) / sizeof(courses[0]);
    }

    int Student::getCourseCount() const
    {
        return courseCount;
    }

    Course *Student::getCourse(int index) const
    {
        return courses[index];
    }
} // namespace PA3