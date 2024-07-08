#include <iostream>
#include <cmath>
using namespace std;

class MyInteger
{
public:
    MyInteger();
    MyInteger(int newint);
    void SetInt(int newint);
    int GetInt();
    int operator[](int index);

private:
    int num;
};

MyInteger::MyInteger()
{
    num = 0;
}

MyInteger::MyInteger(int newint)
{
    num = newint;
}

void MyInteger::SetInt(int newint)
{
    num = newint;
}

int MyInteger::GetInt()
{
    return num;
}

int MyInteger::operator[](int index)
{
    int temp;
    if (index < 0)
    {
      cout << "Index out of bounds" << endl;
        return -1;
    }
    else
    {
        temp = (int) (num / (pow(10, index)));
        return temp % 10;
    }

}

int main()
{
    MyInteger num(418);
    cout << num[0] << " " << num[1] << " " << num[2] << endl;
    cout << num[3] << endl;
    cout << num[-1] << endl;
    return 0;
}