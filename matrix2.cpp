#include "matrix2.h"
Matrix::Matrix(int rows, int cols, int val){
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

void Matrix::print(){
    for(int m=0;m<rows;m++){
        for(int n=0;n<cols;n++){
            cout << "[" << setw(7) << fixed << setprecision(3) << x[m][n] << " ]" << "  ";
        }   
        cout << endl;
    }
    cout << endl;
}

void Matrix::set(){   //set each element with user input
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

void Matrix::load(string filename) {
    ifstream loadf(filename);  // Input file stream

    if (loadf.is_open()) {
        cout << "File successfully opened." << endl;
        cout << "Reading from " << filename << "." << endl;

        vector<vector<double>> temp; // Temporary storage for the matrix
        string line;

        while (getline(loadf, line)) { // Read line by line
            stringstream s(line);      // Create a stringstream for the current line
            vector<double> row;       // Temporary vector for the row
            string buffer;

            while (s >> buffer) { // Parse each value in the line
                row.push_back(stod(buffer)); // Convert string to double and add to row
            }

            if (temp.empty()) { // First row determines the number of columns
                cols = row.size();
            } else if (row.size() != cols) { // Check column consistency
                cerr << "Error: Inconsistent number of columns at row " << temp.size() + 1 << "." << endl;
                return;
            }

            temp.push_back(row); // Add the row to the matrix
        }

        // Assign the temporary matrix to the class variable
        x = temp;
        rows = temp.size(); // Set the number of rows

    } else {
        cerr << "Error: Unable to open file " << filename << "." << endl;
    }

    loadf.close(); // Close the file stream
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

void Matrix::zero(){   //set current matrix to all zero
    for (int m=0;m<rows;m++){  //nested for loop to iterate through indexes mn [row][column] of the array 
        for(int n=0;n<cols;n++){
            x[m][n] = 0.0;  //set to 0 
        }
    }
}

void Matrix::add(Matrix B){  //adds current matrix with another matrix 
    if(B.rows != rows || B.cols != cols){
        cerr << "Addition failed." << endl << "Incompatible matrix dimensions." << endl;
    }
    else{
        for (int m=0;m<rows;m++){ //nested for loop to iterate through indexes mn [row][column] of the array 
            for (int n=0;n<cols;n++){
                x[m][n]+= B.x[m][n];  //sumation of current element with element of the other matrix 
            }
        }
    }
}

void Matrix::sub(Matrix B){  //adds current matrix with another matrix 
    if(B.rows != rows || B.cols != cols){
        cerr << "Subtraction failed." << endl << "Incompatible matrix dimensions." << endl;
    }
    else{
        for (int m=0;m<rows;m++){ //nested for loop to iterate through indexes mn [row][column] of the array 
            for (int n=0;n<cols;n++){
                x[m][n]-= B.x[m][n];  //sumation of current element with element of the other matrix 
            }
        }
    }
}

void Matrix::lMult(Matrix B){  //if current Matrix(A), C = B x A 

    if(B.cols != rows){
        cerr << "Left multiplication failed." << endl << "Incompatible matrix dimensions." << endl;
    }
    else{
        Matrix temp(B.rows,cols,0.0);  //temporary matrix to store results of the operation

        for (int m=0;m<B.rows;m++){ //nested for loop to iterate through indexes mn [row][column] of the array 
            for (int n=0;n<cols;n++){
                for(int i=0;i<B.cols;i++){  //for loop to interate through row of one matrix and column of one matrix simultaneously 
                    temp.x[m][n] += (B.x[m][i])*(x[i][n]);
                }
            }
        }
        
        *this = temp;
    }
}

void Matrix::rMult(Matrix B){  //if current Matrix(A), C = A x B
    if(B.rows != cols){
        cerr << "Right multiplication failed." << endl << "Incompatible matrix dimensions." << endl;
    }
    else{
        Matrix temp(rows,B.cols,0.0);  //temporary matrix to store results of the operation

        for (int m=0;m<rows;m++){ //nested for loop to iterate through indexes mn [row][column] of the array 
            for (int n=0;n<B.cols;n++){
                for(int i=0;i<cols;i++){  //for loop to interate through row of one matrix and column of one matrix simultaneously 
                    temp.x[m][n] += (x[m][i])*(B.x[i][n]);
                }
            }
        }

        *this = temp;
    }
}

void Matrix::sMult(double s){  //multiplies current vector by a scalar "s"
    for (int m=0;m<rows;m++){   //nested for loop to iterate through indexes mn [row][column] of the array 
        for (int n=0;n<cols;n++){
            x[m][n] *= s;   
    }    
        }
}

double Matrix::det(){  //calculates and returns the determinant of current matrix
    double determinant;

    if(rows != cols){
        cerr << "Determinant not found." << endl << "Incompatible matrix dimensions." << endl;
        return 0;
    }

    if (rows == 2) {
        determinant = (x[0][0]*x[1][1]) - (x[0][1]*x[1][0]);   //ad - bc
        cout << "Determinant is: " << determinant << endl;  //displays the determinant 
        return determinant;   //returns the determinant
    }

    if (rows == 3){
        double diagonal = 0.0;  //diagonal of the matrix 
        double anti_diagonal = 0.0; //antidiagonal of the matrix 

        for(int n=0;n<3;n++){  //iterates and sums through the diagonal of the matrix 
            diagonal += x[0][n] * x[1][(n+1)%3] * x[2][(n+2)%3]; //utilizing modulo to return to safe index beyond 2 
        }

        for(int n=2;n>=0;n--){  //iterate and sums through the anti-diagonal of the matrix 
            anti_diagonal += x[0][n] * x[1][(n+2)%3] * x[2][(n+1)%3]; //utilizing modulo to return to safe index beyond 2 
        }

        determinant = diagonal - anti_diagonal;  //subtraction to obtain the determinant 
        cout << "Determinant is: " << determinant << endl;  //displays the determinant 
        return determinant;   //returns the determinant
    }
    cerr << "Determinant not found: Unsupported matrix size (only 2x2 and 3x3 supported)." << endl;
    return 0; 
}

void Matrix::inv(){  //calculates the inverse of the current matrix 
    if (rows != cols) {
        cerr << "Inverse not found: Matrix must be square." << endl;
        return;
    }
    
    double determinant = det();  //declare determinant
    
    if (determinant == 0) {
        cout << "This matrix is singular and has no inverse." << endl;
        return;
    } 

    if (rows == 2) {
        Matrix core(2, 2, 0.0); 
        core.x[0][0] = x[1][1];  // d
        core.x[0][1] = -x[0][1]; // -b
        core.x[1][0] = -x[1][0]; // -c
        core.x[1][1] = x[0][0];  // a

        // Scale by 1/determinant
        for (int m=0;m<2;m++){
            for (int n=0; n<2;n++) {
                x[m][n]=(1/determinant) * core.x[m][n];
            }
        }
    } 

    else if(rows == 3){  
        Matrix core(rows,cols,0.0); //matrix to store the cofactors of the current matrix 
        for (int m=0;m<3;m++) {   //nested for loop to iterate through indexes mn [row][column] of the array 
            for (int n=0;n<3;n++) {
                core.x[m][n] = ((x[(m+1)%3][(n+1)%3]) * (x[(m+2)%3][(n+2)%3])) - 
                ((x[(m+1)%3][(n+2)%3]) * (x[(m+2)%3][(n+1)%3])); //utilizing modulo to return to safe index beyond 2 
            }
        }
        core.transpose();  //tranpose the core factors 

        for(int m=0;m<3;m++){  //nested for loop to iterate through indexes mn [row][column] of the array 
            for(int n=0;n<3;n++){
                x[m][n] = (1/determinant)*(core.x[m][n]); 
            }
        }
    }
    else{
        cout << "This Matrix is singular and has no inverse." <<endl;  //message to notify non-inverse matrix
    }
}


void Matrix::gaus(){   //executes gaussian elimination 
    double pivot;
    double factor;

    for(int k=0;k<rows;k++){  //iterates for each diagonal
        if(x[k][k]==0){  //if pivot is 0 swap with row below

            for(int i=k+1;i<rows;i++){  
                if (x[i][k] != 0) {
                    swapRows(k, i); //swap the current row with row i
                    break;
                }
            }
        }

        pivot=x[k][k];  //pivot is non-zero, divide by itself and whole row to make leading 1

        for(int i=0;i<cols;i++){  
            x[k][i]/=pivot;
        }

        for(int i=k+1;i<rows;i++){  //eliminate the elements below the pivots 
            factor=x[i][k]; //exp. x is a factor

            for(int j=0;j<cols;j++){
                x[i][j]-= factor*x[k][j];  //exp. R2 = R2 - xR1 (equation)
            }
        }
    }

    for (int k=rows-1;k>=0;k--){    //reverses the previous provess (invert triangle)
        for (int i =k-1;i>=0;i--){ 
            double factor = x[i][k];

            for (int j=0;j<cols;j++){
                    x[i][j] -= factor * x[k][j];  //exp. R2 = R2 - xR1 (equation)
            }
        }
    }
}

void Matrix::swapRows(int row1, int row2){ //swaps two rows
    for (int i=0;i<cols;i++) {
        swap(x[row1][i], x[row2][i]);
    }
}