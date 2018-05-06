#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#define _USE_MATH_DEFINES
using namespace std;

double ff(double y){ return -y;}

int main(){
    int N=10000;
    double p, dp, ddp, t, ti, tf, h;
    ti=0.;
    tf=50*M_PI;
    t = ti;
    p=0.;
    dp=1.0;
    
    h = (tf-t)/(double) N; // time step
    
    ofstream out;
    out.open("Ver-out.txt");
    out << t << " " << dp << " " << p << endl;
    for (int i=1;i<=N;i++){
        ddp = ff(p);
        p = p + dp*h + 0.5*ddp*h*h;
        dp = dp + 0.5*(ddp+ff(p))*h;
        t = t+h;
        out << t << " " << dp << " " << p << endl;
    }
    out.close();
    
    // file input gnuplot
    ofstream ploter;
    ploter.open("plot_Ver.in");
    ploter << "# gnuplot input file\n";
    ploter << "set xrange ["<< ti << ":" << tf << "]\n";
    ploter << "set xlabel \"t\"\n";
    ploter << "set ylabel \"y(t) = sin(t)\"\n";
    ploter << "plot \"Ver-out.txt\" u 1:3 w d lc 3, sin(x) w l\n";
    ploter.close();

    // jalankan gnuplot
    system("gnuplot -persist < plot_Ver.in");

    return 0;
}

