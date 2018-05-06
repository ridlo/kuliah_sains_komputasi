/*****************************************************************************/
/* shooting method with rk4 for heat transfer                                */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                        */
/* Absolutly no warranty implied or expressed                                */
/*****************************************************************************/
#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

double f(double x, double y){
    double u;
    double alpha = 16.0; // konstanta konduksi
    double ym = 27.0; // temperatur ruangan
    u = alpha*(y - ym);
    return u;}

int main(){
    double a, b, ya, yb, z1, z2, h, slope, tol;
    double ky1, kz1, ky2, kz2, ky3, kz3, ky4, kz4;
    int N, itmax, iter=0, i, j, m, n;
    
    a  = 0.0; // batas x kiri
    b  = 1.0; // batas x kanan
    ya = 0.0; // suhu di kiri
    yb = 100.0; // suhu di kanan
    
    z1 = 7.5; // tebakan pertama dan kedua nilai turunan fungsi di kiri
    z2 = 12.5;

    N = 101; // jumlah grid
    itmax = 101; // jumlah max iterasi shooting
    
    h = (b-a)/100.;
    
    // inisiasi array
    double x[itmax][N], y[itmax][N], z[itmax][N];
    x[0][0] = a;
    y[0][0] = ya;
    z[0][0] = z1;
    
    // iterasi shooting methods
    j = 0;
    do{
        iter += 1;
        for (i=1;i<N;i++){ // RK4
            ky1 = h*z[j][i-1];
            kz1 = h*f(x[j][i-1], y[j][i-1]);        
            ky2 = h*(z[j][i-1] + kz1/2.);
            kz2 = h*f(x[j][i-1] + h/2., y[j][i-1] + ky1/2.);
            ky3 = h*(z[j][i-1] + kz2/2.);
            kz3 = h*f(x[j][i-1] + h/2., y[j][i-1] + ky2/2.);
            ky4 = h*(z[j][i-1] + kz3);
            kz4 = h*f(x[j][i-1] + h, y[j][i-1] + ky3);
            
            y[j][i] = y[j][i-1] + (ky1 + 2.*(ky2+ky3) + ky4)/6.;
            z[j][i] = z[j][i-1] + (kz1 + 2.*(kz2+kz3) + kz4)/6.;
            x[j][i] = x[j][i-1] + h;
            }

        j += 1;
        x[j][0] = a;
        y[j][0] = ya;
        if (j == 1){
            z[j][0] = z2;}
        else{
            slope = (y[j-1][N-1] - y[j-2][N-1])/(z[j-1][0] - z[j-2][0]);
            z[j][0] = z[j-1][0] + (yb - y[j-1][N-1])/slope;}
        
        tol = y[j-1][N-1] - yb;
        } while (j < itmax && fabs(tol) > 0.1);
     
    for (n=0;n<N;n++){
        printf("%f\t", x[0][n]);
        for (m=0;m<iter;m++){
            printf("%f\t",y[m][n]);}
        cout << endl;}
    
    return 0;}
