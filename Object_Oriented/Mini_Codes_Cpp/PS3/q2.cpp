#include <iostream>
#include <vector>
using namespace std;

int main() {
    //Variable declarations
    int i;
    int current;
    int numSuitors;

    cout << "Enter the number of suitors: ";
    cin >> numSuitors;

    vector<int> suitors(numSuitors);

    for (int i = 0; i < numSuitors; i++) {
        suitors[i] = i + 1; 
    }

    if(numSuitors <=0)
    {
        cout<< "Not enough suitors"<<endl;
    }
    else if (numSuitors == 1)
    {
        cout<< "You would stand first in line."<<endl;
    }
    else
    {
        current = 0;
        while(suitors.size() > 1)
        {
            //Count three people ahead or go two people down
            //since we include the current person in the count

            for(i = 0; i < 2; i++)
            {
                current++;
                if(current == suitors.size())
                {
                    current = 0;
                }
            }
            //Eleminate contestant current
            suitors.erase(suitors.begin() + current);
            if(current == suitors.size())
            {
                current = 0;
            }
        }
        cout<< "To win the princess, you should stand in position "<<suitors[0]<<endl;
    }
}