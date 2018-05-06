#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define _USE_MATH_DEFINES
#define c 299792458.
using namespace std;

unsigned int n=0;
int myrank, nprocs;

void plot(double Rrad);
double unirand(){return (double) rand()/(double) RAND_MAX;}

double randomwalker(){
    //cout << "          Random Walk Simulation of \n";
    //cout << "Radiation (photon) in Radiative Zone of the Sun\n";
    
    double r, theta, phi, x, y, z, dx, dy, dz, Rrad, P, l, f, rho, dt, t, prand;
    double Rsun = 500000000.;
    double me = 9.11e-31; // kg
    double mp = 1.67e-27; // kg
    double sigmaT = 6.65245854533e-29; // m^2
    double coll; // Tracking (m)
    unsigned int n=0;
    x = 0.0; y = 0.0; z = 0.0, t=0.0;
    Rrad = 5; // m
    
    // constant density
    //cout << "Constant Density Model\n";
    //rho = 15000.;
    //f = (me+mp)/(sqrt(2.)*sigmaT*rho);
    //cout<<f<<endl;
    //dt = f/(c);
    //l = c*dt;
    //P = 1. - exp(-l/f);
    /*cout << "radius                = " << Rrad << endl;
    cout << "mean free path        = " << f << endl;
    cout << "time step             = " << dt << endl;
    cout << "step size             = " << l << endl;
    cout << "static prob collision = " << P << endl;
    */
    
    phi = 2.*M_PI*unirand(); theta = acos(1.-2.*unirand());
    l=0;
    do{
		rho = (-1*(3*10*10*10*10)*(5*r/Rrad))+(1.5*10*10*10*10*10);
		f = (me+mp)/(sqrt(2.)*sigmaT*rho);
        coll = -1*f*log(unirand());
        l = l + coll;
            phi = 2.*M_PI*unirand(); 
            theta = acos(1.-2.*unirand());
            dx = coll*sin(theta)*cos(phi); 
            dy = coll*sin(theta)*sin(phi); 
            dz = coll*cos(theta);
            x=x+dx; 
            y=y+dy; 
            z=z+dz;
            dt = coll/c;
            
        t += dt;
        n = n+1;
        r = sqrt(x*x + y*y + z*z);
        //cout<<rho<<endl;
        //cout<<n<<" "<<t<<endl;
    } while (r <= Rrad);
    //cout << "escape time for r = " << r << " is " << t << endl;
    //cout << "number of step    = " << n << endl;
    double tm = t/(Rrad/c);
    //cout << "t_mode,scale      = " << tm << endl;
    //cout << n << " " << t << endl;
    //usleep(1001000); // biar seed random berubah dulu kalau misal ternyata gak sampai sedetik program dah selesai, lalu perlu di run lagi
    //plot(Rrad);
    return t;
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

int main(int argc, char** argv){
	clock_t t;
	t = clock();
//  Initialize MPI.
//
  MPI::Init ( argc, argv );
//
//  Get the number of processors.
//
  nprocs = MPI::COMM_WORLD.Get_size ( );
//
//  Get the rank of this processor.
//
  myrank = MPI::COMM_WORLD.Get_rank ( );
    
    if (myrank==0)
    {
		
		ofstream out0;
		out0.open("Randomwalk-linear-0.txt");
		srand(4);
		for (int i=0; i<250; i++)
		{
			out0<<randomwalker()<<endl;
		}
		out0.close();
	}
	if (myrank==1)
    {
		
		ofstream out1;
		out1.open("Randomwalk-linear-1.txt");
		srand(1);
		for (int i=0; i<250; i++)
		{
			out1<<randomwalker()<<endl;
		}
		out1.close();
	}
	
	if (myrank==2)
    {
		
		ofstream out2;
		out2.open("Randomwalk-linear-2.txt");
		srand(2);
		for (int i=0; i<250; i++)
		{
			out2<<randomwalker()<<endl;
		}
		out2.close();
	}
	
	if (myrank==3)
    {
		
		ofstream out3;
		out3.open("Randomwalk-linear-3.txt");
		srand(3);
		for (int i=0; i<250; i++)
		{
			out3<<randomwalker()<<endl;
		}
		out3.close();
	}
	
	t = clock() -t;
	cout<<(float)t/CLOCKS_PER_SEC<<endl;
	
	MPI_Finalize();
	return 0;
}
