#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include "lcg.h"
using namespace std;

int N=0, Ntot=0;
double x, y, res, a, b, c=0.0;

double unirand(){return (double)randu()/(double)MAX_RAND;}
double fx(double x){ return sin(sqrt(x));}
void input();
void plot();

int main(){
    cout << "=== Definite Integral for f(x) = sin(sqrt(x))\n"; 
    cout << "=== using MonteCarlo method\n";    
    input();
    while (a < 0. || b < 0. || b < a || a == b || Ntot < 2){
        cout << "Error input boundary for this function\n";
        input();}
    
    // mencari maksimum dengan bilangan random
    for (int i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        if (fabs(fx(x)) > c) {c = fabs(fx(x));}}
    c = c + 0.1; // agar lebih menjamin c >= maksimum fungsi

    // montecarlo
    rseed(time(NULL));
    ofstream out("f2-out.txt");
    for (int i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        if (fx(x) >= 0.){
            y = c*unirand();
            if (y <= fx(x)){ N++; }}
        else {
            y = -c*unirand();
            if (y >= fx(x)){ N--; }}
        out << x << " " << y << "\n";
    }
    out.close();
    
    res = ((double)N / (double)Ntot) * c * (b-a);
    printf("Hasil integrasi = %f\n", res);

    plot();
    return 0;
}

void input(){   
    cout << "Enter the boundary (x>=0):\n";
    cout << "Lower (a) = "; cin >> a;
    cout << "Upper (b) = "; cin >> b;
    cout << "N_total   = "; cin >> Ntot;
}

void plot(){
    ofstream ploter("plot.in");
    ploter << "#gnuplot input file\n";
    ploter << "set xlabel \"x\"\n";
    ploter << "set ylabel \"f(x)\"\n";
    ploter << "plot \"f2-out.txt\" w d title \"data\", sin(sqrt(x)) w l\n";
    ploter.close();
    
    system("gnuplot -persist < plot.in");
}
