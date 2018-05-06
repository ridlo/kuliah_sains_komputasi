#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

double f(double x, double y){
    return -y;}

int main(){
    // jumlah grid
    int N = 1000, i, j;

    // ya = temperatur kiri
    // yb = temperatur kanan
    // yc = temperatur ambient atau lingkungan
    // za dan zb adalah tebakan awal nilai turunan pertama
    double ya=0.0, yb=100.0, za=7.5, zb=12.5;

    // x dan dx
    double a=0.0, b=100.0, h;
    h = (b-a)/(double) N;

    // alokasi array
    double x[N], y[N], z[N];
    
    //inisiasi
    x[0] = 0.0;
    y[0] = 0.0;
    z[0] = 1.0;

    for (i=1;i<=N;i++){
        double ky1, kz1, ky2, kz2, ky3, kz3, ky4, kz4;
        ky1 = h*z[i-1];
        kz1 = h*f(x[i-1], y[i-1]);        
        ky2 = h*(z[i-1] + kz1/2.);
        kz2 = h*f(x[i-1] + h/2., y[i-1] + ky1/2.);
        ky3 = h*(z[i-1] + kz2/2.);
        kz3 = h*f(x[i-1] + h/2., y[i-1] + ky2/2.);
        ky4 = h*(z[i-1] + kz3);
        kz4 = h*f(x[i-1] + h, y[i-1] + ky3);
        
        y[i] = y[i-1] + (ky1 + 2.*(ky2+ky3) + ky4)/6.;
        z[i] = z[i-1] + (kz1 + 2.*(kz2+kz3) + kz4)/6.;
        x[i] = x[i-1] + h;}

    for (j=0;j<=N;j++){
        printf("%f %f %f\n", x[j], y[j], z[j]);}

    return 0;}
