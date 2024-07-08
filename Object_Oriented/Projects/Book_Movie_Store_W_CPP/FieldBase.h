#ifndef FIELDBASE_H
#define FIELDBASE_H

#include <string>
class FieldBase { //FieldBase class it is an abstract class
public:
    bool isMultiValue =false; //isMultiValue is false by default
    virtual std::string toString() const = 0; //pure virtual function
    virtual ~FieldBase() {} //virtual destructor
};

#endif // FIELDBASE_H