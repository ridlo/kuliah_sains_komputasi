/* Ridlo Wahyudi W. - 20912009 */
// Genetic Algorithm

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;

double a=0., b=0.3;
int p=10; // jumlah populasi
int MAX=1000; // maksimum iterasi
double pEl=0.25; // probabilitas bikin individu baru di sekitar xbest
double mEl=0.1*(b-a); // rentang sebaran
double pMt=0.25; // probabilitas ganti individu

double f(double x){ return 10. + (sin(1./x))/((x-0.16)*(x-0.16));}

double x['p'], y['p']; // populasi
double xbetter, ybetter, xbest, ybest;
double xi['p'], yi['p']; // induk
double xa['p'], ya['p']; // offspring
double unirand(){return (double)rand()/(double)RAND_MAX;}
void generate();
void fitness();
void best();
void better();
void bob();
void selection();
//void crossover();
void mutasi();
void print_pop();
void plot();

int main(){
    //cout << "Genetic Algorithm for maximum of function\n";
    unsigned int k=1;
    srand(time(NULL));
    generate();
    fitness();
    print_pop();
    cout << "\n\n";
    best();
    ofstream out("20912009_06_out.txt");
    out << k << " " << xbest << " " << ybest << endl;
    for (int i=0;i<MAX;i++){
        selection();
        for (int i=0;i<p;i++){x[i] = xi[i]; y[i] = yi[i];} // swap pop dg induk
        better(); // cek pop
        bob();
        print_pop();
        cout << "\n\n";
        mutasi();
        for (int i=0;i<p;i++){x[i] = xa[i]; y[i] = ya[i];} // swap pop dg anak (induk yg dimutasi)
        better();
        bob();
        k = k+1;
        out << k << " " << xbest << " " << ybest << endl;
        //print_pop();
        //cout << "\n\n";
    }
    out.close();
    //cout << "Hasil terbaik setelah " << MAX << " iterasi: " << endl;
    //cout << "x    = " << xbest << endl;
    //cout << "f(x) = " << ybest << endl;

    plot();
    return 0;
}

void generate(){// generate populasi
    for (int i=0;i<p;i++){
        x[i] = (b-a)*unirand()+a;}
}

void fitness(){
    for (int i=0;i<p;i++){
        y[i] = f(x[i]);}
}

void best(){
    xbest = x[0];
    ybest = y[0];
    for (int i=1;i<p;i++){
        if (y[i] > ybest){ 
            ybest = y[i];
            xbest = x[i];}}
}

void better(){
    xbetter = x[0];
    ybetter = y[0];
    for (int i=1;i<p;i++){
        if (y[i] > ybetter){ 
            ybetter = y[i];
            xbetter = x[i];}}
}

void bob(){
    if (ybetter > ybest){
        ybest = ybetter;
        xbest = xbetter;}
}

void selection(){ 
    // elistism -> membuat induk d yg dkt2 induk terbaik 
    // kok jadi kayak SA -_-? 
    double prob;
    for (int i=0;i<p;i++){
        prob = unirand();
        if (prob<pEl){
            xi[i] = fmod(mEl*unirand() + (xbest - 0.5*mEl), b) + a; 
            // sebar disekitar maksimum dalam rentang mEl, 
            // modulo -> kalau2 maksimum ada dibatas
            yi[i] = f(xi[i]);}
        else{
            xi[i] = x[i];
            yi[i] = y[i];}
    }
}

void mutasi(){
    // mutasi dengan cara buat baru
    double pmut;
    for (int i=0;i<p;i++){
        pmut = unirand();
        if (pmut<pMt){
            xa[i] = (b-a)*unirand() + a;
            ya[i] = f(xa[i]);}
        else{
            xa[i] = xi[i];
            ya[i] = yi[i];}
    }
}

void print_pop(){for (int i=0;i<p;i++){cout << x[i] << " " << y[i] << endl;}}

void plot(){
    ofstream ploter("plot_ga.in");
    ploter << "# gnuplot input file\n";
    ploter << "set xlabel \"iterasi\"\n";
    ploter << "set ylabel \"fitness - f(x)\"\n";
    ploter << "plot \"20912009_06_out.txt\" u 1:3 w l lc 2 title \"fitness\"\n";
    ploter.close();
    
    system("gnuplot -persist < plot_ga.in");
}
