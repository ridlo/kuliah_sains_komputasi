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

double f(double x, double y)
{
    double z = x*y + y*x*x + 1.;
    return z;
}

int main()
{
    double res, x, y, z, a, b, c, d, o=0.;
    int N=0, Ntot, i;
    a = -2.;
    b = 1.;
    c = -1.;
    d = 2.;
    cout << "Menghitung nilai integral dengan MonteCarlo\n" ;
    cout << "Fungsi f(x, y) = x^y + y*x^2 + 1  \n";
    cout << "dengan batas integrasi x=[-2, 1] y=[-1, 2]\n";
    cout << "Masukkan jumlah angka random = "; cin >> Ntot;
   
    srand(time(NULL)); // seed

    // mencari maximum fungsi dengan cara monte-carlo
    for (i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        y = c + (d-c)*unirand();
        if (fabs(f(x, y)) > o) {o = fabs(f(x, y));}
    }
    
    // mencari integral fungsi dengan cara monte-carlo
    ofstream out;
    out.open("2dintMonte_data.txt");
    for (i = 0; i<Ntot; i++){
        x = a + (b-a)*unirand();
        y = c + (d-c)*unirand();
        if (f(x, y) > 0.){
            z = o*unirand();
            if (z <= f(x, y)){ N++; }
        }
        else {
            z = -o*unirand();
            if (z >= f(x, y)){ N--; }
        }
        out << x << " " << y << " " << z << "\n";
    }
    out.close();

    res = (double)N / (double)Ntot * o*(b-a)*(d-c);
    printf("Hasil integrasinya = %f\n", res);
    //cout << o << endl ; 
    ofstream ploter;
    ploter.open("2dintMonte_gnuplot.in");
    ploter << "# gnuplot input file\n";
    ploter << "set xrange ["<< a << ":" << b << "]\n";
    ploter << "set yrange ["<< c << ":" << d << "]\n";
    ploter << "set xlabel \"x\"\n";
    ploter << "set ylabel \"y\"\n";
    ploter << "set zlabel \"f(x, y)\"\n";
    ploter << "splot \"2dintMonte_data.txt\" with dots, x*y + y*x*x  + 1. lc 3\n";
    ploter.close();

    system("gnuplot -persist < 2dintMonte_gnuplot.in");
    return 0;
}
