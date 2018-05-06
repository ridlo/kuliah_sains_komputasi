#include <iostream>
#define m 3 
#define n 3
using namespace std;

void print_matrix(double *matrix, int rows, int cols){
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            cout << matrix[i*cols + j] << " ";}
        cout << "\n";}
}

int main(){
    double B[m][n] = {{3,2,1},{3,2,4},{6,7,5}};
    print_matrix((double *)&B, m, n);

    return 0;
}
