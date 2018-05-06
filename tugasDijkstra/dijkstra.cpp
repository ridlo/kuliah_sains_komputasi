#include<iostream>
#define INF 999
using namespace std;

unsigned int node, jalan, i, j, a, b;
float dSimpul[100][100];
float jSimpul[100];
char ans;

void jNode(){
    cout << "======== Dijkstra Algorithm ========\n";
    cout << "Masukkan jumlah node       = "; cin >> node;
    cout << "Masukkan node start        = "; cin >> a;
    cout << "Masukkan node finish       = "; cin >> b;
    cout << "Masukkan jarak tiap titik \n";
    
    // isi matriks dengan infinity
    for (i=0; i<node; i++){
        for (j=0; j<node; j++){
            dSimpul[i][j] = INF;
        }
    }
    // isi matriks jarak dengan infinity
    /*for (i=0; i<node; i++){
        jSimpul[i] = INF;
        jSimpul[a-1] = 0;
    }*/

    // ganti isi matriks
    do {
        cout << "Awal  | Tujuan | Jarak\n"; 
        cin >> i; cout << '\t'; cin >> j; cout << "\t"; cin >> dSimpul[i-1][j-1]; cout << "\n";
        if (i > node || j > node){
            cout << "Node yang anda masukkan melebihi input jumlah node.\n";
            dSimpul[i-1][j-1] = INF;
        }
        cout << "                       Input jalur lagi? (y/n) "; cin >> ans;
    } while (ans != 'n');
}

struct vertec{
    int node;
    float jarak;
} j[100];

vertec minJ(vertec j){
    float min=INF;
    for (i=0; i<node; i++){
        if (j.jarak
}
/*
void dijkstra(){
    do {
        jarak += djarak;
    } while ();
}
*/

int main(){
    jNode();
    cout << "\n=== Matrix node input anda ===\n";
    for (i=0; i<node; i++){
        for (j=0; j<node; j++){
            cout << dSimpul[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "Posisi awal  = " << a << "\n";
    cout << "Tujuan akhir = " << b << "\n";

    return 0;
}
