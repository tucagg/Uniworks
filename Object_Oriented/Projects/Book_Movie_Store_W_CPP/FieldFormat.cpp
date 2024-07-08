#include "FieldFormat.h"

//constructor
FieldFormat::FieldFormat(const std::string &name, const std::string &type, bool isArray, bool isFirst) : name(name), type(type), isArray(isArray) , isFirst(isFirst) {}

const std::string &FieldFormat::getName() const // it returns name 
{
    return name; 
}

const std::string &FieldFormat::getType() const // it returns type
{
    return type;
}

bool FieldFormat::isArrayField() const // it returns isArray
{
    return isArray;
}