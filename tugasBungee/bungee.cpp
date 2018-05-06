/**********************************************************************/
/* bungee.cpp / trampoline                                            */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                 */        /**********************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
using namespace std;

double Cd=0.1, rho=1.225, A=1.;
double g=9.8;
double k=200.;
double yi=80., yo=50.; // panjang tali 30 meter
double m=70.;

double totalF(double t, double v, double y);
double fd(double t, double v);
double fs(double t, double y);

int main(){
    int N = 10000, i, j;
    double ti=0.0, tf=15.;
    double vi=0.0, h;
    
    h = (tf-ti)/(double) N;
    
    double y[N], v[N], t[N];
    y[0] = yi;
    v[0] = vi;
    t[0] = ti;

    // Runge-Kutta 
    for (i=1;i<=N;i++){
        double ky1, kv1, ky2, kv2, ky3, kv3, ky4, kv4;
        ky1 = h*v[i-1];
        kv1 = h*totalF(t[i-1], v[i-1], y[i-1])/m;        
        ky2 = h*(v[i-1] + kv1/2.);
        kv2 = h*totalF(t[i-1] + h/2., v[i-1] + kv1/2., y[i-1] + ky1/2.)/m;
        ky3 = h*(v[i-1] + kv2/2.);
        kv3 = h*totalF(t[i-1] + h/2., v[i-1] + kv2/2., y[i-1] + ky2/2.)/m;
        ky4 = h*(v[i-1] + kv3);
        kv4 = h*totalF(t[i-1] + h, v[i-1] + kv3, y[i-1] + ky3);
        
        y[i] = y[i-1] + (ky1 + 2.*(ky2+ky3) + ky4)/6.;
        v[i] = v[i-1] + (kv1 + 2.*(kv2+kv3) + kv4)/6.;
        t[i] = t[i-1] + h;
    }
    
    ofstream outfile;
    outfile.open("bungee.txt");
    for (j=0;j<=N;j++){
        outfile << t[j] << " " << v[j] << " " << y[j] << "\n";}
    outfile.close();

    ofstream ploter;
    ploter.open("plot_bungee.in");
    ploter << "# gnuplot input file\n";
    ploter << "set terminal wxt size 1200, 500\n";
    ploter << "set multiplot layout 1,2\n";
    ploter << "set xlabel \"t\"\n";
    ploter << "set ylabel \"y(t)\"\n";
    ploter << "plot \"bungee.txt\" using 1:3 with lines\n";
    ploter << "set ylabel \"v(t)\"\n";
    ploter << "plot \"bungee.txt\" using 1:2 with lines\n";
    ploter << "unset multiplot\n";
    ploter.close();
    
    system("gnuplot -persist < plot_bungee.in");

    return 0;
}

double totalF(double t, double v, double y){
    double w;
    w = m*g;
    return fs(t,y) + fd(t,v) - w;
}

double fd(double t, double v){
    double konst, gesek;
    konst = 0.5*Cd*rho*A;
    gesek = konst*v*v;
    if (v < 0.){return gesek;}
    else{ return -1.*gesek;}
}

double fs(double t, double y){
    double Dy;
    Dy = y-yo;
    if (Dy > 0.){return 0;}
    else{ return -k*Dy;}
}
