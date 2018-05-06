/******************************************************************************/
/* banjir.cpp                                                                 */
/* Runge-Kutta-Fehlberg method for solving initial value problem              */
/* Copyleft (c) 2012. Ridlo W. Wibowo                                         */
/* Absolutely no warranty implied or expressed                                */
/******************************************************************************/

#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

/* Konversi Satuan */
// panjang -> cm
// waktu   -> hari

double A = 6615200000000.0; // cm2

/*** MASUK ***/
// Qr(t), Hujan
double Qr(double t){
    //double vr = 0.4517453798767967; // cm/hr
    //double Qrc = vr*A; // cm3/hr
    double Qrc = 2988386036960.9854; // cm3/hr
    return Qrc;}

// Qf(t), Sungai dan banjir kiriman
double Qf(double t){
    double Qfc = 345600000000000.0; // cm3/hr
    return Qfc;}

/*** KELUAR ***/
// Qd(t, y), Kanal Pembuangan
double Qd(double t, double y){
    double Qdc = 259200000000000.0; // cm3/hr
    //if (y > 0.001){
        return Qdc;}
    //else{
      //  return 0.;}}

// Qa(t, y), Penyerapan Tanah
double Qa(double t, double y){
    double c;
    double Qac;
    // asumsi a=100 , g = 9.8 m/s2 = 7315660800000.0 cm/hr2,  
    c = 3825091057.7396717;
    Qac = c*sqrt(y);
    /*if (y > 0.001){
        Qac = c*sqrt(y);}
    else{
        Qac = 0.;}*/
    return Qac;}

// Qu(t), Penguapan
double Qu(double t){
    double Quc = 86400000000000.0; // cm3/hr
    return Quc;}


/*****************************************************************************/
/* y' =f(t, y) = Qr(t) + Qf(t) - Qd(t, y) - Qa(t, y) - Qu(t)                 */
double dy(double t, double y){
    double w;
    w = (Qr(t) + Qf(t) - Qd(t, y) - Qa(t, y) - Qu(t))/A;



void rkf45(double dy(double, double), double *t, double *y, double h, double *eps);


int main(){
    const double a = 0.0, b = 730.50;
    double y = 1.0, t, h, e;
    const int n = 73050;
    int i;
    
    h = (b-a)/(double) n;
    t = a;
    
    for (i=1;i<=n;i++){
        rkf45(dy, &t, &y, h, &e);
        printf("%f %f %g\n", t, y, e);}

    return 0;}

/******************************************************************************/

void rkf45(double dy(double, double), double* t, double* y, double h, double* eps){
    double c20, c21;
    double c30, c31, c32;
    double c40, c41, c42, c43; 
    double c50, c51, c52, c53, c54;
    double c60, c61, c62, c63, c64, c65;
    double a1, a2, a3, a4, a5;
    double b1, b2, b3, b4, b5, b6;
    double K1, K2, K3, K4, K5, K6, y4;
    
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

    K1 = h * dy(*t, *y);
    K2 = h * dy(*t + c20*h, *y + c21*K1);
    K3 = h * dy(*t + c30*h, *y + c31*K1 + c32*K2);
    K4 = h * dy(*t + c40*h, *y + c41*K1 + c42*K2 + c43*K3);
    K5 = h * dy(*t +     h, *y + c51*K1 + c52*K2 + c53*K3 + c54*K4);
    K6 = h * dy(*t + c60*h, *y + c61*K1 + c62*K2 + c63*K3 + c64*K4 + c65*K5);

    y4 = *y + a1*K1 + a3*K3 + a4*K4 + a5*K5; // RK4
    *y += b1*K1 + b3*K3 + b4*K4 + b5*K5 + b6*K6; // RK5 <-- using the higher order estimation
    *eps = fabs(*y - y4); // Error estimation
    *t += h;}

