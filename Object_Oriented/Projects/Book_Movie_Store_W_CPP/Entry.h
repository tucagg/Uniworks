#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "FieldBase.h"
#include "Field.h"

class Entry: public FieldBase{
private:
    std::vector<FieldBase*> fields; //fields vector
public:
    Entry() = default; //default constructor
    Entry(const Entry& other); //copy constructor
    Entry& operator=(const Entry& other); //copy assignment operator
    bool operator==(const Entry& other) const; //compare operator
    ~Entry(); //destructor
    void addField(FieldBase* field); //add field to entry
    std::string getFieldAsString(size_t index) const; //return field as string
    size_t getFieldCount() const; //return fields.size()
    const FieldBase* getField(size_t index) const; //return fields[index]
    std::string toString() const override; //return fields as string
    friend std::ostream& operator<<(std::ostream& os, const Entry& entry);  //output operator
};

#endif // ENTRY_H