/******************************************************/
/* Lorenz System using Verlet algorithm               */
/* copyleft (c) 2012. Ridlo W. Wibowo                 */
/******************************************************/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
using namespace std;

double sigma=10.;
double rho=28.;
double beta=8./3.;

double fdx(double x, double y){return sigma*(y-x);}
double fdy(double x, double y, double z){return x*(rho-z) - y;}
double fdz(double x, double y, double z){return x*y - beta*z;}

int main(){
    int N=10000;
    double x, y, z, t, tf, h;
    // Inisiasi
    x=3.;
    y=5.;
    z=1.;
    t=0.;
    tf=50.;
    
    h = (tf-t)/(double) N; // time step
    ofstream out;
    out.open("lorenzVer-out.txt");
    out << t << " " << x << " " << y << " " << z << endl;
    for (int i=1;i<=N;i++){
        x = x + fdx(x,y)*h - 0.5*sigma*h*h; // plus turunan keduanya
        y = y + fdy(x,y,z)*h - 0.5*h*h;
        z = z + fdz(x,y,z)*h - 0.5*beta*h*h;
        t = t+h;
        out << t << " " << x << " " << y << " " << z << endl;
    }
    out.close();

    // plot hasil
    ofstream ploter;
    ploter.open("plot_lorenzVer.in");
    ploter << "# gnuplot input file\n";
    ploter << "set term wxt 0\n";
    ploter << "plot \"lorenzVer-out.txt\" u 1:2 w d, \"lorenzVer-out.txt\" u 1:3 w d, \"lorenzVer-out.txt\" u 1:4 w d\n";
    ploter << "set term wxt 1\n";
    ploter << "set xlabel \"x\"\n";
    ploter << "set ylabel \"y\"\n";
    ploter << "set zlabel \"z\"\n";
    ploter << "set xrange [-20:25]\n";
    ploter << "set yrange [-30:30]\n";
    ploter << "set zrange [-20:60]\n";
    ploter << "splot \"lorenzVer-out.txt\" u 2:3:4 w d lc 3\n";
    ploter.close();

    // jalankan gnuplot
    system("gnuplot -persist < plot_lorenzVer.in");

    return 0;
}

