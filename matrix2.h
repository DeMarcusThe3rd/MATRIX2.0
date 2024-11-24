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
    double get(int m, int n);
    void save(string filename);
    void load(string filename);
    void transpose();
    void eye();


};

