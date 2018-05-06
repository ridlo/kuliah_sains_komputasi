#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#define c 299792458.
using namespace std;

void plot(double Rrad);
double unirand(){return (double) rand()/(double) RAND_MAX;}

int main(){
    cout << "          Random Walk Simulation of \n";
    cout << "Radiation (photon) in Radiative Zone of the Sun\n";
    
    clock_t tstart, tend;
    double cpu_time_used;
    tstart = clock();
    double r, theta, phi, x, y, z, dx, dy, dz, Rrad, P, l, f, rho, dt, t, prand;
    double me = 9.11e-31; // kg
    double mp = 1.67e-27; // kg
    double sigmaT = 6.65245854533e-29; // m^2
    unsigned int n=0;
    double rcol;
    x = 0.0; y = 0.0; z = 0.0, t=0.0, dt=0.0;
    Rrad = 0.05; // m
    
    // constant density
    cout << "Constant Density Model\n";
    rho = 15000.;
    f = (me+mp)/(sqrt(2.)*sigmaT*rho);
    cout << "radius                = " << Rrad << endl;
    cout << "mean free path        = " << f << endl;

    srand(time(NULL));
    ofstream out("position-photon.txt");
    out << x << " " << y << " " << z << endl;
    do{ 
            phi = 2.*M_PI*unirand(); theta = acos(1.-2.*unirand());
            rcol = -f*log(unirand());
            dt = rcol/c;
            t = t+dt;
            dx = rcol*sin(theta)*cos(phi); 
            dy = rcol*sin(theta)*sin(phi); 
            dz = rcol*cos(theta);
            x=x+dx; 
            y=y+dy; 
            z=z+dz;
            out << x << " " << y << " " << z << endl;
            n = n+1;
            r = sqrt(x*x + y*y + z*z);
    } while (r <= Rrad);
    out.close();
    
    cout << "escape time for r = " << r << " is " << t << endl;
    cout << "number of step    = " << n << endl;
    double tm = t/(Rrad/c);
    cout << "t_mode,scale      = " << tm << endl;
    tend = clock();
    cpu_time_used = ((double)(tend - tstart))/CLOCKS_PER_SEC;
    cout << "Computation time = " << cpu_time_used << endl;
    plot(Rrad);
    return 0;
}

void plot(double Rrad){
    ofstream ploter("plot_photon.in");
    ploter << "# gnuplot input file\n";
    ploter << "set term wxt size 800,600\n";
    ploter << "set parametric\n";
    ploter << "set angle degree\n";
    ploter << "set urange [0:360]\n";
    ploter << "set vrange [-90:90]\n";
    ploter << "set isosample 12,11\n";
    ploter << "set ticslevel 0\n";
    ploter << "set size 0.7,1.0\n";
    ploter << "set nokey\n";
    ploter << "a="<<Rrad<<"\n";
    ploter << "fx(u,v)=cos(u)*cos(v)\n";
    ploter << "fy(u,v)=sin(u)*cos(v)\n";
    ploter << "fz(v)=sin(v)\n";
    ploter << "splot a*fx(u,v),a*fy(u,v),a*fz(v), \"position-photon.txt\" w l lc 3\n";
    ploter.close();

    system("gnuplot -persist < plot_photon.in");
}
