#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Student
{
	public:
		Student();
		~Student();
		void InputData(); 
		void OutputData(); 
		void ResetClasses(); 
		Student& operator=(const Student& rightSide); 
	private:
		string name;
		int numClasses;
		string *classList;
};

Student::Student()
{
	numClasses = 0;
	classList = NULL;
	name = "";
}

Student::~Student()
{
	if(classList != NULL)
	{
		delete [] classList;
	}
}

void Student::ResetClasses()
{
	if(classList != NULL)
	{
		delete [] classList;
		classList = NULL;
	}
	numClasses = 0;
}

void Student::InputData()
{
	ResetClasses();

	cout << "Enter student name:" << endl;
	getline(cin, name);
	cout << "Enter number of classes:" << endl;
	cin >> numClasses;
	cin.ignore(2,'\n'); 
	if(numClasses > 0)
	{
		classList = new string[numClasses];
		for(int i = 0; i < numClasses; i++)
		{
			cout << "Enter name of class " << (i+1) << endl;
			getline(cin, classList[i]);
		}
	}
	cout << endl;
}

void Student::OutputData()
{
	cout << "Name: " << name << endl;
	cout << "Number of classes: " << numClasses << endl;
	for(int i = 0; i < numClasses; i++)
		cout << " class " << (i+1) << ":" << classList[i] << endl;
	cout << endl;
}

Student& Student::operator =(const Student& rightSide)
{
	if(this->classList == rightSide.classList)
		return *this;

	ResetClasses(); 
	name = rightSide.name;
	numClasses = rightSide.numClasses;
	if(numClasses > 0)
	{
		classList = new string[numClasses];
		for(int i = 0; i < numClasses; i++)
			classList[i] = rightSide.classList[i];
	}
	return *this;
}

int main()
{
	Student s1, s2;
	s1.InputData(); 
	cout << "Student 1's data:" << endl;
	s1.OutputData(); 
	cout << endl;
	s2 = s1;
	cout << "Student 2's data after assignment from student 1:" << endl;
	s2.OutputData(); 
	s1.ResetClasses();
	cout << "Student 1's data after reset:" << endl;
	s1.OutputData(); 
	cout << "Student 2's data, should still have original classes:" << endl;
	s2.OutputData(); 
	cout << endl;
	return 0;
}