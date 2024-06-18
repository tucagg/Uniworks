#include <iostream>
using namespace std;

bool asal_mi(int n) {
    if (n <= 1) 
    {
        return false;
    }
    
    for (int i = 2; i * i <= n; ++i) {
        
        if (n % i == 0) 
        {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "Prime numbers between 3 and 100:" << std::endl;
    for (int num = 3; num <= 100; ++num) {
        if (asal_mi(num)) {
            cout << num << endl;
        }
    }
    return 0;
}
