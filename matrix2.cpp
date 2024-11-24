#include "matrix2.h"
/*  defaulting to 3x3
Matrix::Matrix(int rows, int cols, int val) {
    if (rows <= 0 || cols <= 0) {
        cerr << "Matrix dimensions must be positive." << endl;
        // Default to 3x3 if invalid
        rows = 3;
        cols = 3;
    }
    this->rows = rows;
    this->cols = cols;
    x.resize(rows, vector<double>(cols, val));
}
*/

Matrix::Matrix(int rows, int cols, int val){  //constructor definition
    while (rows <= 0 ||cols <= 0) {
            cerr << "Matrix dimensions must be positive." << endl;
            cout << "Enter Row: ";
            cin >> rows;
            cout << "Enter Column: ";
            cin >> cols;
    }

    this->rows = rows;
    this->cols = cols;
    x.resize(rows, vector<double>(cols, val));
}

void Matrix::print(){
    for(int m=0;m<rows;m++){
        for(int n=0;n<cols;n++){
            cout << "[" << setw(7) << fixed << setprecision(3) << x[m][n] << " ]" << "  ";
        }   
        cout << endl;
    }
    cout << endl;
}

void Matrix::set(){
    if(!(rows<=0 || cols<=0)){
        cout << "Enter elements for " << rows << "x" << cols << " Matrix:" << endl;
        for (int m=0;m<rows;m++){  //nested for loop to iterate through indexes mn [row][column] of the array 
            for(int n=0;n<cols;n++){
                cout <<"Element [" << m+1 << "][" << n+1 << "]: ";
                cin >> x[m][n]; 
            }
        }
    }
    cerr << "Invalid matrix dimensions." <<endl;
}

void Matrix::set(int m,int n,double val){
    if ((m>=0 && m<rows)&&(cols>=0 && n<cols)){  //checks if within bounds
        x[m][n] = val; //set the element at the specific matrix index 
    }
    else{
        cerr << "Index out of bounds!" << endl;
    }
    cout << endl;
}

double Matrix::get(int m, int n){  //get element at the specified index 
    if ((m>=0 && m<rows) &&(n>=0 && n<cols)){ //condition for the input index to be within bounds (0 to 2)
        cout << "Element at (" << m+1 << "," << n+1 << ") is: "; 
        cout << fixed << setprecision(3) << x[m][n] << endl;  //displays the element retrieved 
        return x[m][n];  //returns the element as a double for calculation purposes
    }
    else{
        cerr << "Index out of bounds!" << endl;  //prints error message 
        return 0;
    } 
}

void Matrix::save(string filename){
    ofstream savef(filename);  //declare "savef" as output stream to a file 

    if(savef.is_open()){  //condition to check if file is opened successfully
        cout << "File successfully opened." << endl;
        cout << "Writing to "<< filename << "." << endl; 
        for (int m=0;m<rows;m++){   //nested for loop to iterate through indexes mn [row][column] of the array 
                for (int n=0;n<cols;n++){  
                    savef << x[m][n] << " ";  //saves element read into output file stream with formatting 
                }
                savef << endl;  //new line after every 3 elements 
            }
        }

    else{
        cerr << "Error writing to " << filename << "." <<  endl;   //error message displayed if file not found 
        cout << "Closing File..." << endl;   //error message displayed if file not found 
    }
    savef.close();  //closes file stream regardless
}

void Matrix::load(string filename){
    rows=0;
    int space=0;
    ifstream loadf(filename);  //declare "loadf" as an input file stream to a file 
    
    if(loadf.is_open()){  //condition to check if file is opened successfully 
        cout << "File successfully opened." << endl;
        cout << "Reading from "<< filename << "." << endl; 

        while(getline(loadf,line)){
            rows++;  //increments for every row read
            for(char c : line){
                if (c == ' '){
                    space++;
                }
            }
        }
        cols = (space + rows)/rows;
        loadf.clear();
        loadf.seekg(0);
        x.resize(rows, vector<double>(cols, 0.0));
        for (int m=0;m<rows;m++) {  //nested for loop to iterate through indexes mn [row][column] of the array 
            for (int n=0;n<cols;n++) {
                loadf >> x[m][n];  //loads elements saved into the matrix
            }
        }
    }

    else{
        cout << "Error reading " << filename << "." <<  endl;   //error message displayed if file not found 
        cout << "Closing File..." << endl;   //error message displayed if file not found 
    }
    loadf.close();  //closes file stream regardless 
}

void Matrix::transpose(){  //tranposes the current matrix (swaps row with column and vice versa)
    Matrix temp(cols,rows,0.0);
    for (int m=0; m<rows; m++) {
        for (int n=0; n<cols; n++) {
            temp.x[n][m] = x[m][n]; 
        }
    }
    x = temp.x; 
    swap(rows, cols); 
}

void Matrix::eye(){
    if(rows != cols){
        cerr << "Matrix is not squared, unable to set identity." << endl;
    }

    for (int m=0;m<rows;m++){  //nested for loop to iterate through indexes mn [row][column] of the array 
        for(int n=0;n<cols;n++){
            if (m==n){      //condition to check if row index is equal to column index (check if on diagonal)
                x[m][n] = 1.0; //set to 1
            }
            else{
                x[m][n] = 0.0;  //set to 0 
            }
        }
    }    
}