// Copyleft (c) 2012. Ridlo W. Wibowo
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<fstream>
#define _USE_MATH_DEFINES
using namespace std;


double unirand(){return (double) rand()/(double) RAND_MAX;}

int main(){
    double l = 0.1, phi, theta;
    double x, y, z;
    int n=10000;

    srand(time(NULL));
    ofstream out("bola.txt");
    for (int i=0;i<n;i++){
        phi = 2.*M_PI*unirand();
        theta = acos(1. - 2.*unirand());
        //theta = M_PI*unirand();

        x = l*sin(theta)*cos(phi);
        y = l*sin(theta)*sin(phi);
        z = l*cos(theta);
        
        out << x << " " << y << " " << z << " " << endl;
    }
    out.close();
    
    return 0;
}
