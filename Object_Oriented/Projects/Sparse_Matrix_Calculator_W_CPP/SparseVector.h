//SparseVector.h
#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <iostream>
#include <vector>

// data structure to store the index and value of a non-zero element
struct data
{
    int index;
    double value;
};

// class to store the non-zero elements of a vector
class SparseVector
{
    private:
        std::vector<data> alldata;
        int maxindex;  // the maximum index of the non-zero elements
    public:
        SparseVector();
        SparseVector(int n);
        SparseVector(std::string filename);
        void set(int index, double d, int maxindex);
        double get(int index);
        int size();
        SparseVector operator+(SparseVector &v);// this is the addition operator
        SparseVector operator-(SparseVector &v);// this is the subtraction operator
        SparseVector operator-(); // this is the unary minus operator
        double operator*(SparseVector &v);
        friend std::ostream& operator<<(std::ostream& os, const SparseVector& v); //text representation of the vector
        friend double dot(const SparseVector &v1, const SparseVector &v2); //function to get the dot product of two vectors
        void read(std::string filename);      //function to read from file
        void write(std::string filename);         //function to write to file
        int getMaxIndex();         //function to get the maximum index
        std::vector<data> getNonZeroElements() const; //function to get the non-zero elements
        friend SparseVector operator+(const SparseVector& v1, const SparseVector& v2); //function to add two vectors
        void remove(int index);//function to remove an element from the vector
};
#endif
