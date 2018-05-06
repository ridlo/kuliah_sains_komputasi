/****************************************************/
/* Simple Genetic Algorithm - 1D function           */
/* Copyleft (c) 2012. Ridlo W. Wibowo               */
/****************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
#define _USE_MATH_DEFINES
using namespace std;

/***************** FUNCTION *********************/
/* mencari panjang vektor biner minimum */
double minL(double xi, double xf, int ko){
    return log((xf-xi) * pow(10., ko) + 1.)/log(2.);
}

/* random biner */
int brand(){ return rand()%2;}

/* random uniform 0-1 */
double unirand(){ return (double)rand()/(double)RAND_MAX;}

/* menghitung nilai real desimal */
double toDec(double xi, double xf, double li, int khrom[]){
    unsigned int sum = 0;
    for (int i=0;i<li;i++){ sum += khrom[i]*pow(2,i);}
    return (xi + sum*((xf-xi)/(pow(2,li) - 1)));
}

/****************** INPUT PARAMETER *********************/
/* fungsi */
double func(double x){
    //return (x*x - 10.*cos(2.*M_PI*x) + 10.);
    return (x*sin(10.*M_PI*x) + 1.);
}

/* batas bawah dan atas fungsi */
double a = -1.;
double b = 2.;

/* ketelitian bilangan (angka di belakang koma) */
// anggap ketelitian yang di inginkan setiap variabel sama
int k = 5; //angka di belakang koma

/* jumlah khromosom dalam populasi */
int n = 50;

/* peluang terjadi cross-over */
double pc = 0.8;

/* peluang terjadi mutasi */
double pm = 0.1;

/* banyaknya iterasi */
int N = 300;

/* tipe optimasi, 0 = maximisasi, 1 = minimisasi */
int tipe = 0;

/************* GENETIC FUNCTION ************/
double l = ceil(minL(a,b,k));

/* populasi */
int pop['n']['l'];
int induk['n']['l'];
int anak['n']['l'];

/* desimal, variabel dan fitness */
double x['n']; double y['n'];
double xbest, ybest;
double xbestpop, ybestpop;

/* Generate Populasi Awal - biner */
void generate(){
    for (int i=0;i<n;i++){
        for (int j=0;j<l;j++){
            pop[i][j] = brand();
        }
    }
}

/* mencari nilai fitness */
void fitness(){
    for (int i=0;i<n;i++){
        x[i] = toDec(a,b,l,pop[i]);
        y[i] = func(x[i]);
    }
}

/* selection, Roulette-Wheel */
void selectRoulette(){
    fitness();
    double totFit = 0.;
    double cumFit['n'];
    double tot = 0.;
    double fit['n'];
    double rs;
    
    double mini = y[0]; // cari minimum fitness
    for (int i=1;i<n;i++){ 
        if (y[i] < mini){ mini = y[i];}
    }
    
    double geser = fabs(mini) + 1; // geser dikitlah
    if (tipe == 0){
        for (int i=0;i<n;i++){ 
            fit[i] = (y[i] + geser);
        }
    } // maksimisasi
    else{for (int i=0;i<n;i++){ fit[i] = 1./(y[i] + geser) ;}} // minimisasi
    
    for (int i=0;i<n;i++){ totFit = totFit + fit[i];}
    for (int i=0;i<n;i++){ 
        cumFit[i] = tot + (fit[i]/totFit); 
        tot = cumFit[i];
    }

    for (int i=0;i<n;i++){
        rs = unirand();
        for (int j=0;j<n;j++){
            if (rs <= cumFit[j]){
                for (int w=0;w<l;w++){ induk[i][w] = pop[j][w];}
                break;
            }
        }
    }
}

/* cross-over */
void crossover(){
    int parent['n']['l'];
    int j=0;
    int p=0;
    for (int i=0;i<n;i++){
        if (unirand() <= pc){
            for (int w=0;w<l;w++){ parent[j][w] = induk[i][w];}
            j += 1;
        }
        else{
            for (int w=0;w<l;w++){ anak[p][w] = induk[i][w];}
            p += 1;
        }
    }
    if (j%2 == 1){ // kalau ganjil
        for (int w=0;w<l;w++){ anak[p][w] = parent[j-1][w];}
        p += 1;
        j -= 1;
    }
    for (int i=0;i<j/2;i++){
        int rk = 1 + rand()%((int)l-1);
        for (int q=0;q<rk;q++){
            anak[p+(2*i)][q] = parent[(2*i)][q];
            anak[p+(2*i+1)][q] = parent[(2*i+1)][q];
        }
        for (int r=rk;r<l;r++){
            anak[p+(2*i)][r] = parent[(2*i+1)][r];
            anak[p+(2*i+1)][r] = parent[(2*i)][r];
        }
    }
}

/* mutation */
void mutasi(){
    for (int i=0;i<n;i++){
        for (int j=0;j<l;j++){
            if (unirand() <= pm){
                if (anak[i][j] == 0){ anak[i][j] = 1;}
                else{ anak[i][j] = 0;}
            }
        }
    }
}

/* tukar populasi lama dengan yang baru */
void swapper(){
    for (int i=0;i<n;i++){
        for (int j=0;j<l;j++){
            pop[i][j] = anak[i][j];
        }
    }
}

/* simpan nilai terbaik di populasi */
void keep_the_best(){
    fitness();
    xbestpop = x[0], ybestpop = y[0];
    if (tipe == 0){
        for (int i=1;i<n;i++){
            if (y[i] > ybestpop){ xbestpop = x[i]; ybestpop = y[i];}
        }
    } else{
        for (int i=1;i<n;i++){
            if (y[i] < ybestpop){ xbestpop = x[i]; ybestpop = y[i];}
        }
    }

    if (tipe == 0){
        if (ybestpop > ybest){ ybest = ybestpop; xbest = xbestpop;}
    } else{
        if (ybestpop < ybest){ ybest = ybestpop; xbest = xbestpop;}
    }
}

/* print best of the best */
void init(){keep_the_best(); xbest = xbestpop; ybest = ybestpop;}
void print_best(){ cout << xbest << " " << ybest << endl;}
void print_best_pop(){ cout << xbestpop << " " << ybestpop << endl;}

/* print real variable */
void print_real(){
    for (int i=0;i<n;i++){
        cout << x[i] << " " << y[i] << endl;
    }
    cout << "\n\n";
}

/* print populasi */
void print_pop(){
    for (int i=0;i<n;i++){
        for (int j=0;j<l;j++){
            cout << pop[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/* print induk */
void print_induk(){
    for (int i=0;i<n;i++){
        for (int j=0;j<l;j++){
            cout << induk[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/* print anak */
void print_anak(){
    for (int i=0;i<n;i++){
        for (int j=0;j<l;j++){
            cout << anak[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/* simple plot */
void plotter(){
    ofstream plot("plot.gnu");
    //plot << "set yrange [-1:45]\n";
    plot << "set xlabel \"Number of iteration\"\n";
    plot << "set ylabel \"Fitness - f(x)\"\n";
    plot << "plot \"best.txt\" u 1:3 w l, \"best-pop.txt\" u 1:3 w l\n";
    plot.close();
    system ("gnuplot -persist < plot.gnu");
}

/*************** MAIN ***************/
int main(){
    // cout << l << endl;
    
    srand(time(NULL));
    
    generate();
    init(); // print_pop();
    ofstream out1("best-pop.txt");
    ofstream out2("best.txt");
    for (int s=0;s<N;s++){
        selectRoulette();
        // print_induk();  
        crossover();
        // print_anak();
        mutasi();
        // print_anak();
        swapper();
        keep_the_best();
        //out1 << s << " " << xbestpop << " " << ybestpop << endl;       
        //out2 << s << " " << xbest << " " << ybest << endl; 
        //print_real();
        //cout << s << " "; print_best_pop();
        //cout << s << " "; print_best();
    }
    cout << "\nBest Value: \n";
    print_best();
    //out1.close(); out2.close();
    //plotter();
    return 0;
}
