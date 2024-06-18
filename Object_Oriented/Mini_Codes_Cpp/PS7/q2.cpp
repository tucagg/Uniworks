#include <iostream>
#include <string>

using namespace std;

template <class T, class V>
class Pair
{
public:
    Pair();
    Pair(T first, V second);
    void set_first(T a);
    void set_second(V a);
    T get_first();
    V get_second();

private:
    T first;
    V second;
};

template <class T, class V>
Pair<T, V>::Pair(T f, V s)
{
    first = f;
    second = s;
}

template <class T, class V>
void Pair<T, V>::set_first(T a) { first = a; }

template <class T, class V>
void Pair<T, V>::set_second(V a) { second = a; }

template <class T, class V>
T Pair<T, V>::get_first() { return first; }

template <class T, class V>
V Pair<T, V>::get_second() { return second; }

int main()
{
    Pair<char, char> p('A', 'B');
    cout << "First is " << p.get_first() << endl;
    p.set_first('Z');
    cout << "First changed to " << p.get_first() << endl;
    cout << "The pair is " << p.get_first() << ", " << p.get_second() << endl;

    Pair<int, string> p2(34, "Bill");
    Pair<string, int> pe("Bill", 34);
    cout << "The pair is " << p2.get_first() << ", " << p2.get_second() << endl;
    return 0;
}