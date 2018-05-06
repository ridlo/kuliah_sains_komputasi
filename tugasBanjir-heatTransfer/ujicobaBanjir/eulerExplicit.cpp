#include<iostream>
#include<math.h>
using namespace std;

float fungsi(float y){
    float fy;
    fy = -4.0e-12*(pow(y, 4) - pow(250.0, 4));
    return fy;}

int main(){
    float y0, dt, a, b;
    y0 = 2500.;
    a  = 0.;
    b  = 10.;
    int N  = 5;

    dt = (b-a)/N;
    float y[N];
    y[0] = y0;
    for (int i=0;i<N;i++){
        y[i+1] = y[i] + dt*fungsi(y[i]);
        cout << dt*(i+1) << "\t" << y[i+1] << "\n";}

    return 0;}

