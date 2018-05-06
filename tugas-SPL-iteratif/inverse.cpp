#include <iostream>
#define n 3
using namespace std;

/*double A[n][n]={{4., -1., 0., -1., 0., 0.},
                {-1., 4., -1., 0., -1., 0.},
                {0., -1., 4., 0., 0., -1.},
                {0., 0., -1., 0., -1., 4.},
                {-1., 0., 0., 4., -1., 0.},
                {0., -1., 0., -1., 4., -1.}};
double b[n]={0., 5., 0., 6., 6., -2.};
*/
double C[n][n] = {{3, 2, 105},
                  {2, -3, 103},
                  {1, 1, 3}};
void print_matrix(double *matrix, int rows, int cols){
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            cout << matrix[i*cols + j] << " ";}
        cout << "\n";}
}

int main(){
    
    // scaling & pivoting
    for (int j=0;j<n;j++)
        for (int i=j;i<n,i++){
            for 

    return 0;
}
