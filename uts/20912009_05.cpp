/* Ridlo Wahyudi W. - 20912009 */
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
using namespace std;

double K1=10.;
double K2=2.;
double C=0.001;
double D=0.002;

double fdP(double p, double q){return (K1*p - C*p*q);}
double fdQ(double p, double q){return (-K2*q + D*p*q);}
void plot();

int main(){
    int N=1000;
    double pi, qi, ti, tf, h;
    double p, q, t;
    // kondisi awal
    pi=5000.;
    qi=100.;
    ti=0.;
    tf=5.;
    h = (tf-ti)/(double) N; // time step
    p=pi; q=qi; t=ti; // inisiasi 
    
    // Verlet algorithm -> gak yakin
    ofstream out;
    out.open("20912009_05_Ver_out.txt");
    out << t << " " << p << " " << q << endl;
    for (int i=1;i<=N;i++){
        p = p + fdP(p,q)*h;
        q = q + fdQ(p,q)*h; 
        t = t + h;
        out << t << " " << p << " " << q << endl;
    }
    out.close();
    
    // Runge-Kutta method
    p=pi; q=qi; t=ti; // inisiasi lagi
    ofstream outfile;
    outfile.open("20912009_05_RK_out.txt");
    outfile << t << " " << p << " " << q << endl;
    double kp1, kp2, kp3, kp4, kq1, kq2, kq3, kq4;
    double ksp, ksq;
    for (int i=1;i<=N;i++){
            kp1 = h*fdP(p, q); 
            kq1 = h*fdQ(p, q);
            
            ksp = p+kp1/2.; ksq = q+kq1/2.;
            kp2 = h*fdP(ksp, ksq);
            kq2 = h*fdQ(ksp, ksq);
            
            ksp = p+kp2/2.; ksq = q+kq2/2.;
            kp3 = h*fdP(ksp, ksq);
            kq3 = h*fdQ(ksp, ksq);
            
            ksp = p+kp3; ksq = q+kq3;
            kp4 = h*fdP(ksp, ksq);
            kq4 = h*fdQ(ksp, ksq);
        
        p = p + (kp1 + 2.*(kp2+kp3) + kp4)/6.;
        q = q + (kq1 + 2.*(kq2+kq3) + kq4)/6.;
        t = t + h;
        outfile << t << " " << p << " " << q << endl;
    } 
    outfile.close(); 
    
    plot();

    return 0;
}

void plot(){
    // plot hasil
    ofstream ploter("ploter.in");
    ploter << "#gnuplot input file\n";
    ploter << "set term png \n";
    ploter << "set output \"RK.png\"\n";
    ploter << "set xlabel \"t (tahun)\" \n";
    ploter << "set ylabel \"N\" \n";
    ploter << "plot \"20912009_05_RK_out.txt\" u 1:2 w l title \"Populasi Kijang\", \"20912009_05_RK_out.txt\" u 1:3 w l title \"Populasi Harimau\"\n";
    ploter << "set output \"Verlet.png\"\n";
    ploter << "set xlabel \"t (tahun)\" \n";
    ploter << "set ylabel \"N\" \n";
    ploter << "plot \"20912009_05_Ver_out.txt\" u 1:2 w l title \"Populasi Kijang\", \"20912009_05_Ver_out.txt\" u 1:3 w l title \"Populasi Harimau\"\n";
    ploter.close();
    
    // jalankan gnuplot
    system("gnuplot < ploter.in");
}
