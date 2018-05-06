#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include "lcg.h"
using namespace std;

int N, Ntot;
double x, y, res, a, b, c=1.0;

double unirand(){return (double)randu()/(double)MAX_RAND;}
double fx(double x){ return sqrt(1.-pow(x,4));}
void input();

int main(){
    cout << "=== Definite Integral for f(x) = sqrt(1-x^4)\n"; 
    cout << "=== using MonteCarlo method\n";    
    input();
    while (a < -1. || a > 1. || b < -1. || b > 1. || b < a || a == b){
        cout << "Error input boundary for this function\n";
        input();}
    
    // montecarlo
    rseed(time(NULL));
    ofstream out("f1-out.txt");
    for (int i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        y = c*unirand();
        if (y<=fx(x)){ N++;}
        out << x << " " << y << endl;}
    out.close();
    res = (double)N/(double)Ntot * c * (b-a);
    printf("Hasil integrasi = %f\n", res);

    return 0;
}

void input(){   
    cout << "Enter the boundary (-1<=x<=1):\n";
    cout << "Lower (a) = "; cin >> a;
    cout << "Upper (b) = "; cin >> b;
    cout << "N_total   = "; cin >> Ntot;
}
