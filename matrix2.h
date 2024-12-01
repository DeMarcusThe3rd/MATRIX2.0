#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
private:
    int rows; //Number of rows
    int cols; //Number of columns
    string line;
    vector<vector<double>> x; // 2D vector to store matrix elements

public:
    Matrix(int rows, int cols, int val);//constructor prototype
    void print();    //prints matrix aesthitically 
    void set();  //sets each element based on matrix size (user input)
    void set(int M,int N,double val);   //sets specific elements
    double get(int m, int n);  //returns the specific elements
    void save(string filename);  //saves matrix written to a txt file 
    void load(string filename);  //loads matrix from txt file 
    void transpose();  //tranposes current matrix 
    void eye();  //sets matrix to identity matrix 
    void zero();  //zeroes out the matrix 
    void add(Matrix B); //adds current matrix with the another matrix 
    void sub(Matrix B);  //subtracts current matrix with another matrix 
    void lMult(Matrix B);  //left multiplies current matrix with another  (A x B)
    void rMult(Matrix B);  //right multiplies current matrix with another (B x A)
    void sMult(double s);  //scalar multiplication 
    double det();   //finds the determinant of a matrix 
    void inv();  //inverses the matrix 
    void gaus();  //executes gaussian elimination (REF and RREF )
    void swapRows(int row1, int row2);   //swaps two rows 
};

