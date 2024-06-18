#include <iostream>
#include <cstring>

using namespace std;

const int MAX_DIGITS = 21;

// Reverse the array
void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}
// Add two arrays
void addArrays(int num1[], int num2[], int result[]) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; ++i) {
        int sum = num1[i] + num2[i] + carry;
        if (sum > 9) {
            cout << "Integer overflow!" << endl;
            exit(0);
        }
        result[i] = sum;
        carry = 0;
        if (sum >= 10) {
            carry = 1;
            result[i] = sum - 10;
        }
    }
}
// Find the length of the string
int findLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    if(len > MAX_DIGITS) {
        cout << "Integer overflow" << std::endl;
        exit(0);
    }
    return len;
}   

int main() {
    // Declare variables
    char input1[MAX_DIGITS + 1], input2[MAX_DIGITS + 1];
    int num1[MAX_DIGITS] = {0}, num2[MAX_DIGITS] = {0}, result[MAX_DIGITS] = {0};

    while (true) {
        cout << "Enter the first number (up to " << MAX_DIGITS << " digits): ";
        cin >> input1;

        cout << "Enter the second number (up to " << MAX_DIGITS << " digits): ";
        cin >> input2;
    
        // Convert characters to integers
        int len1 = findLength(input1);
        int len2 = findLength(input2);

        for (int i = 0; i < len1; ++i) {
            num1[i] = input1[len1 - i - 1] - '0';
        }
        for (int i = 0; i < len2; ++i) {
            num2[i] = input2[len2 - i - 1] - '0';
        }
        // Add the two numbers
        addArrays(num1, num2, result);

        if (result[MAX_DIGITS - 1] > 0) {
            cout << "Integer overflow!" << endl;
            break;
        } else {
            reverseArray(result, MAX_DIGITS);
            cout << "Sum: ";
            bool leadingZero = true;
            for (int i = 0; i < MAX_DIGITS; ++i) {
                if (result[i] != 0 || !leadingZero) {
                    cout << result[i];
                    leadingZero = false;
                }
            }
            cout << endl;
        }

        char choice;
        cout << "Do you want to perform another addition? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    return 0;
}
