#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int insan(int insanskor) {
    cout << "Human's turn. Current score: " << insanskor << endl;
    int turnTotal = 0;
    char choice;
    
    do {
        int dice = rand() % 6 + 1;
        if (dice == 1) {
            cout << "You rolled a 1. Turn ends." << endl;
            return 0;
        }
        else {
            cout << "You rolled a " << dice << ". Roll again (r) or hold (h)? ";
            cin >> choice;
            if (choice == 'r') {
                turnTotal += dice;
            }
        }
    } while (choice == 'r');
    
    return turnTotal;
}

int pc(int pcskor) {
    cout << "Computer's turn. Current score: " << pcskor << endl;
    int turnTotal = 0;
    
    while (turnTotal < 20) {
        int dice = rand() % 6 + 1;
        if (dice == 1) {
            cout << "Computer rolled a 1. Turn ends." << endl;
            return 0;
        }
        else {
            cout << "Computer rolled a " << dice << "." << endl;
            turnTotal += dice;
        }
    }
    
    cout << "Computer holds." << endl;
    return turnTotal;
}


int main() {
    srand(time(0)); // Seed for random number generation
    
    int insanskor = 0;
    int pcskor = 0;
    
    while (insanskor < 100 && pcskor < 100) {
        // Human's turn
        insanskor += insan(insanskor);
        if (insanskor >= 100) {
            cout << "Human wins!" << endl;
            break;
        }
        
        // Computer's turn
        pcskor += pc(pcskor);
        if (pcskor >= 100) {
            cout << "Computer wins!" << endl;
            break;
        }
    }
    
    return 0;
}

