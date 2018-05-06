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

void hiker();

int main(){
    int k = 1000;
    for (int j=0;j<k;j++){
        hiker();
    }
    return 0;
}

void hiker(){
    double step=1.0; // hiker's step is constant: 1 m
    double theta=0.0;
    double Rmax=100.;
    double x=0., y=0., dx=0., dy=0., r=0.; // initial at 0,0
    int n = 0;

    srand(time(NULL));
    do{
        theta = randtheta();
        dx = step*cos(theta); // actually this method is not effective, because dx and dy are just some constants for this problem
        dy = step*sin(theta);
        x = x + dx; 
        y = y + dy;
        r = sqrt(x*x + y*y);
        n++;
    } while (r < Rmax); // stop until reach Rmax
    cout << n << " " << atan(y/x) << endl;
    usleep(1001000);
}

