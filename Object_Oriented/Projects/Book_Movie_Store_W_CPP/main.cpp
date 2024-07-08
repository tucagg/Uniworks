//main.cpp
#include "Catalog.h"


int main() {

    // it is for writing output to output.txt
    std::ofstream out("output.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    Catalog catalog; //create catalog object
    catalog.readData(); // read data.txt and create entries and fieldformats 
    catalog.readCommands(); // read commands.txt and execute commands
    
    return 0;
}
