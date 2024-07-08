#ifndef FIELDFORMAT_H
#define FIELDFORMAT_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

class FieldFormat {
private:
    std::string name;
    std::string type;
    bool isArray;
    bool isFirst;
public:
    FieldFormat(const std::string& name, const std::string& type, bool isArray, bool isFirst); //constructor
    const std::string& getName() const; //getter
    const std::string& getType() const; //getter
    bool isArrayField() const; //getter
};

#endif // FIELDFORMAT_H