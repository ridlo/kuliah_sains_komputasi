#include<iostream>
#include<fstream>
#include<time.h>
#include "lcg.h"
using namespace std;

double unirand(){
    return (double)randu()/(double)MAX_RAND;
}

int main(){
    int N = 1000000;
    rseed(time(NULL));
    ofstream out("random.txt");
    for (int i=0;i<N;i++){
        out << unirand() << " " << unirand() << endl;
    }
    out.close();
    
    return 0;
}
