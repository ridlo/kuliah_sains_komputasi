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

double Cd=0.1, rho=1.225, A=1.;
double g=9.8;
double k=200.;
double yi=80., yo=50.; // panjang tali 30 meter
double m=70.;

double totalF(double t, double v, double y);
double fd(double t, double v);
double fs(double t, double y);
void plot();

int main(){
    int N = 10000, i, j;
    double ti=0.0, tf=15.;
    double vi=0.0, h;
    
    h = (tf-ti)/(double) N;
    
    double y, v, t;
    y = yi;
    v = vi;
    t = ti;
    double ky1, kv1, ky2, kv2, ky3, kv3, ky4, kv4;

    ofstream outfile;
    outfile.open("bungee.txt");
        outfile << t << " " << v << " " << y << endl;
    // Runge-Kutta 
    for (i=1;i<=N;i++){ 
        ky1 = h*v;
        kv1 = h*totalF(t, v, y)/m;        
        ky2 = h*(v+kv1/2.);
        kv2 = h*totalF(t+h/2., v+kv1/2., y+ky1/2.)/m;
        ky3 = h*(v+kv2/2.);
        kv3 = h*totalF(t+h/2., v+kv2/2., y+ky2/2.)/m;
        ky4 = h*(v+kv3);
        kv4 = h*totalF(t+h, v+kv3, y+ky3);
        
        y = y + (ky1 + 2.*(ky2+ky3) + ky4)/6.;
        v = v + (kv1 + 2.*(kv2+kv3) + kv4)/6.;
        t = t + h;
        outfile << t << " " << v << " " << y << endl;
    } 
    outfile.close();
    
    plot();

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

void plot(){
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
}
