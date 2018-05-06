#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;

/*************************************************************************************/
int npop = 20; // jumlah populasi
int gen  = 15; // jumlah gen di setiap khromosom (jumlah kota)
int m=npop, n=gen; 
int populasi['m']['n']; // matriks populasi
int induk['m']['n'];
int anak['m']['n'];

int jarak['n']['n']; // matriks jarak antar kota
int fitness['m']; // matriks penampung fitness tiap khromosom (jarak yang dilalui)
int min_best, min_better;
int khromTerbaik['n']; // khromosom dengan fitness terkecil dari populasi sebelumnya
int khromBaik['n']; // khromosom dengan fitness terkecil dari populasi baru
int GA_MAXITER=1000;
float pMut=0.4;

/*************************************************************************************/
void input(); // input jarak antar kota: random, simetris, 1-30 
void generate(); // generate populasi
void nilaiFit(); // cek fitness
void best();
void better();
void best_of_the_best();
void elistism();
void selection(); 
//void crossover(); 
void mutasi(); 
void swaper(); 
//void print_matrix(int *matrix, int rows, int cols);// print matriks, untuk cek
void printp();
void printi();
void printa();
void printpf();
void printj();
void print_minFit();

/************************************************************************************/
/* main program */
int main(int argc, char **argv){ 
    cout << "--- Genetic Algorithm for TSP ---\n";
    srand(time(NULL));
    input(); // generate jarak random
    generate(); // generate populasi random
    nilaiFit();
    best();
    for (int i=0; i<GA_MAXITER;i++){
        nilaiFit(); // nyari fitness di populasi
        better(); // nyari fitness terbaik di populasi
        best_of_the_best(); // bandingkan yang terbaik dg terbaik sblmnya
        //printpf();
        print_minFit(); // print kromosom terbaik dan fitnessnya

        selection(); // seleksi induk dari populasi -> induk
        //selectRoulet();
        //cout << endl;
        //printi();
        
        //crossover(); // kawinkan induk -> anak
        
        mutasi(); // mutasikan anak -> anak termutasi
        //cout << endl;
        //printa();
        swaper(); // swap anak dan populasi -> populasi baru
        
        //elistism();
    }
    return 0;
}

/***********************************************************************************/
void input(){
    for (int i=0;i<gen;i++){
        for (int j=0;j<=i;j++){
            if (j==i){
                jarak[i][j] = 0;}
            else{
                jarak[i][j] = rand()%20 + 1;}}}
    
    for (int j=0;j<gen;j++){              // simetrisasi
        for (int i=0;i<=j;i++){
            jarak[i][j] = jarak[j][i];}}
}

void generate(){
    bool sami;  
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            do {
                sami = false;
                populasi[i][j] = rand()%gen;
                for (int k=0;k<j;k++){
                    if (populasi[i][j] == populasi[i][k]){
                        sami = true;
                        break;}}
            } while (sami);}}
}

void nilaiFit(){
    int jpop, a, b;
    for (int i=0;i<npop;i++){
        jpop = 0;
        for (int j=0;j<gen;j++){
            j += gen;
            a = populasi[i][j%gen];
            b = populasi[i][(j+1)%gen];
            jpop += jarak[a][b];
            j -= gen;}
        fitness[i] = jpop;}
}

void best(){
    min_best = fitness[0];
    for (int j=0;j<gen;j++){
        khromTerbaik[j] = populasi[0][j];}

    for (int i=1;i<npop;i++){
        if (fitness[i] < min_best){
            for (int j=0;j<gen;j++){
                khromTerbaik[j] = populasi[i][j];}
            min_best = fitness[i];}}
}

void better(){
    min_better = fitness[0];
    for (int j=0;j<gen;j++){
        khromBaik[j] = populasi[0][j];}

    for (int i=1;i<npop;i++){
        if (fitness[i] < min_better){
            for (int j=0;j<gen;j++){
                khromBaik[j] = populasi[i][j];}
            min_better = fitness[i];}}
}

void best_of_the_best(){
    if (min_better < min_best){
        for (int i=0;i<gen;i++){
            khromTerbaik[i] = khromBaik[i];}
        min_best = min_better;}
}

void elistism(){
    for (int j=0;j<gen;j++){
        populasi[0][j] = khromBaik[j];}
}

void selection(){ // copy
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            induk[i][j] = populasi[i][j];}}
}

void selectRoulet(){
    // roulette
    double r['m'];
    int roulet['m'];
    int sumfitness=0;
    double prosenfit['m'];
    double cumprofit['m'];
    double tot=0.;
    
    for (int i=0;i<npop;i++){
        sumfitness = sumfitness + fitness[i];}

    for (int i=0;i<npop;i++){
        prosenfit[i] = (double)fitness[i]/(double)sumfitness;}
}

void mutasi(){
    // copy induk dulu
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            anak[i][j] = induk[i][j];}}
    
    float p;
    int gen_a, gen_b;
    // mutation
    for (int i=0;i<npop;i++){
        p = ((double)rand()/(double)RAND_MAX);
        if (p<=pMut){
            gen_a = rand()%gen;
            gen_b = rand()%gen;
            anak[i][gen_a] = induk[i][gen_b];
            anak[i][gen_b] = induk[i][gen_a];}}
}

void swaper(){
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            populasi[i][j]=anak[i][j];}}
}

/*void crossover(){
    int parent1['n'];
    int parent2['n'];
    int child['n']
*/

/*void mutasi(){
    int gen_a, gen_b;
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            buffer
*/

/******************************************************************************/
// urusan ngeprint untuk check
void printp(){
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            cout << populasi[i][j] << "\t";}
        cout << endl;}
}

void printi(){
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            cout << induk[i][j] << "\t";}
        cout << endl;}
}

void printa(){
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            cout << anak[i][j] << "\t";}
        cout << endl;}
}

void printpf(){
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            cout << populasi[i][j] << "\t";}
        cout << "... (" << fitness[i] << ")" << endl;}
}

void printj(){
    for (int i=0;i<gen;i++){
        for (int j=0;j<gen;j++){
            cout << jarak[i][j] << "\t";}
        cout << endl;}
}

void print_minFit(){
    for (int j=0;j<gen;j++){
        cout << khromTerbaik[j] << "\t";}
    cout << "... (" << min_best << ")" << endl;
}

/*
?? knp fail ??
void print_matrix(int *matrix, int rows, int cols){
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            cout << matrix[cols*i +j] << "\t";}
        cout << endl;}
}

*/

