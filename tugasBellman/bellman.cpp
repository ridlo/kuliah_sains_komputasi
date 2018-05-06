#include <iostream>
#define INF 9999
using namespace std;

int main(){
    int n=5;
    int R[5][5] = {{0, 7, 4, INF, INF},
                   {INF, 0, 3, INF, INF},
                   {2, 2, 0, 5, 2},
                   {INF, 3, 3, 0, INF},
                   {INF, INF, 3, 1, 0}};
    int Di[5], Df[5];
    int df;
    // mencari rute terpendek untuk seluruh kota lain dari satu kota
    //Bellman Ford Method
    //inisiasi
    for (int i=0;i<n;i++){
        Di[i] = R[0][i];
        Df[i] = INF;}
    
    int k=0; 
    bool check;
    do{
        Df[0] = 0;
        for (int i=1;i<n;i++){
            for (int j=0;j<n;j++){
                df = Di[j] + R[j][i];
                if (df < Df[i]){ Df[i] = df;}}}
        // check
        check=true;
        for (int i=0;i<n;i++){
            if (Di[i] != Df[i]){
                check=false; 
                break;}}
        // swap
        for (int i=0;i<n;i++){Di[i] = Df[i];}
        k++;
    } while(check==false);

    for (int i=0; i<n; i++){
        cout << Di[i] << " ";}
    cout << endl;
    cout << "iterasi = " << k << endl; 
    return 0;
}
