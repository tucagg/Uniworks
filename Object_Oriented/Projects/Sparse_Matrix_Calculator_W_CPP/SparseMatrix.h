// SparseMatrix.h 
#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <vector>
#include "SparseVector.h" // SparseVector.h dosyasını dahil ettik

struct matrix
{
    int row;
    SparseVector rowData; // Her satırın verilerini bu yapı içinde tutuyoruz
};

class SparseMatrix
{
private:
    std::vector<matrix> matrixVector;
    int maxindex;  // the maximum index of the non-zero elements
public:
    SparseMatrix();
    SparseMatrix(int n);
    SparseMatrix(std::string filename);
    void set(int row, int col, double d, int maxindex);
    double get(int row, int col);
    SparseMatrix transpose();
    SparseMatrix operator+(SparseMatrix &m); // this is the addition operator
    SparseMatrix operator-(SparseMatrix &m); // this is the subtraction operator
    SparseMatrix operator-(); // this is the unary minus operator
    SparseMatrix operator*(SparseMatrix &m);
    friend std::ostream& operator<<(std::ostream& os, const SparseMatrix& m); //text representation of the matrix
    void read(std::string filename); //function to read from file
    void write(std::string filename);  //function to write to file
    int getMaxIndex(); //function to get the maximum index
    void removeZeroRows();
};
#endif
