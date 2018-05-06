#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#define c 299792458.
using namespace std;

double unirand(){return (double) rand()/(double) RAND_MAX;}

void randomwalk(double Rrad){
    double r, theta, phi, x, y, z, dx, dy, dz, f, rho, dt, t, rcol;
    double me = 9.11e-31; // kg
    double mp = 1.67e-27; // kg
    double sigmaT = 6.65245854533e-29; // m^2
    unsigned int n=0;
    x = 0.0; y = 0.0; z = 0.0, t=0.0, dt=0.0; 
    rho = 15000.; // Constant Density
    f = (me+mp)/(sqrt(2.)*sigmaT*rho);
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
            n = n+1;
            r = sqrt(x*x + y*y + z*z);
    } while (r <= Rrad);
    
    double tm = t/(Rrad/c);
    cout << tm << " " << n << endl;
}

int main(){
    clock_t t;
    t = clock();
    int N = 1000;
    double Rrad = 0.5;
    srand(time(NULL));
    for (int i=0;i<N;i++){
        randomwalk(Rrad);
    }
    t = clock() - t;
    cout << "waktu run program = " << t << " clicks  = " << (double)t/(double)CLOCKS_PER_SEC << " detik " << endl;
    return 0;
}
