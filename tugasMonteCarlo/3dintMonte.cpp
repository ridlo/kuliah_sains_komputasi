/**************************************/
/* definite integral using montecarlo */
/* 2012 - ridlo w. wibowo             */
/**************************************/
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

double unirand()
{
    return (double) rand()/ (double) RAND_MAX;
}

double f(double x, double y, double z)
{
    double w = x*y*z*z + x*x*y*z + x*y*y*z*z;
    return w;
}

int main()
{
    double res, x, y, z, w, a, b, c, d, e, fi, o=0.;
    int N=0, Ntot, i;
    a = 1.;
    b = 3.;
    c = 0.;
    d = 2.;
    e = 1.;
    fi = 4.;
    cout << "Menghitung nilai integral dengan MonteCarlo\n" ;
    cout << "Fungsi f(x, y, z) = xyz^2 + x^2yz + xy^2z^2  \n";
    cout << "dengan batas integrasi x=[1, 3] y=[0, 2] z=[1, 4]\n";
    cout << "Masukkan jumlah angka random = "; cin >> Ntot;
   
    srand(time(NULL)); // seed

    // mencari maximum fungsi dengan cara monte-carlo
    for (i=0;i<Ntot;i++){
        x = a + (b-a)*unirand();
        y = c + (d-c)*unirand();
        z = e + (fi-e)*unirand();
        if (fabs(f(x, y, z)) > o) {o = fabs(f(x, y, z));}
    }
    
    // mencari integral fungsi dengan cara monte-carlo
    ofstream out;
    out.open("3dintMonte_data.txt");
    for (i = 0; i<Ntot; i++){
        x = a + (b-a)*unirand();
        y = c + (d-c)*unirand();
        z = e + (fi-e)*unirand();
        if (f(x, y, z) > 0.){
            w = o*unirand();
            if (w <= f(x, y, z)){ N++; }
        }
        else {
            w = -o*unirand();
            if (w >= f(x, y, z)){ N--; }
        }
        out << x << " " << y << " " << z << " " << w << "\n";
    }
    out.close();

    res = (double)N / (double)Ntot * o*(b-a)*(d-c)*(fi-e);
    printf("Hasil integrasinya = %f\n", res);
    cout << o << endl ; 
    
    return 0;
}
