/**********************************************************************/
/* bungee.cpp / trampoline                                            */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                 */        
/**********************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
using namespace std;

double f(double t, double y){
    return 5.*t;
}

int main(){
    int N=1000;
    double yi, dyi, ti, tf, h;
    // Inisiasi
    yi = 1.;
    dyi = 0.;
    ti = 0.;
    tf = 5.;

    h = (tf-ti)/(double) N;
    
    double y, dy, t;
    y = yi;
    dy = dyi;
    t = ti;
    double ky1, ky2, ky3, ky4;

    // Runge-Kutta method
    ofstream outfile;
    outfile.open("rk-out.txt");
    for (int i=1;i<=N;i++){
        outfile << t << " " << y << endl;
            ky1 = h*f(t, y);
            ky2 = h*f(t, y+ky1/2.);
            ky3 = h*f(t, y+ky2/2.);
            ky4 = h*f(t, y+ky3);
        y = y + (ky1 + 2.*(ky2+ky3) + ky4)/6.;
        t = t + h;
    } 
    outfile.close(); 

    ofstream ploter;
    ploter.open("plot_rk.in");
    ploter << "# gnuplot input file\n";
    ploter << "set xlabel \"t\"\n";
    ploter << "set ylabel \"y(t)\"\n";
    ploter << "plot \"rk-out.txt\" using 1:2 with lines\n";
    ploter.close();
    
    system("gnuplot -persist < plot_rk.in");

    return 0;
}

