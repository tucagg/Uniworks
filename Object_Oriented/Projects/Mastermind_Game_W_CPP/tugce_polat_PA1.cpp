#include <iostream>
#include <ctime>

using namespace std;

void isContainsValidCharacters(const char arr[], const int n) // it checks if the given array has valid characters
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < '0' || (arr[i] > '9' && arr[i] < 'a') || arr[i] > 'e')
        {
            cout << "E0";
            exit(0);
        }
    }
}

// this function checks if the given array has unique elements
bool isUnique(const char arr[], const int n)
{
    for (int i = n; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[i] == arr[j])
            {
                return false;
            }
        }
    }
    return true;
}
// this function generates a random number and checks if it is unique
void generateRandom(char secretNumber[], const int length)
{
    // i placed 0 at the end of the array to make it easier to do random number generation (when i declare the 0th elementh,i will not use the 15th index of the array)
    char mychar[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', '0'};
    // as i said before i placed 0 at the end of the array to make it easier to do random number generation (i use 14 instead of 15). so first element of the array cannot be 0
    secretNumber[0] = mychar[rand() % 14];
    for (int i = 1; i < length; i++)
    {
        secretNumber[i] = mychar[rand() % 15];
        while (!isUnique(secretNumber, i))
        {
            secretNumber[i] = mychar[rand() % 15];
        }
    }
}

// this function checks if the given array has the same size with the given number
void isSameSize(const char input[], const int n)
{
    int inputLength;
    for (int i = 0; input[i] != '\0'; i++)
    {
        inputLength = i;
    }
    inputLength++; // i will add 1 to the length because i started from 0
    if (inputLength != n)
    {
        cerr << "E1";
        exit(0);
    }
}

// this function compares the secret number and the input number
bool compare(const char secretNumber[], const char input[], const int n, int tryCount)
{
    int exact = 0;
    int onlyMatch = 0;
    for (int i = 0; i < n; i++)
    {
        if (secretNumber[i] == input[i])
        {
            exact++;
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                if (secretNumber[i] == input[j])
                {
                    onlyMatch++;
                }
            }
        }
    }
    if (exact == n)
    {
        tryCount--;
        cout << "FOUND " << tryCount << endl;
        return true;
    }
    else
    {
        cout << exact << "  " << onlyMatch << endl;
        return false;
    }
}

// this function does the routine of the program (taking input, checking if it is valid, comparing the numbers)
void routine(char secretNumber[], const int length, int tryCount, char input[])
{
    do
    {
        cin >> input;
        tryCount++;
        isContainsValidCharacters(input, length);
        isSameSize(input, length);
        if (!isUnique(input, length) || input[0] == '0')
        {
            cerr << "E0";
            exit(0);
        }
        // if the try count is greater than 100, the program will exit and print "FAILED"
    } while (!compare(secretNumber, input, length, tryCount) && tryCount <= 100);
    if (tryCount >= 100)
    {
        cout << "FAILED" << endl;
        exit(0);
    }
}

// this is the main function and arguments are taken from the command line with argc and argv
int main(int argc, char *argv[])
{
    srand(time(0)); // Seed for random number generation
    // argc, gives the number of command line arguments. argv, is a pointer to an array of character strings that contain the arguments.
    // If the number of arguments is not 3 (argc is 3 because the first argument is the name of the program), the program will exit and print "E0"
    if (argc != 3)
    {
        cerr << "E0" << endl;

        return 1;
    }

    char secretNumber[15];
    // tryCount is declared as 1 because you wanted like this in the homework, but i am not taking input now so i will decrement it later.
    int tryCount = 1;
    char input[15];

    if (argv[1][0] == '-' && argv[1][1] == 'r' && argv[1][2] == '\0')
    {
        // if i subtracted the length by the ASCII value of 0, so i will get the integer value of the character
        int length = argv[2][0] - '0';

        if (length < 1 || length > 15)
        {
            cerr << "E0";
            return 0;
        }
        generateRandom(secretNumber, length);
        routine(secretNumber, length, tryCount, input);
    }

    else if (argv[1][0] == '-' && argv[1][1] == 'u' && argv[1][2] == '\0')
    {
        int length;                              // length of the command line argument (after the -u)
        for (int i = 0; argv[2][i] != '\0'; i++) // i will find the length of the command line argument in this loop
        {
            length = i;
        }
        length++; // i will add 1 to the length because i started from 0

        for (int i = 0; i < length; i++) // i will copy the command line argument to the secretNumber array so i can use it easily
        {
            secretNumber[i] = argv[2][i];
        }

        if (!isUnique(secretNumber, length) || secretNumber[0] == '0') // i will check if the command line argument has unique elements, first element of the array cannot be 0
        {
            cerr << "E0";
            return 0;
        }
        isContainsValidCharacters(secretNumber, length);
        routine(secretNumber, length, tryCount, input);
    }
    else
    {
        cerr << "E0";
    }

    return 0;
}