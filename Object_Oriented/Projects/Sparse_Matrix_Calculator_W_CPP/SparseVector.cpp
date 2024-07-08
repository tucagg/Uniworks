// SparseVector.cpp

#include "SparseVector.h"
#include <iostream>
#include <fstream>

// default constructor
SparseVector::SparseVector()
{
    maxindex = 0;
}

// constructor with size
SparseVector::SparseVector(int n)
{
    maxindex = n;
}

// constructor with file name
SparseVector::SparseVector(std::string filename)
{
    read(filename);
}

// function to set the value of a non-zero element
void SparseVector::set(int index, double d, int maxindex)
{
    if (index > maxindex)
    {
        maxindex = index;
    }
    if (alldata.size() == 0)
    {
        data temp;
        temp.index = index;
        temp.value = d;
        alldata.push_back(temp);
    }
    else
    {
        for (int i = 0; i < alldata.size(); i++)
        {
            if (alldata[i].index == index)
            {
                alldata[i].value = d;
                return;
            }
        }
        data temp;
        temp.index = index;
        temp.value = d;
        alldata.push_back(temp);
    }
}

// function to get the value of a non-zero element
double SparseVector::get(int index)
{
    for (int i = 0; i < alldata.size(); i++)
    {
        if (alldata[i].index == index)
        {
            return alldata[i].value;
        }
    }
    return 0;
}

// function to get the size of the vector
int SparseVector::size()
{
    return maxindex;
}

// function to add two vectors
SparseVector SparseVector::operator+(SparseVector &v)
{
    SparseVector temp;
    if (maxindex > v.maxindex)
    {
        temp.maxindex = maxindex;
    }
    else
    {
        temp.maxindex = v.maxindex;
    }
    for (int i = 0; i < alldata.size(); i++)
    {
        temp.set(alldata[i].index, alldata[i].value, temp.maxindex);
    }
    for (int i = 0; i < v.alldata.size(); i++)
    {
        temp.set(v.alldata[i].index, temp.get(v.alldata[i].index) + v.alldata[i].value, temp.maxindex);
    }
    // if the value is zero then we don't need to store it
    for (int i = 0; i < temp.alldata.size(); i++)
    {
        if (temp.alldata[i].value == 0)
        {
            temp.alldata.erase(temp.alldata.begin() + i);
            i--;
        }
    }
    // before returning the result we need to sort the vector
    std::sort(temp.alldata.begin(), temp.alldata.end(), [](const data &a, const data &b)
              { return a.index < b.index; });
    return temp;
}

// function to subtract two vectors
SparseVector SparseVector::operator-(SparseVector &v)
{
    SparseVector temp;
    temp = -v + *this;
    // sort the vector
    std::sort(temp.alldata.begin(), temp.alldata.end(), [](const data &a, const data &b)
              { return a.index < b.index; });
    return temp;
}

// function to get the unary minus of a vector
SparseVector SparseVector::operator-()
{
    SparseVector temp;
    temp.maxindex = maxindex;
    for (int i = 0; i < alldata.size(); i++)
    {
        temp.set(alldata[i].index, -alldata[i].value, temp.maxindex);
    }
    return temp;
}

// function to get the dot product of two vectors
double SparseVector::operator*(SparseVector &v)
{
    double sum = 0;
    if (maxindex > v.maxindex)
    {
        for (int i = 0; i < v.alldata.size(); i++)
        {
            sum += get(v.alldata[i].index) * v.alldata[i].value;
        }
    }
    else
    {
        for (int i = 0; i < alldata.size(); i++)
        {
            sum += v.get(alldata[i].index) * alldata[i].value;
        }
    }
    return sum;
}
// function to get the text representation of a vector
std::ostream &operator<<(std::ostream &os, const SparseVector &v)
{
    for (int i = 0; i < v.alldata.size(); i++)
    {
        if (v.alldata[i].value != 0)
        {
            os << v.alldata[i].index << ":" << v.alldata[i].value << " ";
        }
    }
    return os;
}
// function to read a vector from a file
void SparseVector::read(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        data temp;
        while (file >> temp.index)
        {
            file.ignore(1, ':');
            file >> temp.value;
            alldata.push_back(temp);
            if (temp.index > maxindex)
            {
                maxindex = temp.index;
            }
        }
        file.close();
    }
    else
    {
        // create an file
        std::ofstream file;
        file.open(filename);
        file.close();
    }
}
// function to write a vector to a file
void SparseVector::write(std::string filename)
{
    std::ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        for (int i = 0; i < alldata.size(); i++)
        {
            if (alldata[i].value != 0)
            {
                file << alldata[i].index << ":" << alldata[i].value << " ";
            }
        }
        file.close();
    }
}
// function to get the maximum index
int SparseVector::getMaxIndex()
{
    return maxindex;
}
// function to get the non-zero elements, including the index and the value
std::vector<data> SparseVector::getNonZeroElements() const
{
    return alldata;
}
// Operator overloading for addition of two sparse vectors
SparseVector operator+(const SparseVector &v1, const SparseVector &v2)
{
    SparseVector result;
    int max_index = std::max(v1.maxindex, v2.maxindex);
    result.maxindex = max_index;

    for (const auto &data : v1.alldata)
    {
        result.set(data.index, data.value, max_index);
    }

    for (const auto &data : v2.alldata)
    {
        result.set(data.index, result.get(data.index) + data.value, max_index);
    }
    // if the value is zero then we don't need to store it
    for (int i = 0; i < result.alldata.size(); i++)
    {
        if (result.alldata[i].value == 0)
        {
            result.alldata.erase(result.alldata.begin() + i);
            i--;
        }
    }
    return result;
}

// function to get the dot product of two vectors
double dot(const SparseVector &v1, const SparseVector &v2)
{
    SparseVector result;
    int max_index = std::max(v1.maxindex, v2.maxindex);
    result.maxindex = max_index;

    for (int i = 0; i < v1.alldata.size(); i++)
    {
        for (int j = 0; j < v2.alldata.size(); j++)
        {
            if (v1.alldata[i].index == v2.alldata[j].index)
            {
                // if the value is zero then we don't need to store it
                result.set(v1.alldata[i].index, v1.alldata[i].value * v2.alldata[j].value, max_index);
            }
        }
    }
    // lets get the sum of the result
    double sum = 0;
    for (int i = 0; i < result.alldata.size(); i++)
    {
        sum += result.alldata[i].value;
    }
    return sum;
}
// function to remove a non-zero element
void SparseVector::remove(int index)
{
    for (int i = 0; i < alldata.size(); i++)
    {
        if (alldata[i].index == index)
        {
            alldata.erase(alldata.begin() + i);
            i--;
        }
    }
}