#include "Entry.h"

Entry::~Entry()
{
    for (auto field : fields)
    {
        delete field;
    }
}

void Entry::addField(FieldBase *field)
{
    fields.push_back(field); //add field to entry
}

std::string Entry::getFieldAsString(size_t index) const
{
    std::ostringstream oss;
    oss << fields[index]->toString(); //return field as string
    return oss.str();
}

size_t Entry::getFieldCount() const
{
    return fields.size(); //return fields.size()
}

Entry::Entry(const Entry& other) { //copy constructor
    //it checks isArrayField or not and creates new field
    for (auto field : other.fields) {
        FieldBase* newField = nullptr;
        if (dynamic_cast<Field<std::string>*>(field)) {
            if(dynamic_cast<Field<std::string>*>(field)->isArrayField())
            {
                newField = new Field<std::string>(dynamic_cast<Field<std::string>*>(field)->getValues());
            }
            else
            {
                newField = new Field<std::string>(dynamic_cast<Field<std::string>*>(field)->getValue());
            }
        } else if (dynamic_cast<Field<int>*>(field)) {
            if(dynamic_cast<Field<int>*>(field)->isArrayField())
            {
                newField = new Field<int>(dynamic_cast<Field<int>*>(field)->getValues());
            }
            else
            {
                newField = new Field<int>(dynamic_cast<Field<int>*>(field)->getValue());
            }
        } else if (dynamic_cast<Field<double>*>(field)) {
            if(dynamic_cast<Field<double>*>(field)->isArrayField())
            {
                newField = new Field<double>(dynamic_cast<Field<double>*>(field)->getValues());
            }
            else
            {
                newField = new Field<double>(dynamic_cast<Field<double>*>(field)->getValue());
            }
        } else if (dynamic_cast<Field<float>*>(field)) {
            if(dynamic_cast<Field<float>*>(field)->isArrayField())
            {
                newField = new Field<float>(dynamic_cast<Field<float>*>(field)->getValues());
            }
            else
            {
                newField = new Field<float>(dynamic_cast<Field<float>*>(field)->getValue());
            }
        } else if (dynamic_cast<Field<char>*>(field)) {
            if(dynamic_cast<Field<char>*>(field)->isArrayField())
            {
                newField = new Field<char>(dynamic_cast<Field<char>*>(field)->getValues());
            }
            else
            {
                newField = new Field<char>(dynamic_cast<Field<char>*>(field)->getValue());
            }
        }
        fields.push_back(newField);
    }
}

Entry& Entry::operator=(const Entry& other) {
    if (this == &other) { // check if this is equal to other
        return *this; // return this
    }
    // Clean up existing fields
    for (auto field : fields) {
        delete field;
    }
    fields.clear();
    // Use the copy constructor
    Entry temp(other);
    std::swap(fields, temp.fields); // Swap the fields with the temporary object
    return *this;
}


bool Entry::operator==(const Entry &other) const //compare operator
{
    if (fields.size() != other.fields.size())
    {
        return false;
    }
    for (size_t i = 0; i < fields.size(); ++i)
    {
        if (fields[i]->toString() != other.fields[i]->toString())
        {
            return false;
        }
    }
    return true;
}

std::string Entry::toString() const { //return fields as string
    std::ostringstream oss;
    for (size_t i = 0; i < fields.size(); ++i) {
        oss << fields[i]->toString();
        if (i < fields.size() - 1) {
            oss << "|";
        }
    }
    return oss.str();
}

std::__1::ostream &operator<<(std::__1::ostream &os, const Entry &entry) { //output operator
    os << entry.toString();
    return os;
} 