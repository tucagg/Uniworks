// SchoolManagerSystem.cpp
#include "SchoolManagerSystem.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>

namespace PA3
{
    //default constructor
    SchoolManagerSystem::SchoolManagerSystem()
    {
        students = new Student *[0];
        studentCount = 0;
        courses = new Course *[0];
        courseCount = 0;
    }

    //destructor
    SchoolManagerSystem::~SchoolManagerSystem()
    {
        //for dangling pointers
        //delete all students and courses
        for (int i = 0; i < studentCount; ++i)
        {
            delete students[i];
        }
        delete[] students;
        for (int i = 0; i < courseCount; ++i)
        {
            delete courses[i];
        }
        delete[] courses;
    }

    void SchoolManagerSystem::addStudent(Student *student)
    {
        // check if the student with the same ID already exists
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i]->getID() == student->getID())
            {
                //std::cout << "A student with the same ID already exists." << std::endl;
                return;
            }
        }
        // make a new temporary array
        Student **tempStudents = new Student *[studentCount + 1];

        // copy the existing students to the temporary array
        for (int i = 0; i < studentCount; ++i)
        {
            tempStudents[i] = students[i];
        }

        // add the new student
        tempStudents[studentCount] = student;

        // delete the previous student array
        delete[] students;

        // assign the new student array
        students = tempStudents;

        // increase the student count
        ++studentCount;
        
    }

    void SchoolManagerSystem::addCourse(Course *course)
    {
        // make a new temporary array
        Course **tempCourses = new Course *[courseCount + 1];

        // copy the existing courses to the temporary array
        for (int i = 0; i < courseCount; ++i)
        {
            tempCourses[i] = courses[i];
        }

        // add the new course
        tempCourses[courseCount] = course;

        // delete the previous course array
        delete[] courses;

        // assign the new course array
        courses = tempCourses;

        // increase the course count
        ++courseCount;
        
    }

    void SchoolManagerSystem::mainMenu()
    {
        int choice;
        do
        {
            std::cout << "0 exit" << std::endl;
            std::cout << "1 student" << std::endl;
            std::cout << "2 course " << std::endl;
            std::cout << "3 list_all_students" << std::endl;
            std::cout << "4 list_all_courses" << std::endl;
            std::cin >> choice;
            switch (choice)
            {
            case 0:
                //std::cout << "Exiting the program..." << std::endl;
                exit(0);
            case 1:
                studentMenu();
                break;
            case 2:
                courseMenu();
                break;
            case 3:
                listAllStudents();
                break;
            case 4:
                listAllCourses();
                break;
            default:
                //std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        } while (choice != 0);
    }

    void SchoolManagerSystem::studentMenu()
    {
        int choice;
        do
        {
            std::cout << "0 up" << std::endl;
            std::cout << "1 add_student" << std::endl;
            std::cout << "2 select_student" << std::endl;
            std::cin >> choice;
            switch (choice)
            {
            case 0:
                mainMenu();
                break;
            case 1:
            {
                std::string name;
                int ID;
                takeStudentInfo(name, ID);
                Student *student = new Student(name, ID);
                addStudent(student);
                break;
            }
            case 2:
            {
                std::string name;
                int ID;
                selectStudent(name, ID);
                break;
            }
            default:
                //std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }

        } while (choice != 0);
    }

    void SchoolManagerSystem::courseMenu()
    {
        int choice;
        do
        {
            std::cout << "0 up" << std::endl;
            std::cout << "1 add_course" << std::endl;
            std::cout << "2 select_course" << std::endl;
            std::cin >> choice;
            switch (choice)
            {
            case 0:
                mainMenu();
                break;
            case 1:
            {
                std::string name;
                std::string code;
                takeCourseInfo(name, code);
                Course *course = new Course(name, code);
                addCourse(course);
                break;
            }
            case 2:
            {
                std::string name;
                std::string code;
                selectCourse(name, code);
                break;
            }
            default:
                //std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        } while (choice != 0);
    }

    void SchoolManagerSystem::selectStudent(std::string &name, int &ID)
    {
        takeStudentInfo(name, ID);
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i]->getName() == name && students[i]->getID() == ID)
            {
                selectedStudentMenu(students[i]);
                break;
            }
        }
    }

    void SchoolManagerSystem::deleteStudent(Student *student)
    {
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i] == student)
            {
                // we found the student, remove from the array
                for (int j = i; j < studentCount - 1; j++)
                {
                    students[j] = students[j + 1];
                }
                delete student;

                // decrease the size of the student array
                Student **tempStudents = new Student *[studentCount - 1];
                for (int j = 0; j < studentCount - 1; j++)
                {
                    tempStudents[j] = students[j];
                }
                delete[] students;
                students = tempStudents;
                --studentCount;

                //std::cout << "Student deleted" << std::endl;
                break;
            }
        }
    }

    void SchoolManagerSystem::deleteCourse(Course *course)
    {
        for (int i = 0; i < courseCount; i++)
        {
            if (courses[i] == course)
            {
                // we found the course remove from the array
                for (int j = i; j < courseCount - 1; j++)
                {
                    courses[j] = courses[j + 1];
                }

                // decrease the size of the course array
                Course **tempCourses = new Course *[courseCount - 1];
                for (int j = 0; j < courseCount - 1; j++)
                {
                    tempCourses[j] = courses[j];
                }
                delete[] courses;
                courses = tempCourses;
                --courseCount;

                // drop all students from the course
                for (int j = 0; j < course->getStudentCount(); j++)
                {
                    course->getStudent(j)->dropCourse(course);
                }
                delete course;
                break;
            }
        }
    }

    void SchoolManagerSystem::addSelectedStudentToACourse(Student *student)
    {
        int courseNum = listCouresesNotTakenByTheSelectedStudent(student);
        int choice;

        do
        {
            std::cin >> choice;
            if (choice > 0 && choice <= courseNum)
            {
                //we found the course and add the student to the course
                student->addCourse(courses[choice - 1]);
                //we add the student to the course
                courses[choice - 1]->addStudent(student);
                selectedStudentMenu(student);
            }
        } while (choice != 0);
        selectedStudentMenu(student);
    }

    void SchoolManagerSystem::dropSelectedStudentFromACourse(Student *student)
    {
        int courseNum = listCoursesTakenByTheSelectedStudent(student);
        int choice;

        do
        {
            std::cin >> choice;
            if (choice == 0)
            {
                selectedStudentMenu(student);
            }
            if (choice > 0 && choice <= courseNum)
            {
                //we found the course and drop the student from the course
                student->dropCourse(student->getCourse(choice - 1));
                //we drop the student from the course
                courses[choice - 1]->dropStudent(student);
                selectedStudentMenu(student);
            }
        } while (choice != 0);
        selectedStudentMenu(student);
    }

    void SchoolManagerSystem::selectCourse(std::string &name, std::string &code)
    {

        takeCourseInfo(name, code);
        for (int i = 0; i < courseCount; i++)
        {
            if (courses[i]->getName() == name && courses[i]->getCode() == code)
            {
                //std::cout << "Course selected." << std::endl;
                // we found the course, show the course menu
                selectedCourseMenu(courses[i]);
                break;
            }
        }
    }

    int SchoolManagerSystem::listStudentsRegisteredToTheSelectedCourse(Course *course)
    {
        int totalStudent = 0;
        for (int i = 0; i < course->getStudentCount(); i++)
        {
            std::cout << course->getStudent(i)->getName() << " " << course->getStudent(i)->getID() << std::endl;
            totalStudent++;
        }

        return totalStudent;
    }

    int SchoolManagerSystem::listAllStudents() const
    {
        for (int i = 0; i < studentCount; i++)
        {
            std::cout  << students[i]->getName() << " " << students[i]->getID() << std::endl;
        }
        return studentCount;
    }

    int SchoolManagerSystem::listAllCourses() const
    {
        for (int i = 0; i < courseCount; i++)
        {
            std::cout << courses[i]->getCode() << " " << courses[i]->getName() << std::endl;
            
        }
        return courseCount;
    }

    int SchoolManagerSystem::listCoursesTakenByTheSelectedStudent(Student *student)
    {
        int totalCourse = 0;
        std::cout << "0 up" << std::endl;
        for (int i = 0; i < student->getCourseCount(); i++)
        {
            std::cout << totalCourse + 1 << " " << student->getCourse(i)->getCode()<< " " << student->getCourse(i)->getName()  << std::endl;
            totalCourse++;
        }

        return totalCourse;
    }

    int SchoolManagerSystem::listCouresesNotTakenByTheSelectedStudent(Student *student)
    {
        int totalCourse = 0;
        std::cout << "0 up" << std::endl;
        for (int i = 0; i < courseCount; i++)
        {
            bool isTaken = false;
            for (int j = 0; j < student->getCourseCount(); j++)
            {
                if (courses[i] == student->getCourse(j))
                {
                    isTaken = true;
                    break;
                }
            }
            if (!isTaken)
            {
                std::cout << totalCourse + 1 << " " << courses[i]->getCode()<< " " << courses[i]->getName()  << std::endl;
                totalCourse++;
            }
        }

        return totalCourse;
    }

    void SchoolManagerSystem::selectedStudentMenu(Student *student)
    {
        int choice;
        do
        {
            std::cout << "0 up" << std::endl;
            std::cout << "1 delete_student" << std::endl;
            std::cout << "3 add_selected_student_to_a_course" << std::endl;
            std::cout << "4 drop_selected_student_from_a_course" << std::endl;

            std::cin >> choice;

            switch (choice)
            {
            case 0:
                studentMenu();
            case 1:
                deleteStudent(student);
                return; 
            case 3:
                addSelectedStudentToACourse(student);
                break;
            case 4:
                dropSelectedStudentFromACourse(student);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        } while (choice != 0);
        studentMenu();
    }

    void SchoolManagerSystem::selectedCourseMenu(Course *course)
    {
        int choice;
        do
        {
            std::cout << "0 up" << std::endl;
            std::cout << "1 delete_course" << std::endl;
            std::cout << "2 list_students_registered_to_the_selected_course" << std::endl;

            std::cin >> choice;

            switch (choice)
            {
            case 0:
                courseMenu();
                break;
            case 1:
                deleteCourse(course);
                return; 
            case 2:
                listStudentsRegisteredToTheSelectedCourse(course);
                break;
            default:
                //std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        } while (choice != 0);
    }

    void SchoolManagerSystem::takeStudentInfo(std::string &name, int &ID)
    {
        std::string input;
        std::string isim, no;
        std::cin.ignore();
        getline(std::cin, input);
        std::string total[10];
        // seperates the input by spaces and puts them into the total array
        int i = 0;
        std::string temp = "";
        for (int j = 0; j < input.length(); j++)
        {
            if (input[j] == ' ')
            {
                total[i] = temp;
                temp = "";
                i++;
            }
            else
            {
                temp += input[j];
            }
        }
        //if there is a space at the end of the last element, remove it
        total[i] = temp;
        if(total[i] == "")
        {
            i--;
        }
        no = total[i];
        for (int j = 0; j < i; j++)
        {
            isim += total[j];
            if (j != i - 1)
            {
                isim += " ";
            }
        }
        //if the first element starts with a space, remove the space
        if (isim[0] == ' ')
        {
            isim = isim.substr(1, isim.length() - 1);
        }

        name = isim;
        ID = std::stoi(no);
    }

    void SchoolManagerSystem::takeCourseInfo(std::string &name, std::string &code)
    {
        std::string input;
        std::string isim, no;
        std::cin.ignore();
        getline(std::cin, input);
        std::string total[10];
        // seperates the input by spaces and puts them into the total arrays
        int i = 0;
        std::string temp = "";
        for (int j = 0; j < input.length(); j++)
        {
            if (input[j] == ' ' && j!=0)
            {
                total[i] = temp;
                temp = "";
                i++;
            }
            else
            {
                temp += input[j];
            }
        }
        //remove the space at the end of the last element
        if (temp[temp.length() - 1] == ' ')
        {
            temp = temp.substr(0, temp.length() - 1);
        }

        total[i] = temp;
        if(total[i] == "")
        {
            i--;
        }
        int k = 0;
        //if the first element starts with a space remove the space
        if (total[0][0] == ' ')
        {
            total[0] = total[0].substr(1, total[0].length() - 1);
        }
        no = total[k];
        for (int j = 1; j <= i; j++)
        {
            isim += total[j];
            if (j != i - 1)
            {
                isim += " ";
            }
        }

        name = isim;
        code = no;
    }

}