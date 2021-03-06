/****************************************************/
/* Jacobi method                                    */
/* Copyleft (c) 2012. Ridlo W. Wibowo               */
/****************************************************/
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int main()
{    
    int i, j, k=0, Nmax=25;
    int n=3;
    /*double A['n']['n']={{4., -1., 0., -1., 0., 0.},
                        {-1., 4., -1., 0., -1., 0.},
                        {0., -1., 4., 0., 0., -1.},
                        {-1., 0., 0., 4., -1., 0.},
                        {0., -1., 0., -1., 4., -1.},
                        {0., 0., -1., 0., -1., 4.}};
    double b['n']={0., 5., 0., 6., -2., 6.};
    double xi['n']={0., 0., 0., 0., 0., 0.};*/
    double A['n']['n']={{2., -1., 1.},
                        {2., 2., 2.},
                        {-1., -1., 2}};
    double b['n']={-1., 4., -5.};
    double xi['n']={0., 0., 0.};
    double ep=0.00001;
    double xf['n'], eps, sum, vnorm_f['n'], norm_i, norm_f;

    cout << "### Program Jacobi untuk menyelesaikan SPL Ax=b ###\n";
    
    cout << "Matriks A : \n";
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){ 
           cout << A[i][j] << "\t";}
        cout << "\n";}
    cout << "Vektor b : \n";
    for (i=0;i<n;i++){
        cout << b[i] << "\t";}
    cout << endl;
    cout << "Tebakan awal x(k=0): \n";
    for (i=0;i<n;i++){
        cout << xi[i] << " ";}
    cout << endl; 
    cout << "epsilon : " << ep << endl;

    // Jacobi method 
    cout << "Nilai barisan solusi x(k) dan epsilon : \n";
    do {
        for (i=0;i<n;i++){
            sum = 0.;
            for (j=0;j<n;j++){
                if (j != i){
                sum = sum - A[i][j]*xi[j];}}
            xf[i] =  (b[i] + sum)/A[i][i];}
        
        // menghitung epsilon dari Infinity Norm
        for (i=0;i<n;i++){
            vnorm_f[i] = xf[i] - xi[i];}
        norm_f = fabs(vnorm_f[0]);
        norm_i = fabs(xf[0]);
        for (i=1;i<n;i++)
        {
            if (fabs(vnorm_f[i]) > norm_f){norm_f = fabs(vnorm_f[i]);}
            if (fabs(xf[i]) > norm_i){norm_i = fabs(xf[i]);}
        }
        eps = norm_f/norm_i;
        k ++;
        
        // cout << k << "\t";
        for (i=0;i<n;i++){
            xi[i] = xf[i]; // tukar x(k) dengan x(k+1)
            printf("%7.4f ", xf[i]);}
        cout << "\t" << eps;
        cout << endl;

    } while (eps > ep && k < Nmax);
    cout << "Jumlah iterasi : " << k << endl;
    return 0;
}
