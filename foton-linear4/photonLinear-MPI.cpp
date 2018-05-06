#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <string>
#include <mpi.h>
#define _USE_MATH_DEFINES
#define c 299792458.
using namespace std;

double unirand(){return (double) rand()/(double) RAND_MAX;}

double randomwalk(double Rrad){
    double r, theta, phi, x, y, z, dx, dy, dz, f, rho, dt, t, rcol, randcol;
    double me = 9.11e-31; // kg
    double mp = 1.67e-27; // kg
    double sigmaT = 6.65245854533e-29; // m^2
    unsigned int n=0;
    x = 0.0; y = 0.0; z = 0.0, t=0.0, dt=0.0, r=0.0; 
    do{ 
            rho = -3e4*5.*r/Rrad + 1.5e5; // linier gradient density
            f = (me+mp)/(sqrt(2.)*sigmaT*rho);
            phi = 2.*M_PI*unirand(); theta = acos(1.-2.*unirand());
            do {
                randcol = unirand();
            } while (randcol == 0.0 || randcol == 1.0); // menghindari -inf
            rcol = -f*log(randcol);
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
    return tm;
}

int main(int argc, char** argv){
    time_t tstart=time(0), tend, tim;
    int m = 4;
    int N = 250;
    double R[7]={0.05, 0.1, 0.2, 0.5, 1.0, 2.0, 5.0};

        int rank, nprocs;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for (int k=0;k<7;k++){
        double Rrad=R[k];
        for (int j=0;j<m;j++){
            if (rank == j){
                clock_t begin, end;
                time_t start, finish;
                if (Rrad < 1.0){ begin = clock();}
                else { start = time(0);}
                char filename[64];
                srand(time(NULL)+7+j);
	        sprintf(filename, "outfile-lin-MPI-%d-%d.txt", k, j);
                ofstream out(filename);
                for (int i=0;i<N;i++){
                    out << randomwalk(Rrad) << endl;
                }
                if (R[k] < 1.0){ 
                    end = clock();
                    out << "running time = " << (double)(end - begin)/(double)CLOCKS_PER_SEC << " seconds." << endl;
                }
                else {
                    finish = time(0);
                    out << "running time = " << (double)(finish - start) << " seconds." << endl;
                }
                out.close();
            }
        }
    }
        MPI_Finalize();
    tend = time(0);
    tim = tend - tstart;
    cout << "running time = " << tim/60. << " minutes." << endl;
    return 0;
}
