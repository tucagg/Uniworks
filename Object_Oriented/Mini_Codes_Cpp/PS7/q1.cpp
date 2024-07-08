#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class Set
{
    public:
        Set();
        void add(T a);
        int get_size();
        T* get_array();
    private:
        vector<T> data;
};

template <class T>
Set<T>::Set() {}

template <class T>
void Set<T>::add(T dat)
{
    int flag = 0;
    for(int a=0 ; a<data.size() ; a++)
        if(data[a] == dat)
            flag = 1;
    if(flag != 1)
        data.push_back(dat);
    else
        cout << "This data is alreadt exist!\n";
}

template <class T>
int Set<T>::get_size() { return data.size(); }

template <class T>
T* Set<T>::get_array()
{
    T* arr = new T[data.size()];
    for(int a=0 ; a<data.size() ; a++)
        arr[a] = data[a];
    return arr;
}

int main()
{
    Set<int> s1;
    Set<string> s2;
    int* intArray = NULL;
    string* stringArray = NULL;
    int i;

    s1.add(10);
    s1.add(20);
    s1.add(15);
    s1.add(20);
    intArray = s1.get_array();
    cout << "Set one has " << s1.get_size() << " items. Here they are: " << endl;
    for(int a=0 ; a<s1.get_size() ; a++)
        cout << intArray[a] << endl;
    
    s2.add("butter");
    s2.add("hamburgers");
    s2.add("pizza");
    s2.add("hotdogs");
    s2.add("pizza");
    stringArray = s2.get_array();
    cout << "Set two has " << s2.get_size() << " items. Here they are: " << endl;
    for(int a=0 ; a<s2.get_size() ; a++)
        cout << stringArray[a] << endl;
    if(stringArray != NULL) delete[] stringArray;

    return 0;
}