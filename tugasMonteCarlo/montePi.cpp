#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

double unirand()
{
    return (double) rand()/ (double) RAND_MAX;
}

int main()
{
    double pi, x, y, r;
    unsigned int N=0, Ntot;
    
    ofstream outfile;
    outfile.open("rnd-pi.txt");
    
    Ntot = 100000;
    srand(time(NULL));

    for (int i=0; i<Ntot; i++){
        x = unirand();
        y = unirand();
        outfile << x << " " << y << "\n";
        r = x*x + y*y;
        if ( r <= 1. ) {
            N++;}
    }
    outfile.close();
        
    pi = (double)N/(double)Ntot * 4.;
    printf("Hasil dari %d percobaan menghasilkan nilai PI = %f \n", Ntot, pi);
    
    ofstream ploter;
    ploter.open("pi-plot.in");
    ploter << "# gnuplot command for plotting\n";
    ploter << "set terminal wxt size 600, 500\n";
    ploter << "set xrange [0:1]\n";
    ploter << "set xlabel \"x\"\n";
    ploter << "set ylabel \"y\"\n";
    ploter << "plot \"rnd-pi.txt\" with dots, sqrt(1.-x*x)\n";
    ploter.close();
    
    system("gnuplot -persist < pi-plot.in");
    return 0;
}
