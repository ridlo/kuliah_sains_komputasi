/************************************************/
/* ftcs.cpp (forward time central space)        */
/* forward difference method - parabolic PDE    */
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
    cout << "### Parabolic PDE - Forward Difference Method ###\n";
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

    double wi[100];
    double wf[100];
    double x[100];

    // syarat batas
    wi[0] = 0.0;
    wi[nx] = 0.0;
    
    // syarat awal
    x[0] = xi;
    x[nx] = xf;
    for (int i=1; i<nx; i++){
        x[i] = x[i-1] + h;
        wi[i] = sin(x[i]);}
    
    // bentuk output filenya aneh, karena untuk 
    // mempermudah ketika membuat animasi memakai gnuplot
    ofstream out("ftcs-out.txt");
    // print kondisi awal
    for (int i=0; i<=nx; i++){
        out << x[i] << " " << wi[i] << "\n";}
    
    // kerjo dimulai.. ayo
    for (int j=1; j<=nt; j++){
        wf[0] = wi[0];
        wf[nx] = wi[nx];
        for (int i=1; i<nx; i++){
            wf[i] = (1.-2.*lam)*wi[i] + lam*(wi[i+1] + wi[i-1]);}
        
        // print, njur sekalian tuker baru
        out << "\n\n" ;
        for (int i=0; i<=nx; i++){
            out << x[i] << " " << wf[i] << "\n";
            wi[i] = wf[i];}}
    out.close(); 
    cout << "finish...\n";
    return 0;
}
