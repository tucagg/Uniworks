//This program defines a class for tracking hot dog sales.

//It tracks the stand's ID number, hot dogs sold at each stand, and hot dogs sold at all stands.

#include <iostream>
#include <cstdlib>

using namespace std;

class HotDogStand{
    public:
            HotDogStand();
            HotDogStand(int newID, int newNnumSold);
            int GetID();
            void SetID(int newID);
            void JustSold();
            int GetNumSold();
            static int GetTotalSold();

    private:
        static int totalSold;
        int numSold;
        int ID;
};

int HotDogStand::totalSold =0;

//ENTER YOUR CODE HERE

HotDogStand::HotDogStand(){
    ID = 0;
    numSold = 0;
}

HotDogStand::HotDogStand(int newID, int newNumSold){
    ID = newID;
    numSold = newNumSold;
    totalSold += numSold;
}

int HotDogStand::GetID(){
    return ID;
}

void HotDogStand::SetID(int newID){
    ID = newID;
}

void HotDogStand::JustSold(){
    numSold++;
    totalSold++;
}

int HotDogStand::GetNumSold(){
    return numSold;
}

int HotDogStand::GetTotalSold(){
    return totalSold;
}

int main(){
    HotDogStand stand1(1, 0);
    HotDogStand stand2(2, 0);
    HotDogStand stand3(3, 0);

    stand1.JustSold();
    stand2.JustSold();
    stand3.JustSold();
    stand3.JustSold();
    stand3.JustSold();

    cout << "Stand 1 sold " << stand1.GetNumSold() << " hot dogs." << endl;
    cout << "Stand 2 sold " << stand2.GetNumSold() << " hot dogs." << endl;
    cout << "Stand 3 sold " << stand3.GetNumSold() << " hot dogs." << endl;
    cout << "The total number of hot dogs sold is " << HotDogStand::GetTotalSold() << endl;

    return 0;
}

