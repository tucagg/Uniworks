// SparseMatrix.cpp

#include "SparseMatrix.h"
#include <iostream>
#include <fstream>

// default constructor
SparseMatrix::SparseMatrix()
{
    maxindex = 0;
}

// constructor with size
SparseMatrix::SparseMatrix(int n)
{
    maxindex = n;
}

// constructor with file name
SparseMatrix::SparseMatrix(std::string filename)
{
    read(filename);
}

// function to set the value of a non-zero element
void SparseMatrix::set(int row, int col, double d, int maxindex)
{
    if (row > maxindex)
    {
        maxindex = row;
    }
    if (col > maxindex)
    {
        maxindex = col;
    }
    if (matrixVector.size() == 0)
    {
        matrix temp;
        temp.row = row;
        // set maxindex to rowData
        temp.rowData.set(col, d, maxindex);
        matrixVector.push_back(temp);
    }
    else
    {
        for (int i = 0; i < matrixVector.size(); i++)
        {
            if (matrixVector[i].row == row)
            {
                matrixVector[i].rowData.set(col, d, maxindex);
                return;
            }
        }
        matrix temp;
        temp.row = row;
        temp.rowData.set(col, d, maxindex);
        matrixVector.push_back(temp);
    }
}

// function to get the value of a non-zero element
double SparseMatrix::get(int row, int col)
{
    for (int i = 0; i < matrixVector.size(); i++)
    {
        if (matrixVector[i].row == row)
        {
            return matrixVector[i].rowData.get(col);
        }
    }
    return 0;
}

// function to get the maximum index
int SparseMatrix::getMaxIndex()
{
    return maxindex;
}

// function to read from file
void SparseMatrix::read(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            matrix temp;
            std::string tempString = "";
            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] == ' ')
                {
                    temp.row = std::stoi(tempString);
                    tempString = "";
                }
                else if (line[i] == ':')
                {
                    int index = std::stoi(tempString);
                    tempString = "";
                    i++;
                    while (line[i] != ' ' && i < line.size())
                    {
                        tempString += line[i];
                        i++;
                    }
                    double value = std::stod(tempString);
                    tempString = "";
                    temp.rowData.set(index, value, maxindex);
                }
                else
                {
                    tempString += line[i];
                }
            }
            matrixVector.push_back(temp);
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

// function to write to file
void SparseMatrix::write(std::string filename)
{
    std::ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        for (int i = 0; i < matrixVector.size(); i++)
        {
            file << matrixVector[i].row << " ";
            std::vector<data> temp = matrixVector[i].rowData.getNonZeroElements();
            for (int j = 0; j < temp.size(); j++)
            {
                file << temp[j].index << ":" << temp[j].value << " ";
            }
            file << std::endl;
        }
        file.close();
    }
}

// function to get the transpose of the matrix
SparseMatrix SparseMatrix::transpose()
{
    SparseMatrix temp;
    temp.maxindex = maxindex;
    for (int i = 0; i < matrixVector.size(); i++)
    {
        std::vector<data> tempData = matrixVector[i].rowData.getNonZeroElements();
        for (int j = 0; j < tempData.size(); j++)
        {
            // if it is non-zero
            if (tempData[j].value != 0)
            {
                temp.set(tempData[j].index, matrixVector[i].row, tempData[j].value, maxindex);
            }
        }
    }
    // before returning the transpose, sort the matrixVector
    std::sort(temp.matrixVector.begin(), temp.matrixVector.end(), [](const matrix &a, const matrix &b) -> bool
              { return a.row < b.row; });
    return temp;
}

SparseMatrix SparseMatrix::operator+(SparseMatrix &m)
{
    SparseMatrix temp;
    if (maxindex > m.maxindex)
    {
        temp.maxindex = maxindex;
    }
    else
    {
        temp.maxindex = m.maxindex;
    }
    for (int i = 0; i < matrixVector.size(); i++)
    {
        temp.matrixVector.push_back(matrixVector[i]);
    }
    for (int i = 0; i < m.matrixVector.size(); i++)
    {
        bool found = false;
        for (int j = 0; j < temp.matrixVector.size(); j++)
        {
            if (temp.matrixVector[j].row == m.matrixVector[i].row)
            {
                found = true;
                std::vector<data> tempData = m.matrixVector[i].rowData.getNonZeroElements();
                for (int k = 0; k < tempData.size(); k++)
                {
                    double value = temp.matrixVector[j].rowData.get(tempData[k].index) + tempData[k].value;
                    if (value != 0)
                    {
                        temp.matrixVector[j].rowData.set(tempData[k].index, value, temp.maxindex);
                    }
                    else
                    {
                        temp.matrixVector[j].rowData.remove(tempData[k].index);
                    }
                }
            }
        }
        if (!found)
        {
            temp.matrixVector.push_back(m.matrixVector[i]);
        }
    }
    // sort the matrixVector
    std::sort(temp.matrixVector.begin(), temp.matrixVector.end(), [](const matrix &a, const matrix &b) -> bool
              { return a.row < b.row; });

    temp.removeZeroRows(); // Remove zero rows before returning the result
    return temp;
}

SparseMatrix SparseMatrix::operator-(SparseMatrix &m)
{
    SparseMatrix temp;
    temp = -m + *this;
    // sort the matrixVector
    std::sort(temp.matrixVector.begin(), temp.matrixVector.end(), [](const matrix &a, const matrix &b) -> bool
              { return a.row < b.row; });
    return temp;
}

// Operator overloading for unary minus of a sparse matrix
SparseMatrix SparseMatrix::operator-()
{
    SparseMatrix temp;
    temp.maxindex = maxindex;
    for (int i = 0; i < matrixVector.size(); i++)
    {
        temp.matrixVector.push_back(matrixVector[i]);
        std::vector<data> tempData = matrixVector[i].rowData.getNonZeroElements();
        for (int j = 0; j < tempData.size(); j++)
        {
            temp.matrixVector[i].rowData.set(tempData[j].index, -tempData[j].value, temp.maxindex);
        }
    }
    return temp;
}

// Operator overloading for <<
std::ostream &operator<<(std::ostream &os, const SparseMatrix &m)
{
    for (int i = 0; i < m.matrixVector.size(); i++)
    {
        os << m.matrixVector[i].row << " ";
        std::vector<data> temp = m.matrixVector[i].rowData.getNonZeroElements();
        for (int j = 0; j < temp.size(); j++)
        {
            os << temp[j].index << ":" << temp[j].value << " ";
        }
        os << std::endl;
    }
    return os;
}

void SparseMatrix::removeZeroRows()
{
    for (int i = 0; i < matrixVector.size();)
    {
        std::vector<data> temp = matrixVector[i].rowData.getNonZeroElements();
        if (temp.empty())
        {
            matrixVector.erase(matrixVector.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

// Operator overloading for multiplication of two sparse matrices
SparseMatrix SparseMatrix::operator*(SparseMatrix &m)
{
    SparseMatrix temp;
    if (maxindex > m.maxindex)
    {
        temp.maxindex = maxindex;
    }
    else
    {
        temp.maxindex = m.maxindex;
    }
    SparseMatrix mTranspose = m.transpose();
    for (int i = 0; i < matrixVector.size(); i++)
    {
        for (int j = 0; j < mTranspose.matrixVector.size(); j++)
        {
            double value = dot(matrixVector[i].rowData, mTranspose.matrixVector[j].rowData);
            if (value != 0)
            {
                temp.set(matrixVector[i].row, mTranspose.matrixVector[j].row, value, temp.maxindex);
            }
        }
    }
    return temp;
}