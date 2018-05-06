/**********************************************************************/
/* terjun.cpp                                                         */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                 */
/* Sangat tidak terjamin kebenarannya. wkwk                           */
/**********************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#define G 9.8
#define M 1.0
using namespace std;

double f(double t, double v)
{
    if (t < 20.)
    {
        return -G;
    }
    else if (t >= 20. && t < 100.) // saat t = 20 parasut di buka.
    {
        double a, c=0.5;
        a = -G - c*v/M;
        return a;
    }
    else {
        return 0.0;
    }
}

int main()
{
    int N = 5000, i, j;
    double ti=0.0, tf=100., yi=3000., vi=0.0, h;
    h = (tf-ti)/(double) N;
    double y[N], v[N], t[N];
    y[0] = yi;
    v[0] = vi;
    t[0] = ti;

    for (i=1;i<=N;i++){
        double ky1, kv1, ky2, kv2, ky3, kv3, ky4, kv4;
        ky1 = h*v[i-1];
        kv1 = h*f(t[i-1], v[i-1]);        
        ky2 = h*(v[i-1] + kv1/2.);
        kv2 = h*f(t[i-1] + h/2., v[i-1] + kv1/2.);
        ky3 = h*(v[i-1] + kv2/2.);
        kv3 = h*f(t[i-1] + h/2., v[i-1] + kv2/2.);
        ky4 = h*(v[i-1] + kv3);
        kv4 = h*f(t[i-1] + h, v[i-1] + kv3);
        
        if (y[i-1] > 0.01)
        {
            y[i] = y[i-1] + (ky1 + 2.*(ky2+ky3) + ky4)/6.;
            v[i] = v[i-1] + (kv1 + 2.*(kv2+kv3) + kv4)/6.;
            t[i] = t[i-1] + h;
        }
        else {
            y[i] = 0.0;
            v[i] = 0.0;
            t[i] = t[i-1] + h;
        }
    }
    
    ofstream outfile;
    outfile.open("terjun.txt");
    for (j=0;j<=N;j++){
        outfile << t[j] << " " << v[j] << " " << y[j] << "\n";}
    outfile.close();

    ofstream ploter;
    ploter.open("plot.in");
    ploter << "# gnuplot input\n";
    ploter << "set terminal wxt size 800, 300\n";
    ploter << "set multiplot layout 1,2\n";
    ploter << "set xlabel \"t\"\n";
    ploter << "set ylabel \"y(t)\"\n";
    ploter << "plot \"terjun.txt\" using 1:3 with lines\n";
    ploter << "set ylabel \"v(t)\"\n";
    ploter << "plot \"terjun.txt\" using 1:2 with lines\n";
    ploter << "unset multiplot\n";
    ploter.close();
    
    system("gnuplot -persist < plot.in");

    return 0;
}
