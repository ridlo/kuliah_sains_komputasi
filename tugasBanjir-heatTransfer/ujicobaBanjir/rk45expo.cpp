/******************************************************************************/
/* rkf45.cpp                                                                  */
/* Runge-Kutta-Fehlberg method for solving initial value problem              */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                         */
/* Absolutely no warranty implied or expressed                                */
/* ****************************************************************************/

#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

double f(double t, double x){
    return x ;}

void rk45(double f(double, double), double *t, double *x, double h, double *eps);

int main(){
    const double a = 0.0, b = 10.0;
    double x = 1.0, t, h, e;
    const int n = 100; 
    int i;
    double w;
    h = (b-a)/(double) n;
    t = a;

    for (i=1;i<=n;i++){
        rk45(f, &t, &x, h, &e);
        w = 1.0*exp(t);
        printf("%g %g %g %g %g\n", t, x, e, w, w-x);}

    return 0;}

/******************************************************************************/

void rk45(double f(double, double), double* t, double* x, double h, double* eps){
    double c20, c21;
    double c30, c31, c32;
    double c40, c41, c42, c43; 
    double c50, c51, c52, c53, c54;
    double c60, c61, c62, c63, c64, c65;
    double a1, a2, a3, a4, a5;
    double b1, b2, b3, b4, b5, b6;
    double K1, K2, K3, K4, K5, K6, x4, x5;
    
    c20=0.25;
    c21=0.25;
    c30=0.375;
    c31=0.09375;
    c32=0.28125;
    c40=(double) 12/ (double) 13;
    c41=(double) 1932/ (double) 2197;
    c42=(double) -7200/ (double) 2197;
    c43=(double) 7296/ (double) 2197;
    c50=1.0;
    c51=(double) 439/ (double) 216;
    c52=-8.0;
    c53=(double) 3680/ (double) 513;
    c54=(double) -845/ (double) 4104;
    c60=0.5;
    c61=(double) -8/ (double) 27;
    c62=2.0;
    c63=(double) -3544/ (double) 2565;
    c64=(double) 1859/ (double) 4104;
    c65=-0.275;
    a1= (double) 25/ (double) 216;
    a2= 0.0;
    a3= (double) 1408/ (double) 2565;
    a4= (double) 2197/ (double) 4104;
    a5= -0.2;
    b1= (double) 16/ (double) 135;
    b2= 0.0;
    b3= (double) 6656/ (double) 12825;
    b4= (double) 28561/ (double) 56430;
    b5= -0.18;
    b6= (double) 2/ (double) 55;

    K1 = h * f(*t, *x);
    K2 = h * f(*t + c20*h, *x + c21*K1);
    K3 = h * f(*t + c30*h, *x + c31*K1 + c32*K2);
    K4 = h * f(*t + c40*h, *x + c41*K1 + c42*K2 + c43*K3);
    K5 = h * f(*t +     h, *x + c51*K1 + c52*K2 + c53*K3 + c54*K4);
    K6 = h * f(*t + c60*h, *x + c61*K1 + c62*K2 + c63*K3 + c64*K4 + c65*K5);

    x4 = *x + a1*K1 + a3*K3 + a4*K4 + a5*K5; // RK4
    *x += b1*K1 + b3*K3 + b4*K4 + b5*K5 + b6*K6; // RK5 <-- using the higher order estimation
    *eps = fabs(*x - x4); // Error estimation
    *t += h;}
