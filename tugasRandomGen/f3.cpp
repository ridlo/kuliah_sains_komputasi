#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include "lcg.h"
using namespace std;

int N, Ntot;
double x, y, res, a, b, c;

double unirand(){return (double)randu()/(double)MAX_RAND;}
double fx(double x){ return exp(x*x);}
void input();

int main(){
    cout << "=== Definite Integral for f(x) = exp(x^2)\n"; 
    cout << "=== using MonteCarlo method\n";    
    input();
    while (a < -26. || a > 26. || b < -26. || b > 26. || b < a || a == b){
        cout << "Error input boundary for this function\n";
        input();}
    
    // maksimum mengambil batas, karena fungsi selalu positif
    c = fabs(fx(b));
    if (fabs(b) < fabs(a)){ c = fabs(fx(a));}

    // montecarlo
    rseed(time(NULL));
    ofstream out("f3-out.txt");
    for (int i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        y = c*unirand();
        if (y<=fx(x)){ N++;}
        out << x << " " << y << endl;}
    out.close();
    res = (double)N/(double)Ntot * c * (b-a);
    printf("Hasil integrasi = %g\n", res);

    return 0;
}

void input(){   
    cout << "Enter the boundary (-26<=x<=26):\n";
    cout << "Lower (a) = "; cin >> a;
    cout << "Upper (b) = "; cin >> b;
    cout << "N_total   = "; cin >> Ntot;
}
