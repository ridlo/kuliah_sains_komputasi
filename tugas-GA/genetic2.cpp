/********************************************************/
/* Simple Genetic Algorithm | N-dimensional Function    */
/* Copyleft (c) 2012. Ridlo W. Wibowo                   */
/********************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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
/* jumlah variabel dalam fungsi */
int v = 2;

/* batas bawah dan atas fungsi */
int u=2*v;
//double bou['u'] = {-5., 5., -5., 5.}; // dua-dua
double bou['u'] = {-4., 4., -4., 4.}; 

/* ketelitian variable yang dicari (angka di belakang koma) */
int k['v'] = {5, 5}; 

/* fungsi */
double func(double x[]){
    return (0.5*(pow(x[0],4) - 16*pow(x[0],2) + 5*x[0]) + 0.5*(pow(x[1],4) - 16*pow(x[1],2) + 5*x[1]));
    //return (x[0]*x[0] - 10*cos(2.*M_PI*x[0]) + 10. + x[1]*x[1] - 10*cos(2.*M_PI*x[1]) + 10.);
}


/* jumlah khromosom dalam populasi */
int n = 50;

/* peluang terjadi cross-over */
double pc = 0.8;

/* peluang terjadi mutasi */
double pm = 0.1;

/* banyaknya iterasi */
int N = 500;

/* tipe optimasi, 0 = maximisasi, 1 = minimisasi */
int tipe = 1;



/************* GENETIC FUNCTION ************/
/* panjang vektor biner per variabel */
double lvar['v'];
/* panjang vektor biner total */
double l=0;
void vecLength(){
    for (int i=0;i<v;i++){
        lvar[i] = ceil(minL(bou[(2*i)],bou[(2*i)+1],k[i]));
        l += lvar[i];
    }
}

/* populasi */
int pop['n']['l'];
int induk['n']['l'];
int anak['n']['l'];

/* desimal, variabel dan fitness */
double x['n']['v']; double y['n'];
double xbest['v']; double ybest;
double xbestpop['v']; double ybestpop;

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
    int xpart['n']['v']['l'];
    for (int i=0;i<n;i++){
        int sum1 = 0;
        int sum2 = 0;
        for (int j=0;j<v;j++){
            sum2 = sum1+lvar[j];
            int o = 0;
            for (int w=sum1;w<sum2;w++){
                xpart[i][j][o] = pop[i][w];
                o += 1;
            }
            sum1 = sum2;
        }
    }
    
    for (int i=0;i<n;i++){
        for (int j=0;j<v;j++){
            x[i][j] = toDec(bou[(2*j)],bou[(2*j)+1],lvar[j],xpart[i][j]);
        }
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
    
    double mini = y[0];
    for (int i=1;i<n;i++){
        if (y[i] < mini){ mini = y[i];}
    }
    
    double geser = fabs(mini) + 1.;
    if (tipe == 0){
        for (int i=0;i<n;i++){ 
            fit[i] = (y[i] + geser);
         }
    } // maksimisasi
    else{for (int i=0;i<n;i++){ fit[i] = 1./(y[i]+geser);}} // minimisasi
    
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
    for (int i=0;i<v;i++){ xbestpop[i] = x[0][i];}
    ybestpop = y[0];
    if (tipe == 0){
        for (int i=1;i<n;i++){
            if (y[i] > ybestpop){
                for (int j=0;j<v;j++){ xbestpop[j] = x[i][j];}
                ybestpop = y[i];
            }
        }
    } else{
        for (int i=1;i<n;i++){
            if (y[i] < ybestpop){
                for (int j=0;j<v;j++){ xbestpop[j] = x[i][j];}
                ybestpop = y[i];
            }
        }
    }
    
    if (tipe == 0){
        if (ybestpop > ybest){ 
            ybest = ybestpop; 
            for (int j=0;j<v;j++){ xbest[j] = xbestpop[j];}
        }
    } else{
        if (ybestpop < ybest){
            ybest = ybestpop; 
            for (int j=0;j<v;j++){ xbest[j] = xbestpop[j];}
        }
    }
}

/* print best of the best */
void init(){
    keep_the_best(); 
    for (int j=0;j<v;j++){ xbest[j] = xbestpop[j];}
    ybest = ybestpop;
}
void print_best(){
    for (int j=0;j<v;j++){ cout << xbest[j] << " ";}
    cout << " " << ybest << endl;
}
void print_best_pop(){
    for (int j=0;j<v;j++){ cout << xbestpop[j] << " ";}
    cout << " " << ybestpop << endl;
} 

/* print real variable */
void print_real(){
    for (int i=0;i<n;i++){
        for (int j=0;j<v;j++){ cout << x[i][j] << " ";}
        cout << y[i] << endl;
    }
    cout << "\n\n";
}


/*************** FUNGSI-FUNGSI TESTING ******************/
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


/*************** MAIN ***************/
int main(){
    vecLength();
    srand(time(NULL));
    generate();
    init(); //print_pop();
    for (int s=0;s<N;s++){
        selectRoulette();
        //print_induk();  
        crossover();
        //print_anak();
        mutasi();
        //print_anak();
        swapper();
        keep_the_best();
        //print_real();
        //print_best_pop();
    }
    cout << "\nBest value: \n";
    print_best();
     
    return 0;
}
