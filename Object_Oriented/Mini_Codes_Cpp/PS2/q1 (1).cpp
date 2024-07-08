#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to simulate a single duel
int simulateDuel() {
    // Initialize shooters
    bool aaronAlive = true, bobAlive = true, charlieAlive = true;

    while (true) {
        // Aaron shoots
        if (aaronAlive) {
            // Aaron hits with probability 1/3
            if (rand() % 3 == 0) {
                bobAlive = false;
            }
        }

        // Bob shoots
        if (bobAlive) {
            // Bob hits with probability 1/2
            if (rand() % 2 == 0) {
                charlieAlive = false;
            }
        }

        // Charlie shoots
        if (charlieAlive) {
            // Charlie never misses
            aaronAlive = false;
        }

        // Check if only one shooter is alive
        int aliveCount = aaronAlive + bobAlive + charlieAlive;
        if (aliveCount == 1) {
            if (aaronAlive) return 1;
            if (bobAlive) return 2;
            if (charlieAlive) return 3;
        }
    }
}

int main() {
    int aaronWins = 0, bobWins = 0, charlieWins = 0;
    int numDuels = 10000;

    // Seed the random number generator once
    srand(time(0));

    // Simulate duels
    for (int i = 0; i < numDuels; ++i) {
        int winner = simulateDuel();
        if (winner == 1) {
            aaronWins++;
        } else if (winner == 2) {
            bobWins++;
        } else {
            charlieWins++;
        }
    }

    // Calculate and print probabilities
    cout << "Aaron won " << aaronWins << "/" << numDuels << " duels or "
         << (static_cast<double>(aaronWins) / numDuels) * 100 << "%" << endl;
    cout << "Bob won " << bobWins << "/" << numDuels << " duels or "
         << (static_cast<double>(bobWins) / numDuels) * 100 << "%" << endl;
    cout << "Charlie won " << charlieWins << "/" << numDuels << " duels or "
         << (static_cast<double>(charlieWins) / numDuels) * 100 << "%" << endl;

    return 0;
}
