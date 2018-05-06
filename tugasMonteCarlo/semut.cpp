/****************************************/
/* root finding using montecarlo method */
/* 2012 - ridlo w. wibowo               */
/****************************************/
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

double unirand()
{
    return (double) rand()/ (double) RAND_MAX;
}

double f(double x)
{
    double y = cos(x*x) + log(x) - 1.;
    return y;
}

int main(int argc, char* argv[])
{
    double res, x, y, a, b;
    int N=0, Ntot, i;
    a = 1.;
    b = 4.;
    cout << "Menghitung akar-akar persamaan dengan MonteCarlo\n" ;
    cout << "Fungsi f(x) = cos(x^2) + log(x) - 1. \n";
    cout << "dengan batas integrasi x=[1, 4]\n";
    cout << "Masukkan jumlah angka random = "; cin >> Ntot;
   
    srand(time(NULL)); // seed

    // mencari maximum fungsi dengan cara monte-carlo
    for (i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        if (fabs(f(x)) > c) {c = fabs(f(x));}
    }
    
    return 0;
}
