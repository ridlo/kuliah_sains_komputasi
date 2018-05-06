#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#define _USE_MATH_DEFINES
using namespace std;

double fx(double t, double x){ return exp(-t)*sin(x);}

int main(){
    double xi = 0.0, xf=M_PI, x; // L=1.0 -> rentang x
    double ti = 0.0, tf=0.5, t; // time
    int nt = 10; // jumlah pemenggalan di t
    int nx = 10; // jumlah pemenggalan di x

    double k = (tf-ti)/nt;
    double h = (xf-xi)/nx;
    
    x = xi;
    t = ti;
    ofstream out("eksak-out.txt");
    for(int i=0;i<=nt;i++){
        for (int j=0;j<nx;j++){
            out << x+j*h << " " << fx(t+i*k, x+j*h) << "\n";}
        out << xf << " " << 0.0 << "\n";
        out << "\n\n";}
    out.close();

    return 0;
}
