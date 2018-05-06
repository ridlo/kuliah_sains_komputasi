/************************************************/
/* CN.cpp (Crank-Nicolson method)               */
/* parabolic PDE                                */
/* Copyleft (c) 2012. Ridlo W. Wibowo           */
/************************************************/
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#define _USE_MATH_DEFINES
using namespace std;


int main(){
    cout << "### Parabolic PDE - Crank-Nicolson Method ###\n";
    cout << "--- Equation : d(u)/dt = d^2(u)/dx^2 with u(x,t) ---\n";
    double xi = 0.0, xf=M_PI; // L=1.0 -> rentang x
    double ti = 0.0, tf=0.5; // time
    int nt = 10; // jumlah pemenggalan di t
    int nx = 10; // jumlah pemenggalan di x

    double k = (tf-ti)/nt;
    double h = (xf-xi)/nx;
    
    double alpha = 1.;
    double lam = alpha*alpha*k/(h*h);
    cout << "alpha         = " << alpha << endl;
    cout << "step in x (h) = " << h << endl;
    cout << "step in t (k) = " << k << endl;
    cout << "lambda        = " << lam << endl;

    double w[100];
    double x[100];
    double l[100], u[100], z[100];

    // syarat batas
    w[0] = 0.0;
    w[nx] = 0.0;
    
    // syarat awal, insiasi
    x[0] = xi;
    x[nx] = xf;
    for (int i=1; i<nx; i++){
        x[i] = x[i-1] + h;
        w[i] = sin(x[i]);}
    

    // Crout method
    l[1] = 1. + lam;
    u[1] = -lam/(2.*l[1]);

    for (int i=2;i<(nx-1);i++){
        l[i] = 1. + lam + lam*u[i-1]/2.;
        u[i] = -lam/(2.*l[i]);}

    l[nx-1] = 1. + lam + lam*u[nx-2]/2.;
    
    //for (int i=1;i<nx;i++){
    //    cout << l[i] << endl;}
    
    // bentuk output filenya aneh, karena untuk 
    // mempermudah ketika membuat animasi memakai gnuplot
    ofstream out("CN-out.txt");
    // print kondisi awal
    for (int i=0; i<=nx; i++){
        out << x[i] << " " << w[i] << "\n";}
    
    // kerjo dimulai.. ayo
    for (int j=1; j<=nt; j++){
        w[0] = 0.0;
        w[nx] = 0.0;
        z[1] = ((1.-lam)*w[1] + (lam/2.)*w[2])/l[1];
        for (int i=2;i<nx;i++){
            z[i] = ((1.-lam)*w[i] + (lam/2.)*(w[i+1] + w[i-1] + z[i-1]))/l[i];}
        w[nx-1]=z[nx-1];

        for (int i=nx-2;i>=1;i--){
            w[i] = z[i] - u[i]*w[i+1];}
        
        out << "\n\n";
        for (int i=0;i<=nx;i++){
            out << x[i] << " " << w[i] << "\n";}}
    out.close();
    
    cout << "finish...\n";
    return 0;
}
