#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "FieldBase.h"

template <class T>
class Field : public FieldBase
{
private:
    T value;
    std::vector<T> values;

public:
    Field(const T &val) : value(val)
    {
        isMultiValue = false; //isMultiValue is false because it is not an array field
    }
    Field(const std::vector<T> &vals) : values(vals)
    {
        isMultiValue = true; //isMultiValue is true because it is an array field
    }

    std::string toString() const
    {
        int i = 0;
        std::ostringstream oss;
        if (isMultiValue)
        {
            for (size_t i = 0; i < values.size(); i++)
            {
                oss << values[i];
                if (i != values.size() - 1)
                {
                    oss << ":";
                }
            }
        }
        else
        {
            oss << value;
        }
        return oss.str();
    }
    
    void setValue(const T &val)
    {
        value = val; //set value
    }
    const T &getValue() const
    {
        return value; //return value
    }
    void setValues(const std::vector<T> &vals)
    {
        values = vals; //set values vector
    }
    const std::vector<T> &getValues() const
    {
        return values; //return values vector
    } 

    bool isArrayField() const 
    {
        return isMultiValue; //return isMultiValue value so that we can understand if it is an array field or not
    }
    
    ~Field() {}
};

#endif // FIELD_H