#include "matrix2.h"

using namespace std;

int main(){
    Matrix A(5,4,1.0);

    A.print();
    A.gaus();
    A.print();
}