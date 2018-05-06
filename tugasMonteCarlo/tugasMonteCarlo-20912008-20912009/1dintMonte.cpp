/**************************************/
/* definite integral using montecarlo */
/* 2012 - ridlo w. wibowo             */
/**************************************/
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

int main()
{
    double res, x, y, a, b, c=0.;
    int N=0, Ntot, i;
    a = 1.;
    b = 4.;
    cout << "Menghitung nilai integral dengan MonteCarlo\n" ;
    cout << "Fungsi f(x) = cos(x^2) + log(x) - 1. \n";
    cout << "dengan batas integrasi x=[1, 4]\n";
    cout << "Masukkan jumlah angka random = "; cin >> Ntot;
   
    srand(time(NULL)); // seed

    // mencari maximum fungsi dengan cara monte-carlo
    for (i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        if (fabs(f(x)) > c) {c = fabs(f(x));}
    }
    
    // mencari integral fungsi dengan cara monte-carlo
    ofstream out;
    out.open("1dintMonte_data.txt");
    for (i = 0; i<Ntot; i++){
        x = a + (b-a)*unirand();
        if (f(x) > 0.){
            y = c*unirand();
            if (y <= f(x)){ N++; }
        }
        else {
            y = -c*unirand();
            if (y >= f(x)){ N--; }
        }
        out << x << " " << y << "\n";
    }
    out.close();

    res = (double)N / (double)Ntot * c*(b-a);
    printf("Hasil integrasinya = %f\n", res);
    
    ofstream ploter;
    ploter.open("1dintMonte_gnuplot.in");
    ploter << "# gnuplot input file\n";
    ploter << "set xrange ["<< a << ":" << b << "]\n";
    ploter << "set xlabel \"x\"\n";
    ploter << "set ylabel \"f(x)\"\n";
    ploter << "plot \"1dintMonte_data.txt\" with dots, cos(x**2) + log(x) - 1. lt 1 lc 3\n";
    ploter.close();

    system("gnuplot -persist < 1dintMonte_gnuplot.in");
    return 0;
}
