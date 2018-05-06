/***************************************************/
/* Genetic Algorithm for TSP                       */
/* copyleft (c) 2012. Ridlo W. Wibowo              */
/***************************************************/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
using namespace std;

/*************************************************************************************/
int npop = 30; // jumlah populasi
int gen  = 30; // jumlah gen di setiap khromosom (jumlah kota)
double MAX = 100.; // Maksimum dimensi cluster kota
int GA_MAXITER = 1000; // Maksimum iterasi GA
float pMut=0.4; // probabilitas terjadi mutasi pada populasi

int m=npop, n=gen; 
int populasi['m']['n']; // matriks populasi
int induk['m']['n'];
int anak['m']['n'];
double x['n'], y['n']; // matriks posisi x dan y kota
double jarak['n']['n']; // matriks jarak antar kota
double fitness['m']; // matriks penampung fitness tiap khromosom (jarak yang dilalui)
double min_best, min_better;
int khromTerbaik['n']; // khromosom dengan fitness terkecil dari populasi sebelumnya
int khromBaik['n']; // khromosom dengan fitness terkecil dari populasi baru

/*************************************************************************************/
double unirand();
void point();
void input();
void generate(); // generate populasi
void nilaiFit(); // cek fitness
void best(); // untuk ngisi dulu khromTerbaik
void better(); // untuk ngisi khromBaik
void best_of_the_best(); // bandingin baik dan terbaik
void selectRoulette();
// void crossover(); 
void cross_greedy();
void mutasi(); 
void swaper(); 
//void empat();
//void lima();
//void enam();
void copyi();
void fitKhrom();
void recu(int orde);
// void print_matrix(int *matrix, int rows, int cols);// print matriks, untuk cek
void printp();
void printi();
void printa();
void printpf();
void printxy();
void printj();
void print_minFit();
void print_file();
void gnu_plot();

/************************************************************************************/
/* main program */
int main(int argc, char **argv){ 
    cout << "--- Genetic Algorithm for TSP ---\n";
    srand(time(NULL));
    input(); // generate titik random, lalu dihitung jaraknya
    //printxy();
    //printj();
    generate(); // generate populasi random
    nilaiFit();
    best();
    for (int i=0; i<GA_MAXITER;i++){
        //printpf();
        print_minFit(); // print kromosom terbaik dan fitnessnya
        selectRoulette(); // dari populasi -> induk
        //cout << endl;
        //printi();
        
        //crossover(); // kawinkan induk -> anak
        cross_greedy();
        //cout << endl;
        //printa();
        swaper(); // biar di cek dl siapa th ada yg terbaik sblm d mutasi   
        nilaiFit();
        better();
        best_of_the_best();
        
        mutasi(); // mutasikan anak -> anak termutasi
        //cout << endl;
        //printa();
        swaper(); // swap anak dan populasi -> populasi baru
        nilaiFit(); // nyari fitness di populasi
        better(); // nyari fitness terbaik di populasi
        best_of_the_best(); // bandingkan yang terbaik dg terbaik sblmnya
    }
    print_file();
    gnu_plot();
    print_minFit(); 
    cout << endl;

    // algorithma tambahan dari saya, HOHOHO
    for (int i=gen;i>0;i--){
        recu(i);}
    //recu(gen);

    cout<< endl;
    fitKhrom(); 
    print_file();
    gnu_plot();
    return 0;
}

/***********************************************************************************/
double unirand(){
    return ((double)rand()/(double)RAND_MAX);
}

void point(){
    for (int i=0;i<gen;i++){
        x[i] = MAX*unirand();
        y[i] = MAX*unirand();}
}

void input(){
    point();
    for (int i=0;i<gen;i++){
        for (int j=0;j<=i;j++){
            if (j==i){
                jarak[i][j] = 0.;}
            else{
                jarak[i][j] = sqrt((x[j]-x[i])*(x[j]-x[i]) + (y[j]-y[i])*(y[j]-y[i]));}}}
    
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
    int a, b;
    double jpop;
    for (int i=0;i<npop;i++){
        jpop = 0.;
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


void selectRoulette(){
    double sumfitness=0.;
    double fit['m'];
    double cumfitness['m'];
    double tot=0.;
    double r;
    
    for (int i=0;i<npop;i++){
        fit[i] = 1./(double)fitness[i];} // kasus pencarian minimum

    for (int i=0;i<npop;i++){
        sumfitness = sumfitness + fit[i];}

    for (int i=0;i<npop;i++){
        cumfitness[i] = tot + (fit[i]/sumfitness);
        tot = cumfitness[i];}
    
    for (int i=0;i<npop;i++){
        r = (double)rand()/(double)RAND_MAX;
        for (int j=0;j<npop;j++){
            if (r < cumfitness[j]){
                for (int k=0;k<gen;k++){
                    induk[i][k] = populasi[j][k];}
                break;}}}
}

void cross_greedy(){
    int bpk['n'];
    int ibu['n'];
    int w[4], q;
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){ // inisiasi pasangan
            bpk[j] = induk[i%gen][j];
            ibu[j] = induk[(i+1)%gen][j];}
        
        anak[i][0] = rand()%gen; // inisiasi gen anak
        q = anak[i][0];
        for (int j=1;j<gen;j++){
            for (int k=0;k<gen;k++){
                k += gen;
                if (bpk[k%gen] == q){
                    w[0] = bpk[(k-1)%gen];
                    w[1] = bpk[(k+1)%gen];}
                if (ibu[k%gen] == q){
                    w[2] = ibu[(k-1)%gen];
                    w[3] = ibu[(k+1)%gen];}
                k -= gen;}
            
            int res=w[0]; // nyari gen sebelah dg fitness terkecil
            for (int l=1;l<4;l++){
                if (jarak[q][w[l]] < jarak[q][res]){
                    res = w[l];}}
            
            bool sama;
            do {  // check gen sebelumnya di khromosom anak
                sama = false;
                for (int m=0;m<j;m++){
                    if (res == anak[i][m]){
                        sama = true;
                        res = rand()%gen;}} // jika ada yang sama, ambil random
            } while (sama);
            anak[i][j] = res;
            q = res;}}
    
    // anak jadi induk
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            induk[i][j] = anak[i][j];}}
}

void mutasi(){
    double p;
    int gen_a, gen_b;
    // copyi();
    for (int i=0;i<npop;i++){
        p = ((double)rand()/(double)RAND_MAX);
        if (p <= pMut){
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

void copyi(){
    for (int i=0;i<npop;i++){
        for (int j=0;j<gen;j++){
            anak[i][j] = induk[i][j];}}
}

/*
void empat(){
    int node1, node2, node3, node4, s;
    for (int i=0;i<gen;i++){
        i += gen;
        node1 = khromTerbaik[i%gen];
        node2 = khromTerbaik[(i+1)%gen];
        node3 = khromTerbaik[(i+2)%gen];
        node4 = khromTerbaik[(i+3)%gen];
        if ((jarak[node1][node2] + jarak[node3][node4]) > (jarak[node1][node3] + jarak[node2][node4])){
            s = khromTerbaik[(i+1)%gen];
            khromTerbaik[(i+1)%gen] = khromTerbaik[(i+2)%gen];
            khromTerbaik[(i+2)%gen] = s;}
        i -= gen;}
}

void lima(){
    int node1, node2, node3, node4, node5, s;
    for (int i=0;i<gen;i++){
        i += gen;
        node1 = khromTerbaik[i%gen];
        node2 = khromTerbaik[(i+1)%gen];
        node4 = khromTerbaik[(i+3)%gen];
        node5 = khromTerbaik[(i+4)%gen];
        if ((jarak[node1][node2] + jarak[node4][node5]) > (jarak[node1][node4] + jarak[node2][node5])){
            s = khromTerbaik[(i+1)%gen];
            khromTerbaik[(i+1)%gen] = khromTerbaik[(i+3)%gen];
            khromTerbaik[(i+3)%gen] = s;}
        i -= gen;}
}

void enam(){
    int node1, node2, node3, node4, node5, node6, s;
    for (int i=0;i<gen;i++){
        i += gen;
        node1 = khromTerbaik[i%gen];
        node2 = khromTerbaik[(i+1)%gen];
        node5 = khromTerbaik[(i+4)%gen];
        node6 = khromTerbaik[(i+5)%gen];
        if ((jarak[node1][node2] + jarak[node5][node6]) > (jarak[node1][node5] + jarak[node2][node6])){
            s = khromTerbaik[(i+1)%gen];
            khromTerbaik[(i+1)%gen] = khromTerbaik[(i+4)%gen];
            khromTerbaik[(i+4)%gen] = s;}
        i -= gen;}
}
*/

void recu(int orde){
    int node1, node2, node3, node4, s;
    for (int j=orde;j>3;j--){
        for (int i=0;i<gen;i++){
            i += gen;
            node1 = khromTerbaik[i%gen];
            node2 = khromTerbaik[(i+1)%gen];
            node3 = khromTerbaik[(i+j-2)%gen];
            node4 = khromTerbaik[(i+j-1)%gen];
            if ((jarak[node1][node2] + jarak[node3][node4]) > (jarak[node1][node3] + jarak[node2][node4])){
                s = khromTerbaik[(i+1)%gen];
                khromTerbaik[(i+1)%gen] = khromTerbaik[(i+j-2)%gen];
                khromTerbaik[(i+j-2)%gen] = s;}
            i -= gen;}
        //cout << orde << " ";
        }
}

void fitKhrom(){
    int a, b;
    double fit;
    fit = 0.;
    for (int j=0;j<gen;j++){
        j += gen;
        a = khromTerbaik[j%gen];
        b = khromTerbaik[(j+1)%gen];
        fit += jarak[a][b];
        j -= gen;}

    for (int j=0;j<gen;j++){
        cout << khromTerbaik[j] << "\t";}
    cout << "... (" << fit << ")" << endl;   
} 

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

void printxy(){
    for (int i=0;i<gen;i++){
        cout << x[i] << "\t" << y[i] << endl;}
}

void print_minFit(){
    for (int j=0;j<gen;j++){
        cout << khromTerbaik[j] << "\t";}
    cout << "... (" << min_best << ")" << endl;
}

void print_file(){
    ofstream out;
    out.open("gaTSP.txt");
    for (int i=0;i<gen;i++){
        out << x[khromTerbaik[i]] << " " << y[khromTerbaik[i]] << endl;}
    out << x[khromTerbaik[0]] << " " << y[khromTerbaik[0]] << endl;
    out.close();
}
        
void gnu_plot(){
    ofstream ploter;
    ploter.open("gaTSP_plot.in");
    ploter << "# gnuplot input file GA for TSP\n";
    double aa = -1.*MAX/10.;
    double bb = MAX + (MAX/10.);
    ploter << "set xrange [" << aa << ":" << bb << "]\n";
    ploter << "set yrange [" << aa << ":" << bb << "]\n";
    //ploter << "set cbrange [0:1]\n";
    ploter << "set nokey\n";
    ploter << "plot \"gaTSP.txt\" with lines lc 3, \"gaTSP.txt\"\n";
    ploter.close();

    system("gnuplot -persist < gaTSP_plot.in");
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
