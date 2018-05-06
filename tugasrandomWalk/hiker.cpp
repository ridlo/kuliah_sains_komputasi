/*********************************************/
/* hiker.cpp                                 */
/* Copyleft (c) 2012. Ridlo W. Wibowo        */
/*********************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#define _USE_MATH_DEFINES
using namespace std;

double unirand(){ return (double)rand()/(double)RAND_MAX;}

/************************************************************/
/* N-19%, NE-24%, E-17%, SE-10%, S-2%, SW-3%, W-10%, NW-15% */
/* cumulative                                               */
double randtheta(){
       double p = unirand();
       if (p < 0.19){ return 0.5*M_PI;} // N
       else if (p < 0.43){ return 0.25*M_PI;} // NE
       else if (p < 0.60){ return 0.0;} // E
       else if (p < 0.70){ return 1.75*M_PI;} // SE 
       else if (p < 0.72){ return 1.5*M_PI;} // S
       else if (p < 0.75){ return 1.25*M_PI;} // SW
       else if (p < 0.85){ return M_PI;} // W
       else{ return 0.75*M_PI;} // NW
}

void plot(double Rmax);
void animate(int n, double Rmax);

int main(){
    double step=1.0; // hiker's step is constant: 1 m
    double theta=0.0;
    double Rmax=100.;
    double x=0., y=0., dx=0., dy=0., r=0.; // initial at 0,0
    int n = 0;

    ofstream out("hiker-out.txt");
    srand(time(NULL));
    do{
        theta = randtheta();
        dx = step*cos(theta); // actually this method is not effective, because dx and dy are just some constants for this problem
        dy = step*sin(theta);
        x = x + dx; 
        y = y + dy;
        out << x << " " << y << endl;
        r = sqrt(x*x + y*y);
        n++;
    } while (r < Rmax); // stop until reach Rmax
    out.close();

    plot(Rmax);
    //animate(n, Rmax);
    return 0;
}

void plot(double Rmax){
    ofstream ploter("hiker-plot.in");
    ploter << "set term png\n";
    ploter << "set output \"hiker-plot-"<<Rmax<<".png\"\n";
    ploter << "set parametric\n";
    ploter << "set xrange ["<<-Rmax<<":"<<Rmax<<"]\n";
    ploter << "set yrange ["<<-Rmax<<":"<<Rmax<<"]\n";
    ploter << "set size square\n";
    ploter << "plot [0:2*pi] "<<Rmax<<"*sin(t),"<<Rmax<<"*cos(t) notitle, \"hiker-out.txt\" w l title \"path\"\n";
    ploter.close();

    system("gnuplot -persist < hiker-plot.in");
}

void animate(int n, double Rmax){
    ofstream anim("hiker-anim.in");
    anim << "reset\n";
    anim << "set term gif animate size 500,500\n";
    anim << "set output \"hiker-animation.gif\"\n";
    anim << "set parametric\n";
    anim << "set size square\n";
    anim << "i=0\n";
    anim << "n="<<n<<"\n";
    anim << "set xrange ["<<-Rmax<<":"<<Rmax<<"]\n";
    anim << "set yrange ["<<-Rmax<<":"<<Rmax<<"]\n";
    anim << "load \"hiker-animate\"\n";
    anim.close();

    ofstream anime("hiker-animate");
    anime << "plot [0:2*pi] "<<Rmax<<"*sin(t),"<<Rmax<<"*cos(t) notitle, \"hiker-out.txt\" every ::i::i ps 2 pt 6 title sprintf(\"step = %i\", i), \"hiker-out.txt\" every ::0::i w l ls 3 title \"W - E |  path\"\n";
    anime << "i=i+1\n";
    anime << "if (i < n) reread\n";
    anime.close();
    
    system("gnuplot < hiker-anim.in");
}
