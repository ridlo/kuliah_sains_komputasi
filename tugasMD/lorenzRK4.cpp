/******************************************************/
/* Lorenz System using RK4                            */
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

    double kx1, kx2, kx3, kx4, ky1, ky2, ky3, ky4, kz1, kz2, kz3, kz4;
    // Runge-Kutta method
    ofstream outfile;
    outfile.open("lorenzRK4-out.txt");
    outfile << t << " " << x << " " << y << " " << z << endl;
    double ksx, ksy, ksz;
    for (int i=1;i<=N;i++){
            kx1 = h*fdx(x, y); 
            ky1 = h*fdy(x, y, z);
            kz1 = h*fdz(x, y, z);
            
            ksx = x+kx1/2.; ksy = y+ky1/2.; ksz = z+kz1/2.;
            kx2 = h*fdx(ksx, ksy);
            ky2 = h*fdy(ksx, ksy, ksz);
            kz2 = h*fdz(ksx, ksy, ksz); 
            
            ksx = x+kx2/2.; ksy = y+ky2/2.; ksz = z+kz2/2.; 
            kx3 = h*fdx(ksx, ksy);
            ky3 = h*fdy(ksx, ksy, ksz);
            kz3 = h*fdz(ksx, ksy, ksz);
            
            ksx = x+kx3; ksy = y+ky3; ksz = z+kz3;
            kx4 = h*fdx(ksx, ksy);
            ky4 = h*fdy(ksx, ksy, ksz);
            kz4 = h*fdz(ksx, ksy, ksz);
        
        x = x + (kx1 + 2.*(kx2+kx3) + kx4)/6.;
        y = y + (ky1 + 2.*(ky2+ky3) + ky4)/6.;
        z = z + (kz1 + 2.*(kz2+kz3) + kz4)/6.;
        t = t + h;
        outfile << t << " " << x << " " << y << " " << z << endl;
    } 
    outfile.close(); 
    
    // plot hasil
    ofstream ploter;
    ploter.open("plot_lorenzRK4.in");
    ploter << "# gnuplot input file\n";
    ploter << "set term wxt 0\n";
    ploter << "plot \"lorenzRK4-out.txt\" u 1:2 w d, \"lorenzRK4-out.txt\" u 1:3 w d, \"lorenzRK4-out.txt\" u 1:4 w d\n";
    ploter << "set term wxt 1\n";
    ploter << "set xlabel \"x\"\n";
    ploter << "set ylabel \"y\"\n";
    ploter << "set zlabel \"z\"\n";
    ploter << "set xrange [-20:25]\n";
    ploter << "set yrange [-30:30]\n";
    ploter << "set zrange [-20:60]\n";
    ploter << "splot \"lorenzRK4-out.txt\" u 2:3:4 w d lc 3\n";
    ploter.close();
    
    // jalankan gnuplot
    system("gnuplot -persist < plot_lorenzRK4.in");

    return 0;
}

